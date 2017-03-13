#include "zcsystem.h"
#include "zc/zcgplot.h"
#include "zc/zcdayreport.h"
#include "zc/zcquerydutinfo.h"
#include "zc/zcmonitorats.h"
#include "zc/zcmonitorci.h"
#include "zc/zcmonitorvobc.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QThread>

ZcSystem::ZcSystem(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("ZC 子系统"));
    setMinimumSize(800,600);
    setAttribute(Qt::WA_DeleteOnClose, true);
    zcTabWidget = new QTabWidget();
    this->setCentralWidget(zcTabWidget);
    zcTabWidget->setTabsClosable(true);
    connect(zcTabWidget,&QTabWidget::tabCloseRequested,this,&ZcSystem::onTabClose);

    //create new thread to read data from database
    zcSystemThread = new QThread(this);
    zcReadData = new ZCReadData;
    zcReadData->moveToThread(zcSystemThread);
    zcSystemThread->start();
    connect(this,&ZcSystem::destroyed,this,&ZcSystem::onWindowDestroy);
    connect(zcSystemThread,&QThread::finished,zcReadData,&QObject::deleteLater);
}

void ZcSystem::onReceiveZcGplot(const QString msg)
{
    emit sendEventToMss(msg);
}

void ZcSystem::receive_ui_zc_ci_ls()
{
    qDebug()<<"receive data ";
}

void ZcSystem::closeEvent(QCloseEvent *)
{
    emit sendEventToMss("quit");
    close();
//    switch (QMessageBox::information(this,tr("提示"),tr("确认退出ZC系统?"),tr("确认"),tr("取消"),0,1)) {
//    case 0:
//        event->accept();
//        break;
//    default:
//        event->ignore();
//        break;
//    }

}
void ZcSystem::onEventFromMss(const QString msg)
{
    if(zcHashTabWidget.contains(msg))
    {
        zcTabWidget->setCurrentWidget(zcHashTabWidget.value(msg));
        //qDebug()<<"onEventFromMss return";
        return;
    }
    if(msg.compare("deviceMap")==0)
        {
        if(!zcHashTabWidget.contains("zcDevice"))
            {
            ZCGplot *zcgplot=new ZCGplot(zcTabWidget);
            zcTabWidget->addTab(zcgplot,tr("ZC布局图"));
            zcHashTabWidget.insert("zcDevice",zcgplot);
            connect(zcgplot,&ZCGplot::showReport,this,&ZcSystem::onEventFromMap);
            connect(zcgplot,SIGNAL(zcSendEventToMss(QString)),this,SLOT(onReceiveZcGplot(QString)));
            }
        }
        else if(msg.compare("showZCtoAts")==0)
        {
            ZCMonitorATS *zcMonitorAts=new ZCMonitorATS(zcTabWidget,zcReadData);
            zcTabWidget->addTab(zcMonitorAts,tr("ZC与ATS"));
            zcTabWidget->setCurrentWidget(zcMonitorAts);
            zcHashTabWidget.insert("showZCtoAts",zcMonitorAts);
        }
        else if(msg.compare("showZCtoVobc")==0)
        {
            ZCMonitorVOBC *zcMonitorVobc=new ZCMonitorVOBC(zcTabWidget,zcReadData);
            zcTabWidget->addTab(zcMonitorVobc,tr("ZC与VOBC"));
            zcTabWidget->setCurrentWidget(zcMonitorVobc);
            zcHashTabWidget.insert("showZCtoVobc",zcMonitorVobc);
        }
        else if(msg.compare("showZCtoCi")==0)
        {
            ZCMonitorCI *zcMonitorCi=new ZCMonitorCI(zcTabWidget,zcReadData);
            zcTabWidget->addTab(zcMonitorCi,tr("ZC与CI"));
            zcTabWidget->setCurrentWidget(zcMonitorCi);
            zcHashTabWidget.insert("showZCtoCi",zcMonitorCi);
        }
        else if(msg.compare("showZcAlarm")==0)
        {
            ZcDayReport *zcDayReport=new ZcDayReport(zcTabWidget,zcReadData);
            zcTabWidget->addTab(zcDayReport,"报警信息");
            zcTabWidget->setCurrentWidget(zcDayReport);
            zcHashTabWidget.insert("showZcAlarm",zcDayReport);
        }
}
void ZcSystem::onEventFromMap(int type,QString deviceName)
    {
       //qDebug()<<"onEventFromMap type:"<<type<<" deviceName:"<<deviceName;
       QString widgetKey=deviceName+type;
       if(zcHashTabWidget.contains(widgetKey))
       {
           zcTabWidget->setCurrentWidget(zcHashTabWidget.value(widgetKey));
           return;
       }
       if(type==1)
       {
           ZcDayReport *zcDayReport=new ZcDayReport(zcTabWidget,zcReadData);
           zcTabWidget->addTab(zcDayReport,deviceName+"日报警信息");
           zcTabWidget->setCurrentWidget(zcDayReport);
           zcHashTabWidget.insert(widgetKey,zcDayReport);
       }
       else if(type==2)
       {
           ZcDayReport *zcDayReport=new ZcDayReport(zcTabWidget,zcReadData);
           zcTabWidget->addTab(zcDayReport,deviceName+"月报警信息");
           zcTabWidget->setCurrentWidget(zcDayReport);
           zcHashTabWidget.insert(widgetKey,zcDayReport);
       }
       else if(type==3)
       {
           ZcQueryDutinfo *zcQueryDutinfo = new ZcQueryDutinfo(zcTabWidget);
           zcTabWidget->addTab(zcQueryDutinfo,"设备信息");
           zcTabWidget->setCurrentWidget(zcQueryDutinfo);
           zcHashTabWidget.insert(widgetKey,zcQueryDutinfo);
       }
       //qDebug()<<"onEventFromMap hashMap size= "<<zcHashTabWidget.size();
}
void ZcSystem::onTabClose(int index)
{
    zcHashTabWidget.remove(zcHashTabWidget.key(zcTabWidget->currentWidget()));
    zcTabWidget->removeTab(index);
}
void ZcSystem::onWindowDestroy()
{
    zcSystemThread->quit();
    zcSystemThread->wait();
    delete zcSystemThread;
    zcSystemThread = NULL;
}
