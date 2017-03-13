#include "cireaddatathread.h"
#include <QDebug>
#include <QThread>
#include <QSqlError>
#include "mssdbconfig.h"

CiReadDataThread::CiReadDataThread(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,"CIatsconn");
    db.setDatabaseName(MSS_DB_NAME);
    db.setHostName(MSS_DB_HOST_NAME);
    db.setPort(MSS_DB_PORT);
    db.setUserName(MSS_DB_USER);
    db.setPassword(MSS_DB_PASSWORD);

    if(!db.open())
    {
        return;
    }

}

QSqlTableModel *CiReadDataThread::getModel(const QString tableName, const QString filter)
{
    QSqlTableModel *model=new QSqlTableModel(this,db);
    model->setTable(tableName);
    model->setFilter(filter);
    model->select();
    return model;
}

void CiReadDataThread::DealFromCIAts(const QString tableName, const QString filter)
{
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToCIAts(model);
}

void CiReadDataThread::DealFromCIVobc(const QString tableName, const QString filter)
{
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToCIVobc(model);
}

void CiReadDataThread::DealFromCIZc(const QString tableName, const QString filter)
{
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToCIZc(model);
}

void CiReadDataThread::DealFromCIAlarm(const QString id, const QString tableName, const QString filter)
{
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToCIAlarm(id,model);
}
