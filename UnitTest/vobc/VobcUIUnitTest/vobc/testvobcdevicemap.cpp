#include "testvobcdevicemap.h"
#include <QDebug>
#include <QTest>
#include <QMenu>
#include <QSignalSpy>
#include <QTestEventList>
#include <QCursor>
#include <QList>
#include "vobc_data.h"

#define private public
#define protected public
#include "vobcdevice.h"
#undef protected
#undef private

TestVobcDeviceMap::TestVobcDeviceMap()
{

}

void TestVobcDeviceMap::initTestCase()
{
    device =new VobcDevice;
    device->resize(1024,768);
    device->show();
    QTest::mouseMove(device,QPoint(0,0));
}

void TestVobcDeviceMap::testInitial()
{
    QTest::qWait(2000);
    QVERIFY(device->b==1.0);
    QCOMPARE(device->transX,100);
    QCOMPARE(device->transY,50);
    QCOMPARE(device->breakDownList.size(),0);
    QVERIFY(device->lastPoint.x()==0);
    QVERIFY(device->lastPoint.y()==0);
    QVERIFY(device->endPoint.x()==0);
    QVERIFY(device->endPoint.y()==0);

}

void TestVobcDeviceMap::testStyleSheet()
{
    QString styleSheet=device->styleSheet();
    QVERIFY(styleSheet.compare("")!=0);
}

void TestVobcDeviceMap::testDeviceXmlInfo()
{
    QVERIFY(device->hashDeviceMap.size()!=0);
    QVERIFY(device->hashInfoMap.size()!=0);

    QVERIFY(device->hashDeviceMap.contains(device->head));
    QVERIFY(device->hashInfoMap.contains(device->head));
}

void TestVobcDeviceMap::testDeviceTip()
{
    QList<QPushButton *> deviceList;
    deviceList.append(device->buttonHead);
    deviceList.append(device->buttonTail);
    deviceList.append(device->buttonBtm1);
    deviceList.append(device->buttonBtm2);
    deviceList.append(device->buttonAp1);
    deviceList.append(device->buttonAp2);
    deviceList.append(device->buttonSw1);
    deviceList.append(device->buttonSw2);
    deviceList.append(device->buttonDmi1);
    deviceList.append(device->buttonDmi2);
    deviceList.append(device->buttonIO);
    deviceList.append(device->buttonNet);
    deviceList.append(device->buttonPower);
    deviceList.append(device->buttonPulse1);
    deviceList.append(device->buttonPulse2);
    deviceList.append(device->buttonPulse3);
    deviceList.append(device->buttonPulse4);


    for(int i=0;i<deviceList.size();i++)
    {
        QTestEventList events;
        QSignalSpy spy(deviceList.at(i), &QPushButton::clicked);
        events.addMouseMove(deviceList.at(i)->mapFromParent(deviceList.at(i)->pos()),500);
        events.addMouseClick(Qt::LeftButton,Qt::KeyboardModifiers(),QPoint(), 1000);

        events.simulate(deviceList.at(i));
        QVERIFY(spy.count()==1);
    }
    for(int i=0;i<deviceList.size();i++)
    {
        QString tip=deviceList.at(i)->toolTip();
        QVERIFY(tip.compare("")!=0);
    }
}

void TestVobcDeviceMap::testshowReport()
{
    QTest::mouseMove(device->buttonTail);
    device->rightPressButton=device->buttonTail;
    QMenu *menu=device->menu;

    QSignalSpy menuSpy(menu, &QMenu::triggered);
    QSignalSpy ReceivedSpy(device, &VobcDevice::showReport);

    QList<QAction *> actions=menu->actions();
    for(int i=0;i<actions.length();i++)
    {
        if(actions.at(i)->text().compare("")!=0)
        {
            menu->popup(QCursor::pos());
            menu->setActiveAction(actions.at(i));

            QRect rect=menu->actionGeometry(actions.at(i));
            QPoint submenuPos(rect.topLeft() + QPoint(3, 3));
            QTest::mouseClick(menu,Qt::LeftButton,Qt::KeyboardModifiers(),submenuPos, 1000);
        }
    }
    QVERIFY(menuSpy.count()==2);
    QVERIFY(ReceivedSpy.count()==2);

    qDebug()<<"ReceivedSpy:"<<ReceivedSpy;
    QList<QVariant> arguments = ReceivedSpy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    QVERIFY(arguments.at(1).type() == QVariant::String);
    QVERIFY(arguments.at(0).toInt() == 3);
    QVERIFY(arguments.at(1).toString() == "buttonTail");

}

void TestVobcDeviceMap::testshowAlarm()
{
    connect(this,&TestVobcDeviceMap::showAlarm,device,&VobcDevice::onAlarm);
    vobc_subsys_msg_t msg;

    msg.msg_type =(qrand()%4);
    msg.sys_id = (qrand()%4);
    msg.dev_type = 0;
    msg.dev_id = (qrand()%4);
    msg.dev_local = (qrand()%4);
    msg.alarm_type = (qrand()%4);
    msg.alarm_subtype = (qrand()%3);
    msg.alarm_level= (qrand()%3);
    msg.alarm_code= (qrand()%3);
    emit showAlarm(msg);
    QTest::qWait(2000);
    device->update();
    QTest::qWait(2000);

    QVERIFY(device->breakDownList.contains(0));
}

void TestVobcDeviceMap::cleanupTestCase()
{
    device->close();
    delete device;
}
