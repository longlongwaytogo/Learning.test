//import QtQuick 2.2
//import QtQuick.Controls 2.1
//import QtQuick.Controls.Styles 1.2

import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

    Rectangle {
        width: 530
        height: 640
        color: "gray"


        Button {
                text: "Quit";
                anchors.centerIn: parent;
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 70;
                        implicitHeight: 25;
                        border.width: control.pressed ? 2 : 1;
                        border.color: (control.hovered || control.pressed) ? "green" : "#888888";
                    }
                }
                onClicked: Qt.quit();
            }


        Button {
            text: "button_style"
            anchors.top: quitBtn.down + 20
            anchors.left:  quitBtn.left

                }

        Image {

            source: "https://www.baidu.com/s?wd=%E4%BB%8A%E6%97%A5%E6%96%B0%E9%B2%9C%E4%BA%8B&tn=SE_Pclogo_6ysd4c7a&sa=ire_dl_gh_logo&rsv_dl=igh_logo_pc"
        }




    }

