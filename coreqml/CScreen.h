#ifndef CQML_СSCREEN_H
#define CQML_СSCREEN_H

// Qt headers
#include <QtCore/QObject>
#include <QtCore/QSize>

class CScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY( qreal dpiX READ dpiX CONSTANT )
    Q_PROPERTY( qreal dpiY READ dpiY CONSTANT )
    Q_PROPERTY( qreal dpi READ dpi CONSTANT )
    Q_PROPERTY( qreal uiSizeMultiplier READ uiSizeMultiplier NOTIFY uiSizeMultiplierChanged )
    Q_PROPERTY( qreal fontSizeMultiplier READ fontSizeMultiplier NOTIFY fontSizeMultiplierChanged )
    Q_PROPERTY( QSize screenSize READ screenSize CONSTANT )
    Q_DISABLE_COPY_MOVE( CScreen )
public:
    explicit CScreen( QObject* parent = nullptr );

    qreal dpiX() const;
    void setDpiX( qreal dpiX );

    qreal dpiY() const;
    void setDpiY( qreal dpiY );

    qreal dpi() const;
    void setDpi( qreal dpi );

    qreal uiSizeMultiplier() const;
    void setUISizeMultiplier( qreal multiplier );

    qreal fontSizeMultiplier() const;
    void setFontSizeMultiplier( qreal multiplier );

    QSize screenSize() const;
    void setScreenSize( const QSize& size );

Q_SIGNALS:
    void fontSizeMultiplierChanged();
    void uiSizeMultiplierChanged();

private:
    qreal m_DpiX;
    qreal m_DpiY;
    qreal m_Dpi;
    qreal m_UiSizeMultiplier;
    qreal m_FontMultiplier;
    QSize m_Size;
};

#endif // CQML_СSCREEN_H
