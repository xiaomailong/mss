#include <QPushButton>
#include <QDate>
#include "testatsmonitorvobc.h"

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsmonitorvobc.h"
#include "ui_atsmonitorvobc.h"
#undef protected
#undef private


TestAtsMonitorVobc::TestAtsMonitorVobc(QObject *parent) : QObject(parent)
{

}

void TestAtsMonitorVobc::initTestCase()
{
    readdata = new AtsReadData;
    atsVobc = new AtsMonitorVobc(0,readdata);
    atsVobc->show();
}

void TestAtsMonitorVobc::testInit()
{
    QTest::qWait(2000);
    QCOMPARE(atsVobc->packageIndex,0);
    QCOMPARE(atsVobc->totalPage,0);
    QCOMPARE(atsVobc->currentPage,1);
    QCOMPARE(atsVobc->totalCount,0);
}

void TestAtsMonitorVobc::testFindData()
{
    atsVobc->dateTime1.setDate(QDate(2000,1,1));
    QPushButton *button=atsVobc->ui->smonitor;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(atsVobc, &AtsMonitorVobc::sendEventToRead);
    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestAtsMonitorVobc::testUpdateStatus()
{
    QVERIFY(atsVobc->totalCount != 0);
    int totalCount=atsVobc->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==atsVobc->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(atsVobc->totalPage-1));
    }


    QVERIFY(atsVobc->model!=NULL);
}

void TestAtsMonitorVobc::testNextPage()
{
    QPushButton *nextButton=atsVobc->ui->nextbutton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }
    if(atsVobc->totalPage>1)
    {
        QVERIFY(atsVobc->currentPage == 2);
    }
    else if(atsVobc->totalPage<=1)
    {
        QVERIFY(atsVobc->currentPage == 1);
    }
}

void TestAtsMonitorVobc::testLastPage()
{
    QPushButton *lastButton=atsVobc->ui->lastbutton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);
    if(atsVobc->totalPage>1)
    {
        QVERIFY(atsVobc->currentPage == atsVobc->totalPage);
    }
    else if(atsVobc->totalPage<=1)
    {
        QVERIFY(atsVobc->currentPage == 1);
    }
}

void TestAtsMonitorVobc::testPerviousPage()
{
    QPushButton *perButton=atsVobc->ui->prebutton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);
    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }

    if(atsVobc->totalPage>1)
    {
        QVERIFY(atsVobc->currentPage == atsVobc->totalPage-1);
    }
    else
    {
        QVERIFY(atsVobc->currentPage == 1);
    }

}

void TestAtsMonitorVobc::testFirstPage()
{
    QPushButton *firstButton=atsVobc->ui->firstbutton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);
    QVERIFY(atsVobc->currentPage == 1);
}

void TestAtsMonitorVobc::cleanupTestCase()
{
    atsVobc->close();
    delete atsVobc;
    delete readdata;
}
