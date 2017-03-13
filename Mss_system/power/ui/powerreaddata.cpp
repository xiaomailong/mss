#include "powerreaddata.h"
#include "mssdbconfig.h"
#include<QDebug>
#include<QThread>
#include <QSqlError>
PowerReadData::PowerReadData(QObject *parent) : QObject(parent)
{
    qDebug()<<"PowerReadData::PowerReadData:"<<QThread::currentThreadId();

    db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,"POWER");
    db.setDatabaseName(MSS_DB_NAME);
    db.setHostName(MSS_DB_HOST_NAME);
    db.setPort(MSS_DB_PORT);
    db.setUserName(MSS_DB_USER);
    db.setPassword(MSS_DB_PASSWORD);

    if(!db.open())
    {
        qDebug()<<"db open fail"<<db.lastError().text();
        return;
    }

}


QSqlQueryModel *PowerReadData::getQueryModel( const QString &query)
{
    QSqlQueryModel *model=new QSqlQueryModel(this);
    model->setQuery(query,db);
    return model;
}


void PowerReadData::DealFromPowerRealTimeCurve(const QString &query)
{
    qDebug()<<"PowerReadData::DealFromPowerRealTimeCurve:"<<QThread::currentThreadId() <<"query:"<<query;
    QSqlQueryModel *model=getQueryModel(query);
    emit sendDataToPowerRealTime(model);
    qDebug()<<"DealFromPowerRealTimeCurve :"<<model->rowCount();
}


void PowerReadData::DealFromDayReport(const QString &query)
{
    qDebug()<<"PowerReadData::DealFromDayReport:"<<QThread::currentThreadId() <<"query:"<<query;
    QSqlQueryModel *model=getQueryModel(query);
    emit sendDataToDayReport(model);
    qDebug()<<"DealFromDayReport :"<<model->rowCount();
}



void PowerReadData::DealFromPowerCommonCurve(const QString &query)
{
    qDebug()<<"PowerReadData::DealFromPowerCommonCurve:"<<QThread::currentThreadId();
    QSqlQueryModel *model=getQueryModel(query);
    emit sendDataToPowerCommonCurve(model);
    qDebug()<<"DealFromPowerCommonCurve :"<<model->rowCount();
}



void PowerReadData::DealFromPowerAlarm(const QString id, const QString filter)
{
    QString query ="SELECT devicename, voltage,current,frequency , savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle AND ";
    query.append(filter);
    qDebug()<<"PowerReadData::DealFromPowerAlarm:"<<QThread::currentThreadId();
    QSqlQueryModel *model=getQueryModel(query);
    emit sendDataToPowerAlarmReport(id,model);
    qDebug()<<"DealFromPowerCommonCurve :"<<model->rowCount();
}
