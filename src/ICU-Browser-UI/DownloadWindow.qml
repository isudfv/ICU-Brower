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
                height: 30
                color: "transparent"
                Text {
                    height: parent.height
                    x: parent.x + 20
                    text: "下载"
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: 15
                }

                Rectangle {
                    id: favoritetitle
                    property bool canfavorite: FavoritesManager.getCanFavorite(
                                                   header.currentUserId,
                                                   header.currentUrl)
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
                        enabled: true
                        onClicked: {
                            DownloadManager.clearDownloadItem()
                        }
                        onEntered: {
                            enter = true
                            parent.color = "#adadad"
                        }
                        onExited: {
                            enter = false
                            parent.color = "transparent"
                        }
                    }
                }
            }

            Rectangle {
                color: "#cdcdcd"
                height: 2
                Layout.fillWidth: true
            }

            ListView {
                id: downloadList
                Layout.leftMargin: 5
                Layout.rightMargin: 5
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 2
                model: downloadModel
                delegate: Rectangle {
                    property bool isChoose: downloadArea.enter
                                            || deleteArea.enter
                                            || closeArea.enter
                    width: downloadList.width
                    height: 40
                    color: isChoose ? "#dcdcdc" : "white"
//                    border.width: 1
//                    border.color: "black"
                    radius: 2
                    MouseArea {
                        id: downloadArea
                        property bool enter: false
                        anchors.fill: parent
                        hoverEnabled: exist
                        enabled: exist
                        onClicked: {
                            if (downloadItemPrecent === 100) {
                                DownloadManager.showDownLoadItemInExplorer(
                                            downloadItemId, downloadItemPath)
                            } else {
                                DownloadManager.changeDownloadItemPauseState(downloadItemId)
                            }
                        }
                        onEntered: {
                            enter = true
                        }
                        onExited: {
                            enter = false
                        }
                    }
                    RowLayout {
                        anchors.fill: parent
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Rectangle {
                            width: 170
                            height: 40
                            color: "transparent"
                            Text {
                                x: parent.x + 10
                                width: 150
                                elide: Text.ElideRight
                                font.pixelSize: 15
                                text: exist ? downloadItemName : "<s>" + downloadItemName + "</s>"
                                color: exist ? "black" : "gray"
                            }
                            //下载条
                            Rectangle {
                                visible: (downloadItemPrecent !== 100) && exist
                                x: parent.x + 10
                                y: parent.y + 20
                                width: downloadItemPrecent
                                height: 10
                                color: "#cceeff"
                            }
                            Rectangle {
                                visible: (downloadItemPrecent !== 100) && exist
                                x: parent.x + 10
                                y: parent.y + 20
                                width: 100
                                height: 10
                                border.width: 1
                                border.color: "black"
                                color: "transparent"
                            }
                            //下载速度
                            Text {
                                visible: (downloadItemPrecent !== 100) && exist && !pause
                                x: parent.x + 115
                                y: parent.y + 20
                                text: (downloadItemCurrentSpeed > 1000000) ? ((downloadItemCurrentSpeed / 1000000).toFixed(2) + "MB/s") : (downloadItemCurrentSpeed > 1000) ? ((downloadItemCurrentSpeed / 1000).toFixed(2) + "KB/s") : (downloadItemCurrentSpeed.toFixed(2) + "B/s")
                            }
                            Image{
                                visible: (downloadItemPrecent !== 100) && exist && pause
                                width: 15
                                height: 15
                                x: parent.x + 115
                                y: parent.y + 20
                                source: "qrc:/icons/pause.svg"
                            }
                        }
                        //删除文件
                        Rectangle {
                            Layout.rightMargin: 5
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
                                id: deleteArea
                                property bool enter: false
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    if (downloadItemPrecent === 100){
                                        DownloadManager.deleteDownloadItem(downloadItemId,downloadItemPath)
                                    }
                                    else{
                                        DownloadManager.stopDownload(downloadItemId)
                                    }

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
                                    text: "删除文件"
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
                        //删除记录
                        Rectangle {
                            Layout.rightMargin: 10
                            width: 20
                            height: 20
                            color: "transparent"
                            radius: 2
                            Image {
                                source: "qrc:/icons/close.svg"
                                width: 20
                                height: 20
                            }
                            MouseArea {
                                id: closeArea
                                property bool enter: false
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    DownloadManager.removeDownloadItem(downloadItemId);
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
                                    text: "删除下载记录"
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

            ListModel {
                id: downloadModel
            }
        }
    }

    function insertDownloadItem(id, name, url, path) {
        downloadModel.insert(0, {
                                 "downloadItemId": id,
                                 "downloadItemName": name,
                                 "downloadItemPrecent": 0,
                                 "downloadItemCurrentSpeed": 0,
                                 "downloadItemUrl": url,
                                 "downloadItemPath": path,
                                 "exist": true,
                                 "pause": false
                             })
    }

    function removeDownloadItem(id) {
        for (var i = 0; i < downloadModel.count; ++i) {
            if (downloadModel.get(i).downloadItemId === id) {
                downloadModel.remove(i)
                break
            }
        }
    }

    function setFileState(id, exist_) {
        for (var i = 0; i < downloadModel.count; ++i) {
            if (downloadModel.get(i).downloadItemId === id) {
                downloadModel.get(i).exist = exist_
                break
            }
        }
    }

    function updateItemState(id, precent, currentSpeed) {
        for (var i = 0; i < downloadModel.count; ++i) {
            if (downloadModel.get(i).downloadItemId === id) {
                downloadModel.get(i).downloadItemPrecent = precent
                downloadModel.get(i).downloadItemCurrentSpeed = currentSpeed
                break
            }
        }
    }

    function changePauseState(id){
        for (var i = 0; i < downloadModel.count; ++i) {
            if (downloadModel.get(i).downloadItemId === id) {
                downloadModel.get(i).pause = !downloadModel.get(i).pause
                break
            }
        }
    }

    Connections {
        target: DownloadManager
        function onAddItem(id, name, url, path) {
            insertDownloadItem(id, name, url, path)
        }
        function onRemoveItem(id) {
            removeDownloadItem(id)
        }
        function onClearItem() {
            downloadModel.clear()
        }
        function onSetFileState(id, exist_) {
            setFileState(id, exist_)
        }
        function onUpdateItemState(id, precent, currentSpeed) {
            updateItemState(id, precent, currentSpeed)
        }
        function onChangePauseState(id){
             changePauseState(id)
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
}
