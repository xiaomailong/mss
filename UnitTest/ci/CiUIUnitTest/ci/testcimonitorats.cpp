#include "testcimonitorats.h"
#include <QPushButton>
#include <QDate>

#define private public
#define protected public
#include "cireaddatathread.h"
#include "cimonitorats.h"
#include "ui_cimonitorats.h"
#undef protected
#undef private

TestCiMonitorAts::TestCiMonitorAts()
{

}

void TestCiMonitorAts::initTestCase()
{
    readData=new CiReadDataThread;
    ciAts=new CiMonitorAts(0,readData);
    ciAts->show();
}

void TestCiMonitorAts::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(ciAts->packageIndex,0);
    QCOMPARE(ciAts->totalPage,0);
    QCOMPARE(ciAts->currentPage,1);
    QCOMPARE(ciAts->totalCount,0);
    QVERIFY(ciAts->model==NULL);
}

void TestCiMonitorAts::testFindData()
{
    ciAts->beginDateTime.setDate(QDate(2000,1,1));

    QPushButton *button=ciAts->ui->monitorButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(ciAts, &CiMonitorAts::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestCiMonitorAts::testUpdateStatus()
{
    QVERIFY(ciAts->totalCount != 0);

    int totalCount=ciAts->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==ciAts->totalPage);
    }else
    {
        QVERIFY(totalCount/100 ==(ciAts->totalPage-1));
    }

    QVERIFY(ciAts->model!=NULL);
}

void TestCiMonitorAts::testNextPage()
{
    QPushButton *nextButton=ciAts->ui->nextButton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);

    if(ciAts->totalPage>1)
    {
        QVERIFY(ciAts->currentPage == 2);
    }else if(ciAts->totalPage<=1)
    {
        QVERIFY(ciAts->currentPage == 1);
    }
}

void TestCiMonitorAts::testLastPage()
{
    QPushButton *lastButton=ciAts->ui->lastPageButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(ciAts->totalPage>1)
    {
        QVERIFY(ciAts->currentPage == ciAts->totalPage);
    }else if(ciAts->totalPage<=1)
    {
        QVERIFY(ciAts->currentPage == 1);
    }
}

void TestCiMonitorAts::testPerviousPage()
{
    QPushButton *preButton=ciAts->ui->prevButton;
    QSignalSpy preButtonSpy(preButton, &QPushButton::clicked);
    QTest::mouseClick(preButton,Qt::LeftButton);

    if(ciAts->totalPage>1)
    {
        QVERIFY(ciAts->currentPage == ciAts->totalPage-1);
    }else
    {
        QVERIFY(ciAts->currentPage == 1);
    }
}

void TestCiMonitorAts::testFirstPage()
{
    QPushButton *firstButton=ciAts->ui->firstPageButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(ciAts->currentPage == 1);
}

void TestCiMonitorAts::cleanupTestCase()
{
    ciAts->close();
    delete ciAts;
    delete readData;
}
