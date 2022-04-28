import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Rectangle {
            color: "red"
            Layout.fillWidth: parent
            height: 2
        }

        Rectangle {
            color: "green"
            Layout.fillWidth: parent
            height: 35
        }

//        RowLayout {}
    }
}
