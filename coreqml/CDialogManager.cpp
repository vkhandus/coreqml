#include "CDialogManager.h"

// Core headers
#include "coreqml/CDialog.h"

CDialogManager::CDialogManager( QObject* parent )
    : QObject( parent )
{
}

void CDialogManager::initialize( QObject* qmlDialogManager )
{
    m_pQMLDialogManager = qmlDialogManager;
}

void CDialogManager::deinitialize()
{
    m_pQMLDialogManager = nullptr;
}

QQuickItem* CDialogManager::showDialog( CDialog* dlg )
{
    if ( m_pQMLDialogManager )
    {
        QVariant returnedValue;
        QVariant dialogCtrl = QVariant::fromValue<CDialog*>( dlg );
        QMetaObject::invokeMethod( m_pQMLDialogManager, "showDialogCtrl",
                                   Q_RETURN_ARG( QVariant, returnedValue ),
                                   Q_ARG( QVariant, dialogCtrl ) );
        return qvariant_cast<QQuickItem*>( returnedValue );
    }

    return nullptr;
}

void CDialogManager::dismissDialog( CDialog* dlg, int result )
{
    if ( m_pQMLDialogManager )
    {
        QVariant dialogCtrl = QVariant::fromValue<CDialog*>( dlg );
        QMetaObject::invokeMethod( m_pQMLDialogManager, "dismissDialogCtrl",
                                   Q_ARG( QVariant, dialogCtrl ),
                                   Q_ARG( QVariant, result ) );
    }
}

bool CDialogManager::dismissAllDialogs()
{
    bool result = false;

    if ( m_pQMLDialogManager )
    {
        QVariant returnedValue;
        QVariant onlyBelongsToCurrentView{ false };
        QMetaObject::invokeMethod( m_pQMLDialogManager, "dismissAllDialogs",
                                   Q_RETURN_ARG( QVariant, returnedValue ),
                                   Q_ARG( QVariant, onlyBelongsToCurrentView ) );
        result = returnedValue.toBool();
    }

    return result;
}
