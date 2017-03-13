#ifndef POWERREADDATA_H
#define POWERREADDATA_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
class PowerReadData : public QObject
{
    Q_OBJECT
public:
    explicit PowerReadData(QObject *parent = 0);
    QSqlQueryModel *getQueryModel(  const QString &query);

signals:
    void sendDataToPowerRealTime(QSqlQueryModel *model);
    void sendDataToDayReport(QSqlQueryModel *model);
    void sendDataToPowerCommonCurve(QSqlQueryModel *model);
    void sendDataToPowerAlarmReport(const QString id,QSqlQueryModel *tableModel);
public slots:
     void DealFromPowerRealTimeCurve(const QString &query);
     void DealFromDayReport(const QString &query);
     void DealFromPowerCommonCurve(const QString &query);
     void DealFromPowerAlarm(const QString id, const QString filter);

private:
    QSqlDatabase db;
};

#endif // POWERREADDATA_H
