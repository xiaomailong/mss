#ifndef ATS_DATA_H
#define ATS_DATA_H

#include "unifw.h"
#include "b2v.h"
#ifdef __cplusplus
extern "C"{
#endif
//Common header data
typedef struct {
    quint16     interface_type;
    quint32     send_id_msg;
    quint32     incept_id_msg;
    quint8      edition_control_msg;
    quint32     edition_check_msg;
    quint32     msg_list;
    quint8      com_cycle;
    quint32     opposite_msg_list;
    quint32     smsg_self_list;
    quint8      pro_edition;
}ats_common_header_t;

//app header data
typedef struct {
    quint16     msg_len;
    quint16     msg_type;
}ats_app_header_t;

/***************************************
 *
 * ATS to VOBC
 * According to doc LRTSW-SYS-VOBC与ATS通信接口协议-v0.0.2.docx
 *
 *
 ***************************************/

//heart beat data
typedef struct
{
    //quint16     msg_type;//0x0201
    quint8      year;
    quint8      month;
    quint8      date;
    quint8      hour;
    quint8      minute;
    quint8      second;
}ats_vobc_heartbeat_t;


//ATO command
typedef struct
{
    //quint16     msg_type;//0x0203
    quint16     service_id;
    quint16     line_id;
    quint32     next_zc_id;
    quint32     next_ci_id;
    quint32     next_ats_id;
    quint16     cargroupline_id;
    quint16     cargroup_id;
    quint16     sourceline_id;
    quint16     trainnum_id;
    quint16     destination_track_id;
    quint32     destination_id;
    quint8      plan_traffic_direction;
    quint16     next_skip_stop_id;
    quint16     station_stop_time;
    quint8      next_skip_stop_operation;
    quint16     nc_interval_operation;
    quint8      detain_operation;
    quint8      reentry_operation;
    quint8      back_indication;
    quint8      gating_strategy;
    uint32_t    reserved_field;
}ats_vobc_ato_cmd_t;



/***************************************
 *
 * ATS to CI
 * According to doc LRTSW-SYS-ATS与CI通信接口协议-v0.1.0.docx
 *
 *
 ***************************************/

//heart beat data
typedef struct
{
    //quint16     msg_type;//0x0201
    quint8      year;
    quint8      month;
    quint8      date;
    quint8      hour;
    quint8      minute;
    quint8      second;
}ats_ci_heartbeat_t;


//command common
typedef struct
{
    //quint16     msg_type;//0x0203
    quint8      cmd_cnt;//cmd_cnt * ats_ci_cmd_data_t
}ats_ci_cmd_t;

//command data
typedef struct
{
    quint8      cmd_type;
    quint32     device_id;
    quint8      device_type;
    quint8      reserved_field;//0xFF
}ats_ci_cmd_data_t;

//running state
typedef struct
{
    //quint16     msg_type;//0x0205
    quint8      main_standby_sts;
    quint8      ato_req_rsp;
}ats_ci_status_t;



/***************************************
 *
 * ATS to ZC
 * According to doc LRTSW-SYS-ATS与ZC通信接口协议-v0.0.2.docx
 *
 *
 ***************************************/

//heart beat data
typedef struct
{
    //quint16     msg_type;//0x0201
    quint8      year;
    quint8      month;
    quint8      date;
    quint8      hour;
    quint8      minute;
    quint8      second;
}ats_zc_heartbeat_t;


//tsr validata info
typedef struct
{
    //quint16     msg_type;//0x0203
    quint8      tmp_speed_limit;
    quint16     logic_track_cnt;//logic_track_cnt * ats_zc_tsr_logic_track_data_t
}ats_zc_tsr_validate_t;

typedef struct
{
    quint16     logic_track_id;
}ats_zc_tsr_logic_track_data_t;

//tsr execute cmdinfo
typedef struct
{
    //quint16     msg_type;//0x0205
    quint8      tmp_speed_limit;
    quint16     logic_track_cnt; //logic_track_cnt * ats_zc_tsr_logic_track_data_t
}ats_zc_tsr_exec_cmd_t;

//tsr power on confirm
typedef struct
{
    //quint16     msg_type;//0x0209
    quint16     zc_id;
}ats_zc_tsr_on_confirm_t;

/***************************************
 *
 * ATS to MSS
 * According to doc LRTSW-SYS-ATS与XXX.docx
 *
 *
 ***************************************/
typedef struct
{
    //quint16     msg_type;//0x0203
    quint16         sys_id;
    quint8          dev_type;
    quint16         dev_id;
    quint8          dev_local;
    quint8          alarm_type;
    quint8          alarm_subtype;
    quint8          alarm_level;
    quint16         alarm_code;
}ats_mss_alarm_t;


DCLR_TAB(ats_common_header_cv, var_item_t);
DCLR_TAB(ats_app_header_cv, var_item_t);

DCLR_TAB(ats_vobc_heartbeat_cv, var_item_t);
DCLR_TAB(ats_vobc_ato_cmd_cv, var_item_t);

DCLR_TAB(ats_ci_heartbeat_cv, var_item_t);
DCLR_TAB(ats_ci_cmd_cv, var_item_t);
DCLR_TAB(ats_ci_cmd_data_cv, var_item_t);
DCLR_TAB(ats_ci_status_cv, var_item_t);

DCLR_TAB(ats_zc_heartbeat_cv, var_item_t);
DCLR_TAB(ats_zc_tsr_validate_cv, var_item_t);
DCLR_TAB(ats_zc_tsr_logic_track_data_cv, var_item_t);
DCLR_TAB(ats_zc_tsr_exec_cmd_cv, var_item_t);
DCLR_TAB(ats_zc_tsr_on_confirm_cv, var_item_t);

DCLR_TAB(ats_mss_alarm_cv, var_item_t);

#ifdef __cplusplus
}
#endif
#endif // ATS_DATA_H
