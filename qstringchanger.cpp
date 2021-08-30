#include "qstringchanger.h"

QStringChanger::QStringChanger(QObject *parent) : QObject(parent)
{
    oldText  = QLinkedList <QChar>();
    oldMorze = QLinkedList <QString>();
}

QString QStringChanger::textToMorze()
{
    QString retStr;

    for (auto iter: oldMorze) {
        if (retStr.isEmpty()) {
            retStr += iter;
        } else if (iter.size() > 1 || iter == "[.-]") {
            if (retStr [ retStr.size() - 1] != ' ')
                retStr += ' ';
            retStr += iter + ' ';
        } else {
            retStr += iter;
        }
    }

    return retStr;
}

QString QStringChanger::morzeToText()
{
    QString retStr, addMorze;

    for (auto iter: oldMorzeChar) {
        if (iter == ' ') {
            int ind = morze.indexOf(addMorze);
            if (ind != -1)
                if (ind != lat.size() - 1)
                    retStr += lat[ind];
                else
                    retStr.resize(retStr.size() - 1);
            else
                retStr += addMorze;
            addMorze.clear();
            retStr += ' ';
        } else {
            addMorze += iter;
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
    if (oldText.size() < text.size()) {
        int _position = position - (text.size() - oldText.size());
        while (oldText.size() < text.size()) {
            oldMorze.insert(oldMorze.begin() + _position, extraMorze(text[_position]));
            oldText.insert(oldText.begin() + _position, text[_position]);
            _position += 1;
        }
    } else {
        while (oldText.size() > text.size()) {
            oldMorze.erase(oldMorze.begin() + position);
            oldText.erase(oldText.begin() + position);
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
    if (oldMorzeChar.size() < morze.size()) {
        int _position = position - (morze.size() - oldMorzeChar.size());
        while (oldMorzeChar.size() < morze.size()) {
            oldMorzeChar.insert(oldMorzeChar.begin() + _position, morze[_position]);
            _position += 1;
        }
    } else {
        while (oldMorzeChar.size() > morze.size()) {
            oldMorzeChar.erase(oldMorzeChar.begin() + position);
        }
    }
    emit retStr(morzeToText());
}

void QStringChanger::clearStrList()
{
    oldMorze.clear();
    oldMorzeChar.clear();
    oldText.clear();
}
