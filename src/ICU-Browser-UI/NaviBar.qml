import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import Managers

//import Qt5Compat.GraphicalEffects
Item {
    id: navibar
    property alias url: textfield.text
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
                                parent.color = "#f7f7f7"
                                enter = false
                                WindowManager.doGoBack(header.currentWindowIndex)
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
                                parent.color = "#f7f7f7"
                                enter = false
                                WindowManager.doGoForward(header.currentWindowIndex)
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
                                WindowManager.doReLoad(header.currentWindowIndex)
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
                                WindowManager.doLoadUrl(header.currentWindowIndex,header.defaultUrl,header.currentUserId)
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
                    id: textfield
                    implicitHeight: 34
                    implicitWidth: rootWindow.width - 390
                    verticalAlignment: TextInput.AlignVCenter
                    clip: true
                    selectByMouse: true
                    selectedTextColor: "white"
                    selectionColor: "#0078d4"
                    onPressed: {
                        rootWindow.requestActivate()
                    }
                    onAccepted: {
                        WindowManager.doLoadUrl(header.currentWindowIndex,text,header.currentUserId)
                    }

                    font {
                        pixelSize: 14
                    }

                    text: header.currentUrl
                    background: Rectangle {
                        anchors.fill: parent
                        color: "white"
                        implicitHeight: parent.height
                        implicitWidth: parent.width
                        border.width: 1
                        border.color: "#f7f7f7"
                        radius: 3
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
                                favoritemenu.visible = true
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

                        FavoriteMenu {
                            y: rootWindow.y + navibar.y + 39
                            x: rootWindow.x + starButton.parent.x - 200
                            width: 250
                            height: 400
                            id: favoritemenu
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
                                historyMenu.visible = true
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

                        HistoryMenu {
                            y: rootWindow.y + navibar.y + 39
                            x: rootWindow.x + starButton.parent.x - 300
                            width: 400
                            height: 400
                            id: historyMenu
                        }
                    }

                    Rectangle {
                        id: downloadButton
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
                            source: "qrc:/icons/download.svg"
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
                                downloadwindow.visible = true
                            }

                            ToolTip {
                                visible: parent.enter
                                text: "下载记录"
                                delay: 500
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                        }

                        DownloadWindow {
                            y: rootWindow.y + navibar.y + 39
                            x: rootWindow.x + downloadButton.parent.x - 105
                            width: 250
                            height: 400
                            id: downloadwindow
                        }
                    }

                    Rectangle {
                        property bool isLoginWindow: false
                        property bool isRegisterWindow: false
                        property bool isUserWindow: false

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
                                if (currentUserId !== 0) {
                                    userButton.isUserWindow = true
                                }
                                else {
                                    userButton.isLoginWindow = true
                                }
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

                            LoginWindow {
                                id: loginWindow
                                visible: userButton.isLoginWindow
                                y: rootWindow.y + 37 * 2 + 2
                                x: rootWindow.x + rootWindow.width - loginWindow.width - 2
                            }
                            RegisterWindow {
                                id: registerWindow
                                visible: userButton.isRegisterWindow
                                y: rootWindow.y + 37 * 2 + 2
                                x: rootWindow.x + rootWindow.width - registerWindow.width - 2
                            }
                            UserWindow {
                                id: userWindow
                                visible: userButton.isUserWindow
                                y: rootWindow.y + 37 * 2 + 2
                                x: rootWindow.x + rootWindow.width - userWindow.width - 2
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

