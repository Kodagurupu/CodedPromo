#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QFile>
#include <QObject>
#include <QThread>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "arduino.h"

enum Actions
{
    None = -1,
    Read = 0,
    Move = 1,
    Image = 2
};

class Presentation : public QObject
{
    Q_OBJECT
signals:
    void ended();
    void reciveResonce();
    void sendText(QString);
    void sendCommand(QString);

public:
    explicit Presentation(QObject *parent = nullptr);
    Q_INVOKABLE void configure(QThread &thread, QString filename);
    Q_INVOKABLE bool getStatus();

public slots:
    void working();
    void endWork();
    void sendResponce();

private:
    bool active;
    QString currentFile;
    QJsonObject lastTask;

    void getContent();
    Actions getAction(QString data);
};

class Activity : public QObject
{
    Q_OBJECT
signals:
    void sendText(QString);
    void sendCommand(QString);
    void sendResponce();

public:
    explicit Activity(QObject *parent = nullptr);
    Q_INVOKABLE void showPresentation(QString file);

public slots:
    void rText(QString text);
    void rCommand(QString command);
    void reciveResponse();

private:
    Presentation *presentation;
    QThread thread;

    void resetThread();
};

#endif // ACTIVITY_H
