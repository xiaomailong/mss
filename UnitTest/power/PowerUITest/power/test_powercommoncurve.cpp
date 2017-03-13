#include "test_powercommoncurve.h"
#include <QSignalSpy>
#include <QPushButton>
#include <QDebug>

Test_PowerCommonCurve::Test_PowerCommonCurve(QObject *parent) : QObject(parent)
{

}

void Test_PowerCommonCurve::initTestCase()
{
    model = new PowerDisplayChoiceModel(this);
    readdata=new PowerReadData;
    powerCommonCurve=new PowerCommonCurveWidget(0,readdata);
    powerCommonCurve->show();

}



void Test_PowerCommonCurve::testQueryData(){
    date=QDate::currentDate();

    QPushButton *button=powerCommonCurve->ui->queryButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(powerCommonCurve, &PowerCommonCurveWidget::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    qDebug()<<"zwz Test_PowerRealTimeCurve findSpy.count()="<<findSpy.count();
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 1);
}
