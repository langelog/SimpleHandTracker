#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <NiTE.h>

using namespace std;
using namespace cv;

int main()
{
    Mat                         frame(Size(640,480), CV_8UC3);
    nite::HandTracker*          pHandTracker;
    nite::HandTrackerFrameRef   handFrame;
    nite::NiTE::initialize();
    pHandTracker = new nite::HandTracker;
    pHandTracker->create();

    pHandTracker->startGestureDetection(nite::GESTURE_HAND_RAISE);

    while(true) {
        nite::Status rc = pHandTracker->readFrame(&handFrame);
        const nite::Array<nite::GestureData>& gestures = handFrame.getGestures();
        for(int i=0; i<gestures.getSize(); ++i) {
            if(gestures[i].isComplete()) {
                nite::HandId id;
                pHandTracker->startHandTracking(gestures[i].getCurrentPosition(), &id);
            }
        }

        const nite::Array<nite::HandData>& hands = handFrame.getHands();
        int g_nHandsCount = hands.getSize();

        frame = Scalar(0,0,0);
        for(int i=0; i<g_nHandsCount; i++) {
            float x = 0.0, y = 0.0, z = 0.0;
            const nite::HandData& handData = hands[i];
            if(handData.isTracking()) {
                pHandTracker->convertHandCoordinatesToDepth(
                            handData.getPosition().x,
                            handData.getPosition().y,
                            handData.getPosition().z, &x, &y);
                cv::circle(frame, Point(int(x),int(y)), 1,Scalar(255,200,100),10);
            }
        }
        imshow("Kinect", frame);
        waitKey(1);

    } // fin while

    return 0;
}

