#include <QPushButton>
#include <QDate>
#include "testvobcalarmreport.h"
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcalarmreport.h"
#include "ui_vobcalarmreport.h"
#undef protected
#undef private

TestVobcAlarmReport::TestVobcAlarmReport()
{

}

void TestVobcAlarmReport::initTestCase()
{
    readData=new VobcReadDataThread;
    vobcAlarm=new VobcAlarmReport(0,readData);
    vobcAlarm->show();
}

void TestVobcAlarmReport::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(vobcAlarm->totalPage,0);
    QCOMPARE(vobcAlarm->currentPage,1);
    QCOMPARE(vobcAlarm->totalCount,0);
}

void TestVobcAlarmReport::testFindData()
{
    vobcAlarm->dateTime1.setDate(QDate(2000,1,1));

    QPushButton *button=vobcAlarm->ui->findButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(vobcAlarm, &VobcAlarmReport::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestVobcAlarmReport::testUpdateStatus()
{
    QVERIFY(vobcAlarm->totalCount != 0);

    int totalCount=vobcAlarm->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==vobcAlarm->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(vobcAlarm->totalPage-1));
    }

    QVERIFY(vobcAlarm->model!=NULL);
}

void TestVobcAlarmReport::testNextPage()
{
    QPushButton *nextButton=vobcAlarm->ui->nextButton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }

    if(vobcAlarm->totalPage>1)
    {
        QVERIFY(vobcAlarm->currentPage == 2);
    }
    else if(vobcAlarm->totalPage<=1)
    {
        QVERIFY(vobcAlarm->currentPage == 1);
    }

}

void TestVobcAlarmReport::testLastPage()
{
    QPushButton *lastButton=vobcAlarm->ui->lastButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(vobcAlarm->totalPage>1)
    {
        QVERIFY(vobcAlarm->currentPage == vobcAlarm->totalPage);
    }
    else if(vobcAlarm->totalPage<=1)
    {
        QVERIFY(vobcAlarm->currentPage == 1);
    }
}

void TestVobcAlarmReport::testPerviousPage()
{
    QPushButton *perButton=vobcAlarm->ui->perviousButton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }

    if(vobcAlarm->totalPage>1)
    {
        QVERIFY(vobcAlarm->currentPage == vobcAlarm->totalPage-1);
    }
    else
    {
        QVERIFY(vobcAlarm->currentPage == 1);
    }
}

void TestVobcAlarmReport::testFirstPage()
{
    QPushButton *firstButton=vobcAlarm->ui->firstButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(vobcAlarm->currentPage == 1);
}

void TestVobcAlarmReport::cleanupTestCase()
{
    vobcAlarm->close();
    delete vobcAlarm;
    delete readData;
}
