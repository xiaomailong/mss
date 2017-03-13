#ifndef TESTCIALARMREPORT_H
#define TESTCIALARMREPORT_H

#include <QObject>
#include <QtTest>
#include "cireaddatathread.h"

#define private public
#define protected public
#include "cialarmreport.h"
#include "ui_cialarmreport.h"
#undef protected
#undef private

class TestCiAlarmReport : public QObject
{
    Q_OBJECT
public:
    TestCiAlarmReport();

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
    CiAlarmReport *reportWidget;


};

#endif // TESTCIALARMREPORT_H
