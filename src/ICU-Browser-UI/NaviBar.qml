import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
//import Qt5Compat.GraphicalEffects

Item {
    height: 36
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Rectangle {
            color: "#f7f7f7"
            Layout.fillWidth: parent
            height: 2
        }

        Rectangle {
            id: rectangle
            color: "#f7f7f7"
            Layout.fillWidth: parent
            Layout.fillHeight: parent
            RowLayout {
                anchors.left: parent.left
                anchors.leftMargin: 5
                Layout.fillHeight: true
                spacing: 5

                RowLayout {
                    spacing: 2
                    Rectangle {
                        height: 34
                        Layout.alignment: Qt.AlignLeft
                        width: 45
                        color: "#f7f7f7"
                        radius: 3
                        Image {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            height: 20
                            width: 20
                            source: "qrc:/icons/arrow-back.svg"
                        }
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.color = "#dcdcdc"
                            onExited: parent.color = "#f7f7f7"

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }
                        }
                    }

                    Rectangle {
                        height: 34
                        Layout.alignment: Qt.AlignLeft
                        width: 45
                        color: "#f7f7f7"
                        radius: 3
                        Image {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            height: 20
                            width: 20
                            // id: plusTab
                            source: "qrc:/icons/arrow-forward.svg"
                        }
                        MouseArea {
                            //id: mouseRegion
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.color = "#dcdcdc"
                            onExited: parent.color = "#f7f7f7"

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }
                        }
                    }

                    Rectangle {
                        height: 34
                        Layout.alignment: Qt.AlignLeft
                        width: 45
                        color: "#f7f7f7"
                        radius: 3
                        Image {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            height: 20
                            width: 20
                            //id: plusTab
                            source: "qrc:/icons/refresh.svg"
                        }
                        MouseArea {
                            //id: mouseRegion
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.color = "#dcdcdc"
                            onExited: parent.color = "#f7f7f7"

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }
                        }
                    }

                    Rectangle {
                        height: 34
                        Layout.alignment: Qt.AlignLeft
                        width: 45
                        color: "#f7f7f7"
                        radius: 3
                        Image {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            height: 20
                            width: 20
                            //id: plusTab
                            source: "qrc:/icons/home_light.svg"
                        }
                        MouseArea {
                            //id: mouseRegion
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.color = "#dcdcdc"
                            onExited: parent.color = "#f7f7f7"

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }
                        }
                    }
                }

//                Rectangle {
//                    id: rec
//                    width: 100
//                    height: 28
//                    color: "red"

//                }

//                DropShadow {
//                        anchors.fill: rec
//                        cached: true
//                        horizontalOffset: 3
//                        verticalOffset: 3
//                        radius: 8.0
////                        samples: 16
//                        color: "#80000000"
//                        source: rec
//                    }

                TextField {
                    implicitHeight: 34
                    implicitWidth: 900
                    verticalAlignment: TextInput.AlignVCenter
                    clip: true

                    font {
                        pixelSize: 14
                    }

                    text: "https://bilibili.com"
//                    placeholderText.

                    background: Rectangle {
                        anchors.fill: parent
                        //                        anchors.horizontalCenter: parent.horizontalCenter
                        //                        anchors.verticalCenter: rectangle.verticalCenter
                        color: "white"
                        implicitHeight: 32
                        implicitWidth: 900
                        border.width: 1
                        border.color: "#f7f7f7"
                        radius: 3
//border.color: "red"
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.border.color = "#cecece"
                            onExited: parent.border.color = "white"
                        }
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/

