#-------------------------------------------------
#
# Project created by QtCreator 2017-01-19T14:22:05
#
#-------------------------------------------------

QT       += core gui sql network xml charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mss_system
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
    msssystem.cpp \
    atssystem.cpp \
    cisystem.cpp \
    zcsystem.cpp \
    vobcsystem.cpp \
    vobc/vobcalarmreport.cpp \
    vobc/vobcdevice.cpp \
    vobc/vobccabinet.cpp \
    vobc/vobcinforeport.cpp \
    vobc/vobcmonitorats.cpp \
    vobc/vobcmonitorzc.cpp \
    vobc/vobcmonitorci.cpp \
    vobc/vobcreaddatathread.cpp \
    vobc/service/src/vobcsimulate.cpp \
    vobc/service/src/vobcatsservice.cpp \
    vobc/service/src/vobcdcsservice.cpp \
    vobc/vobcdomxml.cpp \
    common/mss_transfer_data.cpp \
    ci/cisignalmachine.cpp \
    ci/cimonitorats.cpp \
    ci/cimonitorzc.cpp \
    ci/cimonitorvobc.cpp \
    ci/cidevice.cpp \
    ci/cixmlutil.cpp \
    ci/service/ciservice.cpp \
    ci/service/cisimulate.cpp \
    power/ui/powercabinet.cpp \
    power/ui/powerdevicewidget.cpp \
    power/ui/powerdaycurvewidget.cpp \
    power/ui/powercommoncurvewidget.cpp \
    power/ui/powerrealtimecurvewidget.cpp \
    power/ui/powerwindow.cpp \
    power/service/src/powerprocess.cpp \
    power/service/src/powersimulatedataservice.cpp \
    power/ui/poweralarmsystem.cpp \
    power/ui/powerreaddata.cpp \
    zc/zcsimulatedatathread.cpp \
    zc/zcdatathread.cpp \
    zc/zcgplot.cpp \
    zc/zcdayreport.cpp \
    zc/zcmonitorats.cpp \
    zc/zcmonitorci.cpp \
    zc/zcmonitorvobc.cpp \
    zc/zcquerydutinfo.cpp \
    zc/zcreaddata.cpp \
    utils/b2v/src/b2v.cpp \
    ats/atsalarmreport.cpp \
    ats/atsdevice.cpp \
    ats/atsinforeport.cpp \
    ats/atsmonitorci.cpp \
    ats/atsmonitorvobc.cpp \
    ats/atsmonitorzc.cpp \
    ats/atsreaddata.cpp \
    ats/service/src/SimulateDataService.cpp \
    ats/atsdomxml.cpp \
    zc/zcreadinfofromxml.cpp \
    utils/crc/src/crc.c \
    utils/rsspi/src/RSSP_I_cfg.c \
    utils/rsspi/src/RSSP_I_process.c \
    utils/rsspi/src/RSSP_I_protocol.c \
    utils/rsspi/src/RSSP_I_unibase.c \
    rsspi/rsspi.cpp \
    rsspi/rsspithread.cpp \
    power/ui/powerdomxml.cpp \
    rsspi/rsspisimulate.cpp \
    showdetailalarm.cpp \
    splash.cpp \
    ats/service/src/atsprocess.cpp \
    ci/ciaxlecounter.cpp \
    ci/cireaddatathread.cpp \
    ci/cirealtimereport.cpp \
    ci/cialarmreport.cpp \
    ci/citransponders.cpp \
    ci/cipointswitch.cpp \
    power/ui/powerdayreport.cpp \
    power/ui/powerchartwidget.cpp \
    power/ui/powerdisplaychoicemodel.cpp

