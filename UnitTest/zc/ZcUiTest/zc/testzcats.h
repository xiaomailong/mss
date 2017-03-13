#ifndef TESTZCATS_H
#define TESTZCATS_H
#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "zcreaddata.h"
#include "zcmonitorats.h"
#include "ui_zcmonitorats.h"
#undef protected
#undef private

class TestZcAts: public QObject
{
     Q_OBJECT
public:
    TestZcAts();
private Q_SLOTS:
    void zcInitTestCase();
    void zcTestInitial();
    void zcTestFindData();
    void testUpdateStatus();
    void zcTestNextbutton();
    void zcTestPerviouspage();
    void zcChangeToPage();
    void cleanZcTestCase();
private:
    ZCReadData *readData;
    ZCMonitorATS *zcToAts;
};

#endif // TESTZCATS_H
