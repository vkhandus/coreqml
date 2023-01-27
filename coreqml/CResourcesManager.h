#ifndef CQML_СRESOURCES_MANAGER_H
#define CQML_СRESOURCES_MANAGER_H

// Qt headers
#include <QtCore/QObject>

class CResourcesManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( CResourcesManager )
public:
    explicit CResourcesManager( QObject* parent = nullptr );

    Q_INVOKABLE bool isResourceValid( const QString& url );
};

#endif // CQML_СRESOURCES_MANAGER_H
