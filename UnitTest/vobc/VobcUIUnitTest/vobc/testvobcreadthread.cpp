#include "testvobcreadthread.h"
#include <QThread>
#include <QSqlDatabase>
#include <QSqlTableModel>

#define private public
#define protected public
#include "vobcreaddatathread.h"
#undef protected
#undef private

Q_DECLARE_METATYPE(QSqlTableModel *)

TestVobcReadThread::TestVobcReadThread()
{
    readData=new VobcReadDataThread;
}

void TestVobcReadThread::testDbConnection()
{
    QSqlDatabase db=QSqlDatabase::database("vobcatsconn");
    QVERIFY(db.isDriverAvailable("QMYSQL"));
    QVERIFY(db.isValid());
    QVERIFY(db.isOpen());
}

void TestVobcReadThread::testGetDbData()
{
    QSqlTableModel *model=readData->getModel("vobc_ats_ato","");
    QVERIFY(model->rowCount()>0);
}

void TestVobcReadThread::testVobcAtsData()
{
    QSignalSpy spy(readData,&VobcReadDataThread::sendDataToVOBCAts);

    connect(this,&TestVobcReadThread::sendEventToRead,readData,&VobcReadDataThread::dealFromVOBCAts);
    emit sendEventToRead("vobc_ats_ato","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);

}

void TestVobcReadThread::testVobcCiData()
{
    QSignalSpy spy(readData,&VobcReadDataThread::sendDataToVOBCCi);

    connect(this,&TestVobcReadThread::sendEventToRead,readData,&VobcReadDataThread::dealFromVOBCCi);
    emit sendEventToRead("vobc_ci","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestVobcReadThread::testVobcZcData()
{
    QSignalSpy spy(readData,&VobcReadDataThread::sendDataToVOBCZc);

    connect(this,&TestVobcReadThread::sendEventToRead,readData,&VobcReadDataThread::dealFromVOBCZc);
    emit sendEventToRead("vobc_zc_train","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestVobcReadThread::testVobcAlarmData()
{
    QSignalSpy spy(readData,&VobcReadDataThread::sendDataToVOBCAlarm);

    connect(this,&TestVobcReadThread::sendAlarmToRead,readData,&VobcReadDataThread::dealFromVOBCAlarm);
    emit sendAlarmToRead("aaaa","vobc_subsys_alarm","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QString id=arguments.at(0).toString();
    QSqlTableModel *model=arguments.at(1).value<QSqlTableModel *>();

    QVERIFY(id=="aaaa");
    QVERIFY(model->rowCount() >0);
}
