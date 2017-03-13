#include "zcreaddata.h"
#include <QDebug>
#include <QThread>
#include <QSqlError>
#include "mssdbconfig.h"

ZCReadData::ZCReadData(QObject *parent) : QObject(parent)
{
      db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,"zcuiconn");//add MySql driver
      db.setHostName(MSS_DB_HOST_NAME);//hostname
      db.setPort(MSS_DB_PORT);//port
      db.setUserName(MSS_DB_USER);
      db.setPassword(MSS_DB_PASSWORD);
      db.setDatabaseName(MSS_DB_NAME);//database name
      if( db.open() )
      {
          qDebug()<<"Succeed to connected db!";
      }
      else
      {
          qDebug()<<"Failed to connected db!";
          db.close();
      }
}

QSqlTableModel *ZCReadData::getModel(const QString tableName, const QString filter)
{
    QSqlTableModel *model=new QSqlTableModel(this,db);
    model->setTable(tableName);
    model->setFilter(filter);
    model->select();
    return model;
}
//receive message from ats and return model to ats
void ZCReadData::DealFromZCAts(const QString tableName, const QString filter)
{
    //qDebug()<<"ZCReadData::DealFromZCAts:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToZCAts(model);
    //qDebug()<<"DealFromZCAts :"<<model->rowCount();
}
//receive message from ats and return model to vobc
void ZCReadData::DealFromZCVobc(const QString tableName, const QString filter)
{
    //qDebug()<<"ZCReadData::DealFromZCVobc:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToZCVobc(model);
    //qDebug()<<"DealFromZCVobc :"<<model->rowCount();
}
//receive message from ats and return model to ci
void ZCReadData::DealFromZCCi(const QString tableName, const QString filter)
{
    //qDebug()<<"ZCReadData::DealFromZCCi:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToZCCi(model);
    //qDebug()<<"DealFromZCCi :"<<model->rowCount();
}
//receive message from ats and return model to alarm
void ZCReadData::DealFromZCAlarm(const QString tableName, const QString filter)
{
    //qDebug()<<"ZCReadData::DealFromZCAlarm:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToZCAlarm(model);
    //qDebug()<<"DealFromZCAlarm :"<<model->rowCount();
}
