#include "opencv.h"
#ifdef IS_OPENCV

OpenCV::OpenCV(QObject *parent) : QObject(parent)
{
    service.initService(thread);
    service.moveToThread(&thread);
}

cvService::cvService(QObject *parent)
    : QObject(parent)
{
    deviceID = 0;
    apiID = CAP_ANY;
}

void cvService::worker()
{
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) {
        qCritical() << "[OPENCV] Can't open camera";
        return;
    }
    while (true)
    {
        cap.read(frame);
        if (frame.empty()) {
            qCritical() << "[OPENCV] Error reading from camera";
            break;
        }
        imshow("Video", frame);
        if (waitKey(5) >= 0)
            break;
    }
}

void cvService::initService(QThread &thread)
{
    connect(&thread, &QThread::started, this, &cvService::worker);
}
#endif
