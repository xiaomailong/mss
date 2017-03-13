#ifndef TESTATSREADDATA_H
#define TESTATSREADDATA_H

#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "atsreaddata.h"
#undef protected
#undef private

class TestAtsReadData : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsReadData(QObject *parent = 0);

private Q_SLOTS:
    void testDbConnection();
    void testGetDbData();
    void testAtsVobcData();
    void testAtsZcData();
    void testAtsCiData();
    void testAtsAlarmData();

signals:
    void sendEventToRead(const QString tableName,const QString filter);
    void sendAlarmToRead(const QString id,const QString tableName,QString filter);

private:
    AtsReadData *readData;
};

#endif // TESTATSREADDATA_H
