#include "arduino.h"

Arduino::Arduino(QObject *parent)
    : QObject(parent)
{
    qInfo() << "[ARDUINO] init";
    qInfo() << "[ARDUINO] openPort";
    serial.setPortName("COM8");
    service.initService(thread, serial);
    service.moveToThread(&thread);
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
    service.sendCommand(command);
}

bool Arduino::in(QList<QString> list, QVariant value)
{
    foreach( QVariant item, list )
        if (item == value) return true;
    return false;
}

ArduinoService::ArduinoService(QObject *parent)
    : QObject(parent)
{
    qInfo() << "[ARDUINO_SERVICE] Init service";
}

void ArduinoService::initService(QThread &thread, QSerialPort &serial)
{
    _serial = &serial;
    connect(&thread, &QThread::started, this, &ArduinoService::worker);
}

void ArduinoService::worker()
{
    while (true)
    {
        QThread::currentThread()->msleep(100);
    }
}


void ArduinoService::sendCommand(Commands command)
{
    qInfo() << "[ARDUINO_SERVICE] sending to COM: " + QString::number(command);
    if (_serial->isOpen() && _serial->isWritable())
    {
        QByteArray data = QString::number(command).toUtf8();
        _serial->write(data);
    }
}
