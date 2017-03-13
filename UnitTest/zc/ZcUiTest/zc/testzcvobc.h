#ifndef TESTZCVOBC_H
#define TESTZCVOBC_H
#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "zcreaddata.h"
#include "zcmonitorvobc.h"
#include "ui_zcmonitorvobc.h"
#undef protected
#undef private

class TestZcVobc : public QObject
{
    Q_OBJECT
public:
    TestZcVobc();
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
    ZCMonitorVOBC *zcToVobc;
};

#endif // TESTZCVOBC_H
