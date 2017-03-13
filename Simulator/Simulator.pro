#-------------------------------------------------
#
# Project created by QtCreator 2017-03-03T12:25:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
    mainwindow.cpp \
    ats/atswidget.cpp \
    ci/ciwidget.cpp \
    power/powerwidget.cpp \
    vobc/vobcwidget.cpp \
    zc/zcwidget.cpp \
    utils/processor/networkprocessor.cpp \
    utils/processor/burstprocessor.cpp \
    utils/processor/abstractprocessor.cpp \
    utils/processor/periodicprocessor.cpp \
    common/simulatoruserdata.cpp

HEADERS  += mainwindow.h \
    ats/atswidget.h \
    ci/ciwidget.h \
    power/powerwidget.h \
    vobc/vobcwidget.h \
    zc/zcwidget.h \
    utils/processor/networkprocessor.h \
    utils/processor/burstprocessor.h \
    utils/processor/abstractprocessor.h \
    utils/processor/periodicprocessor.h \
    common/simulatorconfig.h \
    common/simulatorlogconfig.h \
    common/simulatoruserdata.h

INCLUDEPATH += common \
    utils/processor \
    ats \
    ci \
    power \
    zc \
    vobc


MSS_SYSTEM_DIR = $$PWD/../Mss_system

INCLUDEPATH += $$MSS_SYSTEM_DIR/common \
    $$MSS_SYSTEM_DIR/utils/b2v/inc \
    $$MSS_SYSTEM_DIR/ci/service \
    $$MSS_SYSTEM_DIR/zc \
    $$MSS_SYSTEM_DIR/ats/service/inc \
    $$MSS_SYSTEM_DIR/power/service/inc \
    $$MSS_SYSTEM_DIR/vobc/service/inc

SOURCES += $$MSS_SYSTEM_DIR/common/mss_transfer_data.cpp \
    $$MSS_SYSTEM_DIR/utils/b2v/src/b2v.cpp

HEADERS  += ats/atsperiodicprocessor.h \
    ats/atsburstprocessor.h \
    ats/atsdatafactory.h

SOURCES += ats/atsburstprocessor.cpp \
    ats/atsperiodicprocessor.cpp \
    ats/atsdatafactory.cpp \


FORMS    += mainwindow.ui \
    ats/atswidget.ui \
    ci/ciwidget.ui \
    power/powerwidget.ui \
    vobc/vobcwidget.ui \
    zc/zcwidget.ui

