#include "network.h"

Network::Network()
{
    qInfo() << "[NETWORK] init";
    haveConnection = getState();
}

bool Network::getState()
{
    QEventLoop loop;
    netRequest.setUrl(QUrl(privateData.serverAddr));
    netReply = netMgr->get(netRequest);
    netMgr->connect(netReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (netReply->readAll() == "")
        return false;
    else
        return true;
}

bool Network::post(QString addr, QJsonObject data)
{
    if (!haveConnection)
    {
        qCritical() << "[NETWORK] Err: no internet connection";
        emit recived("");
        return false;
    }
    QJsonDocument jsonDoc (data);
    QByteArray postData = jsonDoc.toJson();
    netRequest.setUrl(addr);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    netReply = netMgr->post(netRequest, postData);
    QObject::connect(netReply, &QNetworkReply::finished, this, &Network::reciveData);
    return true;
}

bool Network::get(QString addr)
{
    if (!haveConnection)
    {
        qCritical() << "[NETWORK] Err: no internet connection";
        emit recived("");
        return false;
    }
    netRequest.setUrl(addr);
    netReply = netMgr->get(netRequest);
    netMgr->connect(netReply, &QNetworkReply::finished, this, &Network::reciveData);
    return true;
}

void Network::reciveData()
{
    QString data = netReply->readAll();
    if (data == recivedData)
    {
        emit recived(data);
        return;
    }
    recivedData = data;
    emit recived(data);
}

QString Network::getRecived()
{
    return recivedData;
}
