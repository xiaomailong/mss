#ifndef TESTATSMONITORZC_H
#define TESTATSMONITORZC_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsmonitorzc.h"
#undef protected
#undef private

class TestAtsMonitorZc : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsMonitorZc(QObject *parent = 0);

private Q_SLOTS:
    void initTestCase();
    void testInit();
    void testFindData();
    void testUpdateStatus();
    void testNextPage();
    void testLastPage();
    void testPerviousPage();
    void testFirstPage();
    void cleanupTestCase();

private:
    AtsReadData *readdata;
    AtsMonitorZc *atsZc;
};

#endif // TESTATSMONITORZC_H
