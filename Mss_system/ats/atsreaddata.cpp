#include "atsreaddata.h"
#include <QDebug>
#include <QThread>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include "mssdbconfig.h"

#define ATS_DEBUG_ENABLED 0

#if ATS_DEBUG_ENABLED
#define ATS_DEBUG       qDebug
#define ATS_INFO        qInfo
#define ATS_WARN        qWarning
#define ATS_FATAL       qFatal
#define ATS_CRITICAL       qCritical
#else
#define ATS_DEBUG       QT_NO_QDEBUG_MACRO
#define ATS_INFO        QT_NO_QDEBUG_MACRO
#define ATS_WARN        QT_NO_QDEBUG_MACRO
#define ATS_FATAL       QT_NO_QDEBUG_MACRO
#define ATS_CRITICAL    QT_NO_QDEBUG_MACRO
#endif

AtsReadData::AtsReadData(QObject *parent) : QObject(parent)
{
    ATS_DEBUG()<<"AtsReadData:current thread id : "<<QThread::currentThreadId();
    db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,"atsconn");
    db.setDatabaseName(MSS_DB_NAME);
    db.setHostName(MSS_DB_HOST_NAME);
    db.setUserName(MSS_DB_USER);
    db.setPassword(MSS_DB_PASSWORD);
    if(!db.open())
    {
        ATS_DEBUG()<<"db open fail"<<db.lastError().text();
        return;
    }
}

QSqlTableModel *AtsReadData::getModel(const QString tableName, const QString filter)
{
    QSqlTableModel *model=new QSqlTableModel(this,db);
    model->setTable(tableName);
    model->setFilter(filter);
    model->select();
    return model;
}

void AtsReadData::DealFromAtsBovc(const QString tableName,const QString filter)
{
    //ATS_DEBUG()<<"AtsReadData::DealFromATSBovc:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToAtsVobc(model);
    //ATS_DEBUG()<<"DealFromATSBovc :"<<model->rowCount();
}

void AtsReadData::DealFromAtsCi(const QString tableName,const QString filter)
{
    //ATS_DEBUG()<<"AtsReadData::DealFromATSCi:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToAtsCi(model);
    //ATS_DEBUG()<<"DealFromATSBovc :"<<model->rowCount();
}

void AtsReadData::DealFromAtsZc(const QString tableName,const QString filter)
{
    //ATS_DEBUG()<<"AtsReadData::DealFromATSZc:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToAtsZc(model);
    //ATS_DEBUG()<<"DealFromATSBovc :"<<model->rowCount();
}

void AtsReadData::DealFromAtsAlarm(const QString id,const QString tableName, const QString filter)
{
    //ATS_DEBUG()<<"AtsReadData::DealFromATSAlarm:"<<QThread::currentThreadId()<<"table:"<<tableName<<" filter:"<<filter;
    QSqlTableModel *model=getModel(tableName,filter);
    emit sendDataToAtsAlarm(id,model);
    //ATS_DEBUG()<<"DealFromATSAlarm :"<<model->rowCount();
}


