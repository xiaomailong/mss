#include "poweralarmsystem.h"
#include "ui_poweralarmsystem.h"

#include <QDebug>

PowerAlarmSystem::PowerAlarmSystem(QWidget *parent,PowerReadData *readData,int type,QString deviceName) :
    QWidget(parent),
    ui(new Ui::PowerAlarmSystem)
{
    ui->setupUi(this);
    this->type=type;
    this->deviceName=deviceName;
    //ui->dateEdit->setDisplayFormat("yyyy-MM");

    totalPage=0;
    currentPage=1;
    totalCount=0;
    dateTime1=QDateTime::currentDateTime();

    dateTime2=QDateTime::currentDateTime();
    model=NULL;
    deviceIndex=0;
    deviceTypeIndex=0;
    faultTypeIndex=0;
    faultLevelIndex=0;
    qDebug()<<"power alarm type :"<<type;
    if(type==3)
    {
        dateTime1.setTime(QTime(0,0));
    }
    else if(type==4)
    {
        int year=dateTime1.date().year();
        int month=dateTime1.date().month();
        dateTime1.setDate(QDate(year,month,1));
        dateTime1.setTime(QTime(0,0));
        ui->dateTimeEdit->setCalendarPopup(true);
        ui->dateTimeEdit_2->setCalendarPopup(true);
    }
    ui->dateTimeEdit->setDateTime(dateTime1);
    ui->dateTimeEdit_2->setDateTime(dateTime2);

    connect(this,&PowerAlarmSystem::sendEventToRead,readData,&PowerReadData::DealFromPowerAlarm);
    connect(readData,&PowerReadData::sendDataToPowerAlarmReport,this,&PowerAlarmSystem::onDataFromRead);

}

PowerAlarmSystem::~PowerAlarmSystem()
{
    delete ui;
}

void PowerAlarmSystem::onDataFromRead(const QString id,QSqlQueryModel *tableModel)
{
    model=tableModel;
    if(id.compare(type+deviceName)==0)
    {

        if(isGetCount)
        {
            totalCount=model->rowCount();
            totalPage=(totalCount % pageRecordCount ==0)?(totalCount / pageRecordCount):(totalCount / pageRecordCount +1);
            qDebug()<<"PowerAlarmSystem totalPage :"<<totalPage;
            updateStatus();
            isGetCount=false;
            findData();
            return;
        }
        ui->tableView->setModel(model);
        //ui->tableView->scrollToBottom();
        //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->verticalHeader()->hide();
        ui->tableView->show();
    }
}


void PowerAlarmSystem::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }

    QString tableName;
    tableName="subsys_power_alarm";

    int limitIndex = (currentPage-1) * pageRecordCount;

    QString filter;
    //filter.append("1=1 ");
    filter.append(QString("time>'%1' and time<'%2' ").arg(dateTime1.toString("yyyy-MM-dd HH:mm:ss")).arg(dateTime2.toString("yyyy-MM-dd HH:mm:ss")));
    if(deviceTypeIndex!=0)
    {
        filter.append(QString("and device_type=%1 ").arg(deviceTypeIndex-1));
    }
    if(faultTypeIndex!=0)
    {
        filter.append(QString("and fault_type=%1 ").arg(faultTypeIndex-1));
    }
    if(faultLevelIndex!=0)
    {
        filter.append(QString("and fault_type=%1 ").arg(faultLevelIndex-1));
    }

    if(isGetCount)
    {
        emit sendEventToRead(type+deviceName,/*tableName,*/filter);
    }else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(pageRecordCount)));
        emit sendEventToRead(type+deviceName,/*tableName,*/filter);
    }
}


void PowerAlarmSystem::on_findButton_clicked()
{
    isGetCount=true;
    findData();
}



void PowerAlarmSystem::on_firstButton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void PowerAlarmSystem::on_perviousButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void PowerAlarmSystem::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void PowerAlarmSystem::on_lastButton_clicked()
{
    currentPage=totalPage;
    findData();
    updateStatus();
}

void PowerAlarmSystem::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime1=dateTime;
}

void PowerAlarmSystem::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime2=dateTime;
}


void PowerAlarmSystem::updateStatus()
{
    ui->totalLabel->setText(QString("共 %1 条记录").arg(QString::number(totalCount)));
    ui->pageLabel->setText(QString("共 %1 页  当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));

    if(currentPage == 1)
    {
        ui->perviousButton->setEnabled(false);
        if(totalPage==1)
        {
            ui->nextButton->setEnabled(false);
        }else
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

void PowerAlarmSystem::on_deviceComboBox_currentIndexChanged(int index)
{
    deviceIndex=index;

}

void PowerAlarmSystem::on_typeComboBox_currentIndexChanged(int index)
{
    deviceTypeIndex=index;

}

void PowerAlarmSystem::on_faultTypeComboBox_currentIndexChanged(int index)
{
    faultTypeIndex=index;
}

void PowerAlarmSystem::on_faultLevelComboBox_currentIndexChanged(int index)
{
    faultLevelIndex=index;
}
