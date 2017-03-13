#include "testcidevice.h"
#include <QTest>
#include <QSignalSpy>
#include <QWidget>
#include <QPoint>

#define private public
#define protected public
#include "cidevice.h"
#include "mssdatadefine.h"
#include "ci_data.h"
#undef protected
#undef private


TestCiDevice::TestCiDevice(QObject *parent) : QObject(parent)
{

}

void TestCiDevice::initTestCase()
{
    ciDevice = new CiDevice;
    ciDevice->resize(1024,768);
    ciDevice->show();
    QTest::mouseMove(ciDevice,QPoint(0,0));
    QTest::qWait(2000);
}

void TestCiDevice::testInitial()
{
    QCOMPARE(ciDevice->scale,1.0);
    QCOMPARE(ciDevice->transX,100);
    QCOMPARE(ciDevice->transY,50);
    QCOMPARE(ciDevice->list.size(),0);
    QVERIFY(ciDevice->startPoint.x()==0);
    QVERIFY(ciDevice->startPoint.y()==0);
    QVERIFY(ciDevice->endPoint.x()==0);
    QVERIFY(ciDevice->endPoint.y()==0);
    QVERIFY(ciDevice->hashDeviceMap.size()!=0);
    QVERIFY(ciDevice->hashDeviceMap.contains(4));
}

void TestCiDevice::testStyleSheet()
{
    QString styleSheet = ciDevice->styleSheet();

    QVERIFY(styleSheet.compare("")!=0);

}

void TestCiDevice::testDeviceTip()
{
    QTest::mouseMove(ciDevice,QPoint(660,160));
    QSignalSpy buttonspy(ciDevice->buttonCI,&QPushButton::clicked);
    QTest::mouseClick(ciDevice->buttonCI,Qt::LeftButton,Qt::KeyboardModifiers(), QPoint(), 1000);
    QTest::qWait(2000);
    QVERIFY(buttonspy.count() == 1);

    QString tip=ciDevice->buttonCI->toolTip();
    QVERIFY(tip.compare("") != 0);

}

void TestCiDevice::testShowReport()
{
    QTest::mouseMove(ciDevice,QPoint(660,310));
    ciDevice->rightPressButton = ciDevice->buttonRelay;
    QMenu *menu = ciDevice->menu;

    QSignalSpy menuspy(menu,&QMenu::triggered);
    QSignalSpy ReceivedSpy(ciDevice, &CiDevice::showReport);
    QList<QAction *> actions=menu->actions();
    for(int i=0;i<actions.length();i++){
        if(actions.at(i)->text().compare("")!=0)
        {
            menu->popup(QCursor::pos());
            menu->setActiveAction(actions.at(i));

            QRect rect=menu->actionGeometry(actions.at(i));
            QPoint submenuPos(rect.topLeft() + QPoint(3, 3));
            QTest::mouseClick(menu,Qt::LeftButton,Qt::KeyboardModifiers(),submenuPos, 1000);
        }
    }
    QVERIFY(menuspy.count()==2);
    QVERIFY(ReceivedSpy.count()==2);

    qDebug()<<"ReceivedSpy:"<<ReceivedSpy;
    QList<QVariant> arguments = ReceivedSpy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    QVERIFY(arguments.at(1).type() == QVariant::String);
    QVERIFY(arguments.at(0).toInt() == 6);
    QVERIFY(arguments.at(1).toString() == "buttonjidianqi");

}

void TestCiDevice::testShowAlarm()
{

}

void TestCiDevice::cleanupTestCase()
{

}
//QTEST_MAIN(TestCiDevice)
