#include "testzcgplot.h"

#include <QDebug>
#include <QTest>
#include <QMenu>
#include <QSignalSpy>

#define private public
#define protected public
#include "zcgplot.h"
#undef protected
#undef private

TestZcgplot::TestZcgplot()
{

}

void TestZcgplot::zcWindowinit(){
    device = new ZCGplot();
    device->resize(800,600);
    device->show();
    QTest::mouseMove(device,QPoint(0,0));
}
void TestZcgplot::testInitial()
{
    QTest::qWait(2000);
    QVERIFY(device->zcGplotMagnification==1.0);
    QCOMPARE(device->transX,100);
    QCOMPARE(device->transY,100);
    QVERIFY(device->lastPoint.x()==0);
    QVERIFY(device->lastPoint.y()==0);
    QVERIFY(device->endPoint.x()==0);
    QVERIFY(device->endPoint.y()==0);

}
void TestZcgplot::testStyleSheet()
{
    QString styleSheet=device->styleSheet();
    QVERIFY(styleSheet.compare("")!=0);
}
void TestZcgplot::testDeviceTip()
{
    QTest::mouseMove(device,QPoint(450,170));
    QSignalSpy buttonSpy(device->buttonOfZc, &QPushButton::clicked);
    QTest::mouseClick(device->buttonOfZc,Qt::LeftButton,Qt::KeyboardModifiers(), QPoint(), 1000);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);
    QString tip=device->buttonOfZc->toolTip();
    QVERIFY(tip.compare("")!=0);
}


void TestZcgplot::testshowReport()
{
    QTest::mouseMove(device,QPoint(450,170));
    device->rightbutton=device->buttonOfZc;
    QMenu *menu=device->zcClickRightMenu;
    QSignalSpy menuSpy(menu, &QMenu::triggered);
    QSignalSpy ReceivedSpy(device, &ZCGplot::showReport);

    QList<QAction *> actions=menu->actions();
    for(int i=0;i<actions.length();i++)
    {
        if(actions.at(i)->text().compare("")!=0)
        {
            menu->popup(device->buttonOfZc->pos());
            menu->setActiveAction(actions.at(i));
            QRect rect=menu->actionGeometry(actions.at(i));
            QPoint submenuPos(rect.topLeft() + QPoint(3, 3));
            QTest::mouseClick(menu,Qt::LeftButton,Qt::KeyboardModifiers(),submenuPos, 1000);
        }
    }
    QVERIFY(menuSpy.count()==3);
    QVERIFY(ReceivedSpy.count()==3);

    qDebug()<<"ReceivedSpy:"<<ReceivedSpy;
    QList<QVariant> arguments = ReceivedSpy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    QVERIFY(arguments.at(1).type() == QVariant::String);
    QVERIFY(arguments.at(0).toInt() == 1);
    QVERIFY(arguments.at(1).toString() == "buttonOfZc");

}
//void TestZcgplot::testshowAlarm()
//{
//    connect(this,&TestZcgplot::showAlarm,device,&ZCGplot::onAlarm);

//    emit showAlarm("zc alarm msg");
//    QTest::qWait(2000);
//    device->update();
//    QTest::qWait(2000);
//}

void TestZcgplot::cleanUpTestCase()
{
    device->close();
    delete device;
}
