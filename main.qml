import QtQuick 2.12
import QtQuick.Window 2.12

import "qml.qrc:/TextBox.qml"
import "qml.qrc:/LangBox.qml"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property var activeItem  : latTextBox
    property var inactiveItem: morzeTextBox

    Connections {
        target: MCore
        onSendStrToQml: {
            console.log(str)
            inactiveItem.text = str
        }
    }

    LangBox {
        x: 2
        y: 2
        width: parent.width * 0.5 - 2
        height: parent.height * 0.1
        lang: "lat"
    }
    LangBox {
        x: parent.width * 0.5
        y: 2
        width: parent.width * 0.5 - 2
        height: parent.height * 0.1
        lang: "mor"
    }

    TextBox {
        id: latTextBox
        x: 2
        y: parent.height * 0.1 + 4
        width: parent.width * 0.5 - 2
        height: parent.height * 0.9 - 4
        readonly: false

        onBoxTextChanged: {
            console.log("lat", code, text.length, text)
            MCore.changeString("lat", code, text)
        }
    }

    TextBox {
        id: morzeTextBox
        x: parent.width * 0.5
        y: parent.height * 0.1 + 4
        width: parent.width * 0.5 - 2
        height: parent.height * 0.9 - 4
        readonly: true

        onBoxTextChanged: {
            console.log("mor", code, text)
            MCore.changeString("mor", code, text.length, text)
        }
    }
}
