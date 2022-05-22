import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import Managers

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
        onCurrentItemChanged: {
            header.currentTabItem = currentItem
            header.currentWindowIndex = currentItem.windowId
            header.currentUrl = currentItem.windowUrl
            WindowManager.toggleTab(currentItem.windowId)
        }

        onCountChanged: {
            if(count === 0){
                Qt.quit()
            }

            adjustItem()
        }
    }

    Component {
        id: tabButton
        TabButton {
            id: button
            property int windowId: 0
            property string windowTitle: " "
            property string windowUrl: " "
            property string windowIcon: "qrc:/icons/stackoverflow.svg"
            implicitWidth: 300
            implicitHeight: 32

            contentItem: Item {
                anchors.fill: parent
                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    Image {
                        Layout.leftMargin: 10
                        source: Qt.resolvedUrl(windowIcon)
                        sourceSize.width: 16
                        sourceSize.height: 16
                    }
                    Text {
                        text: button.windowTitle
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
                            source: "qrc:/icons/close.svg"
                            width: 16
                            height: 16
                        }
                        MouseArea {
                            property bool enter: false
                            anchors.fill: parent
                            onClicked: {
                                WindowManager.removeWindow(button.windowId)
                            }
                            hoverEnabled: true
                            onEntered: {
                                enter = true
                                parent.color = "#adadad"
                            }
                            onExited: {
                                enter = false
                                parent.color = "transparent"
                            }
                            ToolTip {
                                visible: parent.enter
                                text: "关闭标签页"
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
            background: Rectangle {
                //                id: bg
                anchors.fill: parent
                color: button.focus ? "#f7f7f7" : "transparent"
                focus: true
                radius: 6
                MouseArea {
                    property bool enter: false
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        enter = true
                    }
                    onExited: {
                        enter = false
                    }
                    onClicked: parent.clicked()
                    ToolTip {
                        visible: parent.enter
                        text: button.windowTitle + "\n" + button.windowUrl
                        delay: 1000
                        background: Rectangle {
                            color: "#f7f7f7"
                            border.color: "black"
                            border.width: 1
                            radius: 5
                        }
                    }
                }
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
            function setState(title_, url_, windowIcon_) {
                windowTitle = title_
                windowUrl = url_
                windowIcon = windowIcon_
            }

            onWindowUrlChanged: {
                if (tabBar.currentItem === this) {
                    header.currentUrl = windowUrl
                }
            }

            onWindowTitleChanged: {
                if (tabBar.currentItem === this) {
                    header.currentTitle = windowTitle
                }
            }
        }
    }

    Connections {
        target: WindowManager
        function onAddTab(windowId_, windowTitle_, windowUrl_, windowIcon_, toToggle_) {
            addTabItem(windowId_, windowTitle_, windowUrl_, windowIcon_,
                       toToggle_)
        WindowManager.resizeWindow(rootWindow.width, rootWindow.height - 74)
        }
        function onRemoveTab(windowId_) {
            removeTabItem(windowId_)
        }
        function onSetTabState(windowId_, title_, url_, icon_) {
            setTabState(windowId_, title_, url_, icon_)
        }
        function onParentWindowSet()  {
        WindowManager.addWindow(header.defaultUrl)
        }
//        function onWindowCreated() {
//            console.info("====================================")
//        WindowManager.resizeWindow(0, 74, rootWindow.width, rootWindow.height - 74)
//        }
    }

    Component.onCompleted: {
//        WindowManager.addWindow(header.defaultUrl)
//        WindowManager.resizeWindow(0, 74, width, height - 74)
//        WindowManager.addWindow(header.defaultUrl)
//        WindowManager.removeWindow(tabBar.itemAt(tabBar.count - 1).windowId)
        // todo: 玄学问题：只有一个tab时虽然有focus但无法正确显示颜色。
    }

    function addTabItem(windowId_, windowTitle_, windowUrl_, windowIcon_, toToggle_) {
        tabBar.addItem(tabButton.createObject(tabBar))
        tabBar.itemAt(tabBar.count - 1).windowTitle = windowTitle_
        tabBar.itemAt(tabBar.count - 1).windowId = windowId_
        tabBar.itemAt(tabBar.count - 1).windowUrl = windowUrl_
        tabBar.itemAt(tabBar.count - 1).windowIcon = windowIcon_
        if (toToggle_) {
            tabBar.setCurrentIndex(tabBar.count - 1)
        }
    }

    function removeTabItem(windowId_) {
        for (var i = 0; i < tabBar.count; ++i) {
            if (tabBar.itemAt(i).windowId === windowId_) {
                tabBar.removeItem(tabBar.itemAt(i))
                break
            }
        }
    }
    function setTabState(windowId_, title_, url_, icon_) {
        for (var i = 0; i < tabBar.count; ++i) {
            if (tabBar.itemAt(i).windowId === windowId_) {
                tabBar.itemAt(i).windowTitle = title_
                tabBar.itemAt(i).windowUrl = url_
                tabBar.itemAt(i).windowIcon = icon_
                break
            }
        }
    }

    function adjustItem() {
        // the algorithm is undecided
        var equal_width = Window.width / tabBar.count - 50 / tabBar.count
        if (equal_width < 300) {
            for (var i = 0; i < tabBar.count; ++i) {
                tabBar.itemAt(i).implicitWidth = equal_width
            }
        } else {
            for (var j = 0; j < tabBar.count; ++j) {
                tabBar.itemAt(j).implicitWidth = 300
            }
        }
    }

    //    function setBrowserIdToTab(browserId_,tabIndex_){
    //        tabBar.itemAt(tabIndex_).browserId = browserId_
    //    }
    Window.onWidthChanged: {
        adjustItem()
    }
    //    function
}
