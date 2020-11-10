#include "controlldaemon.h"

ControllDaemon::ControllDaemon(QObject *parent) : QObject(parent)
{
    qInfo() << "[DAEMON] Started";
    connect(this, &ControllDaemon::moving, &arduino, &armsControll::reciveCommand);
}

ControllDaemon::~ControllDaemon()
{
    QThread::currentThread()->quit();
    delete net;
}

void ControllDaemon::initService(QThread &thread)
{
    connect(&thread, &QThread::started, this, &ControllDaemon::run);
}

void ControllDaemon::run()
{
    QEventLoop loop;
    net = new Network;
    while (true)
    {
        bool state = net->get(srvData.serverAddr + "/" + srvData.workingDir + "/" + srvData.sessionID + "/robot.txt");
        if (state)
            connect(net, &Network::recived, &loop, &QEventLoop::quit);
        else
        {
            qDebug("[YANDEX_SERVICE] internet error");
            return;
        }
        loop.exec();

        if (lastCommand == net->getRecived())
            continue;

        lastCommand = net->getRecived();

        qInfo() << "[DAEMON] Recived" << net->getRecived();

        QList<QString> args = net->getRecived().split(" ");
        QList<QString> argv = args[1].split("\n");

        if (args[0] == "play")
        {
            emit startSpeak(argv[0]);
        }

        if (args[0] == "move")
        {
            emit moving(Parse(argv[0].toInt()));
        }

        QThread::currentThread()->msleep(500);
    }
}
