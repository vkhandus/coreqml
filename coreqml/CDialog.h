#ifndef CQML_СDIALOG_H
#define CQML_СDIALOG_H

// Qt headers
#include <QtCore/QObject>
#include <QtCore/QUrl>

class QQuickItem;

class CDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QUrl source READ source CONSTANT )
public:
    enum ResultCode
    {
        Dismissed = -3,
        Rejected,
        Cancelled,
        Succeeded
    };
    Q_ENUM(ResultCode)

    explicit CDialog( QUrl source, QObject* parent = nullptr );

public Q_SLOTS:
    virtual QQuickItem* show();
    virtual void dismiss( int result );

Q_SIGNALS:
    void finished( int result );

protected:
    QUrl source() const;

private:
    QUrl m_ViewSource;
};

#endif // CQML_СDIALOG_H
