#include <QString>
#include <QtTest>
#include <QObject>
#include <QtWidgets>
#include "zcdatathread.h"
#include <QPushButton>
#include "mssdbconfig.h"

Q_DECLARE_METATYPE(quint8*)

#define TEST_BUF_LEN 512
class ZcTest : public QObject
{
    Q_OBJECT

public:
    ZcTest();
    enum TestDataType
    {
        zc_receiveData_start = 1,
        zc_ci_ls,
        zc_ci_sp,
        zc_ci_pslr,
        zc_ats_tvc,
        zc_ats_tec,
        zc_ats_ts,
        zc_vobc_tc,
        zc_vobc_arlr,
        zc_vobc_alr,
        zc_vobc_scm,
        zc_receiveData_end,
        zc_receiveAlarmData_start = zc_receiveData_end,
        zc_monitor,
        zc_receiveAlarmData_end,
        zc_invalid_start = zc_receiveAlarmData_end,
        zc_invalid_buf_null,
        zc_invalid_len_zero,
        zc_invalid_buf_len_lt_header,
        zc_monitor_invalid_buf_len_lt_data,
        zc_monitor_invalid_buf_len_bg_data,
        zc_ci_ls_invalid_buf_len_lt_header_add_data,
        zc_ci_sp_invalid_buf_len_lt_header_add_data,
        zc_ci_pslr_invalid_buf_len_lt_header_add_data,
        zc_ats_tvc_invalid_buf_len_lt_header_add_data,
        zc_ats_tec_invalid_buf_len_lt_header_add_data,
        zc_ats_ts_invalid_buf_len_lt_header_add_data,
        zc_vobc_tc_invalid_buf_len_lt_header_add_data,
        zc_vobc_arlr_invalid_buf_len_lt_header_add_data,
        zc_vobc_alr_invalid_buf_len_lt_header_add_data,
        zc_vobc_scm_invalid_buf_len_lt_header_add_data,
        zc_ci_ls_invalid_buf_len_bg_header_add_data,
        zc_ci_sp_invalid_buf_len_bg_header_add_data,
        zc_ci_pslr_invalid_buf_len_bg_header_add_data,
        zc_ats_tvc_invalid_buf_len_bg_header_add_data,
        zc_ats_tec_invalid_buf_len_bg_header_add_data,
        zc_ats_ts_invalid_buf_len_bg_header_add_data,
        zc_vobc_tc_invalid_buf_len_bg_header_add_data,
        zc_vobc_arlr_invalid_buf_len_bg_header_add_data,
        zc_vobc_alr_invalid_buf_len_bg_header_add_data,
        zc_vobc_scm_invalid_buf_len_bg_header_add_data,
        zc_unknown_interface,
        zc_ci_unknown_msg,
        zc_ats_unknown_msg,
        zc_vobc_unknown_msg,
        zc_invalid_end
    };
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testOpenDB();
    void testCreateTB();
    void testStart();
    void testSendUiZcCiLs();
    void testInsertData();
    void testDealZcCi_data();
    void testDealZcCi();
    void testDealZcAts_data();
    void testDealZcAts();
    void testDealZcVobc_data();
    void testDealZcVobc();
    void testReceiveData_data();
    void testReceiveData();
    void testReceiveAlarmData_data();
    void testReceiveAlarmData();
private:
    ZcDataThread *zcDataThreadTest;
    QMap<TestDataType, const char*> zcMap;
    QUdpSocket *testZcUdpSocket;
private:
    void constructTestData(TestDataType type, quint8** bufPtr, quint16* lenPtr);
    bool isAcceptedByonReceiveData(TestDataType type);
    bool isAcceptedByonReceiveData2(TestDataType type);
    bool isInvalidData(TestDataType type);
};
Q_DECLARE_METATYPE(ZcTest::TestDataType)
ZcTest::ZcTest()
{
    zcDataThreadTest = NULL;
}
void ZcTest::initTestCase()
{
    zcDataThreadTest = new ZcDataThread("zcdbtest");
    testZcUdpSocket = new QUdpSocket(this);

    zcMap.insert(zc_ci_ls, "zc_ci_ls");
    zcMap.insert(zc_ci_sp, "zc_ci_sp");
    zcMap.insert(zc_ci_pslr, "zc_ci_pslr");
    zcMap.insert(zc_ats_tvc, "zc_ats_tvc");
    zcMap.insert(zc_ats_tec, "zc_ats_tec");
    zcMap.insert(zc_ats_ts, "zc_ats_ts");
    zcMap.insert(zc_vobc_tc, "zc_vobc_tc");
    zcMap.insert(zc_vobc_arlr, "zc_vobc_arlr");
    zcMap.insert(zc_vobc_alr, "zc_vobc_alr");
    zcMap.insert(zc_vobc_scm, "zc_vobc_scm");
    zcMap.insert(zc_monitor, "zc_monitor");
    zcMap.insert(zc_invalid_buf_null, "zc_invalid_buf_null null");
    zcMap.insert(zc_invalid_len_zero, "zc_invalid_len_zero len zero");
    zcMap.insert(zc_invalid_buf_len_lt_header, "zc_invalid_buf len < len(header)");
    zcMap.insert(zc_monitor_invalid_buf_len_lt_data, "zc_monitor_invalid_buf len < len(data)");
    zcMap.insert(zc_monitor_invalid_buf_len_bg_data, "zc_monitor_invalid_buf len > len(data)");
    zcMap.insert(zc_ci_ls_invalid_buf_len_lt_header_add_data, "zc_ci_ls_invalid_buf len < len(header+data)");
    zcMap.insert(zc_ci_sp_invalid_buf_len_lt_header_add_data, "zc_ci_sp_invalid_buf len < len(header+data)");
    zcMap.insert(zc_ci_pslr_invalid_buf_len_lt_header_add_data, "zc_ci_pslr_invalid_buf len < len(header+data)");
    zcMap.insert(zc_ats_tvc_invalid_buf_len_lt_header_add_data, "zc_ats_tvc_invalid_buf len < len(header+data)");
    zcMap.insert(zc_ats_tec_invalid_buf_len_lt_header_add_data, "zc_ats_tec_invalid_buf len < len(header+data)");
    zcMap.insert(zc_ats_ts_invalid_buf_len_lt_header_add_data, "zc_ats_ts_invalid_buf len < len(header+data)");
    zcMap.insert(zc_vobc_tc_invalid_buf_len_lt_header_add_data, "zc_vobc_tc_invalid_buf len < len(header+data)");
    zcMap.insert(zc_vobc_arlr_invalid_buf_len_lt_header_add_data, "zc_vobc_arlr_invalid_buf len < len(header+data)");
    zcMap.insert(zc_vobc_alr_invalid_buf_len_lt_header_add_data, "zc_vobc_alr_invalid_buf len < len(header+data)");
    zcMap.insert(zc_vobc_scm_invalid_buf_len_lt_header_add_data, "zc_vobc_scm_invalid_buf len < len(header+data)");
    zcMap.insert(zc_ci_ls_invalid_buf_len_bg_header_add_data, "zc_ci_ls_invalid_buf len > len(header+data)");
    zcMap.insert(zc_ci_sp_invalid_buf_len_bg_header_add_data, "zc_ci_sp_invalid_buf len > len(header+data)");
    zcMap.insert(zc_ci_pslr_invalid_buf_len_bg_header_add_data, "zc_ci_pslr_invalid_buf len > len(header+data)");
    zcMap.insert(zc_ats_tvc_invalid_buf_len_bg_header_add_data, "zc_ats_tvc_invalid_buf len > len(header+data)");
    zcMap.insert(zc_ats_tec_invalid_buf_len_bg_header_add_data, "zc_ats_tec_invalid_buf len > len(header+data)");
    zcMap.insert(zc_ats_ts_invalid_buf_len_bg_header_add_data, "zc_ats_ts_invalid_buf len > len(header+data)");
    zcMap.insert(zc_vobc_tc_invalid_buf_len_bg_header_add_data, "zc_vobc_tc_invalid_buf len > len(header+data)");
    zcMap.insert(zc_vobc_arlr_invalid_buf_len_bg_header_add_data, "zc_vobc_arlr_invalid_buf len > len(header+data)");
    zcMap.insert(zc_vobc_alr_invalid_buf_len_bg_header_add_data, "zc_vobc_alr_invalid_buf len > len(header+data)");
    zcMap.insert(zc_vobc_scm_invalid_buf_len_bg_header_add_data, "zc_vobc_scm_invalid_buf len > len(header+data)");
    zcMap.insert(zc_unknown_interface, "zc_unknown_interface");
    zcMap.insert(zc_ci_unknown_msg, "zc_ci_unknown_msg");
    zcMap.insert(zc_ats_unknown_msg, "zc_ats_unknown_msg");
    zcMap.insert(zc_vobc_unknown_msg, "zc_vobc_unknown_msg");

    qRegisterMetaType<stream_head_info_t>("stream_head_info_t*");

    QVERIFY(zcDataThreadTest != NULL);
}
void ZcTest::cleanupTestCase()
{
    if(zcDataThreadTest != NULL){
        delete zcDataThreadTest;
        zcDataThreadTest = NULL;
    }

}
bool ZcTest::isAcceptedByonReceiveData(TestDataType type)
{
    if(type > zc_receiveData_start && type < zc_receiveData_end){
        return true;
    } else {
        return false;
    }
}

