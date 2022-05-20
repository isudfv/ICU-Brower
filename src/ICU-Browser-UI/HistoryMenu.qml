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
        border.width: 2
        border.color: "#cdcdcd"
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            id: historyLayout
            spacing: 2

            // 历史记录头部
            Rectangle {
                z: 2    // 避免被listView覆盖
                id: headRectangle
                // 判断用户是否在进行历史的搜索
                property bool isSearch: false

                // 外观设置
                height: 45
                width: historyRectangle.width
                color: "white"
                radius: 5
                border.width: 2
                border.color: "#cdcdcd"

                RowLayout {
                    anchors.fill: parent
                    // Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    spacing: 2

                    // 未搜索状态的由三矩形组成
                    // 1. 历史记录
                    Rectangle {
                        id: title
                        property bool enter: false
                        // 布局设置
                        Layout.leftMargin: 12
                        visible: !headRectangle.isSearch
                        // 外观设置
                        color: title.enter ? "#cdcdcd" : "white"
                        height: 30
                        width: 70
                        radius: 5
                        Text {
                            // 字体内容以及格式设置
                            text: "历史记录"
                            font.bold: true
                            font.pixelSize: 15
                            // 设置在矩形中垂直居中
                            // 需要绑定矩形的高度
                            height: parent.height
                            width: parent.width
                            horizontalAlignment:  Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        ToolTip {
                            visible: title.enter
                            text: "回到顶部"
                            delay: 500
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
                            onClicked: {
                                // 回到记录顶部
                                myList.positionViewAtBeginning()
                            }
                            onEntered: {
                                title.enter = true
                            }
                            onExited: {
                                title.enter = false
                            }
                        }
                    }

                    // 2. 进入搜索
                    Rectangle {
                        id: enterSearch
                        Layout.leftMargin: 240              // 布局设置，一个较大间隔使得靠右
                        visible: !headRectangle.isSearch                        
                        property bool enter: false

                        height: 30
                        width: 30
                        radius: 5
                        color: enterSearch.enter ? "#cdcdcd" : "white"

                        Image {
                            source: "qrc:/icons/search.svg"
                            width: 20
                            height: 20
                            // 居中设置
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        
                        ToolTip {
                            visible: enterSearch.enter
                            text: "搜索历史记录"
                            delay: 500
                            background: Rectangle {
                                color: "#f7f7f7"
                                border.color: "black"
                                border.width: 1
                                radius: 5
                            }
                        }

                        MouseArea {
                            anchors.fill: parent            // 充满父类
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

                    // 3.清空历史记录
                    Rectangle {
                        id: clearAll
                        Layout.rightMargin: 12              // 布局设置
                        visible: !headRectangle.isSearch                        
                        property bool enter: false

                        // 外观设置
                        height: 30
                        width: 30
                        radius: 5
                        color: clearAll.enter ? "#d96b6a" : "white"

                        Image {
                            source: "qrc:/icons/delete.svg"
                            width: 20
                            height: 20
                            // 居中设置
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ToolTip {
                            visible: clearAll.enter
                            text: "清空历史记录"
                            delay: 500
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
                        id: backNormal
                        Layout.leftMargin: 12
                        property bool enter: false
                        visible: headRectangle.isSearch
                        
                        // 外观设置
                        height: 30
                        width: 30
                        radius: 5
                        color: backNormal.enter ? "#cdcdcd" : "white"

                        Image {
                            source: "qrc:/icons/back.svg"
                            width: 20
                            height: 20
                            // 居中设置
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        ToolTip {
                            visible: backNormal.enter
                            text: "退出搜索"
                            delay: 500

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
                        height: 30
                        width: 330
                        radius: 5

                        TextField {                            
                            id: input
                            anchors.fill: parent
                            leftPadding: 40                 // 左侧留白
                            focusReason: Qt.MouseFocusReason

                            // 回车即完成
                            onEditingFinished: {
                                // console.info("finished")
                            }

                            // 改变即发送信号
                            onTextEdited: {
                                // console.info("edited")
                                historyManager.loadHistory(header.currentUserId, clearHistory, addHistoryItem, input.text)
                            }

                            // 居中
                            verticalAlignment: TextField.AlignVCenter
                            // 设置光标、输入文字大小
                            font.pixelSize: 14

                            // 背景框
                            background: Rectangle {
                                // 左侧的搜索图标
                                Rectangle {
                                    x: 10
                                    width: 20
                                    height: 20
                                    // 垂直居中设置
                                    anchors.verticalCenter: parent.verticalCenter
                                    Image {
                                        source: "qrc:/icons/search.svg"
                                        width: 20
                                        height: 20
                                        // 居中设置
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.verticalCenter: parent.verticalCenter
                                    }
                                }
                                // 圆角以及边框设置
                                radius: 5
                                border.color: input.focus ? "#404142" : "#cdcdcd"
                                border.width: input.focus ? 2 : 1
                                // 鼠标悬浮时设置一个边框大小的变换
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: {
                                        if (!input.focus) {
                                            parent.border.width = 2
                                        }
                                    }
                                    onExited: {
                                        if (!input.focus) {
                                            parent.border.width = 1
                                        }
                                    }
                                }
                            }
                        }
                    }

                }
            }

            // 具体的历史记录项
            ListView {
                id: myList
                model: historyModel

                // 布局设置
                Layout.leftMargin: 12
                Layout.fillHeight: true
                Layout.fillWidth: true

                // 滚动显示条
                 ScrollIndicator.vertical: ScrollIndicator { }


                
                // ScrollBar.vertical: ScrollBar {
                //     size: 0.5
                //     anchors.top: headRectangle.bottom
                //     policy: ScrollBar.AsNeeded
                // }


                // 选项
                delegate: Rectangle {
                    id: detailRectangle
                    property bool enter: false
                    color: detailRectangle.enter || signalDelete.enter ? "#cdcdcd" : "transparent"
                    width: historyRectangle.width - 24
                    height: 38
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
                            height: 38
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
                            color: signalDelete.enter ? "#d96b6a" : "transparent"
                            height: 38
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
                                    console.info(dateText.text)
                                    console.info(nameText.text)
                                    historyManager.removeHistory(nameText.text, url, dateText.text, timeText.text, header.currentUserId, removeHistoryItem)
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
                        height: 38
                        radius: 3
                        color: groupItem.enter || deleteSignle.enter ? "#cdcdcd" : "transparent"

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
                                height: 38
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
                                height: 38
                                radius: 5
                            }
                            // 删除本日的历史记录
                            Rectangle {
                                id: deleteSignle
                                property bool enter: false
                                color: deleteSignle.enter ? "#d96b6a" : "transparent"
                                width: 40
                                height: 38
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
                                    delay: 500
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

                flickableDirection: Flickable.AutoFlickDirection
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
        headRectangle.isSearch = false;
        historyManager.loadHistory(header.currentUserId, clearHistory, addHistoryItem)
    }

    function addHistoryItem(name, url, time, date){
        historyModel.insert(0,{"name":name, "url":url, "time": time, "date": date})
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

    Connections {
        target: historyManager
        function onAddItem(name,url,time,date){
            addHistoryItem(name, url, time, date)
        }
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
