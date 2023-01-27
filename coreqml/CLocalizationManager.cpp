#include "coreqml/CLocalizationManager.h"

// Qt headers
#include <QtGui/QGuiApplication>

CLocalizationManager::CLocalizationManager( QObject* parent )
    : QObject{ parent },
      m_Translator{},
      m_DefaultTranslator{}
{
    qApp->installTranslator( &m_DefaultTranslator );
    qApp->installTranslator( &m_Translator );
}

void CLocalizationManager::changeTranslator( const QString& translatorFile, const QString& path )
{
    bool defaultOk = m_DefaultTranslator.load( "en_GB", path );
    bool currentOk = m_Translator.load( translatorFile, path );

    Q_ASSERT_X( defaultOk && currentOk, "translation", "Cannot install translator" );

    Q_EMIT onTranslatorChanged();
}
