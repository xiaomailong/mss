#include "testcimonitorzc.h"

TestCiMonitorZc::TestCiMonitorZc()
{

}

void TestCiMonitorZc::initTestCase()
{
    readData=new CiReadDataThread;
    ciZc=new CiMonitorZc(0,readData);
    ciZc->show();
}

void TestCiMonitorZc::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(ciZc->packageIndex,0);
    QCOMPARE(ciZc->totalPage,0);
    QCOMPARE(ciZc->currentPage,1);
    QCOMPARE(ciZc->totalCount,0);
    QVERIFY(ciZc->model==NULL);
}

void TestCiMonitorZc::testFindData()
{
    ciZc->beginDateTime.setDate(QDate(2000,1,1));

    QPushButton *button=ciZc->ui->monitorButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(ciZc, &CiMonitorZc::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestCiMonitorZc::testUpdateStatus()
{
    QVERIFY(ciZc->totalCount != 0);

    int totalCount=ciZc->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==ciZc->totalPage);
    }else
    {
        QVERIFY(totalCount/100 ==(ciZc->totalPage-1));
    }

    QVERIFY(ciZc->model!=NULL);
}

void TestCiMonitorZc::testNextPage()
{
    QPushButton *nextButton=ciZc->ui->nextPage;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(nextButtonSpy.count() == 1);

    if(ciZc->totalPage>1)
    {
        QVERIFY(ciZc->currentPage == 2);
    }else if(ciZc->totalPage<=1)
    {
        QVERIFY(ciZc->currentPage == 1);
    }
}

void TestCiMonitorZc::testLastPage()
{
    QPushButton *lastButton=ciZc->ui->lastPageButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(ciZc->totalPage>1)
    {
        QVERIFY(ciZc->currentPage == ciZc->totalPage);
    }else if(ciZc->totalPage<=1)
    {
        QVERIFY(ciZc->currentPage == 1);
    }
}

void TestCiMonitorZc::testPerviousPage()
{
    QPushButton *perButton=ciZc->ui->prevPage;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    QVERIFY(perButtonSpy.count() == 1);

    if(ciZc->totalPage>1)
    {
        QVERIFY(ciZc->currentPage == ciZc->totalPage-1);
    }else
    {
        QVERIFY(ciZc->currentPage == 1);
    }
}

void TestCiMonitorZc::testFirstPage()
{
    QPushButton *firstButton=ciZc->ui->firstPageButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(ciZc->currentPage == 1);
}

void TestCiMonitorZc::cleanupTestCase()
{
    ciZc->close();
    delete ciZc;
    delete readData;
}
