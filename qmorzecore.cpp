#include "qmorzecore.h"

#include <QtDebug>

QMorzeCore::QMorzeCore(QObject *parent) : QObject(parent)
{
    changer = new QStringChanger();
    connect(changer, &QStringChanger::retStr,
            this,    &QMorzeCore::recStr);
    connect(changer, &QStringChanger::createTask,
            this,    &QMorzeCore::recNewTask);
    connect(changer, &QStringChanger::changeTask,
            this,    &QMorzeCore::recChangesTask);
}

void QMorzeCore::changeString(QString lang, int code, int position, QString text)
{
    qDebug() << "Core >>" << code << " " << position << " " << text;

    if (position == 0) {
        //QtConcurrent::run(changer, &QStringChanger::clearStrList);
        changer->clearStrList();
        position = text.size();
    }

    if (lang == "lat") {
        if (code == 0)
            QtConcurrent::run(changer, &QStringChanger::latOneChanging, text, position);
        else
            QtConcurrent::run(changer, &QStringChanger::latSevChanging, text, position);
    } else {
        if (code == 0)
            QtConcurrent::run(changer, &QStringChanger::morOneChanging, text, position);
        else
            QtConcurrent::run(changer, &QStringChanger::morSevChanging, text, position);
    }
}

void QMorzeCore::recStr(QString str)
{ emit sendStrToQml(str); }

void QMorzeCore::recNewTask(int from, int to)
{ emit sendDataToProgressBar(from, to); }

void QMorzeCore::recChangesTask(int value)
{ emit sendValueToProgressBar(value); }
