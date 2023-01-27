#ifndef CQML_VIEW_CONTROLLER_FACTORY_H
#define CQML_VIEW_CONTROLLER_FACTORY_H

// Qt headers
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

class ViewController;

class ViewControllerFactory
{
public:
    static ViewControllerFactory& instance();

    template<class T>
    void registerViewController( const QString& name )
    {
        m_CreateMap[ name ] = &ViewControllerFactory::create<T>;
    }

    ViewController* createViewController( const QString& name, const QVariantMap& params );

private:
    ViewControllerFactory() = default;

    template<class T>
    static ViewController* create( const QVariantMap& params )
    {
        return new T( params );
    }

    QMap<QString, ViewController* (*)( const QVariantMap& )> m_CreateMap;
};

#endif // CQML_VIEW_CONTROLLER_FACTORY_H
