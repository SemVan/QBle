#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T21:11:19
#
#-------------------------------------------------

QT       += core gui bluetooth network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = QBle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ble_linker.cpp \
    qcustomplot.cpp \
    udpserver.cpp \
    datacontainer.cpp

HEADERS  += mainwindow.h \
    ble_linker.h \
    qcustomplot.h \
    udpserver.h \
    datacontainer.h

FORMS    += mainwindow.ui
