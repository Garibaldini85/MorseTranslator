import QtQuick 2.0

import "qml.qrc:/BaseBox.qml"

Item {
    property string lang: "lang"

    BaseBox {
        anchors.fill: parent
        textBox: lang
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