HEADERS  += msssystem.h \
    atssystem.h \
    cisystem.h \
    zcsystem.h \
    vobcsystem.h \
    vobc/vobcalarmreport.h \
    vobc/vobcdevice.h \
    vobc/vobccabinet.h \
    vobc/vobcinforeport.h \
    vobc/vobcmonitorats.h \
    vobc/vobcmonitorzc.h \
    vobc/vobcmonitorci.h \
    vobc/vobcreaddatathread.h \
    vobc/service/inc/vobcsimulate.h \
    common/vobc_ats_parse.h \
    common/vobc_ci_comm.h \
    vobc/service/inc/vobcatsservice.h \
    vobc/service/inc/vobcdcsservice.h \
    common/vobc_data.h \
    common/vobc_data.cpp \
    vobc/vobcdomxml.h \
    ci/cisignalmachine.h \
    ci/cimonitorats.h \
    ci/cimonitorzc.h \
    ci/cimonitorvobc.h \
    ci/cidevice.h \
    ci/cixmlutil.h \
    ci/service/ciservice.h \
    ci/service/cisimulate.h \
    common/ci_data.h \
    common/ci_data.cpp \
    power/ui/powercabinet.h \
    power/ui/powerdevicewidget.h \
    power/ui/powerdaycurvewidget.h \
    power/ui/powercommoncurvewidget.h \
    power/ui/powerrealtimecurvewidget.h \
    common/power_data.h \
    common/power_data.cpp \
    power/service/inc/powerprocess.h \
    power/service/inc/powersimulatedataservice.h \
    power/ui/powerwindow.h \
    power/ui/poweralarmsystem.h \
    power/ui/powerreaddata.h \
    zc/zcsimulatedatathread.h \
    zc/zcdatathread.h \
    zc/zcgplot.h \
    zc/zcmonitorats.h \
    zc/zcmonitorci.h \
    zc/zcmonitorvobc.h \
    zc/zcquerydutinfo.h \
    common/zcdata.h \
    common/zcdata.cpp \
    common/zc_protocol_pub.h \
    zc/zcreaddata.h \
    utils/b2v/inc/b2v.h \
    utils/b2v/inc/unifw.h \
    utils/b2v/inc/unifw_errno.h \
    common/ats_data.h \
    common/ats_data.cpp \
    ats/atsalarmreport.h \
    ats/atsdevice.h \
    ats/atsinforeport.h \
    ats/atsmonitorci.h \
    ats/atsmonitorvobc.h \
    ats/atsmonitorzc.h \
    ats/atsreaddata.h \
    ats/service/inc/SimulateDataService.h \
    ats/atsdomxml.h \
    zc/zcreadinfofromxml.h \
    utils/crc/inc/crc.h \
    utils/rsspi/inc/RSSP_I_cfg.h \
    utils/rsspi/inc/RSSP_I_process.h \
    utils/rsspi/inc/RSSP_I_protocol.h \
    utils/rsspi/inc/RSSP_I_unibase.h \
    rsspi/rsspi.h \
    rsspi/rsspithread.h \
    power/ui/powerdomxml.h \
    zc/zcdayreport.h \
    rsspi/rsspisimulate.h \
    vobc/vobcuicommon.h \
    showdetailalarm.h \
    splash.h \
    common/mssdbconfig.h \
    common/mssdatadefine.h \
    ats/service/inc/atsprocess.h \
    ci/ciaxlecounter.h \
    ci/cireaddatathread.h \
    ci/cirealtimereport.h \
    ci/cialarmreport.h \
    ci/citransponders.h \
    ci/cipointswitch.h \
    power/ui/powerdayreport.h \
    power/ui/powerchartwidget.h \
    power/ui/powerdisplaychoicemodel.h



FORMS    += msssystem.ui \
    vobc/vobcalarmreport.ui \
    vobc/vobcinforeport.ui \
    vobc/vobcmonitorats.ui \
    vobc/vobcmonitorzc.ui \
    vobc/vobcmonitorci.ui \
    ci/cimonitorats.ui \
    ci/cimonitorzc.ui \
    ci/cimonitorvobc.ui \
    power/ui/powerdaycurvewidget.ui \
    power/ui/powercommoncurvewidget.ui \
    power/ui/powerrealtimecurvewidget.ui \
    zc/zcdayreport.ui \
    zc/zcmonitorats.ui \
    zc/zcmonitorvobc.ui \
    zc/zcquerydutinfo.ui \
    ats/atsalarmreport.ui \
    ats/atsinforeport.ui \
    ats/atsmonitorci.ui \
    ats/atsmonitorvobc.ui \
    ats/atsmonitorzc.ui \
    power/ui/poweralarmsystem.ui \
    zc/zcmonitorci.ui \
    showdetailalarm.ui \
    ci/cirealtimereport.ui \
    ci/cialarmreport.ui \
    power/ui/powerdayreport.ui

RESOURCES += \
    vobc.qrc \
    ci.qrc \
    zc.qrc \
    ats.qrc \
    power.qrc \
    images.qrc


INCLUDEPATH += common \
    vobc \
    ci \
    power\
    ats \
    rsspi

INCLUDEPATH += ats/service/inc
INCLUDEPATH += vobc/service/inc
INCLUDEPATH += power/service/inc

INCLUDEPATH += utils/b2v/inc

INCLUDEPATH += utils/crc/inc

INCLUDEPATH += utils/rsspi/inc

INCLUDEPATH += ci/service

CONFIG(release, debug|release){
    DEFINES += QT_NO_DEBUG_OUTPUT \
               QT_NO_INFO_OUTPUT \
               QT_NO_WARNING_OUTPUT
}
RC_FILE = mss.rc

