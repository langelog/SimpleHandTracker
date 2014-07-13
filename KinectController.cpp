#include "KinectController.h"

KinectController::KinectController() {
    isReady = false;
}

void KinectController::init() {
    ////////////////////////////////////////////////////////////////////////
    /// OPENNI INITIALIZATION:                                           ///
    ////////////////////////////////////////////////////////////////////////
    //----------------------------------------------------------------------
    cout << "Initializing OpenNI...";
    if(openni::OpenNI::initialize() != openni::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    //----------------------------------------------------------------------
    cout << "Opening Device...";
    if(device.open(openni::ANY_DEVICE) != openni::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    //----------------------------------------------------------------------
    cout << "Creating streamer for color...";
    if(color.create(device, openni::SENSOR_COLOR) != openni::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    //----------------------------------------------------------------------
//    cout << "Creating streamer for depth...";
//    if(depth.create(device, openni::SENSOR_DEPTH) != openni::STATUS_OK) {
//        cout << "Failed" << endl;
//        return;
//    }
//    cout << "OK" << endl;
    //----------------------------------------------------------------------
    cout << "Starting color streaming...";
    if(color.start() != openni::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    //----------------------------------------------------------------------
//    cout << "Starting depth streaming...";
//    if(depth.start() != openni::STATUS_OK) {
//        cout << "Failed" << endl;
//        return;
//    }
//    cout << "OK" << endl;
    ////////////////////////////////////////////////////////////////////////
    /// NiTE INITIALIZATION:                                             ///
    ////////////////////////////////////////////////////////////////////////
    //----------------------------------------------------------------------
    cout << "Initializing NiTE...";
    if(nite::NiTE::initialize() != nite::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    //----------------------------------------------------------------------
    cout << "Creating Hand Tracker...";
    if(pHandTracker.create() != nite::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    //----------------------------------------------------------------------
    cout << "Setting Start Gesture Detection...";
    if(pHandTracker.startGestureDetection(nite::GESTURE_HAND_RAISE) != nite::STATUS_OK) {
        cout << "Failed" << endl;
        return;
    }
    cout << "OK" << endl;
    isReady = true;
    //----------------------------------------------------------------------
}

void KinectController::run() {
    string colorTitle = "Kinect Color";
//    string depthTitle = "Kinect Depth";
    cout << endl << "#####################################################" << endl;
    if(!isReady) {
        cout << "Trying to run controller: Not ready!" << endl;
        return;
    }

    while(isReady) {
        if(color.readFrame(&colorFrame) != openni::STATUS_OK) {
            cout << "Failed to read color frame" << endl;
            continue;
        }
//        if(depth.readFrame(&depthFrame) != openni::STATUS_OK) {
//            cout << "Failed to read depth frame" << endl;
//            continue;
//        }
        const openni::RGB888Pixel* imageBuffer = (const openni::RGB888Pixel*)colorFrame.getData();
//        const openni::Grayscale16Pixel* depthBuffer = (const openni::Grayscale16Pixel*)depthFrame.getData();

        cFrame.create(colorFrame.getHeight(), colorFrame.getWidth(), CV_8UC3);
//        dFrame.create(depthFrame.getHeight(), depthFrame.getWidth(), CV_16UC1);
        memcpy(cFrame.data, imageBuffer, 3*colorFrame.getHeight()*colorFrame.getWidth()*sizeof(uint8_t));
//        memcpy(dFrame.data, depthBuffer, depthFrame.getHeight()*depthFrame.getWidth()*sizeof(uint16_t));
        cv::cvtColor(cFrame,cFrame,CV_RGB2BGR);

        //############################################################################
        // HERE WE HAVE AVAILABLE THE COLOR IMAGE FROM KINECT, NOW WE GET THE HANDS ##
        //############################################################################

        pHandTracker.readFrame(&handFrame);
        const nite::Array<nite::GestureData>& gestures = handFrame.getGestures();
        for(int i=0; i<gestures.getSize(); i++) {
            if(gestures[i].isComplete()) {
                nite::HandId id;
                pHandTracker.startHandTracking(gestures[i].getCurrentPosition(), &id);
            }
        }

        const nite::Array<nite::HandData>& hands = handFrame.getHands();
        int nHands = hands.getSize();

        for(int i=0; i<nHands; i++) {
            const nite::HandData& handData = hands[i];
            if(handData.isTracking()) {
                float x, y;
                pHandTracker.convertHandCoordinatesToDepth(
                            handData.getPosition().x,
                            handData.getPosition().y,
                            handData.getPosition().z,
                            &x, &y);
                cv::circle(cFrame,Point(int(x), int(y)),1,Scalar(61,0,245),10);
            }
        }



        imshow((const string)colorTitle, cFrame);
//        imshow((const string)depthTitle, dFrame);
        if(waitKey(1) == 'q')
            isReady = false;

    }
}


//    pHandTracker = new nite::HandTracker;
//    pHandTracker->create();
//    pHandTracker->startGestureDetection(nite::GESTURE_HAND_RAISE);

//        const nite::Array<nite::HandData>& hands = handFrame.getHands();
//        int g_nHandsCount = hands.getSize();

//        if(g_nHandsCount>0) {
//            const nite::HandData& handData = hands[0];
//            if(handData.isTracking()) {
//                float x, y;
//                pHandTracker->convertHandCoordinatesToDepth(
//                            handData.getPosition().x,
//                            handData.getPosition().y,
//                            handData.getPosition().z,
//                            &x, &y);
//                cout << x << " | " << y << endl;
//            }
//        } else {
//            cout << 0.0 << " | " << 0.0 << endl;
//        }
//    }
