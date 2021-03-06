#include "zcmonitorvobc.h"
#include "ui_zcmonitorvobc.h"
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

ZCMonitorVOBC::ZCMonitorVOBC(QWidget *parent,ZCReadData *zcReadVobcData) :
    QWidget(parent),
    ui(new Ui::ZCMonitorVOBC)
{
    ui->setupUi(this);
    //init values
    packageIndex=0;
    totalPage=0;
    currentPage=1;
    totalRecrodCount=0;
    PageRecordCount=100;
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

    connect(this,&ZCMonitorVOBC::sendEventToRead,zcReadVobcData,&ZCReadData::DealFromZCVobc);
    connect(zcReadVobcData,&ZCReadData::sendDataToZCVobc,this,&ZCMonitorVOBC::onEventFromRead);
    on_queryButton_clicked();
}
ZCMonitorVOBC::~ZCMonitorVOBC()
{
    delete ui;
}
//receive data from zcreadData
void ZCMonitorVOBC::onEventFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount){
        totalRecrodCount=model->rowCount();
        getTotalPage();
        qDebug()<<"ZCMonitorABS totalPage :"<<totalPage;
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }
    qDebug()<<"ZCMonitorVOBC onDataFromRead :"<<model->rowCount();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();
    isFinding=false;
    updateStatus();

}
//get total page according to the record in database
void ZCMonitorVOBC::getTotalPage(){
    totalPage=(totalRecrodCount % PageRecordCount ==0)?(totalRecrodCount / PageRecordCount):(totalRecrodCount / PageRecordCount +1);
}
//transfer the table name through emit sendEventToRead and message will receive in onEventFromRead
void ZCMonitorVOBC::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    QString tableName;
    if(packageIndex==0)
    {
        tableName="zc_vobc_tc";
    }
    else if(packageIndex==1)
    {
        tableName="zc_vobc_arlr";
    }
    else if(packageIndex==2)
    {
        tableName="zc_vobc_alr";
    }
    else if(packageIndex==3)
    {
        tableName="zc_vobc_scm";
    }
    int limitIndex = (currentPage-1) *PageRecordCount;
    QString filter;
    filter.append(QString("time>'%1' and time<'%2' ").arg(startDateTime.toString("yyyy-MM-dd HH:mm:ss")).arg(endDateTime.toString("yyyy-MM-dd HH:mm:ss")));

    if(isGetCount){
        emit sendEventToRead(tableName,filter);
    }else{
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount)));
        emit sendEventToRead(tableName,filter);
    }
}
//update button label show message
void ZCMonitorVOBC::updateStatus()
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
void ZCMonitorVOBC::on_queryButton_clicked()
{
    isGetCount=true;
    findData();
}

void ZCMonitorVOBC::on_prevButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void ZCMonitorVOBC::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void ZCMonitorVOBC::on_switchPageButton_clicked()
{
    currentPage = ui->switchPageLineEdit->text().toInt();
    if (ui->switchPageLineEdit->text()==NULL)
    {
        return;
    }
    findData();
    updateStatus();
}

void ZCMonitorVOBC::on_filter_cbo_currentIndexChanged(int index)
{
     packageIndex=index;
}

void ZCMonitorVOBC::on_comboBox_currentIndexChanged(int index)
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
void ZCMonitorVOBC::on_startDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    startDateTime = dateTime;
}

void ZCMonitorVOBC::on_endDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    endDateTime = dateTime;
}

void ZCMonitorVOBC::on_pushButton_clicked()
{
    getTotalPage();
    findData();
    updateStatus();
}
