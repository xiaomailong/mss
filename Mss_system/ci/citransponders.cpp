#include "citransponders.h"
#include <QPainter>
#include<QColor>
#include<QBrush>
#include<QPen>
#include<QPoint>
#include <QMouseEvent>
#include <QDebug>

CiTransponders::CiTransponders(QWidget *parent) : QPushButton(parent)
{
    isWorking = true;
    hasAlarm = false;
    alarmLevel = 0;;
}

void CiTransponders::paintEvent(QPaintEvent *)
{
     float  buttonWidth = width();   //button width
     float  buttonHeight = height();   //button height
     QPointF points[3] = {
         QPointF(0,buttonHeight-1),
         QPointF(buttonWidth/2,0),
         QPointF(buttonWidth,buttonHeight-1),
     };
     QPainter  painter(this);
     QPen pen;
     pen.setColor(Qt::black);
     pen.setWidth(1);
     pen.setStyle(Qt::SolidLine);
     painter.setPen(pen);
     if(isWorking)
     {
         painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
     }else
     {
         painter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));
     }

     painter.drawPolygon(points,3);

     if(hasAlarm)
     {
         if(alarmLevel == 1)
         {
             painter.setBrush(Qt::gray);
         }else if(alarmLevel == 2)
         {
             painter.setBrush(Qt::yellow);
         }else if(alarmLevel == 3)
         {
             painter.setBrush(Qt::red);
         }
         painter.drawEllipse(buttonWidth/2, 0, buttonWidth/2, buttonWidth/2);
     }
}

void CiTransponders::onEventFromDevice(int state)
{
    switch (state)
    {
    case 0:
        isWorking = false;
        update();
        break;
    case 1:
        isWorking = true;
        update();
        break;
    default:
        break;
    }
}

void CiTransponders::onAlarmFromDevice(int alarmLevel)
{
    hasAlarm = true;
    this->alarmLevel = alarmLevel;
    update();
}
