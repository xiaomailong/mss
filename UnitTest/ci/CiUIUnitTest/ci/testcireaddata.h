#ifndef TESTCIREADDATA_H
#define TESTCIREADDATA_H
#include <QtTest>

#define private public
#define protected public
#include "cireaddatathread.h"
#undef protected
#undef private


class TestCiReadData : public QObject
{
    Q_OBJECT
public:
    TestCiReadData();

signals:

private Q_SLOTS:
    void testDbConnection();
    void testGetDbData();
    void testCiAtsData();
    void testCiZcData();
    void testCiVobcData();
    void testCiAlarmData();

signals:
    void sendEventToRead(const QString tableName,const QString filter);
    void sendAlarmToRead(const QString id,const QString tableName,QString filter);

private:
    CiReadDataThread *readData;
};

#endif // TESTCIREADDATA_H
