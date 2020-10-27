import QtQuick 2.0
import QtQuick.Layouts 1.3


Item
{
    id: root
    width: parent.width
    height: parent.height

    property string preview: ""
    property string serviceText: ""

    signal triggered

    Image
    {
        id: pImage
        anchors.fill: parent
        source: preview
        sourceSize: Qt.size(pImage.width, pImage.height)
    }

    Text {
        text: qsTr(serviceText)
        anchors.centerIn: parent
        color: "White"
        font.pointSize: 64
    }

    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            triggered()
        }
    }

}
