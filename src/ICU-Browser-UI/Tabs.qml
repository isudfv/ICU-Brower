import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Row {
    Layout.leftMargin: 5
    //    anchors.left: parent.left + 10
    //    anchors.bottomMargin: 0
    TabBar {
        //        x: 2
        id: tabBar
        //        anchors.bottom: parent.bottom
        //        anchors.bottomMargin: 0
        spacing: 0

        background: Rectangle {
            color: "#cdcdcd"
        }
    }

    Component {
        id: tabButton
        TabButton {
            id: button
            implicitWidth: 300
            implicitHeight: 32
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    button.focus = true
//                }
//            }
            onClicked: {
                console.log(tabBar.currentIndex)
            }

            contentItem: Item {
                anchors.fill: parent
                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    Image {
                        Layout.leftMargin: 10
                        source: "qrc:/icons/stackoverflow.png"
                        width: 16
                        height: 16
                    }
                    Text {
                        text: "fuck"
                        fontSizeMode: Text.Fit
                        width: 228
                        height: 16
                        Layout.fillWidth: true
                        clip: true
                        elide: Text.ElideRight
                    }
                    Rectangle {
                        Layout.rightMargin: 10
                        width: 16
                        height: 16
                        color: "transparent"
                        radius: 2
                        Image {
                            source: "qrc:/icons/close.png"
                            width: 16
                            height: 16
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                removeAt(button)
                            }
                            hoverEnabled: true
                            onEntered: parent.color = "#adadad"
                            onExited: parent.color = "transparent"
                        }
                    }
                }
            }
            background: Rectangle {
//                id: bg
                anchors.fill: parent
                color: button.focus ? "#f7f7f7" : "transparent"
                focus: true
                radius: 6
                Rectangle {
                    color: parent.color
                    implicitWidth: parent.parent.implicitWidth
                    //                        width: 300
                    //                        Layout.fillWidth: parent
                    height: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                }
                // right radius
                Rectangle {
                    color: button.focus ? "#f7f7f7" : "transparent"
                    implicitWidth: 6
                    implicitHeight: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0

                    anchors.left: parent.right
                    anchors.leftMargin: 0
                }
                Rectangle {
                    width: 12
                    height: 12
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.right
                    color: button.focus ? "#cdcdcd" : "transparent"
                    radius: 6
                }
                // left radius
                Rectangle {
                    color: button.focus ? "#f7f7f7" : "transparent"
                    implicitWidth: 6
                    implicitHeight: 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0

                    anchors.right: parent.left
                    anchors.leftMargin: 0
                }
                Rectangle {
                    width: 12
                    height: 12
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.left
                    color: button.focus ? "#cdcdcd" : "transparent"
                    //                    color: "#cdcdcd"
                    radius: 6
                }
            }
        }
    }

    Component.onCompleted: {
        parent.addaaa.connect(addItem)
        addItem()
        addItem()
        tabBar.takeItem(tabBar.count - 1)
        tabBar.itemAt(tabBar.count - 1).focus = true
        // todo: 玄学问题：只有一个tab时虽然有focus但无法正确显示颜色。
    }


    function addItem() {
        tabBar.addItem(tabButton.createObject(tabBar))
        tabBar.setCurrentIndex(tabBar.count - 1)
        adjustItem()
    }

    function removeAt(item) {
        tabBar.removeItem(item)
        if (tabBar.count === 0){
            Qt.quit()
        }

        adjustItem()
    }

    function adjustItem() {
        // the algorithm is undecided
        var equal_width = Window.width / tabBar.count - 50 / tabBar.count
        if (equal_width < 300) {
            for (var i = 0; i < tabBar.count; ++i) {
                tabBar.itemAt(i).implicitWidth = equal_width
            }
        }
    }

    Window.onWidthChanged:
        adjustItem()

}
