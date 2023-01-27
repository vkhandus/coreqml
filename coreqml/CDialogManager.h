#ifndef CQML_СDIALOG_MANAGER_H
#define CQML_СDIALOG_MANAGER_H

// Qt headers
#include <QtCore/QObject>
#include <QtQuick/QQuickItem>

class CDialog;

class CDialogManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( CDialogManager )
public:
    explicit CDialogManager( QObject* parent = nullptr );

    /*!
     *  Links QML DialogManager item with CPP one.
     *  QML DialogManager handles the Dialogs UI.
     */
    Q_INVOKABLE void initialize( QObject* qmlDialogManager );

    /*!
     *  Unlinks QML DialogManager item with CPP one.
     */
    Q_INVOKABLE void deinitialize();

    /*!
     *  Shows dialog. Returns pointer to QML dialog type
     */
    QQuickItem* showDialog( CDialog* dlg );

    /*!
     *  Dismisses dialog
     */
    void dismissDialog( CDialog* dlg, int result );

    /*!
     *  Dismisses all dialogs
     */
    bool dismissAllDialogs();

private:
    QObject* m_pQMLDialogManager = nullptr;
};

#endif // CQML_СDIALOG_MANAGER_H
