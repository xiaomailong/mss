#include <QApplication>
#include "ats/testatsdevice.h"
#include "ats/testatsreaddata.h"
#include "ats/testatsmonitorvobc.h"
#include "ats/testatsmonitorzc.h"
#include "ats/testatsmonitorci.h"
#include "ats/testatswindow.h"
#include "ats/testatsdomxml.h"
#include "ats/testatsalarmreport.h"


int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    TestAtsDevice  testAtsDevice;
    QTest::qExec(&testAtsDevice,argc,argv);

    TestAtsReadData testAtsReadData;
    QTest::qExec(&testAtsReadData,argc,argv);

    TestAtsMonitorVobc testAtsMonitorVobc;
    QTest::qExec(&testAtsMonitorVobc,argc,argv);

    TestAtsMonitorZc testAtsMonitorZc;
    QTest::qExec(&testAtsMonitorZc,argc,argv);

    TestAtsMonitorCi testAtsMonitorCi;
    QTest::qExec(&testAtsMonitorCi,argc,argv);

    TestAtsWindow testAtsWindow;
    QTest::qExec(&testAtsWindow,argc,argv);

    TestAtsDomXml testAtsDomXml;
    QTest::qExec(&testAtsDomXml,argc,argv);

    TestAtsAlarmReport testAtsAlarmReport;
    QTest::qExec(&testAtsAlarmReport,argc,argv);

    return 0;
}
