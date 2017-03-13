#ifndef TESTZCCI_H
#define TESTZCCI_H
#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "zcreaddata.h"
#include "zcmonitorci.h"
#include "ui_zcmonitorci.h"
#undef protected
#undef private

class TestZcCi : public QObject
{
     Q_OBJECT
public:
    TestZcCi();
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
    ZCMonitorCI *zcToCi;
};

#endif // TESTZCCI_H
