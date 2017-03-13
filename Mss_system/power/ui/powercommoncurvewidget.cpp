#include "powercommoncurvewidget.h"
#include "ui_powercommoncurvewidget.h"
#include <QString>
#include <QDebug>
#include <QSqlRecord>
PowerCommonCurveWidget::PowerCommonCurveWidget(QWidget *parent,PowerReadData *readData,int curveType) :
    QWidget(parent),
    ui(new Ui::PowerCommonCurveWidget)
{
    ui->setupUi(this);
    date=QDate::currentDate();

    int year=date.year();
    int month=date.month();

    date.setDate(year,month,1);
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(date);
    CurveType = curveType ;
    connect(this,&PowerCommonCurveWidget::sendEventToRead,readData,&PowerReadData::DealFromPowerCommonCurve);
    connect(readData,&PowerReadData::sendDataToPowerCommonCurve,this,&PowerCommonCurveWidget::OnGetData);

}

PowerCommonCurveWidget::~PowerCommonCurveWidget()
{
    delete ui;
}


void PowerCommonCurveWidget:: OnGetData(QSqlQueryModel *model){
    if(model !=NULL){

        QMap<QString,qint16> m_map;
        while(model->canFetchMore())
        {
            model->fetchMore();
        }
        int count=model->rowCount();

        for(int i=0;i<count;i++)
        {

           // int year=model->data(model->index(i,0)).toDate().year();
            int voltage= model->record(i).value("voltage").toInt();

            QDateTime dt =  model->record(i).value("savetime").toDateTime() ;
           // QString date = dt.toString("dd.MM.yyyy hh:mm:ss");
           // qDebug()<<"zwz date ="<<date<<"voltage = "<<voltage;

            m_map.insert(dt.toString("dd.MM.yyyy hh:mm:ss"),voltage);


           /* if(m_map.contains(year))
            {
                int value=m_map[year];
                value++;
                m_map[year]=value;
            }
            else
            {
                m_map[year]=1;
            }*/
        }

        QMap<QString,qint16>::iterator it; //遍历map
        for ( it = m_map.begin(); it != m_map.end(); ++it )
        {
            qDebug() <<it.key()<<"mainwindow:"<<it.value();
        }
        chw=new PowerChartWidget(this);
        chw->updateUI(m_map,CurveType);

    }

}









void PowerCommonCurveWidget::on_dateEdit_userDateChanged(const QDate &date1)
{
    date = date1;

}

void PowerCommonCurveWidget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    devicename = arg1;
}

void PowerCommonCurveWidget::on_comboBox_currentIndexChanged(int index)
{
    deviceType = index;
}

void PowerCommonCurveWidget::on_queryButton_clicked()
{
    //QString date1 = date.toString("yyyy-MM-dd 00:00:00");
    QString query ="SELECT devicename, voltage,current,frequency , savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle AND ";
    query.append(QString("savetime >='%1'and savetime<'%2' ").arg(date.toString("yyyy-MM-dd 00:00:00")).arg(date.toString("yyyy-MM-dd 24:00:00")));
    query.append(QString("and devicename= '%1' ").arg("dc_002"));
    query.append(QString("and type= '%1' ").arg("0"));
    //  QString query ="SELECT devicename, voltage,current,frequency ,savetime FROM psp_infomanage JOIN device on device.handle = psp_infomanage.handle";
    qDebug()<<"zwz query ="<<query;
    emit sendEventToRead(query);

}
