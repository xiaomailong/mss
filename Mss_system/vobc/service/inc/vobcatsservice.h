#ifndef VOBCATSSERVICE_H
#define VOBCATSSERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "vobc_data.h"
class VobcAtsService : public QObject
{
    Q_OBJECT
public:
    explicit VobcAtsService(QObject *parent = 0);
    ~VobcAtsService();

    void setInstFlag(bool);
signals:
    void reportAlarmMsg(vobc_subsys_msg_t atsMsg);
    void castError(int code);
    //requirement is not clear now
    //void StateMsg();
public slots:
    void handleAtsData(quint8 *buf, quint16 len);
    void startService();
    void stopService();
private:
    bool openDatabase();
    bool createTable(const QString &queryStr);
    void closeDatabase();
    bool insertData(EVobcTb tableName, void *data, void *rawData, quint16 length);
    inline void printDatabaseError();

    QSqlDatabase db;
    QSqlQuery query;
    QString connectName;
    bool isInstDisplay;
};

#endif // VOBCATSSERVICE_H
