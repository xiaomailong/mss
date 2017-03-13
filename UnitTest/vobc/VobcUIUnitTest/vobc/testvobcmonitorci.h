#ifndef TESTVOBCMONITORCI_H
#define TESTVOBCMONITORCI_H

#include <QtTest>
#include <QObject>
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcmonitorci.h"
#include "ui_vobcmonitorci.h"
#undef protected
#undef private

class TestVobcMonitorCi : public QObject
{
    Q_OBJECT
public:
    TestVobcMonitorCi();

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
    VobcMonitorCI *vobcCi;
};

#endif
