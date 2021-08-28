import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    property string textBox        : "mda"
    property string colorBox       : "#94ebd8"
    property string colorBorder    : "#00787a"
    property string colorText      : "#003d34"
    property bool   isEmitedSignal : false
    property bool   isRO           : true
    property int    horAlig        : Text.AlignHCenter
    property int    verAlig        : Text.AlignVCenter
    property string oldString      : ""
    property var    itemKeyNav     : textArea

    /* code 0, 1, 2
     * 0 changing one symbol
     * 1 past
     * 2 cut
     */
    signal baseTextChanged(int code, string baseText)

    Rectangle {
        anchors.fill: parent
        color: colorBox
        border.color: "#00787a"
        border.width: 5
        radius: 30



        ScrollView
        {
            clip: true
            x: parent.radius / 3.14
            y: parent.radius / 3.14
            width: parent.width - parent.radius / 3.14 * 2
            height: parent.height - parent.radius / 3.14 * 2

            FocusScope {
                anchors.fill: parent

                TextArea {
                    id: textArea
                    anchors.fill: parent
                    horizontalAlignment: horAlig
                    verticalAlignment: verAlig
                    color: "#003d34"
                    text: textBox
                    readOnly: isRO
                    wrapMode: TextEdit.Wrap
                    onTextChanged: {
                        if (isEmitedSignal) {
                            if (Math.abs(text - oldString) > 1)
                                baseTextChanged(1, text)
                            else
                                baseTextChanged(0, text)
                            oldString = text

                        }
                    }

//                    Keys.onPressed: {
//                        if (event.key === Qt.Key_V
//                        && event.modifiers === Qt.ControlModifier) {
//                            baseTextChanged(1, text)
//                            oldString = text
//                        } else if (event.key === Qt.Key_X
//                        && event.modifiers === Qt.ControlModifier) {
//                            baseTextChanged(2, text)
//                            oldString = text
//                        } else if (event.modifiers === Qt.NoModifier
//                        && oldString.length !== text.length) {
//                            baseTextChanged(0, text)
//                            oldString = text
//                        }
//                    }

                    KeyNavigation.priority: KeyNavigation.BeforeItem
                    KeyNavigation.tab: itemKeyNav
                }
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/