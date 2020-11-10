#ifndef CONTROLLDAEMON_H
#define CONTROLLDAEMON_H

#include <QObject>
#include <QThread>

#include "network.h"
#include "armscontroll.h"
#include "../sources/private.h"

class ControllDaemon : public QObject
{
    Q_OBJECT
signals:
    void startSpeak(QString);
    void moving(int);

public:
    explicit ControllDaemon(QObject *parent = nullptr);
    ~ControllDaemon();
    void initService(QThread &thread);

public slots:
    void run();

private:
    Network *net;
    Private srvData;
    armsControll arduino;
    QString lastCommand;
};

#endif // CONTROLLDAEMON_H
