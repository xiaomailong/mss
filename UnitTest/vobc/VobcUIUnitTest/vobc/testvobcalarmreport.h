#ifndef TESTVOBCALARMREPORT_H
#define TESTVOBCALARMREPORT_H

#include <QtTest>
#include <QObject>
#include "vobcreaddatathread.h"

#define private public
#define protected public
#include "vobcalarmreport.h"
#include "ui_vobcalarmreport.h"
#undef protected
#undef private

class TestVobcAlarmReport : public QObject
{
    Q_OBJECT
public:
    TestVobcAlarmReport();

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
    VobcAlarmReport *vobcAlarm;
};

#endif
