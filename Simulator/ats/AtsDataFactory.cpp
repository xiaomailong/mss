#include "atsdatafactory.h"
#include "simulatorconfig.h"
#include "simulatorlogconfig.h"
#include "ats_data.h"
#include "mssdatadefine.h"
#include "b2v.h"
#include <QDate>
#include <QTime>

#define BUF_SIZE 256
AtsDataFactory::AtsDataFactory()
{
    ATS_SIMULATOR_LOG_ENTRY();
    atsVobcMsgList = rand() % 0xFFFF;
    atsCiMsgList = rand() % 0xFFFF;
    atsZcMsgList = rand() % 0xFFFF;
    atsMssMsgList = rand() % 0xFFFF;
}

AtsDataFactory::~AtsDataFactory()
{
    ATS_SIMULATOR_LOG_ENTRY();
}


AtsDataFactory& AtsDataFactory::getInstance()
{
    static AtsDataFactory instance;
    return instance;
}

void AtsDataFactory::getData(AtsDataType type, quint8**bufPtr, quint16* lenPtr)
{
    quint8* buf = NULL;
    quint16 padLength = 0;
    quint16 checkLength = 0;
    quint16 appHeaderOffset = 0;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    ATS_SIMULATOR_LOG_ENTRY();
    buf = new quint8[BUF_SIZE];
    *bufPtr = buf;
    switch(type){
    case AtsVobcHeartBeatDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_vobc_heartbeat_t heartbeat;
        atsHeader.interface_type = ATS_VOBC_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_VOBC;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsVobcMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_VOBC_HEARTBEAT_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        checkLength = b2v_var_to_bytes((quint8*)(&heartbeat), buf + padLength, ats_vobc_heartbeat_cv_table, ats_vobc_heartbeat_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsVobcAtoCmdDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_vobc_ato_cmd_t atsVobcAtoCmd;
        atsHeader.interface_type = ATS_VOBC_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_VOBC;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsVobcMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_VOBC_ATO_CMD_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsVobcAtoCmd.service_id = ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.line_id =  ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.next_zc_id = ((quint32)(rand())) % 0xFFFFFFFF;
        atsVobcAtoCmd.next_ci_id = ((quint32)(rand())) % 0xFFFFFFFF;
        atsVobcAtoCmd.next_ats_id = ((quint32)(rand())) % 0xFFFFFFFF;
        atsVobcAtoCmd.cargroupline_id = ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.cargroup_id = (((quint16)(rand())) % 999 ) + 1;
        atsVobcAtoCmd.sourceline_id = ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.trainnum_id = (((quint16)(rand())) % 9999 ) + 1;
        atsVobcAtoCmd.destination_track_id = ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.destination_id = ((quint32)(rand())) % 0xFFFFFFFF;
        atsVobcAtoCmd.plan_traffic_direction = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
        atsVobcAtoCmd.next_skip_stop_id = ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.station_stop_time = ((quint16)(rand())) % 0xFFFF;
        atsVobcAtoCmd.next_skip_stop_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
        atsVobcAtoCmd.nc_interval_operation = 0;
        atsVobcAtoCmd.detain_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
        atsVobcAtoCmd.reentry_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
        atsVobcAtoCmd.back_indication = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
        atsVobcAtoCmd.gating_strategy = ((rand() % 2 ) == 0) ? 0x55 : 0xCC;
        atsVobcAtoCmd.reserved_field = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsVobcAtoCmd), buf + padLength, ats_vobc_ato_cmd_cv_table, ats_vobc_ato_cmd_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsCiHeartBeatDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_ci_heartbeat_t heartbeat;
        atsHeader.interface_type = ATS_CI_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_CI;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsCiMsgList++;
        atsHeader.com_cycle = 8;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_CI_HEARTBEAT_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        checkLength = b2v_var_to_bytes((quint8*)(&heartbeat), buf + padLength, ats_ci_heartbeat_cv_table, ats_ci_heartbeat_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsCiCmdDataType:
    {
        quint16 temp_len = 0;
        int i = 0;
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_ci_cmd_t atsCiCmd;
        ats_ci_cmd_data_t atsCiCmdData;
        atsHeader.interface_type = ATS_CI_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_CI;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsCiMsgList;
        atsHeader.com_cycle = 8;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_CI_CMD_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsCiCmd.cmd_cnt = (((quint8) (rand())) % 4) + 1;
        checkLength = b2v_var_to_bytes((quint8*)(&atsCiCmd), buf + padLength, ats_ci_cmd_cv_table, ats_ci_cmd_cv_table_len);
        padLength += checkLength;
        temp_len += checkLength;
        for(i = 0; i < atsCiCmd.cmd_cnt; i++){
            atsCiCmdData.cmd_type = (((quint8) (rand())) % 0x37) + 1;
            atsCiCmdData.device_id = ((quint32)(rand())) % 0xFFFFFFFF;
            atsCiCmdData.device_type = (((quint8) (rand())) % 0x11) + 1;
            atsCiCmdData.reserved_field = 0xFF;
            checkLength = b2v_var_to_bytes((quint8*)(&atsCiCmdData), buf + padLength, ats_ci_cmd_data_cv_table, ats_ci_cmd_data_cv_table_len);
            temp_len += checkLength;
            padLength += checkLength;
        }
        atsAppHeader.msg_len = 2 + temp_len;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsCiStatusDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_ci_status_t atsCiStatus;
        atsHeader.interface_type = ATS_CI_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_CI;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsCiMsgList;
        atsHeader.com_cycle = 8;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_CI_RUNNING_STS_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsCiStatus.main_standby_sts = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
        atsCiStatus.ato_req_rsp = ((rand() % 2 ) == 0) ? 0x55 : 0xCC;
        checkLength = b2v_var_to_bytes((quint8*)(&atsCiStatus), buf + padLength, ats_ci_status_cv_table, ats_ci_status_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsZcHeartBeatDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_zc_heartbeat_t heartbeat;
        atsHeader.interface_type = ATS_ZC_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_ZC;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsZcMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_ZC_HEARTBEAT_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        checkLength = b2v_var_to_bytes((quint8*)(&heartbeat), buf + padLength, ats_zc_heartbeat_cv_table, ats_zc_heartbeat_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsZcTsrValidateDataType:
    {
        quint16 temp_len = 0;
        int i = 0;
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_zc_tsr_validate_t atsZcTsrValidate;
        ats_zc_tsr_logic_track_data_t atsZcTsrLogicTrackData;
        atsHeader.interface_type = ATS_ZC_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_ZC;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsZcMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_ZC_TSR_VALIDATE_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsZcTsrValidate.tmp_speed_limit = ((rand() % 2 ) == 0) ? 2 : 0xFF;
        atsZcTsrValidate.logic_track_cnt = (((quint8) (rand())) % 4) + 1;
        checkLength = b2v_var_to_bytes((quint8*)(&atsZcTsrValidate), buf + padLength, ats_zc_tsr_validate_cv_table, ats_zc_tsr_validate_cv_table_len);
        padLength += checkLength;
        temp_len += checkLength;
        for(i = 0; i < atsZcTsrValidate.logic_track_cnt; i++){
            atsZcTsrLogicTrackData.logic_track_id = ((quint16)(rand())) % 0xFFFF;
            checkLength = b2v_var_to_bytes((quint8*)(&atsZcTsrLogicTrackData), buf + padLength, ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
            temp_len += checkLength;
            padLength += checkLength;
        }
        atsAppHeader.msg_len = 2 + temp_len;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsZcTsrExecCmdDataType:
    {
        quint16 temp_len = 0;
        int i = 0;
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_zc_tsr_exec_cmd_t ats_zc_tsr_exec_cmd;
        ats_zc_tsr_logic_track_data_t atsZcTsrLogicTrackData;
        atsHeader.interface_type = ATS_ZC_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_ZC;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsZcMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_ZC_TSR_EXEC_CMD_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        ats_zc_tsr_exec_cmd.tmp_speed_limit = ((rand() % 2 ) == 0) ? 2 : 0xFF;
        ats_zc_tsr_exec_cmd.logic_track_cnt = (((quint8) (rand())) % 4) + 1;
        checkLength = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_exec_cmd), buf + padLength, ats_zc_tsr_exec_cmd_cv_table, ats_zc_tsr_exec_cmd_cv_table_len);
        padLength += checkLength;
        temp_len += checkLength;
        for(i = 0; i < ats_zc_tsr_exec_cmd.logic_track_cnt; i++){
            atsZcTsrLogicTrackData.logic_track_id = ((quint16)(rand())) % 0xFFFF;
            checkLength = b2v_var_to_bytes((quint8*)(&atsZcTsrLogicTrackData), buf + padLength, ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
            temp_len += checkLength;
            padLength += checkLength;
        }
        atsAppHeader.msg_len = 2 + temp_len;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsZcTsrOnConfirmDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_zc_tsr_on_confirm_t atsZcTsrOnConfirm;
        atsHeader.interface_type = ATS_ZC_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_ZC;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsZcMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_ZC_TSR_ON_CONFIRM_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsZcTsrOnConfirm.zc_id = ((quint16)(rand())) % 0xFFFF;
        checkLength = b2v_var_to_bytes((quint8*)(&atsZcTsrOnConfirm), buf + padLength, ats_zc_tsr_on_confirm_cv_table, ats_zc_tsr_on_confirm_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case AtsMssAlarmDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_mss_alarm_t atsMssAlarm;
        atsHeader.interface_type = ATS_MSS_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_MSS;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsMssMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsMssAlarm.sys_id = ID_MESSAGE_ATS;
        atsMssAlarm.dev_type = ((quint8)(rand())) % 0x04;
        atsMssAlarm.dev_id = ((quint16)(rand())) % 0xFFFF;
        atsMssAlarm.dev_local = ((quint8)(rand())) % 0x04;
        atsMssAlarm.alarm_type = ((quint8)(rand())) % 0x02;
        atsMssAlarm.alarm_subtype = ((quint8)(rand())) % 0x04;
        atsMssAlarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
        atsMssAlarm.alarm_code = ((quint16)(rand())) % 0xFFFF;
        checkLength = b2v_var_to_bytes((quint8*)(&atsMssAlarm), buf + padLength, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case VobcMssAlarmDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_mss_alarm_t atsMssAlarm;
        atsHeader.interface_type = ATS_MSS_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_VOBC;
        atsHeader.incept_id_msg = ID_MESSAGE_MSS;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsMssMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        atsMssAlarm.sys_id = ID_MESSAGE_ATS;
        atsMssAlarm.dev_type = ((quint8)(rand())) % 0x04;
        atsMssAlarm.dev_id = ((quint16)(rand())) % 0xFFFF;
        atsMssAlarm.dev_local = ((quint8)(rand())) % 0x04;
        atsMssAlarm.alarm_type = ((quint8)(rand())) % 0x02;
        atsMssAlarm.alarm_subtype = ((quint8)(rand())) % 0x04;
        atsMssAlarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
        atsMssAlarm.alarm_code = ((quint16)(rand())) % 0xFFFF;
        checkLength = b2v_var_to_bytes((quint8*)(&atsMssAlarm), buf + padLength, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    default:
    {
        padLength = BUF_SIZE;
    }
        break;
    }
    *lenPtr = padLength;
}


void AtsDataFactory::getData(AtsDataType type, const void* extraInfo, quint8**bufPtr, quint16* lenPtr)
{
    quint8* buf = NULL;
    quint16 padLength = 0;
    quint16 checkLength = 0;
    quint16 appHeaderOffset = 0;
    ATS_SIMULATOR_LOG_ENTRY();
    buf = new quint8[BUF_SIZE];
    *bufPtr = buf;
    switch(type){
    case AtsMssAlarmDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_mss_alarm_t atsMssAlarm;

        atsHeader.interface_type = ATS_MSS_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_ATS;
        atsHeader.incept_id_msg = ID_MESSAGE_MSS;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsMssMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        memcpy(&atsMssAlarm, extraInfo, sizeof(ats_mss_alarm_t));
        atsMssAlarm.sys_id = ID_MESSAGE_ATS;
        checkLength = b2v_var_to_bytes((quint8*)(&atsMssAlarm), buf + padLength, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    case VobcMssAlarmDataType:
    {
        ats_common_header_t atsHeader;
        ats_app_header_t atsAppHeader;
        ats_mss_alarm_t atsMssAlarm;
        atsHeader.interface_type = ATS_MSS_INTERFACE;
        atsHeader.send_id_msg = ID_MESSAGE_VOBC;
        atsHeader.incept_id_msg = ID_MESSAGE_MSS;
        atsHeader.edition_control_msg = 0xFF;
        atsHeader.edition_check_msg = 0xFFFFFFFF;
        atsHeader.msg_list = atsMssMsgList++;
        atsHeader.com_cycle = 5;
        atsHeader.pro_edition = 3;
        checkLength = b2v_var_to_bytes((quint8*)(&atsHeader), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        padLength += checkLength;
        appHeaderOffset = padLength;
        atsAppHeader.msg_type = ATS_MSS_ALARM_MSG_TYPE;
        atsAppHeader.msg_len = 0;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + padLength, ats_app_header_cv_table, ats_app_header_cv_table_len);
        padLength += checkLength;
        memcpy(&atsMssAlarm, extraInfo, sizeof(ats_mss_alarm_t));
        atsMssAlarm.sys_id = ID_MESSAGE_VOBC;
        checkLength = b2v_var_to_bytes((quint8*)(&atsMssAlarm), buf + padLength, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
        padLength += checkLength;
        atsAppHeader.msg_len = 2 + checkLength;
        checkLength = b2v_var_to_bytes((quint8*)(&atsAppHeader), buf + appHeaderOffset, ats_app_header_cv_table, ats_app_header_cv_table_len);
    }
        break;
    default:
    {
        padLength = BUF_SIZE;
    }
        break;
    }
    *lenPtr = padLength;
}
