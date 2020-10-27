import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

import QtGraphicalEffects 1.0

Item
{
    id: root
    anchors.fill: parent

    Rectangle
    {
        id: background
        color: "white"
        anchors.fill: parent

        Rectangle
        {
            id: panel
            width: 520
            height: parent.height / 2

            anchors.centerIn: parent
            color: "#00000000"

            ColumnLayout
            {
                id: authPanel
                anchors.fill: parent
                anchors.margins: 10
                opacity: 0
                spacing: 12

                Rectangle {Layout.fillHeight: true}

                RowLayout
                {
                    Layout.fillWidth: true

                    Rectangle
                    {
                        Layout.fillWidth: true
                    }

                    Image
                    {
                        id: accountIcon
                        width: 94
                        height: 94

                        source: "qrc:/assets/images/account_circle-white.svg"
                        sourceSize: Qt.size(accountIcon.width, accountIcon.height)
                    }

                    Text
                    {
                        text: "Admin"
                        color: "white"
                        font.pointSize: 48
                    }

                    Rectangle
                    {
                        Layout.fillWidth: true
                    }
                }

                Rectangle {height: 10}

                TextField
                {
                    Material.accent: Material.Indigo
                    Layout.fillWidth: true
                    height: 62
                    placeholderText: "Введите пароль администратора"
                    echoMode: TextField.Password
                }

                Button
                {
                    Layout.fillWidth: true
                    Material.accent: Material.Indigo
                    highlighted: true
                    width: 100
                    height: 62
                    text: "Login"

                    onClicked:
                    {
                        root.parent.switchFunc.page = "AdminPage.qml"
                        root.parent.switchFunc.start()
                    }
                }

                Rectangle {Layout.fillHeight: true}

                NumberAnimation on opacity
                {
                    id: showPanel
                    from: 0
                    to: 1
                    duration: 700
                    running: false
                }

                Timer
                {
                    interval: 600
                    running: true
                    onTriggered: showPanel.start()
                }
            }

        }

        BusyIndicator
        {
            width: 42
            height: 42
            anchors.centerIn: parent
            visible: showPanel.started ? false : true
        }

        ColorAnimation on color
        {
            id: startAnim
            from: "white"
            to: "#b3d1ff"
            duration: 600
            running: true
        }
    }
}
