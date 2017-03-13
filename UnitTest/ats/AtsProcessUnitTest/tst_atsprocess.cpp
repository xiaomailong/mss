#include <QString>
#include <QtTest>
#include "atsprocess.h"
#include <QThread>
#include <QByteArray>
#include "ats_data.h"
#include "mssdatadefine.h"
#include <QDate>
#include <QTime>
#include <QMap>
#include <QList>
#include <QSignalSpy>

Q_DECLARE_METATYPE(quint8*)
Q_DECLARE_METATYPE(ats_mss_alarm_t*)
#define TEST_BUF_LEN 256
class AtsProcessUnitTest : public QObject
{
    Q_OBJECT

public:
    AtsProcessUnitTest();
    enum TestDataType
    {
        ats_onReceiveData_start = 1,
        ats_vobc_heartbeat,
        ats_vobc_ato_cmd,
        ats_ci_heartbeat,
        ats_ci_cmd,
        ats_ci_status,
        ats_zc_heartbeat,
        ats_zc_tsr_validate,
        ats_zc_tsr_exec_cmd,
        ats_zc_tsr_on_confirm,
        ats_onReceiveData_end,
        ats_onDeviceDataReceived_start = ats_onReceiveData_end,
        ats_mss_alarm,
        vobc_mss_alarm,
        ats_onDeviceDataReceived_end,
        ats_invalid_start = ats_onDeviceDataReceived_end,
        ats_invalid_buf_null,
        ats_invalid_len_zero,
        ats_ci_invalid_buf_len_lt_common_header,
        ats_zc_invalid_buf_len_lt_common_header,
        ats_vobc_invalid_buf_len_lt_common_header,
        ats_mss_invalid_buf_len_lt_common_header,
        vobc_mss_invalid_buf_len_lt_common_header,
        ats_ci_invalid_buf_len_lt_plus_app_header,
        ats_zc_invalid_buf_len_lt_plus_app_header,
        ats_vobc_invalid_buf_len_lt_plus_app_header,
        ats_mss_invalid_buf_len_lt_plus_app_header,
        ats_invalid_buf_len_lg,
        ats_invalid_end
    };
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
#if 0
    void init();
    void cleanup();
#endif
    void test_start();
    void test_onReceiveData_data();
    void test_onReceiveData();
    void test_onDeviceDataReceived_data();
    void test_onDeviceDataReceived();
    void test_stop();
private:


    void construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr);
    bool isAcceptedByonReceiveData(TestDataType type);
    bool isAcceptedByonDeviceDataReceived(TestDataType type);
    bool isInvalidData(TestDataType type);
private:
    quint32 m_ats_vobc_msg_list;
    quint32 m_ats_ci_msg_list;
    quint32 m_ats_zc_msg_list;
    quint32 m_ats_mss_msg_list;
    AtsProcess *m_atsprocess;
    QMap<TestDataType, const char*> m_map;
};

Q_DECLARE_METATYPE(AtsProcessUnitTest::TestDataType)

AtsProcessUnitTest::AtsProcessUnitTest()
{
    qDebug("Entry");
    m_atsprocess = NULL;
    qRegisterMetaType<ats_mss_alarm_t*>("ats_mss_alarm_t*");
}

