#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../modules/network.h"
#include "../modules/yandexapi.h"
#include "../modules/messageservice.h"
#include "private.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/assets/forms/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    MessageService service;
    Private privateData;
    YandexApi yandex(privateData.serverAddr + "/" + privateData.workingDir, privateData.sessionID);
    QObject::connect(&yandex, &YandexApi::newData, &service, &MessageService::getData);

    return app.exec();
}
