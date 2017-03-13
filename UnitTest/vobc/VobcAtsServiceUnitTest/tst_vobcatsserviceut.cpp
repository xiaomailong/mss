#include <QString>
#include <QtTest>
#include "vobcatsservice.h"
Q_DECLARE_METATYPE(vobc_subsys_msg_t)
#define TEST_BUF_LEN 255
Q_DECLARE_METATYPE(quint8*)

class VobcAtsServiceUnitTest : public QObject
{
    Q_OBJECT

public:
    VobcAtsServiceUnitTest();
    enum TestDataType{
        correct_data_start,
        subsys_alarm,
        correct_data_end,

        incorrect_data_begin = correct_data_end,
        subsys_notToVobc,
        subsys_alarm_invalid_len,
        null_point,
        subsys_insertErr,
        incorrect_data_end,
    };
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_start();
    void test_HandleAtsData();
    void test_HandleAtsData_data();
    void test_HandleAtsDataInsertErr();
    void test_HandleAtsInstDisplay();
    void test_HandleAtsInstDisplay_data();
    void test_stop();
private:
    void construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr);
    bool isInvalidData(TestDataType type);

    VobcAtsService atsService;
    QMap<TestDataType, const char*> m_map;

};
Q_DECLARE_METATYPE(VobcAtsServiceUnitTest::TestDataType)

VobcAtsServiceUnitTest::VobcAtsServiceUnitTest()
{
}

void VobcAtsServiceUnitTest::initTestCase()
{
    m_map.insert(subsys_alarm, "subsys_alarm");
    m_map.insert(subsys_notToVobc, "subsys_notToVobc");
    m_map.insert(subsys_alarm_invalid_len, "subsys_alarm_invalid_len");
    m_map.insert(null_point, "null_point");
}

void VobcAtsServiceUnitTest::test_start()
{
    QSignalSpy spy_error(&atsService, &VobcAtsService::castError);
    atsService.startService();
    QCOMPARE(spy_error.count(), 0);
}

bool VobcAtsServiceUnitTest::isInvalidData(TestDataType type)
{
    if(type > incorrect_data_begin && type < incorrect_data_end){
        return true;
    } else {
        return false;
    }
}

void VobcAtsServiceUnitTest::construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr)
{
    quint8* buf = NULL;
    buf = new quint8[TEST_BUF_LEN];
    vobc_ats_header_t s;
    quint16 sizebuf, pad_len = 0;
    *buf_ptr = buf;
    switch (type) {
    case subsys_alarm:
    case subsys_alarm_invalid_len:
    {
        s.vobc_ats_interface = ATS_MSS_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ATS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;

        //convert struct to bytes
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);
        vobc_subsys_msg_t ats_mss_alarm;
        ats_mss_alarm.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
        ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.dev_id = ((quint16)(rand())) % 0xFFFF;
        ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
        ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
        ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0xFFFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&ats_mss_alarm, buf+sizebuf +2, vobc_subsys_cv_table, vobc_subsys_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = 0;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
        break;
    }
    case subsys_notToVobc:
    {
        s.vobc_ats_interface = ATS_MSS_INTERFACE;
        s.send_id_msg = ID_MESSAGE_ATS;
        s.incept_id_msg = ID_MESSAGE_ATS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;

        //convert struct to bytes
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);
        vobc_subsys_msg_t ats_mss_alarm;
        ats_mss_alarm.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
        ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.dev_id = ((quint16)(rand())) % 0xFFFF;
        ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
        ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
        ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0xFFFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&ats_mss_alarm, buf+sizebuf +2, vobc_subsys_cv_table, vobc_subsys_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        break;
    }
    case subsys_insertErr:
    {
        s.vobc_ats_interface = ATS_MSS_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ATS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;

        //convert struct to bytes
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);
        vobc_subsys_msg_t ats_mss_alarm;
        ats_mss_alarm.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
        ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.dev_id = ((quint16)(rand())) % 0xFFFF;
        ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
        ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
        ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
        ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0xFFFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&ats_mss_alarm, buf+sizebuf +2, vobc_subsys_cv_table, vobc_subsys_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;
        break;
    }
    case null_point:
    {
        delete[] buf;
        *buf_ptr = NULL;
        break;
    }
    default:
        break;
    }
    *len_ptr = pad_len;

}

