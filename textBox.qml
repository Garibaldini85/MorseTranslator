import QtQuick 2.0

import "qml.qrc:/BaseBox.qml"

Item {
    property string text    : ""
    property bool   readonly: false

    signal boxTextChanged (int code, int position, string text)

    BaseBox {
        id: baseBox
        anchors.fill: parent
        textBox: text
        isRO: readonly
        isEmitedSignal: true
        horAlig: Text.AlignLeft
        verAlig: Text.AlignTop
        isSelecting: true
        onBaseTextChanged: {
            boxTextChanged (code, basePosition, baseText)
        }
    }
}
