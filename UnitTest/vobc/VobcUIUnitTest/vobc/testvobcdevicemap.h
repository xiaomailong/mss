#ifndef TESTVOBCDEVICEMAP_H
#define TESTVOBCDEVICEMAP_H

#include <QObject>
#include <QtTest>
#include "vobc_data.h"

#define private public
#define protected public
#include "vobcdevice.h"
#undef protected
#undef private

class TestVobcDeviceMap : public QObject
{
    Q_OBJECT
public:
    TestVobcDeviceMap();

private Q_SLOTS:

    void initTestCase();

    void testInitial();
    void testStyleSheet();
    void testDeviceXmlInfo();
    void testDeviceTip();
    void testshowReport();
    void testshowAlarm();

    void cleanupTestCase();


signals:
    void showAlarm(vobc_subsys_msg_t AtsMsg);

private:
    VobcDevice *device;
};

#endif // TESTVOBCDEVICEMAP_H
