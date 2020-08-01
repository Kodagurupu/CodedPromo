#ifndef YANDEXAPI_H
#define YANDEXAPI_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "network.h"

struct Interfaces
{
    QJsonObject screen;
    QJsonObject payments;
    QJsonObject acountLinking;
};

struct Meta
{
    QString locale;
    QString timezone;
    QString client_id;
    Interfaces interfaces;
};

struct User
{
    QString user_id;
};

struct Application
{
    QString application_id;
};

struct Session
{
    qint16 message_id;
    QString session_id;
    QString skill_id;
    User user;
    Application application;
    QString user_id;
    bool _new;
};

struct Nlu
{
    QJsonArray tokens;
    QJsonArray entities;
    QJsonObject intents;
};

struct Markup
{
    bool dangerous_context;
};

struct _Request
{
    QString command;
    QString original_utterance;
    Nlu nlu;
    Markup markup;
    QString type;
};

struct Request
{
    Meta Meta;
    Session session;
    _Request request;
    QString version;
};


class Service : public QObject
{
    Q_OBJECT

signals:
    void dataRecived(QJsonObject);

public:
    Service(QObject *parent = nullptr);
    void initService(QThread &thread, QString server, QString sessionID);

public slots:
    void runService();

private:
    Network *net;
    QString serviceURL;
    QString sessionID;
};


class YandexApi : public QObject
{
    Q_OBJECT
signals:
    void newData(Request);

public:
    YandexApi(QString server, QString sessionID);
    ~YandexApi();
    Request getRequest();

private:
    QThread thread;
    Service service;
    Request lastRequest;
    Request unparseJson(QJsonObject data);

public slots:
    void getTheadData(QJsonObject data);
};

#endif // YANDEXAPI_H
