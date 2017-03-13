#include <QString>
#include <QtTest>
#include "vobcdcsservice.h"

#define TEST_BUF_LEN 256
Q_DECLARE_METATYPE(quint8*)

class VobcRilServiceUnitTest : public QObject
{
    Q_OBJECT

public:
    VobcRilServiceUnitTest();
    enum TestDataType{
        correct_data_start,
        vobc_ci = correct_data_start,
        vobc_ats_train,
        vobc_ats_ato,
        vobc_ats_alarm,
        vobc_ats_check,
        vobc_zc_train,
        vobc_zc_register,
        correct_data_end,

        incorrect_data_begin = correct_data_end,
        null_point,
        vobc_ci_invalid_len,
        vobc_ats_train_invalid_len,
        vobc_ats_ato_invalid_len,
        vobc_ats_alarm_invalid_len,
        vobc_ats_check_invalid_len,
        vobc_zc_train_invalid_len,
        vobc_zc_register_invalid_len,
        vobc_zc_register_insert_err,
        incorrect_data_end,


    };

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
#if 0
    void init();
    void cleanup();
#endif
    void test_start();
    void test_HandleRilData();
    void test_HandleRilData_data();
    void test_HandleRilDataInsertErr();
    void test_stop();
private:
    void construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr);
    QMap<TestDataType, const char*> m_map;
    VobcDcsService rilService;
    bool isInvalidData(TestDataType type);
};
Q_DECLARE_METATYPE(VobcRilServiceUnitTest::TestDataType)

VobcRilServiceUnitTest::VobcRilServiceUnitTest()
{
}

void VobcRilServiceUnitTest::initTestCase()
{
    m_map.insert(vobc_ci, "vobc_ci");
    m_map.insert(vobc_ats_train, "vobc_ats_train");
    m_map.insert(vobc_ats_ato, "vobc_ats_ato");
    m_map.insert(vobc_ats_alarm, "vobc_ats_alarm");
    m_map.insert(vobc_ats_check, "vobc_ats_check");
    m_map.insert(vobc_zc_train, "vobc_zc_train");
    m_map.insert(vobc_zc_register, "vobc_zc_register");
    m_map.insert(null_point, "null_point");
    m_map.insert(vobc_ci_invalid_len, "vobc_ci_invalid_len");
    m_map.insert(vobc_ats_train_invalid_len, "vobc_ats_train_invalid_len");
    m_map.insert(vobc_ats_ato_invalid_len, "vobc_ats_ato_invalid_len");
    m_map.insert(vobc_ats_alarm_invalid_len, "vobc_ats_alarm_invalid_len");
    m_map.insert(vobc_ats_check_invalid_len, "vobc_ats_check_invalid_len");
    m_map.insert(vobc_zc_train_invalid_len, "vobc_zc_train_invalid_len");
    m_map.insert(vobc_zc_register_invalid_len, "vobc_zc_register_invalid_len");
    m_map.insert(vobc_zc_register_insert_err, "vobc_zc_register_insert_err");
}

void VobcRilServiceUnitTest::cleanupTestCase()
{
}

void VobcRilServiceUnitTest::test_start()
{
    QSignalSpy spy_error(&rilService, &VobcDcsService::castError);
    rilService.startService();
    QCOMPARE(spy_error.count(), 0);
}

bool VobcRilServiceUnitTest::isInvalidData(TestDataType type)
{
    if(type > incorrect_data_begin && type < incorrect_data_end){
        return true;
    } else {
        return false;
    }
}

