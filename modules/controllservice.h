#ifndef CONTROLLSERVICE_H
#define CONTROLLSERVICE_H

#include <QObject>

#include "arduino.h"
#include "yandexapi.h"
#include "../sources/private.h"
#include "messageservice.h"

class ControllService : public QObject
{
    Q_OBJECT
    Q_ENUM(Commands)

public:
    explicit ControllService(QObject *parent = nullptr);
    Q_INVOKABLE void toggleAutoMode(bool);

public slots:
    void sendToArduino(Request);

private:
    bool autoMovement;
    Arduino arduino;
    YandexApi *yandex;
    Private privateData;
    MessageService service;

signals:
    void reciveArduinoCommand(Commands);
};

#endif // CONTROLLSERVICE_H
