#ifndef TESTCIMONITORATS_H
#define TESTCIMONITORATS_H

#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "cireaddatathread.h"
#include "cimonitorats.h"
#include "ui_cimonitorats.h"
#undef protected
#undef private

class TestCiMonitorAts : public QObject
{
    Q_OBJECT
public:
    TestCiMonitorAts();

signals:


private Q_SLOTS:
    void initTestCase();

    void testInitial();
    void testFindData();
    void testUpdateStatus();
    void testNextPage();
    void testLastPage();
    void testPerviousPage();
    void testFirstPage();

    void cleanupTestCase();

private:
    CiReadDataThread *readData;
    CiMonitorAts *ciAts;
};

#endif // TESTCIMONITORATS_H
