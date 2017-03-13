#include "powerprocess.h"
#include "powersimulatedataservice.h"
#include "power_data.h"
#include "mssdbconfig.h"

#include <QString>
#include <QtTest>
#include <QByteArray>
#include <QDate>
#include <QTime>
#include <QMap>
#include <QList>
#include <QSignalSpy>

Q_DECLARE_METATYPE(quint8*)
#define TEST_BUF_LEN 256

class PowerUnitTestTest : public QObject
{
    Q_OBJECT

public:
    PowerUnitTestTest();
    enum TestDataType
    {
        power_receiveData_start = 1,
        power_data_header,
        power_receiveData_end,
        power_invalid_start = power_receiveData_end,
        power_invalid_buf_null,
        power_invalid_len_zero,
        power_invalid_buf_len_lg,
        power_invalid_end
    };

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void powertestOpenAndCloseDB();
    void powertestCreateTBOfInfo();
    void powertestCreateTBOfDevice();
    void test_receiveDataByUDP_data();
    void test_receiveDataByUDP();
    void test_receiveData_data();
    void test_receiveData();
    void powerreceiveData();

private:
    void construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr);
    bool isAcceptedByonReceiveData(TestDataType type);
    bool isAcceptedByonDeviceDataReceived(TestDataType type);
    bool isInvalidData(TestDataType type);

private:
    PowerProcess *testpower;
    QMap<TestDataType, const char*> m_map;
    QUdpSocket *testPowerUdpSocket;
};

Q_DECLARE_METATYPE(PowerUnitTestTest::TestDataType)

PowerUnitTestTest::PowerUnitTestTest()
{
}

void PowerUnitTestTest::initTestCase()
{
    testpower = new PowerProcess();
    m_map.insert(power_data_header, "power_data_header");
    m_map.insert(power_invalid_buf_null, "power_invalid_len_zero");
    m_map.insert(power_invalid_len_zero, "power_invalid_len_zero");
    m_map.insert(power_invalid_buf_len_lg, "power_invalid_buf_len_lg");
    testPowerUdpSocket = new QUdpSocket(this);
    QVERIFY(testpower != NULL);
}

void PowerUnitTestTest::cleanupTestCase()
{
    testpower->closeDB();
    QVERIFY2(!testpower->db.isOpen(),"Failure");
    QSqlDatabase::removeDatabase(MSS_DB_NAME);
    if(testpower != NULL)
    {
        delete testpower;
        testpower = NULL;
    }
}

void PowerUnitTestTest::powertestOpenAndCloseDB()
{
    QVERIFY2(!testpower->db.isOpen(),"Failure");
    testpower->openDB();
    QVERIFY2(testpower->db.isOpen(),"Failure");
}

void PowerUnitTestTest::powertestCreateTBOfInfo()
{
    if(!testpower->db.isOpen())
    {
        testpower->openDB();
    }
    QSqlQuery query(testpower->db);

    if(testpower->db.tables().contains("psp_infomanage"))
    {
        query.exec("drop table psp_infomanage");
    }

    QVERIFY2(!testpower->db.tables().contains("psp_infomanage"),"Failure");
    QString queryStr = "create table if not exists "
                       "psp_infomanage(id int auto_increment primary key,voltage float,current float, "
                       "frequency float,phase float,"
                       "handle int,type int,statue int,"
                       "level int,savetime datetime,rawdata varchar(255))";
    testpower->createTBOfInfo(queryStr);
    QVERIFY2(testpower->db.tables().contains("psp_infomanage"),"Failure");

}

void PowerUnitTestTest::powertestCreateTBOfDevice()
{
    QSqlQuery query(testpower->db);
    if(testpower->db.tables().contains("device"))
    {
        qDebug()<<"the device table is already create,so drop it";
        query.exec("drop table device");
    }

    QVERIFY2(!testpower->db.tables().contains("device"),"Failure");
    QString queryStr = "create table if not exists "
                       "device(id int auto_increment primary key,devicename varchar(255),handle int)";
    testpower->createTBOfDevice(queryStr);

    QVERIFY2(testpower->db.tables().contains("device"),"Failure");
}

void PowerUnitTestTest::powerreceiveData()
{
    power_data_header_t s;
    quint8 buf3[256] ;
    s.voltage = 220.0;
    s.current = 5.5;
    s.hz = 100;
    s.angle = 90;
    s.handle = 5;
    s.owner = 3;
    s.type = 2;
    s.resevied2 = 0;

    int buf2[11] = {0,s.voltage,s.current,s.hz,s.angle,s.handle,s.type,s.owner};
    b2v_var_to_bytes((quint8 *)&s, buf3, power_data_header_cv_table, power_data_header_cv_table_len);
    testpower->receiveData(buf3,8);

    QSqlQuery query(testpower->db);
    query.exec("select * from psp_infomanage order by id desc LIMIT 1");
//    QSqlRecord rec = query.record();
    while(query.next())
    {
        for(int index = 1; index < 5; index++)
        {
            QVERIFY2(qAbs(query.value(index).toInt() - buf2[index])<0.0000001, "Failure");
        }
    }
}

