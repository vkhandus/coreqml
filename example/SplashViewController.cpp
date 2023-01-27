#include "SplashViewController.h"

// Qt headers
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>

SplashViewController::SplashViewController( QObject* parent )
    : ViewController{ QUrl{ "qrc:/QML/SplashView.qml" }, parent },
      m_Splash( "qrc:/res/splash.gif" )
{
}
