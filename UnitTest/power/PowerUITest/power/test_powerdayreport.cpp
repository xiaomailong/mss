#include "test_powerdayreport.h"
#include "powerreaddata.h"
#include "powerdayreport.h"
#include <QSignalSpy>
Test_PowerDayReport::Test_PowerDayReport(QObject *parent) : QObject(parent)
{

}



void Test_PowerDayReport::initTestCase()
{
    model = new PowerDisplayChoiceModel(this);
    readdata=new PowerReadData;
    dayport=new PowerDayReport(0,readdata);
    dayport->show();

}

void Test_PowerDayReport::testShowModel()
{
    //QVERIFY(dayport->model->rowCount()==4);

    connect(dayport,&PowerDayReport::sendEventToRead,readdata,&PowerReadData::DealFromDayReport);
    connect(readdata,&PowerReadData::sendDataToDayReport,dayport,&PowerDayReport::OnGetData);
    dayport->getDayReportData();
    QSignalSpy ReceivedSpy1(dayport,&PowerDayReport::OnGetData);
    dayport->allChecked();
    qDebug()<<"dayport->sqlTablemodel->columnCount()"<<dayport->sqlTablemodel->columnCount();
    QVERIFY(dayport->sqlTablemodel->columnCount()>=4);
    for(int i =0;i<4;i++)
    {
        //QModelIndex *index = new QModelIndex ;
        QModelIndex index=model->index(i,0,QModelIndex());
        QVariant checkstate = model->data(index,Qt::CheckStateRole);
        QVERIFY(checkstate==Qt::Checked);
    }
}
