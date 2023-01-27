#ifndef EX_SPLASH_VIEW_CONTROLLER_H
#define EX_SPLASH_VIEW_CONTROLLER_H

#include "coreqml/ViewController.h"

#include <QtCore/QUrl>

class SplashViewController : public ViewController
{
    Q_OBJECT
    Q_PROPERTY( QUrl splash MEMBER m_Splash CONSTANT )
public:
    explicit SplashViewController( QObject* parent = nullptr );

Q_SIGNALS:
    void loaded();

private:
    QUrl m_Splash;
};

#endif // EX_SPLASH_VIEW_CONTROLLER_H
