QT += core gui dtkwidget serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DtkSerialport
TEMPLATE = app

CONFIG += c++11 link_pkgconfig

SOURCES += \
        main.cpp \
    dtkserialport.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    dtkserialport.h

DISTFILES += \
    hyw.ico

RC_ICONS = hyw.ico
