#include <QApplication>
#include "zc/testzcci.h"
#include "zc/testzcats.h"
#include "zc/testzcvobc.h"
#include "zc/testzcxml.h"
#include "zc/testzcreaddata.h"
#include "zc/testalarmreport.h"
#include "zc/testzcgplot.h"
#include "zc/testzcwindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    TestZcCi zcci;
    QTest::qExec(&zcci,argc,argv);

    TestZcAts zcats;
    QTest::qExec(&zcats,argc,argv);

    TestZcVobc zcvobc;
    QTest::qExec(&zcvobc,argc,argv);

    TestZcXml zcxml;
    QTest::qExec(&zcxml,argc,argv);

    TestZcReaddata readdata;
    QTest::qExec(&readdata,argc,argv);

    testAlarmReport alarm;
    QTest::qExec(&alarm,argc,argv);

    TestZcgplot zcgplot;
    QTest::qExec(&zcgplot,argc,argv);


    TestZcWindow zcwin;
    QTest::qExec(&zcwin,argc,argv);

    return 0;
}
