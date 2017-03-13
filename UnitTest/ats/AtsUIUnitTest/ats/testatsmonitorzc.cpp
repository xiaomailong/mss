#include <QPushButton>
#include <QDate>
#include "testatsmonitorzc.h"

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsmonitorzc.h"
#include "ui_atsmonitorzc.h"
#undef protected
#undef private

TestAtsMonitorZc::TestAtsMonitorZc(QObject *parent) : QObject(parent)
{

}


void TestAtsMonitorZc::initTestCase()
{
    readdata = new AtsReadData;
    atsZc = new AtsMonitorZc(0,readdata);
    atsZc->show();
}

void TestAtsMonitorZc::testInit()
{
    QTest::qWait(2000);
    QCOMPARE(atsZc->packageIndex,0);
    QCOMPARE(atsZc->totalPage,0);
    QCOMPARE(atsZc->currentPage,1);
    QCOMPARE(atsZc->totalCount,0);
}

void TestAtsMonitorZc::testFindData()
{
    atsZc->dateTime1.setDate(QDate(2000,1,1));
    QPushButton *button=atsZc->ui->startmonitor;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(atsZc, &AtsMonitorZc::sendEventToRead);
    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestAtsMonitorZc::testUpdateStatus()
{
    QVERIFY(atsZc->totalCount != 0);
    int totalCount=atsZc->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==atsZc->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(atsZc->totalPage-1));
    }
    QVERIFY(atsZc->model!=NULL);
}

void TestAtsMonitorZc::testNextPage()
{
    QPushButton *nextButton=atsZc->ui->nextbutton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }
    if(atsZc->totalPage>1)
    {
        QVERIFY(atsZc->currentPage == 2);
    }
    else if(atsZc->totalPage<=1)
    {
        QVERIFY(atsZc->currentPage == 1);
    }
}

void TestAtsMonitorZc::testLastPage()
{
    QPushButton *lastButton=atsZc->ui->lastbutton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);
    if(atsZc->totalPage>1)
    {
        QVERIFY(atsZc->currentPage == atsZc->totalPage);
    }
    else if(atsZc->totalPage<=1)
    {
        QVERIFY(atsZc->currentPage == 1);
    }
}

void TestAtsMonitorZc::testPerviousPage()
{
    QPushButton *perButton=atsZc->ui->prebutton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);
    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }
    if(atsZc->totalPage>1)
    {
        QVERIFY(atsZc->currentPage == atsZc->totalPage-1);
    }
    else
    {
        QVERIFY(atsZc->currentPage == 1);
    }
}

void TestAtsMonitorZc::testFirstPage()
{
    QPushButton *firstButton=atsZc->ui->firstbutton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);
    QVERIFY(atsZc->currentPage == 1);
}

void TestAtsMonitorZc::cleanupTestCase()
{
    atsZc->close();
    delete atsZc;
    delete readdata;
}
