#include "CApplicationWindow.h"

// Qt headers
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>

// Core headers
#include "coreqml/ViewController.h"

CApplicationWindow::CApplicationWindow( QWindow* parent )
    : QQuickView{ parent },
      m_pRootController{ nullptr }
{
    setResizeMode( QQuickView::SizeRootObjectToView );
    rootContext()->setContextProperty( "cAppWindow", this );    
}

CApplicationWindow::~CApplicationWindow() = default;

void CApplicationWindow::setRootViewController( ViewController* ctrl )
{
    if ( m_pRootController != ctrl )
    {
        m_pRootController = ctrl;
        Q_EMIT rootViewControllerChanged();
    }
}

ViewController* CApplicationWindow::rootViewController()
{
    return m_pRootController;
}

void CApplicationWindow::exposeEvent( QExposeEvent* ev )
{
    QQuickView::exposeEvent( ev );
    static bool once = false;

    if ( !once )
    {
        once = true;
        Q_EMIT windowExposed();
    }
}
