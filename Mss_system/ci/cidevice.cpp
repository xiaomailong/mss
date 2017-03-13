#include "cidevice.h"
#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QDebug>

CiDevice::CiDevice(QWidget *parent) : QWidget(parent)
{
    QFile styleSheet("://qss/ci.qss");
    if (!styleSheet.open(QFile::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    this->setStyleSheet(styleSheet.readAll());
    styleSheet.close();

    scale = 1.0;
    transX=100;
    transY=50;
    startPoint.setX(0);
    startPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);

    hashDeviceMap.insert(4,"CI");
    hashDeviceMap.insert(5,"jidianqi");
    hashDeviceMap.insert(6,"jizhou");
    hashDeviceMap.insert(7,"LEU");
    hashDeviceMap.insert(8,"PSD");
    hashDeviceMap.insert(9,"ESP");
    hashDeviceMap.insert(10,"IBP");
    hashDeviceMap.insert(11,"SPKS");
    hashDeviceMap.insert(12,"IO");
    hashDeviceMap.insert(13,"jidianqi_out");
    hashDeviceMap.insert(14,"PSD_out");
    hashDeviceMap.insert(15,"ESP_out");
    hashDeviceMap.insert(16,"IBP_out");
    list.clear();

    buttonCI = new QPushButton("联锁",this);
    buttonCI->setObjectName("buttonCI");

    buttonRelay = new QPushButton("继电器\n接口柜",this);
    buttonRelay->setObjectName("buttonRelay");

    buttonAxle = new QPushButton("计轴",this);
    buttonAxle->setObjectName("buttonAxle");

    buttonLEU = new QPushButton("LEU",this);
    buttonLEU->setObjectName("LEU");

    buttonPSD = new QPushButton("PSD",this);
    buttonPSD->setObjectName("PSD");

    buttonESP = new QPushButton("ESP",this);
    buttonESP->setObjectName("ESP");

    buttonIBP = new QPushButton("IBP",this);
    buttonIBP->setObjectName("IBP");

    buttonSPKS = new QPushButton("SPKS",this);
    buttonSPKS->setObjectName("SPKS");

    buttonIO = new QPushButton("远程IO",this);
    buttonIO->setObjectName("IO");

    buttonRelayOut = new QPushButton("继电器\n接口柜",this);
    buttonRelayOut->setObjectName("buttonRelayOut");

    buttonPSDOut = new QPushButton("PSD",this);
    buttonPSDOut->setObjectName("PSDOut");

    buttonESPOut = new QPushButton("ESP",this);
    buttonESPOut->setObjectName("ESPOut");

    buttonIBPOut = new QPushButton("IBP",this);
    buttonIBPOut->setObjectName("IBPOut");

    buttonAxle1 = new CiAxleCounter(this);
    buttonAxle1->setObjectName("buttonAxle1");

    buttonAxle2 = new CiAxleCounter(this);
    buttonAxle2->setObjectName("buttonAxle2");

    buttonPointSwitch = new CiPointSwitch(this);
    buttonPointSwitch->setObjectName("buttonPointSwitch");

    buttonSignalMachine = new CiSignalMachine(this);
    buttonSignalMachine->setObjectName("buttonSignalMachine");

    buttonTransponders1 = new CiTransponders(this);
    buttonTransponders1->setObjectName("buttonTransponders1");

    buttonTransponders2 = new CiTransponders(this);
    buttonTransponders2->setObjectName("buttonTransponders2");


    equipmentStationText = new QLabel("设备集中站",this);
    equipmentNonCentralizedStationText = new QLabel("设备非集中站",this);
    ethernetText1 = new QLabel("以太网",this);
    ethernetText2 = new QLabel("RS422",this);
    ethernetText3 = new QLabel("以太网/RS422",this);
    relayText1 = new QLabel("继电",this);
    relayText2 = new QLabel("继电",this);
    sourceText = new QLabel("有源应答器",this);
    noSourceText = new QLabel("无源应答器",this);
    pointSwitchText = new QLabel("转辙机",this);
    axleCounterText = new QLabel("计轴器",this);
    signalMachineText = new QLabel("信号机",this);

    menu = new QMenu(this);
    menu->addAction("查询设备状态表", this, &CiDevice::queryDeviceStatesReport);
    menu->addSeparator();
    menu->addAction("查询报警信息", this, &CiDevice::queryAlarmReport);
    menu->addSeparator();

    connect(this,&CiDevice::sendStateToSignal,buttonSignalMachine,&CiSignalMachine::onEventFromDevice);
    connect(this,&CiDevice::sendAlarmToSignal,buttonSignalMachine,&CiSignalMachine::onAlarmFromDevice);
    connect(this,&CiDevice::sendStateToTransponders,buttonTransponders1,&CiTransponders::onEventFromDevice);
    connect(this,&CiDevice::sendAlarmToTransponders,buttonTransponders1,&CiTransponders::onAlarmFromDevice);
    connect(this,&CiDevice::sendStateToZhuanzhe,buttonPointSwitch,&CiPointSwitch::onEventFromDevice);
    connect(this,&CiDevice::sendAlarmToZhuanzhe,buttonPointSwitch,&CiPointSwitch::onAlarmFromDevice);

}
CiDevice::~CiDevice()
{

}

void CiDevice::paintEvent(QPaintEvent *event)
{
    event = event;
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setRenderHint(QPainter::Antialiasing);

    QTransform transform;
    transform.translate(transX,transY);
    transform.scale(scale,scale);
    painter.setTransform(transform);
    //drawDashLine
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);

    QPainterPath leftRect;
    leftRect.moveTo(40,50);
    leftRect.lineTo(200,50);
    leftRect.lineTo(200,500);
    leftRect.lineTo(40,500);
    leftRect.lineTo(40,50);
    painter.drawPath(leftRect);

    QPainterPath rightRect;
    rightRect.moveTo(350,50);
    rightRect.lineTo(980,50);
    rightRect.lineTo(980,500);
    rightRect.lineTo(350,500);
    rightRect.lineTo(350,50);
    painter.drawPath(rightRect);

    QPainterPath left_PSD_ESP_IBP;
    left_PSD_ESP_IBP.moveTo(78,310);
    left_PSD_ESP_IBP.lineTo(78,450);
    left_PSD_ESP_IBP .moveTo(117,310);
    left_PSD_ESP_IBP.lineTo(117,450);
    left_PSD_ESP_IBP .moveTo(157,310);
    left_PSD_ESP_IBP.lineTo(157,450);
    painter.drawPath(left_PSD_ESP_IBP);

    QPainterPath rightCiAxle;
    rightCiAxle.moveTo(430,250);
    rightCiAxle.lineTo(430,160);
    rightCiAxle.lineTo(550,160);
    painter.drawPath(rightCiAxle);

    //drawSolidLine
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    QPainterPath leftIORelay;
    leftIORelay.moveTo(120,210);
    leftIORelay.lineTo(120,250);
    painter.drawPath(leftIORelay);

    QPainterPath CiIOPath;
    CiIOPath.moveTo(120,170);
    CiIOPath.lineTo(120,130);
    CiIOPath.lineTo(550,130);
    painter.drawPath(CiIOPath);

    QPainterPath rightAxlePath;
    rightAxlePath.moveTo(460,280);
    rightAxlePath.lineTo(550,280);
    rightAxlePath.moveTo(416,538);
    rightAxlePath.lineTo(416,250);
    rightAxlePath.moveTo(440,250);
    rightAxlePath.lineTo(440,510);
    rightAxlePath.lineTo(496,510);
    rightAxlePath.lineTo(496,598);
    painter.drawPath(rightAxlePath);

    QPainterPath rightRelayPath;
    rightRelayPath.moveTo(560,310);
    rightRelayPath.lineTo(560,350);
    rightRelayPath.lineTo(78,350);

    rightRelayPath.moveTo(570,310);
    rightRelayPath.lineTo(570,370);
    rightRelayPath.lineTo(117,370);

    rightRelayPath.moveTo(580,310);
    rightRelayPath.lineTo(580,390);
    rightRelayPath.lineTo(157,390);

    rightRelayPath.moveTo(590,310);
    rightRelayPath.lineTo(590,600);

    rightRelayPath.moveTo(600,310);
    rightRelayPath.lineTo(600,495);
    rightRelayPath.lineTo(738,495);
    rightRelayPath.lineTo(738,560);

    rightRelayPath.moveTo(610,310);
    rightRelayPath.lineTo(610,390);
    rightRelayPath.lineTo(678,390);
    rightRelayPath.lineTo(678,450);

    rightRelayPath.moveTo(620,310);
    rightRelayPath.lineTo(620,370);
    rightRelayPath.lineTo(717,370);
    rightRelayPath.lineTo(717,450);

    rightRelayPath.moveTo(630,310);
    rightRelayPath.lineTo(630,350);
    rightRelayPath.lineTo(757,350);
    rightRelayPath.lineTo(757,450);

    rightRelayPath.moveTo(640,310);
    rightRelayPath.lineTo(640,330);
    rightRelayPath.lineTo(807,330);
    rightRelayPath.lineTo(807,450);

    painter.drawPath(rightRelayPath);

    QPainterPath rightCIRelay;
    rightCIRelay.moveTo(600,180);
    rightCIRelay.lineTo(600,250);
    painter.drawPath(rightCIRelay);

    QPainterPath rightCILEU;
    rightCILEU.moveTo(650,140);
    rightCILEU.lineTo(870,140);
    rightCILEU.lineTo(870,250);
    painter.drawPath(rightCILEU);

    QPainterPath rightLEUPath;
    rightLEUPath.moveTo(870,280);
    rightLEUPath.lineTo(870,580);
    painter.drawPath(rightLEUPath);

    //drawArrows
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));

    drawArrows(painter,120,170,CiDevice::directions::down);
    drawArrows(painter,550,130,CiDevice::directions::right);

    drawArrows(painter,120,210,CiDevice::directions::up);
    drawArrows(painter,120,250,CiDevice::directions::down);

    drawArrows(painter,430,250,CiDevice::directions::down);
    drawArrows(painter,550,160,CiDevice::directions::right);

    drawArrows(painter,600,250,CiDevice::directions::down);
    drawArrows(painter,600,180,CiDevice::directions::up);

    drawArrows(painter,650,140,CiDevice::directions::left);
    drawArrows(painter,870,250,CiDevice::directions::down);

    drawArrows(painter,550,280,CiDevice::directions::right);

    //drawButtons
    drawButtons(buttonCI,100,80,550,100);
    drawButtons(buttonRelay,100,60,550,250);
    drawButtons(buttonAxle,60,60,400,250);
    drawButtons(buttonLEU,70,60,835,250);
    drawButtons(buttonPSD,35,35,660,450);
    drawButtons(buttonESP,35,35,700,450);
    drawButtons(buttonIBP,35,35,740,450);
    drawButtons(buttonSPKS,55,35,780,450);
    drawButtons(buttonIO,80,40,80,170);
    drawButtons(buttonRelayOut,100,60,70,250);
    drawButtons(buttonPSDOut,35,35,60,450);
    drawButtons(buttonESPOut,35,35,100,450);
    drawButtons(buttonIBPOut,35,35,140,450);
    drawButtons(buttonAxle1,32,36,400,520);
    drawButtons(buttonAxle2,32,36,480,580);
    drawButtons(buttonSignalMachine,30,60,730,545);
    drawButtons(buttonPointSwitch,50,50,565,575);
    drawButtons(buttonTransponders1,20,20,860,580);
    drawButtons(buttonTransponders2,20,20,950,580);

    //drawLabel
     QFont font = painter.font();
     drawLabel(equipmentStationText,font,12,380, 70, 150, 30);
     drawLabel(equipmentNonCentralizedStationText,font,12,80, 70, 150, 30);

     drawLabel(ethernetText1,font,8,260, 105, 50, 30);
     drawLabel(ethernetText2,font,8,470, 135, 50, 30);
     drawLabel(ethernetText3,font,8,750, 115, 100, 30);

     drawLabel(relayText1,font,8,120, 215, 30, 30);
     drawLabel(relayText2,font,8,490, 260, 30, 30);

     drawLabel(pointSwitchText,font,8,620, 560, 50, 30);
     drawLabel(axleCounterText,font,8,510, 560, 50, 30);
     drawLabel(signalMachineText,font,8,750, 560, 50, 30);
     drawLabel(sourceText,font,8,870, 560, 70, 30);
     drawLabel(noSourceText,font,8,960, 560, 70, 30);

     QPainterPath safeRedMainLinePath;
     safeRedMainLinePath.moveTo(10,5);
     safeRedMainLinePath.lineTo(1024,5);
     pen.setColor(Qt::red);
     pen.setWidth(6);
     painter.setPen(pen);
     painter.drawPath(safeRedMainLinePath);

     QPainterPath safeBlueMainLinePath;
     safeBlueMainLinePath.moveTo(10,20);
     safeBlueMainLinePath.lineTo(1024,20);
     pen.setColor(Qt::blue);
     pen.setWidth(6);
     painter.setPen(pen);
     painter.drawPath(safeBlueMainLinePath);

     QPainterPath safeRedViceLinePath;
     safeRedViceLinePath.moveTo(610,9);
     safeRedViceLinePath.lineTo(610,100);
     pen.setColor(Qt::red);
     pen.setWidth(3);
     painter.setPen(pen);
     painter.drawPath(safeRedViceLinePath);

     QPainterPath safeBlueViceLinePath;
     safeBlueViceLinePath.moveTo(590,20);
     safeBlueViceLinePath.lineTo(590,100);
     pen.setColor(Qt::blue);
     pen.setWidth(3);
     painter.setPen(pen);
     painter.drawPath(safeBlueViceLinePath);

     pen.setColor(Qt::black);
     pen.setWidth(2);
     painter.setPen(pen);
     int railStartX=40;
     int railStartY=630;
     for(int i=0;i<50;i++)
     {
        QPainterPath railPath;
        railPath.moveTo(railStartX+i*20,railStartY);
        railPath.lineTo(railStartX+i*20,railStartY+150);
        painter.drawPath(railPath);
     }

     QPainterPath railLongPath;
     railLongPath.moveTo(railStartX,railStartY+30);
     railLongPath.lineTo(railStartX+50*20,railStartY+30);

     railLongPath.moveTo(railStartX,railStartY+120);
     railLongPath.lineTo(railStartX+50*20,railStartY+120);
     painter.drawPath(railLongPath);

     int ForkStartX = 200;
     int ForkStartY = 400;
     painter.rotate(25);
     for(int i=10;i<25;i++)
     {
        QPainterPath ForkPath;
        ForkPath.moveTo(ForkStartX+i*20,ForkStartY);
        ForkPath.lineTo(ForkStartX+i*20,ForkStartY+150);
        painter.drawPath(ForkPath);
     }
     QPainterPath ForkLongPath;
     ForkLongPath.moveTo(ForkStartX+200,ForkStartY+30);
     ForkLongPath.lineTo(ForkStartX+200+14*20,ForkStartY+30);

     ForkLongPath.moveTo(ForkStartX+200,ForkStartY+120);
     ForkLongPath.lineTo(ForkStartX+200+14*20,ForkStartY+120);
     painter.drawPath(ForkLongPath);

}

