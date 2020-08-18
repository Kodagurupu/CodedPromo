//#define IS_OPENCV

#ifdef IS_OPENCV

#ifndef OPENCV_H
#define OPENCV_H

#include <QDebug>
#include <QThread>
#include <QObject>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

class cvService : public QObject
{
    Q_OBJECT
signals:

public:
    cvService(QObject *parent = nullptr);
    void initService(QThread &thread);

public slots:
    void worker();

private:
    Mat frame;
    VideoCapture cap;
    int deviceID;
    int apiID;
};

class OpenCV : public QObject
{
    Q_OBJECT
public:
    explicit OpenCV(QObject *parent = nullptr);

signals:


private:
    QThread thread;
    cvService service;
};

#endif // OPENCV_H

#endif
