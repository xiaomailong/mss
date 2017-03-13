#include "testciwindow.h"
#include <QtTest>
#include <QHash>
#include <QSignalSpy>

#define private public
#define protected public
#include "cisystem.h"
#undef protected
#undef private

TestCiWindow::TestCiWindow()
{

}

void TestCiWindow::initTestCase()
{
    ci = new CiSystem;
    ci->show();
}

void TestCiWindow::testInitial()
{
    QCOMPARE(ci->hashTabWidget.size(),0);
    QVERIFY(ci->tabWidget!=NULL);
    QVERIFY(ci->readData!=NULL);
    QVERIFY(ci->thread!=NULL);
}

void TestCiWindow::testEventFromMss()
{
    connect(this,&TestCiWindow::EventFromMss,ci,&CiSystem::onEventFromMss);

    emit EventFromMss("deviceMap");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("CiDevice"));

    emit EventFromMss("showCiAts");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("showCiAts"));

    emit EventFromMss("showCiZc");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("showCiZc"));

    emit EventFromMss("showCiVobc");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("showCiVobc"));

    emit EventFromMss("showCiAlarm");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("showCiAlarm"));
}

void TestCiWindow::testEventFromMap()
{
    connect(this,&TestCiWindow::EventFromMap,ci,&CiSystem::onEventFromMap);

    emit EventFromMap(1,"buttonCI");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("buttonCI\u0001"));

    emit EventFromMap(1,"buttonjidianqi");
    QTest::qWait(2000);
    QVERIFY(ci->hashTabWidget.contains("buttonjidianqi\u0001"));

}


void TestCiWindow::testTabClose()
{
    int count1=ci->tabWidget->count();
    ci->tabWidget->setCurrentIndex(1);
    ci->onTabClose(1);
    int count2=ci->tabWidget->count();
    QVERIFY(count1-count2==1);
}

void TestCiWindow::testSendEventToMss()
{
    QSignalSpy spy(ci,&CiSystem::sendEventToMss);
    ci->close();
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);
}

void TestCiWindow::testWindowDestroy()
{
    QVERIFY(ci->thread==NULL);
}

void TestCiWindow::cleanupTestCase()
{
}
