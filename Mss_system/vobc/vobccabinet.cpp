#include "vobccabinet.h"
#include "vobcuicommon.h"
#include <QFile>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QMenu>

VobcCabinet::VobcCabinet(QWidget *parent) : QWidget(parent)
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
    transY=30;

    lastPoint.setX(0);
    lastPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);

    button_fan=new QPushButton(this);
    button_fan->setObjectName("button_fan");

    button_rtm=new QPushButton(this);

    button_unknown1=new QPushButton(this);
    button_unknown1->setObjectName("button_unknown1");

    widgetA=new QWidget(this);

    hLayout1=new QHBoxLayout;
    hLayout1->setContentsMargins(0,1,0,0);
    hLayout1->setSpacing(1);

    button_1=new QPushButton("1");
    button_2=new QPushButton("2");
    button_3=new QPushButton("3");
    button_4=new QPushButton("4");
    button_5=new QPushButton("5");
    button_6=new QPushButton("6");
    button_7=new QPushButton("7");
    button_8=new QPushButton("8");
    button_9=new QPushButton("9");
    button_10=new QPushButton("10");

    QList<QPushButton *> buttonAList;
    buttonAList<<button_1<<button_2<<button_3<<button_4<<button_5<<button_6<<button_7<<button_8<<button_9<<button_10;
    for (int i = 0; i < buttonAList.size(); i++)
    {
          buttonAList.at(i)->setMinimumSize(28,58);
          buttonAList.at(i)->setObjectName(QString("button_'%1'").arg(i));
          buttonAList.at(i)->installEventFilter(this);
    }

    hLayout1->addWidget(button_1);
    hLayout1->addWidget(button_2);
    hLayout1->addWidget(button_3);
    hLayout1->addWidget(button_4);
    hLayout1->addWidget(button_5);
    hLayout1->addWidget(button_6);
    hLayout1->addWidget(button_7);
    hLayout1->addWidget(button_8);
    hLayout1->addWidget(button_9);
    hLayout1->addWidget(button_10);
    widgetA->setLayout(hLayout1);

    button_unknown2=new QPushButton(this);
    button_unknown2->setObjectName("button_unknown2");

    widgetAB=new QWidget(this);

    widgetB=new QWidget(this);

    QHBoxLayout *hLayout2=new QHBoxLayout;
    hLayout2->setContentsMargins(0,1,0,0);
    hLayout2->setSpacing(1);

    button2_1=new QPushButton("1");
    button2_2=new QPushButton("2");
    button2_3=new QPushButton("3");
    button2_4=new QPushButton("4");
    button2_5=new QPushButton("5");
    button2_6=new QPushButton("6");
    button2_7=new QPushButton("7");
    button2_8=new QPushButton("8");
    button2_9=new QPushButton("9");
    button2_10=new QPushButton("10");

    QList<QPushButton *> buttonAList2;
    buttonAList2<<button2_1<<button2_2<<button2_3<<button2_4<<button2_5<<button2_6<<button2_7<<button2_8<<button2_9<<button2_10;
    for (int i = 0; i < buttonAList2.size(); i++)
    {
          buttonAList2.at(i)->setMinimumSize(28,58);
          buttonAList2.at(i)->setObjectName(QString("button2_'%1'").arg(i));
          buttonAList2.at(i)->installEventFilter(this);
    }

    hLayout2->addWidget(button2_1);
    hLayout2->addWidget(button2_2);
    hLayout2->addWidget(button2_3);
    hLayout2->addWidget(button2_4);
    hLayout2->addWidget(button2_5);
    hLayout2->addWidget(button2_6);
    hLayout2->addWidget(button2_7);
    hLayout2->addWidget(button2_8);
    hLayout2->addWidget(button2_9);
    hLayout2->addWidget(button2_10);

    widgetB->setLayout(hLayout2);

    button_unknown3=new QPushButton(this);
    button_unknown3->setObjectName("button_unknown3");

    button_relays=new QPushButton(this);
    button_relays->setObjectName("button_relays");

    button_btm=new QPushButton(this);
    button_btm->setObjectName("button_btm");

    button_conn=new QPushButton(this);
    button_conn->setObjectName("button_conn");

    menu = new QMenu(this);
    //menu->setStyleSheet("font: 10pt \"微软雅黑\";");
    //menu->addAction("查询日报表", this, this->queryDayInformation);
    //menu->addAction("查询设备状态表", this, &VOBCDevice::queryMonInformation);
    //menu->addSeparator();
    menu->addAction("查询日报警信息", this, &VobcCabinet::queryDayReport);
    menu->addAction("查询月报警信息", this, &VobcCabinet::queryMonReport);
    menu->addSeparator();
}

