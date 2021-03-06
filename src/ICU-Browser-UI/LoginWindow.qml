import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Managers

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
            text: qsTr("登录")
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            font {
                pixelSize: 20
            }
        }

        Rectangle {
            id: inputRectangle
            //            id: rectangle1
            width: 150
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 70
            anchors.horizontalCenter: parent.horizontalCenter
            TextField {
                id: userName
                anchors.fill: parent
                //                implicitHeight: 48
                //                implicitWidth: 250
                verticalAlignment: TextInput.AlignVCenter

                //                verticalAlignment: PlaceholderText.AlignVCenter
                font.pixelSize: 15

                selectByMouse: true
                selectedTextColor: "white"
                selectionColor: "#0078d4"

                wrapMode: TextField.Wrap
                //                echoMode: TextInput.Password
                leftPadding: 32
                placeholderText: "输入用户名"
                background: Rectangle {
                    anchors.fill: parent
                    //                        anchors.horizontalCenter: parent.horizontalCenter
                    //                        anchors.verticalCenter: rectangle.verticalCenter
                    color: "white"
                    implicitHeight: parent.height
                    implicitWidth: parent.width
                    border.width: 1
                    border.color: "#cecece"
                    radius: 3
                }
            }
            Image {
                //                id: name25
                source: "qrc:/icons/user.svg"
                anchors.leftMargin: 4
                width: 24
                height: 24
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
        }

        Rectangle {

            //            id: rectangle1
            width: 150
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 110
            anchors.horizontalCenter: parent.horizontalCenter
            TextField {
                id: password
                anchors.fill: parent
                verticalAlignment: TextInput.AlignVCenter
                //                anchors.verticalCenter: parent.verticalCenter
                //                             text: ""
                placeholderText: "输入密码"

                font.pixelSize: 15
                wrapMode: TextField.Wrap
                echoMode: TextInput.Password
                leftPadding: 32
                background: Rectangle {
                    anchors.fill: parent
                    //                        anchors.horizontalCenter: parent.horizontalCenter
                    //                        anchors.verticalCenter: rectangle.verticalCenter
                    color: "white"
                    implicitHeight: parent.height
                    implicitWidth: parent.width
                    border.width: 1
                    border.color: "#cecece"
                    radius: 3
                }
            }
            Image {
                //                id: name25
                source: "qrc:/icons/locker.svg"
                anchors.leftMargin: 4
                width: 24
                height: 24
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
        }

        Button {
            height: 32
            width: 90
            text: "登录"

            font {
                pixelSize: 15
            }

            anchors.top: parent.top
            anchors.topMargin: 150

            anchors.left: parent.left
            anchors.leftMargin: rootWindow.width / 2 - inputRectangle.width / 2

            background: Rectangle {
                implicitWidth: 80
                implicitHeight: 32
                border.color: "#26282a"
                border.width: 1
                radius: 4
            }

            onClicked: {
                UserManager.doLogin(userName.text, password.text, loginStateCheck)
                password.text = ""
            }
        }

        Button {
            height: 32
            width: 50
            text: "注册"

            font {
                pixelSize: 15
            }

            anchors.top: parent.top
            anchors.topMargin: 150

            anchors.right: parent.right
            anchors.rightMargin: rootWindow.width / 2 - inputRectangle.width / 2

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 54
                border.color: "#26282a"
                border.width: 1
                radius: 4
            }

            onClicked: {
                userButton.isLoginWindow = false
                userButton.isRegisterWindow = true
            }
        }
    }

    onActiveFocusItemChanged: {
        if (!activeFocusItem) {
            userButton.isLoginWindow = false
        }
    }
    onVisibleChanged: {
        if (visible) {
            requestActivate()
        }
    }

    function loginStateCheck(error_code, uid = "") {
        console.info("callback called with ec: ", error_code)
//        console.info(userManager.LoginSuccess, userManager.userNotExist, Manager.PasswordError)
        switch (error_code) {
        case UserManager.LoginSuccess:
        {
            console.info("success")
            userButton.isLoginWindow = false;
            userButton.isRegisterWindow = false;
            userButton.isUserWindow = true;
            setUserInfo(uid, userName.text)
            break
        }
        case UserManager.UserNotExist:
        {
            console.info("User Not Exist")
            userName.text=""
            userName.placeholderText = "User Not Exist";
            password.text = "";
            break
        }
        case UserManager.PasswordError:
            console.info("Password Error")
//            userName.placeholderText = "Password Error";
            password.text = ""
            password.placeholderText = "Password Error"
            break
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

