#ifndef VOBCREADDATATHREAD_H
#define VOBCREADDATATHREAD_H

#include <QObject>
#include <QSqlTableModel>

class VobcReadDataThread : public QObject
{
    Q_OBJECT
public:
    explicit VobcReadDataThread(QObject *parent = 0);
    ~VobcReadDataThread();
    QSqlTableModel *getModel(const QString tableName,const QString filter);

signals:
    void sendDataToVOBCAts(QSqlTableModel *model);
    void sendDataToVOBCCi(QSqlTableModel *model);
    void sendDataToVOBCZc(QSqlTableModel *model);
    void sendDataToVOBCAlarm(const QString id,QSqlTableModel *model);

public slots:
    void dealFromVOBCAts(const QString tableName,const QString filter);
    void dealFromVOBCCi(const QString tableName,const QString filter);
    void dealFromVOBCZc(const QString tableName,const QString filter);
    void dealFromVOBCAlarm(const QString id,const QString tableName,const QString filter);

private:
    QSqlDatabase db;
};

#endif // VOBCREADDATATHREAD_H
