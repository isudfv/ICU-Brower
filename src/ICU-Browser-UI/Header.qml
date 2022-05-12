import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
//    property QtObject rootWindow
    id: header
    property bool activeBack: false
    property bool activeForward: false
    property string currentUrl: "https://www.bilibili.com"
    property string currentTitle: "moep"
    property int userid: 0
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
        target: windowManager
        function onSetState(activeBack_,activeForward_,currentUrl_,currentTitle_){
            setWindowState(activeBack_,activeForward_,currentUrl_,currentTitle_)
        }
    }

    function setWindowState(activeBack_,activeForward_,currentUrl_,currentTitle_){
        activeBack = activeBack_
        activeForward = activeForward_
        currentUrl = currentUrl_
        currentTitle = currentTitle_
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