void CiDevice::drawButtons(QPushButton *button,int width,int height,int x, int y)
{
    button->setGeometry(x*scale+transX,y*scale+transY,width*scale,height*scale);
    button->installEventFilter(this);
    if(list.contains(button->objectName()))
    {
        button->setStyleSheet("QPushButton{border-image: url(://images/close.png);}");
    }else
    {
        button->setStyleSheet("QPushButton{border-style:outset;}");
    }
}

void CiDevice::drawArrows(QPainter &painter, qreal x, qreal y, int direction)
{
   QPointF arrow[3];
   switch (direction)
   {
     case 0:
         arrow[0] = QPointF(x, y);
         arrow[1] = QPointF(x-3, y+6);
         arrow[2] = QPointF(x+3, y+6);
         painter.drawPolygon(arrow, 3);
         break;
     case 1:
         arrow[0] = QPointF(x, y);
         arrow[1] = QPointF(x-3, y-6);
         arrow[2] = QPointF(x+3, y-6);
         painter.drawPolygon(arrow, 3);
         break;
     case 2:
         arrow[0] = QPointF(x, y);
         arrow[1] = QPointF(x+6, y-3);
         arrow[2] = QPointF(x+6, y+3);
         painter.drawPolygon(arrow, 3);
         break;
     case 3:
         arrow[0] = QPointF(x, y);
         arrow[1] = QPointF(x-6, y-3);
         arrow[2] = QPointF(x-6, y+3);
         painter.drawPolygon(arrow, 3);
         break;
     default:
         break;
   }
}

