#include "opencv.h"

Camera::Camera(QObject *parent) : QObject(parent)
{
    deviceID = 2;
    apiID = CAP_ANY;
}

Camera::~Camera()
{
    QThread::currentThread()->exit();
    QThread::currentThread()->quit();
}

void Camera::initService(QThread &thread)
{
    connect(&thread, &QThread::started, this, &Camera::run);
}

void Camera::run()
{
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) {
        qCritical() << "[OPENCV] Can't open camera";
        return;
    }

    while(true)
    {
        cap.read(frame);
        if (frame.empty()) {
            qCritical() << "[OPENCV] Error reading from camera";
            break;
        }
        imshow("Live", frame);

        if (waitKey(5) >= 0) break;
    }
}

cvService::cvService(QObject *parent)
    : QObject(parent)
{
    deviceID = 1;
    apiID = CAP_ANY;

    char fileName[] = "objects/people.xml";
    if (!cascade.load(fileName))
    {
        qCritical() << "[OPENCV] Can't open cascade";
    }
}

cvService::~cvService()
{
    QThread::currentThread()->exit();
    QThread::currentThread()->quit();
}

void cvService::findObjects()
{
    Mat grey;
    int counter = 0;
    vector<Rect> faces;

    cvtColor(frame, grey, COLOR_BGR2GRAY);
    cascade.detectMultiScale(grey, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    for (Rect face : faces)
    {
        Point center( face.x + face.width * 0.5, face.y + face.height * 0.5 );
        ellipse(
                    frame,
                    center,
                    Size(
                        face.width * 0.5,
                        face.height* 0.5),
                    0,
                    0,
                    360,
                    Scalar( 255, 0, 255 ),
                    4,
                    8,
                    0 );
        counter++;
    }

    QJsonObject output;
    output["count"] = counter;

    emit foundPeople(output);
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

        resize(frame, frame, Size(300, 250));
        findObjects();

        imshow("Video", frame);
        if (waitKey(5) >= 0)
            break;

        QThread::currentThread()->msleep(5);
    }
}


void cvService::initService(QThread &thread)
{
    connect(&thread, &QThread::started, this, &cvService::worker);
}
