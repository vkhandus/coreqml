#include "CButtonsDialog.h"

namespace
{
    int UNIQUE_AUTO_ID = 128;
}

DialogButtonInfo::DialogButtonInfo( QString title, QObject* parent )
    : QObject{ parent },
      m_ButtonID{ UNIQUE_AUTO_ID++ },
      m_Title{ std::move( title ) }
{
}

int DialogButtonInfo::id() const
{
    return m_ButtonID;
}

QString DialogButtonInfo::title() const
{
    return m_Title;
}

CButtonsDialog::CButtonsDialog( QUrl source, QString title, QString text, DialogButtons buttons, QObject* parent )
    : CDialog{ std::move( source ), parent },
      m_Buttons{ std::move( buttons ) },
      m_Title{ std::move( title ) },
      m_Text{ std::move( text ) }
{
}

CButtonsDialog::~CButtonsDialog()
{
    qDeleteAll( m_Buttons );
}

DialogButtonInfo* CButtonsDialog::addButton( const QString& text )
{
    auto* pButtonInfo = new DialogButtonInfo( text );
    m_Buttons.push_back( pButtonInfo );

    return pButtonInfo;
}

DialogButtons CButtonsDialog::buttons() const
{
    return m_Buttons;
}
