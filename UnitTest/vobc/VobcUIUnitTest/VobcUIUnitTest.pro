#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T14:51:17
#
#-------------------------------------------------

QT       += widgets network sql xml testlib

TARGET = VobcUIUnitTest
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

HEADERS +=  vobc/testvobcmonitorats.h \
            vobc/testvobcdevicemap.h \
            vobc/testvobcreadthread.h \
            vobc/testvobcwindow.h \
            vobc/testvobcalarmreport.h \
            vobc/testvobcmonitorci.h \
            vobc/testvobcmonitorzc.h \
            vobc/testvobccabinet.h \
            vobc/testvobcdomxml.h

SOURCES += main.cpp \
            vobc/testvobcmonitorats.cpp \
            vobc/testvobcdevicemap.cpp \
            vobc/testvobcreadthread.cpp \
            vobc/testvobcwindow.cpp \
            vobc/testvobcalarmreport.cpp \
            vobc/testvobcmonitorci.cpp \
            vobc/testvobcmonitorzc.cpp \
            vobc/testvobccabinet.cpp \
            vobc/testvobcdomxml.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"


INCLUDEPATH += $$PWD/../../../Mss_system/ \
               $$PWD/../../../Mss_system/common \
               $$PWD/../../../Mss_system/utils/b2v/inc \
               $$PWD/../../../Mss_system/vobc \
               $$PWD/../../../Mss_system/vobc/service/inc

HEADERS += $$PWD/../../../Mss_system/vobc/vobcreaddatathread.h \
           $$PWD/../../../Mss_system/common/mssdbconfig.h \
           $$PWD/../../../Mss_system/vobc/vobcalarmreport.h \
           $$PWD/../../../Mss_system/vobc/vobcinforeport.h \
           $$PWD/../../../Mss_system/vobc/vobcmonitorats.h \
           $$PWD/../../../Mss_system/vobc/vobcmonitorci.h \
           $$PWD/../../../Mss_system/vobc/vobcmonitorzc.h \
           $$PWD/../../../Mss_system/vobc/vobcdevice.h \
           $$PWD/../../../Mss_system/vobc/vobccabinet.h \
           $$PWD/../../../Mss_system/vobc/vobcdomxml.h \
           $$PWD/../../../Mss_system/common/vobc_data.h \
           $$PWD/../../../Mss_system/vobcsystem.h



SOURCES += $$PWD/../../../Mss_system/vobc/vobcreaddatathread.cpp \
           $$PWD/../../../Mss_system/vobc/vobcalarmreport.cpp \
           $$PWD/../../../Mss_system/vobc/vobcinforeport.cpp \
           $$PWD/../../../Mss_system/vobc/vobcmonitorats.cpp \
           $$PWD/../../../Mss_system/vobc/vobcmonitorci.cpp \
           $$PWD/../../../Mss_system/vobc/vobcmonitorzc.cpp \
           $$PWD/../../../Mss_system/vobc/vobcdevice.cpp \
           $$PWD/../../../Mss_system/vobc/vobccabinet.cpp \
           $$PWD/../../../Mss_system/vobc/vobcdomxml.cpp \
           $$PWD/../../../Mss_system/vobcsystem.cpp

FORMS    +=$$PWD/../../../Mss_system/vobc/vobcalarmreport.ui \
           $$PWD/../../../Mss_system/vobc/vobcmonitorats.ui \
           $$PWD/../../../Mss_system/vobc/vobcmonitorci.ui \
           $$PWD/../../../Mss_system/vobc/vobcmonitorzc.ui \
           $$PWD/../../../Mss_system/vobc/vobcinforeport.ui

RESOURCES += \
    $$PWD/../../../Mss_system/vobc.qrc

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
