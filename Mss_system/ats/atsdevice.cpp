#include "ats/atsdevice.h"
#include "ats/atsdomxml.h"
#include <QFile>
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QToolButton>
#include <QMenu>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>
#include <ats_data.h>

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


AtsDevice::AtsDevice(QWidget *parent) : QWidget(parent)
{
    QString qss;
    QFile qssFile(":/qss/ats.qss");
    qssFile.open(QFile::ReadOnly);
    if (qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }

    b=1;
    transX=100;
    transY=100;
    lastPoint.setX(0);
    lastPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);
    initViews();
}

AtsDevice::~AtsDevice()
{

}

void AtsDevice::initViews()
{
    //breakDownList.clear();

    initDeviceXmlInfo();
    //control center lable ...
    controlCenter = new QLabel(this);
    controlCenter->setObjectName("controlCenter");

    leftCenter = new QLabel(this);
    leftCenter->setObjectName("leftCenter");

    rightCenter = new QLabel(this);
    rightCenter->setObjectName("rightCenter");

    aNetwork = new QLabel(this);//A network
    aNetwork->setObjectName("aNetwork");

    bNetwork = new QLabel(this);
    bNetwork->setObjectName("bNetwork");

    QFont ft;
    ft.setPointSize(15);
    controlCenter->setFont(ft);

    //interchanger button1 & button2
    interChanger1 = new QPushButton(this);
    interChanger1->setObjectName("interChanger1");

    interChanger2 = new QPushButton(this);
    interChanger2->setObjectName("interChanger2");

    displayEditLable = new QLabel(this);
    displayEditLable->setObjectName("displayEditLable");

    displayEdit = new QPushButton(this);
    displayEdit->setObjectName("displayEdit");

    dispatcherLable = new QLabel(this);
    dispatcherLable->setObjectName("dispatcherLable");

    dispatcher = new QPushButton(this);
    dispatcher->setObjectName("dispatcher");

    printerLable = new QLabel(this);
    printerLable->setObjectName("printerLable");

    printer = new QPushButton(this);
    printer->setObjectName("printer");

    display = new QPushButton(this);
    display->setObjectName("display");

    displayLable = new QLabel(this);
    displayLable->setObjectName("displayLable");

    //right up

    applyServer1 = new QPushButton(this);
    applyServer1->setObjectName("applyServer1");

    applyServer1Lable = new QLabel(this);
    applyServer1Lable->setObjectName("applyServer1Lable");

    applyServer2Lable = new QLabel(this);
    applyServer2Lable->setObjectName("applyServer2Lable");

    applyServer2 = new QPushButton(this);
    applyServer2->setObjectName("applyServer2");

    //database server
    dbServer1Lable = new QLabel(this);
    dbServer1Lable->setObjectName("dbServer1Lable");

    dbServer1 = new QPushButton(this);
    dbServer1->setObjectName("dbServer1");

    diskArrayLabel = new QLabel(this);
    diskArrayLabel->setObjectName("diskArrayLabel");

    diskArray = new QPushButton(this);
    diskArray->setObjectName("diskArray");

    dbServer2Lable = new QLabel(this);
    dbServer2Lable->setObjectName("dbServer2Lable");

    dbServer2 = new QPushButton(this);
    dbServer2->setObjectName("dbServer2");

    //cs
    clockSystem = new QPushButton(this);
    clockSystem->setObjectName("clockSystem");

    descibeLable = new QLabel(this);
    descibeLable->setObjectName("descibeLable");
    descibeLable->setWordWrap(true);
    descibeLable->setAlignment(Qt::AlignTop);

    //right down

    largeScreenLable = new QLabel(this);
    largeScreenLable->setObjectName("largeScreenLable");

    largeScreen = new QPushButton(this);
    largeScreen->setObjectName("largeScreen");

    interfaceServer1Lable = new QLabel(this);
    interfaceServer1Lable->setObjectName("interfaceServer1Lable");

    interfaceServer1 = new QPushButton(this);
    interfaceServer1->setObjectName("interfaceServer1");

    interfaceServer2Lable = new QLabel(this);
    interfaceServer2Lable->setObjectName("interfaceServer2Lable");

    interfaceServer2 = new QPushButton(this);
    interfaceServer2->setObjectName("interfaceServer2");

    //4
    atsMaintenanceLable = new QLabel(this);
    atsMaintenanceLable->setObjectName("atsMaintenanceLable");

    atsMaintenance = new QPushButton(this);
    atsMaintenance->setObjectName("atsMaintenance");

    commServer1Lable = new QLabel(this);
    commServer1Lable->setObjectName("commServer1Lable");


    commServer1 = new QPushButton(this);
    commServer1->setObjectName("commServer1");

    commServer2Lable = new QLabel(this);
    commServer2Lable->setObjectName("commServer2Lable");

    commServer2 = new QPushButton(this);
    commServer2->setObjectName("commServer2");

    hashDeviceMap.insert(interchanger1,interChanger1);
    hashDeviceMap.insert(interchanger2,interChanger2);
    //workstation
    hashDeviceMap.insert(displayws,displayEdit);
    hashDeviceMap.insert(dispatherws,dispatcher);
    hashDeviceMap.insert(rundisplayws,display);
    hashDeviceMap.insert(largescreenws,largeScreen);
    hashDeviceMap.insert(atsmaintenancews,atsMaintenance);
    //printer
    hashDeviceMap.insert(colorprinter,printer);
    //server
    hashDeviceMap.insert(apply1,applyServer1);
    hashDeviceMap.insert(apply2,applyServer2);
    hashDeviceMap.insert(db1,dbServer1);
    hashDeviceMap.insert(db2,dbServer2);
    hashDeviceMap.insert(interface1,interfaceServer1);
    hashDeviceMap.insert(interface2,interfaceServer2);
    hashDeviceMap.insert(comm1,commServer1);
    hashDeviceMap.insert(comm2,commServer2);



    menu = new QMenu(this);
    menu->addAction("查询日报警报表", this, SLOT(queryDayReport()));
    menu->addAction("查询月报警报表", this, SLOT(queryMonthReport()));
    menu->addSeparator();
    menu->addAction("查询设备状态表", this, SLOT(queryDeviceState()));
    menu->addSeparator();
    //menu->addAction(QIcon(":/image/20.jpg"),"Q",this,SLOT(queryDayReport()));
}

