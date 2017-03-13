#include "vobcdcsservice.h"
#include "../../vobcuicommon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "unifw.h"
#include "b2v.h"
#include "mssdatadefine.h"
#include "vobc_data.h"
#include "mssdbconfig.h"

VobcDcsService::VobcDcsService(QObject *parent) : QObject(parent),
    connectName("VobcDcsDB")
{

}
VobcDcsService::~VobcDcsService()
{

}
void VobcDcsService::startService()
{
    bool ret = false;
    if(openDatabase())
    {
        //create table if not exists
        ret = createTable("create table if not exists "
                "vobc_ats_ato(id int unsigned primary key auto_increment, "
                "time timestamp not null default current_timestamp, "
                "vobc_ats_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
                "msg_len smallint unsigned, msg_type smallint unsigned, service_id smallint unsigned, line_id smallint unsigned, "
                "cargroup_line_id smallint unsigned, cargroup_id smallint unsigned, sourceline_id smallint unsigned, "
                "trainnum_id smallint unsigned, destination_track_id smallint unsigned, destination_id int unsigned, "
                "driver_id smallint unsigned, mode_ato tinyint unsigned, nc_interval_operation smallint unsigned, "
                "status_skipstop tinyint unsigned, status_detain tinyint unsigned, nextstation_id smallint unsigned, "
                "reserved_field int unsigned, rawdata blob)");

        ret = ret && createTable("create table if not exists "
               "vobc_ats_train(id int unsigned primary key auto_increment,"
               "time timestamp not null default current_timestamp, "
               "vobc_ats_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
               "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
               "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
               "msg_len smallint unsigned, msg_type smallint unsigned, train_id smallint unsigned, line_id smallint unsigned,"
               "status_train_pos tinyint unsigned, dir_train tinyint unsigned, dir_whell tinyint unsigned, "
               "head_estimate_logic_id smallint unsigned, head_estimate_offset int unsigned, tail_estimate_logic_id smallint unsigned, "
               "tail_estimate_offset int unsigned, over_read smallint unsigned, lack_read smallint unsigned,"
               "mode_atp tinyint unsigned, mode_cbtc tinyint unsigned, status_train_complete tinyint unsigned, "
               "status_emerg_brake tinyint unsigned, status_ar tinyint unsigned, vel_msg smallint unsigned, "
               "status_psd tinyint unsigned, status_trainstoparea tinyint unsigned, status_stoptrain tinyint unsigned, "
               "status_unmanned_reentry tinyint unsigned, mode_preselect tinyint unsigned, reasonof_emerg_brake tinyint unsigned, "
               "vel_emerg_brake smallint unsigned, vel_recommend smallint unsigned, pos_security int unsigned, "
               "sec_track_id smallint unsigned, sec_track_offset int unsigned, pos_obstacle int unsigned, "
               "obs_track_id smallint unsigned, obs_track_offset int unsigned, reserved_field int unsigned, rawdata blob)");

        ret = ret && createTable("create table if not exists "
               "vobc_ats_alarm(id int unsigned primary key auto_increment,"
               "time timestamp not null default current_timestamp, "
               "vobc_ats_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
               "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
               "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
               "msg_len smallint unsigned, msg_type smallint unsigned, train_id smallint unsigned, alarm_ato tinyint unsigned, "
               "alarm_btm tinyint unsigned, alarm_vel_ui tinyint unsigned, alarm_radar tinyint unsigned, "
               "alarm_train_com tinyint unsigned, alarm_speed_measure tinyint unsigned, alarm_acceleration_measure tinyint unsigned, "
               "alarm_reserved1 tinyint unsigned, alarm_reserved2 tinyint unsigned, alarm_atp tinyint unsigned, "
               "board_info1 tinyint unsigned, board_info2 tinyint unsigned, board_info3 tinyint unsigned,"
               "board_info4 tinyint unsigned, board_info5 tinyint unsigned, board_info6 tinyint unsigned,"
               "rawdata blob)");

        ret = ret && createTable("create table if not exists "
               "vobc_ats_check(id int unsigned primary key auto_increment,"
               "time timestamp not null default current_timestamp, "
               "vobc_ats_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
               "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
               "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
               "msg_len smallint unsigned, msg_type smallint unsigned, train_id smallint unsigned, status_check1 tinyint unsigned, "
               "status_check2 tinyint unsigned, status_check3 tinyint unsigned, status_check4 tinyint unsigned,"
               "status_check5 tinyint unsigned, status_check6 tinyint unsigned, rawdata blob)");

        ret = ret && createTable("create table if not exists "
               "vobc_zc_train(id int unsigned primary key auto_increment,"
               "time timestamp not null default current_timestamp, "
               "vobc_zc_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
               "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
               "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
               "msg_len smallint unsigned, msg_type smallint unsigned, dir tinyint unsigned, active_side tinyint unsigned, "
               "head_estimate_logic_id smallint unsigned, head_estimate_offset int unsigned, tail_estimate_logic_id smallint unsigned, "
               "tail_estimate_offset int unsigned, lack_read smallint unsigned, over_read smallint unsigned, "
               "train_length smallint unsigned, wheel_head_length smallint unsigned, op_mode tinyint unsigned, "
               "drive_mode tinyint unsigned, stop_response tinyint unsigned, stop_area smallint unsigned, "
               "stop_area_offset int unsigned, stop_pos_obstacle smallint unsigned, stop_pos_obs_offset int unsigned, "
               "stop_valid tinyint unsigned, status_reentry tinyint unsigned, status_train_complete tinyint unsigned, "
               "led_unmanned_reentry tinyint unsigned, status_emerg_brake tinyint unsigned, train_speed smallint unsigned, "
               "speed_dir tinyint unsigned, recess_length smallint unsigned, status_trainstoparea tinyint unsigned, "
               "ctl_zcid int unsigned, rawdata blob)");

        ret = ret && createTable("create table if not exists "
               "vobc_zc_register(id int unsigned primary key auto_increment,"
               "time timestamp not null default current_timestamp, "
               "vobc_zc_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
               "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
               "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
               "msg_len smallint unsigned, msg_type smallint unsigned, register_mode tinyint unsigned, log_out_reason tinyint unsigned, "
               "rawdata blob)");

        ret = ret && createTable("create table if not exists "
               "vobc_ci(id int unsigned primary key auto_increment,"
               "time timestamp not null default current_timestamp, "
               "vobc_ci_interface smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
               "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
               "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, pro_edition tinyint unsigned, "
               "nc_data tinyint unsigned, dir_train tinyint unsigned, s_trainstoparea tinyint unsigned, "
               "n_psd_type tinyint unsigned, n_psd tinyint unsigned, nid_psd_1 smallint unsigned, "
               "nc_psd_1 tinyint unsigned, nid_psd_2 smallint unsigned, nc_psd_2 tinyint unsigned, rawdata blob)");
        if(!ret)
        {
            printDatabaseError();
            emit castError(ErrCreateTable);
        }
    }
    else
    {
        printDatabaseError();
        emit castError(ErrOpenDatabase);
    }
}

