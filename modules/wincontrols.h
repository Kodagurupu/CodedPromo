#ifndef WINCONTROLS_H
#define WINCONTROLS_H

#ifdef WIN32

#define WINVER 0x0500

#include <QObject>
#include <QThread>
#include <windows.h>

class WinControls : public QObject
{
    Q_OBJECT
public:
    explicit WinControls(QObject *parent = nullptr);
    Q_INVOKABLE void sendEnter();
    Q_INVOKABLE void swipeWindow();
    Q_INVOKABLE void sendKeys(QString keys);

};

#endif

#endif // WINCONTROLS_H
