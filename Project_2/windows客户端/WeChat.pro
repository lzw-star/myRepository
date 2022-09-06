#-------------------------------------------------
#
# Project created by QtCreator 2021-12-30T19:18:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeChat
TEMPLATE = app

include(./netapi/netapi.pri)
INCLUDEPATH += ./netapi

include(./MD5/md5.pri)
INCLUDEPATH += ./MD5

include(./AudioApi/audioapi.pri)
INCLUDEPATH += ./AudioApi

include(./VideoApi/videoapi.pri)
INCLUDEPATH += ./VideoApi

SOURCES += main.cpp\
        wechatdialog.cpp \
    ckernel.cpp \
    logindialog.cpp \
    roomdialog.cpp \
    usershow.cpp

HEADERS  += wechatdialog.h \
    ckernel.h \
    logindialog.h \
    roomdialog.h \
    usershow.h

FORMS    += wechatdialog.ui \
    logindialog.ui \
    roomdialog.ui \
    usershow.ui

RESOURCES += \
    resource.qrc
