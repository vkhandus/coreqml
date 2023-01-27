#ifndef CQML_СPALETTE_MANAGER_H
#define CQML_СPALETTE_MANAGER_H

// Qt headers
#include <QtCore/QObject>

class CPaletteManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int paletteMode READ paletteMode WRITE setPaletteMode NOTIFY paletteModeChanged )
    Q_DISABLE_COPY_MOVE( CPaletteManager )
public:
    explicit CPaletteManager( QObject* parent = nullptr );

    void setPaletteMode( int mode );
    int paletteMode() const;

Q_SIGNALS:
    void paletteModeChanged( int mode );

private:
    int m_PaletteMode = -1;
};

#endif // CQML_СPALETTE_MANAGER_H
