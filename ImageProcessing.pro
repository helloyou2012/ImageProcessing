#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T22:04:02
#
#-------------------------------------------------

QT       += core gui

TARGET = ImageProcessing
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ImageScene.cpp \
    OpencvFunction.cpp \
    ColorWeightDialog.cpp \
    ImageItem.cpp \
    subimagewidget.cpp \
    subimagetab.cpp

HEADERS  += MainWindow.h \
    ImageScene.h \
    OpencvFunction.h \
    ColorWeightDialog.h \
    ImageItem.h \
    subimagewidget.h \
    subimagetab.h

INCLUDEPATH +=/usr/local/include/opencv2
LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_contrib.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_features2d.so \
        /usr/local/lib/libopencv_flann.so \
        /usr/local/lib/libopencv_gpu.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_legacy.so \
        /usr/local/lib/libopencv_ml.so \
        /usr/local/lib/libopencv_objdetect.so \
        /usr/local/lib/libopencv_video.so

RESOURCES += \
    ImageProcessing.qrc

OTHER_FILES += \
    menu_view.png \
    menu_delete.png \
    menu_analyse.png