void AtsProcessUnitTest::initTestCase()
{
    m_atsprocess = new AtsProcess();
    m_map.insert(ats_vobc_heartbeat, "ats_vobc_heartbeat");
    m_map.insert(ats_vobc_ato_cmd, "ats_vobc_ato_cmd");
    m_map.insert(ats_ci_heartbeat, "ats_ci_heartbeat");
    m_map.insert(ats_ci_cmd, "ats_ci_cmd");
    m_map.insert(ats_ci_status, "ats_ci_status");
    m_map.insert(ats_zc_heartbeat, "ats_zc_heartbeat");
    m_map.insert(ats_zc_tsr_validate, "ats_zc_tsr_validate");
    m_map.insert(ats_zc_tsr_exec_cmd, "ats_zc_tsr_exec_cmd");
    m_map.insert(ats_zc_tsr_on_confirm, "ats_zc_tsr_on_confirm");
    m_map.insert(ats_mss_alarm, "ats_mss_alarm");
    m_map.insert(vobc_mss_alarm, "vobc_mss_alarm");
    m_map.insert(ats_invalid_buf_null, "ats_invalid_buf null");
    m_map.insert(ats_invalid_len_zero, "ats_invalid_buf len zero");
    m_map.insert(ats_ci_invalid_buf_len_lt_common_header, "ats_ci_invalid_buf len < len(common header)");
    m_map.insert(ats_zc_invalid_buf_len_lt_common_header, "ats_zc_invalid_buf len < len(common header)");
    m_map.insert(ats_vobc_invalid_buf_len_lt_common_header, "ats_vobc_invalid_buf len < len(common header)");
    m_map.insert(ats_mss_invalid_buf_len_lt_common_header, "ats_mss_invalid_buf len < len(common header)");
    m_map.insert(vobc_mss_invalid_buf_len_lt_common_header, "vobc_mss_invalid_buf len < len(common header)");
    m_map.insert(ats_ci_invalid_buf_len_lt_plus_app_header, "ats_ci_invalid_buf len < len(common+app header)");
    m_map.insert(ats_zc_invalid_buf_len_lt_plus_app_header, "ats_zc_invalid_buf len < len(common+app header)");
    m_map.insert(ats_vobc_invalid_buf_len_lt_plus_app_header, "ats_vobc_invalid_buf len < len(common+app header)");
    m_map.insert(ats_mss_invalid_buf_len_lt_plus_app_header, "ats_mss_invalid_buf len < len(common+app header)");
    m_map.insert(ats_invalid_buf_len_lg, "ats_invalid_buf_len_lg");
    m_ats_vobc_msg_list = rand() % 0xFFFF;
    m_ats_ci_msg_list = rand() % 0xFFFF;
    m_ats_zc_msg_list = rand() % 0xFFFF;
    m_ats_mss_msg_list = rand() % 0xFFFF;
    QVERIFY(m_atsprocess != NULL);
}

void AtsProcessUnitTest::cleanupTestCase()
{
    if(m_atsprocess != NULL){
        delete m_atsprocess;
        m_atsprocess = NULL;
    }
}
#if 0
void AtsProcessUnitTest::init()
{
    //qDebug("Entry");
}
void AtsProcessUnitTest::cleanup()
{
    //qDebug("Entry");
}
#endif

void AtsProcessUnitTest::test_start()
{
    QSignalSpy spy_started(m_atsprocess, &AtsProcess::started);
    QSignalSpy spy_error(m_atsprocess, &AtsProcess::error);
    m_atsprocess->start();
    QCOMPARE(spy_error.count() + spy_started.count(), 1);
    if(spy_error.count() == 1){
        QList<QVariant> arguments = spy_error.takeFirst();
        int err = arguments.at(0).toInt();
        QVERIFY(err == AtsProcess::DataBaseOpenError || err == AtsProcess::TableCreateError);
    }
}

bool AtsProcessUnitTest::isAcceptedByonReceiveData(TestDataType type)
{
    if(type > ats_onReceiveData_start && type < ats_onReceiveData_end){
        return true;
    } else {
        return false;
    }
}

bool AtsProcessUnitTest::isAcceptedByonDeviceDataReceived(TestDataType type)
{
    if(type > ats_onDeviceDataReceived_start && type < ats_onDeviceDataReceived_end){
        return true;
    } else {
        return false;
    }
}

bool AtsProcessUnitTest::isInvalidData(TestDataType type)
{
    if(type > ats_invalid_start && type < ats_invalid_end){
        return true;
    } else {
        return false;
    }
}

