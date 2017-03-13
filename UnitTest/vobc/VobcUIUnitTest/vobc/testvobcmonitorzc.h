#ifndef TESTVOBCMONITORZC_H
#define TESTVOBCMONITORZC_H

#include <QtTest>
#include <QObject>
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcmonitorzc.h"
#include "ui_vobcmonitorzc.h"
#undef protected
#undef private

class TestVobcMonitorZC : public QObject
{
    Q_OBJECT
public:
    TestVobcMonitorZC();

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
    VobcMonitorZC *vobcZc;
};

#endif
