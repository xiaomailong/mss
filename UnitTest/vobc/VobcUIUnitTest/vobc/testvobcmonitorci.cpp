#include <QPushButton>
#include <QDate>
#include "testvobcmonitorci.h"
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcmonitorci.h"
#include "ui_vobcmonitorci.h"
#undef protected
#undef private

TestVobcMonitorCi::TestVobcMonitorCi()
{

}

void TestVobcMonitorCi::initTestCase()
{
    readData=new VobcReadDataThread;
    vobcCi=new VobcMonitorCI(0,readData);
    vobcCi->show();
}

void TestVobcMonitorCi::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(vobcCi->packageIndex,0);
    QCOMPARE(vobcCi->totalPage,0);
    QCOMPARE(vobcCi->currentPage,1);
    QCOMPARE(vobcCi->totalCount,0);
}

void TestVobcMonitorCi::testFindData()
{
    vobcCi->dateTime1.setDate(QDate(2000,1,1));

    QPushButton *button=vobcCi->ui->findButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(vobcCi, &VobcMonitorCI::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestVobcMonitorCi::testUpdateStatus()
{
    QVERIFY(vobcCi->totalCount != 0);

    int totalCount=vobcCi->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==vobcCi->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(vobcCi->totalPage-1));
    }

    QVERIFY(vobcCi->model!=NULL);
}

void TestVobcMonitorCi::testNextPage()
{
    QPushButton *nextButton=vobcCi->ui->nextButton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }

    if(vobcCi->totalPage>1)
    {
        QVERIFY(vobcCi->currentPage == 2);
    }
    else if(vobcCi->totalPage<=1)
    {
        QVERIFY(vobcCi->currentPage == 1);
    }

}

void TestVobcMonitorCi::testLastPage()
{
    QPushButton *lastButton=vobcCi->ui->lastButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(vobcCi->totalPage>1)
    {
        QVERIFY(vobcCi->currentPage == vobcCi->totalPage);
    }
    else if(vobcCi->totalPage<=1)
    {
        QVERIFY(vobcCi->currentPage == 1);
    }
}

void TestVobcMonitorCi::testPerviousPage()
{
    QPushButton *perButton=vobcCi->ui->perviousButton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }

    if(vobcCi->totalPage>1)
    {
        QVERIFY(vobcCi->currentPage == vobcCi->totalPage-1);
    }
    else
    {
        QVERIFY(vobcCi->currentPage == 1);
    }
}

void TestVobcMonitorCi::testFirstPage()
{
    QPushButton *firstButton=vobcCi->ui->firstButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(vobcCi->currentPage == 1);
}

void TestVobcMonitorCi::cleanupTestCase()
{
    vobcCi->close();
    delete vobcCi;
    delete readData;
}
