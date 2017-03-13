#include "vobcsystem.h"
#include "vobcdevice.h"
#include "vobccabinet.h"
#include "vobcalarmreport.h"
#include "vobcinforeport.h"
#include "vobcmonitorats.h"
#include "vobcmonitorzc.h"
#include "vobcmonitorci.h"
#include "vobcreaddatathread.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QThread>
#include <QCloseEvent>

VobcSystem::VobcSystem(QWidget *parent) : QMainWindow(parent)
{

    setWindowTitle(tr("VOBC 子系统"));
    setMinimumSize(1024,768);
    //showMaximized();
    setAttribute(Qt::WA_DeleteOnClose, true);

    tabWidget=new QTabWidget(this);
    this->setCentralWidget(tabWidget);
    tabWidget->setTabsClosable(true);
    connect(tabWidget,&QTabWidget::tabCloseRequested,this,&VobcSystem::onTabClose);

    thread=new QThread(this);
    readData=new VobcReadDataThread;
    readData->moveToThread(thread);
    thread->start();
    connect(this,&VobcSystem::destroyed,this,&VobcSystem::onWindowDestroy);
    connect(thread, &QThread::finished, readData, &QObject::deleteLater);

}

VobcSystem::~VobcSystem()
{
    //qDebug()<<"~VobcSystem";
}

void VobcSystem::closeEvent(QCloseEvent *event)
{
    emit sendEventToMss("quit");
    event->accept();
    //qDebug()<<"VobcSystem::closeEvent";
}

void VobcSystem::onEventFromMss(const QString msg)
{
    if(hashTabWidget.contains(msg)){
        tabWidget->setCurrentWidget(hashTabWidget.value(msg));
        return;
    }

    if(msg.compare("deviceMap")==0){
        if(!hashTabWidget.contains("vobcDevice")){
            VobcDevice *vobcDevice=new VobcDevice(tabWidget);
            tabWidget->addTab(vobcDevice,tr("VOBC布局图"));
            hashTabWidget.insert("vobcDevice",vobcDevice);
            connect(vobcDevice,&VobcDevice::showReport,this,&VobcSystem::onEventFromMap);
            connect(this,&VobcSystem::sendAlarmToDevice,vobcDevice,&VobcDevice::onAlarm);
        }
        tabWidget->setCurrentWidget(hashTabWidget.value("vobcDevice"));

        if(!hashTabWidget.contains("cabinet")){
            VobcCabinet *cabinet=new VobcCabinet(tabWidget);
            tabWidget->addTab(cabinet,tr("VOBC机箱图"));
            hashTabWidget.insert("cabinet",cabinet);
            connect(cabinet,&VobcCabinet::showReport,this,&VobcSystem::onEventFromMap);
        }

    }else if(msg.compare("showVobcAts")==0){

        VobcMonitorATS *vobcMonitorAbs=new VobcMonitorATS(tabWidget,readData);
        tabWidget->addTab(vobcMonitorAbs,tr("VOBC与ATS"));
        tabWidget->setCurrentWidget(vobcMonitorAbs);
        hashTabWidget.insert("showVobcAts",vobcMonitorAbs);
    }
    else if(msg.compare("showVobcZc")==0){
        VobcMonitorZC *vobcMonitorZc=new VobcMonitorZC(tabWidget,readData);
        tabWidget->addTab(vobcMonitorZc,tr("VOBC与ZC"));
        tabWidget->setCurrentWidget(vobcMonitorZc);
        hashTabWidget.insert("showVobcZc",vobcMonitorZc);
    }else if(msg.compare("showVobcCi")==0){
        VobcMonitorCI *vobcMonitorCi=new VobcMonitorCI(tabWidget,readData);
        tabWidget->addTab(vobcMonitorCi,tr("VOBC与CI"));
        tabWidget->setCurrentWidget(vobcMonitorCi);
        hashTabWidget.insert("showVobcCi",vobcMonitorCi);
    }else if(msg.compare("showVobcAlarm")==0){
        int type=1;
        QString deviceName="all";
        VobcAlarmReport *allVobcAlarmReport=new VobcAlarmReport(tabWidget,readData,type,deviceName);
        tabWidget->addTab(allVobcAlarmReport,"VOBC报警信息");
        tabWidget->setCurrentWidget(allVobcAlarmReport);
        hashTabWidget.insert("showVobcAlarm",allVobcAlarmReport);
    }

}

void VobcSystem::onEventFromMap(int type, QString deviceName)
{
    qDebug()<<"onEventFromMap type:"<<type<<" deviceName:"<<deviceName;
    QString widgetKey=deviceName+type;
    if(hashTabWidget.contains(widgetKey)){
        tabWidget->setCurrentWidget(hashTabWidget.value(widgetKey));
        return;
    }

    if(type==2){
        VobcInfoReport *vobcInfoReport=new VobcInfoReport(tabWidget,type,deviceName);
        tabWidget->addTab(vobcInfoReport,deviceName+"设备状态表");
        tabWidget->setCurrentWidget(vobcInfoReport);
        hashTabWidget.insert(widgetKey,vobcInfoReport);
    }else if(type==3){
        VobcAlarmReport *vobcAlarmReport=new VobcAlarmReport(tabWidget,readData,type,deviceName);
        QString typeStr="日";
        tabWidget->addTab(vobcAlarmReport,deviceName+typeStr+"报警信息");
        tabWidget->setCurrentWidget(vobcAlarmReport);
        hashTabWidget.insert(widgetKey,vobcAlarmReport);
    }else if(type==4){
        VobcAlarmReport *vobcAlarmReport=new VobcAlarmReport(tabWidget,readData,type,deviceName);
        QString typeStr="月";
        tabWidget->addTab(vobcAlarmReport,deviceName+typeStr+"报警信息");
        tabWidget->setCurrentWidget(vobcAlarmReport);
        hashTabWidget.insert(widgetKey,vobcAlarmReport);
    }

    qDebug()<<"onEventFromMap hashMap size= "<<hashTabWidget.size();

}

void VobcSystem::onAlarmFromMss(vobc_subsys_msg_t AtsMsg)
{
    emit sendAlarmToDevice(AtsMsg);
}

void VobcSystem::onTabClose(int index)
{
    hashTabWidget.remove(hashTabWidget.key(tabWidget->widget(index)));
    tabWidget->removeTab(index);
    qDebug()<<"onTabClose hashMap=="<<hashTabWidget;
    if(tabWidget->count()==0){
        close();
    }
}

void VobcSystem::onWindowDestroy()
{
    thread->quit();
    thread->wait();
    delete thread;
    thread=NULL;
}
