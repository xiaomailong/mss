#include "testcialarmreport.h"
#include "cireaddatathread.h"
#include <QSignalSpy>
#include <QTest>

#define private public
#define protected public
#include "cialarmreport.h"
#include "ui_cialarmreport.h"
#undef protected
#undef private

TestCiAlarmReport::TestCiAlarmReport()
{

}

void TestCiAlarmReport::initTestCase()
{
    readData=new CiReadDataThread;
    reportWidget =new CiAlarmReport(0,readData);
    reportWidget->show();
}

void TestCiAlarmReport::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(reportWidget->totalPage,0);
    QCOMPARE(reportWidget->currentPage,1);
    QCOMPARE(reportWidget->totalCount,0);
    QVERIFY(reportWidget->model==NULL);
}

void TestCiAlarmReport::testFindData()
{
    reportWidget->beginDateTime.setDate(QDate(2000,1,1));

    QPushButton *button=reportWidget->ui->monitorButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(reportWidget, &CiAlarmReport::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestCiAlarmReport::testUpdateStatus()
{
    QVERIFY(reportWidget->totalCount != 0);

    int totalCount=reportWidget->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==reportWidget->totalPage);
    }else
    {
        QVERIFY(totalCount/100 ==(reportWidget->totalPage-1));
    }

    QVERIFY(reportWidget->model!=NULL);
}

void TestCiAlarmReport::testNextPage()
{
    QPushButton *nextButton=reportWidget->ui->nextPage;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(nextButtonSpy.count() == 1);

    if(reportWidget->totalPage>1)
    {
        QVERIFY(reportWidget->currentPage == 2);
    }else if(reportWidget->totalPage<=1)
    {
        QVERIFY(reportWidget->currentPage == 1);
    }
}

void TestCiAlarmReport::testLastPage()
{
    QPushButton *lastButton=reportWidget->ui->lastPage;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(reportWidget->totalPage>1)
    {
        QVERIFY(reportWidget->currentPage == reportWidget->totalPage);
    }else if(reportWidget->totalPage<=1)
    {
        QVERIFY(reportWidget->currentPage == 1);
    }
}

void TestCiAlarmReport::testPerviousPage()
{
    QPushButton *perButton=reportWidget->ui->prevPage;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    QVERIFY(perButtonSpy.count() == 1);

    if(reportWidget->totalPage>1)
    {
        QVERIFY(reportWidget->currentPage == reportWidget->totalPage-1);
    }else
    {
        QVERIFY(reportWidget->currentPage == 1);
    }
}

void TestCiAlarmReport::testFirstPage()
{
    QPushButton *firstButton=reportWidget->ui->firstPage;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(reportWidget->currentPage == 1);
}

void TestCiAlarmReport::cleanupTestCase()
{
    reportWidget->close();
    delete reportWidget;
    delete readData;
}
