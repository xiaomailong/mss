#include "atsprocess.h"

#include "ats_data.h"
#include "mssdatadefine.h"
#include "mssdbconfig.h"

#define ATS_PROCESS_DEBUG_ENABLED 0
#if ATS_PROCESS_DEBUG_ENABLED
#define ATS_PROCESS_LOG_ENTRY() qDebug("Entry")
#define ATS_PROCESS_DEBUG       qDebug
#define ATS_PROCESS_INFO        qInfo
#define ATS_PROCESS_WARN        qWarning
#else
#define ATS_PROCESS_LOG_ENTRY()
#define ATS_PROCESS_DEBUG       QT_NO_QDEBUG_MACRO
#define ATS_PROCESS_INFO        QT_NO_QDEBUG_MACRO
#define ATS_PROCESS_WARN        QT_NO_QDEBUG_MACRO
#endif

#define ATS_PROCESS_MIN_ROWDATA_LEN (0x1d + 0x2 + 0x2)

AtsProcess::AtsProcess(QObject *parent) : QObject(parent), connectName("atsprocess")
{
    ATS_PROCESS_LOG_ENTRY();
    dataBaseHandler = NULL;
    queryHandler = NULL;
}

bool AtsProcess::openDataBase()
{
    ATS_PROCESS_LOG_ENTRY();
    dataBaseHandler = new QSqlDatabase(QSqlDatabase::addDatabase(MSS_DB_DRIVER, connectName));
    if(dataBaseHandler == NULL)
    {
        goto err;
    }
    dataBaseHandler->setHostName(MSS_DB_HOST_NAME);
    dataBaseHandler->setPort(MSS_DB_PORT);
    dataBaseHandler->setUserName(MSS_DB_USER);
    dataBaseHandler->setPassword(MSS_DB_PASSWORD);
    dataBaseHandler->setDatabaseName(MSS_DB_NAME);
    if(!dataBaseHandler->open())
    {
        qWarning("Failed!!!!");
        goto open_db_err;
    }
    else
    {
        qInfo("Success!!!!");
    }
    queryHandler = new QSqlQuery(*dataBaseHandler);
    if(queryHandler == NULL)
    {
        goto new_query_err;
    }
    return true;

new_query_err:
    dataBaseHandler->close();
open_db_err:
    delete dataBaseHandler;
    dataBaseHandler = NULL;
err:
    QSqlDatabase::removeDatabase(connectName);
    return false;
}

bool AtsProcess::createTable(const QString& queryStr)
{
    ATS_PROCESS_LOG_ENTRY();
    return queryHandler->exec(queryStr);
}

