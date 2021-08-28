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
        if (iter.size() > 1 || iter == "[.-]") {
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

void QStringChanger::latOneChanging(const QString &text)
{
    for ( int i = 0; i < oldText; i++ ) {
        if (text.size() <= i) {
            oldMorze.erase(oldMorze.begin() + i);
            oldText = text;
            break;
        } else if( oldText[i].toUpper() != text[i].toUpper() ) {
            if ( oldText.size() < text.size() )
                oldMorze.insert(oldMorze.begin() + i, extraMorze(text[i]));
            else
                oldMorze.erase(oldMorze.begin() + i);
            oldText = text;
            break;
        }
    }
    if ( oldText.size() != text.size() ) {
        if ( oldText.size() < text.size() )
            oldMorze.insert( oldMorze.end(), extraMorze ( text [ text.size() - 1 ] ) );
        else
            oldMorze.erase( oldMorze.end() );
        oldText = text;
    }

    emit retStr(textToMorze());
}
//aaa
void QStringChanger::latSevChanging(const QString &text)
{
    if (text.size() == 0) {
        oldMorze.clear();
        oldText.clear();
    }
    for ( int i = 0; i < text.size(); i++) {
        if (oldText.size() <= i) {
            oldMorze.append( extraMorze ( text [i] ) );
            oldText.append(text[i]);
        } else if ( oldText[i].toUpper() != text[i].toUpper() ) {
            if (oldText.size() < text.size()) {
                oldMorze.insert(oldMorze.begin() + i, extraMorze(text[i]));
                oldText.insert(i, text[i]);
            } else {
                oldMorze.erase(oldMorze.begin() + i);
                oldText.remove(i, 1);
            }
        }
    }
    emit retStr(textToMorze());
}
