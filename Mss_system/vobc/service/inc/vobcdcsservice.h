#ifndef VOBCDCSSERVICE_H
#define VOBCDCSSERVICE_H

#include <QObject>
#include <QtSql>
#include "vobc_data.h"

class VobcDcsService : public QObject
{
    Q_OBJECT
public:
    explicit VobcDcsService(QObject *parent = 0);
    ~VobcDcsService();

signals:
    void castError(int code);
public slots:
    void handleDcsData(quint8 *buf, quint16 len);
    //start & stop: run in self thread
    void startService();
    void stopService();
protected:
private:
    bool openDatabase();
    bool createTable(const QString &queryStr);
    void closeDatabase();
    bool insertData(EVobcTb tableName, void *data, void *rawData, quint16 length);
    inline void printDatabaseError();
    QSqlDatabase db;
    QSqlQuery query;
    QString connectName;
};

#endif // VOBCDCSSERVICE_H
