#include "testcireaddata.h"
#include <QSqlDatabase>
#include <QSqlTableModel>

#define private public
#define protected public
#include "cireaddatathread.h"
#undef protected
#undef private

TestCiReadData::TestCiReadData()
{
    readData = new CiReadDataThread;
}

void TestCiReadData::testDbConnection()
{
    QSqlDatabase db=QSqlDatabase::database("CIatsconn");
    QVERIFY(db.isDriverAvailable("QMYSQL"));
    QVERIFY(db.isValid());
    QVERIFY(db.isOpen());
}

void TestCiReadData::testGetDbData()
{
    QSqlTableModel *model=readData->getModel("ci_ats_stationyard","");
    QVERIFY(model->rowCount()>0);
}

void TestCiReadData::testCiAtsData()
{
    QSignalSpy spy(readData,&CiReadDataThread::sendDataToCIAts);

    connect(this,&TestCiReadData::sendEventToRead,readData,&CiReadDataThread::DealFromCIAts);
    emit sendEventToRead("ci_ats_stationyard","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestCiReadData::testCiZcData()
{
    QSignalSpy spy(readData,&CiReadDataThread::sendDataToCIZc);

    connect(this,&TestCiReadData::sendEventToRead,readData,&CiReadDataThread::DealFromCIZc);
    emit sendEventToRead("ci_zc_approachunlock_req","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestCiReadData::testCiVobcData()
{
    QSignalSpy spy(readData,&CiReadDataThread::sendDataToCIVobc);

    connect(this,&TestCiReadData::sendEventToRead,readData,&CiReadDataThread::DealFromCIVobc);
    emit sendEventToRead("ci_vobc_data","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestCiReadData::testCiAlarmData()
{
    QSignalSpy spy(readData,&CiReadDataThread::sendDataToCIAlarm);

    connect(this,&TestCiReadData::sendAlarmToRead,readData,&CiReadDataThread::DealFromCIAlarm);
    emit sendAlarmToRead("aaaa","ci_ats_alarm","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QString id=arguments.at(0).toString();
    QSqlTableModel *model=arguments.at(1).value<QSqlTableModel *>();

    QVERIFY(id=="aaaa");
    QVERIFY(model->rowCount() >0);
}


