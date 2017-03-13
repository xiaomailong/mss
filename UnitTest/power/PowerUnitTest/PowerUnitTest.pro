#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T16:11:44
#
#-------------------------------------------------

QT       += testlib sql network

QT       -= gui

TARGET = tst_powerunittesttest
CONFIG   += console
CONFIG   -= app_bundle

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


SOURCES += tst_powerunittesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

MSS_SYSTEM_DIR = $$PWD/../../../Mss_system

INCLUDEPATH += $$MSS_SYSTEM_DIR/power/service/inc
INCLUDEPATH += $$MSS_SYSTEM_DIR/power/service/src
INCLUDEPATH += $$MSS_SYSTEM_DIR/power/ui
INCLUDEPATH += $$MSS_SYSTEM_DIR/common
INCLUDEPATH += $$MSS_SYSTEM_DIR/utils/b2v/inc
INCLUDEPATH += $$MSS_SYSTEM_DIR/utils/crc/inc
INCLUDEPATH += $$MSS_SYSTEM_DIR/utils/rsspi/inc
INCLUDEPATH += $$MSS_SYSTEM_DIR/utils/b2v/src

VPATH += $$MSS_SYSTEM_DIR/power/service/inc
VPATH += $$MSS_SYSTEM_DIR/power/service/src
VPATH += $$MSS_SYSTEM_DIR/power/ui
VPATH += $$MSS_SYSTEM_DIR/common
VPATH += $$MSS_SYSTEM_DIR/utils/rsspi/inc
VPATH += $$MSS_SYSTEM_DIR/utils/b2v/inc
VPATH += $$MSS_SYSTEM_DIR/utils/crc/inc
VPATH += $$MSS_SYSTEM_DIR/utils/b2v/src

SOURCES += $$MSS_SYSTEM_DIR/power/service/src/powerprocess.cpp \
    $$MSS_SYSTEM_DIR/power/service/src/powersimulatedataservice.cpp \
    b2v.cpp \
    power_data.cpp\

HEADERS  +=  power_data.h\
    $$MSS_SYSTEM_DIR/power/service/inc/powerprocess.h \
    $$MSS_SYSTEM_DIR/power/service/inc/powersimulatedataservice.h \
    b2v.h \
    unifw.h \
    unifw_errno.h \

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
