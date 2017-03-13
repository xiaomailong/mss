#include "test_powerrealtimecurve.h"
#include <QSignalSpy>
#include <QPushButton>
#include <QDebug>


Test_PowerRealTimeCurve::Test_PowerRealTimeCurve(QObject *parent) : QObject(parent)
{

}
void Test_PowerRealTimeCurve::initTestCase()
{
    model = new PowerDisplayChoiceModel(this);
    readdata=new PowerReadData;
    realTimeCurve=new PowerRealTimeCurveWidget(0,readdata);
    realTimeCurve->show();

}


void Test_PowerRealTimeCurve::testShowModel(){
    //QVERIFY(dayport->model->rowCount()==4);

    connect(realTimeCurve,&PowerRealTimeCurveWidget::sendEventToRead,readdata,&PowerReadData::DealFromPowerRealTimeCurve);
    connect(readdata,&PowerReadData::sendDataToDayReport,realTimeCurve,&PowerRealTimeCurveWidget::OnGetData);
    QString query = "SELECT devicename, voltage,current,type,frequency ,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    realTimeCurve->getRealTimeData(query);
    //QSignalSpy ReceivedSpy1(realTimeCurve,&PowerRealTimeCurveWidget::OnGetData);
    realTimeCurve->allChecked();
    //qDebug()<<"realTimeCurve->sqlTablemodel->columnCount()"<<realTimeCurve->sqlTablemodel->columnCount();
    //QVERIFY(realTimeCurve->sqlTablemodel->columnCount()>=4);
    for(int i =0;i<4;i++){
        //QModelIndex *index = new QModelIndex ;
        QModelIndex index=model->index(i,0,QModelIndex());
        QVariant checkstate = model->data(index,Qt::CheckStateRole);
        QVERIFY(checkstate==Qt::Checked);
    }
}


void Test_PowerRealTimeCurve::testQueryData(){
    date=QDate::currentDate();

    QPushButton *button=realTimeCurve->ui->queryButton;
    QSignalSpy buttonSpy(button, &QPushButton::clicked);
    QSignalSpy findSpy(realTimeCurve, &PowerRealTimeCurveWidget::sendEventToRead);

    QTest::mouseClick(button,Qt::LeftButton);
    QTest::qWait(2000);
    qDebug()<<"zwz Test_PowerRealTimeCurve findSpy.count()="<<findSpy.count();
    QVERIFY(buttonSpy.count() == 1);
    QVERIFY(findSpy.count() == 1);
}
