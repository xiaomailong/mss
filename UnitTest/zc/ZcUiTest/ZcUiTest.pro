#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T17:10:06
#
#-------------------------------------------------

QT       += widgets network sql xml testlib


TARGET = tst_zcuitesttest
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


SOURCES += \
    main.cpp \
    zc/testalarmreport.cpp \
    zc/testzcats.cpp \
    zc/testzcci.cpp \
    zc/testzcgplot.cpp \
    zc/testzcreaddata.cpp \
    zc/testzcvobc.cpp \
    zc/testzcwindow.cpp \
    zc/testzcxml.cpp \
    $$PWD/../../../Mss_system/zc/zcdayreport.cpp \
    $$PWD/../../../Mss_system/zc/zcgplot.cpp \
    $$PWD/../../../Mss_system/zc/zcmonitorats.cpp \
    $$PWD/../../../Mss_system/zc/zcmonitorci.cpp \
    $$PWD/../../../Mss_system/zc/zcmonitorvobc.cpp \
    $$PWD/../../../Mss_system/zc/zcquerydutinfo.cpp \
    $$PWD/../../../Mss_system/zc/zcreaddata.cpp \
    $$PWD/../../../Mss_system/zc/zcreadinfofromxml.cpp \
    $$PWD/../../../Mss_system/zcsystem.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH +=$$PWD/../../../Mss_system/common

INCLUDEPATH += $$PWD/../../../Mss_system/ \
               $$PWD/../../../Mss_system/zc \
               $$PWD/../../../Mss_system/utils/b2v/inc

FORMS += \
    $$PWD/../../../Mss_system/zc/zcdayreport.ui \
    $$PWD/../../../Mss_system/zc/zcmonitorats.ui \
    $$PWD/../../../Mss_system/zc/zcmonitorci.ui \
    $$PWD/../../../Mss_system/zc/zcmonitorvobc.ui \
    $$PWD/../../../Mss_system/zc/zcquerydutinfo.ui

HEADERS += \
    zc/testalarmreport.h \
    zc/testzcats.h \
    zc/testzcci.h \
    zc/testzcgplot.h \
    zc/testzcreaddata.h \
    zc/testzcvobc.h \
    zc/testzcwindow.h \
    zc/testzcxml.h \
    $$PWD/../../../Mss_system/zc/zcdayreport.h \
    $$PWD/../../../Mss_system/zc/zcgplot.h \
    $$PWD/../../../Mss_system/zc/zcmonitorats.h \
    $$PWD/../../../Mss_system/zc/zcmonitorci.h \
    $$PWD/../../../Mss_system/zc/zcmonitorvobc.h \
    $$PWD/../../../Mss_system/zc/zcquerydutinfo.h \
    $$PWD/../../../Mss_system/zc/zcreaddata.h \
    $$PWD/../../../Mss_system/zc/zcreadinfofromxml.h \
    $$PWD/../../../Mss_system/zcsystem.h

RESOURCES += \
    $$PWD/../../../Mss_system/zc.qrc

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
