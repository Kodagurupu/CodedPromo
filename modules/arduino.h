#ifndef ARDUINO_H
#define ARDUINO_H

#include <QThread>
#include <QObject>
#include <QtSerialPort>

enum Commands
{
    Nothing = -1,
    Forward = 0,
    Backward = 1,
    Left = 2,
    Right = 3,
    Stop = 4
};

struct RawCommands
{
public:
    QList<QString> enForward = {"Forward", "forward", "Go forward", "go forward"};
    QList<QString> ruForward = {"Вперед", "вперед", "Иди вперед", "иди вперед"};
    QList<QString> enBackward = {"Backward", "backward", "Back", "back", "Go back", "go back"};
    QList<QString> ruBackward = {"Назад", "назад", "Иди назад", "иди назад"};
    QList<QString> enLeft = {"Left", "left", "Go left", "go left", "Move left", "move left"};
    QList<QString> ruLeft = {"Влево", "влево", "Налево", "налево"};
    QList<QString> enRight = {"Right", "right", "Go right", "go right", "Move right", "move right"};
    QList<QString> ruRight = {"Вправо", "вправо", "Направо", "направо"};
    QList<QString> enStop = {"Stop", "stop"};
    QList<QString> ruStop = {"Стоп", "стоп"};
};

class ArduinoService : public QObject
{
    Q_OBJECT

signals:
    void connected();

public:
    ArduinoService(QObject *parent = nullptr);
    void initService(QThread &thread, QSerialPort &serial);
    void sendCommand(Commands command);

public slots:
    void worker();

private:
    QSerialPort *_serial;
    Commands lastCommand;
    Commands currentCommand;
};

class Arduino : public QObject
{
    Q_OBJECT

signals:
    void moving(int);

public:
    explicit Arduino(QObject *parent = nullptr);
    Commands getCommand( QString data );
    void move(Commands command);

private:
    QThread thread;
    QSerialPort serial;
    Commands lastCommand;
    ArduinoService service;
    bool in(QList<QString>, QVariant);
};

#endif // ARDUINO_H
