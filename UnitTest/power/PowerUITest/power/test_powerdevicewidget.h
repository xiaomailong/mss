#ifndef TEST_POWERDEVICEWIDGET_H
#define TEST_POWERDEVICEWIDGET_H

#include <QObject>

#define private public
#define protected public
#include "powerdevicewidget.h"
#undef protected
#undef private
class Test_powerdevicewidget : public QObject
{
    Q_OBJECT
public:
    explicit Test_powerdevicewidget(QObject *parent = 0);

private Q_SLOTS:
    void initTestCase() ;
    void testDeviceTip() ;
    void show_contextmenu();

signals:

public slots:
private:
    PowerDeviceWidget *device;
};

#endif // TEST_POWERDEVICEWIDGET_H
