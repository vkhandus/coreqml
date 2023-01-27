#include "ViewController.h"

// Core headers
#include "coreqml/StackController.h"

// Qt headers
#include <QtQuick/QQuickItem>

// This constructor is required to declare this class for qml
ViewController::ViewController( QObject* parent )
    : ViewController{ QUrl{ "qrc:/Core/View.qml" }, parent, {} }
{
}

ViewController::ViewController( QUrl source, QObject* parent, QVariantMap params )
    : QObject{ parent },
      m_Source{ std::move( source ) },
      m_Params{ std::move( params ) },
      m_pAttachedView{ nullptr },
      m_pStackController{ nullptr }
{
}

QUrl ViewController::source() const
{
    return m_Source;
}

QVariantMap ViewController::params() const
{
    return m_Params;
}

StackController* ViewController::stackController() const
{
    return m_pStackController;
}

void ViewController::setStackController( StackController* stackController )
{
    if ( m_pStackController == stackController )
    {
        return;
    }

    m_pStackController = stackController;
    Q_EMIT stackControllerChanged();
}

QQuickItem* ViewController::view() const
{
    return m_pAttachedView;
}

void ViewController::onViewAttached( QQuickItem* item )
{
    m_pAttachedView = item;
    Q_EMIT viewAttached();
}

void ViewController::onViewDetached()
{
    if ( m_pAttachedView )
    {
        m_pAttachedView = nullptr;
        Q_EMIT viewDetached();
    }
}

void ViewController::onViewDidBecomeActive()
{
}

void ViewController::onViewDidBecomeInactive()
{
}
