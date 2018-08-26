import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.2

Window {

    width: 600
    height: 400

    minimumHeight: 380
    minimumWidth: 480

    color: "#121212"

    BusyIndicator {
        id: busy
        running: true
        anchors.centerIn: parent
        z: 2

    }

    Text {
        id: stateLabel
        visible:  false
        anchors.centerIn: parent
        z: 3

    }

    Image {
        id: imageViewer
        asynchronous: true
        cache: false
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit

        onStatusChanged: {
                    if (imageViewer.status === Image.Loading) {
                        busy.running = true;
                        stateLabel.visible = false;
                    }
                    else if(imageViewer.status === Image.Ready){
                        busy.running = false;
                    }
                    else if(imageViewer.status === Image.Error){
                        busy.running = false;
                        stateLabel.visible = true;
                        stateLabel.text = "ERROR";
                    }
                }
        Component.onCompleted: {
            imageViewer.source = "http://img.zcool.cn/community/0117e2571b8b246ac72538120dd8a4.jpg@1280w_1l_2o_100sh.jpg"
        }
    }

    Button {
        id: openFile
        text: "Open"
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        style: ButtonStyle {
            background: Rectangle {
                            implicitHeight: 70
                            implicitWidth: 25
                            color: control.hovered ? "#c0c0c0" : "#a0a0a0"
                            border.width: control.pressed ? 2: 1
                            border.color: (control.pressed || control.hovered) ? "green" : "#888888"

                        }


        }
       onClicked: filedialog.open()
    }

    Text {
        id: iamgePath
        anchors.left: openFile.right
        anchors.leftMargin: 8
        anchors.verticalCenter:  openFile.verticalCenter
        font.pixelSize: 18

    }

    FileDialog {
        id: filedialog
        title: "Please choose a file"
        nameFilters: ["image Files (*.jpg *.png *.gif)"]

        onAccepted: {
            imageViewer.source = filedialog.fileUrl;
            var iamgeFile = new String(filedialog.fileUrl);
            imagePath.text = imageFile.slice(8);

        }
    }
}
