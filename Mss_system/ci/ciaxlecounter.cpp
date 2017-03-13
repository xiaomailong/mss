#include "ciaxlecounter.h"
#include <QPainter>
#include <QPen>

CiAxleCounter::CiAxleCounter(QWidget *parent) : QPushButton(parent)
{

}

void CiAxleCounter::paintEvent(QPaintEvent *)
{
    float  buttonWidth = width();   //button width
    float  buttonHeight = height();   //button height

    QPainter  painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::black);

    painter.drawEllipse(buttonWidth/6, buttonHeight/3, buttonWidth/4, buttonHeight/3);
    painter.drawEllipse(buttonWidth*2/3-2, buttonHeight/3, buttonWidth/4,buttonHeight/3);
    painter.drawLine(0,buttonHeight/2+0.8,buttonWidth,buttonHeight/2+0.8);
}