bool ZcTest::isAcceptedByonReceiveData2(TestDataType type)
{
    if(type > zc_receiveAlarmData_start && type < zc_receiveAlarmData_end){
        return true;
    } else {
        return false;
    }
}

bool ZcTest::isInvalidData(TestDataType type)
{
    if(type > zc_invalid_start && type < zc_invalid_end){
        return true;
    } else {
        return false;
    }
}
void ZcTest::constructTestData(TestDataType type, quint8** bufPtr, quint16* lenPtr)
{
    quint8* buf = NULL;
    quint16 padLen = 0;
    quint16 offset = 0;
    quint16 app_header_offset = 0;
    buf = new quint8[TEST_BUF_LEN];
    *bufPtr = buf;
    switch(type)
    {
    case zc_unknown_interface:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = 0x8002;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_VOBC;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
    }
        break;
    case zc_invalid_buf_len_lt_header:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ZC_CI_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_VOBC;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;

        quint8* buf_for_invalid = NULL;
        quint16 len_for_invalid = 0;
        len_for_invalid = padLen - 1;
        buf_for_invalid = new quint8[len_for_invalid];
        memcpy(buf_for_invalid, buf, len_for_invalid);
        padLen = len_for_invalid;
        *bufPtr = buf_for_invalid;
        delete[] buf;
    }
        break;
    case zc_ci_ls:
    case zc_ci_ls_invalid_buf_len_lt_header_add_data:
    case zc_ci_ls_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ZC_CI_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_CI;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        ci_header_info_t m_ci_header_info_t;
        m_ci_header_info_t.c_msg_len = 0;
        m_ci_header_info_t.c_msg_type = LOGIC_ZONE_STATUS;
        m_ci_header_info_t.c_msg_num = 5;
        offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + padLen, ci_header_destbl_table, ci_header_destbl_table_len);
        padLen += offset;
        logic_track_info_t m_logic_track_info_t;
        for(int i=0;i<m_ci_header_info_t.c_msg_num*0.5;i++)
        {
            quint8 temp = 0;
            temp = temp|0x01;
            if((i*2+1) < m_ci_header_info_t.c_msg_num )temp = temp|0xa0;
            m_logic_track_info_t.l_status = temp;
            offset = b2v_var_to_bytes((quint8 *)&m_logic_track_info_t, buf + padLen, logicTrack_destbl_table, logicTrack_destbl_table_len);
            padLen += offset;
        }
        m_ci_header_info_t.c_msg_len = padLen - app_header_offset - 2;
        offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + app_header_offset, ci_header_destbl_table, ci_header_destbl_table_len);
        if(type == zc_ci_ls_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_ci_ls_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_ci_sp:
    case zc_ci_sp_invalid_buf_len_lt_header_add_data:
    case zc_ci_sp_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ZC_CI_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_CI;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        ci_header_info_t m_ci_header_info_t;
        m_ci_header_info_t.c_msg_len = 0;
        m_ci_header_info_t.c_msg_type = SIGNAL_NEAR_INFO;
        m_ci_header_info_t.c_msg_num = 5;
        offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + padLen, ci_header_destbl_table, ci_header_destbl_table_len);
        padLen += offset;
        signal_close_info_t m_signal_close_info_t;
        for(int i=0;i<m_ci_header_info_t.c_msg_num;i++)
        {
            m_signal_close_info_t.s_status = 0xff;
            offset = b2v_var_to_bytes((quint8 *)&m_signal_close_info_t, buf + padLen, signalClose_destbl_table, signalClose_destbl_table_len);
            padLen += offset;
        }
        m_ci_header_info_t.c_msg_len = padLen - app_header_offset - 2;
        offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + app_header_offset, ci_header_destbl_table, ci_header_destbl_table_len);
        if(type == zc_ci_sp_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_ci_sp_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_ci_pslr:
    case zc_ci_pslr_invalid_buf_len_lt_header_add_data:
    case zc_ci_pslr_invalid_buf_len_bg_header_add_data:
    case zc_ci_unknown_msg:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ZC_CI_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_CI;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        ci_header_info_t m_ci_header_info_t;
        m_ci_header_info_t.c_msg_len = 0;
        m_ci_header_info_t.c_msg_type = PROTECT_ZONE_LOCK_ASK;
        if(type == zc_ci_unknown_msg)
        {
            m_ci_header_info_t.c_msg_type = 0x0200;
        }
        m_ci_header_info_t.c_msg_num = 1;
        offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + padLen, ci_header_destbl_table, ci_header_destbl_table_len);
        padLen += offset;
        protect_zone_lock_rsq_t m_protect_zone_lock_rsq_t;
        //for(int i=0;i<m_ci_header_info_t.c_msg_num;i++)
        //{
            m_protect_zone_lock_rsq_t.p_seri = 0xf0f0;
            offset = b2v_var_to_bytes((quint8 *)&m_protect_zone_lock_rsq_t, buf + padLen, routeUnlockRsq_destbl_table, routeUnlockRsq_destbl_table_len);
            padLen += offset;
        //}
        m_ci_header_info_t.c_msg_len = padLen - app_header_offset - 2;
        offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + app_header_offset, ci_header_destbl_table, ci_header_destbl_table_len);
        if(type == zc_ci_pslr_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_ci_pslr_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_ats_tvc:
    case zc_ats_tvc_invalid_buf_len_lt_header_add_data:
    case zc_ats_tvc_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ATS_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_ATS;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        ats_header_info_t m_ats_header_info_t;
        m_ats_header_info_t.a_msg_len = 9;
        m_ats_header_info_t.a_msg_type = ZC_TSR_VERIFY_FRAME;
        offset = b2v_var_to_bytes((quint8 *)&m_ats_header_info_t, buf + padLen, ats_header_destbl_table, ats_header_destbl_table_len);
        padLen += offset;
        zc_tsr_verify_frame_1_t m_zc_tsr_verify_frame_1_t;
        m_zc_tsr_verify_frame_1_t.z_verify_outcome = 0x55;
        m_zc_tsr_verify_frame_1_t.z_faile_reason = 0xff;
        m_zc_tsr_verify_frame_1_t.z_temp_rate_limit = 0xff;
        m_zc_tsr_verify_frame_1_t.z_logic_tracknum = 0x0f0f;
        offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_verify_frame_1_t, buf + padLen, zc_tsr_verify_frame_1_destbl_table, zc_tsr_verify_frame_1_destbl_table_len);
        padLen += offset;
        zc_tsr_verify_frame_2_t m_zc_tsr_verify_frame_2_t;
        m_zc_tsr_verify_frame_2_t.z_logic_track_id = 0x5500;
        offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_verify_frame_2_t, buf + padLen, zc_tsr_verify_frame_2_destbl_table, zc_tsr_verify_frame_2_destbl_table_len);
        padLen += offset;
        if(type == zc_ats_tvc_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_ats_tvc_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_ats_tec:
    case zc_ats_tec_invalid_buf_len_lt_header_add_data:
    case zc_ats_tec_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ATS_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_ATS;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        ats_header_info_t m_ats_header_info_t;
        m_ats_header_info_t.a_msg_len = 9;
        m_ats_header_info_t.a_msg_type = ZC_TSR_EXEUTE_FRAME;
        offset = b2v_var_to_bytes((quint8 *)&m_ats_header_info_t, buf + padLen, ats_header_destbl_table, ats_header_destbl_table_len);
        padLen += offset;
        zc_tsr_exeute_frame_1_t m_zc_tsr_exeute_frame_1_t;
        m_zc_tsr_exeute_frame_1_t.z_verify_outcome = 0x55;
        m_zc_tsr_exeute_frame_1_t.z_alarm_info = 0xff;
        m_zc_tsr_exeute_frame_1_t.z_temp_rate_limit = 0xff;
        m_zc_tsr_exeute_frame_1_t.z_logic_tracknum = 0x0f0f;
        offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_exeute_frame_1_t, buf + padLen, zc_tsr_exeute_frame_1_destbl_table, zc_tsr_exeute_frame_1_destbl_table_len);
        padLen += offset;
        zc_tsr_exeute_frame_2_t m_zc_tsr_exeute_frame_2_t;
        m_zc_tsr_exeute_frame_2_t.z_logic_track_id = 0x5500;
        offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_exeute_frame_2_t, buf + padLen, zc_tsr_exeute_frame_2_destbl_table, zc_tsr_exeute_frame_2_destbl_table_len);
        padLen += offset;
        if(type == zc_ats_tec_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_ats_tec_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_ats_ts:
    case zc_ats_ts_invalid_buf_len_lt_header_add_data:
    case zc_ats_ts_invalid_buf_len_bg_header_add_data:
    case zc_ats_unknown_msg:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = ATS_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_ATS;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        ats_header_info_t m_ats_header_info_t;
        m_ats_header_info_t.a_msg_len = 7;
        m_ats_header_info_t.a_msg_type = ZC_STATUS_INFO_FRAME;
        if(type == zc_ats_unknown_msg)
        {
            m_ats_header_info_t.a_msg_type = 0x0200;
        }
        offset = b2v_var_to_bytes((quint8 *)&m_ats_header_info_t, buf + padLen, ats_header_destbl_table, ats_header_destbl_table_len);
        padLen += offset;
        zc_status_frame_1_t m_zc_status_frame_1_t;
        m_zc_status_frame_1_t.z_power_on_rsq = 0x55;
        m_zc_status_frame_1_t.z_logic_tracknum = 0x0f0f;
        offset = b2v_var_to_bytes((quint8 *)&m_zc_status_frame_1_t, buf + padLen, zc_status_frame_1_destbl_table, zc_status_frame_1_destbl_table_len);
        padLen += offset;
        zc_status_frame_2_t m_zc_status_frame_2_t;
        m_zc_status_frame_2_t.z_temp_rate_limit = 0x5500;
        offset = b2v_var_to_bytes((quint8 *)&m_zc_status_frame_2_t, buf + padLen, zc_status_frame_2_destbl_table, zc_status_frame_2_destbl_table_len);
        padLen += offset;
        if(type == zc_ats_ts_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_ats_ts_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_vobc_tc:
    case zc_vobc_tc_invalid_buf_len_lt_header_add_data:
    case zc_vobc_tc_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = VOBC_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_VOBC;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        vobc_header_info_t m_vobc_header_info_t;
        m_vobc_header_info_t.v_msg_len = 0;
        m_vobc_header_info_t.v_msg_type = ZC_CONTROLTRAIN;
        offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + padLen, vobc_header_destbl_table, vobc_header_destbl_table_len);
        padLen += offset;
        onboard_control_info_t m_onboard_control_info_t;
        m_onboard_control_info_t.next_zc_id = 0x00010001;
        m_onboard_control_info_t.ma_info_len = 0x1111;
        m_onboard_control_info_t.ma_dir = 0x01;
        m_onboard_control_info_t.stop_response = 0xff;

        m_onboard_control_info_t.stop_response_tk_id = 0x4554;
        m_onboard_control_info_t.stop_response_tk_offset = 0x44554556;
        m_onboard_control_info_t.stop_response_obstacles_tk_id = 0x4444;
        m_onboard_control_info_t.stop_response_obstacles_tk_offset = 0xfffffff0;
        m_onboard_control_info_t.stop_response_overlap = 0xff;

        m_onboard_control_info_t.ma_start_zone_id = 0xffff;
        m_onboard_control_info_t.ma_start_zone_offset = 0xffffffff;
        m_onboard_control_info_t.tk_id = 0xccff;
        m_onboard_control_info_t.tk_offset = 0xffffffff;
        m_onboard_control_info_t.obstacles_tk_id = 0xffff;

        m_onboard_control_info_t.obstacles_tk_offset = 0xffffffff;
        m_onboard_control_info_t.overlap_valid = 0xff;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, onboard_control_1_destbl_table, onboard_control_1_destbl_table_len);
        padLen += offset;

        m_onboard_control_info_t.switch_num = 2;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, switch_num_destbl_table, switch_num_destbl_table_len);
        padLen += offset;
        switch_status_t m_switch_status_t;
        for(int i = 0; i<m_onboard_control_info_t.switch_num; i++)
        {
            m_switch_status_t.switch_id = i;
            m_switch_status_t.switch_statu = i;
            offset = b2v_var_to_bytes((quint8 *)&m_switch_status_t, buf + padLen, switch_status_destbl_table, switch_status_destbl_table_len);
            padLen += offset;
        }

        m_onboard_control_info_t.psd_num = 2;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, psd_num_destbl_table, psd_num_destbl_table_len);
        padLen += offset;
        PSD_status_t m_PSD_status_t;
        for(int i = 0; i<m_onboard_control_info_t.psd_num; i++)
        {
            m_PSD_status_t.psd_id = i;
            m_PSD_status_t.psd_status = i;
            offset = b2v_var_to_bytes((quint8 *)&m_PSD_status_t, buf + padLen, psd_status_destbl_table, psd_status_destbl_table_len);
            padLen += offset;
        }

        m_onboard_control_info_t.esb_num = 2;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, esb_num_destbl_table, esb_num_destbl_table_len);
        padLen += offset;
        ESB_status_t m_ESB_status_t;
        for(int i = 0; i<m_onboard_control_info_t.esb_num; i++)
        {
            m_ESB_status_t.esb_id = i;
            m_ESB_status_t.esb_status = i;
            offset = b2v_var_to_bytes((quint8 *)&m_ESB_status_t, buf + padLen, esb_status_destbl_table, esb_status_destbl_table_len);
            padLen += offset;
        }

        m_onboard_control_info_t.auto_back_button_status = 0x55;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, onboard_control_2_destbl_table, onboard_control_2_destbl_table_len);
        padLen += offset;

        m_onboard_control_info_t.temp_speed_limit_num = 2;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, temp_speed_num_destbl_table, temp_speed_num_destbl_table_len);
        padLen += offset;
        temp_speed_limit_info_t m_temp_speed_limit_info_t;
        for(int i = 0; i<m_onboard_control_info_t.temp_speed_limit_num; i++)
        {
            m_temp_speed_limit_info_t.start_zone_id = i;
            m_temp_speed_limit_info_t.start_zone_offset = 0xffffffff;
            m_temp_speed_limit_info_t.end_zone_id = i;
            m_temp_speed_limit_info_t.end_zone_offset = 0xffffffff;
            m_temp_speed_limit_info_t.reserv = 0xff;
            m_temp_speed_limit_info_t.speed_limit_value = 0x55;
            offset = b2v_var_to_bytes((quint8 *)&m_temp_speed_limit_info_t, buf + padLen, temp_speed_status_destbl_table, temp_speed_status_destbl_table_len);
            padLen += offset;
        }

        m_onboard_control_info_t.destination_status = 0x55;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + padLen, onboard_control_3_destbl_table, onboard_control_3_destbl_table_len);
        padLen += offset;

        m_vobc_header_info_t.v_msg_len = padLen - app_header_offset - 2;
        offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + app_header_offset, vobc_header_destbl_table, vobc_header_destbl_table_len);
        if(type == zc_vobc_tc_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_vobc_tc_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_vobc_arlr:
    case zc_vobc_arlr_invalid_buf_len_lt_header_add_data:
    case zc_vobc_arlr_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = VOBC_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_VOBC;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        vobc_header_info_t m_vobc_header_info_t;
        m_vobc_header_info_t.v_msg_len = 6;
        m_vobc_header_info_t.v_msg_type = ZC_RESPOND_RSQ;
        offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + padLen, vobc_header_destbl_table, vobc_header_destbl_table_len);
        padLen += offset;
        onboard_request_respond_t m_onboard_request_respond_t;
        m_onboard_request_respond_t.request_return = 0x55;
        m_onboard_request_respond_t.unregister_reason = 0xff;
        m_onboard_request_respond_t.reserv = 0xffff;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_request_respond_t, buf + padLen, onboard_request_respond_destbl_table, onboard_request_respond_destbl_table_len);
        padLen += offset;
        if(type == zc_vobc_arlr_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_vobc_arlr_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_vobc_alr:
    case zc_vobc_alr_invalid_buf_len_lt_header_add_data:
    case zc_vobc_alr_invalid_buf_len_bg_header_add_data:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = VOBC_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_VOBC;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        vobc_header_info_t m_vobc_header_info_t;
        m_vobc_header_info_t.v_msg_len = 6;
        m_vobc_header_info_t.v_msg_type = ZC_UNREGISTER_RSQ;
        offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + padLen, vobc_header_destbl_table, vobc_header_destbl_table_len);
        padLen += offset;
        onboard_unregister_rsq_t m_onboard_unregister_rsq_t;
        m_onboard_unregister_rsq_t.cmd = 0x55;
        m_onboard_unregister_rsq_t.unregister_reason = 0xff;
        m_onboard_unregister_rsq_t.reserv = 0xffff;
        offset = b2v_var_to_bytes((quint8 *)&m_onboard_unregister_rsq_t, buf + padLen, onboard_unregister_rsq_destbl_table, onboard_unregister_rsq_destbl_table_len);
        padLen += offset;
        if(type == zc_vobc_alr_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_vobc_alr_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_vobc_scm:
    case zc_vobc_scm_invalid_buf_len_lt_header_add_data:
    case zc_vobc_scm_invalid_buf_len_bg_header_add_data:
    case zc_vobc_unknown_msg:
    {
        stream_head_info_t m_stream_head_info_t;
        m_stream_head_info_t.interface_type = VOBC_ZC_INTERFACE;
        m_stream_head_info_t.sender_id = ID_MESSAGE_ZC;
        m_stream_head_info_t.receiver_id = ID_MESSAGE_VOBC;
        m_stream_head_info_t.map_version = 0x01;
        m_stream_head_info_t.map_version_crc32 =0xFFFFFFFF;
        m_stream_head_info_t.send_num = 0x00000002;
        m_stream_head_info_t.com_period = COMMU_PERIOD;
        m_stream_head_info_t.opposite_num = 0x00000001;
        m_stream_head_info_t.rcv_num = 0x00000002;
        m_stream_head_info_t.protocol_version = 0x01;
        offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
        padLen += offset;
        app_header_offset = offset;
        vobc_header_info_t m_vobc_header_info_t;
        m_vobc_header_info_t.v_msg_len = 8;
        m_vobc_header_info_t.v_msg_type = ZC_SPECIAL_MSG;
        if(type == zc_vobc_unknown_msg)
        {
            m_vobc_header_info_t.v_msg_type = 0x200;
        }
        offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + padLen, vobc_header_destbl_table, vobc_header_destbl_table_len);
        padLen += offset;
        special_control_cmd_t m_special_control_cmd_t;
        m_special_control_cmd_t.cmd = 0x55;
        m_special_control_cmd_t.zc_ci_status = 0xff;
        m_special_control_cmd_t.ma_gener_status_1 = 0x55;
        m_special_control_cmd_t.ma_gener_status_2 = 0xff;
        m_special_control_cmd_t.train_error_info = 0x55;
        m_special_control_cmd_t.auto_back_hold_status = 0xff;
        offset = b2v_var_to_bytes((quint8 *)&m_special_control_cmd_t, buf + padLen, special_control_destbl_table, special_control_destbl_table_len);
        padLen += offset;
        if(type == zc_vobc_scm_invalid_buf_len_bg_header_add_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_vobc_scm_invalid_buf_len_lt_header_add_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_monitor:
    case zc_monitor_invalid_buf_len_bg_data:
    case zc_monitor_invalid_buf_len_lt_data:
    {
        vobc_subsys_msg_t m_vobc_subsys_msg_t;
        m_vobc_subsys_msg_t.msg_type = 0x0011;
        m_vobc_subsys_msg_t.sys_id = 0x0011;
        m_vobc_subsys_msg_t.dev_type = 0x02;
        m_vobc_subsys_msg_t.dev_id = 0x0034;
        m_vobc_subsys_msg_t.dev_local = 0x34;
        m_vobc_subsys_msg_t.alarm_type = 0x01;
        m_vobc_subsys_msg_t.alarm_subtype = 0xff;
        m_vobc_subsys_msg_t.alarm_level = 0x01;
        m_vobc_subsys_msg_t.alarm_code = 0xf0f0;

        offset = b2v_var_to_bytes((quint8 *)&m_vobc_subsys_msg_t, buf, vobc_subsys_cv_table, vobc_subsys_cv_table_len);
        padLen += offset;

        if(type == zc_monitor_invalid_buf_len_bg_data)
        {
            *(buf+padLen)=0x55;
            padLen = padLen + 1;
        }
        if(type == zc_monitor_invalid_buf_len_lt_data)
        {
            quint8* buf_for_invalid = NULL;
            quint16 len_for_invalid = 0;
            len_for_invalid = padLen - 1;
            buf_for_invalid = new quint8[len_for_invalid];
            memcpy(buf_for_invalid, buf, len_for_invalid);
            padLen = len_for_invalid;
            *bufPtr = buf_for_invalid;
            delete[] buf;
        }
    }
        break;
    case zc_invalid_buf_null:
    {
        delete[] buf;
        *bufPtr = NULL;
        padLen = STREAM_HEAD_LEN;
    }
        break;
    case zc_invalid_len_zero:
    {
        padLen = 0;
    }
        break;
    default:
    {
        padLen = TEST_BUF_LEN;
    }
        break;
    }
    *lenPtr = padLen;
}
void ZcTest::testOpenDB()
{
    QEXPECT_FAIL("", "zcDb is not open", Abort);
    QVERIFY(zcDataThreadTest->zcDb.isOpen());
    QVERIFY(zcDataThreadTest->openDB());
    QVERIFY(zcDataThreadTest->zcDb.isOpen());
    QCOMPARE(zcDataThreadTest->zcDb.hostName(),QLatin1String(MSS_DB_HOST_NAME));
    QCOMPARE(zcDataThreadTest->zcDb.port(),MSS_DB_PORT);
    QCOMPARE(zcDataThreadTest->zcDb.userName(),QLatin1String(MSS_DB_USER));
    QCOMPARE(zcDataThreadTest->zcDb.password(),QLatin1String(MSS_DB_PASSWORD));
    QCOMPARE(zcDataThreadTest->zcDb.databaseName(),QLatin1String(MSS_DB_NAME));
}
void ZcTest::testCreateTB()
{
    if(!zcDataThreadTest->zcDb.isOpen())
    {
        zcDataThreadTest->openDB();
    }
    if(zcDataThreadTest->zcDb.tables().contains("zc_test"))
    {
        qDebug()<<"the zc_test table is already create,so drop it";
        zcDataThreadTest->zcQuery.exec("drop table zc_test");
    }

    QCOMPARE(zcDataThreadTest->zcDb.tables().contains("zc_test"),false);
    QString queryStr = "create table "
                       "zc_test(id int auto_increment primary key, time timestamp,"
                       "zc_interface smallint unsigned, send_id_msg int unsigned, "
                       "incept_id_msg int unsigned, edition_control_msg tinyint unsigned, "
                       "edition_check_msg int unsigned, msg_list int unsigned, "
                       "com_cycle tinyint unsigned, opposite_msg_list int unsigned, "
                       "smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                       "msg_type smallint unsigned, logical_section_size smallint unsigned, "
                       "logical_section_state int unsigned, rawdata blob) ";
    zcDataThreadTest->createTB(queryStr);
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_test"));

    //zcDataThreadTest->zcQuery.exec("drop table zc_test");
    //QCOMPARE(zcDataThreadTest->zcDb.tables().contains("zc_test"),false);
}
void ZcTest::testStart()
{
    zcDataThreadTest->start();
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_ci_ls"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_ci_sp"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_ci_pslr"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_ats_tvc"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_ats_tec"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_ats_ts"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_vobc_tc"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_vobc_arlr"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_vobc_alr"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_vobc_scm"));
    QVERIFY(zcDataThreadTest->zcDb.tables().contains("zc_monitor"));
}
void ZcTest::testSendUiZcCiLs()
{
    QSignalSpy stateSpy( zcDataThreadTest, &ZcDataThread::sendUiZcCiLs );
    QVERIFY( stateSpy.isValid() );
    QCOMPARE( stateSpy.count(), 0 );
    zcDataThreadTest->sendSignalUiZcCiLs();
    QCOMPARE( stateSpy.count(), 1 );
}
void ZcTest::testInsertData()
{
    quint8 buf[256];
    stream_head_info_t m_stream_head_info_t;
    quint16 offset = 0;
    quint16 padLen = 0;
    offset = b2v_var_to_bytes((quint8 *)&m_stream_head_info_t, buf, stream_header_destbl_table,stream_header_destbl_table_len);
    padLen += offset;
    vobc_header_info_t m_vobc_header_info_t;
    offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + padLen, vobc_header_destbl_table, vobc_header_destbl_table_len);
    padLen += offset;
    special_control_cmd_t m_special_control_cmd_t;
    offset = b2v_var_to_bytes((quint8 *)&m_special_control_cmd_t, buf + padLen, special_control_destbl_table, special_control_destbl_table_len);
    padLen += offset;

    QString sql= "select * from zc_vobc_scm";
    if(!zcDataThreadTest->zcDb.isOpen())
    {
        zcDataThreadTest->openDB();
    }
    QVERIFY(zcDataThreadTest->zcQuery.exec(sql));
    int dataNum = zcDataThreadTest->zcQuery.size();

    QVERIFY(zcDataThreadTest->insertData(&m_stream_head_info_t, &m_vobc_header_info_t, &m_special_control_cmd_t, buf, padLen));

    QVERIFY(zcDataThreadTest->zcQuery.exec(sql));
    QCOMPARE(zcDataThreadTest->zcQuery.size(),dataNum+1);
}
void ZcTest::testDealZcCi_data()
{
    quint8* bufPtr = NULL;
    bufPtr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(zc_ci_ls);
    testTypes.append(zc_ci_sp);
    testTypes.append(zc_ci_pslr);
    testTypes.append(zc_invalid_buf_null);
    testTypes.append(zc_invalid_len_zero);
    testTypes.append(zc_ci_unknown_msg);
    testTypes.append(zc_ci_ls_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_ci_sp_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_ci_pslr_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_ci_ls_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_ci_sp_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_ci_pslr_invalid_buf_len_lt_header_add_data);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("testType");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++)
    {
        TestDataType testType = *iter;
        const char* dataStr = NULL;
        constructTestData(testType, &bufPtr, &len);
        dataStr = (const char*)(*(zcMap.find(testType)));
        QTest::newRow(dataStr)<<bufPtr<<len<<testType;
    }
}
void ZcTest::testDealZcCi()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, testType);
    QSignalSpy spySendUiZcCiLs(zcDataThreadTest, &ZcDataThread::sendUiZcCiLs);
    QVERIFY( spySendUiZcCiLs.isValid() );
    QCOMPARE( spySendUiZcCiLs.count(), 0 );
    QSignalSpy spySendUiZcCiSp(zcDataThreadTest, &ZcDataThread::sendUiZcCiSp);
    QVERIFY( spySendUiZcCiSp.isValid() );
    QCOMPARE( spySendUiZcCiSp.count(), 0 );
    QSignalSpy spySendUiZcCiPslr(zcDataThreadTest, &ZcDataThread::sendUiZcCiPslr);
    QVERIFY( spySendUiZcCiPslr.isValid() );
    QCOMPARE( spySendUiZcCiPslr.count(), 0 );
    QSignalSpy spyError(zcDataThreadTest, &ZcDataThread::error);
    QVERIFY( spyError.isValid() );
    QCOMPARE( spyError.count(), 0 );
    stream_head_info_t m_stream_head_info_t;
    zcDataThreadTest->dealZcCi(buf, len, &m_stream_head_info_t);
    if(isAcceptedByonReceiveData(testType))
    {
        switch(testType)
        {
        case zc_ci_ls:
        {
            QCOMPARE(spySendUiZcCiLs.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_ci_sp:
        {
            QCOMPARE(spySendUiZcCiSp.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_ci_pslr:
        {
            QCOMPARE(spySendUiZcCiPslr.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        default:
            break;
        }
    }
    else
    {
        QCOMPARE(spySendUiZcCiLs.count(), 0);
        QCOMPARE(spySendUiZcCiSp.count(), 0);
        QCOMPARE(spySendUiZcCiPslr.count(), 0);
        QCOMPARE(spyError.count(), 1);
        QList<QVariant> arguments = spyError.takeFirst();
        QVERIFY(arguments.at(0).toInt() == ZcDataThread::DataInvalid);
    }
}

void ZcTest::testDealZcAts_data()
{
    quint8* bufPtr = NULL;
    bufPtr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(zc_ats_tvc);
    testTypes.append(zc_ats_tec);
    testTypes.append(zc_ats_ts);
    testTypes.append(zc_invalid_buf_null);
    testTypes.append(zc_invalid_len_zero);
    testTypes.append(zc_ats_unknown_msg);
    testTypes.append(zc_ats_tvc_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_ats_tec_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_ats_ts_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_ats_tvc_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_ats_tec_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_ats_ts_invalid_buf_len_lt_header_add_data);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("testType");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++)
    {
        TestDataType testType = *iter;
        const char* dataStr = NULL;
        constructTestData(testType, &bufPtr, &len);
        dataStr = (const char*)(*(zcMap.find(testType)));
        QTest::newRow(dataStr)<<bufPtr<<len<<testType;
    }
}
void ZcTest::testDealZcAts()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, testType);
    QSignalSpy spySendUiZcAtsTvc(zcDataThreadTest, &ZcDataThread::sendUiZcAtsTvc);
    QVERIFY( spySendUiZcAtsTvc.isValid() );
    QCOMPARE( spySendUiZcAtsTvc.count(), 0 );
    QSignalSpy spySendUiZcAtsTec(zcDataThreadTest, &ZcDataThread::sendUiZcAtsTec);
    QVERIFY( spySendUiZcAtsTec.isValid() );
    QCOMPARE( spySendUiZcAtsTec.count(), 0 );
    QSignalSpy spySendUiZcAtsTs(zcDataThreadTest, &ZcDataThread::sendUiZcAtsTs);
    QVERIFY( spySendUiZcAtsTs.isValid() );
    QCOMPARE( spySendUiZcAtsTs.count(), 0 );
    QSignalSpy spyError(zcDataThreadTest, &ZcDataThread::error);
    QVERIFY( spyError.isValid() );
    QCOMPARE( spyError.count(), 0 );
    stream_head_info_t m_stream_head_info_t;
    zcDataThreadTest->dealZcAts(buf, len, &m_stream_head_info_t);
    if(isAcceptedByonReceiveData(testType))
    {
        switch(testType)
        {
        case zc_ats_tvc:
        {
            QCOMPARE(spySendUiZcAtsTvc.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_ats_tec:
        {
            QCOMPARE(spySendUiZcAtsTec.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_ats_ts:
        {
            QCOMPARE(spySendUiZcAtsTs.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        default:
            break;
        }
    }
    else
    {
        QCOMPARE(spySendUiZcAtsTvc.count(), 0);
        QCOMPARE(spySendUiZcAtsTec.count(), 0);
        QCOMPARE(spySendUiZcAtsTs.count(), 0);
        QCOMPARE(spyError.count(), 1);
        QList<QVariant> arguments = spyError.takeFirst();
        QVERIFY(arguments.at(0).toInt() == ZcDataThread::DataInvalid);
    }
}

void ZcTest::testDealZcVobc_data()
{
    quint8* bufPtr = NULL;
    bufPtr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(zc_vobc_tc);
    testTypes.append(zc_vobc_arlr);
    testTypes.append(zc_vobc_alr);
    testTypes.append(zc_vobc_scm);
    testTypes.append(zc_invalid_buf_null);
    testTypes.append(zc_invalid_len_zero);
    testTypes.append(zc_vobc_unknown_msg);
    testTypes.append(zc_vobc_tc_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_vobc_arlr_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_vobc_alr_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_vobc_scm_invalid_buf_len_bg_header_add_data);
    testTypes.append(zc_vobc_tc_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_vobc_arlr_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_vobc_alr_invalid_buf_len_lt_header_add_data);
    testTypes.append(zc_vobc_scm_invalid_buf_len_lt_header_add_data);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("testType");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++)
    {
        TestDataType testType = *iter;
        const char* dataStr = NULL;
        constructTestData(testType, &bufPtr, &len);
        dataStr = (const char*)(*(zcMap.find(testType)));
        QTest::newRow(dataStr)<<bufPtr<<len<<testType;
    }
}
void ZcTest::testDealZcVobc()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, testType);
    QSignalSpy spySendUiZcVobcTc(zcDataThreadTest, &ZcDataThread::sendUiZcVobcTc);
    QVERIFY( spySendUiZcVobcTc.isValid() );
    QCOMPARE( spySendUiZcVobcTc.count(), 0 );
    QSignalSpy spySendUiZcVobcArlrTc(zcDataThreadTest, &ZcDataThread::sendUiZcVobcArlr);
    QVERIFY( spySendUiZcVobcArlrTc.isValid() );
    QCOMPARE( spySendUiZcVobcArlrTc.count(), 0 );
    QSignalSpy spySendUiZcVobcAlr(zcDataThreadTest, &ZcDataThread::sendUiZcVobcAlr);
    QVERIFY( spySendUiZcVobcAlr.isValid() );
    QCOMPARE( spySendUiZcVobcAlr.count(), 0 );
    QSignalSpy spySendUiZcVobcScm(zcDataThreadTest, &ZcDataThread::sendUiZcVobcScm);
    QVERIFY( spySendUiZcVobcScm.isValid() );
    QCOMPARE( spySendUiZcVobcScm.count(), 0 );
    QSignalSpy spyError(zcDataThreadTest, &ZcDataThread::error);
    QVERIFY( spyError.isValid() );
    QCOMPARE( spyError.count(), 0 );
    stream_head_info_t m_stream_head_info_t;
    zcDataThreadTest->dealZcVobc(buf, len, &m_stream_head_info_t);
    if(isAcceptedByonReceiveData(testType))
    {
        switch(testType)
        {
        case zc_vobc_tc:
        {
            QCOMPARE(spySendUiZcVobcTc.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_vobc_arlr:
        {
            QCOMPARE(spySendUiZcVobcArlrTc.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_vobc_alr:
        {
            QCOMPARE(spySendUiZcVobcAlr.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        case zc_vobc_scm:
        {
            QCOMPARE(spySendUiZcVobcScm.count(), 1);
            QCOMPARE(spyError.count(), 0);
        }
            break;
        default:
            break;
        }
    }
    else
    {
        QCOMPARE(spySendUiZcVobcTc.count(), 0);
        QCOMPARE(spySendUiZcVobcArlrTc.count(), 0);
        QCOMPARE(spySendUiZcVobcAlr.count(), 0);
        QCOMPARE(spySendUiZcVobcScm.count(), 0);
        QCOMPARE(spyError.count(), 1);
        QList<QVariant> arguments = spyError.takeFirst();
        QVERIFY(arguments.at(0).toInt() == ZcDataThread::DataInvalid);
    }
}

void ZcTest::testReceiveData_data()
{
    quint8* bufPtr = NULL;
    bufPtr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(zc_ci_ls);
    testTypes.append(zc_ci_sp);
    testTypes.append(zc_ci_pslr);
    testTypes.append(zc_invalid_buf_null);
    testTypes.append(zc_invalid_len_zero);
    testTypes.append(zc_unknown_interface );
    testTypes.append(zc_invalid_buf_len_lt_header);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("testType");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++)
    {
        TestDataType testType = *iter;
        const char* dataStr = NULL;
        constructTestData(testType, &bufPtr, &len);
        dataStr = (const char*)(*(zcMap.find(testType)));
        QTest::newRow(dataStr)<<bufPtr<<len<<testType;
    }
}

void ZcTest::testReceiveData()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, testType);
    QSignalSpy spyReceiveDataOk(zcDataThreadTest, &ZcDataThread::receiveDataOk);
    QVERIFY( spyReceiveDataOk.isValid() );
    QCOMPARE( spyReceiveDataOk.count(), 0 );
    QSignalSpy spyError(zcDataThreadTest, &ZcDataThread::error);
    QVERIFY( spyError.isValid() );
    QCOMPARE( spyError.count(), 0 );
    zcDataThreadTest->receiveData(buf, len);
    if(isAcceptedByonReceiveData(testType))
    {
        QCOMPARE(spyReceiveDataOk.count(), 1);
        QCOMPARE(spyError.count(), 0);
    }
    else
    {
        QCOMPARE(spyReceiveDataOk.count(), 0);
        QCOMPARE(spyError.count(), 1);
        QList<QVariant> arguments = spyError.takeFirst();
        QVERIFY(arguments.at(0).toInt() == ZcDataThread::DataInvalid);
    }
}

void ZcTest::testReceiveAlarmData_data()
{
    quint8* bufPtr = NULL;
    bufPtr = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    QList<TestDataType> testTypes;
    testTypes.append(zc_monitor);
    testTypes.append(zc_invalid_buf_null);
    testTypes.append(zc_invalid_len_zero);
    testTypes.append(zc_monitor_invalid_buf_len_bg_data );
    testTypes.append(zc_monitor_invalid_buf_len_lt_data);
    QTest::addColumn<quint8*>("buf");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<TestDataType>("testType");
    QList<TestDataType>::iterator iter = testTypes.begin();
    for(; iter != testTypes.end(); iter++)
    {
        TestDataType testType = *iter;
        const char* dataStr = NULL;
        constructTestData(testType, &bufPtr, &len);
        dataStr = (const char*)(*(zcMap.find(testType)));
        QTest::newRow(dataStr)<<bufPtr<<len<<testType;
    }
}

void ZcTest::testReceiveAlarmData()
{
    QFETCH(quint8*, buf);
    QFETCH(quint16, len);
    QFETCH(TestDataType, testType);
    testZcUdpSocket->writeDatagram(QByteArray::fromRawData((char *)buf,len), QHostAddress(MSS_ZC_IP), MSS_ZC_PORT);
    QSignalSpy spyReceiveAlarmDataOk(zcDataThreadTest, &ZcDataThread::receiveAlarmDataOk);
    QVERIFY( spyReceiveAlarmDataOk.isValid() );
    QCOMPARE( spyReceiveAlarmDataOk.count(), 0 );
    QSignalSpy spyError(zcDataThreadTest, &ZcDataThread::error);
    QVERIFY( spyError.isValid() );
    QCOMPARE( spyError.count(), 0 );
    zcDataThreadTest->receiveAlarmData();
    if(isAcceptedByonReceiveData2(testType))
    {
        QCOMPARE(spyReceiveAlarmDataOk.count(), 1);
        QCOMPARE(spyError.count(), 0);
    }
    else
    {
        QCOMPARE(spyReceiveAlarmDataOk.count(), 0);
        QCOMPARE(spyError.count(), 1);
        QList<QVariant> arguments = spyError.takeFirst();
        QVERIFY(arguments.at(0).toInt() == ZcDataThread::DataInvalid);
    }
}

QTEST_MAIN(ZcTest)
#include "zctest.moc"

