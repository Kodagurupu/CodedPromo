import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

import Questions 0.1

Item
{
    id: root
    anchors.fill: parent

    property var allQuestions: core.get()
    property var randQuestion: getRandom()

    function getRandom()
    {
        return allQuestions[ Math.floor( Math.random() * allQuestions.length() - 1 ) ]
    }

    Core
    {
        id: questions
    }

    Rectangle
    {
        anchors.fill: parent

        color: "#b3d1ff"

        ColumnLayout
        {
            anchors.fill: parent
            anchors.margins: 10

            RowLayout
            {
                Layout.fillWidth: true

                BackButton
                {
                    onPressed:
                    {
                        root.parent.switchFunc.page = "MainPage.qml"
                        root.parent.switchFunc.start()
                    }
                }

                Rectangle {Layout.fillWidth: true}

                Image
                {
                    id: adminLoader

                    width: 52
                    height: 52

                    source: "qrc:/assets/images/account_circle-white.svg"
                    sourceSize: Qt.size(adminLoader.width, adminLoader.height)

                    anchors.top: parent.top
                    anchors.right: parent.right

                    anchors.rightMargin: 5
                    anchors.topMargin: 5

                    MouseArea
                    {
                        anchors.fill: parent

                        onClicked:
                        {
                            root.parent.switchFunc.page = "AuthPage.qml"
                            root.parent.switchFunc.start()
                        }
                    }
                }
            }

            ColumnLayout
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text
                {
                    text: randQuestion["title"]
                    color: "white"
                    font.pointSize: 48
                }

                Text
                {
                    Layout.fillWidth: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: randQuestion["content"]
                    color: Qt.rgba(0,0,0,0.8)
                    font.pointSize: 16
                }

                Rectangle
                {
                    Layout.fillHeight: true
                }

                ListView
                {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    model: parse(randQuestion["questons"])

                    function parse(data)
                    {
                        var output = []
                        output = data.split(";")
                        return output
                    }

                    delegate: RadioButton
                    {
                        text: modelData
                    }
                }

                Rectangle
                {
                    Layout.fillHeight: true
                }

                Button
                {
                    text: "Готово"
                    height: 64
                    Layout.fillWidth: true
                    highlighted: true
                }

            }

        }
    }

}
