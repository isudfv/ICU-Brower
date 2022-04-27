import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

ColumnLayout {
//    anchors.fill: parent

    //    Tabs{

    //    }
    spacing: 0
    Rectangle {
//        width: 300
        Layout.fillWidth: parent
        Layout.fillHeight: parent
        height: 5
        color: "transparent"
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop

    }

    RowLayout {
        id: root
        //        height: parent.height
//        anchors.fill: parent
        //        anchors.left: parent.left

        //        Layout.fillHeight: parent.height
        signal addaaa

        Tabs {
            id: tabBar
        }

        Rectangle {
            height: 32
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            width: 32
            color: "#cdcdcd"
            Image {
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                height: 32
                width: 32
                id: plusTab
                source: "qrc:/icons/plus.png"
            }
            MouseArea {
                id: mouseRegion
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.color = "#adadad"
                onExited: parent.color = "#cdcdcd"

                onClicked: {
                    root.addaaa()
                    console.debug(root.width, root.height)
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

