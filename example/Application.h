#ifndef EX_APPLICATION_H
#define EX_APPLICATION_H

// Core headers
#include "coreqml/CApplication.h"

// Qt headers
#include <QtCore/QPointer>

// Forward declaration
class ApplicationWindow;

class Application : public CApplication
{
    Q_OBJECT

public:
    Application( int& argc, char** argv );

    QPointer<ApplicationWindow> appWindow() const;
    static Application* instance();

    int run() override;

private:
    QPointer<ApplicationWindow> m_pAppWindow;
};

#endif // EX_APPLICATION_H