void CiDevice::drawLabel(QLabel *label, QFont mfont, int size, int x, int y, int width, int height)
{
    mfont.setPointSize(size*scale);
    QRect r ={int(x*scale+transX),
              int(y*scale+transY),
              int(width*scale),
              int(height*scale)};
    label->setFont(mfont);
    label->setGeometry(r);
}

void CiDevice::setDeviceToolTip(QObject *object)
{
    QString strTip=QString("设备名称:CI系统子设备\n厂商信息:BYD\n起始时间:2011-01-01\n软件版本:1.0\n基本配置");

    if(object == buttonCI&&buttonCI->toolTip().isEmpty())
    {
        buttonCI->setToolTip(strTip);
        return;
    }
    if(object == buttonRelay&&buttonRelay->toolTip().isEmpty())
    {
        buttonRelay->setToolTip(strTip);
        return;
    }
    if(object == buttonIO&&buttonIO->toolTip().isEmpty())
    {
        buttonIO->setToolTip(strTip);
        return;
    }
    if(object == buttonRelayOut&&buttonRelayOut->toolTip().isEmpty())
    {
        buttonRelayOut->setToolTip(strTip);
        return;
    }
    if(object == buttonESP&&buttonESP->toolTip().isEmpty())
    {
        buttonESP->setToolTip(strTip);
        return;
    }
    if(object == buttonESPOut&&buttonESPOut->toolTip().isEmpty())
    {
        buttonESPOut->setToolTip(strTip);
        return;
    }
    if(object == buttonIBP&&buttonIBP->toolTip().isEmpty())
    {
        buttonIBP->setToolTip(strTip);
        return;
    }
    if(object == buttonIBPOut&&buttonIBPOut->toolTip().isEmpty())
    {
        buttonIBPOut->setToolTip(strTip);
        return;
    }
    if(object == buttonSPKS&&buttonSPKS->toolTip().isEmpty())
    {
        buttonSPKS->setToolTip(strTip);
        return;
    }
    if(object == buttonPSD&&buttonPSD->toolTip().isEmpty())
    {
        buttonPSD->setToolTip(CiXMLUtil::readXML("://xml/ci/cipsd.xml","PSD","1"));
        return;
    }
    if(object == buttonPSDOut&&buttonPSDOut->toolTip().isEmpty())
    {
        buttonPSDOut->setToolTip(CiXMLUtil::readXML("://xml/ci/cipsd.xml","PSD","2"));
        return;
    }
    if(object == buttonLEU&&buttonLEU->toolTip().isEmpty())
    {
        buttonLEU->setToolTip(CiXMLUtil::readXML("://xml/ci/cileu.xml","LEU","1"));
        return;
    }
    if(object == buttonAxle&&buttonAxle->toolTip().isEmpty())
    {
        buttonAxle->setToolTip(CiXMLUtil::readXML("://xml/ci/ciaxlecounter.xml","COUNTER","1"));
        return;
    }
    if(object == buttonAxle1&&buttonAxle1->toolTip().isEmpty())
    {
        buttonAxle1->setToolTip(CiXMLUtil::readXML("://xml/ci/ciaxlecounter.xml","COUNTER","1"));
        return;
    }
    if(object == buttonAxle2&&buttonAxle2->toolTip().isEmpty())
    {
        buttonAxle2->setToolTip(CiXMLUtil::readXML("://xml/ci/ciaxlecounter.xml","COUNTER","1"));
        return;
    }
    if(object == buttonSignalMachine&&buttonSignalMachine->toolTip().isEmpty())
    {
        buttonSignalMachine->setToolTip(CiXMLUtil::readXML("://xml/ci/cisignallamp.xml","LAMP","1"));
        return;
    }
    if(object == buttonPointSwitch&&buttonPointSwitch->toolTip().isEmpty())
    {
        buttonPointSwitch->setToolTip(CiXMLUtil::readXML("://xml/ci/ciswitch.xml","SWITCH","1"));
        return;
    }
    if(object == buttonTransponders1&&buttonTransponders1->toolTip().isEmpty())
    {
        buttonTransponders1->setToolTip(CiXMLUtil::readXML("://xml/ci/cileu.xml","LEU","1"));
        return;
    }
    if(object == buttonTransponders2&&buttonTransponders2->toolTip().isEmpty())
    {
        buttonTransponders2->setToolTip(CiXMLUtil::readXML("://xml/ci/cileu.xml","LEU","2"));
        return;
    }

}

