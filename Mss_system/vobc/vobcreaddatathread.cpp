#include "vobcreaddatathread.h"
#include "vobcuicommon.h"
#include <QThread>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include "mssdbconfig.h"

VobcReadDataThread::VobcReadDataThread(QObject *parent) : QObject(parent)
{
    VOBC_DEBUG()<<"VobcReadDataThread::VobcReadDataThread:"<<QThread::currentThreadId();
    db =QSqlDatabase::database("vobcatsconn");
    if(!db.isValid())
    {
	    db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,"vobcatsconn");
	    db.setDatabaseName(MSS_DB_NAME);
	    db.setHostName(MSS_DB_HOST_NAME);
	    db.setPort(MSS_DB_PORT);
	    db.setUserName(MSS_DB_USER);
	    db.setPassword(MSS_DB_PASSWORD);

	    if(!db.open())
	    {
            VOBC_DEBUG()<<"db open fail"<<db.lastError().text();
	    }
	}
}

VobcReadDataThread::~VobcReadDataThread()
{
    //VOBC_DEBUG()<<"VobcReadDataThread::VobcReadDataThread disconstruct";
    db.close();
}

QSqlTableModel *VobcReadDataThread::getModel(const QString tableName, const QString filter)
{
    QSqlTableModel *model=new QSqlTableModel(this,db);
    model->setTable(tableName);
    model->setFilter(filter);
    model->select();
    return model;
}

void VobcReadDataThread::dealFromVOBCAts(const QString tableName,const QString filter)
{
    VOBC_DEBUG()<<"VobcReadDataThread::dealFromVOBCAts:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToVOBCAts(model);
    VOBC_DEBUG()<<"dealFromVOBCAts :"<<model->rowCount();
}

void VobcReadDataThread::dealFromVOBCCi(const QString tableName, const QString filter)
{
    VOBC_DEBUG()<<"VobcReadDataThread::dealFromVOBCCi:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToVOBCCi(model);
    VOBC_DEBUG()<<"dealFromVOBCCi :"<<model->rowCount();
}

void VobcReadDataThread::dealFromVOBCZc(const QString tableName, const QString filter)
{
    VOBC_DEBUG()<<"VobcReadDataThread::dealFromVOBCZc:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToVOBCZc(model);
    VOBC_DEBUG()<<"dealFromVOBCZc :"<<model->rowCount();
}

void VobcReadDataThread::dealFromVOBCAlarm(const QString id,const QString tableName, const QString filter)
{
    VOBC_DEBUG()<<"VobcReadDataThread::dealFromVOBCAlarm:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToVOBCAlarm(id,model);
    VOBC_DEBUG()<<"dealFromVOBCAlarm :"<<model->rowCount();
}
