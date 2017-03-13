#include "cisignalmachine.h"
#include <QPainter>
#include <QPen>
#include <QDebug>

CiSignalMachine::CiSignalMachine(QWidget *parent) : QPushButton(parent),isRed(false),hasAlarm(false),alarmLevel(0)
{

}

void CiSignalMachine::paintEvent(QPaintEvent *)
{
    float  buttonWidth = width();   //button width
    float  buttonHeight = height();   //button height
    float radius = (buttonWidth-1)/2;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 1));
    if(isRed)
    {
        painter.setBrush(Qt::red);
    }else
    {
        painter.setBrush(Qt::green);
    }
    painter.drawEllipse(0, buttonHeight/4, radius, radius);
    painter.drawEllipse(0,buttonHeight/2, radius, radius);
    painter.drawEllipse(0,buttonHeight*3/4, radius, radius);
    painter.drawLine(-radius,buttonHeight-1,radius,buttonHeight-1);
    if(hasAlarm)
    {
        if(alarmLevel == 1)
        {
            painter.setBrush(Qt::gray);
        }else if(alarmLevel == 2)
        {
            painter.setBrush(Qt::yellow);
        }else if(alarmLevel == 3){
            painter.setBrush(Qt::red);
        }
        painter.drawEllipse(radius, 0, radius, radius);
    }
}

void CiSignalMachine::onEventFromDevice(int state)
{
    switch (state)
    {
    case 0:
        isRed = true;
        update();
        break;
    case 1:
        isRed = false;
        update();
    default:
        break;
    }
}

void CiSignalMachine::onAlarmFromDevice(int alarmLevel)
{
    hasAlarm = true;
    this->alarmLevel = alarmLevel;
    update();
}
