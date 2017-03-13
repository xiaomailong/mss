#include <QApplication>
#include "test_powerdevicewidget.h"
#include "test_powerdayreport.h"
#include "test_powerreaddata.h"
#include "test_powerxml.h"
#include "test_powerrealtimecurve.h"
#include "test_powercommoncurve.h"
#include "test_poweralarmreport.h"
#include <QTest>
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Test_powerdevicewidget testPowerDevicewidget;
   // QTest::qExec(&testPowerDevicewidget,argc,argv);
    Test_PowerDayReport testdayreport ;
    //QTest::qExec(&testdayreport,argc,argv);
    Test_PowerReadData testdata;
    //QTest::qExec(&testdata,argc,argv);
    Test_PowerXml testReadXml ;
    //QTest::qExec(&testReadXml,argc,argv);
    Test_PowerRealTimeCurve testpowerrealtime;
    //QTest::qExec(&testpowerrealtime,argc,argv);
    Test_PowerCommonCurve testpowercommon;
   // QTest::qExec(&testpowercommon,argc,argv);
    Test_PowerAlarmReport testpoweralarm;
    QTest::qExec(&testpoweralarm,argc,argv);
    return 0;
}
