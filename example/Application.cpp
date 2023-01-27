#include "Application.h"
#include "ApplicationWindow.h"
#include "GameViewController.h"

#include "coreqml/StackController.h"

// Qt headers
#include <QtQml/QQmlEngine>

Application::Application( int& argc, char** argv )
    : CApplication{ argc, argv },
      m_pAppWindow{}
{
}

QPointer<ApplicationWindow> Application::appWindow() const
{
    return m_pAppWindow;
}

Application* Application::instance()
{
    return static_cast<Application*>( m_pSharedInstance );
}

int Application::run()
{
    screen()->setScreenSize( { 1024, 600 } );
    ApplicationWindow view;
    m_pAppWindow = &view;

    connect( m_pAppWindow->engine(), &QQmlEngine::quit, qApp, &QGuiApplication::quit );

    connect( m_pAppWindow, &ApplicationWindow::loaded, this, [ & ] {
        // Setup software language
        // changeLanguage( settings()->value( "Settings/LanguageIndex" ).toInt() );

        // Initial app view controller
        auto* pCtrl = new GameViewController;
        connect( pCtrl, &GameViewController::gameOver, qApp, &QGuiApplication::quit );

        // will be deleted by ApplicationView instance
        StackController* sc = new StackController( QUrl( "qrc:/QML/MainView.qml" ), m_pAppWindow );
        sc->resetRootViewController( pCtrl );

        m_pAppWindow->setRootViewController( sc );
    } );
    m_pAppWindow->show();

    return CApplication::run();
}