VobcCabinet::~VobcCabinet()
{

}

void VobcCabinet::paintEvent(QPaintEvent *event)
{
    event=event;
    //resize(1600,1200);
    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.setRenderHint(QPainter::Antialiasing);

    QTransform transform;
    transform.translate(transX,transY);
    transform.scale(b,b);
    p.setTransform(transform);

    drawButton(button_fan,100,100,300,20,"风扇");
    drawButton(button_rtm,100,120,300,60,"RTM(无线)");
    drawButton(button_unknown1,100,180,300,20,"");
    widgetA->setGeometry(100*b+transX,200*b+transY,300*b,60*b);
    drawButton(button_unknown2,100,260,300,20,"");
    widgetAB->setGeometry(100*b+transX,280*b+transY,300*b,20*b);
    widgetB->setGeometry(100*b+transX,300*b+transY,300*b,60*b);
    drawButton(button_unknown3,100,360,300,20,"");
    drawButton(button_relays,100,380,300,20,"继电器");
    drawButton(button_btm,100,400,300,60,"BTM");
    drawButton(button_conn,100,460,300,60,"连接器层");

    drawFrame(p,QPoint(100,100),false);
    drawFrame(p,QPoint(100,120),true);
    drawFrame(p,QPoint(100,180),false);
    drawFrame(p,QPoint(100,200),true);
    drawFrame(p,QPoint(100,260),false);
    drawFrame(p,QPoint(100,280),false);
    drawFrame(p,QPoint(100,300),true);
    drawFrame(p,QPoint(100,360),false);
    drawFrame(p,QPoint(100,380),false);
    drawFrame(p,QPoint(100,400),true);
    drawFrame(p,QPoint(100,460),true);

}

void VobcCabinet::drawFrame(QPainter& p,QPoint point,bool isHigh)
{
    int x=point.x();
    int y=point.y();
    p.setBrush(QBrush(QColor(165,165,165)));

    int height=20;
    if(isHigh)
    {
        height=60;
    }

    QPainterPath path;
    path.moveTo(x, y);
    path.lineTo(x,y+height);
    path.lineTo(x-30,y+height);
    path.lineTo(x-30,y);
    path.lineTo(x,y);

    path.moveTo(x+300,y);
    path.lineTo(x+330,y);
    path.lineTo(x+330,y+height);
    path.lineTo(x+300,y+height);
    path.lineTo(x+300,y);
    p.drawPath(path);

    p.setBrush(QBrush(QColor(255,255,255)));
    p.drawEllipse(QPoint(x-15,y+height/2),6,6);
    p.drawEllipse(QPoint(x+315,y+height/2),6,6);
}

void VobcCabinet::drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name)
{
    button->setGeometry(startX*b+transX,startY*b+transY,w*b,h*b);
    button->setText(name);
    button->installEventFilter(this);
}

void VobcCabinet::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        VOBC_DEBUG()<<"mousePressEvent";
        lastPoint=event->pos();
        lastPoint.setX(lastPoint.x()-transX);
        lastPoint.setY(lastPoint.y()-transY);
    }

}

void VobcCabinet::mouseMoveEvent(QMouseEvent *event)
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

void VobcCabinet::mouseReleaseEvent(QMouseEvent *event)
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
void VobcCabinet::wheelEvent(QWheelEvent *event)
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

void VobcCabinet::resizeEvent(QResizeEvent *event)
{
    event=event;
    if(this->parentWidget()!=NULL)
    {
        b=this->parentWidget()->width()/1024.0;
        transX=100*b;
        transY=30*b;

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

bool VobcCabinet::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (MouseEvent->buttons() == Qt::RightButton)
        {
                VOBC_DEBUG()<<"eventFilter 2:"<<obj->objectName();
                rightPressButton=obj;
                menu->exec(QCursor::pos());
        }
    }

    return QObject::eventFilter(obj, event);

}

void VobcCabinet::queryDayInformation()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(1,deviceName);
}

void VobcCabinet::queryMonInformation()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(2,deviceName);
}

void VobcCabinet::queryDayReport()
{
    VOBC_DEBUG()<<"queryDayReport:"<<rightPressButton->objectName();
    QString deviceName=rightPressButton->objectName();
    emit showReport(3,deviceName);
}

void VobcCabinet::queryMonReport()
{
    QString deviceName=rightPressButton->objectName();
    emit showReport(4,deviceName);
}

