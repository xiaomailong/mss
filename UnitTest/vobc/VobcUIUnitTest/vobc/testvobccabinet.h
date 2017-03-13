#ifndef TESTVOBCCABINET_H
#define TESTVOBCCABINET_H

#include <QObject>
#include <QtTest>

#define private public
#define protected public
#include "vobccabinet.h"
#undef protected
#undef private

class TestVobcCabinet : public QObject
{
    Q_OBJECT
public:
    TestVobcCabinet();

private Q_SLOTS:

    void initTestCase();

    void testInitial();
    void testStyleSheet();
    void testQueryDayReport();
    void testQueryMonReport();
    void testCabinetMenu();

    void cleanupTestCase();

signals:

public slots:

private:
    VobcCabinet *vobcCabinet;
};

#endif // TESTVOBCCABINET_H
