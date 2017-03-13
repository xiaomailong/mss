#ifndef TESTATSMONITORCI_H
#define TESTATSMONITORCI_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsmonitorci.h"
#undef protected
#undef private

class TestAtsMonitorCi : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsMonitorCi(QObject *parent = 0);

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
    AtsMonitorCi *atsCi;
};

#endif // TESTATSMONITORCI_H
