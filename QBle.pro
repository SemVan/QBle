#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T21:11:19
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ble_linker.cpp

HEADERS  += mainwindow.h \
    ble_linker.h

FORMS    += mainwindow.ui
