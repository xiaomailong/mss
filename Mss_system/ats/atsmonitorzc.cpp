#include "atsmonitorzc.h"
#include "ui_atsmonitorzc.h"

#include <QSqlTableModel>
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

AtsMonitorZc::AtsMonitorZc(QWidget *parent,AtsReadData *readData) :
    QWidget(parent),
    ui(new Ui::AtsMonitorZc)
{
    ui->setupUi(this);
    packageIndex=0;
    totalPage=0;
    currentPage=1;
    totalCount=0;
    dateTime1=QDateTime::currentDateTime();
    dateTime2=QDateTime::currentDateTime().addDays(1);

    model=NULL;
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit->setDateTime(dateTime1);
    ui->dateTimeEdit_2->setDateTime(dateTime2);
    connect(this,&AtsMonitorZc::sendEventToRead,readData,&AtsReadData::DealFromAtsZc);
    connect(readData,&AtsReadData::sendDataToAtsZc,this,&AtsMonitorZc::onDataFromRead);
    on_startmonitor_clicked();
}

AtsMonitorZc::~AtsMonitorZc()
{
    delete ui;
}

void AtsMonitorZc::onDataFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount)
    {
        totalCount=model->rowCount();
        totalPage=(totalCount % pageRecordCount ==0)?(totalCount / pageRecordCount):(totalCount / pageRecordCount +1);
        ATS_DEBUG()<<"ATSMonitorVOBC totalPage :"<<totalPage;
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }
    //ATS_DEBUG()<<"ATSMonitorVOBC onDataFromRead :"<<model->rowCount();
    ui->tableView->setModel(model);
    //ui->tableView->scrollToBottom();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();
}

void AtsMonitorZc::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    QString tableName;
    if(packageIndex==0)
    {
        tableName="ats_zc_heartbeat";
    }
    else if(packageIndex==1)
    {
        tableName="ats_zc_tsr_validate";
    }
    else if (packageIndex==2)
    {
        tableName="ats_zc_tsr_exec_cmd";
    }
    else if (packageIndex==3)
    {
        tableName="ats_zc_tsr_on_confirm";
    }
    int limitIndex = (currentPage-1) * pageRecordCount;

    QString filter;
    //filter.append("1=1 ");
    filter.append(QString("time>'%1' and time<'%2' ").arg(dateTime1.toString("yyyy-MM-dd HH:mm:ss")).arg(dateTime2.toString("yyyy-MM-dd HH:mm:ss")));

    if(isGetCount)
    {
        emit sendEventToRead(tableName,filter);
    }
    else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(pageRecordCount)));
        emit sendEventToRead(tableName,filter);
    }
}

void AtsMonitorZc::on_startmonitor_clicked()
{
    isGetCount=true;
    currentPage = 1;
    findData();
}

void AtsMonitorZc::on_firstbutton_clicked()
{
    currentPage=1;
    findData();
    updateStatus();
}

void AtsMonitorZc::on_prebutton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void AtsMonitorZc::on_nextbutton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void AtsMonitorZc::on_comboBox_currentIndexChanged(int index)
{
    packageIndex=index;
}

void AtsMonitorZc::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime1=dateTime;
}

void AtsMonitorZc::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    dateTime2=dateTime;
}

void AtsMonitorZc::updateStatus()
{
    ui->totalcount->setText(QString("共 %1 条记录").arg(QString::number(totalCount)));
    ui->page->setText(QString("共 %1 页，当前第 %2 页").arg(QString::number(totalPage)).arg(QString::number(currentPage)));

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

void AtsMonitorZc::on_lastbutton_clicked()
{
    if(totalPage!=0)
    {
        currentPage=totalPage;
    }
    findData();
    updateStatus();
}
