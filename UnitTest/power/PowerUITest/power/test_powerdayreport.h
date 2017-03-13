#ifndef TEST_POWERDAYREPORT_H
#define TEST_POWERDAYREPORT_H

#include <QObject>
#define private public
#define protected public
#include "powerdayreport.h"
#include "powerdisplaychoicemodel.h"
#undef protected
#undef private
#include <QTest>
class Test_PowerDayReport : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerDayReport(QObject *parent = 0);

signals:

public slots:

private Q_SLOTS:
   void initTestCase();
   void testShowModel();

private:
    PowerDayReport *dayport;
    PowerDisplayChoiceModel *model ;
    PowerReadData *readdata;
    Ui::PowerDayReport *ui;
};

#endif // TEST_POWERDAYREPORT_H