void VobcDcsService::stopService()
{
    closeDatabase();
}

bool VobcDcsService::openDatabase()
{
    if(!QSqlDatabase::contains(connectName))
    {
        db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,connectName);
    }
    else
    {
        db = QSqlDatabase::database(connectName);
    }

    db.setHostName(MSS_DB_HOST_NAME);
    db.setPort(MSS_DB_PORT);
    db.setDatabaseName(MSS_DB_NAME);
    db.setUserName(MSS_DB_USER);
    db.setPassword(MSS_DB_PASSWORD);
    query = QSqlQuery(db);
    if(!db.open())
    {
        return false;
    }
    return true;
}

bool VobcDcsService::createTable(const QString &queryStr)
{
    return query.exec(queryStr);
}

void VobcDcsService::closeDatabase()
{
    db.close();
}

void VobcDcsService::printDatabaseError()
{
    if(!db.isOpen())
    {
        VOBC_WARN() << "DB is NOT ready!";
        VOBC_WARN() << db.lastError();
    }
    else
    {
        VOBC_WARN() << query.lastError();
        VOBC_WARN() << db.lastError();
    }
}
void VobcDcsService::handleDcsData(quint8 *buf, quint16 len)
{
    vobc_ats_header_t commonHeader;
    quint16 msgOffset = 0;
    quint16 bufSize = 0xFFFF;
    bool ret = false;

    if(NULL == buf)
    {
        VOBC_WARN() << "NULL pointer!!! Exit.";
        emit castError(ErrInvalidArgument);
        return;
    }

    msgOffset = b2v_bytes_to_var(buf,
                                 (quint8 *)&commonHeader,
                                 vobc_common_header_cv_table,
                                 vobc_common_header_cv_table_len);

    switch (commonHeader.vobc_ats_interface) {
    case ATS_VOBC_INTERFACE:  //vobc_ats interface
    {

        vobc_app_header_len_t appLength;
        bufSize = b2v_bytes_to_var_byoffset(buf,
                                  msgOffset,
                                  (quint8 *)&appLength,
                                  vobc_msg_len_cv_table,
                                  vobc_msg_len_cv_table_len);
        //get ATS msg_type
        uint16_t msgType;
        b2v_bytes_to_var_byoffset(buf,
                                  bufSize,
                                  (quint8 *)&msgType,
                                  vobc_ats_msg_type_cv_table,
                                  vobc_ats_msg_type_cv_table_len);

        switch (msgType) {
        //ato state msg
        case VOBC_ATS_ATOSTATE_MSG_TYPE:
        {
            MssVobcAtsAto totalMsg;
            totalMsg.common_header = commonHeader;
            totalMsg.app_len = appLength;
            bufSize= b2v_bytes_to_var_byoffset(buf,
                                               bufSize,
                                               (quint8 *)&totalMsg.datagram,
                                               vobc_ats_ato_cv_table,
                                               vobc_ats_ato_cv_table_len);

            if(bufSize == len)
            {
                ret = insertData(TableAtsAtoState, &totalMsg, buf, bufSize);
            }
        }
            break;
        case VOBC_ATS_TRAIN_MSG_TYPE:
        {
            //train msg
            MssVobcAtsTrain totalMsg;
            totalMsg.common_header = commonHeader;
            totalMsg.app_len = appLength;
            bufSize = b2v_bytes_to_var_byoffset(buf,
                                                bufSize,
                                                (quint8 *)&totalMsg.datagram,
                                                vobc_ats_train_cv_table,
                                                vobc_ats_train_cv_table_len);
            if(bufSize == len)
            {
                ret = insertData(TableAtsTrain, &totalMsg, buf, bufSize);
            }
        }
            break;
        case VOBC_ATS_VEHICLE_ALARM_MSG_TYPE:
        {
            //VEHICLE EQUIPMENT  alarm
            MssVobcAtsAlarm totalMsg;
            totalMsg.common_header = commonHeader;
            totalMsg.app_len = appLength;
            bufSize = b2v_bytes_to_var_byoffset(buf,
                                                bufSize,
                                                (quint8 *)&totalMsg.datagram,
                                                vobc_ats_alarmmsg_cv_table,
                                                vobc_ats_alarmmsg_cv_table_len);
            if(bufSize == len)
            {
                ret = insertData(TableAtsVehicleAlarm, &totalMsg, buf, bufSize);
            }
        }
            break;
        case VOBC_ATS_VEHICLE_DAILY_MSG_TYPE:
        {
            //VEHICLE EQUIPMENT daily check msg
            MssVobcAtsCheck totalMsg;
            totalMsg.common_header = commonHeader;
            totalMsg.app_len = appLength;
            bufSize = b2v_bytes_to_var_byoffset(buf,
                                                bufSize,
                                                (quint8 *)&totalMsg.datagram,
                                                vobc_ats_check_cv_table,
                                                vobc_ats_check_cv_table_len);
            if(bufSize == len)
            {
                ret = insertData(TableAtsVehicleDailyCheck, &totalMsg, buf, bufSize);
            }
        }
            break;
        default:
        {
            VOBC_WARN() << "unknown vobc ats msg type.";
        }
            break;
        }   //end switch msg_type

    }       //end case VOBC_ATS_IF
        break;

    case VOBC_CI_INTERFACE:  //vobc-ci interface
    {
        uint8_t nc_data;
        b2v_bytes_to_var_byoffset(buf,
                                  msgOffset,
                                  (quint8 *)&nc_data,
                                  vobc_ci_msg_type_cv_table,
                                  vobc_ci_msg_type_cv_table_len);
        switch (nc_data) {
        case VOBC_CI_SHIELDEDGATE_MSG_TYPE:
        {
            //shielded gate datagram
            MssVobcCi totalMsg;
            totalMsg.common_header = commonHeader;
            bufSize = b2v_bytes_to_var_byoffset(buf,
                                                msgOffset,
                                                (quint8 *)&totalMsg.datagram,
                                                vobc_ci_cv_table,
                                                vobc_ci_cv_table_len);
            if(bufSize == len)
            {
                ret = insertData(TableVobcCi, &totalMsg, buf, bufSize);
            }
            break;
        }
        default:
        {
            VOBC_WARN() << "unknown vobc ci msg type";
            break;
        }
        }

    }       //end case VOBC_CI_IF
        break;
    case VOBC_ZC_INTERFACE:
    {
        vobc_app_header_len_t appLength;
        bufSize = b2v_bytes_to_var_byoffset(buf,
                                  msgOffset,
                                  (quint8 *)&appLength,
                                  vobc_msg_len_cv_table,
                                  vobc_msg_len_cv_table_len);
        uint16_t msgType;
        b2v_bytes_to_var_byoffset(buf,
                                  bufSize,
                                  (quint8 *)&msgType,
                                  vobc_zc_msg_type_cv_table,
                                  vobc_zc_msg_type_cv_table_len);
        switch (msgType) {
        case VOBC_ZC_TRAIN_MSG_TYPE:
        {
            MssVobcZcTrain totalMsg;
            totalMsg.common_header = commonHeader;
            totalMsg.app_len = appLength;
            bufSize = b2v_bytes_to_var_byoffset(buf,
                                                bufSize,
                                                (quint8 *)&totalMsg.datagram,
                                                vobc_zc_train_cv_table,
                                                vobc_zc_train_cv_table_len);
            if(bufSize == len)
            {
                ret = insertData(TableZcTrain, &totalMsg, buf, bufSize);
            }
            break;
        }
        case VOBC_ZC_REGISTER_MSG_TYPE:
        {
            MssVobcZcRegister totalMsg;
            totalMsg.common_header = commonHeader;
            totalMsg.app_len = appLength;
            bufSize = b2v_bytes_to_var_byoffset(buf,
                                                bufSize,
                                                (quint8 *)&totalMsg.datagram,
                                                vobc_zc_register_cv_table,
                                                vobc_zc_register_cv_table_len);
            if(bufSize == len)
            {
                ret = insertData(TableZcRegister, &totalMsg, buf, bufSize);
            }
            break;
        }
        default:
        {
            VOBC_WARN() << "unknown vobc zc type";
        }
            break;
        }
    }       //end case VOBC_ZC_IF
        break;
    default:
    {
        VOBC_WARN() << "unknown subsystem msg type" << commonHeader.vobc_ats_interface;
    }
        break;
    }       //end switch header

    if(bufSize != len)
    {
        qWarning("Length is NOT equal! bufSize(0x%x) inputlength(0x%x) type = 0x%x",
                 bufSize, len, commonHeader.vobc_ats_interface);
        emit castError(ErrInvalidArgument);
    }
    else
    {
        if(!ret)
        {
            printDatabaseError();
            emit castError(ErrInsertTable);
        }
    }
    delete[] buf;
}

