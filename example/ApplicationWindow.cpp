#include "ApplicationWindow.h"

// Core headers
#include "coreqml/ViewController.h"

#include "SplashViewController.h"

ApplicationWindow::ApplicationWindow( QWindow* parent /* = nullptr */ )
    : CApplicationWindow{ parent }
{
    // Common::registerMetaTypes( engine() );

    // set default app window color to black
    setColor( Qt::black );
    setSource( QUrl{ "qrc:/QML/ExampleWindow.qml" } );

    auto pSplashCtrl = new SplashViewController;
    connect( pSplashCtrl, &SplashViewController::loaded, this, &ApplicationWindow::initializeUI );
    connect( pSplashCtrl, &SplashViewController::loaded, pSplashCtrl, &SplashViewController::deleteLater );
    setRootViewController( pSplashCtrl );
}

ApplicationWindow::~ApplicationWindow() = default;

void ApplicationWindow::initializeUI()
{
    // QmlRegisterHelper::registerMetaTypes();
    // QmlRegisterHelper::registerContextProperties( rootContext() );

    Q_EMIT loaded();
}
