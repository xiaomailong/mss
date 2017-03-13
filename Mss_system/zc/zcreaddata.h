#ifndef ZCREADDATA_H
#define ZCREADDATA_H

#include <QObject>
#include <QSqlTableModel>
class ZCReadData : public QObject
{
    Q_OBJECT
public:
    explicit ZCReadData(QObject *parent = 0);
    QSqlTableModel *getModel(const QString tableName,const QString filter); //get table model

signals:
    void sendDataToZCAts(QSqlTableModel *model);
    void sendDataToZCVobc(QSqlTableModel *model);
    void sendDataToZCCi(QSqlTableModel *model);
    void sendDataToZCAlarm(QSqlTableModel *model);
public slots:
    void DealFromZCAts(const QString tableName,const QString filter);
    void DealFromZCVobc(const QString tableName,const QString filter);
    void DealFromZCCi(const QString tableName,const QString filter);
    void DealFromZCAlarm(const QString tableName,const QString filter);
private :
    QSqlDatabase db;
};

#endif // ZCREADDATA_H
