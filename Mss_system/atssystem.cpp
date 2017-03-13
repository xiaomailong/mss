#include "atssystem.h"
#include "ats/atsdevice.h"
#include "ats/atsinforeport.h"
#include <QTabWidget>
#include <QDebug>
#include <QCloseEvent>

AtsSystem::AtsSystem(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("ATS 子系统"));
    setMinimumSize(1280,700);
    //showMaximized();
    setAttribute(Qt::WA_DeleteOnClose, true);

    atsTabWidget = new QTabWidget(this);
    this->setCentralWidget(atsTabWidget);
    atsTabWidget->setTabsClosable(true);
    // close tab widget
    connect(atsTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(onTabClose(int)));

    thread=new QThread(this);
    readData=new AtsReadData;
    readData->moveToThread(thread);
    thread->start();
    connect(this,&AtsSystem::destroyed,this,&AtsSystem::onWindowDestroy);
    connect(thread, &QThread::finished, readData, &QObject::deleteLater);
}

void AtsSystem::closeEvent(QCloseEvent *event)
{

    emit sendEventToMss("quit");
    event->accept();
    //close();
}

void AtsSystem::onTabClose(int index)
{

    hashTabWidget.remove(hashTabWidget.key(atsTabWidget->widget(index)));
    atsTabWidget->removeTab(index);
    qDebug()<<"onTabClose hashMap size= "<<hashTabWidget.size();
    if(atsTabWidget->count()==0){
        close();
    }
}


void AtsSystem::onEventFormMss(const QString msg)
{
    if(hashTabWidget.contains(msg)){
        atsTabWidget->setCurrentWidget(hashTabWidget.value(msg));
        return;
    }

    if (msg.compare("ATSdeviceMap")==0) {
        if (!hashTabWidget.contains("atsDevice")) {
            qDebug()<<" show ATS布局图 ";
            atsDevice = new AtsDevice(atsTabWidget);
            //atsDevice->show();
            atsTabWidget->addTab(atsDevice,tr("ATS布局图"));
            hashTabWidget.insert("atsDevice",atsDevice);
            connect(atsDevice,&AtsDevice::showReport,this,&AtsSystem::onEventFromMap);
            connect(this,&AtsSystem::sendAlarmToDevice,atsDevice,&AtsDevice::onShowAlarm);

        }
        atsTabWidget->setCurrentWidget(hashTabWidget.value("atsDevice"));
    } else if (msg.compare("showAtsVobc")==0) {
        //ATSMonitorVOBC *atsMonitorVobc=new ATSMonitorVOBC(atsTabWidget);
        AtsMonitorVobc *atsMonitorVobc=new AtsMonitorVobc(atsTabWidget,readData);
        atsTabWidget->addTab(atsMonitorVobc,tr("ATS 与 VOBC"));
        atsTabWidget->setCurrentWidget(atsMonitorVobc);
        hashTabWidget.insert("showAtsVobc",atsMonitorVobc);
    } else if (msg.compare("showAtsZc")==0) {
        //AtsMonitorZc *AtsMonitorZc=new AtsMonitorZc(atsTabWidget);
        AtsMonitorZc *atsMonitorZc=new AtsMonitorZc(atsTabWidget,readData);
        atsTabWidget->addTab(atsMonitorZc,tr("ATS 与 ZC"));
        atsTabWidget->setCurrentWidget(atsMonitorZc);
        hashTabWidget.insert("showAtsZc",atsMonitorZc);
    } else if (msg.compare("showAtsCi")==0) {
        //ATSMonitorCI *atsMonitorCi=new ATSMonitorCI(atsTabWidget);
        AtsMonitorCi *atsMonitorCi=new AtsMonitorCi(atsTabWidget,readData);
        atsTabWidget->addTab(atsMonitorCi,tr("ATS 与 CI"));
        atsTabWidget->setCurrentWidget(atsMonitorCi);
        hashTabWidget.insert("showAtsCi",atsMonitorCi);
    } else if (msg.compare("showAtsAlarm")==0) {
        int type=3;
        QString deviceName="all";
        AtsAlarmReport *allAtsAlarmReport=new AtsAlarmReport(atsTabWidget,readData,type,deviceName);
        atsTabWidget->addTab(allAtsAlarmReport,"ATS报警信息");
        atsTabWidget->setCurrentWidget(allAtsAlarmReport);
        hashTabWidget.insert("showAtsAlarm",allAtsAlarmReport);
    }


}

void AtsSystem::onEventFromMap(int type,QString deviceName)
{
    qDebug()<<"onEventFromMap type:"<<type<<" deviceName:"<<deviceName;
    QString widgetKey=deviceName+type;

    if(hashTabWidget.contains(widgetKey)){
        atsTabWidget->setCurrentWidget(hashTabWidget.value(widgetKey));
        return;
    }
    if (type == 0) {
        AtsInfoReport *atsReport = new AtsInfoReport(atsTabWidget);
        atsTabWidget->addTab(atsReport,deviceName);
        atsTabWidget->setCurrentWidget(atsReport);
        hashTabWidget.insert(widgetKey,atsReport);
        qDebug()<<"onEventFromMap ---widgetKey:"<<widgetKey;
    } else if (type == 1) {
        //AtsAlarmReport *alarmReport = new AtsAlarmReport(atsTabWidget);
        AtsAlarmReport *alarmReport = new AtsAlarmReport(atsTabWidget,readData,type,deviceName);
        QString typeStr="日";
        atsTabWidget->addTab(alarmReport,deviceName+typeStr+"报警信息");
        atsTabWidget->setCurrentWidget(alarmReport);
        hashTabWidget.insert(widgetKey,alarmReport);
    } else if (type == 2) {
        AtsAlarmReport *alarmReport = new AtsAlarmReport(atsTabWidget,readData,type,deviceName);
        QString typeStr="月";
        atsTabWidget->addTab(alarmReport,deviceName+typeStr+"报警信息");
        atsTabWidget->setCurrentWidget(alarmReport);
        hashTabWidget.insert(widgetKey,alarmReport);
    }
}

void AtsSystem::onAlarmFromMss(ats_mss_alarm_t *alarm_info)
{
    emit sendAlarmToDevice(alarm_info);
}

void AtsSystem::onWindowDestroy() {
    qDebug()<<"AtsSystem::onWindowDestroy= thread quit wait ";
    thread->quit();
    thread->wait();
    delete thread;
    thread=NULL;
}

