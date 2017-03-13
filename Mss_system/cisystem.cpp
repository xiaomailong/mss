#include "cisystem.h"
#include "cialarmreport.h"
#include "cirealtimereport.h"
#include "cimonitorats.h"
#include "cimonitorzc.h"
#include "cimonitorvobc.h"
#include "cidevice.h"
#include "mssdatadefine.h"
#include <QDebug>
#include <QThread>
CiSystem::CiSystem(QWidget *parent) : QMainWindow(parent)
{

    setWindowTitle(tr("CI 子系统"));
    setMinimumSize(1024,786);
    setAttribute(Qt::WA_DeleteOnClose, true);
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    connect(tabWidget,&QTabWidget::tabCloseRequested,this,&CiSystem::onTabClose);

    this->setCentralWidget(tabWidget);

    thread=new QThread(this);
    readData=new CiReadDataThread;
    readData->moveToThread(thread);
    thread->start();
    connect(this,&CiSystem::destroyed,this,&CiSystem::onWindowDestroy);
    connect(thread, &QThread::finished, readData, &QObject::deleteLater);

}

void CiSystem::closeEvent(QCloseEvent *event)
{
    event = event;
    emit sendEventToMss("close");
    close();
}

void CiSystem::onEventFromMss(const QString msg)
{
    if(hashTabWidget.contains(msg))
    {
        tabWidget->setCurrentWidget(hashTabWidget.value(msg));
        return;
    }

    if(msg.compare("deviceMap") == 0)
    {
        if(!hashTabWidget.contains("CiDevice"))
        {
            CiDevice * ciDevice = new CiDevice(tabWidget);
            tabWidget->addTab(ciDevice,tr("CI布局图"));
            hashTabWidget.insert("CiDevice",ciDevice);
            connect(ciDevice,&CiDevice::showReport,this,&CiSystem::onEventFromMap);
            connect(this,&CiSystem::sendEventToDevices,ciDevice,&CiDevice::onEventFromCis);
        }
        tabWidget->setCurrentWidget(hashTabWidget.value("CiDevice"));
    }else if(msg.compare("showCiAts") == 0)
    {
        CiMonitorAts *ciMonitorAts = new CiMonitorAts(tabWidget,readData);
        tabWidget->addTab(ciMonitorAts,tr("CI与ATS"));
        tabWidget->setCurrentWidget(ciMonitorAts);
        hashTabWidget.insert("showCiAts",ciMonitorAts);
    }else if(msg.compare("showCiZc") == 0)
    {
        CiMonitorZc *ciMonitorZc = new CiMonitorZc(tabWidget,readData);
        tabWidget->addTab(ciMonitorZc,tr("CI与ZC"));
        tabWidget->setCurrentWidget(ciMonitorZc);
        hashTabWidget.insert("showCiZc",ciMonitorZc);
    }else if(msg.compare("showCiVobc") == 0)
    {
        CiMonitorVobc *ciMonitorVobc = new CiMonitorVobc(tabWidget,readData);
        tabWidget->addTab(ciMonitorVobc,tr("CI与VOBC"));
        tabWidget->setCurrentWidget(ciMonitorVobc);
        hashTabWidget.insert("showCiVobc",ciMonitorVobc);
    }else if(msg.compare("showCiAlarm") == 0)
    {
        int type=1;
        QString deviceName="all";
        CiAlarmReport *allCIAlarmReport=new CiAlarmReport(tabWidget,readData,type,deviceName);
        tabWidget->addTab(allCIAlarmReport,"CI报警信息");
        tabWidget->setCurrentWidget(allCIAlarmReport);
        hashTabWidget.insert("showCiAlarm",allCIAlarmReport);
    }
}

void CiSystem::onEventFromMap(int type, QString deviceName)
{
    QString widgetKey=deviceName+type;
    if(hashTabWidget.contains(widgetKey))
    {
        tabWidget->setCurrentWidget(hashTabWidget.value(widgetKey));
        return;
    }
    if(type == 0)
    {
        CiRealTimeReport *realTimereportWidget = new CiRealTimeReport(tabWidget);
        tabWidget->addTab(realTimereportWidget,deviceName+"设备状态表");
        tabWidget->setCurrentWidget(realTimereportWidget);
        hashTabWidget.insert(widgetKey,realTimereportWidget);
    }else if(type == 1)
    {
        CiAlarmReport *ciReport=new CiAlarmReport(tabWidget,readData,type,deviceName);
        tabWidget->addTab(ciReport,deviceName+"报警统计表");
        tabWidget->setCurrentWidget(ciReport);
        hashTabWidget.insert(widgetKey,ciReport);
    }
}

void CiSystem::onTabClose(int index)
{
    hashTabWidget.remove(hashTabWidget.key(tabWidget->widget(index)));
    tabWidget->removeTab(index);
    if(tabWidget->count() == 0)
    {
        close();
    }
}
void CiSystem::receiveCiAlarm(ci_ci_t* data)
{
    if(ID_MESSAGE_CI == data->moduleid_code)
    {
        emit sendEventToDevices(data);
    }

}

void CiSystem::onWindowDestroy()
{
    thread->quit();
    thread->wait();
    delete thread;
    thread = NULL;
}
