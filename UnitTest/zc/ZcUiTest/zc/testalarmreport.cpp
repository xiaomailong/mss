#include "testalarmreport.h"

#include <QPushButton>
#include <QDate>
#include <QDebug>
#define private public
#define protected public
#include "zcreaddata.h"
#include "zcdayreport.h"
#include "ui_zcdayreport.h"
#undef protected
#undef private

testAlarmReport::testAlarmReport()
{

}
void testAlarmReport::zcInitTestCase()
{
    readData=new ZCReadData;
    zcDayReport=new ZcDayReport(0,readData);
    zcDayReport->show();
}
void testAlarmReport::zcTestInitial()
{
    QTest::qWait(2000);
    QCOMPARE(zcDayReport->packageIndex,0);
    QCOMPARE(zcDayReport->totalPage,0);
    QCOMPARE(zcDayReport->currentPage,1);
    QCOMPARE(zcDayReport->totalRecrodCount,0);
    QVERIFY(zcDayReport->model!=NULL);
}
void testAlarmReport::zcTestFindData()
{
    zcDayReport->startDateTime.setDate(QDate(2000,1,1));

    QPushButton *button=zcDayReport->ui->queryButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(zcDayReport, &ZcDayReport::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void testAlarmReport::testUpdateStatus()
{
    QVERIFY(zcDayReport->totalRecrodCount !=0);

    int totalCount=zcDayReport->totalRecrodCount;
    if(totalCount % zcDayReport->PageRecordCount ==0)
    {
        QVERIFY(totalCount/zcDayReport->PageRecordCount==zcDayReport->totalPage);
    }
    else
    {
        QVERIFY(totalCount/zcDayReport->PageRecordCount ==(zcDayReport->totalPage-1));
    }
    QVERIFY(zcDayReport->model!=NULL);
}

void testAlarmReport::zcTestNextbutton(){

    QPushButton *nextbutton = zcDayReport->ui->nextButton;
    QSignalSpy buttonspy(nextbutton,&QPushButton::clicked);
    QTest::mouseClick(nextbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if(zcDayReport->totalPage>1)
    {
       QVERIFY(zcDayReport->currentPage==2);
    }
    else
    {
        QVERIFY(zcDayReport->currentPage == 1);
    }
}
void testAlarmReport::zcTestPerviouspage()
{
    QPushButton *perbutton = zcDayReport->ui->prevButton;
    QSignalSpy buttonspy(perbutton,&QPushButton::clicked);
    QTest::mouseClick(perbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);

    if (zcDayReport->totalPage>1)
    {
        QVERIFY(zcDayReport->currentPage==1);
    }
    else
    {
        QVERIFY(zcDayReport->currentPage==1);
    }
}

void testAlarmReport::zcChangeToPage(){
   QPushButton *changebutton = zcDayReport->ui->switchPageButton;
   QSignalSpy buttonspy(changebutton,&QPushButton::clicked);
   QLineEdit *changelabel = zcDayReport->ui->switchPageLineEdit;
   QVERIFY(changelabel->text()==NULL);
   QTest::qWait(2000);
   QTest::mouseClick(changebutton,Qt::LeftButton);
   QVERIFY(changelabel->text()==NULL);
   QTest::qWait(2000);
   QVERIFY(buttonspy.count()==1);
}

void testAlarmReport::cleanZcTestCase()
{
    zcDayReport->close();
    delete zcDayReport;
    delete readData;
}
