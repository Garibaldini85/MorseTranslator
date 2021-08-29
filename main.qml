import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "qml.qrc:/TextBox.qml"
import "qml.qrc:/LangBox.qml"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property var activeItem  : firTextBox
    property var inactiveItem: secTextBox

    Connections {
        target: MCore
        onSendStrToQml: {
            console.log(str)
            inactiveItem.text = str
        }
    }

    Button {
        x: parent.width * 0.4 + 2
        y: 2
        width: parent.width * 0.2 - 4
        height: parent.height * 0.1
        text: "change"

        onClicked: {
            let str = firLangBox.lang
            firLangBox.lang = secLangBox.lang
            secLangBox.lang = str

            str = firTextBox.text
            firTextBox.text = secTextBox.text
            secTextBox.text = str
        }
    }

    LangBox {
        id: firLangBox
        x: 2
        y: 2
        width: parent.width * 0.4 - 2
        height: parent.height * 0.1
        lang: "lat"
    }
    LangBox {
        id: secLangBox
        x: parent.width * 0.6
        y: 2
        width: parent.width * 0.4 - 2
        height: parent.height * 0.1
        lang: "mor"
    }

    TextBox {
        id: firTextBox
        x: 2
        y: parent.height * 0.1 + 4
        width: parent.width * 0.5 - 2
        height: parent.height * 0.9 - 4
        readonly: false

        onBoxTextChanged: {
            console.log(69, firLangBox.lang, code, position, text.length, text)
            MCore.changeString(firLangBox.lang, code, position, text)
        }
    }

    TextBox {
        id: secTextBox
        x: parent.width * 0.5
        y: parent.height * 0.1 + 4
        width: parent.width * 0.5 - 2
        height: parent.height * 0.9 - 4
        readonly: true

        onBoxTextChanged: {
            console.log(secLangBox.lang, code, text)
            MCore.changeString(secLangBox.lang, code, text.length, text)
        }
    }
}
