#ifndef EX_APPLICATION_WINDOW_H
#define EX_APPLICATION_WINDOW_H

// Core headers
#include "coreqml/CApplicationWindow.h"

class ApplicationWindow : public CApplicationWindow
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( ApplicationWindow )
public:
    explicit ApplicationWindow( QWindow* parent = nullptr );
    ~ApplicationWindow() override;

protected Q_SLOTS:
    void initializeUI();

Q_SIGNALS:
    void loaded();
};

#endif // EX_APPLICATION_WINDOW_H
