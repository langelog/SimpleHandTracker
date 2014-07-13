TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

####################################################
## OPENNI + NiTE                                  ##
####################################################
INCLUDEPATH += "C:\Program Files (x86)\OpenNI2\Include"
LIBS += "C:\Program Files (x86)\OpenNI2\Lib\OpenNI2.lib"
INCLUDEPATH += "C:\Program Files (x86)\PrimeSense\NiTE2\Include"
LIBS += "C:\Program Files (x86)\PrimeSense\NiTE2\Lib\NiTE2.lib"

####################################################
## OPENCV                                         ##
####################################################
INCLUDEPATH += "C:\opencv-source\opencv\build\include"
LIBS += "C:\opencv-source\opencv\build\x86\vc10\lib\opencv_core247.lib"
LIBS += "C:\opencv-source\opencv\build\x86\vc10\lib\opencv_highgui247.lib"
LIBS += "C:\opencv-source\opencv\build\x86\vc10\lib\opencv_imgproc247.lib"
LIBS += "C:\opencv-source\opencv\build\x86\vc10\lib\opencv_features2d247.lib"
LIBS += "C:\opencv-source\opencv\build\x86\vc10\lib\opencv_calib3d247.lib"

SOURCES += main.cpp \
    KinectController.cpp

HEADERS += \
    KinectController.h

