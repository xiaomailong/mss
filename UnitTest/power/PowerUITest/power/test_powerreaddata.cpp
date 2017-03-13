#include "test_powerreaddata.h"
#include <QString>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "power/ui/powerrealtimecurvewidget.h"
Test_PowerReadData::Test_PowerReadData(QObject *parent) : QObject(parent)
{
  readData = new PowerReadData();

}

void Test_PowerReadData::testDbConnection()
{
    QSqlDatabase db=QSqlDatabase::database("POWERDB");
    QVERIFY(db.isDriverAvailable("QMYSQL"));
    QVERIFY(db.isValid());
    QVERIFY(db.isOpen());
}

void Test_PowerReadData::testGetDbData()
{
    QString query ="SELECT devicename, voltage,current,frequency savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    QSqlQueryModel *model=readData->getQueryModel(query);
    QVERIFY(model->rowCount()>0);
}



void Test_PowerReadData::testRealTimeCurve()
{
    QSignalSpy spy(readData,&PowerReadData::sendDataToPowerRealTime);
    connect(this,&Test_PowerReadData::sendEventToRead,readData,&PowerReadData::DealFromPowerRealTimeCurve);
    QString query ="SELECT devicename, voltage,current,frequency ,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    emit sendEventToRead(query);

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlQueryModel *model=arguments.at(0).value<QSqlQueryModel *>();
    QVERIFY(model->rowCount() >0);

}




void Test_PowerReadData::testDayReport()
{
    QSignalSpy spy(readData,&PowerReadData::sendDataToDayReport);
    connect(this,&Test_PowerReadData::sendEventToRead,readData,&PowerReadData::DealFromDayReport);
    QString query ="SELECT devicename, voltage,current,frequency ,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle ";
    date=QDate::currentDate();
    query.append(QString("AND savetime>='%1' ").arg(date.toString("yyyy-MM-dd")));
    emit sendEventToRead(query);

    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments=spy.takeFirst();
    QSqlQueryModel *model=arguments.at(0).value<QSqlQueryModel *>();
    QVERIFY(model->rowCount() >=0);

}
