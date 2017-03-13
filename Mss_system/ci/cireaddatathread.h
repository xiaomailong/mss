#ifndef CIREADDATATHREAD_H
#define CIREADDATATHREAD_H

#include <QObject>
#include <QSqlTableModel>

class CiReadDataThread : public QObject
{
    Q_OBJECT
public:
    explicit CiReadDataThread(QObject *parent = 0);
    QSqlTableModel *getModel(const QString tableName,const QString filter);

signals:

    void sendDataToCIAts(QSqlTableModel *model);
    void sendDataToCIVobc(QSqlTableModel *model);
    void sendDataToCIZc(QSqlTableModel *model);
    void sendDataToCIAlarm(const QString id,QSqlTableModel *model);

public slots:

    void DealFromCIAts(const QString tableName,const QString filter);
    void DealFromCIVobc(const QString tableName,const QString filter);
    void DealFromCIZc(const QString tableName,const QString filter);
    void DealFromCIAlarm(const QString id,const QString tableName,const QString filter);

private:
    QSqlDatabase db;
};

#endif // CIREADDATATHREAD_H
