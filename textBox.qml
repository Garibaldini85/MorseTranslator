import QtQuick 2.0

import "qml.qrc:/BaseBox.qml"

Item {
    property string text          : ""
    property string holderBaseText: ""
    property bool   readonly      : false
    property bool   emitting      : true

    signal boxTextChanged (int code, int position, string text)

    function clearOldString() {
        baseBox.oldString = ""
        baseBox.baseTextChanged(1, 0, text)
    }

    BaseBox {
        id: baseBox
        anchors.fill: parent
        textBox: text
        isRO: readonly
        isEmitedSignal: emitting
        horAlig: Text.AlignLeft
        verAlig: Text.AlignTop
        isSelecting: true
        holderText: holderBaseText
        onBaseTextChanged: {
            boxTextChanged (code, basePosition, baseText)
        }
    }
}
