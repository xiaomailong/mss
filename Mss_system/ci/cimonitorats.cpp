#include "cimonitorats.h"
#include "ui_cimonitorats.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>

CiMonitorAts::CiMonitorAts(QWidget *parent,CiReadDataThread *readData) :
    QWidget(parent),
    ui(new Ui::CiMonitorAts)
{
    ui->setupUi(this);
    packageIndex=0;
    totalPage=0;
    currentPage=1;
    totalCount=0;
    beginDateTime=QDateTime::currentDateTime().addDays(-1);
    endDateTime=QDateTime::currentDateTime();

    ui->startDateTime->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->endDateTime->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->startDateTime->setDateTime(beginDateTime);
    ui->endDateTime->setDateTime(endDateTime);

    model=NULL;

    connect(this,&CiMonitorAts::sendEventToRead,readData,&CiReadDataThread::DealFromCIAts);
    connect(readData,&CiReadDataThread::sendDataToCIAts,this,&CiMonitorAts::onEventFromRead);
    on_monitorButton_clicked();
}

CiMonitorAts::~CiMonitorAts()
{
    delete ui;
}

void CiMonitorAts::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    QString tableName;
    if(packageIndex==0)
    {
        tableName="ci_ats_stationyard";
    }else if(packageIndex==1)
    {
        tableName="ci_ats_alarm";
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

void CiMonitorAts::updateStatus()
{
    ui->totalRecordLabel->setText(QString("共 %1 条记录").arg(QString::number(totalCount)));
    ui->totalPage->setText(QString("共 %1 页  当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));

    if(currentPage == 1)
    {
        ui->prevButton->setEnabled(false);
        if(totalPage <= 1)
        {
            ui->nextButton->setEnabled(false);
        }else
        {
            ui->nextButton->setEnabled(true);
        }
    }else if(currentPage == totalPage)
    {
        ui->prevButton->setEnabled(true);
        ui->nextButton->setEnabled(false);
    }else
    {
        ui->prevButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
    }
}

void CiMonitorAts::onEventFromRead(QSqlTableModel *tableModel)
{
    model = tableModel;
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


void CiMonitorAts::on_monitorButton_clicked()
{
    isGetCount=true;
    findData();
}

void CiMonitorAts::on_prevButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void CiMonitorAts::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void CiMonitorAts::on_comboBox_currentIndexChanged(int index)
{
    packageIndex = index;
}

void CiMonitorAts::on_startDateTime_dateTimeChanged(const QDateTime &dateTime)
{
    beginDateTime = dateTime;
}

void CiMonitorAts::on_endDateTime_dateTimeChanged(const QDateTime &dateTime)
{
    endDateTime = dateTime;
}

void CiMonitorAts::on_firstPageButton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void CiMonitorAts::on_lastPageButton_clicked()
{
    currentPage=totalPage;
    findData();
    updateStatus();
}

