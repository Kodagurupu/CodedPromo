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
    qInfo() << "[ARDUINO_ARMS] init";
    qInfo() << "[ARDUINO_ARMS] openPort";
    serial.setPortName("COM4");
    if (!serial.open(QIODevice::WriteOnly))
    {
        qInfo() << "[ARDUINO_ARMS] Init Serial Port";
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
    } else
        qInfo() << "[ARDUINO_ARMS] failed open port";
}

void armsControll::reciveCommand(int command)
{
    qInfo() << "[ARDUINO_SERVICE_ARMS] sending to COM: " + QString::number(command);
    if (serial.isOpen() && serial.isWritable())
    {
        QByteArray data = QString::number(command).toUtf8();
        serial.write(data);
    }
}
