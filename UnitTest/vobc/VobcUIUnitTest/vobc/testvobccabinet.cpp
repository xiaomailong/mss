#include "testvobccabinet.h"

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "vobccabinet.h"
#undef protected
#undef private

TestVobcCabinet::TestVobcCabinet()
{

}

void TestVobcCabinet::initTestCase()
{
    vobcCabinet=new VobcCabinet;
    vobcCabinet->resize(1024,768);
    vobcCabinet->show();
    QTest::mouseMove(vobcCabinet,QPoint(0,0));
}

void TestVobcCabinet::testInitial()
{
     QTest::qWait(2000);
     QVERIFY(vobcCabinet->b==1.0);
     QCOMPARE(vobcCabinet->transX,100);
     QCOMPARE(vobcCabinet->transY,30);
     QVERIFY(vobcCabinet->lastPoint.x()==0);
     QVERIFY(vobcCabinet->lastPoint.y()==0);
     QVERIFY(vobcCabinet->endPoint.x()==0);
     QVERIFY(vobcCabinet->endPoint.y()==0);

}

void TestVobcCabinet::testStyleSheet()
{
    QString styleSheet=vobcCabinet->styleSheet();
    QVERIFY(styleSheet.compare("")!=0);
}

void TestVobcCabinet::testQueryDayReport()
{
    QSignalSpy spy(vobcCabinet,&VobcCabinet::showReport);
    vobcCabinet->rightPressButton=vobcCabinet->button_btm;
    vobcCabinet->queryDayReport();
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments = spy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    QVERIFY(arguments.at(1).type() == QVariant::String);
    QVERIFY(arguments.at(0).toInt() == 3);
    QVERIFY(arguments.at(1).toString() == "button_btm");
}

void TestVobcCabinet::testQueryMonReport()
{
    QSignalSpy spy(vobcCabinet,&VobcCabinet::showReport);
    vobcCabinet->rightPressButton=vobcCabinet->button_btm;
    vobcCabinet->queryMonReport();
    QTest::qWait(2000);
    QVERIFY(spy.count()==1);

    QList<QVariant> arguments = spy.takeFirst();

    QVERIFY(arguments.at(0).type() == QVariant::Int);
    QVERIFY(arguments.at(1).type() == QVariant::String);
    QVERIFY(arguments.at(0).toInt() == 4);
    QVERIFY(arguments.at(1).toString() == "button_btm");
}

void TestVobcCabinet::testCabinetMenu()
{
    QTest::mouseMove(vobcCabinet->button_btm);
    vobcCabinet->rightPressButton=vobcCabinet->button_btm;
    QMenu *menu=vobcCabinet->menu;

    QSignalSpy menuSpy(menu, &QMenu::triggered);
    QSignalSpy ReceivedSpy(vobcCabinet, &VobcCabinet::showReport);

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
    QVERIFY(arguments.at(1).toString() == "button_btm");

}

void TestVobcCabinet::cleanupTestCase()
{
    vobcCabinet->close();
    delete vobcCabinet;
}


