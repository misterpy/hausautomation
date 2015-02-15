import QtQuick 2.3
import QtQuick.Controls 1.2


ApplicationWindow {
    visible: true
    width: 790
    height: 790
    color: "#3e4045"
    title: qsTr("Hausautomation GUI")

    menuBar: MenuBar {
        Menu {
            title: qsTr("Options")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Button {
        id: button1on
        x: 326
        y: 164
        width: 123
        height: 74
        text: qsTr("On")
        onClicked: {
            controlLogic.turnOn("0");
        }
    }

    Text {
        id: text1
        x: 154
        y: 26
        width: 287
        height: 45
        color: "#e4d7d7"
        text: qsTr("Hausautomation")
        styleColor: "#f9f9f9"
        font.bold: true
        font.pixelSize: 36
    }

    Text {
        id: text2
        x: 146
        y: 179
        width: 119
        height: 44
        color: "#999999"
        text: "Licht 1"
        font.pixelSize: 39
    }

    Text {
        id: text3
        x: 143
        y: 275
        width: 122
        height: 44
        color: "#999999"
        text: "Licht 2"
        font.pixelSize: 39
    }

    Button {
        id: button1off
        x: 531
        y: 164
        width: 123
        height: 74
        text: qsTr("Off")
        onClicked: {
            controlLogic.turnOff("0");
        }
    }

    Button {
        id: button2on
        x: 326
        y: 260
        width: 123
        height: 74
        text: qsTr("On")
        onClicked: {
            controlLogic.turnOn("1");
        }
    }

    Button {
        id: button2off
        x: 531
        y: 260
        width: 123
        height: 74
        text: qsTr("Off")
        onClicked: {
            controlLogic.turnOff("1");
        }
    }
}
