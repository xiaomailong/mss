#include "test_powerdevicewidget.h"
#include <QTest>
#include <QString>
#include <QMenu>
#include <QSignalSpy>
#undef protected
#undef private
Test_powerdevicewidget::Test_powerdevicewidget(QObject *parent) : QObject(parent)
{

}


void Test_powerdevicewidget::initTestCase()
{
    device =new PowerDeviceWidget;
    device->resize(1024,900);
    device->show();
    QTest::mouseMove(device,QPoint(0,0));
}

void Test_powerdevicewidget::testDeviceTip()
{
    QTest::mouseMove(device,QPoint(500,100));
    QSignalSpy buttonSpy(device->buttonPower, &QPushButton::clicked);
    QTest::mouseClick(device->buttonPower,Qt::LeftButton,Qt::KeyboardModifiers(), QPoint(), 1000);
    QTest::qWait(2000);
    QVERIFY(buttonSpy.count() == 1);

    QString tip=device->buttonPower->toolTip();
    QVERIFY(tip.compare("")!=0);
}



void Test_powerdevicewidget::show_contextmenu(){
    QTest::mouseMove(device,QPoint(500,100));

    device->buttonPower->setContextMenuPolicy(Qt::CustomContextMenu);
    device->show_contextmenu(QPoint(500,100));
    QTest::qWait(500);
    QMenu *menu=device->popMenu ;



   // QVERIFY(menuSpy1.count()==6);
//
    QSignalSpy ReceivedSpy1(device, &PowerDeviceWidget::showDayCurve);
    QSignalSpy ReceivedSpy2(device, &PowerDeviceWidget::showDayReport);
   QSignalSpy ReceivedSpy3(device, &PowerDeviceWidget::showMonthCurve);
   QSignalSpy ReceivedSpy4(device, &PowerDeviceWidget::showYearCurve);
   QSignalSpy ReceivedSpy5(device, &PowerDeviceWidget::showRealTimeCurve);
    QSignalSpy ReceivedSpy6(device, &PowerDeviceWidget::showPowerAlarm);
    QList<QAction *> actions=menu->actions();
    for(int i=0;i<actions.length();i++){
        if(actions.at(i)->text().compare("")!=0){
            menu->popup(device->buttonPower->pos());
           menu->setActiveAction(actions.at(i));

            QRect rect=menu->actionGeometry(actions.at(i));
            QPoint submenuPos(rect.topLeft() + QPoint(3, 3));
            QTest::mouseClick(menu,Qt::LeftButton,Qt::KeyboardModifiers(),submenuPos, 1000);
        }
    }
    QVERIFY(actions.length()==6);
    qDebug()<<"actions.length():"<<actions.length();
    QVERIFY(ReceivedSpy1.count()==1);
    QVERIFY(ReceivedSpy2.count()==1);
    QVERIFY(ReceivedSpy3.count()==1);
    QVERIFY(ReceivedSpy4.count()==1);
    QVERIFY(ReceivedSpy5.count()==1);
    QVERIFY(ReceivedSpy6.count()==1);
    qDebug()<<"ReceivedSpy:"<<ReceivedSpy1;
    QList<QVariant> arguments = ReceivedSpy1.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    QVERIFY(arguments.at(1).type() == QVariant::String);
   // QVERIFY(arguments.at(0).toInt() == 2);
   // QVERIFY(arguments.at(1).toString() == "button_tail");

}