void AtsProcessUnitTest::construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr)
{
    quint8* buf = NULL;
    quint16 pad_len = 0;
    quint16 check_len = 0;
    quint16 app_header_offset = 0;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    buf = new quint8[TEST_BUF_LEN];
    *buf_ptr = buf;
    switch(type){
        case ats_vobc_heartbeat:
        case ats_vobc_invalid_buf_len_lt_plus_app_header:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_vobc_heartbeat_t heartbeat;
            ats_header.interface_type = ATS_VOBC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_VOBC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_vobc_msg_list;
            m_ats_vobc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_VOBC_HEARTBEAT_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            heartbeat.year = date.year() - 2000;
            heartbeat.month = date.month();
            heartbeat.date = date.day();
            heartbeat.hour = time.hour();
            heartbeat.minute = time.minute();
            heartbeat.second = time.second();
            check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, ats_vobc_heartbeat_cv_table, ats_vobc_heartbeat_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            if(isInvalidData(type)){
                quint8* buf_for_invalid = NULL;
                quint16 len_for_invalid = 0;
                len_for_invalid = pad_len - (((quint16)rand()) % ats_app_header.msg_len) - 1;
                buf_for_invalid = new quint8[len_for_invalid];
                memcpy(buf_for_invalid, buf, len_for_invalid);
                pad_len = len_for_invalid;
                *buf_ptr = buf_for_invalid;
                delete[] buf;
            }
        }
            break;
        case ats_vobc_ato_cmd:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_vobc_ato_cmd_t ats_vobc_ato_cmd;
            ats_header.interface_type = ATS_VOBC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_VOBC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_vobc_msg_list;
            m_ats_vobc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_VOBC_ATO_CMD_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_vobc_ato_cmd.service_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.line_id =  ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.next_zc_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.next_ci_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.next_ats_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.cargroupline_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.cargroup_id = (((quint16)(rand())) % 999 ) + 1;
            ats_vobc_ato_cmd.sourceline_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.trainnum_id = (((quint16)(rand())) % 9999 ) + 1;
            ats_vobc_ato_cmd.destination_track_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.destination_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.plan_traffic_direction = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.next_skip_stop_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.station_stop_time = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.next_skip_stop_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.nc_interval_operation = 0;
            ats_vobc_ato_cmd.detain_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.reentry_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.back_indication = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.gating_strategy = ((rand() % 2 ) == 0) ? 0x55 : 0xCC;
            ats_vobc_ato_cmd.reserved_field = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_vobc_ato_cmd), buf + pad_len, ats_vobc_ato_cmd_cv_table, ats_vobc_ato_cmd_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_ci_heartbeat:
        case ats_ci_invalid_buf_len_lt_plus_app_header:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_ci_heartbeat_t heartbeat;
            ats_header.interface_type = ATS_CI_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_CI;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_ci_msg_list;
            m_ats_ci_msg_list++;
            ats_header.com_cycle = 8;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_CI_HEARTBEAT_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            heartbeat.year = date.year() - 2000;
            heartbeat.month = date.month();
            heartbeat.date = date.day();
            heartbeat.hour = time.hour();
            heartbeat.minute = time.minute();
            heartbeat.second = time.second();
            check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, ats_ci_heartbeat_cv_table, ats_ci_heartbeat_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            if(isInvalidData(type)){
                quint8* buf_for_invalid = NULL;
                quint16 len_for_invalid = 0;
                len_for_invalid = pad_len - (((quint16)rand()) % ats_app_header.msg_len) - 1;
                buf_for_invalid = new quint8[len_for_invalid];
                memcpy(buf_for_invalid, buf, len_for_invalid);
                pad_len = len_for_invalid;
                *buf_ptr = buf_for_invalid;
                delete[] buf;
            }
        }
            break;
        case ats_ci_cmd:
        {
            quint16 temp_len = 0;
            int i = 0;
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_ci_cmd_t ats_ci_cmd;
            ats_ci_cmd_data_t ats_ci_cmd_data;
            ats_header.interface_type = ATS_CI_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_CI;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_ci_msg_list;
            m_ats_ci_msg_list++;
            ats_header.com_cycle = 8;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_CI_CMD_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_ci_cmd.cmd_cnt = (((quint8) (rand())) % 4) + 1;
            check_len = b2v_var_to_bytes((quint8*)(&ats_ci_cmd), buf + pad_len, ats_ci_cmd_cv_table, ats_ci_cmd_cv_table_len);
            pad_len += check_len;
            temp_len += check_len;
            for(i = 0; i < ats_ci_cmd.cmd_cnt; i++){
                ats_ci_cmd_data.cmd_type = (((quint8) (rand())) % 0x37) + 1;
                ats_ci_cmd_data.device_id = ((quint32)(rand())) % 0xFFFFFFFF;
                ats_ci_cmd_data.device_type = (((quint8) (rand())) % 0x11) + 1;
                ats_ci_cmd_data.reserved_field = 0xFF;
                check_len = b2v_var_to_bytes((quint8*)(&ats_ci_cmd_data), buf + pad_len, ats_ci_cmd_data_cv_table, ats_ci_cmd_data_cv_table_len);
                temp_len += check_len;
                pad_len += check_len;
            }
            ats_app_header.msg_len = 2 + temp_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_ci_status:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_ci_status_t ats_ci_status;
            ats_header.interface_type = ATS_CI_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_CI;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_ci_msg_list;
            m_ats_ci_msg_list++;
            ats_header.com_cycle = 8;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_CI_RUNNING_STS_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_ci_status.main_standby_sts = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_ci_status.ato_req_rsp = ((rand() % 2 ) == 0) ? 0x55 : 0xCC;
            check_len = b2v_var_to_bytes((quint8*)(&ats_ci_status), buf + pad_len, ats_ci_status_cv_table, ats_ci_status_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_zc_heartbeat:
        case ats_zc_invalid_buf_len_lt_plus_app_header:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_heartbeat_t heartbeat;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_HEARTBEAT_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            heartbeat.year = date.year() - 2000;
            heartbeat.month = date.month();
            heartbeat.date = date.day();
            heartbeat.hour = time.hour();
            heartbeat.minute = time.minute();
            heartbeat.second = time.second();
            check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, ats_zc_heartbeat_cv_table, ats_zc_heartbeat_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            if(isInvalidData(type)){
                quint8* buf_for_invalid = NULL;
                quint16 len_for_invalid = 0;
                len_for_invalid = pad_len - (((quint16)rand()) % ats_app_header.msg_len) - 1;
                buf_for_invalid = new quint8[len_for_invalid];
                memcpy(buf_for_invalid, buf, len_for_invalid);
                pad_len = len_for_invalid;
                *buf_ptr = buf_for_invalid;
                delete[] buf;
            }
        }
            break;
        case ats_zc_tsr_validate:
        {
            quint16 temp_len = 0;
            int i = 0;
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_tsr_validate_t ats_zc_tsr_validate;
            ats_zc_tsr_logic_track_data_t ats_zc_tsr_logic_track_data;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_TSR_VALIDATE_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_zc_tsr_validate.tmp_speed_limit = ((rand() % 2 ) == 0) ? 2 : 0xFF;
            ats_zc_tsr_validate.logic_track_cnt = (((quint8) (rand())) % 4) + 1;
            check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_validate), buf + pad_len, ats_zc_tsr_validate_cv_table, ats_zc_tsr_validate_cv_table_len);
            pad_len += check_len;
            temp_len += check_len;
            for(i = 0; i < ats_zc_tsr_validate.logic_track_cnt; i++){
                ats_zc_tsr_logic_track_data.logic_track_id = ((quint16)(rand())) % 0xFFFF;
                check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_logic_track_data), buf + pad_len, ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
                temp_len += check_len;
                pad_len += check_len;
            }
            ats_app_header.msg_len = 2 + temp_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_zc_tsr_exec_cmd:
        {
            quint16 temp_len = 0;
            int i = 0;
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_tsr_exec_cmd_t ats_zc_tsr_exec_cmd;
            ats_zc_tsr_logic_track_data_t ats_zc_tsr_logic_track_data;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_TSR_EXEC_CMD_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_zc_tsr_exec_cmd.tmp_speed_limit = ((rand() % 2 ) == 0) ? 2 : 0xFF;
            ats_zc_tsr_exec_cmd.logic_track_cnt = (((quint8) (rand())) % 4) + 1;
            check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_exec_cmd), buf + pad_len, ats_zc_tsr_exec_cmd_cv_table, ats_zc_tsr_exec_cmd_cv_table_len);
            pad_len += check_len;
            temp_len += check_len;
            for(i = 0; i < ats_zc_tsr_exec_cmd.logic_track_cnt; i++){
                ats_zc_tsr_logic_track_data.logic_track_id = ((quint16)(rand())) % 0xFFFF;
                check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_logic_track_data), buf + pad_len, ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
                temp_len += check_len;
                pad_len += check_len;
            }
            ats_app_header.msg_len = 2 + temp_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_zc_tsr_on_confirm:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_tsr_on_confirm_t ats_zc_tsr_on_confirm;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_TSR_ON_CONFIRM_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_zc_tsr_on_confirm.zc_id = ((quint16)(rand())) % 0xFFFF;
            check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_on_confirm), buf + pad_len, ats_zc_tsr_on_confirm_cv_table, ats_zc_tsr_on_confirm_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_mss_alarm:
        case ats_mss_invalid_buf_len_lt_plus_app_header:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_mss_alarm_t ats_mss_alarm;
            ats_header.interface_type = ATS_MSS_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_MSS;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_mss_msg_list;
            m_ats_mss_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_MSS_ALARM_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
            ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.dev_id = ((quint16)(rand())) % 0xFFFF;
            ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
            ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
            ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0xFFFF;
            check_len = b2v_var_to_bytes((quint8*)(&ats_mss_alarm), buf + pad_len, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            if(isInvalidData(type)){
                quint8* buf_for_invalid = NULL;
                quint16 len_for_invalid = 0;
                len_for_invalid = pad_len - (((quint16)rand()) % ats_app_header.msg_len) - 1;
                buf_for_invalid = new quint8[len_for_invalid];
                memcpy(buf_for_invalid, buf, len_for_invalid);
                pad_len = len_for_invalid;
                *buf_ptr = buf_for_invalid;
                delete[] buf;
            }
        }
            break;
        case vobc_mss_alarm:
        {
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_mss_alarm_t ats_mss_alarm;
            ats_header.interface_type = ATS_MSS_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_VOBC;
            ats_header.incept_id_msg = ID_MESSAGE_MSS;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_mss_msg_list;
            m_ats_mss_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_MSS_ALARM_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
            ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.dev_id = ((quint16)(rand())) % 0xFFFF;
            ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
            ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
            ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0xFFFF;
            check_len = b2v_var_to_bytes((quint8*)(&ats_mss_alarm), buf + pad_len, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        }
            break;
        case ats_invalid_buf_null:
        {
            delete[] buf;
            *buf_ptr = NULL;
        }
            break;
        case ats_invalid_len_zero:
        {
            pad_len = 0;
        }
            break;
        case ats_mss_invalid_buf_len_lt_common_header:
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            ats_common_header_t ats_header;
            ats_header.interface_type = ATS_MSS_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_MSS;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_mss_msg_list;
            m_ats_mss_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            len_for_invalid = (((quint16)rand()) % (pad_len - 1)) + 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
            break;
        case vobc_mss_invalid_buf_len_lt_common_header:
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            ats_common_header_t ats_header;
            ats_header.interface_type = ATS_MSS_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_VOBC;
            ats_header.incept_id_msg = ID_MESSAGE_MSS;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_mss_msg_list;
            m_ats_mss_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            len_for_invalid = (((quint16)rand()) % (pad_len - 1)) + 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
            break;
        case ats_ci_invalid_buf_len_lt_common_header:
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            ats_common_header_t ats_header;
            ats_header.interface_type = ATS_CI_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_CI;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_ci_msg_list;
            m_ats_ci_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            len_for_invalid = (((quint16)rand()) % (pad_len - 1)) + 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
            break;
        case ats_zc_invalid_buf_len_lt_common_header:
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            ats_common_header_t ats_header;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            len_for_invalid = (((quint16)rand()) % (pad_len - 1)) + 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
            break;
        case ats_vobc_invalid_buf_len_lt_common_header:
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            ats_common_header_t ats_header;
            ats_header.interface_type = ATS_VOBC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_VOBC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_vobc_msg_list;
            m_ats_vobc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            len_for_invalid = (((quint16)rand()) % (pad_len - 1)) + 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
            break;
        case ats_invalid_buf_len_lg:
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

void AtsProcessUnitTest::test_onReceiveData_data()
{
    quint8* buf_ptr = NULL;
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(ats_vobc_heartbeat);
    testTypes.append(ats_vobc_ato_cmd);
    testTypes.append(ats_ci_heartbeat);
    testTypes.append(ats_ci_cmd);
    testTypes.append(ats_ci_status);
    testTypes.append(ats_zc_heartbeat);
    testTypes.append(ats_zc_tsr_validate);
    testTypes.append(ats_zc_tsr_exec_cmd);
    testTypes.append(ats_zc_tsr_on_confirm);
    testTypes.append(ats_mss_alarm);
    testTypes.append(ats_invalid_buf_null);
    testTypes.append(ats_invalid_len_zero);
    testTypes.append(ats_ci_invalid_buf_len_lt_common_header);
    testTypes.append(ats_zc_invalid_buf_len_lt_common_header);
    testTypes.append(ats_vobc_invalid_buf_len_lt_common_header);
    testTypes.append(ats_mss_invalid_buf_len_lt_common_header);
    testTypes.append(ats_ci_invalid_buf_len_lt_plus_app_header);
    testTypes.append(ats_zc_invalid_buf_len_lt_plus_app_header);
    testTypes.append(ats_vobc_invalid_buf_len_lt_plus_app_header);
    testTypes.append(ats_mss_invalid_buf_len_lt_plus_app_header);
    testTypes.append(ats_invalid_buf_len_lg);
    QTest::addColumn<quint8*>("buf");
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

void AtsProcessUnitTest::test_onReceiveData()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, test_type);
    QSignalSpy spy_dataReceived(m_atsprocess, &AtsProcess::dataReceived);
    QSignalSpy spy_error(m_atsprocess, &AtsProcess::error);
    QSignalSpy spy_deviceDataReceived(m_atsprocess, &AtsProcess::deviceDataReceived);
    m_atsprocess->onReceiveData(buf, len);
    if(isAcceptedByonReceiveData(test_type)){
        QCOMPARE(spy_deviceDataReceived.count(), 0);
        QCOMPARE(spy_dataReceived.count() + spy_error.count(), 1);
        if(spy_error.count() == 1){
            QList<QVariant> arguments = spy_error.takeFirst();
            QVERIFY(arguments.at(0).toInt() == AtsProcess::EntryInsertError);
        } else {
            QList<QVariant> arguments = spy_dataReceived.takeFirst();
            QVERIFY(arguments.size() == 0);
        }
    } else {
        QCOMPARE(spy_deviceDataReceived.count(), 0);
        QCOMPARE(spy_dataReceived.count(), 0);
        QCOMPARE(spy_error.count(), 1);
        QList<QVariant> arguments = spy_error.takeFirst();
        QVERIFY(arguments.at(0).toInt() == AtsProcess::DataInvalidError);
    }
}

