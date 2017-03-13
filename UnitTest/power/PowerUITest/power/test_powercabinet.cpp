#include "test_powercabinet.h"
#include <QObject>
#include <QtTest>



Test_PowerCabinet::Test_PowerCabinet(QObject *parent) : QObject(parent)
{

}

void Test_PowerCabinet::initTestCase()
{
    powerCabinet=new Powercabinet;
    powerCabinet->resize(1024,768);
    powerCabinet->show();
    QTest::mouseMove(powerCabinet,QPoint(0,0));

}



void Test_PowerCabinet::testInitial()
{
     QTest::qWait(2000);
     QVERIFY(powerCabinet->scale==1.0);
     QCOMPARE(powerCabinet->transX,100);
     QCOMPARE(powerCabinet->transY,30);
     QVERIFY(powerCabinet->lastPoint.x()==0);
     QVERIFY(powerCabinet->lastPoint.y()==0);
     QVERIFY(powerCabinet->endPoint.x()==0);
     QVERIFY(powerCabinet->endPoint.y()==0);

}


void Test_PowerCabinet::testStyleSheet()
{
    QString styleSheet=powerCabinet->styleSheet();
    QVERIFY(styleSheet.compare("")!=0);
}
