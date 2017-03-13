#include "powerrealtimecurvewidget.h"
#include "ui_powerrealtimecurvewidget.h"
#include "power/ui/powerdisplaychoicemodel.h"
//#include "power/ui/checkboxdelegate.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

PowerRealTimeCurveWidget::PowerRealTimeCurveWidget(QWidget *parent,PowerReadData *readData) :
    QWidget(parent),
    ui(new Ui::PowerRealTimeCurveWidget)
{
    ui->setupUi(this);

  /*  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","LL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("test");

    if(!db.open())
    {
        QMessageBox::warning(this,"sql open fail",db.lastError().text());
        return;
    }


    sqlTablemodel=new QSqlQueryModel(this);

    if(!db.tables().contains("psp_infomanage"))
    {
        qDebug() << "table not exist";
    }else
    {
       // sqlTablemodel->setTable("psp_infomanage");
       // QSqlQuery query;

       // query.exec("SELECT  voltage,current,type,frequency FROM psp_infomanage");

       sqlTablemodel->setQuery("SELECT devicename, voltage,current,frequency ,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle");


    }
*/


    model = new PowerDisplayChoiceModel(this);
    realtimeTableList<<"电压"<<"电流"<<"频率"<<"相位角";
    model->setChoice(realtimeTableList);
    ui->tableView->setModel(model);
    connect(ui->all_check, SIGNAL(clicked()), this, SLOT(allChecked()));
    connect(ui->all_clean, SIGNAL(clicked()), this, SLOT(allClean()));

    connect(model,&PowerDisplayChoiceModel::checkStatusChange,this,&PowerRealTimeCurveWidget::displaySqlTableColumn);
    connect(model,&PowerDisplayChoiceModel::cleanAllChecked,this,&PowerRealTimeCurveWidget::cleanAllCheckBox);
    connect(model,&PowerDisplayChoiceModel::cleanAllCleaned,this,&PowerRealTimeCurveWidget::cleanAllCleanBox);
    connect(ui->displaytime, SIGNAL(clicked()), this, SLOT(displayTime()));
    connect(this,&PowerRealTimeCurveWidget::sendEventToRead,readData,&PowerReadData::DealFromPowerRealTimeCurve);
    connect(readData,&PowerReadData::sendDataToPowerRealTime,this,&PowerRealTimeCurveWidget::OnGetData);

}



PowerRealTimeCurveWidget::~PowerRealTimeCurveWidget()
{
    delete ui;
}

void PowerRealTimeCurveWidget:: OnGetData(QSqlQueryModel *model)
{
    if(model !=NULL){
        model->setHeaderData(sqlQueryCount,Qt::Horizontal,"设备名称");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"电压");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"电流");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"频率");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"相位角");
        model->setHeaderData(++sqlQueryCount,Qt::Horizontal,"时间");
        ui->tableView_2->setModel(model);
        ui->tableView_2->setColumnHidden(display_time,true);

    }

}



void PowerRealTimeCurveWidget::getRealTimeData( const QString &query)
{
    //if(sqlTablemodel!=NULL){
    //    sqlTablemodel->clear();
     //   sqlTablemodel=NULL;
    //}
   // query = "SELECT devicename, voltage,current,type,frequency ,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    emit sendEventToRead(query);
}

void PowerRealTimeCurveWidget::displaySqlTableColumn(const QModelIndex &index,bool checked)
{
    if(checked ==false){
        qDebug()<<"column ="<<index.column();
        qDebug()<<"row ="<<index.row();
        ui->tableView_2->setColumnHidden(index.row()+1,true);
        sqlQueryCount--;
    }else{
        ui->tableView_2->setColumnHidden(index.row()+1,false);
        sqlQueryCount++;
    }
    update();
}


void PowerRealTimeCurveWidget::allChecked()
{
    if(ui->all_check->checkState()){
        int count =4;
        for(int i =0;i<count;i++){
            //QModelIndex *index = new QModelIndex ;
            QModelIndex index=model->index(i,0,QModelIndex());
            model->setData(index,Qt::Checked,Qt::CheckStateRole);
            ui->all_clean->setCheckState(Qt::Unchecked);

        }


    }

}

void PowerRealTimeCurveWidget::allClean()
{
    if(ui->all_clean->checkState()){
        int count =4;
        for(int i =0;i<count;i++){
            //QModelIndex *index = new QModelIndex ;
            QModelIndex index=model->index(i,0,QModelIndex());
            model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
            ui->all_check->setCheckState(Qt::Unchecked);
        }


    }

}

void PowerRealTimeCurveWidget::cleanAllCheckBox()
{
    ui->all_check->setCheckState(Qt::Unchecked);

}


void PowerRealTimeCurveWidget::cleanAllCleanBox()
{
    ui->all_clean->setCheckState(Qt::Unchecked);

}


void PowerRealTimeCurveWidget::displayTime()
{
    if(ui->displaytime->checkState()){
        ui->tableView_2->setColumnHidden(display_time,false);
      }else{
        ui->tableView_2->setColumnHidden(display_time,true);
      }


}

void PowerRealTimeCurveWidget::on_queryButton_clicked()
{
    QString query="SELECT devicename, voltage,current,frequency ,phase,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    getRealTimeData(query);
}
