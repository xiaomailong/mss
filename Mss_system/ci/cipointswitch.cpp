#include "cipointswitch.h"
#include <QPainter>
#include <QPen>
#include <QDebug>

CiPointSwitch::CiPointSwitch(QWidget *parent) : QPushButton(parent)
{
    isRotate = false;
    hasAlarm = false;
    alarmLevel = 0;
}

void CiPointSwitch::paintEvent(QPaintEvent *)
{
    float  buttonWidth = width();   //button width
    float  buttonHeight = height();   //button height
    QPainter  painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 3));
    if(isRotate)
    {
        painter.drawLine(0,0,buttonWidth/2,buttonHeight/2);
    }else
    {
        painter.drawLine(buttonWidth/2,buttonHeight/2,buttonWidth,0);
    }
    painter.drawLine(0,buttonHeight/2,buttonWidth,buttonHeight/2);

    if(hasAlarm)
    {
        painter.setPen(QPen(Qt::black, 1));
        if(alarmLevel == 1)
        {
            painter.setBrush(Qt::gray);
        }else if(alarmLevel ==2)
        {
            painter.setBrush(Qt::yellow);
        }else if(alarmLevel == 3)
        {
            painter.setBrush(Qt::red);
        }
        painter.drawEllipse(buttonWidth*3/4, buttonHeight/4, buttonWidth/4, buttonWidth/4);
    }
}

void CiPointSwitch::onEventFromDevice(int state)
{

    switch (state)
    {
    case 0:
        isRotate = false;
        update();
        break;
    case 1:
        isRotate = true;
        update();
        break;
    default:
        break;
    }
}

void CiPointSwitch::onAlarmFromDevice(int alarmLevel)
{
    hasAlarm = true;
    this->alarmLevel = alarmLevel;
    update();
}
