#ifndef QSTRINGCHANGER_H
#define QSTRINGCHANGER_H

#include <QObject>
#include <QLinkedList>
#include <QRegExp>

class QStringChanger : public QObject
{
    Q_OBJECT
public:
    explicit QStringChanger(QObject *parent = nullptr);

private:
    QList<QChar> lat  = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', ' ', '.', '-'};
    QStringList morze = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.",
                        "--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","-...-", "......", "-....-"};
    QLinkedList <QString> oldMorze;
    QLinkedList <QChar>   oldMorzeChar, oldText;

    QString textToMorze();
    QString morzeToText();
    QString extraSymbol(const QString & str);
    QString extraMorze (const QChar & chr);
    void    createNewTask(const int & sizeNew, const int & sizeOld);
    void check(QString text);

public slots:
    void latOneChanging(const QString &text, const int &position);
    void latSevChanging(const QString &text, const int &position);
    void morOneChanging(const QString &morze,const int &position);
    void morSevChanging(const QString &morze,const int &position);
    void clearStrList();

signals:
    void retStr(QString str);
    void createTask(int from, int to);
    void changeTask(int value);

};

#endif // QSTRINGCHANGER_H
