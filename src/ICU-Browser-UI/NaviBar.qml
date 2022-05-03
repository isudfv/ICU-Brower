import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

//import Qt5Compat.GraphicalEffects
Item {
    id: navibar

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
                        id: backButton
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
                            source: header.activeBack ? "qrc:/icons/black-arrow-back.svg" : "qrc:/icons/gray-arrow-back.svg"
                        }

                        MouseArea {
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: header.activeBack
                            enabled: header.activeBack
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "返回"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: forwardButton
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
                            source: header.activeForward ? "qrc:/icons/black-arrow-forward.svg" : "qrc:/icons/gray-arrow-forward.svg"
                        }
                        MouseArea {
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: header.activeForward
                            enabled: header.activeForward
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "继续"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: flashButton
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
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "刷新"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: homeButton
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
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "主页"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }
                    }
                }
                TextField {
                    id: tf
                    implicitHeight: 34
                    implicitWidth: rootWindow.width - 345
                    verticalAlignment: TextInput.AlignVCenter
                    clip: true
                    selectByMouse: true
                    selectedTextColor: "white"
                    selectionColor: "#0078d4"
                    onPressed: {
                        rootWindow.requestActivate()
                    }

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
                        implicitHeight: parent.height
                        implicitWidth: parent.width
                        border.width: 1
                        border.color: "#f7f7f7"
                        radius: 3
                        //border.color: "red"
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                parent.border.color = "#cecece"
                            }
                            onExited: parent.border.color = "white"
                        }
                    }
                }

                RowLayout {
                    spacing: 2
                    Rectangle {
                        id: starButton
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
                            source: "qrc:/icons/star.svg"
                        }
                        MouseArea {
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "收藏夹"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: historyButton
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
                            source: "qrc:/icons/history.svg"
                        }
                        MouseArea {
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "历史记录"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }
                    }

                    Rectangle {
                        id: userButton
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
                            source: "qrc:/icons/user.svg"
                        }
                        MouseArea {
                            property bool enter: false
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                parent.color = "#dcdcdc"
                                enter = true
                            }
                            onExited: {
                                parent.color = "#f7f7f7"
                                enter = false
                            }

                            onClicked: {
                                root.addaaa()
                                console.debug(root.width, root.height)
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "用户信息"
                                delay: 500
                                background: Rectangle {
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
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/

