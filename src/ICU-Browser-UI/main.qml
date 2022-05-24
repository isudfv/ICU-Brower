//import QtQuick
//import QtQuick.Window
//import QtQuick.Controls
//Window {
////    signal sizeChange(int x, int y, int width, int height)
//    visible: true
//    width: 400
//    height: 400

////    onSizeChange: {
////        cefWindow.resizeCEFWindow(0, 0, width, height)
////        console.debug(width, height)
////    }
//    onWidthChanged: cefWindow.resizeCEFWindow(0, 0, width, height)
//    onHeightChanged: cefWindow.resizeCEFWindow(0, 0, width, height)
//}
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Managers


Window {
    id: rootWindow
    width: 960
    height: 540
    visible: true
    signal closeWindow()
    color: "#cdcdcd"
    //    flags: Qt.Window | Qt.CustomizeWindowHint

    //    property int headHeight: 111
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Header {
            Layout.fillWidth: true
            height: 111
            Layout.alignment: Qt.AlignTop

            //            rootWindow: rootWindow
        }
    }

    onClosing: function(closeEvent){
        closeEvent.accepted = false
        closeWindow()
    }

    onWidthChanged: {
        WindowManager.resizeWindow(width, height - 74)
    }
    onHeightChanged: {
        WindowManager.resizeWindow(width, height - 74)
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}
}
##^##*/

