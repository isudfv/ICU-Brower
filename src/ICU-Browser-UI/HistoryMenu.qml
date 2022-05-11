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
                    width: historylist.width
                    height: 30
//                    color: "transparent"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            //doload(url)
                        }
                        onEntered: {
                            parent.color = "#dcdcdc"
                            icon.color = "#dcdcdc"
                            detail.color = "#dcdcdc"
                            date.color = "#dcdcdc"
                        }
                        onExited: {
                            parent.color = "transparent"
                            icon.color = "transparent"
                            detail.color = "transparent"
                            date.color = "transparent"
                        }
                    }
                    RowLayout {
                        anchors.fill: parent

                        spacing: 5
                        Rectangle {
                            id: icon
                            Layout.leftMargin: 5
//                            color: "grey"
                            width: 20
                            height: 20
                            radius: 2
                            Image {
//                                source: "qrc:/icons/close.svg"
                                source: img
                                width: 20
                                height: 20
                            }
                        }

                        Rectangle {
                            id: detail
                            width:300
//                            color: "pink"
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

                        Rectangle {
                            id: date
                            Layout.rightMargin: 5
//                            color: "purple"
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
         ListElement {
             img: "qrc:/icons/history.svg"
             name: "googledfajdflkdsajflkasjdfkljasklfjaskljfasdfjklkljdsafjklasdfafdsjlk"
             time: "12:12"
             url: "bilibili.com"
         }
         ListElement {
             img: "qrc:/icons/history.svg"
             name: "youtube"
             time: "12:12"
             url: "bilibili.com"
         }
    }

    onActiveFocusItemChanged: {
        if(!activeFocusItem){
        visible = false
    }
}
onVisibleChanged: {
    if(visible)
    {
//        menu.open()
    }
}
}
