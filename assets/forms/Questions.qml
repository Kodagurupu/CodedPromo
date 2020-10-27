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
                    text: qsTr("Заголовок Опроса")
                    color: "white"
                    font.pointSize: 48
                }

                Text
                {
                    Layout.fillWidth: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: qsTr("Опрос — это выяснение мнения сообщества по тем или иным вопросам. По итогам опроса могут быть изменены или отменены существующие либо приняты новые правила и руководства (за исключением противоречащих общим принципам проекта).

        Организатором опроса может быть любой участник Википедии (в том числе анонимный). Если в опросе высказалось значительное количество участников, а итог опроса не оспаривается в течение разумного срока, можно считать консенсус достигнутым.

        Создание

        Перед созданием опроса обязательно обсудите с другими участниками необходимость опроса, возможно, вы можете получить ответ на форуме.

        Посмотрите, возможно, такой или похожий опрос уже проводился или проводится сейчас:")
                    color: Qt.rgba(0,0,0,0.8)
                    font.pointSize: 16
                }

                Rectangle
                {
                    Layout.fillHeight: true
                }

                CheckBox
                {
                    text: "Вы согласны с утверждением 1"
                }

                CheckBox
                {
                    text: "Вы согласны с утверждением 2"
                }

                CheckBox
                {
                    text: "Вы согласны с утверждением 3"
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
