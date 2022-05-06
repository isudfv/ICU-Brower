import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    id:rootwindow
    visible: false
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint
    ColumnLayout {
        anchors.fill: parent

        Menu{
            id:menu
            height: parent.height
            width: parent.width
//            Layout.fillWidth: parent
            Action{
                text: "bilibili"
                onTriggered: {
                    console.log("bilibili")
                }
            }
            Action{
                text: "harmoe"
                onTriggered: {
                    console.log("harmoe")
                }
            }
            Action{
                text: "tomori"
                onTriggered: {
                    console.log("tomori")
                }
            }
            Action{
                text: "tomori"
                onTriggered: {
                    console.log("tomori")
                }
            }
            Action{
                text: "tomori"
                onTriggered: {
                    console.log("tomori")
                }
            }
            Action{
                text: "tomori"
                onTriggered: {
                    console.log("tomori")
                }
            }
            background: Rectangle{
                color: "white"
                radius: 10
                border.width: 3
                border.color: "#f7f7f7"

            }

            onClosed: {
                rootwindow.visible = false
            }

        }
    }
    onActiveFocusItemChanged: {
        if(!activeFocusItem){
            visible = false
        }
    }
    onVisibleChanged: {
        if(visible){
            menu.open()
        }
    }
}