void CiDevice::queryDeviceStatesReport()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(0,deviceName);
}

void CiDevice::resizeEvent(QResizeEvent *event)
{
    event = event;
    if(this->parentWidget() != NULL)
    {
        scale =this->parentWidget()->width()/1280.0;
        transX = 100*scale;
        transY = 50*scale;
        if(scale<0.2)
        {
            scale=0.2;
        }else if(scale>3)
        {
            scale=3;
        }
        update();
    }
}

void CiDevice::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        scale+=0.05;
    }else
    {
        scale-=0.05;
    }
    if(scale<0.2)
    {
        scale=0.2;
    }else if(scale>3)
    {
        scale=3;
    }
    update();
}


void CiDevice::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        startPoint=event->pos();
        startPoint.setX(startPoint.x()-transX);
        startPoint.setY(startPoint.y()-transY);
    }
}

void CiDevice::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        endPoint = event->pos();
        transX = endPoint.x()-startPoint.x();
        transY = endPoint.y()-startPoint.y();
        update();
    }

}

void CiDevice::mouseReleaseEvent(QMouseEvent *event)
{
    event = event;

}

bool CiDevice::eventFilter(QObject *object, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (mouseEvent->buttons() == Qt::RightButton)
        {
            rightPressButton = object;
            menu->exec(QCursor::pos());
        }
    }else if (mouseEvent->type() == QEvent::Enter)
    {
        setDeviceToolTip(object);
    }else if (mouseEvent->type() == QEvent::Leave)
    {

    }
    return QObject::eventFilter(object, event);
}

