#ifndef QMORZECORE_H
#define QMORZECORE_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>

#include "qstringchanger.h"

class QMorzeCore : public QObject
{
    Q_OBJECT
public:
    explicit QMorzeCore(QObject *parent = nullptr);

private:
    QStringChanger *changer;

public slots:
    void changeString(QString lang, int code, int position, QString text);
    void recStr(QString str);

signals:
    void sendStrToQml(QString str);

};

#endif // QMORZECORE_H
