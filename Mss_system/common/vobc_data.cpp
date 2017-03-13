#include "vobc_data.h"

DEF_TAB_BEGIN(vobc_common_header_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_header_t, vobc_ats_interface)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_header_t, send_id_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_header_t, incept_id_msg)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_header_t, edition_control_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_header_t, edition_check_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_header_t, msg_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_header_t, com_cycle)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_header_t, opposite_msg_list)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_header_t, smsg_self_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_header_t, pro_edition)},
DEF_TAB_END(vobc_common_header_cv);

DEF_TAB_BEGIN(vobc_msg_len_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_app_header_len_t, v_msg_len)},
DEF_TAB_END(vobc_msg_len_cv);

DEF_TAB_BEGIN(vobc_ats_msg_type_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, msg_type)},
DEF_TAB_END(vobc_ats_msg_type_cv);

DEF_TAB_BEGIN(vobc_zc_msg_type_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, msg_type)},
DEF_TAB_END(vobc_zc_msg_type_cv);

DEF_TAB_BEGIN(vobc_ci_msg_type_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, nc_data)},
DEF_TAB_END(vobc_ci_msg_type_cv);

DEF_TAB_BEGIN(vobc_subsys_msg_type_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_subsys_msg_t, msg_type)},
DEF_TAB_END(vobc_subsys_msg_type_cv);

DEF_TAB_BEGIN(vobc_ats_ato_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, service_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, line_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, cargroup_line_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, cargroup_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, sourceline_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, trainnum_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, destination_track_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_ato_t, destination_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, driver_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_ato_t, mode_ato)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, nc_interval_operation)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_ato_t, status_skipstop)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_ato_t, status_detain)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_ato_t, nextstation_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_ato_t, reserved_field)},
DEF_TAB_END(vobc_ats_ato_cv);

DEF_TAB_BEGIN(vobc_ats_train_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, train_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, line_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_train_pos)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, dir_train)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, dir_whell)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, head_estimate_logic_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, head_estimate_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, tail_estimate_logic_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, tail_estimate_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, over_read)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, lack_read)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, mode_atp)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, mode_cbtc)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_train_complete)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_emerg_brake)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_ar)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, vel_msg)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_psd)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_trainstoparea)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_stoptrain)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, status_unmanned_reentry)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, mode_preselect)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, reasonof_emerg_brake)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, vel_emerg_brake)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, vel_recommend)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, pos_security)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, sec_track_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, sec_track_offset)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, pos_obstacle)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, obs_track_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, obs_track_offset)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_ats_trainmsg_t, reserved_field)},
DEF_TAB_END(vobc_ats_train_cv);

DEF_TAB_BEGIN(vobc_ats_alarmmsg_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, train_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_ato)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_btm)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_vel_ui)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_radar)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_train_com)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_speed_measure)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_acceleration_measure)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_reserved1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_reserved2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, alarm_atp)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, board_info1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, board_info2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, board_info3)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, board_info4)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, board_info5)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_alarmmsg_t, board_info6)},
DEF_TAB_END(vobc_ats_alarmmsg_cv);

DEF_TAB_BEGIN(vobc_ats_check_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_check_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_ats_check_t, traid_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_check_t, status_check1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_check_t, status_check2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_check_t, status_check3)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_check_t, status_check4)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_check_t, status_check5)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_ats_check_t, status_check6)},
DEF_TAB_END(vobc_ats_check_cv);

DEF_TAB_BEGIN(vobc_ci_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, nc_data)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, dir_train)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, s_trainstoparea)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, n_psd_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, n_psd)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(mss_vobc_ci_t, nid_psd_1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, nc_psd_1)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(mss_vobc_ci_t, nid_psd_2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(mss_vobc_ci_t, nc_psd_2)},
DEF_TAB_END(vobc_ci_cv);

DEF_TAB_BEGIN(vobc_zc_train_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, dir)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, active_side)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, head_estimate_logic_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, head_estimate_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, tail_estimate_logic_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, tail_estimate_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, lack_read)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, over_read)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, train_length)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, wheel_head_length)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, op_mode)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, drive_mode)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, stop_response)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, stop_area)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, stop_area_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, stop_pos_obstacle)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, stop_pos_obs_offset)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, stop_valid)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, status_reentry)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, status_train_complete)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, led_unmanned_reentry)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, status_emerg_brake)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, train_speed)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, speed_dir)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, recess_length)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, status_trainstoparea)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(vobc_zc_trainmsg_t, ctl_zcid)},
DEF_TAB_END(vobc_zc_train_cv);

DEF_TAB_BEGIN(vobc_zc_register_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_zc_register_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_register_t, register_mode)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_zc_register_t, log_out_reason)},
DEF_TAB_END(vobc_zc_register_cv);

DEF_TAB_BEGIN(vobc_subsys_cv, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_subsys_msg_t, msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_subsys_msg_t, sys_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_subsys_msg_t, dev_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_subsys_msg_t, dev_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_subsys_msg_t, dev_local)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_subsys_msg_t, alarm_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_subsys_msg_t, alarm_subtype)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(vobc_subsys_msg_t, alarm_level)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(vobc_subsys_msg_t, alarm_code)},
DEF_TAB_END(vobc_subsys_cv);
