import QtQuick 2.0

import "qml.qrc:/BaseBox.qml"

Item {
    property string text    : ""
    property bool   readonly: false

    signal boxTextChanged (int code, string text)

    BaseBox {
        id: baseBox
        anchors.fill: parent
        textBox: text
        isRO: readonly
        isEmitedSignal: true
        horAlig: Text.AlignLeft
        verAlig: Text.AlignTop

        onBaseTextChanged: {
            boxTextChanged (code, baseText)
        }
    }
}
