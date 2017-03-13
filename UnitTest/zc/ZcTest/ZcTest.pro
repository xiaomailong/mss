
QT += core gui sql testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZcTest

TEMPLATE = app

MSS_SYSTEM_DIR = $$PWD/../../../Mss_system
INCLUDEPATH += $$MSS_SYSTEM_DIR
INCLUDEPATH += $$MSS_SYSTEM_DIR/zc
INCLUDEPATH += $$MSS_SYSTEM_DIR/common
INCLUDEPATH += $$MSS_SYSTEM_DIR/utils/b2v/inc

SOURCES += \
    $$MSS_SYSTEM_DIR/common/mss_transfer_data.cpp \
    $$MSS_SYSTEM_DIR/utils/b2v/src/b2v.cpp \
    $$MSS_SYSTEM_DIR/zc/zcdatathread.cpp \
    zctest.cpp

HEADERS  += \
    $$MSS_SYSTEM_DIR/common/mssdatadefine.h \
    $$MSS_SYSTEM_DIR/utils/b2v/inc/b2v.h \
    $$MSS_SYSTEM_DIR/utils/b2v/inc/unifw.h \
    $$MSS_SYSTEM_DIR/utils/b2v/inc/unifw_errno.h \
    $$MSS_SYSTEM_DIR/zc/zcdatathread.h \
    $$MSS_SYSTEM_DIR/common/zcdata.h \
    $$MSS_SYSTEM_DIR/common/zcdata.cpp

#Automate Unit test purpose
include($$PWD/../../../UnitTest/unittestautocfg.pri)
