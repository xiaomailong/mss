#include <QPushButton>
#include <QDate>
#include "testatsalarmreport.h"

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsalarmreport.h"
#include "ui_atsalarmreport.h"
#undef protected
#undef private

TestAtsAlarmReport::TestAtsAlarmReport(QObject *parent) : QObject(parent)
{

}

void TestAtsAlarmReport::initTestCase()
{
    readdata=new AtsReadData;
    atsAlarm=new AtsAlarmReport(0,readdata);
    atsAlarm->show();
}

void TestAtsAlarmReport::testInit()
{
    QTest::qWait(2000);
    QCOMPARE(atsAlarm->totalPage,0);
    QCOMPARE(atsAlarm->currentPage,1);
    QCOMPARE(atsAlarm->totalCount,0);
}

void TestAtsAlarmReport::testFindData()
{
    atsAlarm->dateTime1.setDate(QDate(2000,1,1));
    QPushButton *button=atsAlarm->ui->findbutton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(atsAlarm, &AtsAlarmReport::sendEventToRead);
    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestAtsAlarmReport::testUpdateStatus()
{
    QVERIFY(atsAlarm->totalCount != 0);

    int totalCount=atsAlarm->totalCount;
    if(totalCount % 100 ==0){
        QVERIFY(totalCount/100==atsAlarm->totalPage);
    }else{
        QVERIFY(totalCount/100 ==(atsAlarm->totalPage-1));
    }

    QVERIFY(atsAlarm->model!=NULL);
}

void TestAtsAlarmReport::testNextPage()
{
    QPushButton *nextButton=atsAlarm->ui->nextbutton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }
    if(atsAlarm->totalPage>1)
    {
        QVERIFY(atsAlarm->currentPage == 2);
    }
    else if(atsAlarm->totalPage<=1)
    {
        QVERIFY(atsAlarm->currentPage == 1);
    }
}

void TestAtsAlarmReport::testLastPage()
{
    QPushButton *lastButton=atsAlarm->ui->lastbutton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);
    if(atsAlarm->totalPage>1)
    {
        QVERIFY(atsAlarm->currentPage == atsAlarm->totalPage);
    }
    else if(atsAlarm->totalPage<=1)
    {
        QVERIFY(atsAlarm->currentPage == 1);
    }
}

void TestAtsAlarmReport::testPerviousPage()
{
    QPushButton *perButton=atsAlarm->ui->prebutton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);
    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }
    if(atsAlarm->totalPage>1)
    {
        QVERIFY(atsAlarm->currentPage == atsAlarm->totalPage-1);
    }
    else
    {
        QVERIFY(atsAlarm->currentPage == 1);
    }
}

void TestAtsAlarmReport::testFirstPage()
{
    QPushButton *firstButton=atsAlarm->ui->firstbutton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);
    QVERIFY(atsAlarm->currentPage == 1);
}

void TestAtsAlarmReport::cleanupTestCase()
{
    atsAlarm->close();
    delete atsAlarm;
    delete readdata;
}
