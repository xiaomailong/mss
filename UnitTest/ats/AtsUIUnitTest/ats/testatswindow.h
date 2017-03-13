#ifndef TESTATSWINDOW_H
#define TESTATSWINDOW_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "atssystem.h"
#undef protected
#undef private


class TestAtsWindow : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsWindow(QObject *parent = 0);

private Q_SLOTS:
    void initTestCase();
    void testInit();
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
    AtsSystem *ats;
};

#endif // TESTATSWINDOW_H
