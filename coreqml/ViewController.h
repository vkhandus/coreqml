#ifndef CQML_VIEW_CONTROLLER_H
#define CQML_VIEW_CONTROLLER_H

// Qt headers
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVariantMap>

class QQuickView;
class QQuickItem;
class StackController;

class View : public QObject
{
    Q_OBJECT
public:
    enum ViewType
    {
        Generic,
        Stack
    };
    Q_ENUM( ViewType )
};

class ViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QUrl source READ source NOTIFY sourceChanged )
    Q_PROPERTY( QVariantMap params READ params NOTIFY paramsChanged )
    Q_PROPERTY( StackController* stackController READ stackController WRITE setStackController NOTIFY stackControllerChanged )
    Q_PROPERTY( QQuickItem* view READ view NOTIFY viewAttached )

public:
    explicit ViewController( QObject* parent = nullptr ); // This constructor is required to declare this class for qml
    explicit ViewController( QUrl source, QObject* parent = nullptr, QVariantMap params = {} );

    QUrl source() const;
    QVariantMap params() const;

    StackController* stackController() const;
    void setStackController( StackController* stackController );

    QQuickItem* view() const;

    Q_INVOKABLE virtual void onViewAttached( QQuickItem* item );
    Q_INVOKABLE virtual void onViewDetached();

    Q_INVOKABLE virtual void onViewDidBecomeActive();
    Q_INVOKABLE virtual void onViewDidBecomeInactive();

Q_SIGNALS:
    void sourceChanged();
    void paramsChanged();
    void stackControllerChanged();

    void viewAttached();
    void viewDetached();

private:
    QUrl m_Source;
    QVariantMap m_Params;
    QQuickItem* m_pAttachedView;
    StackController* m_pStackController;
};

#endif // CQML_VIEW_CONTROLLER_H
