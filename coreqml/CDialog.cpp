#include "coreqml/CDialog.h"

// Core headers
#include "coreqml/CApplication.h"

CDialog::CDialog( QUrl source, QObject* parent )
    : QObject{ parent },
      m_ViewSource{ std::move( source ) }
{
}

QQuickItem* CDialog::show()
{
    return cApp()->dialogManager()->showDialog( this );
}

void CDialog::dismiss( int result )
{
    return cApp()->dialogManager()->dismissDialog( this, result );
}

QUrl CDialog::source() const
{
    return m_ViewSource;
}
