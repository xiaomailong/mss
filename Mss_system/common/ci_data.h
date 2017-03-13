#ifndef CI_DATA_H
#define CI_DATA_H
#include <qdatetime.h>
#include "unifw.h"
#include "b2v.h"
const bool CI_DEBUG = false;
const QString CI_ADRESS="127.0.0.1";
const int CI_PORT = 2222;
const uint16_t  CI_ATS_STATIONYARD = 0x0202;
const uint16_t  CI_ATS_ALARM = 0x0204;
const uint16_t  CI_ZC_MOVE = 0x0201;
const uint16_t  CI_ZC_PSD = 0x0203;
const uint16_t  CI_ZC_ESB = 0x0205;
const uint16_t  CI_ZC_RETURN = 0x0207;
const uint16_t  CI_ZC_SECTION = 0x0209;
const uint16_t  CI_ZC_REQU = 0x020B;
//buff size
const int MAX_UDP_SIZE = 200;
const int MAX_ROUTE_SIZE = 500;
//common header
const int MODULE_HEADER_LEN = 10;
const int CI_ATS_HEADER_LEN = 35;
const int CI_ZC_HEADER_LEN = 35;
const int CI_VOBC_LEN = 41;
typedef struct _ci_data_h
{
    uint16_t    ci_interface;
    uint32_t    send_id_msg;
    uint32_t    incept_id_msg;
}ci_data_h;

/****************  ci_ats_data  ****************/
#define MAX_SIGNAL_NUM  4
#define MAX_SWITCH_NUM  4
#define MAX_PHY_TRACK_NUM  4
#define MAX_LOGIC_TRACK_NUM  4
#define MAX_ROUTE_NUM  4
#define MAX_AUTO_ROUTE_NUM  4
#define MAX_SHILED_DOOR_NUM  4
#define MAX_ESP_NUM  4
#define MAX_REMAIN_CAR_NUM  4
#define MAX_HALF_AUTOBACK_NUM  4
#define MAX_AUTOBACK_NUM  4
#define MAX_SPKS_NUM  4
#define MAX_AUTO_TRIGGER_NUM  4
typedef struct _ci_ats_data_stationyard{
    /* 1  */uint8_t       c_signal[MAX_SIGNAL_NUM];
    /* 2  */uint8_t       c_switch[MAX_SWITCH_NUM];
    /* 3  */uint8_t    c_phy_track[MAX_PHY_TRACK_NUM];
    /* 4  */uint8_t  c_logic_track[MAX_LOGIC_TRACK_NUM];
    /* 5  */uint8_t          c_route_info[MAX_ROUTE_NUM];
    /* 6  */uint8_t          c_auto_route[MAX_AUTO_ROUTE_NUM];
    /* 7  */uint8_t         c_shield_door[MAX_SHILED_DOOR_NUM];
    /* 8  */uint8_t     c_esp_button[MAX_ESP_NUM];
    /* 9  */uint8_t          c_remain_car[MAX_REMAIN_CAR_NUM];
    /* 10  */uint8_t      c_half_autoback[MAX_HALF_AUTOBACK_NUM];
    /* 11  */uint8_t           c_autoback[MAX_AUTOBACK_NUM];
    /* 12  */uint8_t        c_spks[MAX_SPKS_NUM];
    /* 13  */uint8_t       c_auto_trigger[MAX_AUTO_TRIGGER_NUM];

}ci_ats_data_stationyard;
typedef struct _ci_ats_data_h
{
    uint16_t    ci_ats_interface;
    uint32_t    send_id_msg;
    uint32_t    incept_id_msg;
    uint8_t     edition_control_msg;
    uint32_t    edition_check_msg;
    uint32_t    msg_list;
    uint8_t     com_cycle;
    uint32_t    opposite_msg_list;
    uint32_t    smsg_self_list;
    uint8_t     pro_edition;
    uint16_t    package_data_size;
    uint16_t    package_data_type;
    uint16_t    a_msg_num;
}ci_ats_data_h;
typedef struct _ci_ats_data_alarm
{
    uint8_t     filament_burnout;
    uint8_t     filament_fuse;
    uint8_t     power_panel;
    uint8_t     signal_fault_shutdown;
    uint8_t     ci_device_alarm;
    uint8_t     railway_alarm;
    uint8_t     ups_fault;
    uint8_t     leu_communication_state;
    uint8_t     ci_zc_state;
    uint8_t     ci1_state;
    uint8_t     ci2_state;
    uint8_t     power1_state;
    uint8_t     power2_state;
    uint8_t     ci_count;
    uint8_t     ci_communication_state;
    uint8_t     unmanned_reentry;
    uint8_t     turnout_turnout;
    uint8_t     check_num;
    uint8_t     check_condition;
    uint8_t     psd_count;
    uint8_t     psd_x_state;
    uint8_t     station_mode;
    uint8_t     station_block;
    uint8_t     electrolytic_lock;
    uint8_t     autonomy_request;
}ci_ats_data_alarm;
/****************  end ci_ats_data  ****************/


