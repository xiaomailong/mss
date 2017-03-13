#include "zcmonitorats.h"
#include "ui_zcmonitorats.h"
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>


ZCMonitorATS::ZCMonitorATS(QWidget *parent,ZCReadData *zcReadAtsData) :
    QWidget(parent),
    ui(new Ui::ZCMonitorATS)
{
    ui->setupUi(this);
    //init values
    packageIndex=0;
    PageRecordCount=100;
    totalPage=0;
    currentPage=1;
    totalRecrodCount=0;
    model=NULL;
    //set the startDateTime endDateTime
    startDateTime=QDateTime::currentDateTime().addSecs(-300);
    startDateTime.setTime(QTime(0,0));
    endDateTime=QDateTime::currentDateTime().addDays(1);

    ui->startDateEdit->setCalendarPopup(true);
    ui->endDateEdit->setCalendarPopup(true);

    ui->startDateEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->endDateEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

    ui->startDateEdit->setDateTime(startDateTime);
    ui->endDateEdit->setDateTime(endDateTime);

    connect(this,&ZCMonitorATS::sendEventToRead,zcReadAtsData,&ZCReadData::DealFromZCAts);
    connect(zcReadAtsData,&ZCReadData::sendDataToZCAts,this,&ZCMonitorATS::onEventFromRead);
    on_queryButton_clicked();
}

ZCMonitorATS::~ZCMonitorATS()
{
    delete ui;
}
//receive data from zcreadData
void ZCMonitorATS::onEventFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount)
    {
        totalRecrodCount=model->rowCount();
        getTotalPage();
        qDebug()<<"ZCMonitorAts totalPage :"<<totalPage;
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }
    qDebug()<<"ZCMonitorATS onDataFromRead :"<<model->rowCount();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();
    isFinding=false;
    updateStatus();
}
//get total page according to the record in database
void ZCMonitorATS::getTotalPage(){
    totalPage=(totalRecrodCount % PageRecordCount ==0)?(totalRecrodCount / PageRecordCount):(totalRecrodCount / PageRecordCount +1);
}
//transfer the table name through emit sendEventToRead and message will receive in onEventFromRead
void ZCMonitorATS::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    isFinding=true;
    QString tableName;
    if(packageIndex==0)
    {
        tableName="zc_ats_tvc";
    }
    else if(packageIndex==1)
    {
        tableName="zc_ats_tec";
    }
    else if(packageIndex==2)
    {
        tableName="zc_ats_ts";
    }
    int limitIndex = (currentPage-1) *PageRecordCount;

    QString filter;
    //filter.append("1=1 ");
    filter.append(QString("time>'%1' and time<'%2' ").arg(startDateTime.toString("yyyy-MM-dd HH:mm:ss")).arg(endDateTime.toString("yyyy-MM-dd HH:mm:ss")));
    if(isGetCount)
    {
        emit sendEventToRead(tableName,filter);
    }
    else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount)));
        emit sendEventToRead(tableName,filter);
    }
}
//update button label show message
void ZCMonitorATS::updateStatus()
{
    ui->totalPageLabel->setText(QString("共 %1 条记录").arg(QString::number(totalRecrodCount)));
    ui->currentPageLabel->setText(QString("共 %1 页  当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));
    if(isFinding)
    {
        ui->queryButton->setEnabled(false);
    }
    else
    {
        ui->queryButton->setEnabled(true);
    }

    if(currentPage == 1)
    {
        ui->prevButton->setEnabled(false);
        if(totalPage<=1)
        {
            ui->nextButton->setEnabled(false);
        }
        else
        {
            ui->nextButton->setEnabled(true);
        }
    }
    else if(currentPage == totalPage)
    {
        ui->prevButton->setEnabled(true);
        ui->nextButton->setEnabled(false);
    }
    else
    {
        ui->prevButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
    }
}
void ZCMonitorATS::on_queryButton_clicked()
{
    isGetCount=true;
    findData();
}

void ZCMonitorATS::on_prevButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void ZCMonitorATS::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void ZCMonitorATS::on_switchPageButton_clicked()
{
    currentPage = ui->switchPageLineEdit->text().toInt();
    if (ui->switchPageLineEdit->text()==NULL)
    {
        return;
    }
    findData();
    updateStatus();
}

void ZCMonitorATS::on_filter_cbo_currentIndexChanged(int index)
{
    packageIndex=index;
}

void ZCMonitorATS::on_comboBox_currentIndexChanged(int index)
{
    switch (index) 
    {
    case 0:
        PageRecordCount = 100;
        break;
    case 1:
        PageRecordCount = 500;
        break;
    case 2:
        PageRecordCount = 1000;
        break;
    case 3:
        PageRecordCount = 2000;
        break;
    default:
        break;
    }
}

void ZCMonitorATS::on_pushButton_clicked()
{
    getTotalPage();
    findData();
    updateStatus();
}

void ZCMonitorATS::on_startDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    startDateTime = dateTime;
}

void ZCMonitorATS::on_endDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    endDateTime = dateTime;
}
