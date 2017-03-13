#ifndef TESTVOBCWINDOW_H
#define TESTVOBCWINDOW_H

#include <QObject>
#include <QtTest>
#include "vobc_data.h"

#define private public
#define protected public
#include "vobcsystem.h"
#undef protected
#undef private


class TestVobcWindow : public QObject
{
    Q_OBJECT
public:
    TestVobcWindow();


private Q_SLOTS:
    void initTestCase();

    void testInitial();
    void testEventFromMss();
    void testEventFromMap();
    void testAlarmFromMss();
    void testTabClose();
    void testSendEventToMss();
    void testWindowDestroy();

    void cleanupTestCase();


signals:

    void EventFromMss(const QString msg);
    void EventFromMap(int type,QString deviceName);
    void AlarmFromMss(vobc_subsys_msg_t AtsMsg);

private:
    VobcSystem *vobc;

};

#endif // TESTVOBCWINDOW_H
