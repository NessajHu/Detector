#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T22:03:13
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qwt
DEFINES += QT_DLL QWT_DLL
INCLUDEPATH += D:\Qt5.10.0\5.10.0\mingw53_32\include\Qwt\
CONFIG += debug_and_release
CONFIG(debug, debug|release){
    LIBS += -lqwtd
}else{
    LIBS += -lqwt
}

TARGET = Detector
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


SOURCES += \
    main.cpp \
    systemoption.cpp \
    datadisplay.cpp \
    datawave.cpp \
    statusanalysis.cpp \
    historicaldata.cpp \
    mainwindow.cpp \
    datahandle.cpp \
    tcpserver.cpp

HEADERS += \
    systemoption.h \
    datadisplay.h \
    tcpserver.h \
    datawave.h \
    statusanalysis.h \
    historicaldata.h \
    mainwindow.h \
    datahandle.h \
    systemoption.h

SUBDIRS += \
    Detector.pro

DISTFILES += \
    README.md
