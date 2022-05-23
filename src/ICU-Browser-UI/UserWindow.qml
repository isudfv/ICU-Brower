import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Managers

Window {
    id: rootWindow
    visible: true
    height: 300
    width: 250
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint
    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "white"
        radius: 6
        border.width: 1
        border.color: "#aeaeae"
        ColumnLayout {
            anchors.fill: parent
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Rectangle {
                Layout.fillWidth: true
                //                Layout.fillHeight: true
                height: 60
                color: "transparent"
                radius: 6
                //                border.width: 1
                //                border.color: "#aeaeae"
                Text {
                    //            id: name
                    text: qsTr("Hello ") + currentUserName
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 20
                    font {
                        pixelSize: 20
                    }
                }
            }
            Row {
                Layout.fillWidth: true
                Layout.leftMargin: 50
                Layout.rightMargin: 50
                Layout.topMargin: 5
                height: 30
                Text {
                    text: "用户代理："
                    font {
                        pixelSize: 15
                    }
                }

                ComboBox {
                    id: uaControl
                    textRole: "key"
                    valueRole: "value"

                    delegate: ItemDelegate {
                        width: uaControl.width
                        contentItem: Text {
                            text: key
                            color: "black"
                            font: uaControl.font
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        highlighted: uaControl.highlightedIndex === index
                    }

                    indicator: Canvas {
                        id: canvas
                        x: uaControl.width - width - uaControl.rightPadding
                        y: uaControl.topPadding + (uaControl.availableHeight - height) / 2
                        width: 12
                        height: 8
                        contextType: "2d"

                        Connections {
                            target: uaControl
                            function onPressedChanged() {
                                canvas.requestPaint()
                            }
                        }

                        onPaint: {
                            context.reset()
                            context.moveTo(0, 0)
                            context.lineTo(width, 0)
                            context.lineTo(width / 2, height)
                            context.closePath()
                            context.fillStyle = uaControl.pressed ? "black" : "gray"
                            context.fill()
                        }
                    }

                    contentItem: Text {
                        leftPadding: 0
                        rightPadding: uaControl.indicator.width + uaControl.spacing

                        text: uaControl.currentText
                        font: uaControl.font
                        color: "black"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: 60
                        implicitHeight: 20
                        border.color: "black"
                        border.width: uaControl.visualFocus ? 2 : 1
                        radius: 2
                    }

                    popup: Popup {
                        y: uaControl.height
                        width: uaControl.width
                        implicitHeight: contentItem.implicitHeight
                        padding: 1

                        contentItem: ListView {
                            clip: true
                            implicitHeight: contentHeight
                            model: uaControl.popup.visible ? uaControl.delegateModel : null
                            currentIndex: uaControl.highlightedIndex

                            ScrollIndicator.vertical: ScrollIndicator {}
                        }

                        background: Rectangle {
                            border.color: "black"
                            radius: 2
                        }
                    }
                    model: uaModel
                    onCurrentTextChanged: {
                        var uaString = uaModel.get(uaControl.find(uaControl.currentText)).value
                        UserManager.setUserAgent(uaString)
                    }
                }

                ListModel {
                    id: uaModel
                }
            }

            Row {
                Layout.fillWidth: true
                Layout.leftMargin: 50
                Layout.rightMargin: 50
                Layout.topMargin: 5
                height: 30
                Text {
                    text: "广告拦截："
                    font {
                        pixelSize: 15
                    }
                }
                Switch {
                    id: adControl
                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 20
                        radius: 10
                        color: adControl.checked ? "#17a81a" : "#ffffff"
                        border.color: adControl.checked ? "#17a81a" : "#cccccc"

                        Rectangle {
                            x: adControl.checked ? parent.width - width : 0
                            width: 20
                            height: 20
                            radius: 10
                            color: adControl.down ? "#cccccc" : "#ffffff"
                            border.color: adControl.checked ? (adControl.down ? "#17a81a" : "#21be2b") : "#999999"
                        }
                    }
                    onToggled: {
                        UserManager.setAdBlockFlag(
                                    adControl.position ? true : false)
                    }
                }
            }
            Row {
                Layout.fillWidth: true
                Layout.leftMargin: 45
                Layout.rightMargin: 50
                spacing: 20
                Button {
                    text: "同步到云端"

                    onClicked: {
                        UserManager.syncHistoryFromLocal(header.currentUserId)
                        UserManager.syncFavouriteFromLocal(header.currentUserId)
                    }

                    background: Rectangle {
                        width: 70
                        height: 25
                        border.color: "black"
                        border.width: 1
                        radius: 2
                    }
                }
                Button {
                    text: "从云端同步"

                    onClicked: {
                        UserManager.syncHistoryToLocal(header.currentUserId)
                        UserManager.syncFavouriteToLocal(header.currentUserId)
                    }

                    background: Rectangle {
                        width: 70
                        height: 25
                        border.color: "black"
                        border.width: 1
                        radius: 2
                    }
                }
            }

            Row {
                Layout.fillWidth: true
                Layout.leftMargin: 180
                Layout.rightMargin: 30
                Layout.topMargin: 20
                Button {
                    text: "退出登录"

                    onClicked: {
                        UserManager.doLogout(header.setUserInfo)
                    }

                    background: Rectangle {
                        width: 60
                        height: 25
                        border.color: "black"
                        border.width: 1
                        radius: 2
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                //                color: "#66ccff"
                color: "transparent"
            }
        }
    }

    Component.onCompleted: {
        uaModel.append({
                           "key": "Edge",
                           "value": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.67 Safari/537.36 Edg/101.0.100.0"
                       })
        uaModel.append({
                           "key": "ICU",
                           "value": "Mozilla/5.0 (Windows NT 10.0; WOW64) ICU/1.0"
                       })
        uaModel.append({
                           "key": "Chrome",
                           "value": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.67 Safari/537.36"
                       })
        uaModel.append({
                           "key": "FireFox",
                           "value": "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:70.0) Gecko/20100101 Firefox/70.0"
                       })
        uaModel.append({
                           "key": "UC",
                           "value": "Mozilla/5.0 (compatible; MSIE 10.0; Windows Phone 8.0; Trident/6.0; IEMobile/10.0; ARM; Touch; NOKIA; Lumia 920) UCBrowser/10.1.0.563 Mobile"
                       })
        uaModel.append({
                           "key": "Safari",
                           "value": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Safari/605.1.15"
                       })
        uaModel.append({
                           "key": "IE7",
                           "value": "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)"
                       })
        uaModel.append({
                           "key": "Android Mobile",
                           "value": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.67 Mobile Safari/537.36"
                       })
        uaModel.sync()
    }

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            userButton.isUserWindow = false
        }
    }
    onVisibleChanged: {
        if (visible) {
            requestActivate()
        }
    }

    //    Connections{
    //        target: header
    //        function onUseridChanged() {
    //            updataFavariteState()
    //        }
    //        function onNowurlChanged(){
    //            updataFavariteState()
    //        }
    //    }

    //    Component.onCompleted: {
    //        loadFavorite()
    //    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}
}
##^##*/

