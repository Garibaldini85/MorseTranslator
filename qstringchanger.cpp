#include "qstringchanger.h"

QStringChanger::QStringChanger(QObject *parent) : QObject(parent)
{
    oldText  = QString();
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
    return oldText;
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
        oldText.insert(position - 1, text[position - 1]);
    } else {
        oldMorze.erase(oldMorze.begin() + position);
        oldText.remove(position, 1);
    }

    emit retStr(textToMorze());
}
//aaa
void QStringChanger::latSevChanging(const QString &text, const int &position)
{
    if (oldText.size() < text.size()) {
        int _position = position - (text.size() - oldText.size());
        while (oldText.size() < text.size()) {
            oldMorze.insert(oldMorze.begin() + _position, extraMorze(text[_position]));
            oldText.insert(_position, text[_position]);
            _position += 1;
        }
    } else {
        int _position = position + (oldText.size() - text.size());
        while (oldText.size() > text.size()) {
            oldMorze.erase(oldMorze.begin() + _position);
            oldText.remove(_position, 1);
            _position += 1;
        }
    }


//    if (text.size() == 0) {
//        oldMorze.clear();
//        oldText.clear();
//    }
//    for ( int i = 0; i < text.size(); i++) {
//        if (oldText.size() <= i) {
//            oldMorze.append( extraMorze ( text [i] ) );
//            oldText.append(text[i]);
//        } else if ( oldText[i].toUpper() != text[i].toUpper() ) {
//            if (oldText.size() < text.size()) {
//                oldMorze.insert(oldMorze.begin() + i, extraMorze(text[i]));
//                oldText.insert(i, text[i]);
//            } else {
//                oldMorze.erase(oldMorze.begin() + i);
//                oldText.remove(i, 1);
//            }
//        }
//    }
    emit retStr(textToMorze());
}
