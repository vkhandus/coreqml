#ifndef CQML_–°RESOURCES_MANAGER_H
#define CQML_–°RESOURCES_MANAGER_H

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

#endif // CQML_–°RESOURCES_MANAGER_H
