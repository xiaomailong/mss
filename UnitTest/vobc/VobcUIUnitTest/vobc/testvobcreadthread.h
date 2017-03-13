#ifndef TESTVOBCREADTHREAD_H
#define TESTVOBCREADTHREAD_H

#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "vobcreaddatathread.h"
#undef protected
#undef private

class TestVobcReadThread : public QObject
{
    Q_OBJECT
public:
    TestVobcReadThread();

private Q_SLOTS:
    void testDbConnection();
    void testGetDbData();
    void testVobcAtsData();
    void testVobcCiData();
    void testVobcZcData();
    void testVobcAlarmData();

signals:
    void sendEventToRead(const QString tableName,const QString filter);
    void sendAlarmToRead(const QString id,const QString tableName,QString filter);

private:
    VobcReadDataThread *readData;
};

#endif // TESTVOBCREADTHREAD_H
