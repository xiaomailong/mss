#include <QPushButton>
#include <QDate>
#include "testvobcmonitorzc.h"
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcmonitorzc.h"
#include "ui_vobcmonitorzc.h"
#undef protected
#undef private

TestVobcMonitorZC::TestVobcMonitorZC()
{

}

void TestVobcMonitorZC::initTestCase()
{
    readData=new VobcReadDataThread;
    vobcZc=new VobcMonitorZC(0,readData);
    vobcZc->show();
}

void TestVobcMonitorZC::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(vobcZc->packageIndex,0);
    QCOMPARE(vobcZc->totalPage,0);
    QCOMPARE(vobcZc->currentPage,1);
    QCOMPARE(vobcZc->totalCount,0);
}

void TestVobcMonitorZC::testFindData()
{
    vobcZc->dateTime1.setDate(QDate(2000,1,1));

    QPushButton *button=vobcZc->ui->findButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(vobcZc, &VobcMonitorZC::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestVobcMonitorZC::testUpdateStatus()
{
    QVERIFY(vobcZc->totalCount != 0);

    int totalCount=vobcZc->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==vobcZc->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(vobcZc->totalPage-1));
    }

    QVERIFY(vobcZc->model!=NULL);
}

void TestVobcMonitorZC::testNextPage()
{
    QPushButton *nextButton=vobcZc->ui->nextButton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }

    if(vobcZc->totalPage>1)
    {
        QVERIFY(vobcZc->currentPage == 2);
    }
    else if(vobcZc->totalPage<=1)
    {
        QVERIFY(vobcZc->currentPage == 1);
    }

}

void TestVobcMonitorZC::testLastPage()
{
    QPushButton *lastButton=vobcZc->ui->lastButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(vobcZc->totalPage>1)
    {
        QVERIFY(vobcZc->currentPage == vobcZc->totalPage);
    }
    else if(vobcZc->totalPage<=1)
    {
        QVERIFY(vobcZc->currentPage == 1);
    }
}

void TestVobcMonitorZC::testPerviousPage()
{
    QPushButton *perButton=vobcZc->ui->perviousButton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }

    if(vobcZc->totalPage>1)
    {
        QVERIFY(vobcZc->currentPage == vobcZc->totalPage-1);
    }
    else
    {
        QVERIFY(vobcZc->currentPage == 1);
    }
}

void TestVobcMonitorZC::testFirstPage()
{
    QPushButton *firstButton=vobcZc->ui->firstButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(vobcZc->currentPage == 1);
}

void TestVobcMonitorZC::cleanupTestCase()
{
    vobcZc->close();
    delete vobcZc;
    delete readData;
}
