import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
//    property QtObject rootWindow
    id: header
    property bool activeBack: false
    property bool activeForward: false
    property string nowurl: "bilibili.com"
    property string nowtitle: "bilibili"
    property int userid: 0



    MouseArea {
        anchors.fill: parent
        onClicked: {
            rootWindow.requestActivate()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TitleBar {
            height: 37
            Layout.fillWidth: parent
//            rootWindow: rootWindow
//            Layout.fillHeight: parent
//            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
//            Layout.fillWidth: parent
        }
        NaviBar {
            id:navibar
            height: 36
            Layout.fillWidth: parent
//            height
        }

        Rectangle {
            color: "#f7f7f7"
            height: 2
//            width:
            Layout.fillWidth: parent
        }

        Rectangle {
            color: "#cdcdcd"
            height: 36
//            width:
            Layout.fillWidth: parent
        }

    }

    function setWindowState(activeBack_,activeForward_,nowurl_,nowtitle_){
        activeBack = activeBack_
        activeForward = activeForward_
        nowurl = nowurl_
        nowtitle = nowtitle_
    }

    function setUserId(uid){
        userid = uid
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/
