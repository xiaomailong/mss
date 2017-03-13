#include "zcgplot.h"
#include "zcreadinfofromxml.h"
#include <QDebug>
#include <QFile>
#include <QPushButton>
#include <QPainter>
#include <QTransform>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QDockWidget>
#include <QListWidget>
#include <QMessageBox>

ZCGplot::ZCGplot(QWidget *parent) : QWidget(parent)
{
    QFile styleSheet("://qss/zc.qss");
    if (!styleSheet.open(QFile::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    this->setStyleSheet(styleSheet.readAll());
    styleSheet.close();

    zcGplotMagnification=1;
    transX=100;
    transY=100;

    lastPoint.setX(0);
    lastPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);
    //read xml and init ats ci zc vobc button 
    QString strTip =ZCReadInfofromXml::readInfoFromXML("://xml/zc/zcInformation.xml","ZCI","1");
    buttonOfZc=new QPushButton(this);
    buttonOfZc->setToolTip(strTip);
    buttonOfZc->setObjectName("buttonOfZc");
    buttonOfZc->installEventFilter(this);

    buttonOfAts=new QPushButton(this);
    buttonOfAts->setObjectName("buttonOfAts");
    //buttonOfAts->setToolTip(strTip);
    buttonOfAts->installEventFilter(this);

    buttonOfCi=new QPushButton(this);
    buttonOfCi->setObjectName("buttonOfCi");
    //buttonOfCi->setToolTip(strTip);
    buttonOfCi->installEventFilter(this);

    buttonOfvobc=new QPushButton(this);
    buttonOfvobc->setObjectName("buttonOfvobc");
    //buttonOfvobc->setToolTip(strTip);
    buttonOfvobc->installEventFilter(this);

    connect(buttonOfvobc,&QPushButton::clicked,this,&ZCGplot::zcClickshowVobc);
    connect(buttonOfAts,&QPushButton::clicked,this,&ZCGplot::zcClickshowAts);
    connect(buttonOfCi,&QPushButton::clicked,this,&ZCGplot::zcClickshowCi);
    //init the menu
    zcClickRightMenu = new QMenu(this);
    zcClickRightMenu->setStyleSheet("font: 10pt \"微软雅黑\";");
    zcClickRightMenu->addAction("查询日报警报表", this, &ZCGplot::queryDayAlarmReport);
    zcClickRightMenu->addAction("查询月报警报表", this, &ZCGplot::queryMonthAlarmReport);
    zcClickRightMenu->addSeparator();
    zcClickRightMenu->addAction("查询设备信息", this, &ZCGplot::queryDutInformation);
    zcClickRightMenu->addSeparator();
}
//send message when click vobc button to show vobc
void ZCGplot::zcClickshowVobc(){
    emit zcSendEventToMss("vobc");
}
//send message when click ats button to show ats
void ZCGplot::zcClickshowAts(){
    emit zcSendEventToMss("ats");
}
//send message when click ci button to show ci
void ZCGplot::zcClickshowCi(){
    emit zcSendEventToMss("ci");
}
//to show day alarm report
void ZCGplot::queryDayAlarmReport()
{
    QString deviceName = rightbutton->objectName();
    emit showReport(1,deviceName);
}
//to show month alarm report
void ZCGplot::queryMonthAlarmReport()
{
    QString deviceName = rightbutton->objectName();
    emit showReport(2,deviceName);
}
//to show dut information of zc
void ZCGplot::queryDutInformation()
{
    QString deviceName = rightbutton->objectName();
    qDebug()<<"queryDutInformation";
    emit showReport(3,deviceName);
}

void ZCGplot::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(QPen(Qt::black, 2));
    p.setRenderHint(QPainter::Antialiasing);
    QTransform transform;
    transform.translate(transX,transY);
    p.setTransform(transform);
    //draw the button (the button,the location X,Y,width,height,name)
    drawButton(buttonOfCi,60,180,120,60,"CI");
    drawButton(buttonOfZc,360,180,120,60,"ZC");
    drawButton(buttonOfAts,360,60,120,60,"ATS");
    drawButton(buttonOfvobc,360,300,120,60,"VOBC");
    //draw the line (QPainter,location X,Y,the lenth)
    drawCustomLine(p,QPoint(180,210),0,180);
    drawCustomLine(p,QPoint(420,120),90,60);
    drawCustomLine(p,QPoint(420,240),90,60);
}
//mousePressEvent
void ZCGplot::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        lastPoint=event->pos();
        lastPoint.setX(lastPoint.x()-transX);
        lastPoint.setY(lastPoint.y()-transY);
    }
}
//resizeEvent
void ZCGplot::resizeEvent(QResizeEvent *)
{
    if(this->parentWidget()!=NULL)
        {
        zcGplotMagnification=this->parentWidget()->width()/1024.0;
        transX=100*zcGplotMagnification;
        transY=50*zcGplotMagnification;

        if(zcGplotMagnification<0.2)
        {
            zcGplotMagnification=0.2;
        }
        else if(zcGplotMagnification>5)
        {
            zcGplotMagnification=5;
        }
        update();
    }
}
//mouseMoveEvent
void ZCGplot::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint=event->pos();
        transX=endPoint.x()-lastPoint.x();
        transY=endPoint.y()-lastPoint.y();
        //qDebug()<<"mouseMoveEvent transX:"<<transX<<" transY:"<<transY;
        update();
    }
}
//mouseReleaseEvent
void ZCGplot::mouseReleaseEvent(QMouseEvent *)
{
//    if(event->button()==Qt::LeftButton){
//        endPoint=event->pos();
//        transX=endPoint.x()-lastPoint.x();
//        transY=endPoint.y()-lastPoint.y();
//        //qDebug()<<"mouseReleaseEvent transX:"<<transX<<" transY:"<<transY;
//        update();
//    }
}
//event Filter
bool ZCGplot::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (MouseEvent->buttons() == Qt::RightButton)
        {
            rightbutton = obj;
            QString deviceName = rightbutton->objectName();
            if (!deviceName.compare("buttonOfZc"))
            {
                zcClickRightMenu->exec(QCursor::pos());
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
//wheelEvent
void ZCGplot::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0){
        zcGplotMagnification+=0.05;
    }else{
        zcGplotMagnification-=0.05;
    }
    if(zcGplotMagnification<0.2){
        zcGplotMagnification=0.2;
    }else if(zcGplotMagnification>5){
        zcGplotMagnification=5;
    }
    update();
}
//drawButton
void ZCGplot::drawButton(QPushButton *button,int startX,int startY,int w,int h,QString name)
{
    button->setGeometry(startX*zcGplotMagnification+transX,startY*zcGplotMagnification+transY,w*zcGplotMagnification,h*zcGplotMagnification);
    button->setText(name);
    button->installEventFilter(this);
}

