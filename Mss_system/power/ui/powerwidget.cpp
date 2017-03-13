#include "powerwidget.h"
#include <qevent>
#include <qcursor>
#include<QHelpEvent>
#include <QToolTip>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include<QFont>
#include<QMenu>
#include"dayreport.h"

Powerwidget::Powerwidget(QWidget *parent):QWidget(parent)
{

     resize(1024,900);
     initUi();
}

Powerwidget::~Powerwidget()
{

}



void Powerwidget::initUi()
{

    buttonPower = new QPushButton("电源屏",this);
    buttonPower->setToolTip("电源屏状态");
    buttonPower->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(buttonPower,&QWidget::customContextMenuRequested,this,this->show_contextmenu);

    buttonLock = new QPushButton("计算机联锁",this);

    buttonZC = new QPushButton("ZC",this);

    buttonCI = new QPushButton("CI",this);

    buttonATS = new QPushButton("ATS",this);

    USPLabel = new QLabel("USP",this);
   // USPLabel->setGeometry(QRect(350,100,50,500));

    scale =1;
    //外电网label
    PowerLabel = new QLabel("外电网",this);
    transX =0;
    transY =0;
  // PowerLabel->setBackgroundRole(QPalette::Shadow);
   // PowerLabel->setGeometry(QRect(100,100,280,500));
   // PowerLabel->setText("外电网");



}

void Powerwidget::drawLabel(QLabel *label,QString str,int x1,int y1,int x2,int y2){
     //label->setBackgroundRole(QPalette::Shadow);
     label->setGeometry(QRect(x1*scale+transX,y1*scale+transY,x2*scale,y2*scale));
     label->setText(str);
     //qDebug()<<"zwz str ="<<str;

}


void Powerwidget::drawRect(QPainter *painter,QPen *pen,QBrush *brush,const QColor &color,int penwidth,Qt::PenStyle style,int x,int y,int w,int h){
    pen->setColor(color);
    pen->setWidth(penwidth);
    pen->setStyle(style);
    painter->setPen(*pen);
    if(brush !=NULL)
        painter->setBrush(*brush);
    painter->drawRect(x*scale+transX,y*scale+transY,w*scale,h*scale);
}

void Powerwidget::drawHorizionLine(QPainter *painter,QPen *pen,const QColor &color,int penwidth,int x1,int y1,int x2,int y2  ){
    pen->setColor(color);
    pen->setWidth(penwidth);
    painter->setPen(*pen);
    QLineF lineBlueHorizion(x1*scale+transX, y1*scale+transY,x2*scale+transX,y2*scale+transY);
   // qDebug()<<"zwz x1*scale ="<<x1*scale ;
  //  qDebug()<<"zwz x2*scale ="<<x2*scale ;
    painter->drawLine(lineBlueHorizion);

}

void Powerwidget::drawVerticalLine(QPainter *painter,QPen *pen,const QColor &color,int penwidth,int x1,int y1,int x2,int y2  ){
    pen->setColor(color);
    pen->setWidth(penwidth);
    painter->setPen(*pen);
    QLineF lineBlueHorizion(x1*scale+transX, y1*scale+transY,x2*scale+transX,y2*scale+transY);
    painter->drawLine(lineBlueHorizion);

}


void Powerwidget::drawButton(QPushButton *button,QPainter *painter,QString style,int x,int y,int w,int h){
    button->resize(w*scale,h*scale);
    button->move(x*scale+transX,y*scale+transY);
    //qDebug()<<"zwz drawButton x*scale ="<<x*scale ;
   // qDebug()<<"zwz drawButton w*scale ="<<w*scale ;
    button->setStyleSheet(style);
    QFont font = painter->font();
    font.setPointSize(12*scale);
    button->setFont(font);
}

