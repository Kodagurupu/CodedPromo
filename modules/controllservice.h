#ifndef CONTROLLSERVICE_H
#define CONTROLLSERVICE_H

#include <QObject>

#include "opencv.h"
#include "arduino.h"
#include "activity.h"
#include "yandexapi.h"
//#include "wincontrols.h"
#include "messageservice.h"
#include "../sources/private.h"

class ControllService : public QObject
{
    Q_OBJECT
    Q_ENUM(Commands)
    Q_PROPERTY(bool autoMove READ getMove WRITE setMove NOTIFY moveChanged)
    Q_PROPERTY(QJsonObject people READ getPeople NOTIFY peopleChanged)

signals:
    void endActivity();
    void reciveVideo(QString);
    void reciveArduinoCommand(Commands);
    void moveChanged(bool);
    void peopleChanged(QJsonObject);

public:
    explicit ControllService(QObject *parent = nullptr);
    //Q_INVOKABLE void sendText(QString);
    Q_INVOKABLE void toggleAutoMode(bool);
    Q_INVOKABLE void showPresentation(QString file);
    Q_INVOKABLE QString cimage;

    bool getMove();
    QJsonObject getPeople();

    void setMove(bool);

public slots:
    void reciveToArduino(QString);
    void requestToArduino(Request);
    void reciveOpenCV(QJsonObject);

private:
    bool autoMovement;
    QJsonObject people;

    Camera externCam0;
    cvService externCam1;

    QThread camThread0;
    QThread camThread1;

    //WinControls win;
    Arduino arduino;
    Activity activity;
    YandexApi *yandex;
    Private privateData;
    MessageService service;
};

#endif // CONTROLLSERVICE_H
