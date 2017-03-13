#include "zcdayreport.h"
#include "ui_zcdayreport.h"
#include "zcreaddata.h"

ZcDayReport::ZcDayReport(QWidget *parent,ZCReadData *zcReadAlarmData) :
    QWidget(parent),
    ui(new Ui::ZcDayReport)
{
    ui->setupUi(this);
    //init values
    packageIndex=0;
    totalPage=0;
    PageRecordCount=100;
    currentPage=1;
    totalRecrodCount=0;
    model=NULL;

    startDateTime=QDateTime::currentDateTime().addSecs(-300);;
    startDateTime.setTime(QTime(0,0));
    endDateTime=QDateTime::currentDateTime().addDays(1);

    ui->startDateEdit->setCalendarPopup(true);
    ui->endDateEdit->setCalendarPopup(true);

    ui->startDateEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->endDateEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

    ui->startDateEdit->setDateTime(startDateTime);
    ui->endDateEdit->setDateTime(endDateTime);

    connect(this,&ZcDayReport::sendEventToRead,zcReadAlarmData,&ZCReadData::DealFromZCAlarm);
    connect(zcReadAlarmData,&ZCReadData::sendDataToZCAlarm,this,&ZcDayReport::onEventFromRead);
    on_queryButton_clicked();
}

ZcDayReport::~ZcDayReport()
{
    delete ui;
}
//receive data from zcreadData
void ZcDayReport::onEventFromRead(QSqlTableModel *tableModel)
{
    model=tableModel;
    if(isGetCount){
        totalRecrodCount=model->rowCount();
        getTotalPage();
        qDebug()<<"ZcDayReport totalPage :"<<totalPage;
        updateStatus();
        isGetCount=false;
        findData();
        return;
    }
    qDebug()<<"ZcDayReport onDataFromRead :"<<model->rowCount();

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->show();
    isFinding=false;
    updateStatus();
}
//get total page according to the record in database
void ZcDayReport::getTotalPage(){
    totalPage=(totalRecrodCount % PageRecordCount ==0)?(totalRecrodCount / PageRecordCount):(totalRecrodCount / PageRecordCount +1);
}
//transfer the table name through emit sendEventToRead and message will receive in onEventFromRead
void ZcDayReport::findData()
{
    if(model!=NULL)
    {
        model->clear();
        model=NULL;
    }
    QString tableName;
    tableName="zc_monitor";
    int limitIndex = (currentPage-1) *PageRecordCount;
    QString filter;
    //filter.append("1=1 ");
    filter.append(QString("time>'%1' and time<'%2' ").arg(startDateTime.toString("yyyy-MM-dd HH:mm:ss")).arg(endDateTime.toString("yyyy-MM-dd HH:mm:ss")));
    if(isGetCount){
        emit sendEventToRead(tableName,filter);
    }
    else
    {
        filter.append(QString("limit %1,%2;").arg(QString::number(limitIndex)).arg(QString::number(PageRecordCount)));
        emit sendEventToRead(tableName,filter);
    }
}
//update button label show message
void ZcDayReport::updateStatus()
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

void ZcDayReport::on_queryButton_clicked()
{
    isGetCount=true;
    findData();
}
void ZcDayReport::on_prevButton_clicked()
{
    currentPage--;
    findData();
    updateStatus();
}

void ZcDayReport::on_nextButton_clicked()
{
    currentPage++;
    findData();
    updateStatus();
}

void ZcDayReport::on_switchPageButton_clicked()
{
    currentPage = ui->switchPageLineEdit->text().toInt();
    if(ui->switchPageLineEdit->text()==NULL) return;
    findData();
    updateStatus();
}

void ZcDayReport::on_filter_cbo_currentIndexChanged(int index)
{
     packageIndex=index;
}
void ZcDayReport::on_startDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    startDateTime = dateTime;
}

void ZcDayReport::on_endDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    endDateTime = dateTime;
}
void ZcDayReport::on_comboBox_currentIndexChanged(int index)
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

void ZcDayReport::on_pushButton_clicked()
{
    getTotalPage();
    findData();
    updateStatus();
}