void AtsProcessUnitTest::test_onDeviceDataReceived_data()
{
    quint8* buf_ptr = NULL;
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(ats_vobc_heartbeat);
    testTypes.append(ats_vobc_ato_cmd);
    testTypes.append(ats_ci_heartbeat);
    testTypes.append(ats_ci_cmd);
    testTypes.append(ats_ci_status);
    testTypes.append(ats_zc_heartbeat);
    testTypes.append(ats_zc_tsr_validate);
    testTypes.append(ats_zc_tsr_exec_cmd);
    testTypes.append(ats_zc_tsr_on_confirm);
    testTypes.append(ats_mss_alarm);
    testTypes.append(vobc_mss_alarm);
    testTypes.append(ats_invalid_buf_null);
    testTypes.append(ats_invalid_len_zero);
    testTypes.append(ats_mss_invalid_buf_len_lt_common_header);
    testTypes.append(ats_mss_invalid_buf_len_lt_plus_app_header);
    testTypes.append(vobc_mss_invalid_buf_len_lt_common_header);
    testTypes.append(ats_invalid_buf_len_lg);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("test_type");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++){
        TestDataType test_type = *iter;
        const char* data_str = NULL;
        construct_test_data(test_type, &buf_ptr, &len);
        data_str = (const char*)(*(m_map.find(test_type)));
        QTest::newRow(data_str)<<buf_ptr<<len<<test_type;;
    }
}

