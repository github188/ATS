#-------------------------------------------------
#
# Project created by QtCreator 2013-09-27T13:48:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = atsgui
TEMPLATE = app

INCLUDEPATH += ../include \
            ../../libs/libosa/include \
            ../../utils/cJSON  \
            ../../libs/libsdk/inc


win32{
SOURCES += \
    ../../libs/libosa/src/win32/osa_cvt.c \
    ../../libs/libosa/src/win32/osa_file.c \
    ../../libs/libosa/src/win32/osa_dir.c \
    ../../libs/libosa/src/win32/osa_socket.c \
    ../../libs/libosa/src/win32/osa_select.c \
    ../../libs/libosa/src/win32/osa_time.c \
    ../../libs/libosa/src/win32/osa_dll.c \
    ../../libs/libosa/src/win32/osa_timer.c \
    ../../libs/libosa/src/win32/osa_thread.c


LIBS +=-lws2_32
}

!win32{
SOURCES += \
    ../../libs/libosa/src/linux/osa_socket.c \
    ../../libs/libosa/src/linux/osa_select.c \
    ../../libs/libosa/src/linux/osa_file.c \
    ../../libs/libosa/src/linux/osa_dir.c \
    ../../libs/libosa/src/linux/osa_time.c \
    ../../libs/libosa/src/linux/osa_dll.c \
    ../../libs/libosa/src/linux/osa_timer.c \
    ../../libs/libosa/src/linux/osa_thread.c
}

SOURCES += \
    ../../utils/cJSON/cJSON.c \
    ../../libs/libosa/src/common/osa_random.c \
    ../../libs/libosa/src/common/osa_msg.c \
    ../../libs/libosa/src/common/osa_mem.c \
    ../../libs/libosa/src/common/osa_log.c


SOURCES += main.cpp \
    mainwindow.cpp \
    agent.cpp \
    logindialog.cpp \
    devconnectdialog.cpp \
    device.cpp \
    configdialog.cpp \
    aboutdialog.cpp \
    sdkmanger.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    ../include/agent.h \
    devconnectdialog.h \
    device.h \
    configdialog.h \
    aboutdialog.h \
    sdkmanger.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    devconnectdialog.ui \
    configdialog.ui \
    aboutdialog.ui

RESOURCES += \
    companyLogo.qrc
