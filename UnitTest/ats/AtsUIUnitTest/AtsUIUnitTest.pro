#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T16:21:02
#
#-------------------------------------------------

QT       += widgets sql xml testlib

TARGET = AtsUIUnitTest
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
INCLUDEPATH += $$PWD/../../../Mss_system \
               $$PWD/../../../Mss_system/ats \
               $$PWD/../../../Mss_system/common \
               $$PWD/../../../Mss_system/utils/b2v/inc

HEADERS += $$PWD/../../../Mss_system/ats/atsdevice.h \
           $$PWD/../../../Mss_system/ats/atsdomxml.h \
           $$PWD/../../../Mss_system/ats/atsalarmreport.h \
           $$PWD/../../../Mss_system/ats/atsinforeport.h \
           $$PWD/../../../Mss_system/ats/atsmonitorci.h \
           $$PWD/../../../Mss_system/ats/atsmonitorvobc.h \
           $$PWD/../../../Mss_system/ats/atsmonitorzc.h \
           $$PWD/../../../Mss_system/common/mssdbconfig.h \
           $$PWD/../../../Mss_system/utils/b2v/inc/b2v.h \
           $$PWD/../../../Mss_system/utils/b2v/inc/unifw.h \
           $$PWD/../../../Mss_system/utils/b2v/inc/unifw_errno.h \
           $$PWD/../../../Mss_system/ats/atsreaddata.h \
           $$PWD/../../../Mss_system/atssystem.h


SOURCES += $$PWD/../../../Mss_system/ats/atsdevice.cpp \
           $$PWD/../../../Mss_system/ats/atsdomxml.cpp \
           $$PWD/../../../Mss_system/ats/atsalarmreport.cpp \
           $$PWD/../../../Mss_system/ats/atsinforeport.cpp \
           $$PWD/../../../Mss_system/ats/atsmonitorci.cpp \
           $$PWD/../../../Mss_system/ats/atsmonitorvobc.cpp \
           $$PWD/../../../Mss_system/ats/atsmonitorzc.cpp \
           $$PWD/../../../Mss_system/ats/atsreaddata.cpp \
           $$PWD/../../../Mss_system/atssystem.cpp \
           $$PWD/../../../Mss_system/utils/b2v/src/b2v.cpp



FORMS    += $$PWD/../../../Mss_system/ats/atsalarmreport.ui \
            $$PWD/../../../Mss_system/ats/atsinforeport.ui \
            $$PWD/../../../Mss_system/ats/atsmonitorci.ui \
            $$PWD/../../../Mss_system/ats/atsmonitorvobc.ui \
            $$PWD/../../../Mss_system/ats/atsmonitorzc.ui

RESOURCES += \
    $$PWD/../../../Mss_system/ats.qrc

HEADERS += ats/testatsdevice.h \
           ats/testatsmonitorvobc.h \
           ats/testatsreaddata.h \
           ats/testatsmonitorzc.h \
           ats/testatsmonitorci.h \
           ats/testatswindow.h \
           ats/testatsdomxml.h \
           ats/testatsalarmreport.h

SOURCES += ats/testatsdevice.cpp \
           ats/testatsmonitorvobc.cpp \
           ats/testatsreaddata.cpp \
           ats/testatsmonitorzc.cpp \
           ats/testatsmonitorci.cpp \
           ats/testatswindow.cpp \
           ats/testatsdomxml.cpp \
           ats/testatsalarmreport.cpp \
           main.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