void VobcRilServiceUnitTest::construct_test_data(TestDataType type, quint8** buf_ptr, quint16* len_ptr)
{
    quint8* buf = NULL;
    buf = new quint8[TEST_BUF_LEN];
    vobc_ats_header_t s;
    quint16 sizebuf, pad_len = 0;
    *buf_ptr = buf;
    switch (type) {
    case vobc_ci:
    case vobc_ci_invalid_len:
    {
        s.vobc_ats_interface = 0x9008;
        s.send_id_msg = qrand()%0xFFFFFFFF;
        s.incept_id_msg = qrand()%0xFFFFFFFF;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        mss_vobc_ci_t data;
        data.nc_data = 0x01;
        data.dir_train = qrand()%0xFF;
        data.s_trainstoparea = qrand()%0xFF;
        data.n_psd_type = qrand()%0xFF;
        data.n_psd = qrand()%0xFF;
        data.nid_psd_1 = qrand()%0xFFFF;
        data.nc_psd_1 = qrand()%0xFF;
        data.nid_psd_2 = qrand()%0xFFFF;
        data.nc_psd_2 = qrand()%0xFF;
        pad_len = b2v_var_to_bytes_byoffset((quint8 *)&data, buf, sizebuf, vobc_ci_cv_table, vobc_ci_cv_table_len);

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = pad_len +1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
        break;
    }
    case vobc_ats_train:
    case vobc_ats_train_invalid_len:
    {
        s.vobc_ats_interface = ATS_VOBC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ATS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_ats_trainmsg_t data;
        data.msg_type = 0x0204;
        data.train_id = qrand()%0xFFFF;
        data.line_id = qrand()%0xFFFF;
        data.status_train_pos = qrand()%0xFF;
        data.dir_train = qrand()%0xFF;
        data.dir_whell = qrand()%0xFF;
        data.head_estimate_logic_id = qrand()%0xFFFF;
        data.head_estimate_offset = qrand()%0xFFFFFFFF;
        data.tail_estimate_logic_id = qrand()%0xFFFF;
        data.tail_estimate_offset = qrand()%0xFFFFFFFF;
        data.over_read = qrand()%0xFFFF;
        data.lack_read = qrand()%0xFFFF;
        data.mode_atp = qrand()%0xFF;
        data.mode_cbtc = qrand()%0xFF;
        data.status_train_complete = qrand()%0xFF;
        data.status_emerg_brake = qrand()%0xFF;
        data.status_ar = qrand()%0xFF;
        data.vel_msg = qrand()%0xFFFF;
        data.status_psd = qrand()%0xFF;
        data.status_trainstoparea = qrand()%0xFF;
        data.status_stoptrain = qrand()%0xFF;
        data.status_unmanned_reentry = qrand()%0xFF;
        data.mode_preselect = qrand()%0xFF;
        data.reasonof_emerg_brake = qrand()%0xFF;
        data.vel_emerg_brake = qrand()%0xFFFF;
        data.vel_recommend = qrand()%0xFFFF;
        data.pos_security = qrand()%0xFFFFFFFF;
        data.sec_track_id = qrand()%0xFFFF;
        data.sec_track_offset = qrand()%0xFFFFFFFF;
        data.pos_obstacle = qrand()%0xFFFFFFFF;
        data.obs_track_id = qrand()%0xFFFF;
        data.obs_track_offset = qrand()%0xFFFFFFFF;
        data.reserved_field = qrand()%0xFFFFFFFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&data, buf + sizebuf + 2, vobc_ats_train_cv_table, vobc_ats_train_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = pad_len - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }

        break;
    }
    case vobc_ats_ato:
    case vobc_ats_ato_invalid_len:
    {
        s.vobc_ats_interface = ATS_VOBC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_MSS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;

        //convert struct to bytes
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_ats_ato_t sAto;
        sAto.msg_type = 0x0202;
        sAto.service_id = qrand()%0xFFFF;
        sAto.line_id = qrand()%0xFFFF;
        sAto.cargroup_line_id = qrand()%0xFFFF;
        sAto.cargroup_id = qrand()%0xFFFF;
        sAto.sourceline_id = qrand()%0xFFFF;
        sAto.trainnum_id = qrand()%0xFFFF;
        sAto.destination_track_id = qrand()%0xFFFF;
        sAto.destination_id = qrand()%0xFFFFFFFF;
        sAto.driver_id = qrand()%0xFFFF;
        sAto.mode_ato = qrand()%0xFF;
        sAto.nc_interval_operation = qrand()%0xFFFF;
        sAto.status_skipstop = qrand()%0xFF;
        sAto.status_detain = qrand()%0xFF;
        sAto.nextstation_id =qrand()%0xFFFF;
        sAto.reserved_field = qrand()%0xFFFFFFFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&sAto, buf+sizebuf +2, vobc_ats_ato_cv_table, vobc_ats_ato_cv_table_len);
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
    case vobc_ats_alarm:
    case vobc_ats_alarm_invalid_len:
    {
        s.vobc_ats_interface = ATS_VOBC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ATS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_ats_alarmmsg_t data;
        data.msg_type = 0x0206;
        data.train_id = qrand()%0xFFFF;
        data.alarm_ato = qrand()%0xFF;
        data.alarm_btm = qrand()%0xFF;
        data.alarm_vel_ui = qrand()%0xFF;
        data.alarm_radar = qrand()%0xFF;
        data.alarm_train_com = qrand()%0xFF;
        data.alarm_speed_measure = qrand()%0xFF;
        data.alarm_acceleration_measure = qrand()%0xFF;
        data.alarm_reserved1 = qrand()%0xFF;
        data.alarm_reserved2 = qrand()%0xFF;
        data.alarm_atp = qrand()%0xFF;
        data.board_info1 = qrand()%0xFF;
        data.board_info2 = qrand()%0xFF;
        data.board_info3 = qrand()%0xFF;
        data.board_info4 = qrand()%0xFF;
        data.board_info5 = qrand()%0xFF;
        data.board_info6 = qrand()%0xFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&data, buf + sizebuf + 2, vobc_ats_alarmmsg_cv_table, vobc_ats_alarmmsg_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = sizebuf;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
        break;
    }
    case vobc_ats_check:
    case vobc_ats_check_invalid_len:
    {
        s.vobc_ats_interface = ATS_VOBC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ATS;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_ats_check_t data;
        data.msg_type = 0x0208;
        data.traid_id = qrand()%0xFFFF;
        data.status_check1 = qrand()%0xFF;
        data.status_check2 = qrand()%0xFF;
        data.status_check3 = qrand()%0xFF;
        data.status_check4 = qrand()%0xFF;
        data.status_check5 = qrand()%0xFF;
        data.status_check6 = qrand()%0xFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&data, buf + sizebuf + 2, vobc_ats_check_cv_table, vobc_ats_check_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = sizebuf + 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }

        break;
    }
    case vobc_zc_train:
    case vobc_zc_train_invalid_len:
    {
        s.vobc_ats_interface = VOBC_ZC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ZC;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_zc_trainmsg_t data;
        data.msg_type = 0x0202;
        data.dir = qrand()%0xFF;
        data.active_side = qrand()%0xFF;
        data.head_estimate_logic_id = qrand()%0xFFFF;
        data.head_estimate_offset = qrand()%0xFFFFFFFF;
        data.tail_estimate_logic_id = qrand()%0xFFFF;
        data.tail_estimate_offset = qrand()%0xFFFFFFFF;
        data.lack_read = qrand()%0xFFFF;
        data.over_read = qrand()%0xFFFF;
        data.train_length = qrand()%0xFFFF;
        data.wheel_head_length = qrand()%0xFFFF;
        data.op_mode = qrand()%0xFF;
        data.drive_mode = qrand()%0xFF;
        data.stop_response = qrand()%0xFF;
        data.stop_area = qrand()%0xFFFF;
        data.stop_area_offset = qrand()%0xFFFFFFFF;
        data.stop_pos_obstacle = qrand()%0xFFFF;
        data.stop_pos_obs_offset = qrand()%0xFFFFFFFF;
        data.stop_valid = qrand()%0xFF;
        data.status_reentry = qrand()%0xFF;
        data.status_train_complete = qrand()%0xFF;
        data.led_unmanned_reentry = qrand()%0xFF;
        data.status_emerg_brake = qrand()%0xFF;
        data.train_speed = qrand()%0xFFFF;
        data.speed_dir = qrand()%0xFF;
        data.recess_length = qrand()%0xFFFF;
        data.status_trainstoparea = qrand()%0xFF;
        data.ctl_zcid = qrand()%0xFFFFFFFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&data, buf + sizebuf +2, vobc_zc_train_cv_table, vobc_zc_train_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = sizebuf - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
        break;
    }
    case vobc_zc_register:
    case vobc_zc_register_invalid_len:
    {
        s.vobc_ats_interface = VOBC_ZC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ZC;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_zc_register_t data;
        data.msg_type = 0x0206;
        data.register_mode = qrand()%0xFF;
        data.log_out_reason = qrand()%0xFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&data, buf + sizebuf + 2, vobc_zc_register_cv_table, vobc_zc_register_cv_table_len);
        b2v_var_to_bytes((quint8 *)&app_header_len, buf + sizebuf, vobc_msg_len_cv_table, vobc_msg_len_cv_table_len);
        pad_len = sizebuf + app_header_len.v_msg_len +2;

        if(isInvalidData(type)){
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = ((quint16)rand()) % pad_len;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            pad_len = len_for_invalid;
            *buf_ptr = buf_for_invalid;
            delete[] buf;
        }
        break;
    }
    case vobc_zc_register_insert_err:
    {
        s.vobc_ats_interface = VOBC_ZC_INTERFACE;
        s.send_id_msg = ID_MESSAGE_VOBC;
        s.incept_id_msg = ID_MESSAGE_ZC;
        s.edition_check_msg = qrand()%0xFF;
        s.edition_control_msg = qrand()%0xFFFFFFFF;
        s.msg_list = qrand()%0xFFFFFFFF;
        s.com_cycle = qrand()%0xFF;
        s.opposite_msg_list = qrand()%0xFFFFFFFF;
        s.smsg_self_list = qrand()%0xFFFFFFFF;
        s.pro_edition = qrand()%0xFF;
        sizebuf = b2v_var_to_bytes((quint8 *)&s, buf, vobc_common_header_cv_table, vobc_common_header_cv_table_len);

        vobc_zc_register_t data;
        data.msg_type = 0x0206;
        data.register_mode = qrand()%0xFF;
        data.log_out_reason = qrand()%0xFF;

        vobc_app_header_len_t app_header_len;
        app_header_len.v_msg_len = b2v_var_to_bytes((quint8 *)&data, buf + sizebuf + 2, vobc_zc_register_cv_table, vobc_zc_register_cv_table_len);
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
    {
        pad_len = TEST_BUF_LEN;
        break;
    }
    }
    *len_ptr = pad_len;
}
void VobcRilServiceUnitTest::test_HandleRilData_data()
{
    quint8 * buf_ptr = NULL;
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(vobc_ci);
    testTypes.append(vobc_ats_train);
    testTypes.append(vobc_ats_ato);
    testTypes.append(vobc_ats_alarm);
    testTypes.append(vobc_ats_check);
    testTypes.append(vobc_zc_train);
    testTypes.append(vobc_zc_register);
    testTypes.append(vobc_ci_invalid_len);
    testTypes.append(vobc_ats_train_invalid_len);
    testTypes.append(vobc_ats_ato_invalid_len);
    testTypes.append(vobc_ats_alarm_invalid_len);
    testTypes.append(vobc_ats_check_invalid_len);
    testTypes.append(vobc_zc_train_invalid_len);
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

void VobcRilServiceUnitTest::test_HandleRilData()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, test_type);
    QSignalSpy spy_error(&rilService, &VobcDcsService::castError);
    rilService.handleDcsData(buf,len);
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
void VobcRilServiceUnitTest::test_HandleRilDataInsertErr()
{
    quint8 * buf_ptr = NULL;
    quint16 len = 0;
    construct_test_data(vobc_zc_register_insert_err, &buf_ptr, &len);
    QSignalSpy spy_error(&rilService, &VobcDcsService::castError);
    rilService.stopService();
    rilService.handleDcsData(buf_ptr,len);
    QCOMPARE(spy_error.count(), 1);
    if(spy_error.count() == 1){
        QList<QVariant> arguments = spy_error.takeFirst();
        int err = arguments.at(0).toInt();
        QVERIFY(err == ErrInsertTable);
    }
}

void VobcRilServiceUnitTest::test_stop()
{
    rilService.stopService();
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VobcRilServiceUnitTest)

#include "tst_vobcrilserviceut.moc"
