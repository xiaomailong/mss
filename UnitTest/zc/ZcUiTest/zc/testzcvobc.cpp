#include "testzcvobc.h"
#include <QPushButton>
#include <QDate>
#include <QDebug>
#define private public
#define protected public
#include "zcreaddata.h"
#include "zcmonitorvobc.h"
#include "ui_zcmonitorvobc.h"
#undef protected
#undef private
TestZcVobc::TestZcVobc()
{

}
void TestZcVobc::zcInitTestCase()
{
    readData=new ZCReadData;
    zcToVobc=new ZCMonitorVOBC(0,readData);
    zcToVobc->show();
}
void TestZcVobc::zcTestInitial()
{
    QTest::qWait(2000);
    QCOMPARE(zcToVobc->packageIndex,0);
    QCOMPARE(zcToVobc->totalPage,0);
    QCOMPARE(zcToVobc->PageRecordCount,100);
    QCOMPARE(zcToVobc->currentPage,1);
    QCOMPARE(zcToVobc->totalRecrodCount,0);
    QVERIFY(zcToVobc->model!=NULL);
}
void TestZcVobc::zcTestFindData()
{
    zcToVobc->startDateTime.setDate(QDate(2000,1,1));

    QPushButton *button=zcToVobc->ui->queryButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(zcToVobc, &ZCMonitorVOBC::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 2);
}

void TestZcVobc::testUpdateStatus()
{
    QVERIFY(zcToVobc->totalRecrodCount !=0);

    int totalCount=zcToVobc->totalRecrodCount;
    if(totalCount % zcToVobc->PageRecordCount ==0)
    {
        QVERIFY(totalCount/zcToVobc->PageRecordCount==zcToVobc->totalPage);
    }
    else
    {
        QVERIFY(totalCount/zcToVobc->PageRecordCount ==(zcToVobc->totalPage-1));
    }
    QVERIFY(zcToVobc->model!=NULL);
}

void TestZcVobc::zcTestNextbutton()
{
    QPushButton *nextbutton = zcToVobc->ui->nextButton;
    QSignalSpy buttonspy(nextbutton,&QPushButton::clicked);
    QTest::mouseClick(nextbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if(zcToVobc->totalPage>1)
    {
       QVERIFY(zcToVobc->currentPage==2);
    }
    else
    {
       QVERIFY(zcToVobc->currentPage == 1);
    }
}
void TestZcVobc::zcTestPerviouspage(){
    QPushButton *perbutton = zcToVobc->ui->prevButton;
    QSignalSpy buttonspy(perbutton,&QPushButton::clicked);
    QTest::mouseClick(perbutton,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count()==1);
    if(zcToVobc->totalPage>1)
    {
        QVERIFY(zcToVobc->currentPage == 1);
    }
    else
    {
        QVERIFY(zcToVobc->currentPage==1);
    }
}

void TestZcVobc::zcChangeToPage(){
   QPushButton *changebutton = zcToVobc->ui->switchPageButton;
   QSignalSpy buttonspy(changebutton,&QPushButton::clicked);
   QLineEdit *changelabel = zcToVobc->ui->switchPageLineEdit;
   QVERIFY(changelabel->text()==NULL);
   QTest::qWait(2000);
   QTest::mouseClick(changebutton,Qt::LeftButton);
   QVERIFY(changelabel->text()==NULL);
   QTest::qWait(2000);
   QVERIFY(buttonspy.count()==1);
}

void TestZcVobc::cleanZcTestCase()
{
    zcToVobc->close();
    delete zcToVobc;
    delete readData;
}
