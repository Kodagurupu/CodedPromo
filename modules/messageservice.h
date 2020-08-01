#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <QDebug>
#include <QObject>
#include "yandexapi.h"

class MessageService : public QObject
{
    Q_OBJECT
public:
    explicit MessageService(QObject *parent = nullptr);

public slots:
    void getData(Request);

};

#endif // MESSAGESERVICE_H
