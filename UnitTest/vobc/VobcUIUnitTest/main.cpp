#include <QApplication>
#include "vobc/testvobcalarmreport.h"
#include "vobc/testvobcmonitorats.h"
#include "vobc/testvobcmonitorci.h"
#include "vobc/testvobcmonitorzc.h"
#include "vobc/testvobcdevicemap.h"
#include "vobc/testvobccabinet.h"
#include "vobc/testvobcreadthread.h"
#include "vobc/testvobcdomxml.h"
#include "vobc/testvobcwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    TestVobcAlarmReport testVobcAlarmReport;
    QTest::qExec(&testVobcAlarmReport,argc,argv);

    TestVobcMonitorAts testVobcMonitorAts;
    QTest::qExec(&testVobcMonitorAts,argc,argv);

    TestVobcMonitorCi testVobcMonitorCi;
    QTest::qExec(&testVobcMonitorCi,argc,argv);

    TestVobcMonitorZC testVobcMonitorZC;
    QTest::qExec(&testVobcMonitorZC,argc,argv);


    TestVobcDeviceMap testVobcDeviceMap;
    QTest::qExec(&testVobcDeviceMap,argc,argv);

    TestVobcCabinet testVobcCabinet;
    QTest::qExec(&testVobcCabinet,argc,argv);

    TestVobcDomXml testVobcDomXml;
    QTest::qExec(&testVobcDomXml,argc,argv);

    TestVobcReadThread testVobcReadThread;
    QTest::qExec(&testVobcReadThread,argc,argv);

    TestVobcWindow testVobcWindow;
    QTest::qExec(&testVobcWindow,argc,argv);

    return 0;
}
