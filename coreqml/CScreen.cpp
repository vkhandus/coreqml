#include "CScreen.h"

// Qt headers
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

CScreen::CScreen( QObject* parent )
    : QObject( parent ),
      m_DpiX{},
      m_DpiY{},
      m_Dpi{},
      m_UiSizeMultiplier{ 1. },
      m_FontMultiplier{ 1. },
      m_Size{}
{
    if ( qApp && !qApp->screens().isEmpty() )
    {
        auto screen = qApp->primaryScreen();
        m_DpiX = screen->physicalDotsPerInchX();
        m_DpiY = screen->physicalDotsPerInchY();
        m_Dpi = screen->physicalDotsPerInch();
        m_Size = screen->size();
    }
}

qreal CScreen::dpiX() const
{
    return m_DpiX;
}

void CScreen::setDpiX( qreal dpiX )
{
    m_DpiX = dpiX;
}

qreal CScreen::dpiY() const
{
    return m_DpiY;
}

void CScreen::setDpiY( qreal dpiY )
{
    m_DpiY = dpiY;
}

qreal CScreen::dpi() const
{
    return m_Dpi;
}

void CScreen::setDpi( qreal dpi )
{
    m_Dpi = dpi;
}

void CScreen::setUISizeMultiplier( qreal multiplier )
{
    if ( !qFuzzyCompare( m_UiSizeMultiplier, multiplier ) )
    {
        m_UiSizeMultiplier = multiplier;
        Q_EMIT uiSizeMultiplierChanged();
    }
}

qreal CScreen::fontSizeMultiplier() const
{
    return m_FontMultiplier;
}

void CScreen::setFontSizeMultiplier( qreal multiplier )
{
    if ( !qFuzzyCompare( m_FontMultiplier, multiplier ) )
    {
        m_FontMultiplier = multiplier;
        Q_EMIT fontSizeMultiplierChanged();
    }
}

qreal CScreen::uiSizeMultiplier() const
{
    return m_UiSizeMultiplier;
}

QSize CScreen::screenSize() const
{
    return m_Size;
}

void CScreen::setScreenSize( const QSize& size )
{
    m_Size = size;
}
