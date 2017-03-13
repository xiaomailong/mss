#include "zcdata.h"
#include "zc_protocol_pub.h"

DEF_TAB_BEGIN(stream_header_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(stream_head_info_t, interface_type)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(stream_head_info_t, sender_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(stream_head_info_t, receiver_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(stream_head_info_t, map_version)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(stream_head_info_t, map_version_crc32)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(stream_head_info_t, send_num)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(stream_head_info_t, com_period)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(stream_head_info_t, opposite_num)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(stream_head_info_t, rcv_num)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(stream_head_info_t, protocol_version)},
DEF_TAB_END(stream_header_destbl);

DEF_TAB_BEGIN(ci_header_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(ci_header_info_t, c_msg_len)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(ci_header_info_t, c_msg_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(ci_header_info_t, c_msg_num)},
DEF_TAB_END(ci_header_destbl);

DEF_TAB_BEGIN(logicTrack_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(logic_track_info_t, l_status)},
DEF_TAB_END(logicTrack_destbl);

DEF_TAB_BEGIN(signalClose_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(signal_close_info_t, s_status)},
DEF_TAB_END(signalClose_destbl);

DEF_TAB_BEGIN(routeUnlockRsq_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(protect_zone_lock_rsq_t, p_seri)},
DEF_TAB_END(routeUnlockRsq_destbl);

DEF_TAB_BEGIN(ats_header_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(ats_header_info_t, a_msg_len)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(ats_header_info_t, a_msg_type)},
DEF_TAB_END(ats_header_destbl);

DEF_TAB_BEGIN(zc_tsr_verify_frame_1_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_tsr_verify_frame_1_t, z_verify_outcome)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_tsr_verify_frame_1_t, z_faile_reason)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_tsr_verify_frame_1_t, z_temp_rate_limit)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(zc_tsr_verify_frame_1_t, z_logic_tracknum)},
DEF_TAB_END(zc_tsr_verify_frame_1_destbl);

DEF_TAB_BEGIN(zc_tsr_verify_frame_2_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(zc_tsr_verify_frame_2_t, z_logic_track_id)},
DEF_TAB_END(zc_tsr_verify_frame_2_destbl);

DEF_TAB_BEGIN(zc_tsr_exeute_frame_1_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_tsr_exeute_frame_1_t, z_verify_outcome)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_tsr_exeute_frame_1_t, z_alarm_info)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_tsr_exeute_frame_1_t, z_temp_rate_limit)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(zc_tsr_exeute_frame_1_t, z_logic_tracknum)},
DEF_TAB_END(zc_tsr_exeute_frame_1_destbl);

DEF_TAB_BEGIN(zc_tsr_exeute_frame_2_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(zc_tsr_exeute_frame_2_t, z_logic_track_id)},
DEF_TAB_END(zc_tsr_exeute_frame_2_destbl);

DEF_TAB_BEGIN(zc_status_frame_1_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(zc_status_frame_1_t, z_power_on_rsq)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(zc_status_frame_1_t, z_logic_tracknum)},
DEF_TAB_END(zc_status_frame_1_destbl);

DEF_TAB_BEGIN(zc_status_frame_2_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(zc_status_frame_2_t, z_temp_rate_limit)},
DEF_TAB_END(zc_status_frame_2_destbl);

DEF_TAB_BEGIN(vobc_header_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(vobc_header_info_t, v_msg_len)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(vobc_header_info_t, v_msg_type)},
DEF_TAB_END(vobc_header_destbl);

DEF_TAB_BEGIN(onboard_request_respond_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_request_respond_t, request_return)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_request_respond_t, unregister_reason)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_request_respond_t, reserv)},
DEF_TAB_END(onboard_request_respond_destbl);

DEF_TAB_BEGIN(onboard_unregister_rsq_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_unregister_rsq_t, cmd)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_unregister_rsq_t, unregister_reason)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_unregister_rsq_t, reserv)},
DEF_TAB_END(onboard_unregister_rsq_destbl);

DEF_TAB_BEGIN(special_control_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(special_control_cmd_t, cmd)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(special_control_cmd_t, zc_ci_status)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(special_control_cmd_t, ma_gener_status_1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(special_control_cmd_t, ma_gener_status_2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(special_control_cmd_t, train_error_info)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(special_control_cmd_t, auto_back_hold_status)},
DEF_TAB_END(special_control_destbl);

DEF_TAB_BEGIN(onboard_control_1_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(onboard_control_info_t, next_zc_id)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, ma_info_len)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_control_info_t, ma_dir)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_control_info_t, stop_response)},

    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, stop_response_tk_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(onboard_control_info_t, stop_response_tk_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, stop_response_obstacles_tk_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(onboard_control_info_t, stop_response_obstacles_tk_offset)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_control_info_t, stop_response_overlap)},

    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, ma_start_zone_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(onboard_control_info_t, ma_start_zone_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, tk_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(onboard_control_info_t, tk_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, obstacles_tk_id)},

    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(onboard_control_info_t, obstacles_tk_offset)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_control_info_t, overlap_valid)},
DEF_TAB_END(onboard_control_1_destbl);

DEF_TAB_BEGIN(onboard_control_2_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_control_info_t, auto_back_button_status)},
DEF_TAB_END(onboard_control_2_destbl);

DEF_TAB_BEGIN(onboard_control_3_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(onboard_control_info_t, destination_status)},
DEF_TAB_END(onboard_control_3_destbl);

DEF_TAB_BEGIN(switch_num_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, switch_num)},
DEF_TAB_END(switch_num_destbl);

DEF_TAB_BEGIN(switch_status_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(switch_status_t, switch_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(switch_status_t, switch_statu)},
DEF_TAB_END(switch_status_destbl);

DEF_TAB_BEGIN(psd_num_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, psd_num)},
DEF_TAB_END(psd_num_destbl);

DEF_TAB_BEGIN(psd_status_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(PSD_status_t, psd_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(PSD_status_t, psd_status)},
DEF_TAB_END(psd_status_destbl);

DEF_TAB_BEGIN(esb_num_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, esb_num)},
DEF_TAB_END(esb_num_destbl);

DEF_TAB_BEGIN(esb_status_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(ESB_status_t, esb_id)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(ESB_status_t, esb_status)},
DEF_TAB_END(esb_status_destbl);

DEF_TAB_BEGIN(temp_speed_num_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(onboard_control_info_t, temp_speed_limit_num)},
DEF_TAB_END(temp_speed_num_destbl);

DEF_TAB_BEGIN(temp_speed_status_destbl, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(temp_speed_limit_info_t, start_zone_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(temp_speed_limit_info_t, start_zone_offset)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(quint16), _SIZE_OFFSET(temp_speed_limit_info_t, end_zone_id)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(quint32), _SIZE_OFFSET(temp_speed_limit_info_t, end_zone_offset)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(temp_speed_limit_info_t, reserv)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(quint8), _SIZE_OFFSET(temp_speed_limit_info_t, speed_limit_value)},
DEF_TAB_END(temp_speed_status_destbl);


