#ifndef TEST_POWERALARMREPORT_H
#define TEST_POWERALARMREPORT_H
#include <QtTest>
#define private public
#define protected public
#include "powerreaddata.h"
#include "poweralarmsystem.h"
#include "ui_poweralarmsystem.h"
#undef protected
#undef private
class Test_PowerAlarmReport : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerAlarmReport(QObject *parent = 0);

signals:

public slots:
private:
    PowerReadData *readdata ;
    PowerAlarmSystem *alarmReport ;
private Q_SLOTS:
    void initTestCase();
    void testInitial();
    void testFindData();
};

#endif // TEST_POWERALARMREPORT_H
