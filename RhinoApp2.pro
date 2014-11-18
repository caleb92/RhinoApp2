#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T23:07:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RhinoApp2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stasm/asm.cpp \
    stasm/classicdesc.cpp \
    stasm/convshape.cpp \
    stasm/err.cpp \
    stasm/eyedet.cpp \
    stasm/eyedist.cpp \
    stasm/faceroi.cpp \
    stasm/hat.cpp \
    stasm/hatdesc.cpp \
    stasm/landmarks.cpp \
    stasm/misc.cpp \
    stasm/pinstart.cpp \
    stasm/print.cpp \
    stasm/shape17.cpp \
    stasm/shapehacks.cpp \
    stasm/shapemod.cpp \
    stasm/startshape.cpp \
    stasm/stasm.cpp \
    stasm/stasm_lib.cpp \
    stasm/MOD_1/facedet.cpp \
    stasm/MOD_1/initasm.cpp \
    videotools.cpp \
    qmyvideotools.cpp \
    mainwindow2.cpp

HEADERS  += mainwindow.h \
    stasm/asm.h \
    stasm/atface.h \
    stasm/basedesc.h \
    stasm/classicdesc.h \
    stasm/convshape.h \
    stasm/err.h \
    stasm/eyedet.h \
    stasm/eyedist.h \
    stasm/faceroi.h \
    stasm/hat.h \
    stasm/hatdesc.h \
    stasm/landmarks.h \
    stasm/landtab_muct77.h \
    stasm/misc.h \
    stasm/pinstart.h \
    stasm/print.h \
    stasm/shape17.h \
    stasm/shapehacks.h \
    stasm/shapemod.h \
    stasm/startshape.h \
    stasm/stasm.h \
    stasm/stasm_landmarks.h \
    stasm/stasm_lib.h \
    stasm/stasm_lib_ext.h \
    stasm/MOD_1/facedet.h \
    stasm/MOD_1/initasm.h \
    videotools.h \
    qmyvideotools.h \
    mainwindow2.h

FORMS    += mainwindow.ui

RESOURCES += \
    RhinoApp2.qrc

INCLUDEPATH += C:\\OpenCV-2.3.1\\opencv\\build\\include
INCLUDEPATH += C:\\stasm4.1.0\\stasm

#OpneCV libraries
LIBS += -LC:\\OpenCV-2.3.1\\mybuild\\lib\\Debug \
  -lopencv_calib3d231d \
  -lopencv_contrib231d \
  -lopencv_core231d \
  -lopencv_features2d231d \
  -lopencv_flann231d \
  -lopencv_gpu231d \
  -lopencv_highgui231d \
  -lopencv_imgproc231d \
  -lopencv_legacy231d \
  -lopencv_ml231d \
  -lopencv_objdetect231d \
  -lopencv_video231d
# -lopencv_ts231d \

OTHER_FILES +=
