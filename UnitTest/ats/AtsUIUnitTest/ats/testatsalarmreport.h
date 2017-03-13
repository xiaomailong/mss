#ifndef TESTATSALARMREPORT_H
#define TESTATSALARMREPORT_H

#include <QObject>
#include <QtTest>
#include <atsreaddata.h>

#define private public
#define protected public
#include "atsalarmreport.h"
#include "ui_atsalarmreport.h"
#undef protected
#undef private


class TestAtsAlarmReport : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsAlarmReport(QObject *parent = 0);

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
    AtsAlarmReport *atsAlarm;
};

#endif // TESTATSALARMREPORT_H
