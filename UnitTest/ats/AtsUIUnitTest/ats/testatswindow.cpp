#include "testatswindow.h"

#include <QtTest>
#include <QHash>
#include <QSignalSpy>


#define private public
#define protected public
#include "atssystem.h"
#undef protected
#undef private

TestAtsWindow::TestAtsWindow(QObject *parent) : QObject(parent)
{

}

void TestAtsWindow::initTestCase()
{
     ats = new AtsSystem;
     ats->show();
}

void TestAtsWindow::testInit()
{
    QCOMPARE(ats->hashTabWidget.size(),0);
    QVERIFY(ats->atsTabWidget!=NULL);
    QVERIFY(ats->readData!=NULL);
    QVERIFY(ats->thread!=NULL);
}

void TestAtsWindow::testEventFromMss()
{
    connect(this,&TestAtsWindow::EventFromMss,ats,&AtsSystem::onEventFormMss);

    emit EventFromMss("ATSdeviceMap");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("atsDevice"));

    emit EventFromMss("showAtsVobc");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("showAtsVobc"));

    emit EventFromMss("showAtsZc");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("showAtsZc"));

    emit EventFromMss("showAtsCi");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("showAtsCi"));

    emit EventFromMss("showAtsAlarm");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("showAtsAlarm"));
}

void TestAtsWindow::testEventFromMap()
{
    connect(this,&TestAtsWindow::EventFromMap,ats,&AtsSystem::onEventFromMap);

    emit EventFromMap(1,"display_edit");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("display_edit\u0001"));

    emit EventFromMap(2,"dispatcher");
    QTest::qWait(2000);
    QVERIFY(ats->hashTabWidget.contains("dispatcher\u0002"));
}

void TestAtsWindow::testTabClose()
{
    int count1=ats->atsTabWidget->count();
    ats->atsTabWidget->setCurrentIndex(1);
    ats->onTabClose(1);
    int count2=ats->atsTabWidget->count();
    QVERIFY(count1-count2==1);
}

void TestAtsWindow::testSendEventToMss()
{
    QSignalSpy spy(ats,&AtsSystem::sendEventToMss);
    ats->close();
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);
}

void TestAtsWindow::testWindowDestroy()
{
    QVERIFY(ats->thread==NULL);
}

void TestAtsWindow::cleanupTestCase()
{

}
