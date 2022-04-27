import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    property QtObject rootWindow
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TitleBar {
            height: 37
            Layout.fillWidth: parent
//            Layout.fillHeight: parent
//            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
//            Layout.fillWidth: parent
        }
        Rectangle {
            color:"#f7f7f7"
            height: 111 - 37
            Layout.fillWidth: parent
            Layout.fillHeight: parent
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.33;height:480;width:640}
}
##^##*/
