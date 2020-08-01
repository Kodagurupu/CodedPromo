#include "messageservice.h"

MessageService::MessageService(QObject *parent) : QObject(parent)
{

}

void MessageService::getData(Request data)
{
    qDebug() << data.request.command;
}
