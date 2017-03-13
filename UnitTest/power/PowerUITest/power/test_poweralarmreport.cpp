#include "test_poweralarmreport.h"
#include <QObject>
#include <QPushButton>
#include <QDate>
Test_PowerAlarmReport::Test_PowerAlarmReport(QObject *parent) : QObject(parent)
{

}

void Test_PowerAlarmReport::initTestCase()
{
    readdata=new PowerReadData;
    alarmReport=new PowerAlarmSystem(0,readdata);
    alarmReport->show();
}

void Test_PowerAlarmReport::testInitial()
{
    QTest::qWait(2000);
    QCOMPARE(alarmReport->totalPage,0);
    QCOMPARE(alarmReport->currentPage,1);
    QCOMPARE(alarmReport->totalCount,0);
    QVERIFY(alarmReport->model==NULL);
}


void Test_PowerAlarmReport::testFindData()
{
    alarmReport->dateTime1.setDate(QDate(2000,1,1));

    QPushButton *button=alarmReport->ui->findButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(alarmReport, &PowerAlarmSystem::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    qDebug()<<"Test_PowerAlarmReport findSpy.count()"<<findSpy.count();
    QVERIFY(findSpy.count() == 2);

}
