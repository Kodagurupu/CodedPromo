import QtQuick 2.12
import QtQuick.Window 2.12

import ControllService 0.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Promorobot")

    Rectangle
    {
        anchors.fill: parent

        Rectangle
        {
            width: 250
            height: 100
            color: "purple"
            anchors.centerIn: parent

            Text {
                anchors.centerIn: parent
                text: "Провести презентацию"
                color: "white"
                font.pixelSize: 16
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    service.toggleAutoMode(true);
                    service.showPresentation("assets/presentation0/presentation0.json");
                }
            }
        }
    }

    ControllService
    {
        id: service
    }
}
