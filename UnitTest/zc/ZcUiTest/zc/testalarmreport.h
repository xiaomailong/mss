#ifndef TESTALARMREPORT_H
#define TESTALARMREPORT_H
#include <QtTest>
#include <QObject>

#define private public
#define protected public
#include "zcreaddata.h"
#include "zcdayreport.h"
#include "ui_zcdayreport.h"
#undef protected
#undef private

class testAlarmReport: public QObject
{
     Q_OBJECT
public:
    testAlarmReport();
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
    ZcDayReport *zcDayReport;
};

#endif // TESTALARMREPORT_H
