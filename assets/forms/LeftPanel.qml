import QtQuick 2.0

Item
{
    width: 150
    height: parent.height

    Rectangle
    {
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0.1)

        ListView
        {
            anchors.fill: parent
            spacing: 6

            model: [
                { "image" : "", "text" : "Voice" },
                { "image" : "", "text" : "" },
                { "image" : "", "text" : "" },
                { "image" : "", "text" : "" },
                { "image" : "", "text" : "Settings" }
            ]

            delegate: Rectangle
            {
                width: parent.width
                height: 62
                color: Qt.rgba(0,0,0,0.1)

                Text {
                    anchors.centerIn: parent
                    text: modelData["text"]
                    color: "white"
                }
            }
        }
    }

}
