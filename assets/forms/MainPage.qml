import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

Item
{
    id: root
    anchors.fill: parent

    Rectangle
    {
        id: background
        color: "#b3d1ff"
        anchors.fill: parent

        GridView
        {
            anchors.fill: parent
            anchors.margins: 10

            cellHeight: 605
            cellWidth: root.width / 2 - 10

            model: [
                {"preview" : "qrc:/assets/images/opros.jpg"},
                {"preview" : "qrc:/assets/images/i.jpg"},
                {"preview" : "qrc:/assets/images/ma2.png"},
                {"preview" : "qrc:/assets/images/maxresdefault.jpg"},
                {"preview" : "qrc:/assets/images/1592031847_tass_38188666.jpg"},
            ]

            delegate: Service
            {
                width: root.width / 2 - 15
                height: 600

                preview: modelData["preview"]
                serviceText: ""

                onTriggered:
                {
                    if (index == 0)
                    {
                        root.parent.switchFunc.page = "Questions.qml"
                        root.parent.switchFunc.start()
                    } else if (index == 1)
                    {
                        root.parent.switchFunc.page = "Weather.qml"
                        root.parent.switchFunc.start()
                    }


                }
            }

        }

    }

}
