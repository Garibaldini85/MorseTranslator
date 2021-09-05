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

    //property var activeItem  : firTextBox
    //property var inactiveItem: secTextBox

    Connections {
        target: MCore
        onSendStrToQml: {
            //console.log(str)
            secTextBox.text = str
            progBar.visible = false
            butChange.visible = true
            firTextBox.readonly = false
            firTextBox.emitting = true
        }

        onSendDataToProgressBar: {
            //console.log(from, to)
            progBar.value = 0
            progBar.from = from
            progBar.to = to
        }

        onSendValueToProgressBar: {
            //console.log(progBar.to - value)
            progBar.value = progBar.to - value }
    }

    Button {
        id: butChange
        x: parent.width * 0.4 + 2
        y: 2
        width: parent.width * 0.2 - 4
        height: parent.height * 0.1
        text: "change"

        onClicked: {
            firTextBox.emitting = false

            let str = firLangBox.lang
            firLangBox.lang = secLangBox.lang
            secLangBox.lang = str

            //str = firTextBox.text
            //firTextBox.text = secTextBox.text
            //secTextBox.text = str
            firTextBox.text = secTextBox.text
            secTextBox.text = ""

            firTextBox.clearOldString()
        }
    }

    ProgressBar {
        id: progBar
        x: parent.width * 0.4 + 2
        y: 2
        width: parent.width * 0.2 - 4
        height: parent.height * 0.1
        visible: false
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
        emitting: true
        holderBaseText: "Вводить текст сюда"

        onBoxTextChanged: {
            progBar.visible = true
            butChange.visible = false
            firTextBox.readonly = true
            console.log(progBar.visible, butChange.visible, firTextBox.readonly)
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
        emitting: false
        holderBaseText: "Выводить текст здесь"

        onBoxTextChanged: {
            //console.log(secLangBox.lang, code, text)
            //MCore.changeString(secLangBox.lang, code, text.length, text)
        }
    }
}
