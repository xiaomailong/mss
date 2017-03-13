#include "vobcmonitorci.h"
#include "ui_vobcmonitorci.h"
#include <QSqlTableModel>
#include "vobcuicommon.h"

VobcMonitorCI::VobcMonitorCI(QWidget *parent,VobcReadDataThread *readData) :
    QWidget(parent),
    ui(new Ui::VobcMonitorCI)
{
    ui->setupUi(this);

    packageIndex=0;
    totalPage=0;
    currentPage=1;
    totalCount=0;
    dateTime1=QDateTime::currentDateTime().addSecs(-300);
    dateTime2=QDateTime::currentDateTime().addDays(1);
    model=NULL;

    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit->setDateTime(dateTime1);
    ui->dateTimeEdit_2->setDateTime(dateTime2);

    connect(this,&VobcMonitorCI::sendEventToRead,readData,&VobcReadDataThread::dealFromVOBCCi);
    connect(readData,&VobcReadDataThread::sendDataToVOBCCi,this,&VobcMonitorCI::onDataFromRead);

    on_findButton_clicked();
}

VobcMonitorCI::~VobcMonitorCI()
{
    delete ui;
}


void VobcMonitorCI::onDataFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount)
    {
        totalCount=model->rowCount();
        totalPage=(totalCount % PageRecordCount ==0)?(totalCount / PageRecordCount):(totalCount / PageRecordCount +1);
        VOBC_DEBUG()<<"VobcMonitorCI totalPage :"<<totalPage;
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }

    VOBC_DEBUG()<<"VobcMonitorCI onDataFromRead :"<<model->rowCount();

    ui->tableView->setModel(model);
    //ui->tableView->scrollToBottom();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();

    isFinding=false;
    updateStatus();
}


void VobcMonitorCI::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    isFinding=true;
    updateStatus();

    QString tableName;
    if(packageIndex==0)
    {
        tableName="vobc_ci";
    }
    int limitIndex = (currentPage-1) * PageRecordCount;

    QString filter;
    filter.append(QString("time>'%1' and time<'%2' ").arg(dateTime1.toString("yyyy-MM-dd HH:mm:ss")).arg(dateTime2.toString("yyyy-MM-dd HH:mm:ss")));

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


void VobcMonitorCI::on_findButton_clicked()
{
    isGetCount=true;
    currentPage=1;
    findData();

}



void VobcMonitorCI::on_firstButton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void VobcMonitorCI::on_perviousButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void VobcMonitorCI::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void VobcMonitorCI::on_lastButton_clicked()
{
    if(totalPage!=0)
    {
        currentPage=totalPage;
    }
    findData();
    updateStatus();
}

void VobcMonitorCI::on_packageComboBox_currentIndexChanged(int index)
{
    packageIndex=index;
}

void VobcMonitorCI::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime1=dateTime;
}

void VobcMonitorCI::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime2=dateTime;
}


void VobcMonitorCI::updateStatus()
{
    ui->totalLabel->setText(QString("共 %1 条记录").arg(QString::number(totalCount)));
    ui->pageLabel->setText(QString("共 %1 页  当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));

    if(isFinding)
    {
        ui->findButton->setEnabled(false);
    }
    else
    {
        ui->findButton->setEnabled(true);
    }

    if(currentPage == 1)
    {
        ui->perviousButton->setEnabled(false);
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
        ui->perviousButton->setEnabled(true);
        ui->nextButton->setEnabled(false);
    }
    else
    {
        ui->perviousButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
    }
}

