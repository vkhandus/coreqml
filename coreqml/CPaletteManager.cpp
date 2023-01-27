#include "coreqml/CPaletteManager.h"

CPaletteManager::CPaletteManager( QObject* parent )
    : QObject( parent )
{

}

void CPaletteManager::setPaletteMode( int mode )
{
    if ( mode != m_PaletteMode )
    {
        m_PaletteMode = mode;
        Q_EMIT paletteModeChanged( mode );
    }
}

int CPaletteManager::paletteMode() const
{
    return m_PaletteMode;
}
