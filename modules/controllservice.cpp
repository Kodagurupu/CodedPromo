#include "controllservice.h"

ControllService::ControllService(QObject *parent)
    : QObject(parent)
{
    qInfo() << "[MAIN_SERVICE] init";
    autoMovement = false;
    yandex = new YandexApi(privateData.serverAddr + "/" + privateData.workingDir, privateData.sessionID);
    connect(this, &ControllService::reciveArduinoCommand, &arduino, &Arduino::move);
    connect(yandex, &YandexApi::newData, this, &ControllService::sendToArduino);
    QObject::connect(yandex, &YandexApi::newData, &service, &MessageService::getData);
}

void ControllService::sendToArduino(Request data)
{
    if (autoMovement)
    {
        Commands command = arduino.getCommand(data.request.command);
        emit reciveArduinoCommand(command);
    }
}

void ControllService::toggleAutoMode(bool param)
{
    if (param == autoMovement)
        return;
    autoMovement = param;
}
