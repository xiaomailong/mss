#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T10:31:58
#
#-------------------------------------------------

QT       += testlib sql

QT       -= gui

TARGET = tst_atsprocess
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



SOURCES += tst_atsprocess.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
MSS_SYSTEM_DIR = $$PWD/../../../Mss_system

HEADERS += $$MSS_SYSTEM_DIR/ats/service/inc/atsProcess.h \
    $$MSS_SYSTEM_DIR/common/ats_data.h \
    $$MSS_SYSTEM_DIR/common/ats_data.cpp \
    $$MSS_SYSTEM_DIR/common/mssdatadefine.h \
    $$MSS_SYSTEM_DIR/common/mssdbconfig.h \
    $$MSS_SYSTEM_DIR/common/vobc_data.cpp \
    $$MSS_SYSTEM_DIR/common/ci_data.cpp \
    $$MSS_SYSTEM_DIR/common/zc_data.cpp \
    $$MSS_SYSTEM_DIR/utils/b2v/inc/b2v.h \
    $$MSS_SYSTEM_DIR/utils/b2v/inc/unifw.h \
    $$MSS_SYSTEM_DIR/utils/b2v/inc/unifw_errno.h

SOURCES += $$MSS_SYSTEM_DIR/ats/service/src/atsprocess.cpp \
    $$MSS_SYSTEM_DIR/common/mss_transfer_data.cpp \
    $$MSS_SYSTEM_DIR/utils/b2v/src/b2v.cpp


INCLUDEPATH += $$MSS_SYSTEM_DIR/ats/service/inc \
    $$MSS_SYSTEM_DIR/common \
    $$MSS_SYSTEM_DIR/utils/b2v/inc \
    $$MSS_SYSTEM_DIR/ci

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)

