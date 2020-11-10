#ifndef CONTROLLSERVICE_H
#define CONTROLLSERVICE_H

#include <QObject>

#include "opencv.h"
//#include "arduino.h"
#include "activity.h"
#include "yandexapi.h"
//#include "wincontrols.h"
#include "controlldaemon.h"
#include "messageservice.h"
#include "../sources/private.h"

class ControllService : public QObject
{
    Q_OBJECT
    Q_ENUM(Commands)
    Q_PROPERTY(bool autoMove READ getMove WRITE setMove NOTIFY moveChanged)
    Q_PROPERTY(QJsonObject people READ getPeople NOTIFY peopleChanged)
    Q_PROPERTY(QString audio READ getAudio NOTIFY audioChanged)

signals:
    void endActivity();
    void reciveVideo(QString);
    void reciveArduinoCommand(Commands);
    void moveChanged(bool);
    void peopleChanged(QJsonObject);
    void audioChanged(QString);

public:
    explicit ControllService(QObject *parent = nullptr);
    //Q_INVOKABLE void sendText(QString);
    Q_INVOKABLE void toggleAutoMode(bool);
    Q_INVOKABLE void showPresentation(QString file);
    Q_INVOKABLE QString cimage;

    bool getMove();
    QString getAudio();
    QJsonObject getPeople();

    void setMove(bool);

public slots:
    void reciveToArduino(QString);
    void requestToArduino(Request);
    void reciveOpenCV(QJsonObject);
    void reciveAudio(QString);

private:
    bool autoMovement;
    QString audioFile;
    QJsonObject people;

    Camera externCam0;
    cvService externCam1;

    QThread camThread0;
    QThread camThread1;
    QThread daemonThread;

    //WinControls win;
    //Arduino arduino;
    Activity activity;
    YandexApi *yandex;
    Private privateData;
    ControllDaemon daemon;
    MessageService service;
};

#endif // CONTROLLSERVICE_H
