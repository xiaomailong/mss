#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T17:53:00
#
#-------------------------------------------------

QT       += widgets sql xml testlib charts network

TARGET = tst_powertesttest
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


INCLUDEPATH += $$PWD/../../../Mss_system

SOURCES += power/main.cpp \
    $$PWD/../../../Mss_system/power/ui/powercabinet.cpp \
    $$PWD/../../../Mss_system/power/ui/powerdevicewidget.cpp \
    $$PWD/../../../Mss_system/power/ui/powerdaycurvewidget.cpp \
    $$PWD/../../../Mss_system/power/ui/powercommoncurvewidget.cpp \
    $$PWD/../../../Mss_system/power/ui/powerrealtimecurvewidget.cpp \
    $$PWD/../../../Mss_system/power/ui/powerdisplaychoicemodel.cpp \
    $$PWD/../../../Mss_system/power/ui/powerwindow.cpp \
    $$PWD/../../../Mss_system/power/ui/powerdayreport.cpp \
    $$PWD/../../../Mss_system/power/ui/poweralarmsystem.cpp \
    $$PWD/../../../Mss_system/power/ui/powerreaddata.cpp \
    $$PWD/../../../Mss_system/power/ui/powerdomxml.cpp \
    $$PWD/../../../Mss_system/power/ui/powerchartwidget.cpp \
    power/test_powerdevicewidget.cpp \
    power/test_powerdaycurvewidget.cpp \
    power/test_powerdayreport.cpp \
    power/test_powerreaddata.cpp \
    power/test_powerxml.cpp \
    power/test_powerrealtimecurve.cpp \
    power/test_powercommoncurve.cpp \
    power/test_powercabinet.cpp \
    power/test_poweralarmreport.cpp



HEADERS  += \
    $$PWD/../../../Mss_system/common/mssdbconfig.h \
    $$PWD/../../../Mss_system/power/ui/powercabinet.h \
    $$PWD/../../../Mss_system/power/ui/powerdevicewidget.h \
    $$PWD/../../../Mss_system/power/ui/powerdaycurvewidget.h \
    $$PWD/../../../Mss_system/power/ui/powercommoncurvewidget.h \
    $$PWD/../../../Mss_system/power/ui/powerrealtimecurvewidget.h \
    $$PWD/../../../Mss_system/power/ui/powerdisplaychoicemodel.h \
    $$PWD/../../../Mss_system/power/ui/powerwindow.h \
    $$PWD/../../../Mss_system/power/ui/powerdayreport.h   \
    $$PWD/../../../Mss_system/power/ui/poweralarmsystem.h \
    $$PWD/../../../Mss_system/power/ui/powerreaddata.h \
    $$PWD/../../../Mss_system/power/ui/powerdomxml.h \
    $$PWD/../../../Mss_system/power/ui/powerchartwidget.h \
    power/test_powerdevicewidget.h \
    power/test_powerdaycurvewidget.h \
    power/test_powerdayreport.h \
    power/test_powerreaddata.h \
    power/test_powerxml.h \
    power/test_powerrealtimecurve.h \
    power/test_powercommoncurve.h \
    power/test_powercabinet.h \
    power/test_poweralarmreport.h



FORMS    += \
    $$PWD/../../../Mss_system/power/ui/powerdayreport.ui \
    $$PWD/../../../Mss_system/power/ui/powerdaycurvewidget.ui \
    $$PWD/../../../Mss_system/power/ui/powercommoncurvewidget.ui \
    $$PWD/../../../Mss_system/power/ui/powerrealtimecurvewidget.ui \
    $$PWD/../../../Mss_system/power/ui/poweralarmsystem.ui

RESOURCES += \
    $$PWD/../../../Mss_system/power.qrc


INCLUDEPATH += \
    $$PWD/../../../Mss_system/power \
    $$PWD/../../../Mss_system/common \
    $$PWD/../../../Mss_system/power/ui \
    $$PWD/../../../Mss_system/utils/b2v/inc \
    $$PWD/../../../Mss_system/power/service/inc




DEFINES += SRCDIR=\\\"$$PWD/\\\"

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)

