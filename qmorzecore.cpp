#include "qmorzecore.h"

QMorzeCore::QMorzeCore(QObject *parent) : QObject(parent)
{
    changer = new QStringChanger();
    connect(changer, &QStringChanger::retStr,
            this,    &QMorzeCore::recStr);
}

void QMorzeCore::changeString(QString lang, int code, int position, QString text)
{
    if (position == 0) {
        QtConcurrent::run(changer, &QStringChanger::clearStrList);
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
{
    emit sendStrToQml(str);
}
