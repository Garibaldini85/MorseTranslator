#ifndef QSTRINGCHANGER_H
#define QSTRINGCHANGER_H

#include <QObject>
#include <QLinkedList>

class QStringChanger : public QObject
{
    Q_OBJECT
public:
    explicit QStringChanger(QObject *parent = nullptr);

private:
    QList<QChar> lat  = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', ' '};
    QStringList morze = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.",
                        "--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","-···-"};
    QString oldText;
    QLinkedList <QString> oldMorze;

    QString textToMorze();
    QString morzeToText();
    QString extraSymbol(const QString & str);
    QString extraMorze (const QChar & chr);

public slots:
    void latOneChanging(const QString &text, const int &position);
    void latSevChanging(const QString &text, const int &position);

signals:
    void retStr(QString str);

};

#endif // QSTRINGCHANGER_H
