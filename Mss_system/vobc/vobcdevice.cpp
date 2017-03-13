#include "vobcdevice.h"
#include "vobcdomxml.h"
#include "vobcuicommon.h"
#include <QFile>
#include <QPushButton>
#include <QPainter>
#include <QTransform>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>

VobcDevice::VobcDevice(QWidget *parent) : QWidget(parent)
{
    QFile styleSheet("://qss/vobc.qss");
    if (!styleSheet.open(QFile::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    this->setStyleSheet(styleSheet.readAll());
    styleSheet.close();

    b=1;
    transX=100;
    transY=50;

    lastPoint.setX(0);
    lastPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);

    breakDownList.clear();

    initDeviceXmlInfo();

    buttonHead=new QPushButton(this);
    buttonHead->setObjectName("buttonHead");

    buttonTail=new QPushButton(this);
    buttonTail->setObjectName("buttonTail");

    buttonSw1=new QPushButton(this);
    buttonSw1->setObjectName("buttonSw1");

    buttonSw2=new QPushButton(this);
    buttonSw2->setObjectName("buttonSw2");

    buttonNet=new QPushButton(this);
    buttonNet->setObjectName("buttonNet");

    buttonIO=new QPushButton(this);
    buttonIO->setObjectName("buttonIO");

    buttonPower=new QPushButton(this);
    buttonPower->setObjectName("buttonPower");

    buttonAp1=new QPushButton(this);
    buttonAp1->setObjectName("buttonAp1");

    buttonAp2=new QPushButton(this);
    buttonAp2->setObjectName("buttonAp2");

    buttonDmi1=new QPushButton(this);
    buttonDmi1->setObjectName("buttonDmi1");

    buttonDmi2=new QPushButton(this);
    buttonDmi2->setObjectName("buttonDmi2");

    buttonBtm1=new QPushButton(this);
    buttonBtm1->setObjectName("buttonBtm1");

    buttonBtm11=new QPushButton(this);
    buttonBtm11->setObjectName("buttonBtm11");

    buttonBtm2=new QPushButton(this);
    buttonBtm2->setObjectName("buttonBtm2");

    buttonBtm22=new QPushButton(this);
    buttonBtm22->setObjectName("buttonBtm22");

    buttonRadar1=new QPushButton(this);
    buttonRadar1->setObjectName("buttonRadar1");

    buttonRadar2=new QPushButton(this);
    buttonRadar2->setObjectName("buttonRadar2");

    buttonPulse1=new QPushButton(this);
    buttonPulse1->setObjectName("buttonPulse1");

    buttonPulse2=new QPushButton(this);
    buttonPulse2->setObjectName("buttonPulse2");

    buttonPulse3=new QPushButton(this);
    buttonPulse3->setObjectName("buttonPulse3");

    buttonPulse4=new QPushButton(this);
    buttonPulse4->setObjectName("buttonPulse4");

    hashDeviceMap.insert(head,buttonHead);
    hashDeviceMap.insert(tail,buttonTail);
    hashDeviceMap.insert(dmi1,buttonDmi1);
    hashDeviceMap.insert(dmi2,buttonDmi2);
    hashDeviceMap.insert(btm1,buttonBtm1);
    hashDeviceMap.insert(btm2,buttonBtm2);
    hashDeviceMap.insert(io,buttonIO);
    hashDeviceMap.insert(net,buttonNet);
    hashDeviceMap.insert(power,buttonPower);
    hashDeviceMap.insert(sw1,buttonSw1);
    hashDeviceMap.insert(sw2,buttonSw2);
    hashDeviceMap.insert(ap1,buttonAp1);
    hashDeviceMap.insert(ap2,buttonAp2);
    hashDeviceMap.insert(radar1,buttonRadar1);
    hashDeviceMap.insert(radar2,buttonRadar2);
    hashDeviceMap.insert(pulse1,buttonPulse1);
    hashDeviceMap.insert(pulse3,buttonPulse3);

    menu = new QMenu(this);
    menu->setStyleSheet("font: 10pt \"微软雅黑\";");
    //menu->addAction("查询日报表", this, this->queryDayInformation);
    //menu->addAction("查询设备状态表", this, &VobcDevice::queryMonInformation);
    menu->addAction("查询日报警报表", this, &VobcDevice::queryDayReport);
    menu->addAction("查询月报警报表", this, &VobcDevice::queryMonReport);

}
VobcDevice::~VobcDevice()
{

}

void VobcDevice::paintEvent(QPaintEvent *event)
{
    //VOBC_DEBUG()<<"paintEvent";
    event=event;
    QPainter p(this);

    p.setPen(QPen(Qt::black, 2));
    p.setRenderHint(QPainter::Antialiasing);

    QTransform transform;
    transform.translate(transX,transY);
    transform.scale(b,b);
    p.setTransform(transform);

    drawButton(buttonHead,200,200,120,100,"VOBC 车头");
    drawButton(buttonTail,500,200,120,100,"VOBC 车尾");
    drawButton(buttonSw1,380,120,60,20,"交换机");
    drawButton(buttonSw2,380,160,60,20,"交换机");
    drawButton(buttonNet,380,200,60,20,"车辆网络");
    drawButton(buttonIO,380,240,60,20,"车辆IO");
    drawButton(buttonPower,380,280,60,20,"车载电源");
    drawButton(buttonAp1,210,120,50,50,"车载\nAP/LTE");
    drawButton(buttonAp2,560,120,50,50,"车载\nAP/LTE");
    drawButton(buttonDmi1,100,230,40,40,"DMI");
    drawButton(buttonDmi2,680,230,40,40,"DMI");
    drawButton(buttonBtm1,270,350,50,50,"BTM");
    drawButton(buttonBtm2,500,350,50,50,"BTM");
    drawButton(buttonBtm11,280,450,30,10,"");
    drawButton(buttonBtm22,510,450,30,10,"");
    drawButton(buttonRadar1,100,430,50,50,"多普勒\n雷达");
    drawButton(buttonRadar2,660,430,50,50,"多普勒\n雷达");
    drawButton(buttonPulse1,200,440,30,30,"");
    drawButton(buttonPulse2,240,440,30,30,"");
    drawButton(buttonPulse3,550,440,30,30,"");
    drawButton(buttonPulse4,590,440,30,30,"");

    QPainterPath left_path;
    left_path.moveTo(50, 300);
    left_path.lineTo(120,100);
    left_path.lineTo(360,100);
    left_path.lineTo(360,420);
    left_path.lineTo(80,420);
    left_path.lineTo(50,300);
    p.drawPath(left_path);

    QPainterPath right_path;
    right_path.moveTo(780,300);
    right_path.lineTo(710,100);
    right_path.lineTo(460,100);
    right_path.lineTo(460,420);
    right_path.lineTo(730,420);
    right_path.lineTo(780,300);
    p.drawPath(right_path);

    //draw ap antenna left
    QRectF rectangle1(225.0, 40.0, 20.0, 20.0);
    p.drawArc(rectangle1, -30 *16, 60*16);
    p.drawArc(rectangle1, 150 * 16, 60 * 16);
    QRectF rectangle2(230.0, 45.0, 10.0, 10.0);
    p.drawArc(rectangle2, -30 *16, 60*16);
    p.drawArc(rectangle2, 150 * 16, 60 * 16);
    QPainterPath antenna_path1;
    antenna_path1.moveTo(235,50);
    antenna_path1.lineTo(230,70);
    antenna_path1.lineTo(240,70);
    antenna_path1.lineTo(235,50);
    p.drawPath(antenna_path1);

    //draw ap antenna right
    QRectF rectangle3(575.0, 40.0, 20.0, 20.0);
    p.drawArc(rectangle3, -30 *16, 60*16);
    p.drawArc(rectangle3, 150 * 16, 60 * 16);
    QRectF rectangle4(580.0, 45.0, 10.0, 10.0);
    p.drawArc(rectangle4, -30 *16, 60*16);
    p.drawArc(rectangle4, 150 * 16, 60 * 16);
    QPainterPath antenna_path2;
    antenna_path2.moveTo(585,50);
    antenna_path2.lineTo(580,70);
    antenna_path2.lineTo(590,70);
    antenna_path2.lineTo(585,50);
    p.drawPath(antenna_path2);

    //draw ap antenna arraw
    drawCustomLine(p,QPoint(235,120),QPoint(235,70),Up,true,"");
    drawCustomLine(p,QPoint(585,120),QPoint(585,70),Up,true,"");
    //draw arrow
    drawCustomLine(p,QPoint(235,200),QPoint(235,170),Up,true,"以太网");
    drawCustomLine(p,QPoint(585,200),QPoint(585,170),Up,true,"以太网");

    drawCustomLine(p,QPoint(320,210),QPoint(380,210),Right,true,"MVB");
    drawCustomLine(p,QPoint(320,250),QPoint(380,250),Right,true,"继电器");
    drawCustomLine(p,QPoint(320,290),QPoint(380,290),Right,true,"110V");

    drawCustomLine(p,QPoint(440,210),QPoint(500,210),Right,true,"MVB");
    drawCustomLine(p,QPoint(440,250),QPoint(500,250),Right,true,"继电器");
    drawCustomLine(p,QPoint(440,290),QPoint(500,290),Right,true,"110V");

    QPainterPath sw_path;
    sw_path.moveTo(280,130);
    sw_path.lineTo(380,130);
    sw_path.moveTo(440,130);
    sw_path.lineTo(540,130);

    sw_path.moveTo(300,170);
    sw_path.lineTo(380,170);
    sw_path.moveTo(440,170);
    sw_path.lineTo(520,170);
    p.drawPath(sw_path);
    //draw sw arrow
    drawCustomLine(p,QPoint(280,130),QPoint(280,200),Down,false,"");
    drawCustomLine(p,QPoint(540,130),QPoint(540,200),Down,false,"");
    drawCustomLine(p,QPoint(300,170),QPoint(300,200),Down,false,"");
    drawCustomLine(p,QPoint(520,170),QPoint(520,200),Down,false,"");

    QPainterPath ap_path;
    ap_path.moveTo(210,145);
    ap_path.lineTo(200,145);
    ap_path.lineTo(200,70);
    ap_path.lineTo(370,70);
    ap_path.lineTo(370,150);
    ap_path.lineTo(410,150);

    ap_path.moveTo(410,120);
    ap_path.lineTo(410,70);
    ap_path.lineTo(620,70);
    ap_path.lineTo(620,145);
    p.drawPath(ap_path);
    //draw ap arrow
    drawCustomLine(p,QPoint(410,150),QPoint(410,160),Down,false,"");
    drawCustomLine(p,QPoint(620,145),QPoint(610,145),Left,false,"");
    //draw dmi arrow
    drawCustomLine(p,QPoint(140,250),QPoint(200,250),Right,true,"DMI");
    drawCustomLine(p,QPoint(620,250),QPoint(680,250),Right,true,"DMI");
    //draw radar arrow
    QPainterPath radar_path;
    radar_path.moveTo(125,290);
    radar_path.lineTo(125,430);

    radar_path.moveTo(685,290);
    radar_path.lineTo(685,430);
    p.drawPath(radar_path);
    drawCustomLine(p,QPoint(125,290),QPoint(200,290),Right,false,"RS422/脉冲");
    drawCustomLine(p,QPoint(685,290),QPoint(620,290),Left,false,"RS422/脉冲");
    //draw pulse arrow
    drawCustomLine(p,QPoint(215,440),QPoint(215,300),Up,false,"脉冲");
    drawCustomLine(p,QPoint(255,440),QPoint(255,300),Up,false,"脉冲");
    drawCustomLine(p,QPoint(565,440),QPoint(565,300),Up,false,"脉冲");
    drawCustomLine(p,QPoint(605,440),QPoint(605,300),Up,false,"脉冲");
    //draw btm arrow
    drawCustomLine(p,QPoint(295,450),QPoint(295,400),Up,false,"");
    drawCustomLine(p,QPoint(295,350),QPoint(295,300),Up,false,"RS422");
    drawCustomLine(p,QPoint(525,450),QPoint(525,400),Up,false,"");
    drawCustomLine(p,QPoint(525,350),QPoint(525,300),Up,false,"RS422");


}

void VobcDevice::resizeEvent(QResizeEvent * event)
{
    event=event;
    if(this->parentWidget()!=NULL)
    {
        b=this->parentWidget()->width()/1024.0;
        transX=100*b;
        transY=50*b;

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
}

void VobcDevice::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        VOBC_DEBUG()<<"mousePressEvent";
        lastPoint=event->pos();
        lastPoint.setX(lastPoint.x()-transX);
        lastPoint.setY(lastPoint.y()-transY);
    }

}

