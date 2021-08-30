import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    property string textBox        : "mda"
    property string colorBox       : "#94ebd8"
    property string colorBorder    : "#00787a"
    property string colorText      : "#003d34"
    property bool   isEmitedSignal : false
    property bool   isRO           : true
    property bool   isSelecting    : false
    property int    horAlig        : Text.AlignHCenter
    property int    verAlig        : Text.AlignVCenter
    property string oldString      : ""
    property var    itemKeyNav     : textArea

    /* code 0, 1, 2
     * 0 changing one symbol
     * 1 past/cut
     */
    signal baseTextChanged(int code, int basePosition, string baseText)

    Rectangle {
        anchors.fill: parent
        color: colorBox
        border.color: "#00787a"
        border.width: 5
        radius: 30



        FocusScope
        {
            clip: true
            x: parent.radius / 3.14
            y: parent.radius / 3.14
            width: parent.width - parent.radius / 3.14 * 2
            height: parent.height - parent.radius / 3.14 * 2

             ScrollView {
                anchors.fill: parent

                TextArea {
                    id: textArea
                    anchors.fill: parent
                    horizontalAlignment: horAlig
                    verticalAlignment: verAlig
                    color: "#003d34"
                    text: textBox
                    readOnly: isRO
                    wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
                    selectByKeyboard: isSelecting
                    selectByMouse: isSelecting
                    onTextChanged: {
                        if (isEmitedSignal) {
                            //console.log(cursorPosition)
                            if (Math.abs(text.length - oldString.length) > 1)
                                baseTextChanged(1, cursorPosition, text)
                            else
                                baseTextChanged(0, cursorPosition, text)
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
//             MouseArea {
//                 anchors.fill: parent
//                 onClicked: { textArea.forceActiveFocus(); }
//             }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
