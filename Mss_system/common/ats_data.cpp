#include "ats_data.h"

DEF_TAB_BEGIN(ats_common_header_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_common_header_t, interface_type)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_common_header_t, send_id_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_common_header_t, incept_id_msg)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_common_header_t, edition_control_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_common_header_t, edition_check_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_common_header_t, msg_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_common_header_t, com_cycle)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_common_header_t, opposite_msg_list)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_common_header_t, smsg_self_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_common_header_t, pro_edition)},
DEF_TAB_END(ats_common_header_cv);

DEF_TAB_BEGIN(ats_app_header_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_app_header_t, msg_len)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_app_header_t, msg_type)},
DEF_TAB_END(ats_app_header_cv);


DEF_TAB_BEGIN(ats_vobc_heartbeat_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_heartbeat_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_heartbeat_t, year)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_heartbeat_t, month)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_heartbeat_t, date)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_heartbeat_t, hour)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_heartbeat_t, minute)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_heartbeat_t, second)},
DEF_TAB_END(ats_vobc_heartbeat_cv);

DEF_TAB_BEGIN(ats_vobc_ato_cmd_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, service_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, line_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, next_zc_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, next_ci_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, next_ats_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, cargroupline_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, cargroup_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, sourceline_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, trainnum_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, destination_track_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, destination_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_ato_cmd_t, plan_traffic_direction)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, next_skip_stop_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, station_stop_time)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_ato_cmd_t, next_skip_stop_operation)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, nc_interval_operation)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_ato_cmd_t, detain_operation)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_ato_cmd_t, reentry_operation)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_ato_cmd_t, back_indication)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_vobc_ato_cmd_t, gating_strategy)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_vobc_ato_cmd_t, reserved_field)},
DEF_TAB_END(ats_vobc_ato_cmd_cv);

DEF_TAB_BEGIN(ats_ci_heartbeat_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_ci_heartbeat_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_heartbeat_t, year)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_heartbeat_t, month)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_heartbeat_t, date)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_heartbeat_t, hour)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_heartbeat_t, minute)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_heartbeat_t, second)},
DEF_TAB_END(ats_ci_heartbeat_cv);

DEF_TAB_BEGIN(ats_ci_cmd_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_ci_cmd_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_cmd_t, cmd_cnt)},
DEF_TAB_END(ats_ci_cmd_cv);

DEF_TAB_BEGIN(ats_ci_cmd_data_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_cmd_data_t, cmd_type)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32),  _SIZE_OFFSET(ats_ci_cmd_data_t, device_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_cmd_data_t, device_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_cmd_data_t, reserved_field)},
DEF_TAB_END(ats_ci_cmd_data_cv);

DEF_TAB_BEGIN(ats_ci_status_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_ci_status_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_status_t, main_standby_sts)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_ci_status_t, ato_req_rsp)},
DEF_TAB_END(ats_ci_status_cv);

DEF_TAB_BEGIN(ats_zc_heartbeat_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),  _SIZE_OFFSET(ats_zc_heartbeat_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_zc_heartbeat_t, year)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_zc_heartbeat_t, month)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_zc_heartbeat_t, date)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_zc_heartbeat_t, hour)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_zc_heartbeat_t, minute)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_zc_heartbeat_t, second)},
DEF_TAB_END(ats_zc_heartbeat_cv);

DEF_TAB_BEGIN(ats_zc_tsr_validate_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_validate_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),    _SIZE_OFFSET(ats_zc_tsr_validate_t, tmp_speed_limit)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_validate_t, logic_track_cnt)},
DEF_TAB_END(ats_zc_tsr_validate_cv);

DEF_TAB_BEGIN(ats_zc_tsr_logic_track_data_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_logic_track_data_t, logic_track_id)},
DEF_TAB_END(ats_zc_tsr_logic_track_data_cv);

DEF_TAB_BEGIN(ats_zc_tsr_exec_cmd_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_exec_cmd_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),    _SIZE_OFFSET(ats_zc_tsr_exec_cmd_t, tmp_speed_limit)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_exec_cmd_t, logic_track_cnt)},

DEF_TAB_END(ats_zc_tsr_exec_cmd_cv);

DEF_TAB_BEGIN(ats_zc_tsr_on_confirm_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_on_confirm_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_zc_tsr_on_confirm_t, zc_id)},
DEF_TAB_END(ats_zc_tsr_on_confirm_cv);


//quint16     msg_type;//0x0203
quint8          dev_type;
quint16         dev_id;
quint8          dev_local;
quint8          alarm_type;
quint8          alarm_subtype;
quint8          alarm_level;
quint16         alarm_code;

DEF_TAB_BEGIN(ats_mss_alarm_cv, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_mss_alarm_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_mss_alarm_t, sys_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_mss_alarm_t, dev_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_mss_alarm_t, dev_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_mss_alarm_t, dev_local)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_mss_alarm_t, alarm_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_mss_alarm_t, alarm_subtype)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8),   _SIZE_OFFSET(ats_mss_alarm_t, alarm_level)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16),   _SIZE_OFFSET(ats_mss_alarm_t, alarm_code)},
DEF_TAB_END(ats_mss_alarm_cv);

