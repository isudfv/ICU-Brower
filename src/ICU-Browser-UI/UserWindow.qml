import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    id: rootWindow
    visible: true
    height: 200
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