void AtsProcess::closeDataBase()
{
    ATS_PROCESS_LOG_ENTRY();
    if(dataBaseHandler)
    {
        dataBaseHandler->close();
        delete dataBaseHandler;
        QSqlDatabase::removeDatabase(connectName);
        dataBaseHandler = NULL;
    }
    if(queryHandler)
    {
        delete queryHandler;
        queryHandler = NULL;
    }
}
void AtsProcess::start()
{
    bool ret = false;
    ATS_PROCESS_LOG_ENTRY();
    if(openDataBase())
    {
        do {
            ret = createTable("create table if not exists "
                           "ats_vobc_heartbeat(id bigint unsigned primary key auto_increment, "
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "year tinyint unsigned, month tinyint unsigned, date tinyint unsigned, "
                           "hour tinyint unsigned, minute tinyint unsigned, second tinyint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_vobc_ato_cmd(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "service_id smallint unsigned, line_id smallint unsigned, next_zc_id int unsigned, "
                           "next_ci_id int unsigned, next_ats_id int unsigned, cargroupline_id smallint unsigned, "
                           "cargroup_id smallint unsigned, sourceline_id smallint unsigned, trainnum_id smallint unsigned, "
                           "destination_track_id smallint unsigned, destination_id int unsigned, plan_traffic_direction tinyint unsigned, "
                           "next_skip_stop_id smallint unsigned, station_stop_time smallint unsigned, next_skip_stop_operation tinyint unsigned, "
                           "nc_interval_operation smallint unsigned, detain_operation tinyint unsigned, reentry_operation tinyint unsigned, "
                           "back_indication tinyint unsigned, gating_strategy tinyint unsigned, reserved_field int unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_ci_heartbeat(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "year tinyint unsigned, month tinyint unsigned, date tinyint unsigned, "
                           "hour tinyint unsigned, minute tinyint unsigned, second tinyint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }
            //only save one cmd data
            ret = createTable("create table if not exists "
                           "ats_ci_cmd(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "cmd_cnt tinyint unsigned, cmd_type tinyint unsigned, device_id int unsigned, "
                           "device_type tinyint unsigned, reserved_field tinyint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_ci_status(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "main_standby_sts tinyint unsigned, ato_req_rsp tinyint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_zc_heartbeat(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "year tinyint unsigned, month tinyint unsigned, date tinyint unsigned, "
                           "hour tinyint unsigned, minute tinyint unsigned, second tinyint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_zc_tsr_validate(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "tmp_speed_limit tinyint unsigned, logic_track_cnt smallint unsigned, logic_track_id smallint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_zc_tsr_exec_cmd(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "tmp_speed_limit tinyint unsigned, logic_track_cnt smallint unsigned, logic_track_id smallint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_zc_tsr_on_confirm(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "zc_id smallint unsigned, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }

            ret = createTable("create table if not exists "
                           "ats_mss_alarm(id bigint unsigned primary key auto_increment,"
                           "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                           "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                           "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                           "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                           "msg_len smallint unsigned, msg_type smallint unsigned, "
                           "sys_id int, dev_type int, dev_id int, "
                           "dev_local int, alarm_type int, alarm_subtype int, "
                           "alarm_level int, alarm_code int, "
                           "rawdata blob)");
            if(!ret)
            {
                break;
            }
        }while(0);

        if(!ret)
        {
            printDataBaseError();
            emit error(TableCreateError);
        }
        else
        {
            emit started();
        }
    }
    else
    {
        emit error(DataBaseOpenError);
    }
}

void AtsProcess::stop()
{
    ATS_PROCESS_LOG_ENTRY();
    closeDataBase();
}

AtsProcess::~AtsProcess()
{
    ATS_PROCESS_LOG_ENTRY();
}

bool AtsProcess::isDataBaseReady()
{
    return (dataBaseHandler != NULL) ? true : false;
}

void AtsProcess::printDataBaseError()
{
    if(!isDataBaseReady())
    {
        ATS_PROCESS_WARN("DB not ready!!!!");
    }
    else
    {
        ATS_PROCESS_WARN()<<queryHandler->lastError();
    }
}
bool AtsProcess::insertAtsZcHeartBeatEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_zc_heartbeat_t& atsZcHeartBeat,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_zc_heartbeat(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "year, month, date, "
                  "hour, minute, second, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsZcHeartBeat.year);
    queryHandler->addBindValue(atsZcHeartBeat.month);
    queryHandler->addBindValue(atsZcHeartBeat.date);
    queryHandler->addBindValue(atsZcHeartBeat.hour);
    queryHandler->addBindValue(atsZcHeartBeat.minute);
    queryHandler->addBindValue(atsZcHeartBeat.second);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}

bool AtsProcess::insertAtsCiHeartBeatEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_ci_heartbeat_t& atsCiHeartBeat,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_ci_heartbeat(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "year, month, date, "
                  "hour, minute, second, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsCiHeartBeat.year);
    queryHandler->addBindValue(atsCiHeartBeat.month);
    queryHandler->addBindValue(atsCiHeartBeat.date);
    queryHandler->addBindValue(atsCiHeartBeat.hour);
    queryHandler->addBindValue(atsCiHeartBeat.minute);
    queryHandler->addBindValue(atsCiHeartBeat.second);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}

bool AtsProcess::insertAtsVobcHeartBeatEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_vobc_heartbeat_t& atsVobcHeartBeat,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_vobc_heartbeat(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "year, month, date, "
                  "hour, minute, second, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsVobcHeartBeat.year);
    queryHandler->addBindValue(atsVobcHeartBeat.month);
    queryHandler->addBindValue(atsVobcHeartBeat.date);
    queryHandler->addBindValue(atsVobcHeartBeat.hour);
    queryHandler->addBindValue(atsVobcHeartBeat.minute);
    queryHandler->addBindValue(atsVobcHeartBeat.second);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}


bool AtsProcess::insertAtsZcTsrValidateEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_zc_tsr_validate_t& atsZcTsrValidateHeader,
                                                  const ats_zc_tsr_logic_track_data_t& atsZcTsrLogicTrackData,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_zc_tsr_validate(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "tmp_speed_limit, logic_track_cnt, logic_track_id, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsZcTsrValidateHeader.tmp_speed_limit);
    queryHandler->addBindValue(atsZcTsrValidateHeader.logic_track_cnt);
    queryHandler->addBindValue(atsZcTsrLogicTrackData.logic_track_id);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}


bool AtsProcess::insertAtsZcTsrExecCmdEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_zc_tsr_exec_cmd_t& atsZcTsrExecCmdHeader,
                                                  const ats_zc_tsr_logic_track_data_t& atsZcTsrLogicTrackData,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_zc_tsr_exec_cmd(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "tmp_speed_limit, logic_track_cnt, logic_track_id, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsZcTsrExecCmdHeader.tmp_speed_limit);
    queryHandler->addBindValue(atsZcTsrExecCmdHeader.logic_track_cnt);
    queryHandler->addBindValue(atsZcTsrLogicTrackData.logic_track_id);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}


bool AtsProcess::insertAtsZcTsrOnConfirmEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_zc_tsr_on_confirm_t& atsZcTsrOnConfirm,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_zc_tsr_on_confirm(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "zc_id, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsZcTsrOnConfirm.zc_id);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}


bool AtsProcess::insertAtsCiCmdEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_ci_cmd_t& atsCiCmdHeader,
                                               const ats_ci_cmd_data_t& atsCiCmdData,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_ci_cmd(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "cmd_cnt, cmd_type, device_id, "
                  "device_type, reserved_field, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsCiCmdHeader.cmd_cnt);
    queryHandler->addBindValue(atsCiCmdData.cmd_type);
    queryHandler->addBindValue(atsCiCmdData.device_id);
    queryHandler->addBindValue(atsCiCmdData.device_type);
    queryHandler->addBindValue(atsCiCmdData.reserved_field);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}

bool AtsProcess::insertAtsCiStatusEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_ci_status_t& atsCiStatus,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_ci_status(interface_type, send_id_msg, incept_id_msg, "
                  "edition_control_msg, edition_check_msg, msg_list, "
                  "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                  "msg_len, msg_type, "
                  "main_standby_sts, ato_req_rsp, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsCiStatus.main_standby_sts);
    queryHandler->addBindValue(atsCiStatus.ato_req_rsp);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}

bool AtsProcess::insertAtsVobcAtoCmdEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_vobc_ato_cmd_t& atsVobcAtoCmd,
                                               const quint8* buf, quint16 len)
{
    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_vobc_ato_cmd(interface_type, send_id_msg, incept_id_msg, "
                    "edition_control_msg, edition_check_msg, msg_list, "
                    "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                    "msg_len, msg_type, "
                    "service_id, line_id, next_zc_id, "
                    "next_ci_id, next_ats_id, cargroupline_id, "
                    "cargroup_id, sourceline_id, trainnum_id, "
                    "destination_track_id, destination_id, plan_traffic_direction, "
                    "next_skip_stop_id, station_stop_time, next_skip_stop_operation, "
                    "nc_interval_operation, detain_operation, reentry_operation, "
                    "back_indication, gating_strategy, reserved_field, "
                    "rawdata) "
                    "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsVobcAtoCmd.service_id);
    queryHandler->addBindValue(atsVobcAtoCmd.line_id);
    queryHandler->addBindValue(atsVobcAtoCmd.next_zc_id);
    queryHandler->addBindValue(atsVobcAtoCmd.next_ci_id);
    queryHandler->addBindValue(atsVobcAtoCmd.next_ats_id);
    queryHandler->addBindValue(atsVobcAtoCmd.cargroupline_id);
    queryHandler->addBindValue(atsVobcAtoCmd.cargroup_id);
    queryHandler->addBindValue(atsVobcAtoCmd.sourceline_id);
    queryHandler->addBindValue(atsVobcAtoCmd.trainnum_id);
    queryHandler->addBindValue(atsVobcAtoCmd.destination_track_id);
    queryHandler->addBindValue(atsVobcAtoCmd.destination_id);
    queryHandler->addBindValue(atsVobcAtoCmd.plan_traffic_direction);
    queryHandler->addBindValue(atsVobcAtoCmd.next_skip_stop_id);
    queryHandler->addBindValue(atsVobcAtoCmd.station_stop_time);
    queryHandler->addBindValue(atsVobcAtoCmd.next_skip_stop_operation);
    queryHandler->addBindValue(atsVobcAtoCmd.nc_interval_operation);
    queryHandler->addBindValue(atsVobcAtoCmd.detain_operation);
    queryHandler->addBindValue(atsVobcAtoCmd.reentry_operation);
    queryHandler->addBindValue(atsVobcAtoCmd.back_indication);
    queryHandler->addBindValue(atsVobcAtoCmd.gating_strategy);
    queryHandler->addBindValue(atsVobcAtoCmd.reserved_field);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}

bool AtsProcess::insertAtsMssAlarmEntry(const ats_common_header_t& atsCommonHeader,
                                               const ats_app_header_t& atsAppHeader,
                                               const ats_mss_alarm_t& atsMssAlarm,
                                               const quint8* buf, quint16 len)
{

    ATS_PROCESS_LOG_ENTRY();
    if(!isDataBaseReady())
    {
        return false;
    }
    queryHandler->prepare("insert into ats_mss_alarm(interface_type, send_id_msg, incept_id_msg, "
                    "edition_control_msg, edition_check_msg, msg_list, "
                    "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                    "msg_len, msg_type, "
                    "sys_id, dev_type, dev_id, "
                    "dev_local, alarm_type, alarm_subtype, "
                    "alarm_level, alarm_code, "
                    "rawdata) "
                    "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    queryHandler->addBindValue(atsCommonHeader.interface_type);
    queryHandler->addBindValue(atsCommonHeader.send_id_msg);
    queryHandler->addBindValue(atsCommonHeader.incept_id_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_control_msg);
    queryHandler->addBindValue(atsCommonHeader.edition_check_msg);
    queryHandler->addBindValue(atsCommonHeader.msg_list);
    queryHandler->addBindValue(atsCommonHeader.com_cycle);
    queryHandler->addBindValue(atsCommonHeader.opposite_msg_list);
    queryHandler->addBindValue(atsCommonHeader.smsg_self_list);
    queryHandler->addBindValue(atsCommonHeader.pro_edition);
    queryHandler->addBindValue(atsAppHeader.msg_len);
    queryHandler->addBindValue(atsAppHeader.msg_type);
    queryHandler->addBindValue(atsMssAlarm.sys_id);
    queryHandler->addBindValue(atsMssAlarm.dev_type);
    queryHandler->addBindValue(atsMssAlarm.dev_id);
    queryHandler->addBindValue(atsMssAlarm.dev_local);
    queryHandler->addBindValue(atsMssAlarm.alarm_type);
    queryHandler->addBindValue(atsMssAlarm.alarm_subtype);
    queryHandler->addBindValue(atsMssAlarm.alarm_level);
    queryHandler->addBindValue(atsMssAlarm.alarm_code);
    queryHandler->addBindValue(QByteArray::fromRawData(reinterpret_cast<const char *>(buf),len));
    return queryHandler->exec();
}

bool AtsProcess::isBufValid(quint8* buf, quint16 len)
{
    if(buf != NULL && len > ATS_PROCESS_MIN_ROWDATA_LEN)
    {
        return true;
    }
    return false;
}

void AtsProcess::onDeviceDataReceived(quint8* buf, quint16 len)
{
    quint16 unpackLength = 0;
    quint16 checkLength = 0;
    bool ret = false;
    ats_common_header_t atsCommonHeader;
    ats_app_header_t atsAppHeader;
    ats_mss_alarm_t *alarmInfo =NULL;
    ATS_PROCESS_LOG_ENTRY();
    if(!isBufValid(buf, len))
    {
        goto err_buf_invalid;
    }
    checkLength = b2v_bytes_to_var(buf,
                                   (quint8 *)(&atsCommonHeader),
                                   ats_common_header_cv_table,
                                   ats_common_header_cv_table_len);
    unpackLength += checkLength;

    switch(atsCommonHeader.interface_type)
    {
    case ATS_MSS_INTERFACE:
    {
        if(atsCommonHeader.send_id_msg == ID_MESSAGE_VOBC)
        {
            emit vobcDeviceDataReceived(buf, len);
            return;
        }
        checkLength = b2v_bytes_to_var(buf + unpackLength,
                                       (quint8 *)(&atsAppHeader),
                                       ats_app_header_cv_table,
                                       ats_app_header_cv_table_len);
        if((unpackLength + atsAppHeader.msg_len + 2) > len)
        {
            goto err_buf_invalid;
        }
        unpackLength += checkLength;
        switch(atsAppHeader.msg_type){
        case ATS_MSS_ALARM_MSG_TYPE:
        {
            ats_mss_alarm_t atsMssAlarm;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsMssAlarm),
                                           ats_mss_alarm_cv_table,
                                           ats_mss_alarm_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsMssAlarmEntry(atsCommonHeader,
                                              atsAppHeader,
                                              atsMssAlarm,
                                              buf, len);
                if(ret)
                {
                    alarmInfo = new ats_mss_alarm_t;
                    memcpy(alarmInfo, &atsMssAlarm, sizeof(ats_mss_alarm_t));
                }
            }
        }
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
    if(unpackLength == len)
    {
        if(!ret)
        {
            printDataBaseError();
            emit error(EntryInsertError);
        }
        else
        {
            emit deviceDataReceived(alarmInfo);
            vobc_subsys_msg_t alarmInfo1;
            alarmInfo1.msg_type = ATS_MSS_ALARM_MSG_TYPE;
            alarmInfo1.sys_id = alarmInfo->sys_id;
            alarmInfo1.dev_type = alarmInfo->dev_type;
            alarmInfo1.dev_id = alarmInfo->dev_id;
            alarmInfo1.dev_local = alarmInfo->dev_local;
            alarmInfo1.alarm_type = alarmInfo->alarm_type;
            alarmInfo1.alarm_subtype = alarmInfo->alarm_subtype;
            alarmInfo1.alarm_level = alarmInfo->alarm_level;
            alarmInfo1.alarm_code = alarmInfo->alarm_code;
            emit deviceDataReceived1(alarmInfo1);
        }
        delete[]buf;
        return;
    }
err_buf_invalid:
    ATS_PROCESS_WARN("Error detected!!! unpackLength 0x%x, buf_len 0x%x", unpackLength, len);
    emit error(DataInvalidError);
    if(buf != NULL)
    {
        delete[]buf;
    }
}

void AtsProcess::onReceiveData(quint8* buf, quint16 len)
{
    quint16 unpackLength = 0;
    quint16 checkLength = 0;
    bool ret = false;
    ats_common_header_t atsCommonHeader;
    ats_app_header_t atsAppHeader;
    ATS_PROCESS_LOG_ENTRY();
    if(!isBufValid(buf, len))
    {
        goto err_buf_invalid;
    }
    checkLength = b2v_bytes_to_var(buf,
                                   (quint8 *)(&atsCommonHeader),
                                   ats_common_header_cv_table,
                                   ats_common_header_cv_table_len);
    unpackLength += checkLength;

    switch(atsCommonHeader.interface_type)
    {
    case ATS_ZC_INTERFACE:
    {
        checkLength = b2v_bytes_to_var(buf + unpackLength,
                                       (quint8 *)(&atsAppHeader),
                                       ats_app_header_cv_table,
                                       ats_app_header_cv_table_len);
        if((unpackLength + atsAppHeader.msg_len + 2) > len)
        {
            goto err_buf_invalid;
        }
        unpackLength += checkLength;
        switch(atsAppHeader.msg_type){
        case ATS_ZC_HEARTBEAT_MSG_TYPE:
        {
            ats_zc_heartbeat_t atsZcHeartBeat;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsZcHeartBeat),
                                           ats_zc_heartbeat_cv_table,
                                           ats_zc_heartbeat_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsZcHeartBeatEntry(atsCommonHeader,
                                              atsAppHeader,
                                              atsZcHeartBeat,
                                              buf, len);
            }
        }
            break;
        case ATS_ZC_TSR_VALIDATE_MSG_TYPE:
        {
            ats_zc_tsr_validate_t atsZcTsrValidateHeader;
            ats_zc_tsr_logic_track_data_t atsZcTsrLogicTrackData;
            int i = 0;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsZcTsrValidateHeader),
                                           ats_zc_tsr_validate_cv_table,
                                           ats_zc_tsr_validate_cv_table_len);
            unpackLength += checkLength;
            for(i = 0; i < atsZcTsrValidateHeader.logic_track_cnt; i++)
            {
                checkLength = b2v_bytes_to_var(buf + unpackLength,
                                               (quint8 *)(&atsZcTsrLogicTrackData),
                                               ats_zc_tsr_logic_track_data_cv_table,
                                               ats_zc_tsr_logic_track_data_cv_table_len);
                unpackLength += checkLength;
            }
            if(unpackLength == len)
            {
                ret = insertAtsZcTsrValidateEntry(atsCommonHeader,
                                                   atsAppHeader,
                                                   atsZcTsrValidateHeader,
                                                   atsZcTsrLogicTrackData,
                                                   buf, len);
            }
        }
            break;
        case ATS_ZC_TSR_EXEC_CMD_MSG_TYPE:
        {
            ats_zc_tsr_exec_cmd_t atsZcTsrExecCmdHeader;
            ats_zc_tsr_logic_track_data_t atsZcTsrLogicTrackData;
            int i = 0;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsZcTsrExecCmdHeader),
                                           ats_zc_tsr_exec_cmd_cv_table,
                                           ats_zc_tsr_exec_cmd_cv_table_len);
            unpackLength += checkLength;
            for(i = 0; i < atsZcTsrExecCmdHeader.logic_track_cnt; i++)
            {
                checkLength = b2v_bytes_to_var(buf + unpackLength, (quint8 *)(&atsZcTsrLogicTrackData), ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
                unpackLength += checkLength;
            }
            if(unpackLength == len)
            {
                ret = insertAtsZcTsrExecCmdEntry(atsCommonHeader,
                                                 atsAppHeader,
                                                 atsZcTsrExecCmdHeader,
                                                 atsZcTsrLogicTrackData,
                                                 buf, len);
            }
        }
            break;
        case ATS_ZC_TSR_ON_CONFIRM_MSG_TYPE:
        {
            ats_zc_tsr_on_confirm_t atsZcTsrOnConfirm;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsZcTsrOnConfirm),
                                           ats_zc_tsr_on_confirm_cv_table,
                                           ats_zc_tsr_on_confirm_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsZcTsrOnConfirmEntry(atsCommonHeader,
                                                   atsAppHeader,
                                                   atsZcTsrOnConfirm,
                                                   buf, len);
            }
        }
            break;
        default:
            break;
        }
    }
        break;
    case ATS_VOBC_INTERFACE:
    {
        checkLength = b2v_bytes_to_var(buf + unpackLength,
                                       (quint8 *)(&atsAppHeader),
                                       ats_app_header_cv_table,
                                       ats_app_header_cv_table_len);
        if((unpackLength + atsAppHeader.msg_len + 2) > len)
        {
            goto err_buf_invalid;
        }
        unpackLength += checkLength;
        switch(atsAppHeader.msg_type)
        {
        case ATS_VOBC_HEARTBEAT_MSG_TYPE:
        {
            ats_vobc_heartbeat_t atsVobcHeartBeat;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsVobcHeartBeat),
                                           ats_vobc_heartbeat_cv_table,
                                           ats_vobc_heartbeat_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsVobcHeartBeatEntry(atsCommonHeader,
                                              atsAppHeader,
                                              atsVobcHeartBeat,
                                              buf, len);
            }
        }
            break;
        case ATS_VOBC_ATO_CMD_MSG_TYPE:
        {
            ats_vobc_ato_cmd_t atsVobcAtoCmd;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsVobcAtoCmd),
                                           ats_vobc_ato_cmd_cv_table,
                                           ats_vobc_ato_cmd_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsVobcAtoCmdEntry(atsCommonHeader,
                                              atsAppHeader,
                                              atsVobcAtoCmd,
                                              buf, len);
            }
        }
            break;
        default:
            break;
        }
    }
        break;
    case ATS_CI_INTERFACE:
    {
        checkLength = b2v_bytes_to_var(buf + unpackLength,
                                       (quint8 *)(&atsAppHeader),
                                       ats_app_header_cv_table,
                                       ats_app_header_cv_table_len);
        if((unpackLength + atsAppHeader.msg_len + 2) > len)
        {
            goto err_buf_invalid;
        }
        unpackLength += checkLength;
        switch(atsAppHeader.msg_type)
        {
        case ATS_CI_HEARTBEAT_MSG_TYPE:
        {
            ats_ci_heartbeat_t atsCiHeartBeat;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsCiHeartBeat),
                                           ats_ci_heartbeat_cv_table,
                                           ats_ci_heartbeat_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsCiHeartBeatEntry(atsCommonHeader,
                                              atsAppHeader,
                                              atsCiHeartBeat,
                                              buf, len);
            }
        }
            break;
        case ATS_CI_CMD_MSG_TYPE:
        {
            ats_ci_cmd_t atsCiCmdHeader;
            ats_ci_cmd_data_t atsCiCmdData;
            int i = 0;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsCiCmdHeader),
                                           ats_ci_cmd_cv_table,
                                           ats_ci_cmd_cv_table_len);
            unpackLength += checkLength;
            for(i = 0; i < atsCiCmdHeader.cmd_cnt; i++)
            {
                checkLength = b2v_bytes_to_var(buf + unpackLength,
                                               (quint8 *)(&atsCiCmdData),
                                               ats_ci_cmd_data_cv_table,
                                               ats_ci_cmd_data_cv_table_len);
                unpackLength += checkLength;
            }
            if(unpackLength == len)
            {
                ret = insertAtsCiCmdEntry(atsCommonHeader,
                                        atsAppHeader,
                                        atsCiCmdHeader,
                                        atsCiCmdData,
                                        buf, len);
            }
        }
            break;
        case ATS_CI_RUNNING_STS_MSG_TYPE:
        {
            ats_ci_status_t atsCiStatus;
            checkLength = b2v_bytes_to_var(buf + unpackLength,
                                           (quint8 *)(&atsCiStatus),
                                           ats_ci_status_cv_table,
                                           ats_ci_status_cv_table_len);
            unpackLength += checkLength;
            if(unpackLength == len)
            {
                ret = insertAtsCiStatusEntry(atsCommonHeader,
                                           atsAppHeader,
                                           atsCiStatus,
                                           buf, len);
            }
        }
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }
    if(unpackLength == len)
    {
        if(!ret)
        {
            printDataBaseError();
            emit error(EntryInsertError);
        }
        else
        {
            emit dataReceived();
        }
        delete[]buf;
        return;
    }

err_buf_invalid:
    ATS_PROCESS_WARN("Error detected!!! unpackLength 0x%x, buf_len 0x%x", unpackLength, len);
    emit error(DataInvalidError);
    if(buf != NULL)
    {
        delete[]buf;
    }
}
