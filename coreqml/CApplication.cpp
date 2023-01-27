#include "coreqml/CApplication.h"

// Core headers
#include "coreqml/CDialog.h"
#include "coreqml/CDialogManager.h"
#include "coreqml/CLocalizationManager.h"
#include "coreqml/CScreen.h"
#include "coreqml/StackController.h"
#include "coreqml/ViewController.h"

static void registerQMLTypes()
{
    // register CoreQML types
    qmlRegisterSingletonInstance( "CoreQML", 1, 0, "CApp", CApplication::instance() );

    qmlRegisterUncreatableType<CDialogManager>( "CoreQML", 1, 0, "CDialogManager", "DialogManager can only be accessed from CApp" );
    qmlRegisterUncreatableType<CDialog>( "CoreQML", 1, 0, "Dialog", "Dialog type is not accessible" );
    qmlRegisterUncreatableType<CLocalizationManager>( "CoreQML", 1, 0, "LocalizationManager", "LocalizationManager can only be accessed from CApp" );
    qmlRegisterUncreatableType<CPaletteManager>( "CoreQML", 1, 0, "PaletteManager", "PaletteManager can only be accessed from CApp" );
    qmlRegisterUncreatableType<CResourcesManager>( "CoreQML", 1, 0, "ResourcesManager", "ResourcesManager can only be accessed from CApp" );
    qmlRegisterUncreatableType<CScreen>( "CoreQML", 1, 0, "ScreenInfo", "ScreenInfo can only be accessed from CApp" );
    qmlRegisterUncreatableType<View>( "CoreQML", 1, 0, "ViewType", "ViewType should not be created. It only provides access to enum constants" );
    qmlRegisterUncreatableType<ViewController>( "CoreQML", 1, 0, "ViewController", "ViewController should not be created" );
    qmlRegisterUncreatableType<StackController>( "CoreQML", 1, 0, "StackController", "StackController should not be created" );

    // QML singletons
    qmlRegisterSingletonType( QUrl( "qrc:/Core/Application.qml" ), "CoreQML", 1, 0, "App" );

    // QML types
    qmlRegisterType( QUrl( "qrc:/Core/ApplicationWindow.qml" ), "CoreQML", 1, 0, "ApplicationWindow" );
    qmlRegisterType( QUrl( "qrc:/Core/Button.qml" ), "CoreQML", 1, 0, "Button" );
    qmlRegisterType( QUrl( "qrc:/Core/ButtonPalette.qml" ), "CoreQML", 1, 0, "ButtonPalette" );
    qmlRegisterType( QUrl( "qrc:/Core/ButtonPaletteData.qml" ), "CoreQML", 1, 0, "ButtonPaletteData" );
    qmlRegisterType( QUrl( "qrc:/Core/ButtonPaletteSelector.qml" ), "CoreQML", 1, 0, "ButtonPaletteSelector" );
    qmlRegisterType( QUrl( "qrc:/Core/ButtonsDialogController.qml" ), "CoreQML", 1, 0, "ButtonsDialogController" );
    qmlRegisterType( QUrl( "qrc:/Core/CoreStyle.qml" ), "CoreQML", 1, 0, "CoreStyle" );
    qmlRegisterType( QUrl( "qrc:/Core/DialogView.qml" ), "CoreQML", 1, 0, "DialogView" );
    qmlRegisterType( QUrl( "qrc:/Core/DialogController.qml" ), "CoreQML", 1, 0, "DialogController" );
    qmlRegisterType( QUrl( "qrc:/Core/NavigationBar.qml" ), "CoreQML", 1, 0, "NavigationBar" );
    qmlRegisterType( QUrl( "qrc:/Core/Palette.qml" ), "CoreQML", 1, 0, "Palette" );
    qmlRegisterType( QUrl( "qrc:/Core/Stack.qml" ), "CoreQML", 1, 0, "Stack" );
    qmlRegisterType( QUrl( "qrc:/Core/View.qml" ), "CoreQML", 1, 0, "View" );
}

CApplication* CApplication::m_pSharedInstance = nullptr;

CApplication::CApplication( int& argc, char** argv )
    : QObject{ nullptr },
      m_QApp{ argc, argv },
      m_pDialogManager{ std::make_unique<CDialogManager>() },
      m_pLocalizationManager{ std::make_unique<CLocalizationManager>() },
      m_pScreenInfo{ std::make_unique<CScreen>() },
      m_pResourcesManager{ std::make_unique<CResourcesManager>() },
      m_pPaletteManager{ std::make_unique<CPaletteManager>() }
{
    m_pSharedInstance = this;

    registerQMLTypes();
}

CApplication::~CApplication()
{
    m_pSharedInstance = nullptr;
}

int CApplication::run()
{
    return QGuiApplication::exec();
}

CDialogManager* CApplication::dialogManager() const
{
    return m_pDialogManager.get();
}

CLocalizationManager* CApplication::localizationManager() const
{
    return m_pLocalizationManager.get();
}

CScreen* CApplication::screen() const
{
    return m_pScreenInfo.get();
}

CResourcesManager* CApplication::resourcesManager() const
{
    return m_pResourcesManager.get();
}

CPaletteManager* CApplication::paletteManager() const
{
    return m_pPaletteManager.get();
}

CApplication* CApplication::instance()
{
    return m_pSharedInstance;
}

CApplication* cApp()
{
    return CApplication::instance();
}
