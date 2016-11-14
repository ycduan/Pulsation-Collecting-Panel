#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T15:44:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport printsupport

TARGET = pulsationPanel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spconnector.cpp \
    pulsationhandler.cpp \
    qcustomplot.cpp \
    oscillogramview.cpp

HEADERS  += mainwindow.h \
    spconnector.h \
    pulsationhandler.h \
    qcustomplot.h \
    oscillogramview.h

FORMS    += mainwindow.ui \
    oscillogramview.ui

DISTFILES += \
    pcp.ico \
    pcp.rc

RC_FILE = pcp.rc
