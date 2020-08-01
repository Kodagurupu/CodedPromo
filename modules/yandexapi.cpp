#include "yandexapi.h"

YandexApi::YandexApi(QString server, QString session)
{
    qInfo() << "[YANDEX_API] init";
    service.initService(thread, server, session);
    service.moveToThread(&thread);
    thread.start();
    connect(&service, &Service::dataRecived, this, &YandexApi::getTheadData);
}

YandexApi::~YandexApi()
{
    thread.quit();
    thread.wait();
}

Request YandexApi::unparseJson(QJsonObject data)
{
    Request request;
    QJsonObject currentMeta = data["meta"].toObject();

    Meta metaData;
    metaData.locale = currentMeta["locale"].toString();
    metaData.timezone = currentMeta["timezone"].toString();
    metaData.client_id = currentMeta["client_id"].toString();

    QJsonObject currentInterfaces = currentMeta["interfaces"].toObject();
    Interfaces interfaces;
    interfaces.screen = currentInterfaces["screen"].toObject();
    interfaces.payments = currentInterfaces["payments"].toObject();
    interfaces.acountLinking = currentInterfaces["account_linking"].toObject();
    metaData.interfaces = interfaces;
    request.Meta = metaData;

    QJsonObject currentSession = data["session"].toObject();
    Session session;
    session.message_id = currentSession["message_id"].toInt();
    session.session_id = currentSession["session_id"].toString();
    session.skill_id = currentSession["skill_id"].toString();

    QJsonObject currentUser = currentSession["user"].toObject();
    User user;
    user.user_id = currentUser["user_id"].toString();
    session.user = user;

    QJsonObject currentApplication = currentSession["application"].toObject();
    Application application;
    application.application_id = currentApplication["application_id"].toString();
    session.application = application;

    session.user_id = currentSession["user_id"].toString();
    session._new = currentSession["new"].toBool();
    request.session = session;

    QJsonObject currentRequest = data["request"].toObject();
    _Request _request;
    _request.command = currentRequest["command"].toString();
    _request.original_utterance = currentRequest["original_utterance"].toString();

    QJsonObject currentNlu = currentRequest["nlu"].toObject();
    Nlu nlu;
    nlu.tokens = currentNlu["tokens"].toArray();
    nlu.entities = currentNlu["entities"].toArray();
    nlu.intents = currentNlu["intents"].toObject();
    _request.nlu = nlu;

    QJsonObject currentMarkup = currentRequest["markup"].toObject();
    Markup markup;
    markup.dangerous_context = currentMarkup["dangerous_context"].toBool();
    _request.markup = markup;
    _request.type = currentRequest["type"].toString();
    request.request = _request;

    request.version = data["version"].toString();

    return  request;
}

void YandexApi::getTheadData(QJsonObject data)
{
    qDebug() << "[YANDEX_SERVICE] Got new data";
    Request converted = unparseJson(data);
    if (lastRequest.session.message_id == converted.session.message_id)
        return;
    lastRequest = converted;
    emit newData(lastRequest);
}

Request YandexApi::getRequest()
{
    return lastRequest;
}

Service::Service(QObject *parent) : QObject(parent){ }

void Service::initService(QThread &thread, QString server, QString session)
{
    qDebug() << "[YANDEX_SERVICE] init";
    serviceURL = server;
    sessionID = session;
    connect(&thread, &QThread::started, this, &Service::runService);
}

void Service::runService()
{
    net = new Network();
    QEventLoop loop;
    int counter = 0;
    while (true)
    {
        bool state = net->get(serviceURL + "/" + sessionID + "/responce.json");
        if (state)
            connect(net, &Network::recived, &loop, &QEventLoop::quit);
        else
        {
            qDebug("[YANDEX_SERVICE] internet error");
            return;
        }
        loop.exec();

        QJsonObject jsonData = QJsonDocument::fromJson(net->getRecived().toUtf8()).object();
        emit dataRecived(jsonData);

        counter++;
        if (counter != 0)
            QThread::sleep(1);
    }
}
