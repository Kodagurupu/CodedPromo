#ifndef NETWORK_H
#define NETWORK_H

#include <QDebug>
#include <QObject>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "../sources/private.h"

class Network : public QObject
{
    Q_OBJECT

public slots:
    void reciveData();

signals:
    void recived(QString);

public:
    explicit Network();
    Q_INVOKABLE bool get(QString addr);
    Q_INVOKABLE bool post(QString addr, QVariant data);
    Q_INVOKABLE bool getState();
    Q_INVOKABLE QString getRecived();

private:
    Private privateData;
    bool haveConnection;
    QNetworkAccessManager *netMgr = new QNetworkAccessManager();
    QNetworkRequest netRequest;
    QNetworkReply *netReply;
    QString recivedData;
};

#endif // NETWORK_H
