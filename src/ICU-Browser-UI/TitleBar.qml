import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {

//    property QtObject rootWindow
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Rectangle {
            Layout.fillWidth: parent
            height: 5
            color: "transparent"
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    rootWindow.requestActivate()
//                }
//            }
        }
        RowLayout {
            id: root
            signal addaaa

            Tabs {
                id: tabBar
            }

            Rectangle {
                height: 20
//                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.alignment: Qt.AlignLeft
                width: 20
                color: "#cdcdcd"
                radius: 3
                Image {
                    //                Layout.alignment: Qt.AlignCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    height: 20
                    width: 20
                    id: plusTab
                    source: "qrc:/icons/add.svg"
                }
                MouseArea {
                    id: mouseRegion
                    property bool enter: false
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        enter = true
                        parent.color = "#adadad"
                    }
                    onExited: {
                        enter = false
                        parent.color = "#cdcdcd"
                    }

                    onClicked: {
                        windowManager.addWindow(header.defaultUrl)
//                        root.addaaa()
                    }
                    ToolTip{
                        visible: parent.enter
                        text: "新建标签页"
                        delay: 500
                        background: Rectangle{
                            color: "#f7f7f7"
                            border.color: "black"
                            border.width: 1
                            radius: 5
                        }
                    }
                }
            }
        }
    }
}

