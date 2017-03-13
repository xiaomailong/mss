#ifndef TEST_POWERREADDATA_H
#define TEST_POWERREADDATA_H
#include <QtTest>
#include <QObject>
#define private public
#define protected public
#include "powerreaddata.h"
#undef protected
#undef private
class Test_PowerReadData : public QObject
{
    Q_OBJECT
public:
    explicit Test_PowerReadData(QObject *parent = 0);
private Q_SLOTS:
    void testDbConnection() ;
    void testRealTimeCurve() ;
    void testGetDbData();
    void testDayReport();
signals:
    void sendEventToRead(const QString &query);
public slots:
private:
    PowerReadData *readData;
    QDate date;



};

#endif // TEST_POWERREADDATA_H
