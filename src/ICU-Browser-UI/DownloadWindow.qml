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
        radius: 6
        border.width: 3
        border.color: "#f7f7f7"
        anchors.fill: parent
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
}
