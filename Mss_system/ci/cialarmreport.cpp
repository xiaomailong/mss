#include "cialarmreport.h"
#include "ui_cialarmreport.h"
#include <QDebug>

CiAlarmReport::CiAlarmReport(QWidget *parent,CiReadDataThread *readData,int type,QString deviceName) :
    QWidget(parent),
    ui(new Ui::CiAlarmReport)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);
    this->type = type;
    this->deviceName = deviceName;
    totalPage=0;
    currentPage=1;
    totalCount=0;
    beginDateTime = QDateTime::currentDateTime();

    endDateTime = QDateTime::currentDateTime();
    model=NULL;
    deviceIndex=0;
    deviceTypeIndex=0;
    faultTypeIndex=0;
    faultLevelIndex=0;

    if(type == 5 || type == 1)
    {
        int year=beginDateTime.date().year();
        int month=beginDateTime.date().month();
        beginDateTime.setDate(QDate(year,month,1));
        beginDateTime.setTime(QTime(0,0));
        ui->beginDateTimeEdit->setCalendarPopup(true);
        ui->endDateTimeEdit->setCalendarPopup(true);
    }

    ui->beginDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->endDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->beginDateTimeEdit->setDateTime(beginDateTime);
    ui->endDateTimeEdit->setDateTime(endDateTime);

    connect(this,&CiAlarmReport::sendEventToRead,readData,&CiReadDataThread::DealFromCIAlarm);
    connect(readData,&CiReadDataThread::sendDataToCIAlarm,this,&CiAlarmReport::onDataFromRead);

    on_monitorButton_clicked();

}

CiAlarmReport::~CiAlarmReport()
{
    delete ui;
}

void CiAlarmReport::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }

    QString tableName;
    tableName="ci_ci_data";

    int limitIndex = (currentPage-1) * pageRecordCount;

    QString filter;
    filter.append(QString("time>'%1' and time<'%2' ").arg(beginDateTime.toString("yyyy-MM-dd HH:mm:ss")).arg(endDateTime.toString("yyyy-MM-dd HH:mm:ss")));
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
    }else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(pageRecordCount)));
        emit sendEventToRead(type+deviceName,tableName,filter);
    }
}

void CiAlarmReport::updateStatus()
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

void CiAlarmReport::onDataFromRead(const QString id, QSqlTableModel *tableModel)
{
    model=tableModel;
    if(id.compare(type+deviceName)==0)
    {
        if(isGetCount)
        {
            totalCount=model->rowCount();
            totalPage=(totalCount % pageRecordCount ==0)?(totalCount / pageRecordCount):(totalCount / pageRecordCount +1);
            updateStatus();
            isGetCount=false;
            findData();
            return;
        }
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->verticalHeader()->hide();
        ui->tableView->show();
    }

}

void CiAlarmReport::on_deviceComboBox_currentIndexChanged(int index)
{
    deviceIndex = index;
}

void CiAlarmReport::on_typeComboBox_currentIndexChanged(int index)
{
    deviceTypeIndex = index;
}

void CiAlarmReport::on_faultTypeComboBox_currentIndexChanged(int index)
{
    faultTypeIndex = index;
}

void CiAlarmReport::on_faultLevelComboBox_currentIndexChanged(int index)
{
    faultLevelIndex = index;
}

void CiAlarmReport::on_beginDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    beginDateTime = dateTime;
}

void CiAlarmReport::on_endDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    endDateTime  = dateTime;
}

void CiAlarmReport::on_firstPage_clicked()
{
    currentPage = 1;
    findData();
    updateStatus();
}

void CiAlarmReport::on_prevPage_clicked()
{
    currentPage --;
    findData();
    updateStatus();
}

void CiAlarmReport::on_nextPage_clicked()
{
    currentPage ++;
    findData();
    updateStatus();
}

void CiAlarmReport::on_lastPage_clicked()
{
    currentPage = totalPage;
    findData();
    updateStatus();
}

void CiAlarmReport::on_monitorButton_clicked()
{
    isGetCount=true;
    findData();
}