bool PowerUnitTestTest::isInvalidData(TestDataType type)
{
    if(type > power_invalid_start && type < power_invalid_end)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PowerUnitTestTest::construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr)
{
    quint8* buf = NULL;
    quint16 pad_len = 0;
    quint16 check_len = 0;
    quint16 power_header_offset = 0;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    buf = new quint8[TEST_BUF_LEN];
    *buf_ptr = buf;
    switch(type)
    {
    case power_data_header:
    {
        power_data_header_t power_header;
        power_app_header_t power_app_header;
        power_heartbeat_t heartbeat;
        check_len = b2v_var_to_bytes((quint8*)(&power_header), buf, power_data_header_cv_table, power_data_header_cv_table_len);

        pad_len += check_len;
        power_header_offset = pad_len;
        power_app_header.msg_type = POWER_HEARTBEAT_MSG_TYPE;
        power_app_header.msg_len = 0;
        check_len = b2v_var_to_bytes((quint8*)(&power_app_header), buf + pad_len, power_app_header_cv_table, power_app_header_cv_table_len);
        pad_len += check_len;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, power_heartbeat_cv_table, power_heartbeat_cv_table_len);
        pad_len += check_len;
        power_app_header.msg_len = 2 + check_len;
        check_len = b2v_var_to_bytes((quint8*)(&power_app_header), buf + power_header_offset, power_app_header_cv_table, power_app_header_cv_table_len);
        if(isInvalidData(type))
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = pad_len - (((quint16)rand()) % power_app_header.msg_len) - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case power_invalid_buf_null:
    {
        delete[] buf;
        *buf_ptr = NULL;
        pad_len = 8;
    }
        break;
    case power_invalid_len_zero:
    {
        pad_len = 0;
    }
        break;
    case power_invalid_buf_len_lg:
    {
        pad_len = TEST_BUF_LEN;
    }
        break;
    default:
    {
        pad_len = TEST_BUF_LEN;
    }
        break;
    }
        *len_ptr = pad_len;
}

void PowerUnitTestTest::test_receiveData_data()
{
    quint8* buf_ptr = NULL;
    buf_ptr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(power_data_header);
    testTypes.append(power_invalid_buf_null);
    testTypes.append(power_invalid_len_zero);
    testTypes.append(power_invalid_buf_len_lg);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("test_type");
    QList<TestDataType>::iterator iter = testTypes.begin();

    for(; iter != testTypes.end(); iter++)
    {
        TestDataType test_type = *iter;
        const char* data_str = NULL;
        construct_test_data(test_type, &buf_ptr, &len);
        data_str = (const char*)(*(m_map.find(test_type)));
        QTest::newRow(data_str)<<buf_ptr<<len<<test_type;
    }
}

bool PowerUnitTestTest::isAcceptedByonReceiveData(TestDataType type)
{
    if(type > power_receiveData_start && type < power_receiveData_end)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void PowerUnitTestTest::test_receiveData()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, test_type);

    QSignalSpy spy_dataReceived(testpower, &PowerProcess::dataReceived);
    QVERIFY( spy_dataReceived.isValid() );
    QCOMPARE( spy_dataReceived.count(), 0 );
    QSignalSpy spy_error(testpower, &PowerProcess::error);
    QVERIFY( spy_error.isValid() );
    QCOMPARE( spy_error.count(), 0 );
    testpower->receiveData(buf, len);

    if(isAcceptedByonReceiveData(test_type))
    {
        QCOMPARE(spy_dataReceived.count(), 1);
        QCOMPARE(spy_error.count(), 0);
    }
    else
    {
        QCOMPARE(spy_dataReceived.count(), 0);
        QCOMPARE(spy_error.count(), 1);
        QList<QVariant> arguments = spy_error.takeFirst();
        QVERIFY(arguments.at(0).toInt() == PowerProcess::DataInvalid);
    }
}

void PowerUnitTestTest::test_receiveDataByUDP_data()
{
    quint8* buf_ptr = NULL;
    buf_ptr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(power_data_header);
    testTypes.append(power_invalid_buf_null);
    testTypes.append(power_invalid_len_zero);
    testTypes.append(power_invalid_buf_len_lg);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("test_type");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++)
    {
        TestDataType test_type = *iter;
        const char* data_str = NULL;
        construct_test_data(test_type, &buf_ptr, &len);
        data_str = (const char*)(*(m_map.find(test_type)));
        QTest::newRow(data_str)<<buf_ptr<<len<<test_type;
    }
}

void PowerUnitTestTest::test_receiveDataByUDP()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
//    QFETCH(TestDataType, test_type);
    testPowerUdpSocket->writeDatagram(QByteArray::fromRawData((char *)buf,len), QHostAddress(MSS_DB_HOST_NAME), 7777);
    QSignalSpy spy_dataReceived(testpower, &PowerProcess::dataReceived);
    QVERIFY( spy_dataReceived.isValid() );
    QCOMPARE( spy_dataReceived.count(), 0 );
    QSignalSpy spy_error(testpower, &PowerProcess::error);
    QVERIFY( spy_error.isValid() );
    QCOMPARE( spy_error.count(), 0 );
    testpower->receiveDataByUDP();

    QCOMPARE(spy_dataReceived.count(), 0);
    QCOMPARE(spy_error.count(), 1);
    QList<QVariant> arguments = spy_error.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PowerProcess::DataInvalid);
}

QTEST_APPLESS_MAIN(PowerUnitTestTest)

#include "tst_powerunittesttest.moc"
