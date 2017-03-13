#-------------------------------------------------
#
# Project created by QtCreator 2017-02-25T16:31:30
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_vobcrilserviceut
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

MSS_SYSTEM_DIR = $$PWD/../../../Mss_system
SOURCES += tst_vobcrilserviceut.cpp \
    $$MSS_SYSTEM_DIR/vobc/service/src/vobcdcsservice.cpp \
    $$MSS_SYSTEM_DIR/common/mss_transfer_data.cpp \
    $$MSS_SYSTEM_DIR/utils/b2v/src/b2v.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"


HEADERS += \
    $$MSS_SYSTEM_DIR/vobc/service/inc/vobcdcsservice.h

INCLUDEPATH += $$MSS_SYSTEM_DIR/vobc/service/inc \
    $$MSS_SYSTEM_DIR/common \
    $$MSS_SYSTEM_DIR/utils/b2v/inc

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