//drawCustomLine
void ZCGplot::drawCustomLine(QPainter& p,QPoint point, double angle, double len)
{
    QTransform originTransform= p.transform();

    //init
    p.resetTransform(); // reset the paint
    p.translate(QPoint(point.x()*zcGplotMagnification+transX,point.y()*zcGplotMagnification+transY));

    p.setPen(QPen(Qt::black, 1));
    // draw the line
    QLine line(QPoint(0,0), QPoint(len*zcGplotMagnification,0));
    p.rotate(angle);
    p.drawLine(line);

//    int off_x = 6*zcGplotMagnification;
//    QPainterPath path;
//    path.moveTo(len*zcGplotMagnification-off_x, -5*zcGplotMagnification);
//    path.lineTo(len*zcGplotMagnification,0);
//    path.lineTo(len*zcGplotMagnification-off_x,5*zcGplotMagnification);
//    p.drawPath(path);

//    if(both)
//    {
//        path.moveTo(off_x, -5*zcGplotMagnification);
//        path.lineTo(0,0);
//        path.lineTo(off_x,5*zcGplotMagnification);
//        p.drawPath(path);
//    }

//    if(angle!=0)
//    {
//            p.rotate(-angle);
//    }
//    p.setPen(color);

//    QFont font = p.font();
//    font.setPointSize(8*zcGplotMagnification);


//    p.setFont(font);

//    if(angle==270)
//    {
//        p.drawText(QPoint(5*zcGplotMagnification,-10*zcGplotMagnification), name);
//    }
//    else if(angle==180)
//    {
//        p.drawText(QPoint(-20*zcGplotMagnification,-10*zcGplotMagnification), name);
//    }
//    else if(angle==90)
//    {
//        p.drawText(QPoint(5*zcGplotMagnification,10*zcGplotMagnification), name);
//    }
//    else
//    {
//        p.drawText(QPoint(20*zcGplotMagnification,-10*zcGplotMagnification), name);
//    }

    p.resetTransform(); //painte reset
    p.setTransform(originTransform);
}
