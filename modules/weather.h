#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "network.h"

class Weather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject weather READ getWeather NOTIFY weatherChanged)

signals:
    void weatherChanged(QJsonObject);

public:
    explicit Weather(QObject *parent = nullptr);

public slots:
    void reciveData(QString);

private:
    Network net;
    QString serviceLink;
    QString serviceKey;

    QJsonObject currentWeather;
    QJsonObject getWeather();
};

#endif // WEATHER_H
