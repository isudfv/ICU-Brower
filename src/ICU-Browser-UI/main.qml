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

import com.fuck.test 1.0

Window {
    id: rootWindow
    width: 960
    height: 540
    visible: true
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
        Rectangle {
            color: "red"
            Layout.fillWidth: true
            //            Layout.fillHeight: parent
            anchors.top: Header.bottom
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            //            Layout.alignment: Qt.AlignTop
            height: 20
        }
    }
    onWidthChanged: cefWindow.resizeCEFWindow(0, 111, width, height)
    onHeightChanged: cefWindow.resizeCEFWindow(0, 111, width, height)

    onActiveFocusItemChanged: {
        console.log(activeFocusItem)
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}
}
##^##*/

