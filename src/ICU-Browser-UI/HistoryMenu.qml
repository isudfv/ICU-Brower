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
        id: historyRectangle
        color: "white"
        radius: 10
        border.width: 3
        border.color: "black"
        anchors.fill: parent

        ColumnLayout {
            id: historyLayout
            // anchors.fill: parent
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
            spacing: 2

            // 历史记录头部
            Rectangle {
                id: headRectangle
                // 判断用户是否在进行历史的搜索
                property bool isSearch: false
                // 与历史记录框的左留白、上留白
                Layout.leftMargin: 12
                Layout.topMargin: 10
                height: 25
                width: historyRectangle.width - 24
                color: "red"
                RowLayout {
                    anchors.fill: parent               
                    // Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
                    spacing: 5

                    // 未搜索状态的由四矩形组成
                    // 1. 历史记录
                    Rectangle {
                        visible: !headRectangle.isSearch
                        // 设置样式
                        color: "pink"
                        height: 25
                        width: 80
                        radius: 5
                        Text {
                            // 字体内容以及格式设置
                            text: "历史记录"
                            font.bold: true
                            font.pixelSize: 15
                            // 设置在矩形中居中，需要绑定矩形的高度、宽度
                            height: parent.height
                            width: parent.width
                            horizontalAlignment:  Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    // 2.占位矩形
                    Rectangle {
                        visible: !headRectangle.isSearch
                        width: 221
                        height: 25
                        radius: 5
                        color: "black"
                    }

                    // 3. 进入搜索
                    Rectangle {
                        visible: !headRectangle.isSearch

                        id: enterSearch
                        property bool enter: false

                        height: 25
                        width: 30
                        radius: 5
                        color: enterSearch.enter ? "black" : "purple"

                        Image {
                            source: "qrc:/icons/search.svg"
                            width: 20
                            height: 20
                            // 居中设置
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        MouseArea {
                            ToolTip {
                                visible: enterSearch.enter
                                text: "搜索历史记录"
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }

                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                headRectangle.isSearch = true
                            }
                            onEntered: {
                                enterSearch.enter = true
                            }
                            onExited: {
                                enterSearch.enter = false
                            }
                        }
                    }

                    // 4.清空历史记录
                    Rectangle {
                        visible: !headRectangle.isSearch

                        id: clearHistory
                        property bool enter: false
                        
                        height: 25
                        width: 30
                        radius: 5
                        color: clearHistory.enter ? "black" : "blue"

                        Image {
                            source: "qrc:/icons/delete.svg"
                            width: 20
                            height: 20
                            // 居中设置
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        MouseArea {
                            ToolTip {
                                visible: clearHistory.enter
                                text: "清空历史记录"
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }

                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                headRectangle.isSearch = true
                            }
                            onEntered: {
                                clearHistory.enter = true
                            }
                            onExited: {
                                clearHistory.enter = false 
                            }
                        }
                    }
                    // 搜索状态时的两个矩形
                    // 1. 返回
                    Rectangle {
                        visible: headRectangle.isSearch

                        id: backNormal
                        property bool enter: false

                        height: 25
                        width: 30
                        radius: 5
                        color: backNormal.enter ? "black" : "purple"

                        Image {
                            source: "qrc:/icons/back.svg"
                            width: 20
                            height: 20
                            // 居中设置
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        MouseArea {
                            ToolTip {
                                visible: backNormal.enter
                                text: "退出搜索"
                                background: Rectangle {
                                    color: "#f7f7f7"
                                    border.color: "black"
                                    border.width: 1
                                    radius: 5
                                }
                            }
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                headRectangle.isSearch = false
                            }
                            onEntered: {
                                backNormal.enter = true
                            }
                            onExited: {
                                backNormal.enter = false
                            }
                        }
                    }
                    // 2.搜索框
                    Rectangle {
                        visible: headRectangle.isSearch
                        height: 25
                        width: 340
                        radius: 5
                        
                        TextField {
                            id: input
                            height: 25
                            width: 340

                            // 光标居中
                            verticalAlignment: TextField.AlignVCenter 
                            // 设置光标、输入文字大小
                            font.pixelSize: 14
                            placeholderText: "搜索历史记录"
                            placeholderTextColor: "#767676"

                            // 背景框
                            background: Rectangle {
                                radius: 5
                                border.color: "#979797"
                                border.width: 1
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: {
                                        parent.border.width = 2
                                    }
                                    onExited: {
                                        parent.border.width = 1
                                    }
                                }
                            }                      
                        }
                    }
                }
            }

            // 一条分界线
            Rectangle {
                // color: "#eaeaea"
                color: "black"
                height: 1.5
                width: historyRectangle.width 
            }

            // 具体的历史记录项
            ListView {
                model: historyModel
                // 布局设置
                Layout.leftMargin: 12
                Layout.fillHeight: true
                
                delegate: Rectangle {
                    id: detailRectangle
                    property bool enter: false
                    color: enter || signalDelete.enter ? "#28b0e9" : "black"
                    width: historyRectangle.width - 24
                    height: 25

                    MouseArea {
                        anchors.fill: parent
                        // 鼠标悬浮
                        hoverEnabled: true
                        onEntered: {
                            detailRectangle.enter = true
                        }
                        onExited: {
                            detailRectangle.enter = false
                        }
                    }

                    RowLayout {
                        anchors.fill: parent
                        spacing: 5
                        // 具体历史记录由三矩形构成
                        // 1.历史记录的内容信息
                        Rectangle {
                            color: "pink"
                            height: 25
                            width: 330
                            radius: 5
                            Text {
                                text: name
                                // 设置在矩形中垂直居中；左对齐（默认）
                                // 需要绑定矩形的高度、宽度
                                height: parent.height
                                width: parent.width
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        // 2. 历史记录的时间信息
                        Rectangle {
                            id: signalDelete
                            property bool enter: false
                            color: signalDelete.enter ? "black" : "grey"
                            height: 25
                            width: 40
                            radius: 5
                            // 鼠标未悬浮时：显示时间信息
                            Text {
                                visible: !signalDelete.enter && !detailRectangle.enter
                                text: time
                                // 设置在矩形中居中，需要绑定矩形的高度、宽度
                                height: parent.height
                                width: parent.width
                                horizontalAlignment:  Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            // 鼠标悬浮时： 显示删除按钮
                            Image {
                                visible: detailRectangle.enter || signalDelete.enter
                                source: "qrc:/icons/close.svg"
                                width: 16
                                height: 16
                                // 居中设置
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                onEntered: {
                                    signalDelete.enter = true
                                }
                                onExited: {
                                    signalDelete.enter = false
                                }

                                ToolTip {
                                    visible: signalDelete.enter
                                    text: "删除"
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
        id: historyModel

        ListElement {
            // img: "qrc:/icons/history.svg"
            name: "Bilibili"
            time: "12:00"
            // url: "bilibili.com"
        }
    }

    function loadHistory(){
        historyManager.loadHistory(header.userid, clearHistory, addHistoryItem)
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
