#ifndef CQML_CAPPLICATION_H
#define CQML_CAPPLICATION_H

// Core headers
#include "coreqml/CDialogManager.h"
#include "coreqml/CLocalizationManager.h"
#include "coreqml/CPaletteManager.h"
#include "coreqml/CResourcesManager.h"
#include "coreqml/CScreen.h"

// Qt headers
#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtGui/QGuiApplication>

class CApplication : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( CApplication )
    Q_PROPERTY( CDialogManager* dialogManager READ dialogManager CONSTANT )
    Q_PROPERTY( CLocalizationManager* localizationManager READ localizationManager CONSTANT )
    Q_PROPERTY( CScreen* screen READ screen CONSTANT )
    Q_PROPERTY( CResourcesManager* resourcesManager READ resourcesManager CONSTANT )
    Q_PROPERTY( CPaletteManager* paletteManager READ paletteManager CONSTANT )

public:
    CApplication( int& argc, char** argv );
    ~CApplication() override;

    virtual int run();

    CDialogManager* dialogManager() const;
    CLocalizationManager* localizationManager() const;
    CScreen* screen() const;
    CResourcesManager* resourcesManager() const;
    CPaletteManager* paletteManager() const;

    static CApplication* instance();

protected:
    static CApplication* m_pSharedInstance;

private:
    QGuiApplication m_QApp;
    std::unique_ptr<CDialogManager> m_pDialogManager;
    std::unique_ptr<CLocalizationManager> m_pLocalizationManager;
    std::unique_ptr<CScreen> m_pScreenInfo;
    std::unique_ptr<CResourcesManager> m_pResourcesManager;
    std::unique_ptr<CPaletteManager> m_pPaletteManager;
};

CApplication* cApp();

#endif // CQML_CAPPLICATION_H