bool VobcDcsService::insertData(EVobcTb tableName, void *data, void *rawData, quint16 length)
{
    bool ret = false;

    if(!db.isOpen())
    {
        return ret;
    }

    switch (tableName) {
    case TableAtsAtoState:
    {
        MssVobcAtsAto *datagram = (MssVobcAtsAto *)data;
        query.prepare("insert into vobc_ats_ato(vobc_ats_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "msg_len,msg_type,service_id,line_id,"
                      "cargroup_line_id,cargroup_id,sourceline_id,"
                      "trainnum_id, destination_track_id, destination_id, "
                      "driver_id, mode_ato, nc_interval_operation, "
                      "status_skipstop, status_detain, nextstation_id, "
                      "reserved_field, rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->app_len.v_msg_len);
        query.addBindValue(datagram->datagram.msg_type);
        query.addBindValue(datagram->datagram.service_id);
        query.addBindValue(datagram->datagram.line_id);
        query.addBindValue(datagram->datagram.cargroup_line_id);
        query.addBindValue(datagram->datagram.cargroup_id);
        query.addBindValue(datagram->datagram.sourceline_id);
        query.addBindValue(datagram->datagram.trainnum_id);
        query.addBindValue(datagram->datagram.destination_track_id);
        query.addBindValue(datagram->datagram.destination_id);
        query.addBindValue(datagram->datagram.driver_id);
        query.addBindValue(datagram->datagram.mode_ato);
        query.addBindValue(datagram->datagram.nc_interval_operation);
        query.addBindValue(datagram->datagram.status_skipstop);
        query.addBindValue(datagram->datagram.status_detain);
        query.addBindValue(datagram->datagram.nextstation_id);
        query.addBindValue(datagram->datagram.reserved_field);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableAtsTrain:
    {
        MssVobcAtsTrain *datagram = (MssVobcAtsTrain *)data;
        query.prepare("insert into vobc_ats_train(vobc_ats_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "msg_len,msg_type,train_id,line_id,"
                      "status_train_pos,dir_train,dir_whell,"
                      "head_estimate_logic_id,head_estimate_offset,tail_estimate_logic_id,"
                      "tail_estimate_offset,over_read,lack_read,"
                      "mode_atp,mode_cbtc,status_train_complete,"
                      "status_emerg_brake,status_ar,vel_msg,"
                      "status_psd,status_trainstoparea,status_stoptrain,"
                      "status_unmanned_reentry,mode_preselect,reasonof_emerg_brake,"
                      "vel_emerg_brake, vel_recommend, pos_security, "
                      "sec_track_id,sec_track_offset,pos_obstacle,"
                      "obs_track_id,obs_track_offset,reserved_field,rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->app_len.v_msg_len);
        query.addBindValue(datagram->datagram.msg_type);
        query.addBindValue(datagram->datagram.train_id);
        query.addBindValue(datagram->datagram.line_id);
        query.addBindValue(datagram->datagram.status_train_pos);
        query.addBindValue(datagram->datagram.dir_train);
        query.addBindValue(datagram->datagram.dir_whell);
        query.addBindValue(datagram->datagram.head_estimate_logic_id);
        query.addBindValue(datagram->datagram.head_estimate_offset);
        query.addBindValue(datagram->datagram.tail_estimate_logic_id);
        query.addBindValue(datagram->datagram.tail_estimate_offset);
        query.addBindValue(datagram->datagram.over_read);
        query.addBindValue(datagram->datagram.lack_read);
        query.addBindValue(datagram->datagram.mode_atp);
        query.addBindValue(datagram->datagram.mode_cbtc);
        query.addBindValue(datagram->datagram.status_train_complete);
        query.addBindValue(datagram->datagram.status_emerg_brake);
        query.addBindValue(datagram->datagram.status_ar);
        query.addBindValue(datagram->datagram.vel_msg);
        query.addBindValue(datagram->datagram.status_psd);
        query.addBindValue(datagram->datagram.status_trainstoparea);
        query.addBindValue(datagram->datagram.status_stoptrain);
        query.addBindValue(datagram->datagram.status_unmanned_reentry);
        query.addBindValue(datagram->datagram.mode_preselect);
        query.addBindValue(datagram->datagram.reasonof_emerg_brake);
        query.addBindValue(datagram->datagram.vel_emerg_brake);
        query.addBindValue(datagram->datagram.vel_recommend);
        query.addBindValue(datagram->datagram.pos_security);
        query.addBindValue(datagram->datagram.sec_track_id);
        query.addBindValue(datagram->datagram.sec_track_offset);
        query.addBindValue(datagram->datagram.pos_obstacle);
        query.addBindValue(datagram->datagram.obs_track_id);
        query.addBindValue(datagram->datagram.obs_track_offset);
        query.addBindValue(datagram->datagram.reserved_field);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableAtsVehicleAlarm:
    {
        MssVobcAtsAlarm *datagram = (MssVobcAtsAlarm *)data;
        query.prepare("insert into vobc_ats_alarm(vobc_ats_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "msg_len,msg_type,train_id,alarm_ato,"
                      "alarm_btm,alarm_vel_ui,alarm_radar,"
                      "alarm_train_com,alarm_speed_measure,alarm_acceleration_measure,"
                      "alarm_reserved1,alarm_reserved2,alarm_atp,"
                      "board_info1,board_info2,board_info3,"
                      "board_info4,board_info5,board_info6,"
                      "rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->app_len.v_msg_len);
        query.addBindValue(datagram->datagram.msg_type);
        query.addBindValue(datagram->datagram.train_id);
        query.addBindValue(datagram->datagram.alarm_ato);
        query.addBindValue(datagram->datagram.alarm_btm);
        query.addBindValue(datagram->datagram.alarm_vel_ui);
        query.addBindValue(datagram->datagram.alarm_radar);
        query.addBindValue(datagram->datagram.alarm_train_com);
        query.addBindValue(datagram->datagram.alarm_speed_measure);
        query.addBindValue(datagram->datagram.alarm_acceleration_measure);
        query.addBindValue(datagram->datagram.alarm_reserved1);
        query.addBindValue(datagram->datagram.alarm_reserved2);
        query.addBindValue(datagram->datagram.alarm_atp);
        query.addBindValue(datagram->datagram.board_info1);
        query.addBindValue(datagram->datagram.board_info2);
        query.addBindValue(datagram->datagram.board_info3);
        query.addBindValue(datagram->datagram.board_info4);
        query.addBindValue(datagram->datagram.board_info5);
        query.addBindValue(datagram->datagram.board_info6);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableAtsVehicleDailyCheck:
    {
        MssVobcAtsCheck *datagram = (MssVobcAtsCheck *)data;
        query.prepare("insert into vobc_ats_check(vobc_ats_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "msg_len,msg_type,train_id,status_check1,"
                      "status_check2,status_check3,status_check4,"
                      "status_check5,status_check6,rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->app_len.v_msg_len);
        query.addBindValue(datagram->datagram.msg_type);
        query.addBindValue(datagram->datagram.traid_id);
        query.addBindValue(datagram->datagram.status_check1);
        query.addBindValue(datagram->datagram.status_check2);
        query.addBindValue(datagram->datagram.status_check3);
        query.addBindValue(datagram->datagram.status_check4);
        query.addBindValue(datagram->datagram.status_check5);
        query.addBindValue(datagram->datagram.status_check6);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableVobcCi:
    {
        MssVobcCi *datagram = (MssVobcCi *)data;
        query.prepare("insert into vobc_ci(vobc_ci_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "nc_data,dir_train,s_trainstoparea,"
                      "n_psd_type,n_psd,nid_psd_1,"
                      "nc_psd_1,nid_psd_2,nc_psd_2, rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->datagram.nc_data);
        query.addBindValue(datagram->datagram.dir_train);
        query.addBindValue(datagram->datagram.s_trainstoparea);
        query.addBindValue(datagram->datagram.n_psd_type);
        query.addBindValue(datagram->datagram.n_psd);
        query.addBindValue(datagram->datagram.nid_psd_1);
        query.addBindValue(datagram->datagram.nc_psd_1);
        query.addBindValue(datagram->datagram.nid_psd_2);
        query.addBindValue(datagram->datagram.nc_psd_2);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableZcRegister:
    {
        MssVobcZcRegister *datagram = (MssVobcZcRegister *)data;
        query.prepare("insert into vobc_zc_register(vobc_zc_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "msg_len,msg_type,register_mode,log_out_reason,"
                      "rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->app_len.v_msg_len);
        query.addBindValue(datagram->datagram.msg_type);
        query.addBindValue(datagram->datagram.register_mode);
        query.addBindValue(datagram->datagram.log_out_reason);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableZcTrain:
    {
        MssVobcZcTrain *datagram = (MssVobcZcTrain *)data;
        query.prepare("insert into vobc_zc_train(vobc_zc_interface,send_id_msg,incept_id_msg,"
                      "edition_control_msg,edition_check_msg,msg_list,"
                      "com_cycle,opposite_msg_list,smsg_self_list,pro_edition,"
                      "msg_len,msg_type,dir,active_side,"
                      "head_estimate_logic_id,head_estimate_offset,tail_estimate_logic_id,"
                      "tail_estimate_offset,lack_read,over_read,"
                      "train_length,wheel_head_length,op_mode,"
                      "drive_mode,stop_response,stop_area,"
                      "stop_area_offset,stop_pos_obstacle,stop_pos_obs_offset,"
                      "stop_valid,status_reentry,status_train_complete,"
                      "led_unmanned_reentry,status_emerg_brake,train_speed,"
                      "speed_dir,recess_length,status_trainstoparea,"
                      "ctl_zcid,rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(datagram->common_header.vobc_ats_interface);
        query.addBindValue(datagram->common_header.send_id_msg);
        query.addBindValue(datagram->common_header.incept_id_msg);
        query.addBindValue(datagram->common_header.edition_control_msg);
        query.addBindValue(datagram->common_header.edition_check_msg);
        query.addBindValue(datagram->common_header.msg_list);
        query.addBindValue(datagram->common_header.com_cycle);
        query.addBindValue(datagram->common_header.opposite_msg_list);
        query.addBindValue(datagram->common_header.smsg_self_list);
        query.addBindValue(datagram->common_header.pro_edition);
        query.addBindValue(datagram->app_len.v_msg_len);
        query.addBindValue(datagram->datagram.msg_type);
        query.addBindValue(datagram->datagram.dir);
        query.addBindValue(datagram->datagram.active_side);
        query.addBindValue(datagram->datagram.head_estimate_logic_id);
        query.addBindValue(datagram->datagram.head_estimate_offset);
        query.addBindValue(datagram->datagram.tail_estimate_logic_id);
        query.addBindValue(datagram->datagram.tail_estimate_offset);
        query.addBindValue(datagram->datagram.lack_read);
        query.addBindValue(datagram->datagram.over_read);
        query.addBindValue(datagram->datagram.train_length);
        query.addBindValue(datagram->datagram.wheel_head_length);
        query.addBindValue(datagram->datagram.op_mode);
        query.addBindValue(datagram->datagram.drive_mode);
        query.addBindValue(datagram->datagram.stop_response);
        query.addBindValue(datagram->datagram.stop_area);
        query.addBindValue(datagram->datagram.stop_area_offset);
        query.addBindValue(datagram->datagram.stop_pos_obstacle);
        query.addBindValue(datagram->datagram.stop_pos_obs_offset);
        query.addBindValue(datagram->datagram.stop_valid);
        query.addBindValue(datagram->datagram.status_reentry);
        query.addBindValue(datagram->datagram.status_train_complete);
        query.addBindValue(datagram->datagram.led_unmanned_reentry);
        query.addBindValue(datagram->datagram.status_emerg_brake);
        query.addBindValue(datagram->datagram.train_speed);
        query.addBindValue(datagram->datagram.speed_dir);
        query.addBindValue(datagram->datagram.recess_length);
        query.addBindValue(datagram->datagram.status_trainstoparea);
        query.addBindValue(datagram->datagram.ctl_zcid);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    default:
    {
        VOBC_WARN() << "unknown table type";
    }
        break;
    }
    return ret;
}
