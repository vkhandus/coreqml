#include "coreqml/CResourcesManager.h"

// Qt headers
#include <QtCore/QResource>

CResourcesManager::CResourcesManager( QObject* parent )
    : QObject( parent )
{

}

bool CResourcesManager::isResourceValid( const QString& url )
{
    QResource res{ url.right( url.length() - 3 ) }; // -3 to remove qrc, we need it start from ":/"
    return res.isValid();
}
