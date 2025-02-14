import QtQuick

import TOL

Window {
    width: 640
    height: 400
    visible: true
    title: qsTr("Example Project")

    Column {
        width: parent.width
        height: parent.height

        Text {
            height: parent.height / 2
            width: parent.width
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
            text: "Test loading plugin library (should show a success string):\n\n" + TestElement.printMessage()
        }


        Text {
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            text: "Test loading plugin image provider (should show a blue image):\n"
        }

        Image {
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            sourceSize.height: 100
            sourceSize.width:  parent.width
            source: "image://testimage/blue";
        }
    }
}
