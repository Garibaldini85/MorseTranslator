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

    signal baseTextChanged(string baseText)

    function setCursor(mouseX, mouseY) {
        textArea.cursorPosition = textArea.positionAt(mouseX, mouseY)
    }



    Rectangle {
        //width: widthBox
        //height: heightBox
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


            TextArea {
                id: textArea
                anchors.fill: parent
                horizontalAlignment: horAlig
                verticalAlignment: verAlig
                //color: "#003d34"
                text: textBox
                readOnly: isRO
                wrapMode: TextEdit.Wrap
                //hoverEnabled: true
                onTextChanged: {
                    if (isEmitedSignal) {
                        baseTextChanged(text)
                        console.log(text)
                    }
                }
                onPressed: {
                    console.log("press")

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
