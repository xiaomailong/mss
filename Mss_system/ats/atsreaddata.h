#ifndef ATSREADDATA_H
#define ATSREADDATA_H

#include <QObject>
#include <QSqlTableModel>

class AtsReadData : public QObject
{
    Q_OBJECT
public:
    explicit AtsReadData(QObject *parent = 0);
    QSqlTableModel *getModel(const QString tableName,const QString filter);

signals:
    void sendDataToAtsVobc(QSqlTableModel *model);
    void sendDataToAtsCi(QSqlTableModel *model);
    void sendDataToAtsZc(QSqlTableModel *model);
    void sendDataToAtsAlarm(const QString id,QSqlTableModel *model);

public slots:
     void DealFromAtsBovc(const QString tableName,const QString filter);
     void DealFromAtsCi(const QString tableName,const QString filter);
     void DealFromAtsZc(const QString tableName,const QString filter);
     void DealFromAtsAlarm(const QString id,const QString tableName,const QString filter);

private:
    QSqlDatabase db;
};

#endif // ATSREADDATA_H
