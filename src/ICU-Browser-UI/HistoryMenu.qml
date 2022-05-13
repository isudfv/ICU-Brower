import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    id: rootwindow
    visible: false
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint

    Rectangle {
        color: "white"
        radius: 10
        border.width: 3
        border.color: "#f7f7f7"
        anchors.fill: parent
        ColumnLayout {
            anchors.fill: parent
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Rectangle {
                Layout.fillWidth: true
                height: 40
                color: "transparent"
                Text {
                    height: parent.height
                    x: parent.x + 10
                    text: "历史记录"
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: 15

                    ToolTip {
                        text: "打开历史记录页面"
                    }

                    MouseArea {

                    }
                }

                Rectangle{
                    id: search
                    anchors.verticalCenter: parent.verticalCenter
                    x: parent.x + parent.width - 60
                    width: 20
                    height: 20
                    color: "transparent"
                    radius: 2
                    Image {
                        source: "qrc:/icons/search.svg"
                        width: 20
                        height: 20
                    }
                    MouseArea {
                        property bool enter: false
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            enter = true
                            parent.color = "#adadad"
                        }
                        onExited: {
                            enter = false
                            parent.color = "transparent"
                        }
                        onClicked: {
                            historyManager.addHistory("youtube", "12:00", ".", header.currentUserId, addHistoryItem)
                        }
                        ToolTip {
                            visible: parent.enter
                            text: "搜索历史记录"
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

                Rectangle{
                    id: more
                    anchors.verticalCenter: parent.verticalCenter
                    x: parent.x + parent.width - 30
                    width: 20
                    height: 20
                    color: "transparent"
                    radius: 2
                    Image {
                        source: "qrc:/icons/delete.svg"
                        width: 20
                        height: 20
                    }

                    MouseArea {
                        property bool enter: false
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            enter = true
                            parent.color = "#adadad"
                        }
                        onExited: {
                            enter = false
                            parent.color = "transparent"
                        }
                        onClicked: {
                            historyManager.clearHistory(header.currentUserId, clearHistory)
                        }
                        ToolTip {
                            visible: parent.enter
                            text: "删除历史记录"
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

            ListView {
                id: historylist
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: historymodel
                delegate: Rectangle {
                    property bool enter: false
                    id: rect
                    width: historylist.width
                    height: 30
                    color: enter || cls_mouse.cls_enter ? "#dcdcdc" : "transparent"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            //doload(url)
                        }
                        onEntered: {
                            rect.enter = true
                            // parent.color = "#dcdcdc"
                            // icon.color = "#dcdcdc"
                            // detail.color = "#dcdcdc"
                            // date.color = "#dcdcdc"
                        }
                        onExited: {
                            rect.enter = false
                            // parent.color = "transparent"
                            // icon.color = "transparent"
                            // detail.color = "transparent"
                            // date.color = "transparent"
                        }
                    }

                    RowLayout {
                        anchors.fill: rect
                        spacing: 5
                        // icon
                        Rectangle {
                            id: icon
                            Layout.leftMargin: 5
                            color: rect.color
                            // color: "pink"
                            width: 20
                            height: 20
                            radius: 2
                            Image {
                                // source: "qrc:/icons/close.svg"
                                source: img
                                width: 20
                                height: 20
                            }
                        }

                        // detail
                        Rectangle {
                            id: detail
                            width: 260
                            color: rect.color
                            // color: "purple"
                            height: parent.height
                            Text {
                                text: name
                                height: parent.height
                                width: parent.width
                                verticalAlignment: Text.AlignVCenter
                                clip: true
                                elide: Text.ElideRight
                            }
                        }

                        // date
                        Rectangle {
                            id: date
                            // Layout.rightMargin: 5
                            color: rect.color
                            // color: "grey"
                            height: parent.height
                            width: 50
                            Text {
                                text: time
                                height: parent.height
                                width: parent.width
                                verticalAlignment: Text.AlignVCenter
                                clip: true
                                elide: Text.ElideRight
                            }
                        }
                        // cls
                        Rectangle {
                            id: cls
                            Layout.rightMargin: 5
                            anchors.horizontalCenter: rect.horizontalCenter
                            color: cls_mouse.cls_enter ? "#f08cb8" : rect.color
                            // color: "orange"
                            height: 16
                            width: 16
                            radius: 5
                            Image {
                                source: "qrc:/icons/close.svg"
                                width: 16
                                height: 16
                            }
                            MouseArea {
                                id: cls_mouse
                                property bool cls_enter: false
                                propagateComposedEvents: true
                                anchors.fill: cls
                                hoverEnabled: true
                                onClicked: {
                                    historyManager.removeHistory(name, time, url, header.currentUserId, removeHistoryItem)
                                    console.log(cls_enter)
                                    console.log(rect.enter)
                                }
                                onEntered: {
                                    rect.enter = true
                                    cls_enter = true
                                    // cls.color = "#adadad"
                                }
                                onExited: {
                                    // enter = false
                                    cls_enter = false
                                    // cls.color = "#ead7d4"
                                }
                                ToolTip {
                                    visible: cls_mouse.cls_enter
                                    text: "删除此项历史记录"
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

    ListModel {
        id: historymodel

        ListElement {
            img: "qrc:/icons/history.svg"
            name: "Bilibili"
            time: "12:00"
            url: "bilibili.com"
        }
    }

    function loadHistory(){
        console.log(123)
        historyManager.loadHistory(header.currentUserId, clearHistory, addHistoryItem)
    }

    function addHistoryItem(name,time,url){
        historymodel.append({"name":name, "time":time, "url":url})
    }

    function removeHistoryItem(name, time, url){
        for (let i = 0; i < historymodel.count; ++i) {
            if (historymodel.get(i).url === url) {
                historymodel.remove(i)
                break
            }
        }
    }

    function clearHistory(){
        //清空视图中的历史记录
        historymodel.clear()
    }

    onActiveFocusItemChanged: {
        if(!activeFocusItem){
        visible = false
    }
}
    onVisibleChanged: {
        if(visible) {
           loadHistory()
        }
    }
    Component.onCompleted: {
        loadHistory()
    }
}
