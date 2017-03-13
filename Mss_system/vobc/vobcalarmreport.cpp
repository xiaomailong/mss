#include "vobcalarmreport.h"
#include "ui_vobcalarmreport.h"
#include "vobcreaddatathread.h"
#include "vobcuicommon.h"

VobcAlarmReport::VobcAlarmReport(QWidget *parent,VobcReadDataThread *readData,int type,QString deviceName) :
    QWidget(parent),
    ui(new Ui::VobcAlarmReport)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);
    this->type=type;
    this->deviceName=deviceName;

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
    VOBC_DEBUG()<<"VobcAlarmReport type :"<<type;

    if(type==3)
    {
        dateTime1.setTime(QTime(0,0));
        dateTime2=dateTime2.addDays(1);
        dateTime2.setTime(QTime(0,0));
    }
    else if(type==4 || type==1)
    {
        int year=dateTime1.date().year();
        int month=dateTime1.date().month();
        dateTime1.setDate(QDate(year,month,1));
        dateTime1.setTime(QTime(0,0));

        dateTime2=dateTime2.addMonths(1);
        int yearNext=dateTime2.date().year();
        int monthNext=dateTime2.date().month();
        dateTime2.setDate(QDate(yearNext,monthNext,1));
        dateTime2.setTime(QTime(0,0));

        ui->dateTimeEdit->setCalendarPopup(true);
        ui->dateTimeEdit_2->setCalendarPopup(true);
    }

    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit->setDateTime(dateTime1);
    ui->dateTimeEdit_2->setDateTime(dateTime2);

    connect(this,&VobcAlarmReport::sendEventToRead,readData,&VobcReadDataThread::dealFromVOBCAlarm);
    connect(readData,&VobcReadDataThread::sendDataToVOBCAlarm,this,&VobcAlarmReport::onDataFromRead);

    on_findButton_clicked();
}

VobcAlarmReport::~VobcAlarmReport()
{
    delete ui;
}

void VobcAlarmReport::onDataFromRead(const QString id,QSqlTableModel *tableModel)
{
    model=tableModel;
    if(id.compare(type+deviceName)==0)
    {
        if(isGetCount)
        {
            totalCount=model->rowCount();
            totalPage=(totalCount % PageRecordCount ==0)?(totalCount / PageRecordCount):(totalCount / PageRecordCount +1);
            VOBC_DEBUG()<<"VobcAlarmReport totalPage :"<<totalPage;
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

        isFinding=false;
        updateStatus();

    }
}

void VobcAlarmReport::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    isFinding=true;

    QString tableName;
    tableName="vobc_subsys_alarm";

    int limitIndex = (currentPage-1) * PageRecordCount;

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
        emit sendEventToRead(type+deviceName,tableName,filter);
    }
    else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount)));
        emit sendEventToRead(type+deviceName,tableName,filter);
    }
}

void VobcAlarmReport::on_findButton_clicked()
{
    isGetCount=true;
    findData();
    updateStatus();
}

void VobcAlarmReport::on_firstButton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void VobcAlarmReport::on_perviousButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void VobcAlarmReport::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void VobcAlarmReport::on_lastButton_clicked()
{
    if(totalPage!=0)
    {
        currentPage=totalPage;
    }
    findData();
    updateStatus();
}

void VobcAlarmReport::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime1=dateTime;
}

void VobcAlarmReport::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime2=dateTime;
}

void VobcAlarmReport::updateStatus()
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

void VobcAlarmReport::on_deviceComboBox_currentIndexChanged(int index)
{
    deviceIndex=index;
}

void VobcAlarmReport::on_typeComboBox_currentIndexChanged(int index)
{
    deviceTypeIndex=index;
}

void VobcAlarmReport::on_faultTypeComboBox_currentIndexChanged(int index)
{
    faultTypeIndex=index;
}

void VobcAlarmReport::on_faultLevelComboBox_currentIndexChanged(int index)
{
    faultLevelIndex=index;
}
