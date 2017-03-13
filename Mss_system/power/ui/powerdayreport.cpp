#include "powerdayreport.h"
#include "ui_powerdayreport.h"
#include "power/ui/powerdisplaychoicemodel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include"power/ui/powerreaddata.h"

PowerDayReport::PowerDayReport(QWidget *parent,PowerReadData *readData):QWidget(parent),
    ui(new Ui::PowerDayReport)

{
    ui->setupUi(this);
    model = new PowerDisplayChoiceModel(this);
    realtimeTableList<<"电压"<<"电流"<<"频率"<<"相位角";
    model->setChoice(realtimeTableList);
    ui->tableView->setModel(model);
    connect(ui->all_check, SIGNAL(clicked()), this, SLOT(allChecked()));
    connect(ui->all_clean, SIGNAL(clicked()), this, SLOT(allClean()));

    connect(model,&PowerDisplayChoiceModel::checkStatusChange,this,&PowerDayReport::displaySqlTableColumn);
    connect(model,&PowerDisplayChoiceModel::cleanAllChecked,this,&PowerDayReport::cleanAllCheckBox);
    connect(model,&PowerDisplayChoiceModel::cleanAllCleaned,this,&PowerDayReport::cleanAllCleanBox);
    connect(this,&PowerDayReport::sendEventToRead,readData,&PowerReadData::DealFromDayReport);
    connect(readData,&PowerReadData::sendDataToDayReport,this,&PowerDayReport::OnGetData);

    getDayReportData();
}

PowerDayReport::~PowerDayReport()
{
    delete ui;
}


void PowerDayReport:: OnGetData(QSqlQueryModel *model)
{
    if(model!=NULL)
    {
        model->setHeaderData(sqlQueryCount,Qt::Horizontal,"设备名称");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"电压");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"电流");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"频率");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"相位角");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"时间");
        ui->tableView_2->setModel(model);
    }
}


void PowerDayReport::getDayReportData( )
{
     //QString query ="SELECT devicename, voltage,current,type,frequency  FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    QString query ="SELECT devicename, voltage,current,frequency,phase,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    emit sendEventToRead(query);
}


void PowerDayReport::displaySqlTableColumn(const QModelIndex &index,bool checked)
{
    if(checked ==false)
    {
        qDebug()<<"column ="<<index.column();
        qDebug()<<"row ="<<index.row();
        ui->tableView_2->setColumnHidden(index.row()+1,true);
    }
    else
    {
        ui->tableView_2->setColumnHidden(index.row()+1,false);
    }
    update();
}


void PowerDayReport::allChecked()
{
    if(ui->all_check->checkState())
    {
        int count =4;
        for(int i =0;i<count;i++)
        {
            //QModelIndex *index = new QModelIndex ;
            QModelIndex index=model->index(i,0,QModelIndex());
            model->setData(index,Qt::Checked,Qt::CheckStateRole);
            ui->all_clean->setCheckState(Qt::Unchecked);
        }
    }

}

void PowerDayReport::allClean()
{
    if(ui->all_clean->checkState())
    {
        int count =4;
        for(int i =0;i<count;i++)
        {
            //QModelIndex *index = new QModelIndex ;
            QModelIndex index=model->index(i,0,QModelIndex());
            model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
            ui->all_check->setCheckState(Qt::Unchecked);
        }
    }
}

void PowerDayReport::cleanAllCheckBox()
{
    ui->all_check->setCheckState(Qt::Unchecked);
}


void PowerDayReport::cleanAllCleanBox()
{
    ui->all_clean->setCheckState(Qt::Unchecked);
}
