import QtQuick 2.0

import "qml.qrc:/BaseBox.qml"

Item {
    property string text: "text"

    signal boxTextChanged (string text)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("click")
            baseBox.setCursor(mouseX, mouseY)
        }

    BaseBox {
        id: baseBox
        anchors.fill: parent
        textBox: text
        isRO: false
        isEmitedSignal: true
        horAlig: Text.AlignLeft
        verAlig: Text.AlignTop

        onBaseTextChanged: {
            boxTextChanged (baseText)
        }
    }
    }
}