void AtsProcessUnitTest::test_onDeviceDataReceived()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, test_type);
    QSignalSpy spy_dataReceived(m_atsprocess, &AtsProcess::dataReceived);
    QSignalSpy spy_error(m_atsprocess, &AtsProcess::error);
    QSignalSpy spy_deviceDataReceived(m_atsprocess, &AtsProcess::deviceDataReceived);
    QSignalSpy spy_vobcDeviceDataReceived(m_atsprocess, &AtsProcess::vobcDeviceDataReceived);
    m_atsprocess->onDeviceDataReceived(buf, len);
    if(isAcceptedByonDeviceDataReceived(test_type)){
        QCOMPARE(spy_dataReceived.count(), 0);
        QCOMPARE(spy_deviceDataReceived.count() + spy_error.count() + spy_vobcDeviceDataReceived.count(), 1);
        if(spy_error.count() == 1){
            QList<QVariant> arguments = spy_error.takeFirst();
            QVERIFY(arguments.at(0).toInt() == AtsProcess::EntryInsertError);
        } else if (spy_deviceDataReceived.count() == 1){
            QList<QVariant> arguments = spy_deviceDataReceived.takeFirst();
            QVERIFY(arguments.size() == 1);
            ats_mss_alarm_t *alarm_info = arguments.at(0).value<ats_mss_alarm_t*>();
            QVERIFY(alarm_info != NULL);
            delete alarm_info;
        } else {
            QList<QVariant> arguments = spy_vobcDeviceDataReceived.takeFirst();
            QVERIFY(arguments.size() == 2);
            quint8 *spy_buf = arguments.at(0).value<quint8*>();
            quint16 spy_len = arguments.at(1).value<quint16>();
            QVERIFY(spy_buf != NULL && spy_buf == buf);
            QVERIFY(spy_len == len);
            delete buf;
        }
    } else {
        QCOMPARE(spy_deviceDataReceived.count(), 0);
        QCOMPARE(spy_dataReceived.count(), 0);
        QCOMPARE(spy_vobcDeviceDataReceived.count(), 0);
        QCOMPARE(spy_error.count(), 1);
        QList<QVariant> arguments = spy_error.takeFirst();
        QVERIFY(arguments.at(0).toInt() == AtsProcess::DataInvalidError);
    }
}

void AtsProcessUnitTest::test_stop()
{
    m_atsprocess->stop();
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(AtsProcessUnitTest)

#include "tst_atsprocess.moc"
