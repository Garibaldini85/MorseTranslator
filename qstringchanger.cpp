#include "qstringchanger.h"

#include <QtDebug>

QStringChanger::QStringChanger(QObject *parent) : QObject(parent) { }

QString QStringChanger::textToMorze()
{
    QString retStr;
// как тебе
    for (auto iter: oldMorze) {
        if (retStr.isEmpty()) {
            retStr += iter;
        } else if (iter.size() > 1 || iter == "-" || iter == ".") {
            if (retStr [ retStr.size() - 1] != ' ') {
                retStr += ' ';
                qDebug() << "retStr >>" << retStr;
            }
            retStr += iter + ' ';
            qDebug() << "retStr >>" << retStr;
        } else {
            retStr += iter;
            qDebug() << "retStr >>" << retStr;
        }
    }

    return retStr;
}

QString QStringChanger::morzeToText()
{
    QString retStr, addMorze;

//    for (auto iter = oldMorzeChar.begin(); iter != oldMorzeChar.end(); iter++) {
//        if (lat.indexOf( (*iter).toUpper() ) == -1) {
//            addMorze += *iter;
//        } else {
//            int ind = morze.indexOf(addMorze);
//            if (ind != -1)
//                retStr += lat[ind];
//            else
//                retStr += addMorze;
//            addMorze.clear();
//        }

//    }

    for (auto iter: oldMorzeChar) {
        if (iter == ' ') {
            int ind = morze.indexOf(addMorze);
            if (ind != -1) {

                    retStr += lat[ind];
                    addMorze.clear();
                    qDebug() << "retStr >>" << retStr;

            } else {
                retStr += addMorze;
                addMorze.clear();
                qDebug() << "retStr >>" << retStr;

            }
        } else {
            addMorze += iter;
            qDebug() << "retStr >>" << retStr;
        }
    }

    QChar c = *(oldMorzeChar.begin() + oldMorzeChar.size() - 1);
    if (*(oldMorzeChar.begin() + oldMorzeChar.size() - 1) != ' ') {
        int ind = morze.indexOf(addMorze);
        if (ind != -1)
            retStr += lat[ind];
        else
            retStr += addMorze;
    }

    qDebug() << "retStr >>" << retStr;
    return retStr;
}

QString QStringChanger::extraSymbol(const QString & str)
{
    int ind = morze.indexOf(str);
    if ( ind != -1 )
        return lat[ind];
    else
        return str;
}

QString QStringChanger::extraMorze(const QChar & chr)
{
    int ind = lat.indexOf(chr.toUpper());
    if ( ind != -1 )
        return morze[ind];
    else
        return chr;
}

void QStringChanger::createNewTask(const int &sizeNew, const int &sizeOld)
{
    if (sizeNew > sizeOld)
        emit createTask(0, sizeNew - sizeOld);
    else
        emit createTask(0, sizeOld - sizeNew);
}

void QStringChanger::check(QString text)
{
    QString str;
    for(auto iter: oldMorzeChar) {
        str += iter;
    }
    bool bliat = (str == text);
}

void QStringChanger::latOneChanging(const QString &text, const int &position)
{
    if (oldText.size() < text.size()) {
        oldMorze.insert(oldMorze.begin() + position - 1, extraMorze(text[position - 1]));
        oldText.insert(oldText.begin() + position - 1, text[position - 1]);
    } else {
        oldMorze.erase(oldMorze.begin() + position);
        oldText.erase(oldText.begin() + position);
    }

    emit retStr(textToMorze());
}

void QStringChanger::latSevChanging(const QString &text, const int &position)
{
    QString _text = text;
    createNewTask(text.size(), oldText.size());

    if (oldText.size() < text.size()) {
        int _position = position - (text.size() - oldText.size());
        while (oldMorze.size() < text.size()) {
            oldMorze.insert(oldMorze.begin() + _position, extraMorze(_text[_position]));
            oldText.insert(oldText.begin() + _position, _text[_position]);
            _position += 1;

            //qDebug() << _position << " " << _text.size() << " " << oldMorze.size();

            emit changeTask(abs(oldText.size() - _text.size()));
        }
    } else if (oldText.size() > _text.size()){
        while (oldText.size() > _text.size()) {
            oldMorze.erase(oldMorze.begin() + position);
            oldText.erase(oldText.begin() + position);
            //qDebug() << position << " " << _text.size() << " ", oldMorze.size();

            emit changeTask(abs(oldText.size() - _text.size()));
        }
    }
    emit retStr(textToMorze());
}

void QStringChanger::morOneChanging(const QString &morze, const int &position)
{
    if (oldMorzeChar.size() < morze.size()) {
        oldMorzeChar.insert(oldMorzeChar.begin() + position - 1, morze[position - 1]);
    } else {
        oldMorzeChar.erase(oldMorzeChar.begin() + position);
    }

    emit retStr(morzeToText());
}

void QStringChanger::morSevChanging(const QString &morze, const int &position)
{
    createNewTask(morze.size(), oldMorzeChar.size());

    if (oldMorzeChar.size() < morze.size()) {
        int _position = position - (morze.size() - oldMorzeChar.size());
        while (_position < morze.size()) {
            oldMorzeChar.insert(oldMorzeChar.begin() + _position, morze[_position]);
            _position += 1;

            emit changeTask(abs(oldMorzeChar.size() - morze.size()));
        }
    } else if (oldMorzeChar.size() > morze.size()){
        while (oldMorzeChar.size() > morze.size()) {
            oldMorzeChar.erase(oldMorzeChar.begin() + position);
            emit changeTask(abs(oldMorzeChar.size() - morze.size()));
        }
    }
    check(morze);
    emit retStr(morzeToText());
}

void QStringChanger::clearStrList()
{
    //oldMorze = QLinkedList<QString>();
    //oldMorzeChar = QLinkedList<QChar>();
    //oldMorzeChar.erase(oldMorzeChar.begin(), oldMorzeChar.end());
    while (!oldMorze.isEmpty())
        oldMorze.clear();
    while (!oldMorzeChar.isEmpty())
        oldMorzeChar.clear();
    while (!oldText.isEmpty())
        oldText.clear();
    //oldText = QLinkedList<QChar>();
}
