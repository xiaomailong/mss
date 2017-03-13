#ifndef TESTCIMONITORZC_H
#define TESTCIMONITORZC_H

#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "cireaddatathread.h"
#include "cimonitorzc.h"
#include "ui_cimonitorzc.h"
#undef protected
#undef private

class TestCiMonitorZc : public QObject
{
    Q_OBJECT
public:
    TestCiMonitorZc();

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
    CiMonitorZc *ciZc;
};

#endif // TESTCIMONITORZC_H
