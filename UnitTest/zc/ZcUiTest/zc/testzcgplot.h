#ifndef TESTZCGPLOT_H
#define TESTZCGPLOT_H
#include <QObject>
#include <QtTest>
#define private public
#define protected public
#include "zcgplot.h"
#undef protected
#undef private

class TestZcgplot: public QObject
{
    Q_OBJECT
public:
    TestZcgplot();
private Q_SLOTS :
    void zcWindowinit();
    void testInitial();
    void testStyleSheet();
    void testDeviceTip();
    void testshowReport();
    //void testshowAlarm();
    void cleanUpTestCase();
signals:
    void showAlarm(QString);

private :
    ZCGplot *device;
};

#endif // TESTZCGPLOT_H
