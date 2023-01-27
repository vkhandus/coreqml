#include "StackController.h"

// Core headers
#include "coreqml/ViewControllerFactory.h"

// Qt headers
#include <QtCore/QTimer>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>

StackController::StackController( const QUrl& source, QObject* parent )
    : ViewController{ source, parent }
{
}

StackController::StackController( ViewController* rootController, const QUrl& source, QObject* parent )
    : ViewController{ source, parent }
{
    pushView( rootController );
}

StackController::~StackController()
{
    qDeleteAll( m_Controllers );
}

QList<ViewController*> StackController::viewControllers() const
{
    return m_Controllers;
}

void StackController::onViewAttached( QQuickItem* item )
{
    ViewController::onViewAttached( item );
    Q_EMIT viewControllersChanged();
}

void StackController::resetRootViewController( ViewController* viewController )
{
    if ( viewController )
    {
        StackedControllers tmp;
        tmp.swap( m_Controllers );

        // This signal will launch QML Stack::onViewControllerChanged, which will call destroy() for all views.
        // However, actual destroy() will happens on next runloop iteration ( as specified in docs )
        // That is why below is a magic with QTimer::singleShot: we could only delete an assigned controller when
        // QML views will be deleted, so we schedule deletion with QTimer::singleShot. Also, in timer's handler
        // we will emit viewControllersChanged() signal to create new view for viewController.
        Q_EMIT viewControllersChanged();

        m_Controllers.push_back( viewController );
        QTimer::singleShot( 0, this, [ = ] {
            qDeleteAll( tmp );
            Q_EMIT viewControllersChanged();
        } );
    }
}

void StackController::replaceViewController( ViewController* viewController, int index )
{
    if ( index < m_Controllers.size() )
    {
        ViewController* oldViewController = m_Controllers.takeAt( index );

        // This signal will launch QML Stack::onViewControllerChanged, which will call destroy() for all views.
        // However, actual destroy() will happens on next runloop iteration ( as specified in docs )
        // That is why below is a magic with QTimer::singleShot: we could only delete an assigned controller when
        // QML views will be deleted, so we schedule deletion with QTimer::singleShot. Also, in timer's handler
        // we will emit viewControllersChanged() signal to create new view for viewController.
        Q_EMIT viewControllersChanged();

        m_Controllers.insert( index, viewController );
        QTimer::singleShot( 0, this, [ = ] {
            delete oldViewController;
            Q_EMIT viewControllersChanged();
        } );
    }
}

void StackController::pushView( ViewController* viewController )
{
    if ( viewController )
    {
        viewController->setStackController( this );
        m_Controllers.push_back( viewController );
        Q_EMIT viewControllersChanged();
    }
}

void StackController::popView()
{
    if ( !m_Controllers.isEmpty() )
    {
        ViewController* toRemove = m_Controllers.takeLast();
        Q_EMIT viewControllersChanged();
        toRemove->deleteLater();
    }
}

bool StackController::popToView( const ViewController* viewController )
{
    if ( std::find( std::begin( m_Controllers ), std::end( m_Controllers ), viewController ) != std::end( m_Controllers ) )
    {
        QVector<ViewController*> toRemove;
        while ( m_Controllers.last() != viewController )
        {
            toRemove.push_back( m_Controllers.takeLast() );
        }

        if ( !toRemove.empty() )
        {
            Q_EMIT viewControllersChanged();

            for ( auto* item : toRemove )
            {
                item->deleteLater();
            }
        }

        return true;
    }

    return false;
}

void StackController::popToRootView()
{
    QVector<ViewController*> toRemove;
    while ( m_Controllers.size() > 1 )
    {
        toRemove.push_back( m_Controllers.takeLast() );
    }

    if ( !toRemove.empty() )
    {
        Q_EMIT viewControllersChanged();

        for ( auto* item : toRemove )
        {
            item->deleteLater();
        }
    }
}

void StackController::onViewDidBecomeActive()
{
    ViewController::onViewDidBecomeActive();
}

void StackController::onViewDidBecomeInactive()
{
    ViewController::onViewDidBecomeInactive();
}

ViewController* StackController::resetRootView( const QVariantMap& params )
{
    ViewController* vc = nullptr;

    if ( params.contains( "class" ) )
    {
        vc = ViewControllerFactory::instance().createViewController( params[ "class" ].toString(), params );
    }
    else if ( params.contains( "source" ) )
    {
        vc = new ViewController{ params[ "source" ].toUrl(), nullptr, params };
    }

    resetRootViewController( vc );

    QQmlEngine::setObjectOwnership( vc, QQmlEngine::CppOwnership );
    return vc;
}

ViewController* StackController::pushView( const QVariantMap& params )
{
    ViewController* vc = nullptr;

    if ( params.contains( "class" ) )
    {
        vc = ViewControllerFactory::instance().createViewController( params[ "class" ].toString(), params );
    }
    else if ( params.contains( "source" ) )
    {
        vc = new ViewController{ params[ "source" ].toUrl(), nullptr, params };
    }

    pushView( vc );

    QQmlEngine::setObjectOwnership( vc, QQmlEngine::CppOwnership );
    return vc;
}