void VobcAtsServiceUnitTest::test_HandleAtsData_data()
{
    quint8 * buf_ptr = NULL;
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(subsys_alarm);
    testTypes.append(subsys_alarm_invalid_len);
    testTypes.append(subsys_notToVobc);
    testTypes.append(null_point);


    QTest::addColumn<quint8 *>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("test_type");

    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++){
        TestDataType test_type = *iter;
        const char* data_str = NULL;
        construct_test_data(test_type, &buf_ptr, &len);
        data_str = (const char*)(*(m_map.find(test_type)));
        QTest::newRow(data_str)<<buf_ptr<<len<<test_type;
    }


}

void VobcAtsServiceUnitTest::test_HandleAtsData()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, test_type);
    QSignalSpy spy_error(&atsService, &VobcAtsService::castError);
    atsService.handleAtsData(buf,len);
    if(isInvalidData(test_type)){
        QCOMPARE(spy_error.count(), 1);
        if(spy_error.count() == 1){
            QList<QVariant> arguments = spy_error.takeFirst();
            int err = arguments.at(0).toInt();
            QVERIFY(err == ErrInvalidArgument);
        }
    } else {
        QCOMPARE(spy_error.count(), 0);
    }

}

void VobcAtsServiceUnitTest::test_HandleAtsDataInsertErr()
{

    quint8 * buf_ptr = NULL;
    quint16 len = 0;
    construct_test_data(subsys_insertErr, &buf_ptr, &len);
    QSignalSpy spy_error(&atsService, &VobcAtsService::castError);
    atsService.stopService();
    atsService.handleAtsData(buf_ptr,len);
    QCOMPARE(spy_error.count(), 1);
    if(spy_error.count() == 1){
        QList<QVariant> arguments = spy_error.takeFirst();
        int err = arguments.at(0).toInt();
        QVERIFY(err == ErrInsertTable);
    }
}

void VobcAtsServiceUnitTest::test_HandleAtsInstDisplay_data()
{
    QTest::addColumn<bool>("isDBok");
    QTest::addColumn<bool>("isInstShow");
    QTest::addColumn<int>("result");

    QTest::newRow("Success Insert&setInstT")<<true<<true<<1;
    QTest::newRow("Success Insert&setInstF")<<true<<false<<0;
    QTest::newRow("fail Insert&setInstT")<<false<<true<<0;
    QTest::newRow("fail Insert&setInstF")<<false<<false<<0;

}
void VobcAtsServiceUnitTest::test_HandleAtsInstDisplay()
{
    QFETCH(bool, isDBok);
    QFETCH(bool, isInstShow);
    QFETCH(int, result);
    quint8 * buf_ptr = NULL;
    quint16 len = 0;
    construct_test_data(subsys_alarm, &buf_ptr, &len);
    QSignalSpy spy_error(&atsService, &VobcAtsService::castError);
    QSignalSpy spy_InstShow(&atsService, &VobcAtsService::reportAlarmMsg);

    if(isDBok){
        atsService.startService();
        if(isInstShow)
            atsService.setInstFlag(true);
        else
            atsService.setInstFlag(false);
        atsService.handleAtsData(buf_ptr,len);
        QCOMPARE(spy_error.count(), 0);
        QCOMPARE(spy_InstShow.count(), result);

    }else{
        atsService.stopService();
        if(isInstShow)
            atsService.setInstFlag(true);
        else
            atsService.setInstFlag(false);
        atsService.handleAtsData(buf_ptr,len);
        QCOMPARE(spy_error.count(), 1);
        QCOMPARE(spy_InstShow.count(), result);

    }
}

void VobcAtsServiceUnitTest::test_stop()
{
    atsService.stopService();
    QVERIFY2(true, "Failure");
}

void VobcAtsServiceUnitTest::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(VobcAtsServiceUnitTest)

#include "tst_vobcatsserviceut.moc"