void CiDevice::queryAlarmReport()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(1,deviceName);
}

void CiDevice::onEventFromCis(ci_ci_t* data)
{
    QString deviceOBJ;
    switch (data->device_code)
    {
    case 0://signallamp
        switch (data->alarm_level)
        {
        case 0:
            emit sendStateToSignal(data->device_state);
            break;
        case 1:
        case 2:
        case 3:
            emit sendAlarmToSignal(data->alarm_level);
            break;
        default:
            break;
        }
        break;
    case 1://Transponders
        switch (data->alarm_level)
        {
        case 0:
            emit sendStateToTransponders(data->device_state);
            break;
        case 1:
        case 2:
        case 3:
            emit sendAlarmToTransponders(data->alarm_level);
            break;
        default:
            break;
        }
        break;
    case 2:
        switch (data->alarm_level)
        {
        case 0:
            emit sendStateToZhuanzhe(data->device_state);
            break;
        case 1:
        case 2:
        case 3:
            emit sendAlarmToZhuanzhe(data->alarm_level);
            break;
        default:
            break;
        }
        break;
    case 3:
        switch (data->alarm_level)
        {
        case 0:
            emit sendStateToJizhou(data->device_state);
            break;
        case 1:
        case 2:
        case 3:
            emit sendAlarmToJizhou(data->alarm_level);
            break;
        default:
            break;
        }
        break;
    case 4:
        switch (data->alarm_level)
        {
        case 0:
            buttonCI->setStyleSheet("QPushButton{border-style:outset;}");
            break;
        case 1:
        case 2:
        case 3:
            buttonCI->setStyleSheet("QPushButton{border-image: url(://image/close.png);}");
            break;
        default:
            break;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        switch (data->alarm_level)
        {
        case 0:
            list.clear();
            break;
        case 1:
        case 2:
        case 3:
            list.clear();
            deviceOBJ = hashDeviceMap.value(data->device_code);
            list.append(deviceOBJ);
            update();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
