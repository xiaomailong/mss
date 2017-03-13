#ifndef TESTCIDEVICE_H
#define TESTCIDEVICE_H

#include <QObject>
#define private public
#define protected public
#include "cidevice.h"
#include "mssdatadefine.h"
#include "ci_data.h"
#undef protected
#undef private


class TestCiDevice : public QObject
{
    Q_OBJECT
public:
    explicit TestCiDevice(QObject *parent = 0);

signals:
    void showAlarm(ci_ci_t *msg);

private Q_SLOTS:
    void initTestCase();

    void testInitial();

    void testStyleSheet();

    void testDeviceTip();

    void testShowReport();

    void testShowAlarm();

    void cleanupTestCase();

private:
    CiDevice *ciDevice;
};

#endif // TESTCIDEVICE_H
