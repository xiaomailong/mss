#include "powerwindow.h"
//#include "ui_mainwindow.h"

#include"power/powerdevicewidget.h"
#include"power/powercabinet.h"
#include"power/dayreport.h"
#include"power/powercurvewidget.h"
#include"power/powerdaycurvewidget.h"
#include"power/powercommoncurvewidget.h"
#include"power/powerrealtimecurvewidget.h"
PowerWindow::PowerWindow(QWidget *parent) :
    QMainWindow(parent)

{
 //   ui->setupUi(this);
 //   resize(1024,900);
//    initUi();

    setWindowTitle(tr("电源屏"));
    setMinimumSize(1024,768);
    //showMaximized();


    tabWidget=new QTabWidget();
    this->setCentralWidget(tabWidget);

    QWidget *tab1=new QWidget();
    QWidget *tab2=new QWidget();

    PowerDeviceWidget *power=new PowerDeviceWidget(tab1);

    power->show();

    Powercabinet *cabinet=new Powercabinet(tab2);
    cabinet->show();

    tabWidget->addTab(power,tr("电源屏"));
    tabWidget->addTab(cabinet,tr("电源屏机箱图"));
    tabWidget->setTabsClosable(true);
    connect(power,&PowerDeviceWidget::showDayReport,this,this->onEventForPower);
    connect(power,&PowerDeviceWidget::showDayCurve,this,this->onEventForPower);
    connect(power,&PowerDeviceWidget::showMonthCurve,this,this->onEventForPower);
    connect(power,&PowerDeviceWidget::showYearCurve,this,this->onEventForPower);
    connect(power,&PowerDeviceWidget::showRealTimeCurve,this,this->onEventForPower);

    //add by yhj 20170211 for power monitor system
    server = new powerMonitorSystem_sendData_service2();
    mypsp = new powermonitorsystem2();
    mypsp->start();
    connect(server,SIGNAL(send_psp(quint8*)),mypsp, SLOT(receiveData(quint8*)), Qt::AutoConnection);
    connect(mypsp,SIGNAL(send_alarm(alarm_t*)), this, SLOT(receiveAlarmData(alarm_t*)), Qt::AutoConnection);
    server->start();
    //add end
}


PowerWindow::~PowerWindow()
{

}

void PowerWindow::onEventForPower(int type,QString actionName)
{

    QString widgetKey=actionName+type;
    if(hashTabWidget.contains(widgetKey)){
        tabWidget->setCurrentWidget(hashTabWidget.value(widgetKey));
        return;
    }
    if(type==day_report){
        DayReport *dayReport=new DayReport(tabWidget);
        tabWidget->addTab(dayReport,actionName);
        tabWidget->setCurrentWidget(dayReport);
        hashTabWidget.insert(widgetKey,dayReport);
    }else if(type==day_curve){
        PowerDayCurveWidget *dayCurve=new PowerDayCurveWidget(tabWidget);
        tabWidget->addTab(dayCurve,actionName);
        tabWidget->setCurrentWidget(dayCurve);
        hashTabWidget.insert(widgetKey,dayCurve);
    }else if(type == month_curve){

        PowerCommonCurveWidget *monthCurve=new PowerCommonCurveWidget(tabWidget);
        tabWidget->addTab(monthCurve,actionName);
        tabWidget->setCurrentWidget(monthCurve);
        hashTabWidget.insert(widgetKey,monthCurve);
    }else if(type == year_curve){

        PowerCommonCurveWidget *yearCurve=new PowerCommonCurveWidget(tabWidget);
        tabWidget->addTab(yearCurve,actionName);
        tabWidget->setCurrentWidget(yearCurve);
        hashTabWidget.insert(widgetKey,yearCurve);
    }else if(type == realtime_curve){

        PowerRealTimeCurveWidget *realtime_curve=new PowerRealTimeCurveWidget(tabWidget);
        tabWidget->addTab(realtime_curve,actionName);
        tabWidget->setCurrentWidget(realtime_curve);
        hashTabWidget.insert(widgetKey,realtime_curve);
    }

}


//yhj add 20170211 for power mointor system
void PowerWindow::receiveAlarmData(alarm_t* alarm)
{
    alarm_t t;
    t.handle = alarm->handle;
    qDebug("PowerWindow receiveAlarmData : handle is %d",t.handle);
}
//add end

