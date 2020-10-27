#include "wincontrols.h"

WinControls::WinControls(QObject *parent) : QObject(parent)
{

}

void WinControls::sendMPos(int x, int y)
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    ::Sleep(200);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

    QThread::currentThread()->msleep(500);
}

void WinControls::sendKeys(QString keys)
{
    int arrSize = keys.length();
    INPUT ip;
    ::Sleep(1000);

    for (int i = 0; i < arrSize; i++)
    {
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        byte x = VkKeyScan(keys.at(i).unicode());
        ip.ki.wVk = x;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
    QThread::currentThread()->msleep(2000);
}

void WinControls::swipeWindow()
{
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_TAB, 0, 0, 0);

    Sleep(100);

    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);

    QThread::currentThread()->msleep(500);
}

void WinControls::sendEnter()
{
    keybd_event(VK_RETURN, 0, 0, 0);
    Sleep(100);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    QThread::currentThread()->msleep(500);
}

void WinControls::sendTab()
{
    keybd_event(VK_TAB, 0, 0, 0);
    Sleep(100);
    keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
    QThread::currentThread()->msleep(500);
}
