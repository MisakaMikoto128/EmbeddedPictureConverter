#-------------------------------------------------
#
# Project created by QtCreator 2019-09-05T08:17:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# OpenCV
INCLUDEPATH += \
    D:\Qt\OpenCV\build\x64\install\include \
    D:\Qt\OpenCV\build\x64\install\include\opencv2



LIBS += -L D:\Qt\OpenCV\build\x64\install\x64\mingw\lib \
        -llibopencv_core412        \
        -llibopencv_highgui412     \
        -llibopencv_imgcodecs412   \
        -llibopencv_imgproc412     \
        -llibopencv_features2d412  \
        -llibopencv_calib3d412

RESOURCES += \
    icon.qrc

