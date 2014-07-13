#ifndef KINECTCONTROLLER_H
#define KINECTCONTROLLER_H
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <NiTE.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>

using namespace std;
using namespace cv;

class KinectController
{
public:
    KinectController();

    void init();

    void run();

private:
    openni::Device              device;
    openni::VideoStream         color;
    openni::VideoStream         depth;
    openni::VideoFrameRef       colorFrame;
    openni::VideoFrameRef       depthFrame;
    Mat                         cFrame;
//    Mat                         dFrame;

    nite::HandTracker           pHandTracker;
    nite::HandTrackerFrameRef   handFrame;

    bool                        isReady;


};

#endif // KINECTCONTROLLER_H
