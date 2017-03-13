#ifndef TESTCIMONITORVOBC_H
#define TESTCIMONITORVOBC_H
#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "cireaddatathread.h"
#include "cimonitorvobc.h"
#include "ui_cimonitorvobc.h"
#undef protected
#undef private

class TestCiMonitorVobc : public QObject
{
    Q_OBJECT
public:
    TestCiMonitorVobc();

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
    CiMonitorVobc *ciVobc;
};

#endif // TESTCIMONITORVOBC_H
