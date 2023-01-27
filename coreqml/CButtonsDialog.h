#ifndef CQML_СBUTTONS_DIALOG_H
#define CQML_СBUTTONS_DIALOG_H

// Core headers
#include "coreqml/CDialog.h"

// Qt headers
#include <QtCore/QObject>

class DialogButtonInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY( int id READ id CONSTANT )
    Q_PROPERTY( QString title READ title CONSTANT )

public:
    explicit DialogButtonInfo( QString title, QObject* parent = nullptr );

    int id() const;
    QString title() const;

private:
    int m_ButtonID;
    QString m_Title;
};

using DialogButtons = QList<QObject*>;

class CButtonsDialog : public CDialog
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( CButtonsDialog )
    Q_PROPERTY( QUrl source READ source CONSTANT )
    Q_PROPERTY( DialogButtons buttons READ buttons CONSTANT )
    Q_PROPERTY( QString title MEMBER m_Title CONSTANT )
    Q_PROPERTY( QString text MEMBER m_Text CONSTANT )

public:
    CButtonsDialog( QUrl source, QString title, QString text,
                   DialogButtons buttons = {},
                   QObject* parent = nullptr );

    ~CButtonsDialog() override;

    DialogButtonInfo* addButton( const QString& text );
    DialogButtons buttons() const;

public:
    DialogButtons m_Buttons;
    QString m_Title;
    QString m_Text;
};

#endif // CQML_СBUTTONS_DIALOG_H
