#ifndef TESTATSMONITORVOBC_H
#define TESTATSMONITORVOBC_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "atsreaddata.h"
#include "atsmonitorvobc.h"
#undef protected
#undef private

class TestAtsMonitorVobc : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsMonitorVobc(QObject *parent = 0);

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
    AtsMonitorVobc *atsVobc;
};

#endif // TESTATSMONITORVOBC_H
