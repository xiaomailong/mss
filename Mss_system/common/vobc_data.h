#ifndef MSS_VOBC_H
#define MSS_VOBC_H
#include "unifw.h"
#include "b2v.h"
#include "mssdatadefine.h"
#include "vobc_ats_parse.h"
#include "vobc_ci_comm.h"

#if 1

typedef struct _vobc_app_header_len_t{
    uint16_t     v_msg_len;
}vobc_app_header_len_t;

typedef struct _vobc_ats_alarmmsg_t {
    uint16_t    msg_type;   //0x0206
    uint16_t    train_id;
    uint8_t     alarm_ato;
    uint8_t     alarm_btm;
    uint8_t     alarm_vel_ui;
    uint8_t     alarm_radar;
    uint8_t     alarm_train_com;
    uint8_t     alarm_speed_measure;
    uint8_t     alarm_acceleration_measure;
    uint8_t     alarm_reserved1;
    uint8_t     alarm_reserved2;
    uint8_t     alarm_atp;
    uint8_t     board_info1;
    uint8_t     board_info2;
    uint8_t     board_info3;
    uint8_t     board_info4;
    uint8_t     board_info5;
    uint8_t     board_info6;
}vobc_ats_alarmmsg_t;

typedef struct _mss_vobc_ats_alarmmsg_t {
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_ats_alarmmsg_t datagram;
}MssVobcAtsAlarm;


typedef struct _vobc_ats_check_t {
    uint16_t    msg_type;   //0x0208
    uint16_t    traid_id;
    uint8_t     status_check1;
    uint8_t     status_check2;
    uint8_t     status_check3;
    uint8_t     status_check4;
    uint8_t     status_check5;
    uint8_t     status_check6;
}vobc_ats_check_t;

typedef struct _mss_vobc_ats_check_t {
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_ats_check_t datagram;
}MssVobcAtsCheck;

typedef struct _vobc_zc_trainmsg_t {
    uint16_t    msg_type;   //0x0202
    uint8_t     dir;
    uint8_t     active_side;
    uint16_t    head_estimate_logic_id;
    uint32_t    head_estimate_offset;
    uint16_t    tail_estimate_logic_id;
    uint32_t    tail_estimate_offset;
    uint16_t    lack_read;
    uint16_t    over_read;
    uint16_t    train_length;
    uint16_t    wheel_head_length;
    uint8_t     op_mode;
    uint8_t     drive_mode;
    uint8_t     stop_response;
    uint16_t    stop_area;
    uint32_t    stop_area_offset;
    uint16_t    stop_pos_obstacle;
    uint32_t    stop_pos_obs_offset;
    uint8_t     stop_valid;
    uint8_t     status_reentry;
    uint8_t     status_train_complete;
    uint8_t     led_unmanned_reentry;
    uint8_t     status_emerg_brake;
    uint16_t    train_speed;
    uint8_t     speed_dir;
    uint16_t    recess_length;
    uint8_t     status_trainstoparea;
    uint32_t    ctl_zcid;
}vobc_zc_trainmsg_t;

typedef struct _mss_vobc_zc_trainmsg_t {
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_zc_trainmsg_t datagram;
}MssVobcZcTrain;

typedef struct _vobc_zc_register_t {
    uint16_t    msg_type;       //0x0206
    uint8_t     register_mode;  //login 0x55  logout 0xCC
    uint8_t     log_out_reason;
}vobc_zc_register_t;

typedef struct _mss_vobc_zc_register_t {
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_zc_register_t datagram;
}MssVobcZcRegister;
#endif

typedef struct _mss_vobc_ats_ato {
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_ats_ato_t datagram;
}MssVobcAtsAto;

typedef struct _mss_vobc_ats_train {
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_ats_trainmsg_t datagram;
}MssVobcAtsTrain;

typedef struct _mss_vobc_ci_t{
    uint8_t		nc_data;				/*�������� */
    uint8_t		dir_train;				/*�г����з��� */
    uint8_t		s_trainstoparea;	    /*�г�ͣ��ͣ׼״̬ */
    uint8_t		n_psd_type;				/*�г��������� */
    uint8_t		n_psd;					/*��Ҫ���Ƶ�PSD������ */
    uint16_t	nid_psd_1;				/*PSD_1��ID */
    uint8_t		nc_psd_1;				/*PSD_1�Ŀ������� */
    uint16_t	nid_psd_2;				/*PSD_2��ID */
    uint8_t		nc_psd_2;				/*PSD_2�Ŀ������� */
}mss_vobc_ci_t;

typedef struct _mss_vobc_ci{
    vobc_ats_header_t common_header;
    mss_vobc_ci_t datagram;
}MssVobcCi;

typedef enum vobctable{
    TableAtsAtoState,
    TableAtsTrain,
    TableAtsVehicleAlarm,
    TableAtsVehicleDailyCheck,

    TableVobcCi,
    TableZcTrain,
    TableZcRegister,
    TableSubsysVobcAlarm,
    TableSubsysVobcState
}EVobcTb;

typedef enum vobc_err_code{
    ErrOpenDatabase,
    ErrCreateTable,
    ErrInsertTable,

    ErrInvalidArgument
}EVobcErrCode;

typedef struct _vobc_subsys_msg_t
{
    quint16         msg_type;
    quint16         sys_id;
    quint8          dev_type;
    quint16         dev_id;
    quint8          dev_local;
    quint8          alarm_type;
    quint8          alarm_subtype;
    quint8          alarm_level;
    quint16         alarm_code;
}vobc_subsys_msg_t;

typedef struct _mss_subsys_vobc{
    vobc_ats_header_t common_header;
    vobc_app_header_len_t app_len;
    vobc_subsys_msg_t datagram;
}MssSubSysVobc;

DCLR_TAB(vobc_common_header_cv, var_item_t);
DCLR_TAB(vobc_ats_ato_cv, var_item_t);
DCLR_TAB(vobc_ats_train_cv, var_item_t);
DCLR_TAB(vobc_ci_cv, var_item_t);
DCLR_TAB(vobc_zc_train_cv, var_item_t);
DCLR_TAB(vobc_zc_register_cv, var_item_t);
DCLR_TAB(vobc_ats_alarmmsg_cv, var_item_t);
DCLR_TAB(vobc_ats_check_cv, var_item_t);
DCLR_TAB(vobc_subsys_cv, var_item_t);

DCLR_TAB(vobc_msg_len_cv, var_item_t);
DCLR_TAB(vobc_ats_msg_type_cv, var_item_t);
DCLR_TAB(vobc_ci_msg_type_cv, var_item_t);
DCLR_TAB(vobc_zc_msg_type_cv, var_item_t);
DCLR_TAB(vobc_subsys_msg_type_cv, var_item_t);

#endif // MSS_VOBC_H
