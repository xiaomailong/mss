#include "testzcats.h"
#include <QPushButton>
#include <QDate>
#include <QDebug>
#define private public
#define protected public
#include "zcreaddata.h"
#include "zcmonitorats.h"
#include "ui_zcmonitorats.h"
#undef protected
#undef private
TestZcAts::TestZcAts()
{

}
void TestZcAts::zcInitTestCase()
{
    readData=new ZCReadData;
    zcToAts=new ZCMonitorATS(0,readData);
    zcToAts->show();
}
void TestZcAts::zcTestInitial()
{
    QTest::qWait(2000);
    QCOMPARE(zcToAts->packageIndex,0);
    QCOMPARE(zcToAts->totalPage,0);
    QCOMPARE(zcToAts->currentPage,1);
    QCOMPARE(zcToAts->PageRecordCount,100);
    QCOMPARE(zcToAts->totalRecrodCount,0);
    QVERIFY(zcToAts->model!=NULL);
}
void TestZcAts::zcTestFindData()
{
    zcToAts->startDateTime.setDate(QDate(2000,1,1));
    QPushButton *button=zcToAts->ui->queryButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(zcToAts, &ZCMonitorATS::sendEventToRead);
    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestZcAts::testUpdateStatus()
{
    QVERIFY(zcToAts->totalRecrodCount !=0);

    int totalCount=zcToAts->totalRecrodCount;
    if(totalCount % zcToAts->PageRecordCount ==0)
    {
        QVERIFY(totalCount/zcToAts->PageRecordCount==zcToAts->totalPage);
    }
    else
    {
        QVERIFY(totalCount/zcToAts->PageRecordCount ==(zcToAts->totalPage-1));
    }
    QVERIFY(zcToAts->model!=NULL);
}

void TestZcAts::zcTestNextbutton()
{
    QPushButton *nextbutton = zcToAts->ui->nextButton;
    QSignalSpy buttonspy(nextbutton,&QPushButton::clicked);
    QTest::mouseClick(nextbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if(zcToAts->totalPage>1)
    {
       QVERIFY(zcToAts->currentPage==2);
    }
    else
    {
        QVERIFY(zcToAts->currentPage == 1);
    }
}
void TestZcAts::zcTestPerviouspage()
{
    QPushButton *perbutton = zcToAts->ui->prevButton;
    QSignalSpy buttonspy(perbutton,&QPushButton::clicked);
    QTest::mouseClick(perbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if (zcToAts->totalPage>1){
       QVERIFY(zcToAts->currentPage == 1);
    }
    else
    {
       QVERIFY(zcToAts->currentPage==1);
    }
}

void TestZcAts::zcChangeToPage(){
   QPushButton *changebutton = zcToAts->ui->switchPageButton;
   QSignalSpy buttonspy(changebutton,&QPushButton::clicked);
   QLineEdit *changelabel = zcToAts->ui->switchPageLineEdit;
   QVERIFY(changelabel->text()==NULL);
   QTest::qWait(2000);
   QTest::mouseClick(changebutton,Qt::LeftButton);
   QVERIFY(changelabel->text()==NULL);
   QTest::qWait(2000);
   QVERIFY(buttonspy.count()==1);
}

void TestZcAts::cleanZcTestCase()
{
    zcToAts->close();
    delete zcToAts;
    delete readData;
}
