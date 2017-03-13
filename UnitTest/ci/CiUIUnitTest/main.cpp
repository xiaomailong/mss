#include <QApplication>
#include "ci/testcidevice.h"
#include "ci/TestCiAlarmReport.h"
#include "ci/testcireaddata.h"
#include "ci/testcixml.h"
#include "ci/testcimonitorats.h"
#include "ci/testcimonitorvobc.h"
#include "ci/testcimonitorzc.h"
#include "ci/testciwindow.h"
#include <QTest>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    TestCiDevice  testCiDevice;
    QTest::qExec(&testCiDevice,argc,argv);

    TestCiAlarmReport testCiAlarmReport;
    QTest::qExec(&testCiAlarmReport,argc,argv);

    TestCiXml testCiXml;
    QTest::qExec(&testCiXml,argc,argv);

    TestCiReadData testCiReadData;
    QTest::qExec(&testCiReadData,argc,argv);

    TestCiMonitorAts testCiMonitorAts;
    QTest::qExec(&testCiMonitorAts,argc,argv);

    TestCiMonitorVobc testCiMonitorVobc;
    QTest::qExec(&testCiMonitorVobc,argc,argv);

    TestCiMonitorZc testCiMonitorZc;
    QTest::qExec(&testCiMonitorZc,argc,argv);

    TestCiWindow testCiWindow;
    QTest::qExec(&testCiWindow,argc,argv);


    return 0;
}
