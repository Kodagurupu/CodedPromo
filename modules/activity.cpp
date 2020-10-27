#include "activity.h"

Activity::Activity(QObject *parent) : QObject(parent)
{
    presentation = new Presentation();
    connect(this, &Activity::sendResponce, presentation, &Presentation::sendResponce);
    connect(presentation, &Presentation::sendText, this, &Activity::rText);
    connect(presentation, &Presentation::sendCommand, this, &Activity::rCommand);
    connect(presentation, &Presentation::ended, this, &Activity::resetThread);
}

void Activity::resetThread()
{
    presentation = new Presentation();
    thread.quit();
    thread.wait();
}

void Activity::showPresentation(QString file)
{
    if (!presentation->getStatus())
    {
        presentation->configure(thread, file);
        presentation->moveToThread(&thread);
        thread.start();
    }
    else return;
}

void Activity::rText(QString text) { emit sendText(text); }
void Activity::rCommand(QString command) { emit sendCommand(command); }

Presentation::Presentation( QObject *parent ) : QObject(parent), active( false )
{
    connect(this, &Presentation::ended, this, &Presentation::endWork);
}

void Presentation::endWork()
{
    active = false;
}

void Presentation::configure(QThread &thread, QString filename)
{
    currentFile = filename;
    connect(&thread, &QThread::started, this, &Presentation::working);
}

void Presentation::working()
{
    active = true;
    getContent();
    QEventLoop loop;
    if (!lastTask.empty())
    {
        QJsonArray actions = lastTask["actions"].toArray();
        for (int i = 0; i < actions.count(); i++ )
        {
            QJsonObject currentAction = actions.at(i).toObject();

            QString type = currentAction["action"].toString();
            QString data = currentAction["body"].toString();
            int delay = currentAction["delay"].toInt(); // ms

            Actions action = getAction(type);

            if (action == Read) emit sendText(data);
            if (action == Move) emit sendCommand(data);

            QThread::currentThread()->msleep(delay);

            if (action == Move) emit sendCommand("stop");

            connect(this, &Presentation::reciveResonce, &loop, &QEventLoop::quit);
            loop.exec();
        }
        active = false;
        emit ended();
    } else
    {
        active = false;
        emit ended();
    }
}

void Presentation::getContent()
{
    QFile file(currentFile);
    QString fileContent;
    if ( !file.open(QIODevice::ReadOnly) ) return;

    fileContent = file.readAll();
    lastTask = QJsonDocument::fromJson(fileContent.toUtf8()).object();
}

Actions Presentation::getAction(QString data)
{
    if (data == "read"  || data == "Read")   return Read;
    if (data == "move"  || data == "Move")   return Move;
    if (data == "image" || data == "Image")  return Image;
    return None;
}

bool Presentation::getStatus()
{
    return active;
}

void Presentation::sendResponce() { emit reciveResonce(); }
void Activity::reciveResponse() { emit sendResponce(); }
