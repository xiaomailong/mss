#include "testvobcwindow.h"
#include <QtTest>
#include <QHash>
#include <QSignalSpy>
#include "vobc_data.h"

#define private public
#define protected public
#include "vobcsystem.h"
#undef protected
#undef private

TestVobcWindow::TestVobcWindow()
{

}

void TestVobcWindow::initTestCase()
{
    vobc=new VobcSystem;
    vobc->show();
}

void TestVobcWindow::testInitial()
{
    //QTest::qWait(2000);
    //QCoreApplication::processEvents();

    QCOMPARE(vobc->hashTabWidget.size(),0);
    QVERIFY(vobc->tabWidget!=NULL);
    QVERIFY(vobc->readData!=NULL);
    QVERIFY(vobc->thread!=NULL);
}

void TestVobcWindow::testEventFromMss()
{
    connect(this,&TestVobcWindow::EventFromMss,vobc,&VobcSystem::onEventFromMss);

    emit EventFromMss("deviceMap");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("vobcDevice"));

    emit EventFromMss("showVobcAts");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("showVobcAts"));

    emit EventFromMss("showVobcZc");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("showVobcZc"));

    emit EventFromMss("showVobcCi");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("showVobcCi"));

    emit EventFromMss("showVobcAlarm");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("showVobcAlarm"));

}

void TestVobcWindow::testEventFromMap()
{
    connect(this,&TestVobcWindow::EventFromMap,vobc,&VobcSystem::onEventFromMap);

    emit EventFromMap(3,"buttonHead");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("buttonHead\u0003"));

    emit EventFromMap(4,"buttonTail");
    QTest::qWait(2000);
    QVERIFY(vobc->hashTabWidget.contains("buttonTail\u0004"));
}

void TestVobcWindow::testAlarmFromMss()
{
    qRegisterMetaType<vobc_subsys_msg_t>("vobc_subsys_msg_t");

    connect(this,&TestVobcWindow::AlarmFromMss,vobc,&VobcSystem::onAlarmFromMss);
    QSignalSpy spy(vobc,&VobcSystem::sendAlarmToDevice);

    vobc_subsys_msg_t msg;   
    msg.msg_type =(qrand()%4);
    msg.sys_id = (qrand()%4);
    msg.dev_type = (qrand()%4);
    msg.dev_id = (qrand()%4);
    msg.dev_local = (qrand()%4);
    msg.alarm_type = (qrand()%4);
    msg.alarm_subtype = (qrand()%3);
    msg.alarm_level= (qrand()%3);
    msg.alarm_code= (qrand()%3);

    emit AlarmFromMss(msg);
    QTest::qWait(2000);

    QVERIFY(spy.count()==1);
}

void TestVobcWindow::testTabClose()
{
    int count1=vobc->tabWidget->count();
    vobc->tabWidget->setCurrentIndex(1);
    vobc->onTabClose(1);
    int count2=vobc->tabWidget->count();
    QVERIFY(count1-count2==1);
}

void TestVobcWindow::testSendEventToMss()
{
    QSignalSpy spy(vobc,&VobcSystem::sendEventToMss);
    vobc->close();
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);
}

void TestVobcWindow::testWindowDestroy()
{
    QVERIFY(vobc->thread==NULL);
}

void TestVobcWindow::cleanupTestCase()
{
}
