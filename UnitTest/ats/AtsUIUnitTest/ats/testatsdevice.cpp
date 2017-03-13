#include <QTest>

#include "testatsdevice.h"
#include <QMenu>
#include <QSignalSpy>

#define private public
#define protected public
#include "atsdevice.h"
#undef protected
#undef private

TestAtsDevice::TestAtsDevice(QObject *parent) : QObject(parent)
{
}

void TestAtsDevice::initTestCase()
{
    atsDevice = new AtsDevice;
    atsDevice->resize(1280,768);
    atsDevice->show();
    QTest::mouseMove(atsDevice,QPoint(0,0));
}

void TestAtsDevice::testInitView(){
    QVERIFY(atsDevice->b==1.0);
    QCOMPARE(atsDevice->transX,100);
    QCOMPARE(atsDevice->transY,100);
    QCOMPARE(atsDevice->breakDownList.size(),0);
    QVERIFY(atsDevice->lastPoint.x()==0);
    QVERIFY(atsDevice->lastPoint.y()==0);
    QVERIFY(atsDevice->endPoint.x()==0);
    QVERIFY(atsDevice->endPoint.y()==0);
}

void TestAtsDevice::testStyleSheet()
{
    QString styleSheet=atsDevice->styleSheet();
    QVERIFY(styleSheet.compare("")!=0);
}

void TestAtsDevice::testDeviceXmlInfo()
{
    QVERIFY(atsDevice->hashDeviceMap.size()!=0);
    QVERIFY(atsDevice->hashInfoMap.size()!=0);

    QVERIFY(atsDevice->hashDeviceMap.contains(atsDevice->interchanger1));
    QVERIFY(atsDevice->hashInfoMap.contains(atsDevice->interchanger1));
}

void TestAtsDevice::testDeviceTip()
{
    QTest::mouseMove(atsDevice,QPoint(85,335));
    QSignalSpy buttonSpy(atsDevice->interChanger1, &QPushButton::clicked);
    QTest::mouseClick(atsDevice->interChanger1,Qt::LeftButton,Qt::KeyboardModifiers(), QPoint(), 1000);
    QTest::qWait(3000);
    QVERIFY(buttonSpy.count() == 1);

    QString tip=atsDevice->interChanger1->toolTip();
    QVERIFY(tip.compare("")!=0);
}

void TestAtsDevice::testshowReport()
{
    QTest::mouseMove(atsDevice,QPoint(480,115));
    atsDevice->pressButton = atsDevice->dispatcher;
    QMenu *menu = atsDevice->menu;
    QSignalSpy menuSpy(menu, &QMenu::triggered);
    QSignalSpy ReceivedSpy(atsDevice, &AtsDevice::showReport);

    QList<QAction *> actions=menu->actions();
    for(int i=0;i<actions.length();i++)
    {
        if(actions.at(i)->text().compare("")!=0)
        {
            menu->popup(atsDevice->dispatcher->pos());
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
    QVERIFY(arguments.at(1).toString() == "dispatcher");

}

