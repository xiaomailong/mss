#ifndef TESTATSDEVICE_H
#define TESTATSDEVICE_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "atsdevice.h"
#undef protected
#undef private


class TestAtsDevice : public QObject
{
    Q_OBJECT
public:
    explicit TestAtsDevice(QObject *parent = 0);

private Q_SLOTS:
    void initTestCase();
    void testInitView();
    void testStyleSheet();
    void testDeviceXmlInfo();
    void testDeviceTip();
    void testshowReport();

private:
    AtsDevice *atsDevice;
};

#endif // TESTATSDEVICE_H
