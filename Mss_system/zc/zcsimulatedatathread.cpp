#include "zc/zcsimulatedatathread.h"
#include "zcdata.h"
#include "zc_protocol_pub.h"
#include "mssdatadefine.h"
#include "mssdbconfig.h"
#include "vobc_data.h"

#include <QDebug>

bool DEBUG = false;
int mSleepTime = 500;
#define BUF_SIZE 512

ZcSimulateDataThread::ZcSimulateDataThread(QObject *parent) : QObject(parent)
{
    sendZcUdpSocket = new QUdpSocket(this);
    isStop = false;
}
void ZcSimulateDataThread::start()
{
    while(!isStop) {
        int type = rand()%11;
        quint16 pad_len = 0;
        quint16 offset = 0;
        quint16 app_header_offset = 0;
        quint8 *buf;
        if(DEBUG) qDebug("[ZcSimulateDataThread]run start type %d", type);
        if (type == 0)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            ci_header_info_t m_ci_header_info_t;
            m_ci_header_info_t.c_msg_len = 0;
            m_ci_header_info_t.c_msg_type = LOGIC_ZONE_STATUS;
            m_ci_header_info_t.c_msg_num = 5;
            offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + pad_len, ci_header_destbl_table, ci_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            logic_track_info_t m_logic_track_info_t;
            for(int i=0;i<m_ci_header_info_t.c_msg_num*0.5;i++)
            {
                quint8 temp = 0;
                temp = temp|0x01;
                if((i*2+1) < m_ci_header_info_t.c_msg_num )temp = temp|0xa0;
                m_logic_track_info_t.l_status = temp;
                offset = b2v_var_to_bytes((quint8 *)&m_logic_track_info_t, buf + pad_len, logicTrack_destbl_table, logicTrack_destbl_table_len);
                pad_len += offset;
            }
            m_ci_header_info_t.c_msg_len = pad_len - app_header_offset - 2;
            offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + app_header_offset, ci_header_destbl_table, ci_header_destbl_table_len);
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<m_ci_header_info_t.c_msg_len;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 1)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            ci_header_info_t m_ci_header_info_t;
            m_ci_header_info_t.c_msg_len = 0;
            m_ci_header_info_t.c_msg_type = SIGNAL_NEAR_INFO;
            m_ci_header_info_t.c_msg_num = 5;
            offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + pad_len, ci_header_destbl_table, ci_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            signal_close_info_t m_signal_close_info_t;
            for(int i=0;i<m_ci_header_info_t.c_msg_num;i++)
            {
                m_signal_close_info_t.s_status = 0xff;
                offset = b2v_var_to_bytes((quint8 *)&m_signal_close_info_t, buf + pad_len, signalClose_destbl_table, signalClose_destbl_table_len);
                pad_len += offset;
            }
            m_ci_header_info_t.c_msg_len = pad_len - app_header_offset - 2;
            offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + app_header_offset, ci_header_destbl_table, ci_header_destbl_table_len);
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<m_ci_header_info_t.c_msg_len;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 2)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            ci_header_info_t m_ci_header_info_t;
            m_ci_header_info_t.c_msg_len = 0;
            m_ci_header_info_t.c_msg_type = PROTECT_ZONE_LOCK_ASK;
            m_ci_header_info_t.c_msg_num = 1;
            offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + pad_len, ci_header_destbl_table, ci_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            protect_zone_lock_rsq_t m_protect_zone_lock_rsq_t;
            //for(int i=0;i<m_ci_header_info_t.c_msg_num;i++)
            //{
                m_protect_zone_lock_rsq_t.p_seri = 0xf0f0;
                offset = b2v_var_to_bytes((quint8 *)&m_protect_zone_lock_rsq_t, buf + pad_len, routeUnlockRsq_destbl_table, routeUnlockRsq_destbl_table_len);
                pad_len += offset;
            //}
            m_ci_header_info_t.c_msg_len = pad_len - app_header_offset - 2;
            offset = b2v_var_to_bytes((quint8 *)&m_ci_header_info_t, buf + app_header_offset, ci_header_destbl_table, ci_header_destbl_table_len);
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<m_ci_header_info_t.c_msg_len;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 3)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            ats_header_info_t m_ats_header_info_t;
            m_ats_header_info_t.a_msg_len = 9;
            m_ats_header_info_t.a_msg_type = ZC_TSR_VERIFY_FRAME;
            offset = b2v_var_to_bytes((quint8 *)&m_ats_header_info_t, buf + pad_len, ats_header_destbl_table, ats_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            zc_tsr_verify_frame_1_t m_zc_tsr_verify_frame_1_t;
            m_zc_tsr_verify_frame_1_t.z_verify_outcome = 0x55;
            m_zc_tsr_verify_frame_1_t.z_faile_reason = 0xff;
            m_zc_tsr_verify_frame_1_t.z_temp_rate_limit = 0xff;
            m_zc_tsr_verify_frame_1_t.z_logic_tracknum = 0x0f0f;
            offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_verify_frame_1_t, buf + pad_len, zc_tsr_verify_frame_1_destbl_table, zc_tsr_verify_frame_1_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;
            zc_tsr_verify_frame_2_t m_zc_tsr_verify_frame_2_t;
            m_zc_tsr_verify_frame_2_t.z_logic_track_id = 0x5500;
            offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_verify_frame_2_t, buf + pad_len, zc_tsr_verify_frame_2_destbl_table, zc_tsr_verify_frame_2_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 4)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            ats_header_info_t m_ats_header_info_t;
            m_ats_header_info_t.a_msg_len = 9;
            m_ats_header_info_t.a_msg_type = ZC_TSR_EXEUTE_FRAME;
            offset = b2v_var_to_bytes((quint8 *)&m_ats_header_info_t, buf + pad_len, ats_header_destbl_table, ats_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            zc_tsr_exeute_frame_1_t m_zc_tsr_exeute_frame_1_t;
            m_zc_tsr_exeute_frame_1_t.z_verify_outcome = 0x55;
            m_zc_tsr_exeute_frame_1_t.z_alarm_info = 0xff;
            m_zc_tsr_exeute_frame_1_t.z_temp_rate_limit = 0xff;
            m_zc_tsr_exeute_frame_1_t.z_logic_tracknum = 0x0f0f;
            offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_exeute_frame_1_t, buf + pad_len, zc_tsr_exeute_frame_1_destbl_table, zc_tsr_exeute_frame_1_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;
            zc_tsr_exeute_frame_2_t m_zc_tsr_exeute_frame_2_t;
            m_zc_tsr_exeute_frame_2_t.z_logic_track_id = 0x5500;
            offset = b2v_var_to_bytes((quint8 *)&m_zc_tsr_exeute_frame_2_t, buf + pad_len, zc_tsr_exeute_frame_2_destbl_table, zc_tsr_exeute_frame_2_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 5)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            ats_header_info_t m_ats_header_info_t;
            m_ats_header_info_t.a_msg_len = 7;
            m_ats_header_info_t.a_msg_type = ZC_STATUS_INFO_FRAME;
            offset = b2v_var_to_bytes((quint8 *)&m_ats_header_info_t, buf + pad_len, ats_header_destbl_table, ats_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            zc_status_frame_1_t m_zc_status_frame_1_t;
            m_zc_status_frame_1_t.z_power_on_rsq = 0x55;
            m_zc_status_frame_1_t.z_logic_tracknum = 0x0f0f;
            offset = b2v_var_to_bytes((quint8 *)&m_zc_status_frame_1_t, buf + pad_len, zc_status_frame_1_destbl_table, zc_status_frame_1_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;
            zc_status_frame_2_t m_zc_status_frame_2_t;
            m_zc_status_frame_2_t.z_temp_rate_limit = 0x5500;
            offset = b2v_var_to_bytes((quint8 *)&m_zc_status_frame_2_t, buf + pad_len, zc_status_frame_2_destbl_table, zc_status_frame_2_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 6)
        {
            quint8 buf[512];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            vobc_header_info_t m_vobc_header_info_t;
            m_vobc_header_info_t.v_msg_len = 0;
            m_vobc_header_info_t.v_msg_type = ZC_CONTROLTRAIN;
            offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + pad_len, vobc_header_destbl_table, vobc_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
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
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, onboard_control_1_destbl_table, onboard_control_1_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;

            m_onboard_control_info_t.switch_num = 2;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, switch_num_destbl_table, switch_num_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len4:"<<pad_len;
            switch_status_t m_switch_status_t;
            for(int i = 0; i<m_onboard_control_info_t.switch_num; i++)
            {
                m_switch_status_t.switch_id = i;
                m_switch_status_t.switch_statu = i;
                offset = b2v_var_to_bytes((quint8 *)&m_switch_status_t, buf + pad_len, switch_status_destbl_table, switch_status_destbl_table_len);
                pad_len += offset;
            }
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len5:"<<pad_len;

            m_onboard_control_info_t.psd_num = 2;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, psd_num_destbl_table, psd_num_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len6:"<<pad_len;
            PSD_status_t m_PSD_status_t;
            for(int i = 0; i<m_onboard_control_info_t.psd_num; i++)
            {
                m_PSD_status_t.psd_id = i;
                m_PSD_status_t.psd_status = i;
                offset = b2v_var_to_bytes((quint8 *)&m_PSD_status_t, buf + pad_len, psd_status_destbl_table, psd_status_destbl_table_len);
                pad_len += offset;
            }
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len7:"<<pad_len;

            m_onboard_control_info_t.esb_num = 2;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, esb_num_destbl_table, esb_num_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len8:"<<pad_len;
            ESB_status_t m_ESB_status_t;
            for(int i = 0; i<m_onboard_control_info_t.esb_num; i++)
            {
                m_ESB_status_t.esb_id = i;
                m_ESB_status_t.esb_status = i;
                offset = b2v_var_to_bytes((quint8 *)&m_ESB_status_t, buf + pad_len, esb_status_destbl_table, esb_status_destbl_table_len);
                pad_len += offset;
            }
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len9:"<<pad_len;

            m_onboard_control_info_t.auto_back_button_status = 0x55;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, onboard_control_2_destbl_table, onboard_control_2_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len10:"<<pad_len;

            m_onboard_control_info_t.temp_speed_limit_num = 2;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, temp_speed_num_destbl_table, temp_speed_num_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len11:"<<pad_len;
            temp_speed_limit_info_t m_temp_speed_limit_info_t;
            for(int i = 0; i<m_onboard_control_info_t.temp_speed_limit_num; i++)
            {
                m_temp_speed_limit_info_t.start_zone_id = i;
                m_temp_speed_limit_info_t.start_zone_offset = 0xffffffff;
                m_temp_speed_limit_info_t.end_zone_id = i;
                m_temp_speed_limit_info_t.end_zone_offset = 0xffffffff;
                m_temp_speed_limit_info_t.reserv = 0xff;
                m_temp_speed_limit_info_t.speed_limit_value = 0x55;
                offset = b2v_var_to_bytes((quint8 *)&m_temp_speed_limit_info_t, buf + pad_len, temp_speed_status_destbl_table, temp_speed_status_destbl_table_len);
                pad_len += offset;
            }
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len12:"<<pad_len;

            m_onboard_control_info_t.destination_status = 0x55;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_control_info_t, buf + pad_len, onboard_control_3_destbl_table, onboard_control_3_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len13:"<<pad_len;

            m_vobc_header_info_t.v_msg_len = pad_len - app_header_offset - 2;
            offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + app_header_offset, vobc_header_destbl_table, vobc_header_destbl_table_len);
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len14:"<<m_vobc_header_info_t.v_msg_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 7)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            vobc_header_info_t m_vobc_header_info_t;
            m_vobc_header_info_t.v_msg_len = 6;
            m_vobc_header_info_t.v_msg_type = ZC_RESPOND_RSQ;
            offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + pad_len, vobc_header_destbl_table, vobc_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            onboard_request_respond_t m_onboard_request_respond_t;
            m_onboard_request_respond_t.request_return = 0x55;
            m_onboard_request_respond_t.unregister_reason = 0xff;
            m_onboard_request_respond_t.reserv = 0xffff;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_request_respond_t, buf + pad_len, onboard_request_respond_destbl_table, onboard_request_respond_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 8)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            vobc_header_info_t m_vobc_header_info_t;
            m_vobc_header_info_t.v_msg_len = 6;
            m_vobc_header_info_t.v_msg_type = ZC_UNREGISTER_RSQ;
            offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + pad_len, vobc_header_destbl_table, vobc_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            onboard_unregister_rsq_t m_onboard_unregister_rsq_t;
            m_onboard_unregister_rsq_t.cmd = 0x55;
            m_onboard_unregister_rsq_t.unregister_reason = 0xff;
            m_onboard_unregister_rsq_t.reserv = 0xffff;
            offset = b2v_var_to_bytes((quint8 *)&m_onboard_unregister_rsq_t, buf + pad_len, onboard_unregister_rsq_destbl_table, onboard_unregister_rsq_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 9)
        {
            buf = new quint8[BUF_SIZE];
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
            pad_len += offset;
            app_header_offset = offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len1:"<<pad_len;
            vobc_header_info_t m_vobc_header_info_t;
            m_vobc_header_info_t.v_msg_len = 8;
            m_vobc_header_info_t.v_msg_type = ZC_SPECIAL_MSG;
            offset = b2v_var_to_bytes((quint8 *)&m_vobc_header_info_t, buf + pad_len, vobc_header_destbl_table, vobc_header_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len2:"<<pad_len;
            special_control_cmd_t m_special_control_cmd_t;
            m_special_control_cmd_t.cmd = 0x55;
            m_special_control_cmd_t.zc_ci_status = 0xff;
            m_special_control_cmd_t.ma_gener_status_1 = 0x55;
            m_special_control_cmd_t.ma_gener_status_2 = 0xff;
            m_special_control_cmd_t.train_error_info = 0x55;
            m_special_control_cmd_t.auto_back_hold_status = 0xff;
            offset = b2v_var_to_bytes((quint8 *)&m_special_control_cmd_t, buf + pad_len, special_control_destbl_table, special_control_destbl_table_len);
            pad_len += offset;
            if(DEBUG) qDebug()<<"[ZcSimulateDataThread]pad_len3:"<<pad_len;
            //send emit to ui
            emit send_zc(buf, pad_len);
            QThread::msleep(mSleepTime);
        }
        else if (type == 10)
        {
            buf = new quint8[BUF_SIZE];
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

            //vobc_subsys_msg_t.
            quint16 offset;
            offset = b2v_var_to_bytes((quint8 *)&m_vobc_subsys_msg_t, buf, vobc_subsys_cv_table, vobc_subsys_cv_table_len);
            pad_len += offset;
            //send emit to ui
            //emit send_zc2(buf, pad_len);
            //QThread::sleep(1);
            sendZcUdpSocket->writeDatagram(QByteArray::fromRawData((char *)buf,pad_len), QHostAddress(MSS_ZC_IP), MSS_ZC_PORT);
            QThread::msleep(mSleepTime);
        }
        else
        {
            if(DEBUG) qDebug("[ZcSimulateDataThread]do nothing");
        }
    }
}
