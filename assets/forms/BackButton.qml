import QtQuick 2.0

Item
{
    id: root
    width: 72
    height: 72

    anchors.top: parent.top
    anchors.left: parent.left

    signal pressed

    Image
    {
        anchors.fill: parent
        source: "qrc:/assets/images/back.svg"
        sourceSize: Qt.size(root.width, root.height)
    }

    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            root.pressed()
        }
    }

}
