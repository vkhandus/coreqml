#include "ViewControllerFactory.h"

ViewControllerFactory& ViewControllerFactory::instance()
{
    static ViewControllerFactory vcf;
    return vcf;
}

ViewController* ViewControllerFactory::createViewController( const QString& name, const QVariantMap& params )
{
    return m_CreateMap[ name ]( params );
}
