#ifndef TEST_POWERCOMMONCURVE_H
#define TEST_POWERCOMMONCURVE_H
#define private public
#define protected public
#include "powercommoncurvewidget.h"
#include "powerreaddata.h"
#include "ui_powercommoncurvewidget.h"
#undef protected
#undef private
#include <QTest>
#include <QObject>
#include "powerdisplaychoicemodel.h"

class Test_PowerCommonCurve : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerCommonCurve(QObject *parent = 0);

signals:

public slots:
private :
    PowerReadData *readdata ;
    PowerCommonCurveWidget *powerCommonCurve ;
    PowerDisplayChoiceModel *model ;
    Ui::PowerCommonCurveWidget *ui;
    QDate date;
private Q_SLOTS:
    void initTestCase();
    //void testShowModel();
    void testQueryData();
};

#endif // TEST_POWERCOMMONCURVE_H
