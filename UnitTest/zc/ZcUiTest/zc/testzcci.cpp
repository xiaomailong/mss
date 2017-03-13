#include "testzcci.h"
#include <QPushButton>
#include <QDate>
#include <QDebug>
#define private public
#define protected public
#include "zcreaddata.h"
#include "zcmonitorci.h"
#include "ui_zcmonitorci.h"
#undef protected
#undef private

TestZcCi::TestZcCi()
{

}
void TestZcCi::zcInitTestCase()
{
    readData=new ZCReadData;
    zcToCi=new ZCMonitorCI(0,readData);
    zcToCi->show();
}
void TestZcCi::zcTestInitial()
{
    QTest::qWait(2000);
    QCOMPARE(zcToCi->packageIndex,0);
    QCOMPARE(zcToCi->totalPage,0);
    QCOMPARE(zcToCi->currentPage,1);
    QCOMPARE(zcToCi->PageRecordCount,100);
    QCOMPARE(zcToCi->totalRecrodCount,0);
    QVERIFY(zcToCi->model!=NULL);
}
void TestZcCi::zcTestFindData()
{
    zcToCi->startDateTime.setDate(QDate(2000,1,1));
    QPushButton *button=zcToCi->ui->queryButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(zcToCi, &ZCMonitorCI::sendEventToRead);
    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestZcCi::testUpdateStatus()
{
    QVERIFY(zcToCi->totalRecrodCount !=0);
    int totalCount=zcToCi->totalRecrodCount;
    if(totalCount % zcToCi->PageRecordCount ==0)
    {
        QVERIFY(totalCount/zcToCi->PageRecordCount==zcToCi->totalPage);
    }
    else
    {
        QVERIFY(totalCount/zcToCi->PageRecordCount ==(zcToCi->totalPage-1));
    }
    QVERIFY(zcToCi->model!=NULL);
}

void TestZcCi::zcTestNextbutton()
{
    QPushButton *nextbutton = zcToCi->ui->nextButton;
    QSignalSpy buttonspy(nextbutton,&QPushButton::clicked);
    QTest::mouseClick(nextbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if(zcToCi->totalPage>1)
    {
       QVERIFY(zcToCi->currentPage==2);
    }
    else
    {
       QVERIFY(zcToCi->currentPage == 1);
    }
}
void TestZcCi::zcTestPerviouspage()
{
    QPushButton *perbutton = zcToCi->ui->prevButton;
    QSignalSpy buttonspy(perbutton,&QPushButton::clicked);
    QTest::mouseClick(perbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if(zcToCi->totalPage>1)
    {
       QVERIFY(zcToCi->currentPage == 1);
    }
    else
    {
       QVERIFY(zcToCi->currentPage==1);
    }
}

void TestZcCi::zcChangeToPage(){
    QPushButton *changebutton = zcToCi->ui->switchPageButton;
    QSignalSpy buttonspy(changebutton,&QPushButton::clicked);
    QLineEdit *changelabel = zcToCi->ui->switchPageLineEdit;
    QVERIFY(changelabel->text()==NULL);
    QTest::qWait(2000);
    QTest::mouseClick(changebutton,Qt::LeftButton);
    QVERIFY(changelabel->text()==NULL);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
}

void TestZcCi::cleanZcTestCase()
{
    zcToCi->close();
    delete zcToCi;
    delete readData;
}
