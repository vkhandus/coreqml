#include "GameViewController.h"

#include "coreqml/CButtonsDialog.h"

#include <QtCore/QMap>
#include <QtCore/QMetaType>

GameViewController::GameViewController( QObject* parent )
    : ViewController( QUrl{ "qrc:/QML/GameView.qml" }, parent ),
      m_Bricks{},
      m_CurrentBrick{ -1, -1 },
      m_IsPaused{ true }
{
    m_GameTimer.setInterval( 300 );
    m_GameTimer.callOnTimeout( this, &GameViewController::gameTick );

    restartGame();
    setPaused( true );
}

GameViewController::Bricks GameViewController::bricks()
{
    return m_Bricks;
}

QPoint GameViewController::currentBrick()
{
    return m_CurrentBrick;
}

void GameViewController::setPaused( bool isPaused )
{
    if ( isPaused != m_IsPaused )
    {
        m_IsPaused = isPaused;
        Q_EMIT isPausedChanged();
    }

    if ( m_IsPaused )
    {
        m_GameTimer.stop();
    }
    else
    {
        m_GameTimer.start();
    }
}

bool GameViewController::isPaused()
{
    return m_IsPaused;
}

void GameViewController::restartGame()
{
    m_Bricks = Bricks( 12, QVector<bool>( 8, false ) );
    Q_EMIT bricksChanged();
    m_CurrentBrick = { -1, static_cast<int>( m_Bricks[ 0 ].size() / 2 ) };

    setPaused( false );
}

void GameViewController::endGame()
{
    m_CurrentBrick = { -1, -1 };
    m_GameTimer.stop();

    auto* tryAgain = new DialogButtonInfo( "Try again!" );
    auto* quit = new DialogButtonInfo( "Quit" );
    auto* pDialog =
        new CButtonsDialog( QUrl( "qrc:/QML/ButtonsDialog.qml" ), "",
                           "Good luck next time!", { tryAgain, quit }, this );
    connect( pDialog, &CDialog::finished, this, [ = ]( int result ) {
        if ( result == tryAgain->id() )
        {
            restartGame();
        }
        else if ( result == quit->id() )
        {
            Q_EMIT gameOver();
        }
        pDialog->deleteLater();
    } );
    pDialog->show();
}

bool GameViewController::moveBrick( Qt::Key key )
{
    static QMap<Qt::Key, QPoint> DIR_POINT{
        { Qt::Key_Left, { 0, -1 } },
        { Qt::Key_Right, { 0, 1 } },
        { Qt::Key_Down, { 1, 0 } }
    };

    QPoint nextPos = m_CurrentBrick + DIR_POINT[ key ];
    bool canMove = nextPos.x() >= 0 && nextPos.x() < m_Bricks.size() &&
                   nextPos.y() >= 0 && nextPos.y() < m_Bricks[ 0 ].size() &&
                   m_Bricks[ nextPos.x() ][ nextPos.y() ] == false;
    if ( canMove )
    {
        updateBrick( nextPos );
    }

    return canMove;
}

void GameViewController::gameTick()
{
    bool canMove = moveBrick( Qt::Key_Down );
    if ( !canMove )
    {
        if ( m_CurrentBrick.x() < 0 )
        {
            endGame();
            return;
        }

        m_Bricks[ m_CurrentBrick.x() ][ m_CurrentBrick.y() ] = true;
        Q_EMIT bricksChanged();
        updateBrick( { -1, static_cast<int>( m_Bricks[ 0 ].size() / 2 ) } );
    }
}

void GameViewController::updateBrick( QPoint newPosition )
{
    if ( newPosition != m_CurrentBrick )
    {
        m_CurrentBrick = newPosition;
        Q_EMIT currentBrickChanged();
    }
}
