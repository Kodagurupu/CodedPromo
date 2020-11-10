#include "armscontroll.h"

armCommands Parse(int command)
{
    if (command == -1) return STOP;
    if (command == 0)  return HANDSHAKE;
    if (command == 1)  return FREEDOM;

    return STOP;
}

armsControll::armsControll(QObject *parent) : QObject(parent)
{
    qInfo() << "[ARDUINO] init";
    qInfo() << "[ARDUINO] openPort";
    serial.setPortName("COM3");
    if (!serial.open(QIODevice::WriteOnly))
    {
        qInfo() << "[ARDUINO] Init Serial Port";
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
    } else
        qInfo() << "[ARDUINO] failed open port";
}

void armsControll::reciveCommand(armCommands command)
{
    qInfo() << "[ARDUINO_SERVICE] sending to COM: " + QString::number(command);
    if (serial.isOpen() && serial.isWritable())
    {
        QByteArray data = QString::number(command).toUtf8();
        serial.write(data);
    }
}
