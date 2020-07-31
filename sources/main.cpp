#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../modules/network.h"
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

    Network net;
    Private privateData;
    bool state = net.get(privateData.serverAddr);
    QEventLoop loop;
    if (state)
    {
        QObject::connect(&net, &Network::recived, &loop, &QEventLoop::quit);
        loop.exec();
        QString recivedData = net.getRecived();
        qDebug() << "Yee boi: " << recivedData;
    }

    return app.exec();
}
