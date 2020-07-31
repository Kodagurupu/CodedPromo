#ifndef YANDEXAPI_H
#define YANDEXAPI_H

#include <QDebug>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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

class YandexApi
{
public:
    YandexApi();
    Request unparseJson(QJsonObject data);
};

#endif // YANDEXAPI_H
