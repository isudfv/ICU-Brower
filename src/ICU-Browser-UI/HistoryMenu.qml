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
        border.color: "#f7f7f7"
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
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
                color: "transparent"
                RowLayout {
                    anchors.fill: parent               
                    // Layout.alignment: Qt.AlignLeft | Qt.AlignTop 
                    spacing: 5

                    // 未搜索状态的由四矩形组成
                    // 1. 历史记录
                    Rectangle {
                        visible: !headRectangle.isSearch
                        // 设置样式
                        color: "transparent"
                        // color: "pink"
                        height: 25
                        width: 80
                        radius: 5
                        Text {
                            // 字体内容以及格式设置
                            text: "历史记录"
                            font.bold: true
                            font.pixelSize: 15
                            // 设置在矩形中垂直居中
                            // 需要绑定矩形的高度
                            height: parent.height
                            // width: parent.width
                            // horizontalAlignment:  Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    // 2.占位矩形
                    Rectangle {
                        visible: !headRectangle.isSearch
                        width: 221
                        height: 25
                        radius: 5
                        color: "transparent"
                        // temporary 测试添加记录
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                historyManager.addHistory("youtube", ".", header.currentUserId, addHistoryItem)
                            }
                        }
                    }

                    // 3. 进入搜索
                    Rectangle {
                        visible: !headRectangle.isSearch

                        id: enterSearch
                        property bool enter: false

                        height: 25
                        width: 30
                        radius: 5
                        color: enterSearch.enter ? "#f7f7f7" : "transparent"

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

                        id: clearAll
                        property bool enter: false
                        
                        height: 25
                        width: 30
                        radius: 5
                        color: clearAll.enter ? "#f7f7f7" : "transparent"

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
                                visible: clearAll.enter
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
                                historyManager.clearHistory(header.currentUserId, clearHistory)
                            }
                            onEntered: {
                                clearAll.enter = true
                            }
                            onExited: {
                                clearAll.enter = false 
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
                        color: backNormal.enter ? "#f7f7f7" : "transparent"

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
                                border.color: "#f7f7f7"
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
                color: "#f7f7f7"
                height: 1.5
                width: historyRectangle.width 
            }

            // 具体的历史记录项
            ListView {
                model: historyModel

                // 布局设置
                Layout.leftMargin: 12
                Layout.fillHeight: true

                // 选项
                delegate: Rectangle {
                    id: detailRectangle
                    property bool enter: false
                    color: detailRectangle.enter || signalDelete.enter ? "#f7f7f7" : "transparent"
                    width: historyRectangle.width - 24
                    height: 30
                    radius: 5

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
                            Layout.leftMargin: 5
                            color: "transparent"
                            height: 30
                            width: 325
                            radius: 5
                            Text {
                                id: dateText
                                visible: false
                                text: date
                            }

                            Text {
                                id: nameText
                                text: name
                                // 设置在矩形中垂直居中；左对齐（默认）
                                // 需要绑定矩形的高度、宽度
                                height: parent.height
                                width: parent.width
                                verticalAlignment: Text.AlignVCenter
                                // 信息太长时进行省略显示
                                clip: true
                                elide: Text.ElideRight
                            }
                        }
                        // 2. 历史记录的时间信息
                        Rectangle {
                            id: signalDelete
                            property bool enter: false
                            color: signalDelete.enter ? "#cdcdcd" : "transparent"
                            height: 30
                            width: 40
                            radius: 5
                            // 鼠标未悬浮时：显示时间信息
                            Text {
                                visible: !signalDelete.enter && !detailRectangle.enter
                                id: timeText
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
                                onClicked: {
                                    // console.info(dateText.text)
                                    // console.info(nameText.text)
                                    historyManager.removeHistory(nameText.text, ".", dateText.text, timeText.text, header.currentUserId, removeHistoryItem)
                                }
                                onEntered: {
                                    signalDelete.enter = true
                                }
                                onExited: {
                                    signalDelete.enter = false
                                }

                                ToolTip {
                                    visible: signalDelete.enter
                                    text: "删除此条"
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

                // 分组
                section{
                    //以日期分组
                    property: "date"
                    //指定为完全字符串匹配
                    criteria: ViewSection.FullString

                    //分组标题
                    delegate: Rectangle{
                        id: groupItem
                        property bool enter: false
                        width: historyRectangle.width - 24
                        height: 30
                        color: groupItem.enter || deleteSignle.enter ? "#f7f7f7" : "transparent"

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                // console.log(groupItem.enter)
                            }
                            onEntered: {
                                groupItem.enter = true
                            }
                            onExited: {
                                groupItem.enter = false
                            }
                        }

                        RowLayout {
                            //文本内容
                            Rectangle {
                                color: "transparent"
                                width: 80
                                height: 30
                                radius: 3
                                Text {
                                    //对应section.property指定的字段
                                    text: section
                                    x: 3
                                    font.bold: true
                                    font.pixelSize: 12
                                    // 设置在矩形中垂直居中
                                    // 需要绑定矩形的高度
                                    height: parent.height
                                    // width: parent.width
                                    // horizontalAlignment:  Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            // 占位矩形
                            Rectangle {
                                color: "transparent"
                                width: 246
                                height: 30
                                radius: 5
                            }
                            // 删除本日的历史记录
                            Rectangle {
                                id: deleteSignle
                                property bool enter: false
                                color: deleteSignle.enter ? "#cdcdcd" : "transparent"
                                width: 40
                                height: 30
                                radius: 5
                                Image {
                                    visible: groupItem.enter || deleteSignle.enter
                                    source: "qrc:/icons/close.svg"
                                    width: 16
                                    height: 16
                                    // 居中设置
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                ToolTip {
                                    visible: deleteSignle.enter
                                    text: "删除此日所有历史记录"
                                    background: Rectangle {
                                        color: "#f7f7f7"
                                        border.color: "black"
                                        border.width: 1
                                        radius: 5
                                    }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: {
                                        deleteSignle.enter = true
                                    }
                                    onExited: {
                                        deleteSignle.enter = false
                                    }
                                    onClicked: {
                                        // console.info(section)
                                        historyManager.removeSignalDayHistory(header.currentUserId, section, removeSignalDayHistory)
                                    }
                                }
                            }
                        }
                        
                        
                    }
                    //位置
                    
                }
            }
        }
    }

    // model 
    ListModel {
        // 如果一个section穿插在Model的不同位置，
        // ListView不会将一个分组内的元素放到一起，
        // 而是会显示多个相同的section
        id: historyModel
        
        // ListElement {
        //     name: "bilibili"
        //     time: "00:00"
        //     date: "2001-05-14"
        //     url: "."
        // }
        
    }

    function loadHistory(){
        historyManager.loadHistory(header.currentUserId, clearHistory, addHistoryItem)
    }

    function addHistoryItem(name, url, time, date){
        historyModel.append({"name":name, "url":url, "time": time, "date": date})
    }

    function removeHistoryItem(name, url, time, date){
        for (let i = 0; i < historyModel.count; ++i) {
            if (historyModel.get(i).url === url) {
                historyModel.remove(i)
                break
            }
        }
    }

    function removeSignalDayHistory(uid, date) {
        // 删除单日历史记录
        for (let i = 0; i < historyModel.count; ++i) {
            if (historyModel.get(i).date === date) {
                historyModel.remove(i)
                --i
            }
        }
    }

    function clearHistory(){
        //清空视图中的历史记录
        historyModel.clear()
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