void VobcDevice::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint=event->pos();
        transX=endPoint.x()-lastPoint.x();
        transY=endPoint.y()-lastPoint.y();

        VOBC_DEBUG()<<"mouseMoveEvent transX:"<<transX<<" transY:"<<transY;
        update();
    }

}

void VobcDevice::mouseReleaseEvent(QMouseEvent *event)
{
    event=event;
//    if(event->button()==Qt::LeftButton)
//    {
//        endPoint=event->pos();
//        transX=endPoint.x()-lastPoint.x();
//        transY=endPoint.y()-lastPoint.y();
//        VOBC_DEBUG()<<"mouseReleaseEvent transX:"<<transX<<" transY:"<<transY;
//        update();
//    }
}

void VobcDevice::wheelEvent(QWheelEvent *event)
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

void VobcDevice::initDeviceXmlInfo()
{
    hashInfoMap.insert(head,VobcDomXML::readXML("://xml/vobc/vobc_atp.xml","atp",true));
    hashInfoMap.insert(tail,VobcDomXML::readXML("://xml/vobc/vobc_atp.xml","atp",false));
    hashInfoMap.insert(btm1,VobcDomXML::readXML("://xml/vobc/vobc_btm.xml","btm",true));
    hashInfoMap.insert(btm2,VobcDomXML::readXML("://xml/vobc/vobc_btm.xml","btm",false));

    hashInfoMap.insert(dmi1,VobcDomXML::readXML("://xml/vobc/vobc_dmi.xml","dmi",true));
    hashInfoMap.insert(dmi2,VobcDomXML::readXML("://xml/vobc/vobc_dmi.xml","dmi",false));
    hashInfoMap.insert(io,VobcDomXML::readXML("://xml/vobc/vobc_io.xml","io"));
    hashInfoMap.insert(net,VobcDomXML::readXML("://xml/vobc/vobc_net.xml","net"));
    hashInfoMap.insert(power,VobcDomXML::readXML("://xml/vobc/vobc_power.xml","power"));

    hashInfoMap.insert(sw1,VobcDomXML::readXML("://xml/vobc/vobc_sw.xml","sw",true));
    hashInfoMap.insert(sw2,VobcDomXML::readXML("://xml/vobc/vobc_sw.xml","sw",false));
    hashInfoMap.insert(radar1,VobcDomXML::readXML("://xml/vobc/vobc_radar.xml","radar",true));
    hashInfoMap.insert(radar2,VobcDomXML::readXML("://xml/vobc/vobc_radar.xml","radar",false));

    hashInfoMap.insert(ap1,VobcDomXML::readXML("://xml/vobc/vobc_ap.xml","ap",true));
    hashInfoMap.insert(ap2,VobcDomXML::readXML("://xml/vobc/vobc_ap.xml","ap",false));

    hashInfoMap.insert(pulse1,VobcDomXML::readXML("://xml/vobc/vobc_pulse.xml","pulse",true));
    hashInfoMap.insert(pulse3,VobcDomXML::readXML("://xml/vobc/vobc_pulse.xml","pulse",false));

}

