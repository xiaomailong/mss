#include "testzcwindow.h"
#include <QtTest>
#include <QHash>
#include <QSignalSpy>

#define private public
#define protected public
#include "zcsystem.h"
#undef protected
#undef private

TestZcWindow::TestZcWindow()
{

}
void TestZcWindow::initTestCase()
{
   zc = new ZcSystem;
   zc->show();
}
void TestZcWindow::testInitial()
{
    QCOMPARE(zc->zcHashTabWidget.size(),0);
    QVERIFY(zc->zcTabWidget!=NULL);
    QVERIFY(zc->zcReadData!=NULL);
    QVERIFY(zc->zcSystemThread!=NULL);
}
void TestZcWindow::testEventFromMss()
{
    connect(this,&TestZcWindow::EventFromMss,zc,&ZcSystem::onEventFromMss);

    emit EventFromMss("deviceMap");
    QTest::qWait(2000);
    QVERIFY(zc->zcHashTabWidget.contains("zcDevice"));

    emit EventFromMss("showZCtoAts");
    QTest::qWait(2000);
    QVERIFY(zc->zcHashTabWidget.contains("showZCtoAts"));

    emit EventFromMss("showZCtoVobc");
    QTest::qWait(2000);
    QVERIFY(zc->zcHashTabWidget.contains("showZCtoVobc"));

    emit EventFromMss("showZCtoCi");
    QTest::qWait(2000);
    QVERIFY(zc->zcHashTabWidget.contains("showZCtoCi"));

    emit EventFromMss("showZcAlarm");
    QTest::qWait(2000);
    QVERIFY(zc->zcHashTabWidget.contains("showZcAlarm"));
}

void TestZcWindow::testEventFromMap()
{
    connect(this,&TestZcWindow::EventFromMap,zc,&ZcSystem::onEventFromMap);

    emit EventFromMap(3,"buttonOfzc");
    QTest::qWait(2000);
    QVERIFY(zc->zcHashTabWidget.contains("buttonOfzc\u0003"));
}

void TestZcWindow::testTabClose()
{
    int count1=zc->zcTabWidget->count();
    zc->zcTabWidget->setCurrentIndex(1);
    zc->onTabClose(1);
    int count2=zc->zcTabWidget->count();
    QVERIFY(count1-count2==1);
}

void TestZcWindow::testSendEventToMss()
{
    QSignalSpy spy(zc,&ZcSystem::sendEventToMss);
    zc->close();
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);
}

void TestZcWindow::testWindowDestroy()
{
    QVERIFY(zc->zcSystemThread==NULL);
}
