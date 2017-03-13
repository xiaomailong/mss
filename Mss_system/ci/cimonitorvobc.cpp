#include "cimonitorvobc.h"
#include "ui_cimonitorvobc.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include "cimonitorvobc.h"
#include "cireaddatathread.h"
#include <QDebug>

CiMonitorVobc::CiMonitorVobc(QWidget *parent,CiReadDataThread *readData) :
    QWidget(parent),
    ui(new Ui::CiMonitorVobc)
{
    ui->setupUi(this);

    packageIndex=0;
    totalPage=0;
    currentPage=1;
    totalCount=0;
    beginDateTime = QDateTime::currentDateTime().addDays(-1);
    endDateTime = QDateTime::currentDateTime();
    ui->startDateTime->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->endDateTime->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->startDateTime->setDateTime(beginDateTime);
    ui->endDateTime->setDateTime(endDateTime);

    model = NULL;

    connect(this,&CiMonitorVobc::sendEventToRead,readData,&CiReadDataThread::DealFromCIVobc);
    connect(readData,&CiReadDataThread::sendDataToCIVobc,this,&CiMonitorVobc::onEventFromRead);

    on_monitorButton_clicked();

}

CiMonitorVobc::~CiMonitorVobc()
{
    delete ui;
}

void CiMonitorVobc::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    QString tableName;
    if(packageIndex==0)
    {
        tableName="ci_vobc_data";
    }else if(packageIndex==1)
    {
        tableName="ci_vobc_data";
    }
    int limitIndex = (currentPage-1) *PageRecordCount;

    QString filter;
    filter.append(QString("time>'%1' and time<'%2' ").arg(beginDateTime.toString("yyyy-MM-dd HH:mm:ss")).arg(endDateTime.toString("yyyy-MM-dd HH:mm:ss")));

    if(isGetCount)
    {
        emit sendEventToRead(tableName,filter);
    }else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount)));
        emit sendEventToRead(tableName,filter);
    }
}

void CiMonitorVobc::updateStatus()
{
    ui->totalRecordLabel->setText(QString("共 %1 条记录").arg(QString::number(totalCount)));
    ui->totalPage->setText(QString("共 %1 页  当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));

    if(currentPage == 1)
    {
        ui->prevPage->setEnabled(false);
        if(totalPage <= 1)
        {
            ui->nextPage->setEnabled(false);
        }else
        {
            ui->nextPage->setEnabled(true);
        }
    }else if(currentPage == totalPage)
    {
        ui->prevPage->setEnabled(true);
        ui->nextPage->setEnabled(false);
    }else
    {
        ui->prevPage->setEnabled(true);
        ui->nextPage->setEnabled(true);
    }
}

void CiMonitorVobc::onEventFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount)
    {
        totalCount=model->rowCount();
        totalPage=(totalCount % PageRecordCount ==0)?(totalCount / PageRecordCount):(totalCount / PageRecordCount +1);
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();
}

void CiMonitorVobc::on_monitorButton_clicked()
{
    isGetCount=true;
    findData();
}

void CiMonitorVobc::on_prevPage_clicked()
{
    currentPage --;
    findData();
    updateStatus();
}

void CiMonitorVobc::on_nextPage_clicked()
{
    currentPage ++;
    findData();
    updateStatus();
}

void CiMonitorVobc::on_comboBox_currentIndexChanged(int index)
{
    packageIndex = index;
}

void CiMonitorVobc::on_startDateTime_dateTimeChanged(const QDateTime &dateTime)
{
    beginDateTime = dateTime;
}

void CiMonitorVobc::on_endDateTime_dateTimeChanged(const QDateTime &dateTime)
{
    endDateTime = dateTime;
}

void CiMonitorVobc::on_firstPageButton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void CiMonitorVobc::on_lastPageButton_clicked()
{
    currentPage=totalPage;
    findData();
    updateStatus();
}
