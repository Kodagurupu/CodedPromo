#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../modules/weather.h"
#include "../modules/controllservice.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Weather>("WeatherCore", 0, 1, "WeatherCore");
    qmlRegisterType<ControllService>("ControllService", 0, 3, "ControllService");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/assets/forms/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
