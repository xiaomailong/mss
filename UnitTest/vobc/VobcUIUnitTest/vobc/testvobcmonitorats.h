#ifndef TESTVOBCMONITORATS_H
#define TESTVOBCMONITORATS_H

#include <QtTest>
#include <QObject>
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcmonitorats.h"
#include "ui_vobcmonitorats.h"
#undef protected
#undef private

class TestVobcMonitorAts : public QObject
{
    Q_OBJECT
public:
    TestVobcMonitorAts();

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
    VobcReadDataThread *readData;
    VobcMonitorATS *vobcAts;
};

#endif
