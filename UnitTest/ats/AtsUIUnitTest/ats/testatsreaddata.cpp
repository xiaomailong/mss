#include "testatsreaddata.h"

#include <QThread>
#include <QSqlDatabase>
#include <QSqlTableModel>

#define private public
#define protected public
#include "atsreaddata.h"
#undef protected
#undef private

Q_DECLARE_METATYPE(QSqlTableModel *)


TestAtsReadData::TestAtsReadData(QObject *parent) : QObject(parent)
{
    readData = new AtsReadData;
}

void TestAtsReadData::testDbConnection()
{
    QSqlDatabase db=QSqlDatabase::database("atsconn");
    QVERIFY(db.isDriverAvailable("QMYSQL"));
    QVERIFY(db.isOpen());
}

void TestAtsReadData::testGetDbData()
{
    QSqlTableModel *model=readData->getModel("ats_vobc_heartbeat","");
    QVERIFY(model->rowCount()>0);
}

void TestAtsReadData::testAtsVobcData()
{
    QSignalSpy spy(readData,&AtsReadData::sendDataToAtsVobc);

    connect(this,&TestAtsReadData::sendEventToRead,readData,&AtsReadData::DealFromAtsBovc);
    emit sendEventToRead("ats_vobc_heartbeat","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestAtsReadData::testAtsZcData()
{

    QSignalSpy spy(readData,&AtsReadData::sendDataToAtsZc);

    connect(this,&TestAtsReadData::sendEventToRead,readData,&AtsReadData::DealFromAtsZc);
    emit sendEventToRead("ats_zc_heartbeat","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestAtsReadData::testAtsCiData()
{
    QSignalSpy spy(readData,&AtsReadData::sendDataToAtsCi);

    connect(this,&TestAtsReadData::sendEventToRead,readData,&AtsReadData::DealFromAtsCi);
    emit sendEventToRead("ats_ci_heartbeat","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlTableModel *model=arguments.at(0).value<QSqlTableModel *>();
    QVERIFY(model->rowCount() >0);
}

void TestAtsReadData::testAtsAlarmData()
{
    QSignalSpy spy(readData,&AtsReadData::sendDataToAtsAlarm);

    connect(this,&TestAtsReadData::sendAlarmToRead,readData,&AtsReadData::DealFromAtsAlarm);
    emit sendAlarmToRead("abc","ats_mss_alarm","");

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QString id=arguments.at(0).toString();
    QSqlTableModel *model=arguments.at(1).value<QSqlTableModel *>();

    QVERIFY(id=="abc");
    QVERIFY(model->rowCount() >0);
}
