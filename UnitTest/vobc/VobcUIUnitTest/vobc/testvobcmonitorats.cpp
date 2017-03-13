#include <QPushButton>
#include <QDate>
#include "testvobcmonitorats.h"
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcmonitorats.h"
#include "ui_vobcmonitorats.h"
#undef protected
#undef private

TestVobcMonitorAts::TestVobcMonitorAts()
{

}

void TestVobcMonitorAts::initTestCase()
{
    readData=new VobcReadDataThread;
    vobcAts=new VobcMonitorATS(0,readData);
    vobcAts->show();
}

void TestVobcMonitorAts::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(vobcAts->packageIndex,0);
    QCOMPARE(vobcAts->totalPage,0);
    QCOMPARE(vobcAts->currentPage,1);
    QCOMPARE(vobcAts->totalCount,0);
}

void TestVobcMonitorAts::testFindData()
{
    vobcAts->dateTime1.setDate(QDate(2000,1,1));

    QPushButton *button=vobcAts->ui->findButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(vobcAts, &VobcMonitorATS::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestVobcMonitorAts::testUpdateStatus()
{
    QVERIFY(vobcAts->totalCount != 0);

    int totalCount=vobcAts->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==vobcAts->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(vobcAts->totalPage-1));
    }

    QVERIFY(vobcAts->model!=NULL);
}

void TestVobcMonitorAts::testNextPage()
{
    QPushButton *nextButton=vobcAts->ui->nextButton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }

    if(vobcAts->totalPage>1)
    {
        QVERIFY(vobcAts->currentPage == 2);
    }
    else if(vobcAts->totalPage<=1)
    {
        QVERIFY(vobcAts->currentPage == 1);
    }

}

void TestVobcMonitorAts::testLastPage()
{
    QPushButton *lastButton=vobcAts->ui->lastButton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);

    if(vobcAts->totalPage>1)
    {
        QVERIFY(vobcAts->currentPage == vobcAts->totalPage);
    }
    else if(vobcAts->totalPage<=1)
    {
        QVERIFY(vobcAts->currentPage == 1);
    }
}

void TestVobcMonitorAts::testPerviousPage()
{
    QPushButton *perButton=vobcAts->ui->perviousButton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);

    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }

    if(vobcAts->totalPage>1)
    {
        QVERIFY(vobcAts->currentPage == vobcAts->totalPage-1);
    }
    else
    {
        QVERIFY(vobcAts->currentPage == 1);
    }
}

void TestVobcMonitorAts::testFirstPage()
{
    QPushButton *firstButton=vobcAts->ui->firstButton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);

    QVERIFY(vobcAts->currentPage == 1);
}

void TestVobcMonitorAts::cleanupTestCase()
{
    vobcAts->close();
    delete vobcAts;
    delete readData;
}
