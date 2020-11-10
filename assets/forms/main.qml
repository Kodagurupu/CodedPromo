import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtMultimedia 5.9

import ControllService 0.3

Window
{
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Promorobot")

    Material.theme: Material.Light
    Material.accent: Material.Indigo

    flags: Qt.FramelessWindowHint
    property bool active: false

    Audio
    {
        id: sound
    }

    ControllService
    {
        id: controllService
        autoMove: true

        onPeopleChanged:
        {
            if (people["count"] >= 1)
            {
                active = true
                exitDelay.stop()
                blackScreen.visible = false
            } else
            {
                exitDelay.start()
            }
        }

        onAudioChanged:
        {
            if (controllService.audio.includes("assets/-1.mp3"))
            {
                sound.stop()
                return
            }

            if (controllService.audio.includes("assets/pause.mp3"))
            {
                sound.pause()
                return
            }

            sound.source = controllService.audio
            sound.play()
        }
    }

    Timer
    {
        id: exitDelay

        interval: 3500
        repeat: false

        onTriggered: blackScreen.visible = true
    }

    Rectangle
    {
        anchors.fill: parent
        visible: pageLoader.loaded ? false : true
        color: "white"

        BusyIndicator
        {
            width: 42
            height: 42
            anchors.centerIn: parent
        }
    }

    Loader
    {
        id: pageLoader
        anchors.fill: parent
        source: "MainPage.qml"
        asynchronous: true
        visible: false

        property var switchFunc: switchFunction

        onLoaded:
        {
            pageLoader.visible = true
        }
        onSourceChanged:
        {
            pageLoader.visible = false
        }
    }

    Timer
    {
        id: switchFunction
        interval: 0

        property string page: "MainPage.qml"

        onTriggered: pageLoader.source = page
    }

    Rectangle
    {
        id: blackScreen

        anchors.fill: parent
        color: "black"
    }
}
