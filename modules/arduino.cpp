#include "arduino.h"

Arduino::Arduino(QObject *parent)
    : QObject(parent)
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

Commands Arduino::getCommand( QString data )
{
    RawCommands commands;
    if ( in(commands.enForward, data) ) return Forward;
    if ( in(commands.ruForward, data) ) return Forward;
    if ( in(commands.enBackward, data) ) return Backward;
    if ( in(commands.ruBackward, data) ) return Backward;
    if ( in(commands.enRight, data) ) return Right;
    if ( in(commands.ruRight, data) ) return Right;
    if ( in(commands.enLeft, data) ) return Left;
    if ( in(commands.ruLeft, data) ) return Left;
    if ( in(commands.enStop, data) ) return Stop;
    if ( in(commands.ruStop, data) ) return Stop;
    return Nothing;
}

void Arduino::move(Commands command)
{
    lastCommand = command;
    qInfo() << "[ARDUINO_SERVICE] sending to COM: " + QString::number(command);
    if (serial.isOpen() && serial.isWritable())
    {
        QByteArray data = QString::number(command).toUtf8();
        serial.write(data);
    }
}

bool Arduino::in(QList<QString> list, QVariant value)
{
    foreach( QVariant item, list )
        if (item == value) return true;
    return false;
}
