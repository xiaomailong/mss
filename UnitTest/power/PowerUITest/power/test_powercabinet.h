#ifndef TEST_POWERCABINET_H
#define TEST_POWERCABINET_H

#include <QObject>

#define private public
#define protected public
#include "powercabinet.h"
#undef protected
#undef private
class Test_PowerCabinet : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerCabinet(QObject *parent = 0);

signals:

public slots:
private :
    Powercabinet *powerCabinet ;
private Q_SLOTS:

    void initTestCase();
    void testInitial();
    void testStyleSheet();
};

#endif // TEST_POWERCABINET_H
