#include <QPushButton>
#include <QDate>
#include "testatsmonitorci.h"

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsmonitorci.h"
#include "ui_atsmonitorci.h"
#undef protected
#undef private


TestAtsMonitorCi::TestAtsMonitorCi(QObject *parent) : QObject(parent)
{

}

void TestAtsMonitorCi::initTestCase()
{
    readdata = new AtsReadData;
    atsCi = new AtsMonitorCi(0,readdata);
    atsCi->show();
}

void TestAtsMonitorCi::testInit()
{
    QTest::qWait(2000);
    QCOMPARE(atsCi->packageIndex,0);
    QCOMPARE(atsCi->totalPage,0);
    QCOMPARE(atsCi->currentPage,1);
    QCOMPARE(atsCi->totalCount,0);
}

void TestAtsMonitorCi::testFindData()
{
    atsCi->dateTime1.setDate(QDate(2000,1,1));
    QPushButton *button=atsCi->ui->pushButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(atsCi, &AtsMonitorCi::sendEventToRead);
    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);

}

void TestAtsMonitorCi::testUpdateStatus()
{
    QVERIFY(atsCi->totalCount != 0);
    int totalCount=atsCi->totalCount;
    if(totalCount % 100 ==0)
    {
        QVERIFY(totalCount/100==atsCi->totalPage);
    }
    else
    {
        QVERIFY(totalCount/100 ==(atsCi->totalPage-1));
    }
    QVERIFY(atsCi->model!=NULL);
}

void TestAtsMonitorCi::testNextPage()
{
    QPushButton *nextButton=atsCi->ui->nextbutton;
    QSignalSpy nextButtonSpy(nextButton, &QPushButton::clicked);
    QTest::mouseClick(nextButton,Qt::LeftButton);
    QTest::qWait(2000);
    if(nextButton->isEnabled())
    {
        QVERIFY(nextButtonSpy.count() == 1);
    }
    if(atsCi->totalPage>1)
    {
        QVERIFY(atsCi->currentPage == 2);
    }
    else if(atsCi->totalPage<=1)
    {
        QVERIFY(atsCi->currentPage == 1);
    }
}

void TestAtsMonitorCi::testLastPage()
{
    QPushButton *lastButton=atsCi->ui->lastbutton;
    QSignalSpy lastButtonSpy(lastButton, &QPushButton::clicked);
    QTest::mouseClick(lastButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(lastButtonSpy.count() == 1);
    if(atsCi->totalPage>1)
    {
        QVERIFY(atsCi->currentPage == atsCi->totalPage);
    }
    else if(atsCi->totalPage<=1)
    {
        QVERIFY(atsCi->currentPage == 1);
    }
}

void TestAtsMonitorCi::testPerviousPage()
{
    QPushButton *perButton=atsCi->ui->prebutton;
    QSignalSpy perButtonSpy(perButton, &QPushButton::clicked);
    QTest::mouseClick(perButton,Qt::LeftButton);
    if(perButton->isEnabled())
    {
        QVERIFY(perButtonSpy.count() == 1);
    }

    if(atsCi->totalPage>1)
    {
        QVERIFY(atsCi->currentPage == atsCi->totalPage-1);
    }
    else
    {
        QVERIFY(atsCi->currentPage == 1);
    }
}

void TestAtsMonitorCi::testFirstPage()
{
    QPushButton *firstButton=atsCi->ui->firstbutton;
    QSignalSpy firstButtonSpy(firstButton, &QPushButton::clicked);
    QTest::mouseClick(firstButton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(firstButtonSpy.count() == 1);
    QVERIFY(atsCi->currentPage == 1);
}

void TestAtsMonitorCi::cleanupTestCase()
{
    atsCi->close();
    delete atsCi;
    delete readdata;
}
