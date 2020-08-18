#ifndef CONTROLLSERVICE_H
#define CONTROLLSERVICE_H

#include <QObject>

#include "opencv.h"
#include "arduino.h"
#include "activity.h"
#include "yandexapi.h"
#include "wincontrols.h"
#include "messageservice.h"
#include "../sources/private.h"

class ControllService : public QObject
{
    Q_OBJECT
    Q_ENUM(Commands)
signals:
    void endActivity();
    void reciveVideo(QString);

public:
    explicit ControllService(QObject *parent = nullptr);
    Q_INVOKABLE void sendText(QString);
    Q_INVOKABLE void toggleAutoMode(bool);
    Q_INVOKABLE void showPresentation(QString file);
    Q_INVOKABLE QString cimage;

public slots:
    void reciveToArduino(QString);
    void requestToArduino(Request);

private:
    bool autoMovement;
//    OpenCV opencv;
    WinControls win;
    Arduino arduino;
    Activity activity;
    YandexApi *yandex;
    Private privateData;
    MessageService service;

signals:
    void reciveArduinoCommand(Commands);
};

#endif // CONTROLLSERVICE_H
