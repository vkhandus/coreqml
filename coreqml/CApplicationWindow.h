#ifndef CQML_CAPPLICATION_WINDOW_H
#define CQML_CAPPLICATION_WINDOW_H

#include "coreqml/ViewController.h"

// Qt headers
#include <QtQuick/QQuickView>

class CApplicationWindow : public QQuickView
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( CApplicationWindow )
    Q_PROPERTY( ViewController* rootViewController READ rootViewController NOTIFY rootViewControllerChanged )

public:
    explicit CApplicationWindow( QWindow* parent = nullptr );
    ~CApplicationWindow() override;

    void setRootViewController( ViewController* ctrl );
    ViewController* rootViewController();

Q_SIGNALS:
    void windowExposed();
    void rootViewControllerChanged();

protected:
    void exposeEvent( QExposeEvent* event ) override;

private:
    ViewController* m_pRootController;
};

#endif // CQML_CAPPLICATION_WINDOW_H
