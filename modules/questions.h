#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <QtSql>
#include <QDebug>

#include <QJsonArray>
#include <QJsonObject>

class Questions : public QObject
{
    Q_OBJECT
public:
    explicit Questions();
    Q_INVOKABLE QJsonArray get();
    Q_INVOKABLE void update(QJsonObject);

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
};

#endif // QUESTIONS_H
