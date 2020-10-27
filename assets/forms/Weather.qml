import QtQuick 2.0
import QtQuick.Layouts 1.3
import WeatherCore 0.1

Item
{
    id: root

    anchors.fill: parent

    Rectangle
    {
        id: background
        color: "#b3d1ff"

        anchors.fill: parent

        ColumnLayout
        {
            anchors.fill: parent
            anchors.margins: 10

            BackButton
            {
                onPressed:
                {
                    root.parent.switchFunc.page = "MainPage.qml"
                    root.parent.switchFunc.start()
                }
            }

            RowLayout
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Image
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    source: "qrc:/assets/images/weather/" + weather.weather["icon"]
                }

                Rectangle
                {
                    color: "white"
                    width: 3
                    Layout.fillHeight: true
                }

                ColumnLayout
                {
                    Layout.fillHeight:  true
                    width: 300

                    Text
                    {
                        text: qsTr("Город: Simferopol")
                        color: "white"
                        font.pointSize: 42
                    }

                    Text
                    {
                        text: qsTr("Температура: " + weather.weather["temp"])
                        color: "white"
                        font.pointSize: 18
                    }

                    Text
                    {
                        text: qsTr("Погода: " + weather.weather["weather"])
                        color: "white"
                        font.pointSize: 18
                    }

                    Rectangle {Layout.fillHeight: true}
                }
            }
        }
    }

    WeatherCore
    {
        id: weather
    }

}
