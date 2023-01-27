#ifndef CQML_STACK_CONTROLLER_H
#define CQML_STACK_CONTROLLER_H

// Core headers
#include "coreqml/ViewController.h"

// Qt headers
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtQml/QQmlListProperty>

class StackController : public ViewController
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( StackController )
    Q_PROPERTY( QQmlListProperty<ViewController> viewControllers READ qmlViewControllers NOTIFY viewControllersChanged )

public:
    explicit StackController( const QUrl& source = QUrl( "qrc:/Core/Stack.qml" ), QObject* parent = nullptr );
    explicit StackController( ViewController* rootController, const QUrl& source = QUrl( "qrc:/Core/Stack.qml" ), QObject* parent = nullptr );
    ~StackController() override;

    QQmlListProperty<ViewController> qmlViewControllers()
    {
        return { this, &m_Controllers };
    }

    QList<ViewController*> viewControllers() const;

    void pushView( ViewController* viewController );
    void resetRootViewController( ViewController* viewController );
    void replaceViewController( ViewController* viewController, int index );

    Q_INVOKABLE ViewController* resetRootView( const QVariantMap& params );
    Q_INVOKABLE ViewController* pushView( const QVariantMap& params );
    Q_INVOKABLE void popView();
    Q_INVOKABLE bool popToView( const ViewController* viewController );
    Q_INVOKABLE void popToRootView();

    Q_INVOKABLE void onViewAttached( QQuickItem* item ) override;
    Q_INVOKABLE void onViewDidBecomeActive() override;
    Q_INVOKABLE void onViewDidBecomeInactive() override;

Q_SIGNALS:
    void viewControllersChanged();

private:
    using StackedControllers = QList<ViewController*>;
    StackedControllers m_Controllers;
};

#endif // CQML_STACK_CONTROLLER_H
