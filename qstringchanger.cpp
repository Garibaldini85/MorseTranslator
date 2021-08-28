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
        retStr += iter + " ";
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
        if( oldText[i].toUpper() != text[i].toUpper() ) {
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

void QStringChanger::latSevChanging(const QString &text)
{
    emit retStr(textToMorze());
}
