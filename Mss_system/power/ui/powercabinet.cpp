#include "power/ui/powercabinet.h"
#include <QDebug>
#include <QFile>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>


Powercabinet::Powercabinet(QWidget *parent) : QWidget(parent)
{
    QFile styleSheet("://qss/vobc.qss");
    if (!styleSheet.open(QFile::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    this->setStyleSheet(styleSheet.readAll());
    styleSheet.close();

    scale=1;
    transX=100;
    transY=30;

    lastPoint.setX(0);
    lastPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);

    button_fan=new QPushButton(this);

    button_rtm=new QPushButton(this);

    button_unknown1=new QPushButton(this);
    button_unknown1->setObjectName("button_unknown1");

    widgetA=new QWidget(this);

    hLayout1=new QHBoxLayout;
    hLayout1->setContentsMargins(0,1,0,0);
    hLayout1->setSpacing(1);

    button_1=new QPushButton("电源");
    button_2=new QPushButton("1");
    button_3=new QPushButton("2");
    button_4=new QPushButton("3");
    button_5=new QPushButton("4");
    button_6=new QPushButton("电源");
    button_7=new QPushButton("1");
    button_8=new QPushButton("2");
    button_9=new QPushButton("3");
    button_10=new QPushButton("4");

    QList<QPushButton *> buttonAList;
    buttonAList<<button_1<<button_2<<button_3<<button_4<<button_5<<button_6<<button_7<<button_8<<button_9<<button_10;
    for (int i = 0; i < buttonAList.size(); i++)
    {
          buttonAList.at(i)->setMinimumSize(28,58);
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

    button2_1=new QPushButton("电源");
    button2_2=new QPushButton("1");
    button2_3=new QPushButton("2");
    button2_4=new QPushButton("3");
    button2_5=new QPushButton("4");
    button2_6=new QPushButton("电源");
    button2_7=new QPushButton("1");
    button2_8=new QPushButton("2");
    button2_9=new QPushButton("3");
    button2_10=new QPushButton("4");

    QList<QPushButton *> buttonAList2;
    buttonAList2<<button2_1<<button2_2<<button2_3<<button2_4<<button2_5<<button2_6<<button2_7<<button2_8<<button2_9<<button2_10;
    for (int i = 0; i < buttonAList2.size(); i++)
    {
          buttonAList2.at(i)->setMinimumSize(28,58);
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

    hLayout3=new QHBoxLayout;
    widgetC=new QWidget(this);
    hLayout3->setContentsMargins(0,1,0,0);
    hLayout3->setSpacing(1);

    button3_1=new QPushButton("电源");
    button3_2=new QPushButton("1");
    button3_3=new QPushButton("2");
    button3_4=new QPushButton("3");
    button3_5=new QPushButton("4");
    button3_6=new QPushButton("电源");
    button3_7=new QPushButton("1");
    button3_8=new QPushButton("2");
    button3_9=new QPushButton("3");
    button3_10=new QPushButton("4");
    QList<QPushButton *> buttonAList3;
    buttonAList3<<button3_1<<button3_2<<button3_3<<button3_4<<button3_5<<button3_6<<button3_7<<button3_8<<button3_9<<button3_10;
    for (int i = 0; i < buttonAList2.size(); i++)
    {
          buttonAList3.at(i)->setMinimumSize(28,58);
    }
    hLayout3->addWidget(button3_1);
    hLayout3->addWidget(button3_2);
    hLayout3->addWidget(button3_3);
    hLayout3->addWidget(button3_4);
    hLayout3->addWidget(button3_5);
    hLayout3->addWidget(button3_6);
    hLayout3->addWidget(button3_7);
    hLayout3->addWidget(button3_8);
    hLayout3->addWidget(button3_9);
    hLayout3->addWidget(button3_10);

    widgetC->setLayout(hLayout3);

    button_unknown3=new QPushButton(this);
    button_unknown3->setObjectName("button_unknown3");

    //button_relays=new QPushButton(this);

   // button_btm=new QPushButton(this);

   // button_conn=new QPushButton(this);

}

Powercabinet::~Powercabinet()
{

}

void Powercabinet::paintEvent(QPaintEvent *event)
{
    //resize(1600,1200);
    QPainter p(this);
    event = event;
    p.setPen(QPen(Qt::black, 1));
    p.setRenderHint(QPainter::Antialiasing);

    QTransform transform;
    transform.translate(transX,transY);
    transform.scale(scale,scale);
    p.setTransform(transform);

    drawButton(button_fan,100,100,300,20,"系统状态图");
    drawButton(button_rtm,100,120,300,60,"信号集中监测柜");
    drawButton(button_unknown1,100,180,300,20,"");
    widgetA->setGeometry(100*scale+transX,200*scale+transY,300*scale,60*scale);
    drawButton(button_unknown2,100,260,300,20,"");
    widgetAB->setGeometry(100*scale+transX,280*scale+transY,300*scale,20*scale);
    widgetB->setGeometry(100*scale+transX,300*scale+transY,300*scale,60*scale);
    drawButton(button_unknown3,100,360,300,20,"");
    //drawButton(button_relays,100,380,300,20,"继电器");
    //drawButton(button_btm,100,400,300,60,"BTM");
    //drawButton(button_conn,100,460,300,60,"连接器层");
    widgetC->setGeometry(100*scale+transX,400*scale+transY,300*scale,60*scale);
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
    //drawFrame(p,QPoint(100,460),true);

}

void Powercabinet::drawFrame(QPainter& p,QPoint point,bool isHigh)
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

void Powercabinet::drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name)
{
    button->setGeometry(startX*scale+transX,startY*scale+transY,w*scale,h*scale);
    button->setText(name);
}

void Powercabinet::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        qDebug()<<"mousePressEvent";
        lastPoint=event->pos();
        lastPoint.setX(lastPoint.x()-transX);
        lastPoint.setY(lastPoint.y()-transY);
    }

}

void Powercabinet::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint=event->pos();
        transX=endPoint.x()-lastPoint.x();
        transY=endPoint.y()-lastPoint.y();
        qDebug()<<"mouseMoveEvent transX:"<<transX<<" transY:"<<transY;
        update();
    }
}


void Powercabinet::wheelEvent(QWheelEvent *event)
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
    }
    else if(scale>5)
    {
        scale=5;
    }
    update();
}

void Powercabinet::resizeEvent(QResizeEvent *event)
{
    event =event ;
    scale=this->parentWidget()->width()/1024.0;
    transX=100*scale;
    transY=30*scale;

    if(scale<0.2)
    {
        scale=0.2;
    }
    else if(scale>5)
    {
        scale=5;
    }
    update();
}
