#include "testcimonitorvobc.h"
#include <QPushButton>
#include <QDate>

#define private public
#define protected public
#include "cireaddatathread.h"
#include "cimonitorvobc.h"
#include "ui_cimonitorvobc.h"
#undef protected
#undef private
TestCiMonitorVobc::TestCiMonitorVobc()
{

}

void TestCiMonitorVobc::initTestCase()
{
    readData=new CiReadDataThread;
    ciVobc=new CiMonitorVobc(0,readData);
    ciVobc->show();
}

void TestCiMonitorVobc::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(ciVobc->packageIndex,0);
    QCOMPARE(ciVobc->totalPage,0);
    QCOMPARE(ciVobc->currentPage,1);
    QCOMPARE(ciVobc->totalCount,0);
    QVERIFY(ciVobc->model==NULL);
}

void TestCiMonitorVobc::testFindData()
{
    ciVobc->beginDateTime.setDate(QDate(2000,1,1));

    QPushButton *button=ciVobc->ui->monitorButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(ciVobc, &CiMonitorVobc::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestCiMonitorVobc::testUpdateStatus()
{
    QVERIFY(ciVobc->totalCount != 0);

    int totalCount=ciVobc->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==ciVobc->totalPage);
    }else
    {
        QVERIFY(totalCount/100 ==(ciVobc->totalPage-1));
    }

    QVERIFY(ciVobc->model!=NULL);
}

void TestCiMonitorVobc::testNextPage()
{
    QPushButton *nextButton=ciVobc->ui->nextPage;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(nextButtonSpy.count() == 1);

    if(ciVobc->totalPage>1)
    {
        QVERIFY(ciVobc->currentPage == 2);
    }else if(ciVobc->totalPage<=1)
    {
        QVERIFY(ciVobc->currentPage == 1);
    }
}

void TestCiMonitorVobc::testLastPage()
{
    QPushButton *lastButton=ciVobc->ui->lastPageButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(ciVobc->totalPage>1)
    {
        QVERIFY(ciVobc->currentPage == ciVobc->totalPage);
    }else if(ciVobc->totalPage<=1)
    {
        QVERIFY(ciVobc->currentPage == 1);
    }
}

void TestCiMonitorVobc::testPerviousPage()
{
    QPushButton *perButton=ciVobc->ui->prevPage;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    QVERIFY(perButtonSpy.count() == 1);

    if(ciVobc->totalPage>1)
    {
        QVERIFY(ciVobc->currentPage == ciVobc->totalPage-1);
    }else
    {
        QVERIFY(ciVobc->currentPage == 1);
    }
}

void TestCiMonitorVobc::testFirstPage()
{
    QPushButton *firstButton=ciVobc->ui->firstPageButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(ciVobc->currentPage == 1);
}

void TestCiMonitorVobc::cleanupTestCase()
{
    ciVobc->close();
    delete ciVobc;
    delete readData;
}
