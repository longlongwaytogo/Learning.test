import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    width: 300
    height: 200


    Component {
        id: btnSyle
        ButtonStyle {
            background:  Rectangle {
                implicitHeight: 25
                implicitWidth: 75
                color: "#DDDDDDDD"
                border.width: control.pressed ? 2 : 1
                border.color: (control.hovered || control.pressed) ? "green" : "#888808"
            }
        }
    }


    Button {
        text: "open"
        style: btnSyle
        anchors.left:  parent.left
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        anchors.rightMargin: 10
        id: open_btn


    }
    Button {
        text: "quit"
        style: btnSyle
        anchors.left: open_btn.right
        anchors.top: open_btn.top
        anchors.leftMargin: 6
        onClicked: Qt.quit()
    }
}