void VobcDevice::setDeviceTip(QObject *object)
{
    //VOBC_DEBUG()<<"setDeviceTip ";
    if(object==buttonHead && buttonHead->toolTip().isEmpty())
    {
        buttonHead->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_atp.xml","atp","Dx-1654"));
        return;
    }
    if(object==buttonTail && buttonTail->toolTip().isEmpty())
    {
        buttonTail->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_atp.xml","atp","atp_2"));
        return;
    }
    if(object==buttonSw1 && buttonSw1->toolTip().isEmpty())
    {
        buttonSw1->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_sw.xml","sw","sw_1"));
        return;
    }
    if(object==buttonSw2 && buttonSw2->toolTip().isEmpty())
    {
        buttonSw2->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_sw.xml","sw","sw_2"));
        return;
    }
    if(object==buttonNet && buttonNet->toolTip().isEmpty())
    {
        buttonNet->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_net.xml","net","net_1"));
        return;
    }
    if(object==buttonIO && buttonIO->toolTip().isEmpty())
    {
        buttonIO->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_io.xml","io","io_1"));
        return;
    }
    if(object==buttonPower && buttonPower->toolTip().isEmpty())
    {
        buttonPower->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_power.xml","power","power_1"));
        return;
    }
    if(object==buttonAp1 && buttonAp1->toolTip().isEmpty())
    {
        buttonAp1->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_ap.xml","ap","ap_1"));
        return;
    }
    if(object==buttonAp2 && buttonAp2->toolTip().isEmpty())
    {
        buttonAp2->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_ap.xml","ap","ap_2"));
        return;
    }
    if(object==buttonDmi1 && buttonDmi1->toolTip().isEmpty())
    {
        buttonDmi1->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_dmi.xml","dmi","Dx-1654"));
        return;
    }
    if(object==buttonDmi2 && buttonDmi2->toolTip().isEmpty())
    {
        buttonDmi2->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_dmi.xml","dmi","dmi_2"));
        return;
    }
    if(object==buttonBtm1 && buttonBtm1->toolTip().isEmpty())
    {
        buttonBtm1->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_btm.xml","btm","btm_1"));
        return;
    }
    if(object==buttonBtm2 && buttonBtm2->toolTip().isEmpty())
    {
        buttonBtm2->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_btm.xml","btm","Dx-1654"));
        return;
    }
    if(object==buttonRadar1 && buttonRadar1->toolTip().isEmpty())
    {
        buttonRadar1->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_radar.xml","radar","radar_1"));
        return;
    }
    if(object==buttonRadar2 && buttonRadar2->toolTip().isEmpty())
    {
        buttonRadar2->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_radar.xml","radar","radar_2"));
        return;
    }
    if(object==buttonPulse1 && buttonPulse1->toolTip().isEmpty())
    {
        buttonPulse1->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_pulse.xml","pulse","pulse_1"));
        return;
    }
    if(object==buttonPulse2 && buttonPulse2->toolTip().isEmpty())
    {
        buttonPulse2->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_pulse.xml","pulse","pulse_2"));
        return;
    }
    if(object==buttonPulse3 && buttonPulse3->toolTip().isEmpty())
    {
        buttonPulse3->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_pulse.xml","pulse","pulse_3"));
        return;
    }
    if(object==buttonPulse4 && buttonPulse4->toolTip().isEmpty())
    {
        buttonPulse4->setToolTip(VobcDomXML::readInfoFromXML("://xml/vobc/vobc_pulse.xml","pulse","pulse_4"));
        return;
    }
}