void Powerwidget::paintEvent(QPaintEvent *event){

    QPen pen;
    QPainter myPainter(this);
    QBrush brush;
    QString button_style="QPushButton{background-color:rgb(146, 208, 80);\
    color: black;border-radius: 10px;border: 2px groove gray;\
    border-style: outset;}"
    "QPushButton:hover{background-color:white;color: black;}"
    "QPushButton:pressed{background-color:rgb(85, 170, 255);\
    border-style: inset; }";
   QTransform transform;

   QFont font = myPainter.font();
   font.setPointSize(8*scale);
   myPainter.setFont(font);

   //transform.scale(0.8,0.8);
  // myPainter.setTransform(transform);
     //虚线框power
    drawRect(&myPainter,&pen,NULL,Qt::black,1,Qt::DashLine,10,100,280,500);
    //usp

    brush=QBrush(Qt::yellow,Qt::SolidPattern);
    drawRect(&myPainter,&pen,&brush,Qt::black,1,Qt::DashLine,340,100,50,500);
    //USP--电源屏

    drawHorizionLine(&myPainter,&pen,Qt::blue,5,395, 160,500,160);
    drawHorizionLine(&myPainter,&pen,Qt::blue,5,395, 180,500,180);
    drawHorizionLine(&myPainter,&pen,Qt::blue,5,395, 200,500,200);
    //电源屏--计算机联锁

    drawHorizionLine(&myPainter,&pen,Qt::blue,5,505, 180,800,180);
    //计算机联锁--ATS

    drawHorizionLine(&myPainter,&pen,Qt::blue,5,900, 180,1300,180);
    drawVerticalLine(&myPainter,&pen,Qt::blue,5,1300,180,1300,400);
    //ATS--CI

    drawHorizionLine(&myPainter,&pen,Qt::blue,5,1055, 500,1250,500);
    //CI--ZC

    drawHorizionLine(&myPainter,&pen,Qt::blue,5,750, 500,1050,500);
    //联锁--ZC

    drawHorizionLine(&myPainter,&pen,Qt::blue,5,700, 200,800,200);
    drawVerticalLine(&myPainter,&pen,Qt::blue,5,700, 200,700,400);
    //外电网---usp
    drawHorizionLine(&myPainter,&pen,Qt::blue,5,290, 160,340,160);
    drawHorizionLine(&myPainter,&pen,Qt::blue,5,290, 220,340,220);
    drawHorizionLine(&myPainter,&pen,Qt::blue,5,290, 280,340,280);
    drawHorizionLine(&myPainter,&pen,Qt::blue,5,290, 340,340,340);

    drawButton(buttonPower,&myPainter,button_style,500,100,100,200);
    drawButton(buttonLock,&myPainter,button_style,800,100,100,200);
    drawButton(buttonZC,&myPainter,button_style,650,400,100,200);
    drawButton(buttonCI,&myPainter,button_style,950,400,100,200);
    drawButton(buttonATS,&myPainter,button_style,1250,400,100,200);

    drawLabel(PowerLabel,"外部电网",110,270,150,100);
    drawLabel(USPLabel ,"USP",355,270,150,100);
}

void Powerwidget:: wheelEvent(QWheelEvent *event){
    if(event->delta()>0){
        scale+=0.05;
    }else{
        scale-=0.05;
    }
    if(scale<0.2){
       scale=0.2;
    }else if(scale>5){
        scale=5;
    }
    update();
}


bool Powerwidget::event(QEvent *event)
 {
     if (event->type() == QEvent::ToolTip) {
         QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
            if(QRect(width()/2, height()/2, width()/2, height()/2).contains(helpEvent->pos()))
          {
             //QToolTip::showText(helpEvent->globalPos(), "你好");
         } else {
             QToolTip::hideText();
             event->ignore();
         }

         return true;
     }
     return QWidget::event(event);
 }



void Powerwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        qDebug()<<"mousePressEvent";
        lastPoint=event->pos();
        lastPoint.setX(lastPoint.x()-transX);
        lastPoint.setY(lastPoint.y()-transY);
    }

}


void Powerwidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        endPoint=event->pos();
        transX=endPoint.x()-lastPoint.x();
        transY=endPoint.y()-lastPoint.y();
        qDebug()<<"mouseMoveEvent transX:"<<transX<<" transY:"<<transY;
        update();
    }
}


void Powerwidget::resizeEvent(QResizeEvent *event)
{
    //scale=this->parentWidget()->width()/1024.0;
    scale =this->width()/1480.0;
    transX=100*scale;
    transY=30*scale;

    if(scale<0.2){
        scale=0.2;
    }else if(scale>5){
       scale=5;
    }
    update();
}


void Powerwidget::show_contextmenu(const QPoint& pos)
{
    QMenu *popMenu =new QMenu();
   /* popMenu->addMenu("日曲线");
    popMenu->addMenu("月曲线");
    popMenu->addMenu("年曲线");
    popMenu->addMenu("实时曲线");
    popMenu->addMenu("日报表");
    */
    QAction *showreport =new QAction("日报表",this);
    connect(showreport, &QAction::triggered, this, this->QueryDayReport);

    popMenu->addAction(showreport);
    popMenu->exec(QCursor::pos());
}

void Powerwidget::QueryDayReport(){
    QString tabname = "dayreport";
    emit showDayReport(day_report,"dayreport");

}


