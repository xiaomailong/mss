#include "vobcmonitorats.h"
#include "ui_vobcmonitorats.h"
#include <QSqlTableModel>
#include "vobcuicommon.h"

VobcMonitorATS::VobcMonitorATS(QWidget *parent,VobcReadDataThread *readData) :
    QWidget(parent),
    ui(new Ui::VobcMonitorATS)
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

    connect(this,&VobcMonitorATS::sendEventToRead,readData,&VobcReadDataThread::dealFromVOBCAts);
    connect(readData,&VobcReadDataThread::sendDataToVOBCAts,this,&VobcMonitorATS::onDataFromRead);

    on_findButton_clicked();
}

VobcMonitorATS::~VobcMonitorATS()
{
    delete ui;
}


void VobcMonitorATS::onDataFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount)
    {
        totalCount=model->rowCount();
        totalPage=(totalCount % PageRecordCount ==0)?(totalCount / PageRecordCount):(totalCount / PageRecordCount +1);
        VOBC_DEBUG()<<"VobcMonitorATS totalPage :"<<totalPage;
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }

    VOBC_DEBUG()<<"VobcMonitorATS onDataFromRead :"<<model->rowCount();

    ui->tableView->setModel(model);
    //ui->tableView->scrollToBottom();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();

    isFinding=false;
    updateStatus();
}


void VobcMonitorATS::findData()
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
        tableName="vobc_ats_ato";
    }
    else if(packageIndex==1)
    {
        tableName="vobc_ats_train";
    }
    else if(packageIndex==2)
    {
        tableName="vobc_ats_alarm";
    }
    else if(packageIndex==3)
    {
        tableName="vobc_ats_check";
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


void VobcMonitorATS::on_findButton_clicked()
{
    isGetCount=true;
    currentPage=1;
    findData();
    updateStatus();
}



void VobcMonitorATS::on_firstButton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void VobcMonitorATS::on_perviousButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void VobcMonitorATS::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void VobcMonitorATS::on_lastButton_clicked()
{
    if(totalPage!=0)
    {
        currentPage=totalPage;
    }
    findData();
    updateStatus();
}

void VobcMonitorATS::on_packageComboBox_currentIndexChanged(int index)
{
    packageIndex=index;
}

void VobcMonitorATS::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime1=dateTime;
}

void VobcMonitorATS::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime2=dateTime;
}


void VobcMonitorATS::updateStatus()
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
