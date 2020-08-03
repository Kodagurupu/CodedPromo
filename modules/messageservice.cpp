#include "messageservice.h"

MessageService::MessageService(QObject *parent) : QObject(parent)
{
    qInfo() << "[MESSAGES] init";
}

void MessageService::getData(Request data)
{
    qDebug() << "[MESSAGES]" << data.request.command;
}
