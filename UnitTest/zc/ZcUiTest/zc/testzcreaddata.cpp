#include "testzcreaddata.h"
#include <QThread>
#include <QSqlDatabase>
#include <QSqlTableModel>

#define private public
#define protected public
#include "zcreaddata.h"
#undef protected
#undef private
Q_DECLARE_METATYPE(QSqlTableModel *)

TestZcReaddata::TestZcReaddata()
{
    readData = new ZCReadData;
}
void TestZcReaddata::testDbConnection()
{
    QSqlDatabase db=QSqlDatabase::database("zcuiconn");
    QVERIFY(db.isDriverAvailable("QMYSQL"));
    QVERIFY(db.isValid());
    QVERIFY(db.isOpen());
}
void TestZcReaddata::zcTestGetDbData()
{
    QSqlTableModel *model=readData->getModel("zc_ci_ls","");
    QVERIFY(model->rowCount()>0);
}
void TestZcReaddata::testZcVobcData()
{
    QSignalSpy spy(readData,&ZCReadData::sendDataToZCVobc);

    connect(this,&TestZcReaddata::sendEventToRead,readData,&ZCReadData::DealFromZCVobc);
    emit sendEventToRead("zc_vobc_tc","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);

}
void TestZcReaddata::testZcCiData()
{
    QSignalSpy spy(readData,&ZCReadData::sendDataToZCCi);

    connect(this,&TestZcReaddata::sendEventToRead,readData,&ZCReadData::DealFromZCCi);
    emit sendEventToRead("zc_ci_sp","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}
void TestZcReaddata::testZcAtsData()
{
    QSignalSpy spy(readData,&ZCReadData::sendDataToZCAts);

    connect(this,&TestZcReaddata::sendEventToRead,readData,&ZCReadData::DealFromZCAts);
    emit sendEventToRead("zc_ci_sp","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}
void TestZcReaddata::testZcAlarmData()
{
    QSignalSpy spy(readData,&ZCReadData::sendDataToZCAlarm);
    connect(this,&TestZcReaddata::sendAlarmToRead,readData,&ZCReadData::DealFromZCAlarm);
    emit sendAlarmToRead("zc_monitor","");
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);
}
