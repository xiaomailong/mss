#ifndef ZC_CI_PARSE_H
#define ZC_CI_PARSE_H
#include "unifw.h"
#include "b2v.h"
#include "mssdatadefine.h"
#include "zc_protocol_pub.h"
#include <QMetaType>

#define STREAM_HEAD_LEN 29

#define CI_HEAD_LEN 6
#define LOGIC_TRACK 1
#define SIGNAL_CLOSE 1
#define ROUTE_UNLOCK_RSQ 1

#define ATS_HEAD_LEN 4
#define ZC_TSR_VERIFY_FRAME_1 5
#define ZC_TSR_VERIFY_FRAME_2 2
#define ZC_TSR_EXEUTE_FRAME_1 5
#define ZC_TSR_EXEUTE_FRAME_2 2
#define ZC_STATUS_FRAME_1 3
#define ZC_STATUS_FRAME_2 2

#define VOBC_HEAD_LEN 4
#define ONBOARD_CONTROL 40
#define ONBOARD_REQUEST_RESPOND_LEN 4
#define ONBOARD_UNREGISTER_RSQ_LEN 4
#define SPECIAL_CONTROL_LEN 6

#define ZC_MONITOR_LEN 13

Q_DECLARE_METATYPE(stream_head_info_t)

Q_DECLARE_METATYPE(ci_header_info_t)
Q_DECLARE_METATYPE(logic_track_info_t)
Q_DECLARE_METATYPE(signal_close_info_t)
Q_DECLARE_METATYPE(protect_zone_lock_rsq_t)

Q_DECLARE_METATYPE(ats_header_info_t)
Q_DECLARE_METATYPE(zc_tsr_verify_frame_1_t)
Q_DECLARE_METATYPE(zc_tsr_verify_frame_2_t)
Q_DECLARE_METATYPE(zc_tsr_exeute_frame_1_t)
Q_DECLARE_METATYPE(zc_tsr_exeute_frame_2_t)
Q_DECLARE_METATYPE(zc_status_frame_1_t)
Q_DECLARE_METATYPE(zc_status_frame_2_t)

Q_DECLARE_METATYPE(vobc_header_info_t)
Q_DECLARE_METATYPE(onboard_request_respond_t)
Q_DECLARE_METATYPE(onboard_unregister_rsq_t)
Q_DECLARE_METATYPE(special_control_cmd_t)

/*ZC table enum struct*/
typedef enum _zc_table_t{
    ZC_CI_LS,
    ZC_CI_SP,
    ZC_CI_PSLR,
    ZC_ATS_TVC,
    ZC_ATS_TEC,
    ZC_ATS_TS,
    ZC_VOBC_TC,
    ZC_VOBC_ARLR,
    ZC_VOBC_ALR,
    ZC_VOBC_SCM,
    ZC_MONITOR,
}zc_table_t;

/****************  ci_convert_data  ****************/
DCLR_TAB(stream_header_destbl, var_item_t);
DCLR_TAB(ci_header_destbl, var_item_t);
DCLR_TAB(logicTrack_destbl, var_item_t);
DCLR_TAB(signalClose_destbl, var_item_t);
DCLR_TAB(routeUnlockRsq_destbl, var_item_t);

DCLR_TAB(ats_header_destbl, var_item_t);
DCLR_TAB(zc_tsr_verify_frame_1_destbl, var_item_t);
DCLR_TAB(zc_tsr_verify_frame_2_destbl, var_item_t);
DCLR_TAB(zc_tsr_exeute_frame_1_destbl, var_item_t);
DCLR_TAB(zc_tsr_exeute_frame_2_destbl, var_item_t);
DCLR_TAB(zc_status_frame_1_destbl, var_item_t);
DCLR_TAB(zc_status_frame_2_destbl, var_item_t);

DCLR_TAB(vobc_header_destbl, var_item_t);
DCLR_TAB(onboard_control_1_destbl, var_item_t);
DCLR_TAB(onboard_control_2_destbl, var_item_t);
DCLR_TAB(onboard_control_3_destbl, var_item_t);
DCLR_TAB(switch_num_destbl, var_item_t);
DCLR_TAB(switch_status_destbl, var_item_t);
DCLR_TAB(psd_num_destbl, var_item_t);
DCLR_TAB(psd_status_destbl, var_item_t);
DCLR_TAB(esb_num_destbl, var_item_t);
DCLR_TAB(esb_status_destbl, var_item_t);
DCLR_TAB(temp_speed_num_destbl, var_item_t);
DCLR_TAB(temp_speed_status_destbl, var_item_t);
DCLR_TAB(onboard_request_respond_destbl, var_item_t);
DCLR_TAB(onboard_unregister_rsq_destbl, var_item_t);
DCLR_TAB(special_control_destbl, var_item_t);

DCLR_TAB(zc_monitor_info_t_convert, var_item_t);

#endif // ZC_CI_PARSE_H


