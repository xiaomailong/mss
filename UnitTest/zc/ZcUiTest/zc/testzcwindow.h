#ifndef TESTZCWINDOW_H
#define TESTZCWINDOW_H
#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "zcsystem.h"
#undef protected
#undef private

class TestZcWindow: public QObject
{
    Q_OBJECT
public:
    TestZcWindow();
private Q_SLOTS:
    void initTestCase();

    void testInitial();
    void testEventFromMss();
    void testEventFromMap();
//    void testAlarmFromMss();
    void testTabClose();
    void testSendEventToMss();
    void testWindowDestroy();

signals:

    void EventFromMss(const QString msg);
    void EventFromMap(int type,QString deviceName);
private:
    ZcSystem *zc;
};

#endif // TESTZCWINDOW_H