bool VobcDevice::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (MouseEvent->buttons() == Qt::RightButton)
        {
                rightPressButton=obj;
                menu->exec(QCursor::pos());
        }
    }
    else if (MouseEvent->type() == QEvent::Enter)
    {
        setDeviceTip(obj);
    }
    else if (MouseEvent->type() == QEvent::Leave)
    {
        if (obj == buttonHead)
        {
            VOBC_DEBUG()<<"buttonHeadleave";
        }
    }

    return QObject::eventFilter(obj, event);

}

void VobcDevice::drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name)
{
    button->setGeometry(startX*b+transX,startY*b+transY,w*b,h*b);
    button->setText(name);
    button->installEventFilter(this);
}

void VobcDevice::drawCustomLine(QPainter& p,QPoint point1,QPoint point2,int direction, bool both,const QString& name)
{
    p.setPen(QPen(Qt::black, 1));

    QFont font = p.font();
    font.setPointSize(8);
    p.setFont(font);

    int x1=point1.x();
    int y1=point1.y();
    int x2=point2.x();
    int y2=point2.y();
    p.drawLine(point1,point2);

    // draw arrow
    int off_x = 5;
    int off_y = 5;
    QPainterPath path;
    if(direction==Up)
    {
        path.moveTo(x2-off_x, y2+off_y);
        path.lineTo(x2,y2);
        path.lineTo(x2+off_x,y2+off_y);
        p.drawText(QPoint(x2+off_x,y2+4*off_y), name);
    }
    else if(direction==Down)
    {
        path.moveTo(x2-off_x, y2-off_y);
        path.lineTo(x2,y2);
        path.lineTo(x2+off_x,y2-off_y);
        p.drawText(QPoint(x2+off_x,y2-4*off_y), name);
    }
    else if(direction==Left)
    {
        path.moveTo(x2+off_x, y2-off_y);
        path.lineTo(x2,y2);
        path.lineTo(x2+off_x,y2+off_y);
        p.drawText(QPoint(x2+4*off_x,y2-off_y), name);
    }
    else if(direction==Right)
    {
        path.moveTo(x2-off_x, y2-off_y);
        path.lineTo(x2,y2);
        path.lineTo(x2-off_x,y2+off_y);
        p.drawText(QPoint(x2-(x2-x1)/2-4*name.length(),y2-off_y), name);
    }

    p.drawPath(path);

    if(both)
    {
        direction=-direction;
        if(direction==Up)
        {
            path.moveTo(x1-off_x, y1+off_y);
            path.lineTo(x1,y1);
            path.lineTo(x1+off_x,y1+off_y);
        }
        else if(direction==Down)
        {
            path.moveTo(x1-off_x, y1-off_y);
            path.lineTo(x1,y1);
            path.lineTo(x1+off_x,y1-off_y);
        }
        else if(direction==Left)
        {
            path.moveTo(x1+off_x, y1-off_y);
            path.lineTo(x1,y1);
            path.lineTo(x1+off_x,y1+off_y);
        }
        else if(direction==Right)
        {
            path.moveTo(x1-off_x, y1-off_y);
            path.lineTo(x1,y1);
            path.lineTo(x1-off_x,y1+off_y);
        }

        p.drawPath(path);
    }
}

void VobcDevice::queryDayInformation()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(1,deviceName);
}

void VobcDevice::queryMonInformation()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(2,deviceName);
}

void VobcDevice::onAlarm(vobc_subsys_msg_t AtsMsg)
{
    for(int i=0;i<breakDownList.length();i++)
    {
        hashDeviceMap.value(breakDownList.at(i))->setStyleSheet("QPushButton{border-style:outset;}");
    }

    breakDownList.clear();
    vobc_subsys_msg_t alarmMsg=AtsMsg;
    QString deviceNo=QString::number(AtsMsg.dev_type);

    breakDownList.append(alarmMsg.dev_type);

//    QHashIterator<int,QStringList> it(hashInfoMap);
//    while (it.hasNext())
//    {
//        QStringList deviceNoList=it.next().value();
//        if(deviceNoList.contains(deviceNo))
//        {
//            breakDownList.append(it.key());
//        }
//    }
    for(int i=0;i<breakDownList.length();i++)
    {
        hashDeviceMap.value(breakDownList.at(i))->setStyleSheet("QPushButton{border-image: url(://images/close.png);}");
    }

}
void VobcDevice::queryDayReport()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(3,deviceName);
}

void VobcDevice::queryMonReport()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(4,deviceName);
}

