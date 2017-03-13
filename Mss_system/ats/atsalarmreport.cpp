#include "atsalarmreport.h"
#include "ui_atsalarmreport.h"
#include "ats/atsreaddata.h"
#include <QDebug>

#define ATS_DEBUG_ENABLED 0

#if ATS_DEBUG_ENABLED
#define ATS_DEBUG       qDebug
#define ATS_INFO        qInfo
#define ATS_WARN        qWarning
#define ATS_FATAL       qFatal
#define ATS_CRITICAL       qCritical
#else
#define ATS_DEBUG       QT_NO_QDEBUG_MACRO
#define ATS_INFO        QT_NO_QDEBUG_MACRO
#define ATS_WARN        QT_NO_QDEBUG_MACRO
#define ATS_FATAL       QT_NO_QDEBUG_MACRO
#define ATS_CRITICAL    QT_NO_QDEBUG_MACRO
#endif

AtsAlarmReport::AtsAlarmReport(QWidget *parent,AtsReadData *readData,int type,QString deviceName) :
    QWidget(parent),
    ui(new Ui::AtsAlarmReport)
{
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
    ATS_DEBUG()<<"AtsAlarmReport type :"<<type;
    if(type==1)
    {
        dateTime1.setTime(QTime(0,0));
    }
    else if(type==2 || type ==3)
    {
        int year=dateTime1.date().year();
        int month=dateTime1.date().month();
        dateTime1.setDate(QDate(year,month,1));
        dateTime1.setTime(QTime(0,0));
        ui->dateTimeEdit->setCalendarPopup(true);
        ui->dateTimeEdit_2->setCalendarPopup(true);
    }
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit->setDateTime(dateTime1);
    ui->dateTimeEdit_2->setDateTime(dateTime2);

    connect(this,&AtsAlarmReport::sendEventToRead,readData,&AtsReadData::DealFromAtsAlarm);
    connect(readData,&AtsReadData::sendDataToAtsAlarm,this,&AtsAlarmReport::onDataFromRead);
    on_findbutton_clicked();
}

AtsAlarmReport::~AtsAlarmReport()
{
    delete ui;
}

void AtsAlarmReport::on_findbutton_clicked()
{
    isGetCount=true;
    findData();
}

void AtsAlarmReport::on_firstbutton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void AtsAlarmReport::on_prebutton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void AtsAlarmReport::on_nextbutton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void AtsAlarmReport::on_lastbutton_clicked()
{
    if(totalPage!=0)
    {
        currentPage=totalPage;
    }
    findData();
    updateStatus();
}

void AtsAlarmReport::updateStatus()
{
    ui->totalcount->setText(QString("共 %1 条记录").arg(QString::number(totalCount)));
    ui->page->setText(QString("共 %1 页  当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));

    if(currentPage == 1)
    {
        ui->prebutton->setEnabled(false);
        if(totalPage==1)
        {
            ui->nextbutton->setEnabled(false);
        }
        else
        {
            ui->nextbutton->setEnabled(true);
        }
    }
    else if(currentPage == totalPage)
    {
        ui->prebutton->setEnabled(true);
        ui->nextbutton->setEnabled(false);
    }
    else
    {
        ui->prebutton->setEnabled(true);
        ui->nextbutton->setEnabled(true);
    }

}

void AtsAlarmReport::onDataFromRead(const QString id,QSqlTableModel *tableModel)
{
    model=tableModel;
    if(id.compare(type+deviceName)==0)
    {
        if(isGetCount)
        {
            totalCount=model->rowCount();
            totalPage=(totalCount % pageRecordCount ==0)?(totalCount / pageRecordCount):(totalCount / pageRecordCount +1);
            ATS_DEBUG()<<"AtsAlarmReport totalPage :"<<totalPage;
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


void AtsAlarmReport::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }

    QString tableName;
    tableName="ats_mss_alarm";
    int limitIndex = (currentPage-1) * pageRecordCount;

    QString filter;
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
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(pageRecordCount)));
        emit sendEventToRead(type+deviceName,tableName,filter);
    }
}

void AtsAlarmReport::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime1=dateTime;
}

void AtsAlarmReport::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime2=dateTime;
}

void AtsAlarmReport::on_devicecomboBox_currentIndexChanged(int index)
{
    deviceIndex=index;
}

void AtsAlarmReport::on_typecomboBox_currentIndexChanged(int index)
{
    deviceIndex=index;
}

void AtsAlarmReport::on_faultcomboBox_currentIndexChanged(int index)
{
    faultTypeIndex=index;
}

void AtsAlarmReport::on_faulttypecomboBox_currentIndexChanged(int index)
{
    faultLevelIndex=index;
}


