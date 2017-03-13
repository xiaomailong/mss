#ifndef TESTCIWINDOW_H
#define TESTCIWINDOW_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "cisystem.h"
#undef protected
#undef private

class TestCiWindow : public QObject
{
    Q_OBJECT
public:
    TestCiWindow();

private Q_SLOTS:
    void initTestCase();

    void testInitial();
    void testEventFromMss();
    void testEventFromMap();
    void testTabClose();
    void testSendEventToMss();
    void testWindowDestroy();

    void cleanupTestCase();


signals:

    void EventFromMss(const QString msg);
    void EventFromMap(int type,QString deviceName);

private:
    CiSystem *ci;
};

#endif // TESTCIWINDOW_H
