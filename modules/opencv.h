#ifndef OPENCV_H
#define OPENCV_H

#include <vector>

#include <QDebug>
#include <QThread>
#include <QObject>
#include <QJsonObject>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class cvService : public QObject
{
    Q_OBJECT
signals:
    void foundPeople (QJsonObject);

public:
    cvService(QObject *parent = nullptr);
    ~cvService();
    void initService(QThread &thread);
    void findObjects();

public slots:
    void worker();

private:
    Mat frame;
    VideoCapture cap;
    int deviceID;
    int apiID;
    CascadeClassifier cascade;
};

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(QObject *parent = nullptr);
    ~Camera();
    void initService(QThread &thread);

public slots:
    void run();

private:
    Mat frame;
    VideoCapture cap;
    int deviceID;
    int apiID;
};

#endif
