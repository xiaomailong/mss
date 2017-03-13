#include "ci_data.h"
DEF_TAB_BEGIN(ci_data_h_convert, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_data_h, ci_interface)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_data_h, send_id_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_data_h, incept_id_msg)},
DEF_TAB_END(ci_data_h_convert);
DEF_TAB_BEGIN(ci_ats_h_convert, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ats_data_h, ci_ats_interface)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ats_data_h, send_id_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ats_data_h, incept_id_msg)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_h, edition_control_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ats_data_h, edition_check_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ats_data_h, msg_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_h, com_cycle)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ats_data_h, opposite_msg_list)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ats_data_h, smsg_self_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_h, pro_edition)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ats_data_h, package_data_size)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ats_data_h, package_data_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ats_data_h, a_msg_num)},
DEF_TAB_END(ci_ats_h_convert);

DEF_TAB_BEGIN(ci_ats_data_stationyard_covert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ats_data_stationyard, deviceinfo_len)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_signal)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_switch)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_phy_track)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_logic_track)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_route_info)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_auto_route)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_shield_door)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_esp_button)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_remain_car)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_half_autoback)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_autoback)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_spks)},
    {UNIFW_BIG_ENDIAN, MAX_SIGNAL_NUM, MAX_SIGNAL_NUM*sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_stationyard, c_auto_trigger)},
DEF_TAB_END(ci_ats_data_stationyard_covert);

DEF_TAB_BEGIN(ci_ats_data_alarm_covert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ats_data_alarm, info_len)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, filament_burnout)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, filament_fuse)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, power_panel)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, signal_fault_shutdown)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ci_device_alarm)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, railway_alarm)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ups_fault)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, leu_communication_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ci_zc_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ci1_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ci2_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, power1_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, power2_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ci_count)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, ci_communication_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, unmanned_reentry)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, turnout_turnout)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, check_num)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, check_condition)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, psd_count)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, psd_x_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, station_mode)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, station_block)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, electrolytic_lock)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ats_data_alarm, autonomy_request)},
DEF_TAB_END(ci_ats_data_alarm_covert);

DEF_TAB_BEGIN(ci_vobc_convert, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_vobc_data_t, ci_vobc_interface)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_vobc_data_t, send_id_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_vobc_data_t, incept_id_msg)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, edition_control_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_vobc_data_t, edition_check_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_vobc_data_t, msg_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, com_cycle)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_vobc_data_t, opposite_msg_list)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_vobc_data_t, smsg_self_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, pro_edition)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, nc_data)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, dir_train)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, n_psd)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_vobc_data_t, nid_psd_1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, nc_psd_1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, r_nc_psd_1)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_vobc_data_t, nid_psd_2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, q_psd_2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, r_nc_psd_2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_vobc_data_t, q_signal_aspect)},
DEF_TAB_END(ci_vobc_convert);

DEF_TAB_BEGIN(ci_zc_data_h_convert, var_item_t)
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_data_h, ci_zc_interface)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_data_h, send_id_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_data_h, incept_id_msg)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_data_h, edition_control_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_data_h, edition_check_msg)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_data_h, msg_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_data_h, com_cycle)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_data_h, opposite_msg_list)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_data_h, smsg_self_list)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_data_h, pro_edition)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_data_h, package_data_size)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_data_h, package_data_type)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_data_h, a_msg_num)},
DEF_TAB_END(ci_zc_data_h_convert);

DEF_TAB_BEGIN(ci_zc_route_convert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_route, route_size)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, route_num)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, route_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, signallight_state)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_route, switch_state)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, sectionlock_state1)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, sectionlock_state2)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, sectionlock_state3)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, sectionlock_state4)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, sectionlock_state5)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_route, proctectlock_info)},
DEF_TAB_END(ci_zc_route_convert);

DEF_TAB_BEGIN(ci_zc_psdinfo_convert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_psdinfo, psd_size)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_psdinfo, psd_state)},
DEF_TAB_END(ci_zc_psdinfo_convert);

DEF_TAB_BEGIN(ci_zc_esbbutton_convert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_esbbutton, esb_emergency_size)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_esbbutton, esb_state)},
DEF_TAB_END(ci_zc_esbbutton_convert);

DEF_TAB_BEGIN(ci_zc_returnbutton_convert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_returnbutton, returnbutton_size)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_returnbutton, returnbutton_state)},
DEF_TAB_END(ci_zc_returnbutton_convert);

DEF_TAB_BEGIN(ci_zc_sectionused_convert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_sectionused, zc_size)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_zc_sectionused, zc_state)},
DEF_TAB_END(ci_zc_sectionused_convert);


DEF_TAB_BEGIN(ci_zc_approachunlock_convert, var_item_t)
    //{UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_zc_approachunlock, unlock_size)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_zc_approachunlock, unlock_num)},
DEF_TAB_END(ci_zc_approachunlock_convert);

DEF_TAB_BEGIN(ci_ci_convert, var_item_t)
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ci_t, moduleid_code)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ci_t, device_type)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ci_t, device_code)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ci_t, device_state)},
    {UNIFW_BIG_ENDIAN, 2, sizeof(uint16_t), _SIZE_OFFSET(ci_ci_t, device_place)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ci_t, alarm_type)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ci_t, alarm_subtype)},
    {UNIFW_BIG_ENDIAN, 1, sizeof(uint8_t), _SIZE_OFFSET(ci_ci_t, alarm_level)},
    {UNIFW_BIG_ENDIAN, 4, sizeof(uint32_t), _SIZE_OFFSET(ci_ci_t, detailinfo)},
DEF_TAB_END(ci_ci_convert);


