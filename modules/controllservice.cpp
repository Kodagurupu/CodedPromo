#include "controllservice.h"

ControllService::ControllService(QObject *parent)
    : QObject(parent)
{
    qInfo() << "[MAIN_SERVICE] init";
    autoMovement = false;
    yandex = new YandexApi(privateData.serverAddr + "/" + privateData.workingDir, privateData.sessionID);
    connect(this, &ControllService::reciveArduinoCommand, &arduino, &Arduino::move);
    connect(yandex, &YandexApi::newData, this, &ControllService::requestToArduino);
    connect(yandex, &YandexApi::newData, &service, &MessageService::getData);
    connect(&activity, &Activity::sendCommand, this, &ControllService::reciveToArduino);
    //connect(&activity, &Activity::sendText, this, &ControllService::sendText);
    connect(this, &ControllService::endActivity, &activity, &Activity::reciveResponse);
    connect(&externCam1, &cvService::foundPeople, this, &ControllService::reciveOpenCV);

    externCam0.initService(camThread0);
    externCam1.initService(camThread1);

    externCam0.moveToThread(&camThread0);
    externCam1.moveToThread(&camThread1);

    camThread0.start();
    camThread1.start();
}
/*
void ControllService::sendText(QString command)
{
    win.swipeWindow();
    QThread::currentThread()->msleep(500);
    win.sendMPos(645, 315);
    QThread::currentThread()->msleep(500);
    win.sendMPos(288, 337);
    QThread::currentThread()->msleep(500);
    win.sendKeys(command);
    win.sendMPos(122, 419);
    QThread::currentThread()->msleep(200 * command.count());
    win.swipeWindow();
    QThread::currentThread()->msleep(1000);
    emit endActivity();
}
*/
void ControllService::reciveToArduino(QString data)
{
    Commands command = arduino.getCommand(data);
    emit reciveArduinoCommand(command);
    emit endActivity();
}

void ControllService::showPresentation(QString file)
{
    activity.showPresentation(file);
}

void ControllService::requestToArduino(Request data)
{
    reciveToArduino(data.request.command);
}

void ControllService::toggleAutoMode(bool param)
{
    if (param == autoMovement)
        return;
    autoMovement = param;
}

bool ControllService::getMove()
{
    return autoMovement;
}

QJsonObject ControllService::getPeople()
{
    return people;
}

void ControllService::setMove(bool data)
{
    if (autoMovement == data) return;
    autoMovement = data;
    emit moveChanged(data);
}

void ControllService::reciveOpenCV(QJsonObject data)
{
    if (data["count"] == people["count"]) return;
    people = data;
    emit peopleChanged(data);
}
