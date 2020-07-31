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

bool Network::post(QString addr, QVariant data)
{
    if (!haveConnection)
    {
        qCritical() << "[NETWORK] Err: no internet connection";
        emit recived();
        return false;
    }
    QByteArray postData = data.toByteArray();
    netRequest.setUrl(addr);
    netReply = netMgr->post(netRequest, postData);
    QObject::connect(netReply, &QNetworkReply::finished, this, &Network::reciveData);
    return true;
}

bool Network::get(QString addr)
{
    if (!haveConnection)
    {
        qCritical() << "[NETWORK] Err: no internet connection";
        emit recived();
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
        emit recived();
        return;
    }
    recivedData = data;
    emit recived();
}

QString Network::getRecived()
{
    return recivedData;
}
