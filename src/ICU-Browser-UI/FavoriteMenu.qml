import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Managers

Window {
    id: rootwindow
    visible: false
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint
    Rectangle {
        color: "white"
        radius: 6
        border.width: 2
        border.color: "#cdcdcd"
        anchors.fill: parent
        ColumnLayout {
            anchors.fill: parent
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Rectangle {
                color: "transparent"
                height: 3
                radius: 6
                Layout.fillWidth: true
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.leftMargin: 5
                Layout.rightMargin: 5
                height: 40
                color: "white"
                z:5
                Text {
                    height: parent.height
                    x: parent.x + 20
                    text: "收藏夹"
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: 15
                }

                Rectangle{
                    id: favoritetitle
                    property bool canfavorite: FavoritesManager.getCanFavorite(header.currentUserId,header.currentUrl)
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
                        hoverEnabled: favoritetitle.canfavorite
                        enabled: favoritetitle.canfavorite
                        onClicked: {
                            FavoritesManager.addFavoriteItem(header.currentUrl,header.currentTitle,header.currentUserId)
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
                Rectangle {
                    color: "#cdcdcd"
                    height: 2
                    width: parent.width + 10
                    x:parent.x - 10
                    y:parent.y + 30
                }
            }



            ListView {
                id:favoritelist
                Layout.leftMargin: 2
                Layout.rightMargin: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                // 滚动条
                ScrollIndicator.vertical: ScrollIndicator { }
                model: favoritemodel
                delegate: Rectangle {
                    id: backGround
                    property bool isChoose: enter || closeArea.enter
                    property bool enter: false
                    width: favoritelist.width
                    height: 40
                    radius: 2
                    color: isChoose ? "#dcdcdc":"white"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            WindowManager.doLoadUrl(header.currentWindowIndex,url,header.currentUserId)
                        }
                        onEntered: {
                            parent.enter = true;
                        }
                        onExited: {
                            parent.enter = false
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
                                id:closeArea
                                property bool enter: false
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    FavoritesManager.removeFavoriteItem(header.currentUserId,url)
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
    }

    function clearFavorite(){
        favoritemodel.clear()
    }

    function loadFavorite(){
        FavoritesManager.loadFavorite(header.currentUserId)
    }

    function addFavoriteItem(name,url){
        favoritemodel.append({"name": name,"url": url})
        updataFavoriteState()
    }

    function removeFavariteItem(url){
        for(var i=0;i<favoritemodel.count;i++){
            if(favoritemodel.get(i).url === url){
                favoritemodel.remove(i)
                break
            }

        }
        updataFavoriteState()
    }

    function updataFavoriteState(){
        favoritetitle.canfavorite = FavoritesManager.getCanFavorite(header.currentUserId,header.currentUrl)
    }

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            visible = false
        }
    }
    onVisibleChanged: {
        if (visible) {
            loadFavorite()
            requestActivate()
        }
    }

    Connections{
        target: header
        function onCurrentUrlChanged() {
            updataFavoriteState()
        }
        function onCurrentTitleChanged(){
            updataFavoriteState()
        }
        function onCurrentUserIdChanged(){
            loadFavorite()
            favoritetitle.canfavorite = FavoritesManager.getCanFavorite(header.currentUserId,header.currentUrl)
        }
    }

    Connections{
        target:FavoritesManager
        function onAddFavorite(name,url){
            addFavoriteItem(name,url)
        }
        function onClearFavorite(){
            clearFavorite()
        }
        function onRemoveFavorite(url){
            removeFavariteItem(url)
        }
    }

    Component.onCompleted: {
        loadFavorite()
    }
}
