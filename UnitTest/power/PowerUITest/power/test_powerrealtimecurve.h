#ifndef TEST_POWERREALTIMECURVE_H
#define TEST_POWERREALTIMECURVE_H
#define private public
#define protected public
#include "powerrealtimecurvewidget.h"
#include "powerreaddata.h"
#include "ui_powerrealtimecurvewidget.h"
#undef protected
#undef private
#include <QTest>
#include <QObject>
#include "powerdisplaychoicemodel.h"

class Test_PowerRealTimeCurve : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerRealTimeCurve(QObject *parent = 0);

signals:

public slots:
private :
    PowerReadData *readdata ;
    PowerRealTimeCurveWidget *realTimeCurve ;
    PowerDisplayChoiceModel *model ;
    Ui::PowerRealTimeCurveWidget *ui;
    QDate date;
private Q_SLOTS:
    void initTestCase();
    void testShowModel();
    void testQueryData();
};

#endif // TEST_POWERREALTIMECURVE_H
