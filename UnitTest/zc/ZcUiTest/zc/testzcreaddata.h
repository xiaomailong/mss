#ifndef TESTZCREADDATA_H
#define TESTZCREADDATA_H

#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "zcreaddata.h"
#undef protected
#undef private

class TestZcReaddata: public QObject
{
    Q_OBJECT
public:
    TestZcReaddata();

private Q_SLOTS:
    void testDbConnection();
    void zcTestGetDbData();
    void testZcVobcData();
    void testZcCiData();
    void testZcAtsData();
    void testZcAlarmData();
signals:
    void sendEventToRead(const QString tableName,const QString filter);
    void sendAlarmToRead(const QString tableName,QString filter);


private :
    ZCReadData *readData;
};

#endif // TESTZCREADDATA_H
