#include "questions.h"

Questions::Questions()
{
    db.setDatabaseName("bin/data.db");

    if (!db.open())
    {
        qCritical() << "[Database] Can't open database";
        return;
    }

    if (!db.contains(QLatin1String("Questions")))
    {
        qCritical() << "[Database] Invalid database";
        return;
    }

    db.close();
}

QJsonArray Questions::get()
{
    QJsonArray output;

    if (!db.open())
    {
        qCritical() << "[Database] can't open database for write data";
        return output;
    }

    QSqlQuery query;

    query.prepare("select * from Questions");

    if (!query.exec())
    {
        qCritical() << "[Database] Can't exec query";
        return output;
    }

    while(query.next())
    {
        QJsonObject temp;
        temp["id"] = query.value(0).toInt();
        temp["title"] = query.value(1).toString();
        temp["content"] = query.value(2).toString();
        temp["questions"] = query.value(3).toString();
        temp["v_up"] = query.value(4).toInt();
        temp["v_down"] = query.value(5).toInt();

        output.append(temp);
    }

    return output;
}

void Questions::update(QJsonObject data)
{
    if (!db.open())
    {
        qCritical() << "[Database] can't open database for update data";
        return;
    }

    QSqlQuery query;

    query.prepare("update Questions " \
                  "set title = :title" \
                  ", content = :content" \
                  ", questions = :questions" \
                  ", votes_up = :v_up" \
                  ", votes_down = :v_down");
    if (data.isEmpty())
    {
        qCritical() << "[Database] invalid input data";
        return;
    }

    if (!data["title"].isString())
    {
        qCritical() << "[Database] invalid input data";
        return;
    }

    if (!data["content"].isString())
    {
        qCritical() << "[Database] invalid input data";
        return;
    }

    if (!data["questions"].isString() || data["questions"].isUndefined())
    {
        qCritical() << "[Database] invalid input data";
        return;
    }

    if (!data["v_up"].isDouble() || data["votes_up"].isUndefined())
    {
        qCritical() << "[Database] invalid input data";
        return;
    }

    if (!data["v_down"].isDouble() || data["votes_down"].isUndefined())
    {
        qCritical() << "[Database] invalid input data";
        return;
    }

    query.bindValue(":title", data["tite"].toString());
    query.bindValue("content", data["content"].toString());
    query.bindValue("questions", data["questions"].toString());
    query.bindValue(":v_up", data["v_up"].toInt());
    query.bindValue("v_down", data["v_down"].toInt());

    if (!query.exec())
    {
        qCritical() << "[Database] can't update data";
        return;
    }

    db.close();
}
