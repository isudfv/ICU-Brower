import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import Managers

Item {
//    property QtObject rootWindow
    id: header
    property bool activeBack: false
    property bool activeForward: false
    property string currentUrl: "https://www.bilibili.com"
    property string currentTitle: "moep"
    property int currentUserId: 0
    property string currentUserName: "tourists"
    property Item currentTabItem: null
    property int currentWindowIndex: 0
    property string defaultUrl: "https://www.bilibili.com"



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
            id:titlebar
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

    Connections{
        target: WindowManager
        function onSetHeaderState(activeBack_,activeForward_){
            setWindowState(activeBack_,activeForward_)
        }
    }

    function setWindowState(activeBack_,activeForward_){
        activeBack = activeBack_
        activeForward = activeForward_
    }

    function setUserInfo(userid_,username_){
        currentUserId = userid_
        currentUserName = username_
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/
