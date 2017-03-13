#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T10:32:30
#
#-------------------------------------------------

QT       += widgets sql xml testlib network

TARGET = tst_citest
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

MSS_DIR = $$PWD/../../../Mss_system

INCLUDEPATH += $$MSS_DIR \
               $$MSS_DIR/ci \
               $$MSS_DIR/utils/b2v/inc \
               $$MSS_DIR/common

HEADERS += $$MSS_DIR/ci/cialarmreport.h \
           $$MSS_DIR/ci/ciaxlecounter.h \
           $$MSS_DIR/ci/cirealtimereport.h \
           $$MSS_DIR/ci/cisignalmachine.h \
           $$MSS_DIR/ci/citransponders.h \
           $$MSS_DIR/ci/cipointswitch.h \
           $$MSS_DIR/ci/cimonitorats.h \
           $$MSS_DIR/ci/cimonitorzc.h \
           $$MSS_DIR/ci/cimonitorvobc.h \
           $$MSS_DIR/ci/cidevice.h \
           $$MSS_DIR/ci/cixmlutil.h \
           $$MSS_DIR/common/ci_data.h \
           $$MSS_DIR/ci/cireaddatathread.h \
           $$MSS_DIR/common/mss_data.h \
           $$MSS_DIR/common/mss_db_config.h \
           $$MSS_DIR/utils/b2v/inc/b2v.h \
           $$MSS_DIR/utils/b2v/inc/unifw.h \
           $$MSS_DIR/utils/b2v/inc/unifw_errno.h \
           $$MSS_DIR/cisystem.h

SOURCES += $$MSS_DIR/ci/cialarmreport.cpp \
           $$MSS_DIR/ci/ciaxlecounter.cpp \
           $$MSS_DIR/ci/cirealtimereport.cpp \
           $$MSS_DIR/ci/cisignalmachine.cpp \
           $$MSS_DIR/ci/citransponders.cpp \
           $$MSS_DIR/ci/cipointswitch.cpp \
           $$MSS_DIR/ci/cimonitorats.cpp \
           $$MSS_DIR/ci/cimonitorzc.cpp \
           $$MSS_DIR/ci/cimonitorvobc.cpp \
           $$MSS_DIR/ci/cidevice.cpp \
           $$MSS_DIR/ci/cixmlutil.cpp \
           $$MSS_DIR/common/ci_data.cpp \
           $$MSS_DIR/ci/cireaddatathread.cpp \
           $$MSS_DIR/utils/b2v/src/b2v.cpp \
           $$MSS_DIR/cisystem.cpp



RESOURCES += \
           $$MSS_DIR/ci.qrc

FORMS    += $$MSS_DIR/ci/cialarmreport.ui \
            $$MSS_DIR/ci/cirealtimereport.ui \
            $$MSS_DIR/ci/cimonitorats.ui \
            $$MSS_DIR/ci/cimonitorzc.ui \
            $$MSS_DIR/ci/cimonitorvobc.ui


HEADERS +=  \
    ci/testcialarmreport.h \
    ci/testcixml.h \
    ci/testcireaddata.h \
    ci/testcimonitorats.h \
    ci/testcimonitorvobc.h \
    ci/testcimonitorzc.h \
    ci/testciwindow.h\
    ci/testcidevice.h


SOURCES +=  \
    main.cpp \
    ci/testcialarmreport.cpp \
    ci/testcixml.cpp \
    ci/testcireaddata.cpp \
    ci/testcimonitorats.cpp \
    ci/testcimonitorvobc.cpp \
    ci/testcimonitorzc.cpp \
    ci/testciwindow.cpp\
    ci/testcidevice.cpp
	
DEFINES += SRCDIR=\\\"$$PWD/\\\"

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