/****************  ci_vobc_data  ****************/
typedef struct _ci_vobc_data_t
{
    uint16_t    ci_vobc_interface;
    uint32_t    send_id_msg;
    uint32_t    incept_id_msg;
    uint8_t     edition_control_msg;
    uint32_t    edition_check_msg;
    uint32_t    msg_list;
    uint8_t     com_cycle;
    uint32_t    opposite_msg_list;
    uint32_t    smsg_self_list;
    uint8_t     pro_edition;
    uint8_t     nc_data;
    uint8_t     dir_train;
    uint8_t     n_psd;
    uint16_t    nid_psd_1;
    uint8_t     nc_psd_1;
    uint8_t     r_nc_psd_1;
    uint16_t    nid_psd_2;
    uint8_t     q_psd_2;
    uint8_t     r_nc_psd_2;
    uint8_t     q_signal_aspect;
}ci_vobc_data_t;
/****************  end ci_vobc_data  ****************/


/****************  ci_zc_data  ****************/
typedef struct _ci_zc_data_h
{
    uint16_t    ci_zc_interface;
    uint32_t    send_id_msg;
    uint32_t    incept_id_msg;
    uint8_t     edition_control_msg;
    uint32_t    edition_check_msg;
    uint32_t    msg_list;
    uint8_t     com_cycle;
    uint32_t    opposite_msg_list;
    uint32_t    smsg_self_list;
    uint8_t     pro_edition;
    uint16_t    package_data_size;
    uint16_t    package_data_type;
    uint16_t    a_msg_num;
}ci_zc_data_h;

typedef struct _ci_zc_route
{
    //uint16_t route_size;/
    uint8_t     route_num;
    uint8_t     route_state;
    uint8_t     signallight_state;
    uint16_t    switch_state;
    uint8_t     sectionlock_state1;
    uint8_t     sectionlock_state2;
    uint8_t     sectionlock_state3;
    uint8_t     sectionlock_state4;
    uint8_t     sectionlock_state5;
    uint8_t     proctectlock_info;
}ci_zc_route;

typedef struct _ci_zc_psdinfo
{
    //uint16_t psd_size;
    uint8_t     psd_state;
}ci_zc_psdinfo;

typedef struct _ci_zc_esbbutton
{
    //uint16_t esb_emergency_size;
    uint8_t     esb_state;
}ci_zc_esbbutton;

typedef struct _ci_zc_returnbutton
{
    //uint16_t returnbutton_size;
    uint8_t     returnbutton_state;
}ci_zc_returnbutton;

typedef struct _ci_zc_sectionused
{
    //uint16_t zc_size;
    uint8_t     zc_state;
}ci_zc_sectionused;

typedef struct _ci_zc_approachunlock
{
    //uint16_t unlock_size;
    uint32_t    unlock_num;
}ci_zc_approachunlock;
/****************  end ci_zc_data  ****************/

/****************  ci_ci_data  ****************/
typedef struct _ci_ci_t
{
    uint32_t    moduleid_code;
    uint8_t     device_type;
    uint32_t    device_code;
    uint8_t     device_state;
    uint16_t    device_place;
    uint8_t     alarm_type;
    uint8_t     alarm_subtype;
    uint8_t     alarm_level;
    uint32_t    detailinfo;
}ci_ci_t;
/****************  end ci_ci_data  ****************/

/****************  ci_convert_data define  ****************/
DCLR_TAB(ci_data_h_convert, var_item_t);
DCLR_TAB(ci_ats_h_convert, var_item_t);
DCLR_TAB(ci_ats_data_stationyard_covert, var_item_t);
DCLR_TAB(ci_ats_data_alarm_covert, var_item_t);
DCLR_TAB(ci_vobc_convert, var_item_t);
DCLR_TAB(ci_zc_data_h_convert, var_item_t);
DCLR_TAB(ci_zc_route_convert, var_item_t);
DCLR_TAB(ci_zc_approachunlock_convert, var_item_t);
DCLR_TAB(ci_zc_sectionused_convert, var_item_t);
DCLR_TAB(ci_zc_returnbutton_convert, var_item_t);
DCLR_TAB(ci_zc_psdinfo_convert, var_item_t);
DCLR_TAB(ci_zc_esbbutton_convert, var_item_t);
DCLR_TAB(ci_ci_convert, var_item_t);
/****************  end ci_convert_data  ****************/
#endif // CI_DATA_H
