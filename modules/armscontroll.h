#ifndef ARMSCONTROLL_H
#define ARMSCONTROLL_H

#include <QDebug>
#include <QObject>
#include <QtSerialPort>

typedef enum {
    STOP = -1,
    HANDSHAKE,
    FREEDOM
} armCommands;

armCommands Parse(int);

class armsControll : public QObject
{
    Q_OBJECT
public:
    explicit armsControll(QObject *parent = nullptr);

public slots:
    void reciveCommand(int);

private:
    QSerialPort serial;
};

#endif // ARMSCONTROLL_H
