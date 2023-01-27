#ifndef CQML_СLOCALIZATION_MANAGER_H
#define CQML_СLOCALIZATION_MANAGER_H

// Qt headers
#include <QtCore/QObject>
#include <QtCore/QTranslator>

class CLocalizationManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE( CLocalizationManager )
public:
    explicit CLocalizationManager( QObject* parent = nullptr );

    void changeTranslator( const QString& translatorFile, const QString& path );

Q_SIGNALS:
    void onTranslatorChanged();

private:
    QTranslator m_Translator;
    QTranslator m_DefaultTranslator;
};

#endif // CQML_СLOCALIZATION_MANAGER_H
