#ifndef CQML_GAME_VIEW_CONTROLLER_H
#define CQML_GAME_VIEW_CONTROLLER_H

#include <coreqml/ViewController.h>

#include <QtCore/QPoint>
#include <QtCore/QTimer>

class GameViewController : public ViewController
{
    Q_OBJECT
    using Bricks = QVector<QVector<bool>>;
    Q_PROPERTY( Bricks bricks READ bricks NOTIFY bricksChanged )
    Q_PROPERTY( QPoint currentBrick READ currentBrick NOTIFY currentBrickChanged )
    Q_PROPERTY( bool isPaused WRITE setPaused READ isPaused NOTIFY isPausedChanged )
public:
    GameViewController( QObject* parent = nullptr );

    Bricks bricks();
    QPoint currentBrick();

    void setPaused( bool isPaused );
    bool isPaused();

public Q_SLOTS:
    void restartGame();
    void endGame();
    bool moveBrick( Qt::Key key );

Q_SIGNALS:
    void bricksChanged();
    void currentBrickChanged();
    void gameOver();
    void isPausedChanged();

private:
    void gameTick();
    void updateBrick( QPoint newPosition );

private:
    Bricks m_Bricks;
    QPoint m_CurrentBrick;
    QTimer m_GameTimer;
    bool m_IsPaused;
};

#endif // CQML_GAME_VIEW_CONTROLLER_H
