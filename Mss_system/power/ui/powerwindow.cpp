#include "power/ui/powerwindow.h"
#include "power/ui/powerdevicewidget.h"
#include "power/ui/powercabinet.h"
#include "power/ui/powerdayreport.h"
#include "power/ui/powercurvewidget.h"
#include "power/ui/powerdaycurvewidget.h"
#include "power/ui/powercommoncurvewidget.h"
#include "power/ui/powerrealtimecurvewidget.h"
#include "power/ui/poweralarmsystem.h"
#include <QThread>
PowerWindow::PowerWindow(QWidget *parent) :
    QMainWindow(parent)

{
    setWindowTitle(tr("电源屏"));
    setMinimumSize(1024,768);

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

    thread=new QThread(this);
    readData=new PowerReadData;
    readData->moveToThread(thread);
    thread->start();
    connect(this,&PowerWindow::destroyed,this,&PowerWindow::onWindowDestroy);
    connect(thread, &QThread::finished, readData, &QObject::deleteLater);
    connect(tabWidget,&QTabWidget::tabCloseRequested,this,&PowerWindow::onTabClose);

    connect(power,&PowerDeviceWidget::showDayReport,this,&PowerWindow::onEventForPower);
    connect(power,&PowerDeviceWidget::showDayCurve,this,&PowerWindow::onEventForPower);
    connect(power,&PowerDeviceWidget::showMonthCurve,this,&PowerWindow::onEventForPower);
    connect(power,&PowerDeviceWidget::showYearCurve,this,&PowerWindow::onEventForPower);
    connect(power,&PowerDeviceWidget::showRealTimeCurve,this,&PowerWindow::onEventForPower);
    connect(power,&PowerDeviceWidget::showPowerAlarm,this,&PowerWindow::onEventForPower);
    connect(power,&PowerDeviceWidget::showPowerAlarm,this,&PowerWindow::onEventForPower);

}


PowerWindow::~PowerWindow()
{

}



void PowerWindow::onWindowDestroy()
{
    thread->quit();
    thread->wait();
    delete thread;
}


void PowerWindow::onEventForPower(int type,QString actionName)
{

    QString widgetKey=actionName+type;
    if(hashTabWidget.contains(widgetKey))
    {
        tabWidget->setCurrentWidget(hashTabWidget.value(widgetKey));
        return;
    }
    if(type==day_report)
    {
        PowerDayReport *dayReport=new PowerDayReport(tabWidget,readData);
        tabWidget->addTab(dayReport,actionName);
        tabWidget->setCurrentWidget(dayReport);
        hashTabWidget.insert(widgetKey,dayReport);
    }
    else if(type==day_curve)
    {
        PowerDayCurveWidget *dayCurve=new PowerDayCurveWidget(tabWidget);
        tabWidget->addTab(dayCurve,actionName);
        tabWidget->setCurrentWidget(dayCurve);
        hashTabWidget.insert(widgetKey,dayCurve);
    }
    else if(type == month_curve)
    {

        PowerCommonCurveWidget *monthCurve=new PowerCommonCurveWidget(tabWidget,readData,monthType);
        tabWidget->addTab(monthCurve,actionName);
        tabWidget->setCurrentWidget(monthCurve);
        hashTabWidget.insert(widgetKey,monthCurve);
    }
    else if(type == year_curve)
    {

        PowerCommonCurveWidget *yearCurve=new PowerCommonCurveWidget(tabWidget,readData,yearType);
        tabWidget->addTab(yearCurve,actionName);
        tabWidget->setCurrentWidget(yearCurve);
        hashTabWidget.insert(widgetKey,yearCurve);
    }
    else if(type == realtime_curve)
    {

        PowerRealTimeCurveWidget *realtime_curve=new PowerRealTimeCurveWidget(tabWidget,readData);
        tabWidget->addTab(realtime_curve,actionName);
        tabWidget->setCurrentWidget(realtime_curve);
        hashTabWidget.insert(widgetKey,realtime_curve);
    }
    else if(type == power_alarm)
    {
        PowerAlarmSystem *alarmTab=new PowerAlarmSystem(tabWidget,readData);
        tabWidget->addTab(alarmTab,actionName);
        tabWidget->setCurrentWidget(alarmTab);
        hashTabWidget.insert(widgetKey,alarmTab);
   }

}

void PowerWindow::onTabClose(int index)
{
    hashTabWidget.remove(hashTabWidget.key(tabWidget->widget(index)));
    tabWidget->removeTab(index);
    qDebug()<<"onTabClose hashMap=="<<hashTabWidget;
    if(tabWidget->count()==0){
        close();
    }
}


void PowerWindow::closeEvent(QCloseEvent *event)
{
    emit sendEventToMss("quit");
    event->accept();
    //qDebug()<<"VobcSystem::closeEvent";
}

