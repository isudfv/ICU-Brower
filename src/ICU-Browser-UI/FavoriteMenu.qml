import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    id: rootwindow
    visible: false
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint
    signal userChange(int uid)
    property int userid: 0
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
                    text: "收藏夹"
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: 15
                }

                Rectangle{
                    property bool canfavorite: true //getCanFavorite(uid,url)
                    anchors.verticalCenter :parent.verticalCenter
                    x:parent.x + parent.width - 30
                    width: 20
                    height: 20
                    color: "transparent"
                    radius: 2
                    Image {
                        source: parent.canfavorite ? "qrc:/icons/star.svg" : "qrc:/icons/fillstar.svg"
                        width: 20
                        height: 20
                    }
                    MouseArea {
                        property bool enter: false
                        anchors.fill: parent
                        hoverEnabled: parent.canfavorite
                        enabled: parent.canfavorite
                        onClicked: {
                            //addFavariteItem(uid,)
                            var tempname = "good"
                            var tempurl = "day"
                            cefWindow.trying(tempname,tempurl,addFavoriteItem)
                        }
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
                            text: "收藏当前页面"
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
                id:favoritelist
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: favoritemodel
                delegate: Rectangle {
                    width: favoritelist.width
                    height: 40
                    color: "#f7f7f7"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                        }
                        onEntered: {
                            parent.color = "#dcdcdc"
                        }
                        onExited: {
                            parent.color = "#f7f7f7"
                        }
                    }
                    RowLayout {
                        anchors.fill: parent
                        spacing: 10
                        Text {
                            text: name
                            fontSizeMode: Text.Fit
                            Layout.leftMargin: 10
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
                                hoverEnabled: true
                                onClicked: {
//                                    removeFavariteItem(uid,url,removeFavariteItem)
                                }
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
                                    text: "取消收藏"
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
        id: favoritemodel
        ListElement {
            name: "Bilibili"
            url: "bilibili.com"
        }
        ListElement {
            name: "harmoe"
            url: "bilibili.com"
        }
        ListElement {
            name: "tomori"
            url: "bilibili.com"
        }
    }

    function clearFavorite(){
        favoritemodel.clear()
        favoritemodel.sync()
    }

    function loadFavorite(){
        //loadFavorite(uid,addFavoriteItem,clearFavorite)
    }

    function addFavoriteItem(name,url){
        favoritemodel.append({"name": name,"url": url})
    }

    function removeFavariteItem(url){
        for(var i=0;i<favoritemodel.count;i++){
            if(favoritemodel.get(i).url === url){
                favoritemodel.remove(i)
                break
            }
        }
    }

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            visible = false
        }
    }
    onVisibleChanged: {
        if (visible) {
            requestActivate()
        }
    }

    onUserChange: {
        userid = uid
    }
}
