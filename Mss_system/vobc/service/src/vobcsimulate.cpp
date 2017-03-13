#include "vobcsimulate.h"
#include <QtGlobal>
#include <QTime>
#include "unifw.h"
#include "b2v.h"
#include "vobcuicommon.h"

VobcSimulate::VobcSimulate(QObject *parent) : QThread(parent)
{

}


void VobcSimulate::run()
{
    int num = 0;
    vobc_ats_header_t s;
    qint16 sizebuf;
    quint8 *buf;
    while(!isStop){
        QThread::sleep(1);
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        num = qrand()%240;
        switch (num%8) {
        case 0:
        {
            buf = new quint8[255];

            //ato state
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

            sizebuf = sizebuf + app_header_len.v_msg_len +2;

            emit randomDcsData(buf, sizebuf);

            break;
        }
        case 1:
        {
            buf = new quint8[255];

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
            sizebuf = sizebuf + app_header_len.v_msg_len +2;

            emit randomDcsData(buf, sizebuf);

            break;
        }
        case 2:
        {
            buf = new quint8[255];

            s.vobc_ats_interface = VOBC_CI_INTERFACE;
            s.send_id_msg = ID_MESSAGE_VOBC;
            s.incept_id_msg = ID_MESSAGE_CI;
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
            sizebuf = b2v_var_to_bytes_byoffset((quint8 *)&data, buf, sizebuf, vobc_ci_cv_table, vobc_ci_cv_table_len);
            emit randomDcsData(buf, sizebuf);

            break;
        }
        case 3:
        {
//            vobc_subsys_msg_t msg;
//            msg.id = (ESubsysId)(SUBSYS_VOBC);
//            msg.device_type = (EDeviceType)(qrand()%4);
//            msg.device_NO = "Dx-1654";
//            msg.device_location = (EDeviceLocation)(qrand()%5);
//            msg.fault_type = (EFauleType)(qrand()%2);
//            msg.sub_fault_type = (ESubFauleType)(qrand()%4);
//            msg.fault_level = (EFaultLevel)(qrand()%3);
//            msg.detail= QString::number(qrand(),16);
//            emit randomMsgAlarm(msg);
//            break;
        }
        case 4:
        {
            buf = new quint8[255];

            //vobc_ats_alarm
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
            sizebuf = sizebuf + app_header_len.v_msg_len +2;

            emit randomDcsData(buf, sizebuf);

            break;
        }
        case 5:
        {
            buf = new quint8[255];

            //vobc ats check
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
            sizebuf = sizebuf + app_header_len.v_msg_len +2;
            emit randomDcsData(buf, sizebuf);

            break;
        }
        case 6:
        {
            buf = new quint8[255];

            //vobc zc train
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

            sizebuf = sizebuf + app_header_len.v_msg_len +2;
            emit randomDcsData(buf, sizebuf);

            break;
        }
        case 7:
        {
            buf = new quint8[255];
            //vobc zc register
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
            sizebuf = sizebuf + app_header_len.v_msg_len +2;
            emit randomDcsData(buf, sizebuf);

            break;
        }
        default:
            break;
        }

    }
    VOBC_DEBUG() <<"quit the cycle here";
}

void VobcSimulate::setStopFlag(bool flag)
{
    isStop = flag;
}