void AtsDevice::initDeviceXmlInfo(){
    hashInfoMap.insert(interchanger1,AtsDomXml::readXML("://xml/ats/ats_interchanger.xml","interchanger"));
    hashInfoMap.insert(interchanger2,AtsDomXml::readXML("://xml/ats/ats_interchanger.xml","interchanger"));
    hashInfoMap.insert(displayws,AtsDomXml::readXML("://xml/ats/ats_workstation.xml","workstation"));
    hashInfoMap.insert(dispatherws,AtsDomXml::readXML("://xml/ats/ats_workstation.xml","workstation"));
    hashInfoMap.insert(rundisplayws,AtsDomXml::readXML("://xml/ats/ats_workstation.xml","workstation"));
    hashInfoMap.insert(largescreenws,AtsDomXml::readXML("://xml/ats/ats_workstation.xml","workstation"));
    hashInfoMap.insert(atsmaintenancews,AtsDomXml::readXML("://xml/ats/ats_workstation.xml","workstation"));
    hashInfoMap.insert(colorprinter,AtsDomXml::readXML("://xml/ats/ats_printer.xml","aprinter"));
    hashInfoMap.insert(apply1,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(apply2,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(db1,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(db2,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(interface1,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(interface2,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(comm1,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
    hashInfoMap.insert(comm2,AtsDomXml::readXML("://xml/ats/ats_server.xml","server"));
}

void AtsDevice::setDeviceTip(QObject *object){
    ATS_DEBUG()<<"setDeviceTip  object =" << object;
    if(object==interChanger1 && interChanger1->toolTip().isEmpty())
    {
        interChanger1->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_interchanger.xml","interchanger","interchanger1"));
        return;
    }
    if(object==interChanger2 && interChanger2->toolTip().isEmpty())
    {
        interChanger2->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_interchanger.xml","interchanger","interchanger2"));
        return;
    }

    if(object==displayEdit && displayEdit->toolTip().isEmpty())
    {
        displayEdit->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_workstation.xml","workstation","displayws"));
        return;
    }
    if(object==dispatcher && dispatcher->toolTip().isEmpty())
    {
        dispatcher->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_workstation.xml","workstation","dispatherws"));
        return;
    }
    if(object==display && display->toolTip().isEmpty()){
        display->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_workstation.xml","workstation","rundisplayws"));
        return;
    }
    if(object==largeScreen && largeScreen->toolTip().isEmpty())
    {
        largeScreen->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_workstation.xml","workstation","largescreenws"));
        return;
    }
    if(object==atsMaintenance && atsMaintenance->toolTip().isEmpty()){
        atsMaintenance->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_workstation.xml","workstation","atsmaintenancews"));
        return;
    }
    //printer
    if(object==printer && printer->toolTip().isEmpty())
    {
        printer->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_printer.xml","aprinter","colorprinter"));
        return;
    }
    //server
    if(object==applyServer1 && applyServer1->toolTip().isEmpty())
    {
        applyServer1->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","apply1"));
        return;
    }
    if(object==applyServer2 && applyServer2->toolTip().isEmpty())
    {
        applyServer2->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","apply2"));
        return;
    }
    if(object==dbServer1 && dbServer1->toolTip().isEmpty())
    {
        dbServer1->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","db1"));
        return;
    }
    if(object==dbServer2 && dbServer2->toolTip().isEmpty())
    {
        dbServer2->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","db2"));
        return;
    }
    if(object==interfaceServer1 && interfaceServer1->toolTip().isEmpty())
    {
        interfaceServer1->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","interface1"));
        return;
    }
    if(object==interfaceServer2 && interfaceServer2->toolTip().isEmpty())
    {
        interfaceServer2->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","interface2"));
        return;
    }
    if(object==commServer1 && commServer1->toolTip().isEmpty())
    {
        commServer1->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","comm1"));
        return;
    }
    if(object==commServer2 && commServer2->toolTip().isEmpty())
    {
        commServer2->setToolTip(AtsDomXml::readInfoFromXML("://xml/ats/ats_server.xml","server","comm2"));
        return;
    }
}

void AtsDevice::onShowAlarm(ats_mss_alarm_t *alarm_info)
{
    ATS_DEBUG()<<"AtsDevice::onShowAlarm sys_id:" << alarm_info->sys_id;
    ATS_DEBUG()<<"AtsDevice::onShowAlarm dev_id:" << alarm_info->dev_id;
    ATS_DEBUG()<<"AtsDevice::onShowAlarm dev_type" << alarm_info->dev_type;
    ATS_DEBUG()<<"AtsDevice::onShowAlarm alarm_code" << alarm_info->alarm_code;
    switch (alarm_info->dev_id) {
        case 0:
            if (alarm_info->alarm_code == 1)
            {
                displayEdit->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            } else
            {
                displayEdit->setStyleSheet("QPushButton{border-image: url(://images/station.jpg);}");
            }
            break;
        case 1:
            if (alarm_info->alarm_code == 1)
            {
                dispatcher->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                dispatcher->setStyleSheet("QPushButton{border-image: url(://images/station.jpg);}");
            }

            break;
        case 2:
            if (alarm_info->alarm_code == 1)
            {
                display->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                display->setStyleSheet("QPushButton{border-image: url(://images/station.jpg);}");
            }
            break;
        case 3:
            if (alarm_info->alarm_code == 1)
            {
                largeScreen->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                largeScreen->setStyleSheet("QPushButton{border-image: url(://images/station.jpg);}");
            }
            break;
        case 4:
            if (alarm_info->alarm_code == 1)
            {
                atsMaintenance->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                atsMaintenance->setStyleSheet("QPushButton{border-image: url(://images/station.jpg);}");
            }
        case 5:
            if (alarm_info->alarm_code == 1)
            {
                applyServer1->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                applyServer1->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        case 6:
            if (alarm_info->alarm_code == 1)
            {
                applyServer2->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                applyServer2->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        case 7:
            if (alarm_info->alarm_code == 1) {
                dbServer1->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            } else {
                dbServer1->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        case 8:
            if (alarm_info->alarm_code == 1)
            {
                dbServer2->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                dbServer2->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        case 9:
        case 10:
            if (alarm_info->alarm_code == 1)
            {
                interfaceServer1->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                interfaceServer1->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        case 11:
            if (alarm_info->alarm_code == 1)
            {
                interfaceServer2->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                interfaceServer2->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
            if (alarm_info->alarm_code == 1)
            {
                clockSystem->setStyleSheet("QPushButton{border-image: url(://images/error.jpg);}");
            }
            else
            {
                clockSystem->setStyleSheet("QPushButton{border-image: url(://images/server.jpg);}");
            }
            break;
        default:
            break;
    }
    delete alarm_info;
}

void AtsDevice::queryDayReport()
{
    ATS_DEBUG()<<"queryDayReport()";
    QString tempName = pressButton->objectName();
    emit showReport(1,tempName);
}

void AtsDevice::queryMonthReport()
{
   ATS_DEBUG()<<"queryMonthReport()";
   QString tempName = pressButton->objectName();
   emit showReport(2,tempName);
}

void AtsDevice::queryDeviceState()
{
   ATS_DEBUG()<<"queryDeviceState()";
   QString tempName = pressButton->objectName();
   emit showReport(0,tempName);
}

void AtsDevice::drawLabel(QLabel *label,int startX,int startY,int w,int h,QString name)
{
    label->setGeometry(startX*b+transX,startY*b+transY,w*b,h*b);
    label->setText(name);
}

void AtsDevice::drawLine(QPainter &p, int startX, int startY, int stopX, int stopY)
{
    p.drawLine(QPoint(startX,startY),QPoint(stopX,stopY));
}

void AtsDevice::drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name)
{
    button->setGeometry(startX*b+transX,startY*b+transY,w*b,h*b);
    button->setText(name);
    button->installEventFilter(this);
}

bool AtsDevice::eventFilter(QObject *object, QEvent *event)
{
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if (/*object == interChanger1 &&*/ event->type() == QEvent::MouseButtonPress)
    {
        if (MouseEvent->buttons() == Qt::RightButton)
        {
                pressButton = object;
                menu->exec(QCursor::pos());
        }
    }
    else if (MouseEvent->type() == QEvent::Enter)
    {
        ATS_DEBUG()<<"eventFilter  object =" << object;
        setDeviceTip(object);
    }
    return QObject::eventFilter(object, event);
}

void AtsDevice::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        ATS_DEBUG()<<"mousePressEvent";
        lastPoint=event->pos();
        lastPoint.setX(lastPoint.x()-transX);
        lastPoint.setY(lastPoint.y()-transY);
    }
}

void AtsDevice::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint=event->pos();
        transX=endPoint.x()-lastPoint.x();
        transY=endPoint.y()-lastPoint.y();

        ATS_DEBUG()<<"mouseMoveEvent transX:"<<transX<<" transY:"<<transY;
        update();
    }
}

void AtsDevice::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        b+=0.05;
    }
    else
    {
        b-=0.05;
    }
    if(b<0.2)
    {
        b=0.2;
    }
    else if(b>5)
    {
        b=5;
    }
    update();
}

void AtsDevice::paintEvent(QPaintEvent *event)
{
    event=event;
    QPainter p;
    p.begin(this);
    QPen pen;
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);// dotted line
    p.setPen(pen);

    QTransform transform;
    transform.translate(transX,transY);
    transform.scale(b,b);
    p.setTransform(transform);

    drawLabel(controlCenter,-20,-40,110,40,"控制中心ATS");
    drawLabel(leftCenter,400,-30,100,40,"中央控制室");
    drawLabel(rightCenter,850,-30,100,40,"信号设备室");
    drawLabel(aNetwork,-50,320,40,40,"A网");
    drawLabel(bNetwork,-50,370,40,40,"B网");
    drawLabel(displayEditLable,230,-10,150,30,"运行图编辑/显示工作站");
    drawLabel(dispatcherLable,430,60,150,30,"行车调度员工作站");
    drawLabel(printerLable,270,180,150,30,"A3彩色激光打印机");
    drawLabel(displayLable,430,180,150,30,"运行图显示工作站");
    drawLabel(applyServer1Lable,570,-10,70,30,"应用服务器1");
    drawLabel(applyServer2Lable,650,-10,70,30,"应用服务器2");
    drawLabel(dbServer1Lable,730,-10,80,30,"数据库服务器1");
    drawLabel(diskArrayLabel,775,60,50,30,"磁盘阵列");// disk array
    drawLabel(dbServer2Lable,840,-10,80,30,"数据库服务器2");
    drawLabel(descibeLable,1000,15,100,20*4,"IS CS/时钟系统/广播系统/无线系统/大屏显示等");
    drawLabel(largeScreenLable,570,240,100,30,"大屏接口工作站");
    drawLabel(interfaceServer1Lable,650,240,100,30,"接口服务器1");
    drawLabel(interfaceServer2Lable,730,240,100,30,"接口服务器2");
    drawLabel(atsMaintenanceLable,810,240,100,30,"ATS维护工作站");
    drawLabel(commServer1Lable,890,240,100,30,"通信服务器1");
    drawLabel(commServer2Lable,980,240,100,30,"通信服务器2");
    //drawLabel(ats_care_lable,810,240,100,30,"ATS维护工作站");


    drawButton(interChanger1,-20,230,50,35,"交换机1");
    drawButton(interChanger2,60,230,50,35,"交换机2");
    drawButton(displayEdit,230,15,50,40,"");
    drawButton(dispatcher,380,15,50,40,"");
    drawButton(printer,230,220,50,40,"");
    drawButton(display,380,220,50,40,"");
    drawButton(applyServer1,570,15,30,40,"");
    drawButton(applyServer2,650,15,30,40,"");
    drawButton(dbServer1,730,15,30,40,""); // db 1
    drawButton(diskArray,785,40,30,30,"");//disk
    drawButton(dbServer2,840,15,30,40,"");// db 2
    drawButton(clockSystem,920,15,30,40,"");
    drawButton(largeScreen,570,200,50,40,"");
    drawButton(interfaceServer1,650,200,30,40,"");
    drawButton(interfaceServer2,730,200,30,40,"");
    drawButton(atsMaintenance,810,200,50,40,"");
    drawButton(commServer1,890,200,30,40,"");
    drawButton(commServer2,980,200,30,40,"");

    //Dotted line   .Control Center
    p.drawRoundedRect(-50,-50,1200,350,20,20);//outside
    p.drawRoundedRect(200,-25,300,300,10,10);//inside /left
    p.drawRoundedRect(550,-25,550,300,10,10);//inside /right
    p.drawRoundedRect(990,5,105,60,10,10);//describe

    //descibe
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    p.setPen(pen);
    drawLine(p,920,35,990,35);

    //blue part
    pen.setWidth(2);
    pen.setColor(QColor(Qt::blue));
    pen.setStyle(Qt::SolidLine);
    p.setPen(pen);
    p.drawRoundedRect(150,85,900,75,15,15);
    drawLine(p,-50,350,650,350);
    drawLine(p,260,55,260,85);
    drawLine(p,410,55,410,85);
    //up:Application server
    drawLine(p,590,45,590,85);
    drawLine(p,670,45,670,85);
    drawLine(p,750,45,750,85);
    drawLine(p,860,45,860,85);
    drawLine(p,940,45,940,85);
    //down:Large-screen interface workstation
    drawLine(p,600,160,600,200);
    drawLine(p,670,160,670,200);
    drawLine(p,750,160,750,200);
    drawLine(p,840,160,840,200);
    drawLine(p,910,160,910,200);
    drawLine(p,1000,160,1000,200);
    drawLine(p,260,160,260,220);//down
    drawLine(p,410,160,410,220);//down
    QPainterPath path; //Blue Corner part
    path.moveTo(85,230);
    path.lineTo(85,150);
    path.lineTo(150,150);
    p.drawPath(path);

    drawLine(p,200,270,200,350);//interchanger & A network Connected line

    //red part
    pen.setWidth(2);
    pen.setColor(QColor(Qt::red));
    pen.setStyle(Qt::SolidLine);
    p.setPen(pen);
    p.drawRoundedRect(175,100,850,45,15,15);
    drawLine(p,-50,400,650,400);//a network line
    drawLine(p,250,55,250,100);//up
    drawLine(p,400,55,400,100);//up
    drawLine(p,250,145,250,220);//down
    drawLine(p,400,145,400,220);//down

    //up:Application server(red part)
    drawLine(p,580,45,580,100);
    drawLine(p,660,45,660,100);
    drawLine(p,740,45,740,100);
    drawLine(p,850,45,850,100);
    drawLine(p,930,45,930,100);
    //down:Large-screen interface workstation(red part)
    drawLine(p,590,145,590,200);
    drawLine(p,660,145,660,200);//interface_server2
    drawLine(p,740,145,740,200);
    drawLine(p,830,145,830,200);
    drawLine(p,900,145,900,200);
    drawLine(p,990,145,990,200);

    QPainterPath path1;//Red Corner part
    path1.moveTo(5,230);
    path1.lineTo(5,125);
    path1.lineTo(175,125);
    p.drawPath(path1);
    drawLine(p,5,265,5,400);//interchanger & B network Connected line

    pen.setWidth(1);
    pen.setColor(QColor(180,180,180));
    p.setPen(pen);

    //0207 add triangle
    QPainterPath path_triangle1;
    path_triangle1.moveTo(735,20);
    path_triangle1.lineTo(865,20);
    path_triangle1.lineTo(800,65);
    path_triangle1.lineTo(735,20);
    p.drawPath(path_triangle1);

    QPainterPath path_triangle2;
    path_triangle2.moveTo(755,25);
    path_triangle2.lineTo(845,25);
    path_triangle2.lineTo(800,60);
    path_triangle2.lineTo(755,25);
    p.drawPath(path_triangle2);
    //end
    p.end();
}
