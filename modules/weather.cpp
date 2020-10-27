#include "weather.h"

Weather::Weather(QObject *parent) : QObject(parent)
{
    serviceLink= "http://api.openweathermap.org/data/2.5/weather?q=Simferopol&forecast?id=524901&APPID=";
    serviceKey = "dbe22402b44c53e77bb35dd2671fe6f7";
    net.get(serviceLink + serviceKey);
    connect(&net, &Network::recived, this, &Weather::reciveData);
}

QJsonObject Weather::getWeather()
{
    return currentWeather;
}

void Weather::reciveData(QString data)
{
    QJsonObject output;

    QJsonObject converted = QJsonDocument::fromJson(data.toUtf8()).object();

    output["temp"]    = (int) ((int) converted["main"].toObject()["temp"].toDouble()) - 273;
    output["weather"] = converted["weather"].toArray()[0].toObject()["main"].toString();

    if (output["weather"] == "Clouds")  output["icon"] = "clouds.jpg";
    if (output["weather"] == "Rain")    output["icon"] = "rain.jpg";
    if (output["weather"] == "Snow")    output["icon"] = "snow.jpg";
    if (output["weather"] == "Clear")   output["icon"] = "clear.jpg";

    currentWeather = output;

    emit weatherChanged(output);
}
