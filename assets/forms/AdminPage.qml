import QtQuick 2.0

Item
{
    id: root
    anchors.fill: parent

    property bool isActive: false

    Rectangle
    {
        anchors.fill: parent
        color: "#b3d1ff"
    }

    LeftPanel
    {

    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            logoutSwither.stop()
            isActive = true
            logoutSwither.start()
        }
    }

    Timer
    {
        id: logoutSwither
        interval: 5000
        running: true
        onTriggered:
        {
            isActive = false;
        }
    }

    Timer
    {
        interval: 6000
        repeat: true
        running: true
        onTriggered:
        {
            if (!isActive)
            {
                root.parent.switchFunc.page = "MainPage.qml"
                root.parent.switchFunc.start()
            }
        }
    }
}
