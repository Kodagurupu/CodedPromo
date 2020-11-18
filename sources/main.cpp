#include <QCoreApplication>
#include <QtMultimedia/QMediaPlayer>

#include "../modules/network.h"
#include "../modules/controllservice.h"

int main(int argc, char *argv[])
{
    QMediaPlayer *player = new QMediaPlayer;
    QCoreApplication app(argc, argv);

    Network net;
    ControllService service;

    QObject reciver;

    QObject::connect(&service, &ControllService::peopleChanged, &reciver, [&net](QJsonObject people) {
        qDebug() << people;
        net.post("http://localhost:1080/sendPeople", people);
    });

    QObject::connect(&service, &ControllService::audioChanged, &reciver, [&player](QString file) {
       if ( file.split("-1.mp3").length() > 1 ) {
           return;
       }
       player->setMedia(QUrl::fromLocalFile(file));
       player->play();
    });

    return app.exec();
}
