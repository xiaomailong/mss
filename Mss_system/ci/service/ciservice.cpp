#include "ciservice.h"
#include "ci_data.h"
#include "b2v.h"
#include "mssdatadefine.h"
#include <QtSql>
#include <QDebug>
//for stream test
#include <QDataStream>
#include<QFile>
#include<qiodevice.h>
#include "mssdbconfig.h"
#include "vobc_data.h"

CiService::CiService(QObject *parent) : QObject(parent)
{

}
void CiService::start()
{
    if(CI_DEBUG)
    {
        qDebug("CiService: start init database");
    }
    //init ci route database
    initCiData();
    ciUdpClient = new QUdpSocket(this);
    ciUdpClient->bind(CI_PORT);
    connect(ciUdpClient, &QUdpSocket::readyRead, this, &CiService::receiveUdpData);
}
CiService::~CiService()
{
    if(CI_DEBUG) qDebug("CiService: ~CiService");
    dbConn.close();
}
void CiService::initCiData()
{
    if(openDB())
    {
        //create ci vobc data
        bool result = true;
        result = result && createTable("create table if not exists ci_vobc_data("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp , "
                                       "ci_vobc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned, "
                                       "pro_edition tinyint unsigned, "
                                       "nc_data tinyint unsigned, "
                                       "dir_train tinyint unsigned, "
                                       "n_psd tinyint unsigned, "
                                       "nid_psd_1 smallint unsigned, "
                                       "nc_psd_1 tinyint unsigned, "
                                       "r_nc_psd_1 tinyint unsigned, "
                                       "nid_psd_2 smallint unsigned, "
                                       "q_psd_2 tinyint unsigned, "
                                       "r_nc_psd_2 tinyint unsigned, "
                                       "q_signal_aspect tinyint unsigned, "
                                       "bytedata blob)");
        //create ci ats alarm
        result = result && createTable("create table if not exists ci_ats_alarm ("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_ats_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned, "
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "info_len smallint unsigned, "
                                       "filament_burnout tinyint unsigned, "
                                       "filament_fuse tinyint unsigned, "
                                       "power_panel tinyint unsigned, "
                                       "signal_fault_shutdown tinyint unsigned, "
                                       "ci_device_alarm tinyint unsigned, "
                                       "railway_alarm tinyint unsigned, "
                                       "ups_fault tinyint unsigned, "
                                       "leu_communication_state tinyint unsigned, "
                                       "ci_zc_state tinyint unsigned, "
                                       "ci1_state tinyint unsigned, "
                                       "ci2_state tinyint unsigned, "
                                       "power1_state tinyint unsigned, "
                                       "power2_state tinyint unsigned, "
                                       "ci_count tinyint unsigned, "
                                       "ci_communication_state tinyint unsigned, "
                                       "unmanned_reentry tinyint unsigned, "
                                       "turnout_turnout tinyint unsigned, "
                                       "check_num tinyint unsigned, "
                                       "check_condition tinyint unsigned, "
                                       "psd_count tinyint unsigned, "
                                       "psd_x_state tinyint unsigned, "
                                       "station_mode tinyint unsigned, "
                                       "station_block tinyint unsigned, "
                                       "electrolytic_lock tinyint unsigned, "
                                       "autonomy_request tinyint unsigned, "
                                       "bytedata blob)");
        result = result && createTable("create table if not exists ci_ats_stationyard("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_ats_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned, "
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "deviceinfo_len smallint unsigned, "
                                       "c_signal blob,c_switch blob,c_phy_track blob,c_logic_track blob,"
                                       "c_route_info blob,c_auto_route blob,c_shield_door blob,c_esp_button blob,"
                                       "c_remain_car blob,c_half_autoback blob,c_autoback blob,c_spks blob,c_auto_trigger blob,"
                                       "bytedata blob)");
        result = result && createTable("create table if not exists ci_zc_route ("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_zc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned,"
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "route_size smallint unsigned,"
                                       "route_num tinyint unsigned,"
                                       "route_state tinyint unsigned,"
                                       "signallight_state tinyint unsigned,"
                                       "switch_state smallint unsigned,"
                                       "sectionlock_state1 tinyint unsigned,"
                                       "sectionlock_state2 tinyint unsigned,"
                                       "sectionlock_state3 tinyint unsigned,"
                                       "sectionlock_state4 tinyint unsigned,"
                                       "sectionlock_state5 tinyint unsigned,"
                                       "proctectlock_info tinyint unsigned,"
                                       "bytedata blob)");

        result = result && createTable("create table if not exists ci_zc_psdinfo("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_zc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned,"
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "psd_size smallint unsigned,"
                                       "psd_state tinyint unsigned,"
                                       "bytedata blob)");
        result = result && createTable("create table if not exists ci_zc_esbbutton ("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_zc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned,"
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "esb_emergency_size smallint unsigned,"
                                       "esb_state tinyint unsigned,"
                                       "bytedata blob)");
        result = result && createTable("create table if not exists ci_zc_returnbutton ("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_zc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned,"
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "returnbutton_size smallint unsigned,"
                                       "returnbutton_state tinyint unsigned,"
                                       "bytedata blob)");
        result = result && createTable("create table if not exists ci_zc_sectionused("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_zc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned,"
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "zc_size smallint unsigned,"
                                       "zc_state tinyint unsigned,"
                                       "bytedata blob)");
        result = result && createTable("create table if not exists ci_zc_approachunlock_req("
                                       "id int auto_increment primary key, "
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "ci_zc_interface smallint unsigned, "
                                       "send_id_msg int unsigned, "
                                       "incept_id_msg int unsigned, "
                                       "edition_control_msg tinyint unsigned, "
                                       "edition_check_msg int unsigned, "
                                       "msg_list int unsigned, "
                                       "com_cycle tinyint unsigned, "
                                       "opposite_msg_list int unsigned, "
                                       "smsg_self_list int unsigned,"
                                       "pro_edition tinyint unsigned,"
                                       "package_data_size smallint unsigned,"
                                       "package_data_type smallint unsigned, "
                                       "unlock_size smallint unsigned,"
                                       "unlock_num tinyint unsigned,"
                                       "bytedata blob)");
        //add ci ci data
        result = result && createTable("create table if not exists ci_ci_data("
                                       "id int auto_increment primary key,"
                                       "time TIMESTAMP NOT NULL DEFAULT current_timestamp, "
                                       "moduleid_code int, "
                                       "device_type tinyint, "
                                       "device_code int, "
                                       "device_state tinyint, "
                                       "device_place smallint, "
                                       "alarm_type tinyint, "
                                       "alarm_subtype tinyint,"
                                       "alarm_level tinyint, "
                                       "detailinfo int)");
        if(result)
        {
            emit started();
        }
        else
        {
            emit error(TbCreateError);
        }
    }
    else
    {
        emit error(DbOpenError);
    }
    if(CI_DEBUG)
    {
        qDebug()<<"init database end";
    }
}
bool CiService::createTable(const QString& queryStr)
{
    if(!dbQuery.exec(queryStr))
    {
        qDebug()<<"create table fail "<< dbQuery.lastError();
        return false;
    }
    return true;
}
bool CiService::openDB()
{
    QString connectName = "ciroute";
    QSqlDatabase dbConnInit;
    if(!QSqlDatabase::contains(connectName))
    {
        dbConnInit = QSqlDatabase::addDatabase(MSS_DB_DRIVER, connectName);
    }
    dbConnInit.setHostName(MSS_DB_HOST_NAME);
    dbConnInit.setPort(MSS_DB_PORT);
    dbConnInit.setUserName(MSS_DB_USER);
    dbConnInit.setPassword(MSS_DB_PASSWORD);
    dbConnInit.setDatabaseName(MSS_DB_NAME);
    dbConn = QSqlDatabase::database(connectName);
    int dbresult = dbConn.open();
    if(1 != dbresult)
    {
        qDebug()<<"ci_service_thread Failed to connected db!";
        emit error(DbOpenError);
        dbConn.close();
        return false;
    }
    if(CI_DEBUG) qDebug()<<"CiService success connect db";
    dbQuery = (QSqlQuery)QSqlDatabase::database(connectName);
    return true;
}
void CiService::receiveRouteData(quint8 *buf,quint16 len)
{
    if(CI_DEBUG)
    {
        qDebug()<<"CiService :receiveRouteData receive start threadid:"<< QThread::currentThreadId();
    }
    quint16 headerOffset = 0;
    quint16 dataOffset = 0;
    ci_data_h ciDatah;
    quint16 ciDataHeader = 0;
    if(len < MODULE_HEADER_LEN)
    {
        qDebugErrorValid("CI DATA");
        emit error(DataInvalid);
        return;
    }
    ciDataHeader = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&ciDatah, ci_data_h_convert_table,ci_data_h_convert_table_len);
    if(CI_DEBUG)
    {
        qDebug()<<"len="<<len<<" cidataheader="<<ciDataHeader;
    }
    switch(ciDatah.ci_interface)
    {
    // parsed data here
    case CI_VOBC_INTERFACE:
    {
        ci_vobc_data_t ciVobc;
        if(len != CI_VOBC_LEN)
        {
            qDebugErrorValid("CI_VOBC_INTERFACE");
            emit error(DataInvalid);
            break;
        }
        dataOffset = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&ciVobc, ci_vobc_convert_table,ci_vobc_convert_table_len);
        if(CI_DEBUG)
        {
            qDebug()<<"ENTER CI_VOBC_INTERFACE len="<<len<<" offset ="<<headerOffset;
        }

        //save data to database
        QString ciVobcSql = "insert into ci_vobc_data("
                              "ci_vobc_interface, "
                              "send_id_msg, incept_id_msg, "
                              "edition_control_msg, "
                              "edition_check_msg, "
                              "msg_list, "
                              "com_cycle, "
                              "opposite_msg_list, "
                              "smsg_self_list, "
                              "pro_edition, nc_data, "
                              "dir_train, "
                              "n_psd, nid_psd_1, nc_psd_1, r_nc_psd_1, "
                              "nid_psd_2, q_psd_2, r_nc_psd_2, "
                              "q_signal_aspect, "
                              "bytedata) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
        if(CI_DEBUG)
        {
            qDebug()<<"CI_VOBC_INTERFACE data ci_vobc_interface ="<<ciVobc.ci_vobc_interface<<" q_signal_aspect="<<ciVobc.q_signal_aspect;
        }
        dbQuery.prepare(ciVobcSql);
        dbQuery.addBindValue(ciVobc.ci_vobc_interface);
        dbQuery.addBindValue(ciVobc.send_id_msg);
        dbQuery.addBindValue(ciVobc.incept_id_msg);
        dbQuery.addBindValue(ciVobc.edition_control_msg);
        dbQuery.addBindValue(ciVobc.edition_check_msg);
        dbQuery.addBindValue(ciVobc.msg_list);
        dbQuery.addBindValue(ciVobc.com_cycle);
        dbQuery.addBindValue(ciVobc.opposite_msg_list);
        dbQuery.addBindValue(ciVobc.smsg_self_list);
        dbQuery.addBindValue(ciVobc.pro_edition);
        dbQuery.addBindValue(ciVobc.nc_data);
        dbQuery.addBindValue(ciVobc.dir_train);
        dbQuery.addBindValue(ciVobc.n_psd);
        dbQuery.addBindValue(ciVobc.nid_psd_1);
        dbQuery.addBindValue(ciVobc.nc_psd_1);
        dbQuery.addBindValue(ciVobc.r_nc_psd_1);
        dbQuery.addBindValue(ciVobc.nid_psd_2);
        dbQuery.addBindValue(ciVobc.q_psd_2);
        dbQuery.addBindValue(ciVobc.r_nc_psd_2);
        dbQuery.addBindValue(ciVobc.q_signal_aspect);
        dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, dataOffset));
        if(!dbQuery.exec())
        {
            qDebug()<<"ci route thread error"<<dbQuery.lastError();
            qDebugErrorInsert("CI_VOBC_INTERFACE");
            emit error(EntryInsertError);
        }
    }
        break;
    case CI_ATS_INTERFACE:
    {
        ci_ats_data_h ciAtsh;
        if(len < CI_ATS_HEADER_LEN)
        {
            qDebugErrorValid("CI_ATS_INTERFACE");
            emit error(DataInvalid);
            break;
        }
        headerOffset = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&ciAtsh, ci_ats_h_convert_table,ci_ats_h_convert_table_len);
        if(CI_DEBUG)
        {
            qDebug()<<"ENTER CI_ATS_INTERFACE offset ="<<headerOffset<<"ciAtsh.package_data_type="<<ciAtsh.package_data_type;
        }
        switch(ciAtsh.package_data_type)
        {
        case CI_ATS_ALARM:
        {
            ci_ats_data_alarm ciAtsData;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciAtsData, ci_ats_data_alarm_covert_table, ci_ats_data_alarm_covert_table_len);
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ATS_INTERFACE CI_ATS_ALARM len="<<len<<" datalen="<<headerOffset + dataOffset;
            }
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ATS_ALARM");
                emit error(DataInvalid);
                break;
            }
            //save to database
            QString ciAtsAlarm = "insert into ci_ats_alarm ("
                                   "ci_ats_interface, send_id_msg, incept_id_msg, "
                                   "edition_control_msg, edition_check_msg ,msg_list, "
                                   "com_cycle, opposite_msg_list,smsg_self_list, "
                                   "pro_edition, package_data_size,package_data_type, "
                                   "info_len, "
                                   "filament_burnout, "
                                   "filament_fuse, "
                                   "power_panel, "
                                   "signal_fault_shutdown, "
                                   "ci_device_alarm, "
                                   "railway_alarm, "
                                   "ups_fault, "
                                   "leu_communication_state, "
                                   "ci_zc_state, "
                                   "ci1_state, "
                                   "ci2_state, "
                                   "power1_state, "
                                   "power2_state, "
                                   "ci_count, "
                                   "ci_communication_state, "
                                   "unmanned_reentry, "
                                   "turnout_turnout, "
                                   "check_num, "
                                   "check_condition, "
                                   "psd_count, "
                                   "psd_x_state, "
                                   "station_mode, "
                                   "station_block, "
                                   "electrolytic_lock, "
                                   "autonomy_request, "
                                   "bytedata) values (?,?,?,?,?,?,?,?,?,?,"
                                   "?,?,?,?,?,?,?,?,?,?,"
                                   "?,?,?,?,?,?,?,?,?,?,"
                                   "?,?,?,?,?,?,?,?,?)";
            dbQuery.prepare(ciAtsAlarm);
            dbQuery.addBindValue(ciAtsh.ci_ats_interface);
            dbQuery.addBindValue(ciAtsh.send_id_msg);
            dbQuery.addBindValue(ciAtsh.incept_id_msg);
            dbQuery.addBindValue(ciAtsh.edition_control_msg);
            dbQuery.addBindValue(ciAtsh.edition_check_msg);
            dbQuery.addBindValue(ciAtsh.msg_list);
            dbQuery.addBindValue(ciAtsh.com_cycle);
            dbQuery.addBindValue(ciAtsh.opposite_msg_list);
            dbQuery.addBindValue(ciAtsh.smsg_self_list);
            dbQuery.addBindValue(ciAtsh.pro_edition);
            dbQuery.addBindValue(ciAtsh.package_data_size);
            dbQuery.addBindValue(ciAtsh.package_data_type);
            //dbQuery.addBindValue(ciAtsh.a_msg_num);
            dbQuery.addBindValue(0);
            dbQuery.addBindValue(ciAtsData.filament_burnout);
            dbQuery.addBindValue(ciAtsData.filament_fuse);
            dbQuery.addBindValue(ciAtsData.power_panel);
            dbQuery.addBindValue(ciAtsData.signal_fault_shutdown);
            dbQuery.addBindValue(ciAtsData.ci_device_alarm);
            dbQuery.addBindValue(ciAtsData.railway_alarm);
            dbQuery.addBindValue(ciAtsData.ups_fault);
            dbQuery.addBindValue(ciAtsData.leu_communication_state);
            dbQuery.addBindValue(ciAtsData.ci_zc_state);
            dbQuery.addBindValue(ciAtsData.ci1_state);
            dbQuery.addBindValue(ciAtsData.ci2_state);
            dbQuery.addBindValue(ciAtsData.power1_state);
            dbQuery.addBindValue(ciAtsData.power2_state);
            dbQuery.addBindValue(ciAtsData.ci_count);
            dbQuery.addBindValue(ciAtsData.ci_communication_state);
            dbQuery.addBindValue(ciAtsData.unmanned_reentry);
            dbQuery.addBindValue(ciAtsData.turnout_turnout);
            dbQuery.addBindValue(ciAtsData.check_num);
            dbQuery.addBindValue(ciAtsData.check_condition);
            dbQuery.addBindValue(ciAtsData.psd_count);
            dbQuery.addBindValue(ciAtsData.psd_x_state);
            dbQuery.addBindValue(ciAtsData.station_mode);
            dbQuery.addBindValue(ciAtsData.station_block);
            dbQuery.addBindValue(ciAtsData.electrolytic_lock);
            dbQuery.addBindValue(ciAtsData.autonomy_request);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci ats alarm"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ATS_ALARM");
                emit error(EntryInsertError);
            }
        }
            break;
        case CI_ATS_STATIONYARD:
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ATS_INTERFACE CI_ATS_STATIONYARD";
            }
            ci_ats_data_stationyard ciAtsData;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciAtsData, ci_ats_data_stationyard_covert_table, ci_ats_data_stationyard_covert_table_len);
            if(CI_DEBUG) qDebug()<<"ENTER CI_ATS_INTERFACE CI_ATS_ALARM len="<<len<<" datalen="<<headerOffset + dataOffset;
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ATS_STATIONYARD");
                emit error(DataInvalid);
                break;
            }
            QString ciAtsStationyard = "insert into ci_ats_stationyard("
                                         "ci_ats_interface, send_id_msg, incept_id_msg, "
                                         "edition_control_msg, edition_check_msg , "
                                         "msg_list, com_cycle, opposite_msg_list,smsg_self_list, "
                                         "pro_edition, package_data_size,package_data_type, "
                                         "deviceinfo_len,"
                                         "c_signal,c_switch,c_phy_track,c_logic_track,"
                                         "c_route_info,c_auto_route,c_shield_door,c_esp_button,"
                                         "c_remain_car,c_half_autoback,c_autoback,c_spks,c_auto_trigger,"
                                         "bytedata)values(?,?,?,?,?,?,?,?,?,?,"
                                         "?,?,?,?,?,?,?,?,?,?,"
                                         "?,?,?,?,?,?,?)";
            dbQuery.prepare(ciAtsStationyard);
            dbQuery.addBindValue(ciAtsh.ci_ats_interface);
            dbQuery.addBindValue(ciAtsh.send_id_msg);
            dbQuery.addBindValue(ciAtsh.incept_id_msg);
            dbQuery.addBindValue(ciAtsh.edition_control_msg);
            dbQuery.addBindValue(ciAtsh.edition_check_msg);
            dbQuery.addBindValue(ciAtsh.msg_list);
            dbQuery.addBindValue(ciAtsh.com_cycle);
            dbQuery.addBindValue(ciAtsh.opposite_msg_list);
            dbQuery.addBindValue(ciAtsh.smsg_self_list);
            dbQuery.addBindValue(ciAtsh.pro_edition);
            dbQuery.addBindValue(ciAtsh.package_data_size);
            dbQuery.addBindValue(ciAtsh.package_data_type);
            dbQuery.addBindValue(ciAtsh.a_msg_num);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_signal,MAX_SIGNAL_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_switch,MAX_SWITCH_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_phy_track,MAX_PHY_TRACK_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_logic_track,MAX_LOGIC_TRACK_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_route_info,MAX_ROUTE_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_auto_route,MAX_AUTO_ROUTE_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_shield_door,MAX_SHILED_DOOR_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_esp_button,MAX_ESP_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_remain_car,MAX_REMAIN_CAR_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_half_autoback,MAX_HALF_AUTOBACK_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_autoback,MAX_AUTOBACK_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_spks,MAX_SPKS_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)ciAtsData.c_auto_trigger,MAX_AUTO_TRIGGER_NUM*sizeof(quint8)));
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci ats station"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ATS_STATIONYARD");
                emit error(EntryInsertError);
            }
        }
            break;
        default:
        {
            qDebug()<<"ci_service_thread:receiveData_route_test  CI_ATS_INTERFACE wrong data formate";
            qDebugErrorValid("Invalid CI_ATS_INTERFACE");
            emit error(DataInvalid);
        }
            break;
        }
    }
        break;
    case CI_ZC_INTERFACE:
    {
        ci_zc_data_h ciZch;
        if(len<CI_ZC_HEADER_LEN)
        {
            qDebugErrorValid("CI_ZC_INTERFACE");
            emit error(DataInvalid);
            break;
        }
        headerOffset = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&ciZch, ci_zc_data_h_convert_table, ci_zc_data_h_convert_table_len);
        if(CI_DEBUG)
        {
            qDebug()<<"ENTER CI_ZC_INTERFACE offset ="<<headerOffset<<"cizcsh.package_data_type="<<ciZch.package_data_type;
        }
        switch(ciZch.package_data_type)
        {
        case CI_ZC_MOVE://DRIVE INFO
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_INTERFACE CI_ZC_MOVE";
            }
            ci_zc_route ciZcRoute;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciZcRoute, ci_zc_route_convert_table, ci_zc_route_convert_table_len);
            if(CI_DEBUG) qDebug()<<"ENTER CI_ATS_INTERFACE CI_ZC_MOVE len="<<len<<" datalen="<<headerOffset + dataOffset;
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ZC_MOVE");
                emit error(DataInvalid);
                break;
            }
            QString ciZcMove = "insert into ci_zc_route("
                                 "ci_zc_interface, send_id_msg, incept_id_msg, "
                                 "edition_control_msg, edition_check_msg , "
                                 "msg_list, com_cycle, opposite_msg_list, smsg_self_list,"
                                 "pro_edition, package_data_size,package_data_type, "
                                 "route_size,route_num,route_state,signallight_state,"
                                 "switch_state,sectionlock_state1,sectionlock_state2,sectionlock_state3,sectionlock_state4,sectionlock_state5,"
                                 "proctectlock_info,bytedata)values(?,?,?,?,?,?,?,?,?,?,"
                                 "?,?,?,?,?,?,?,?,?,?,"
                                 "?,?,?,?)";
            dbQuery.prepare(ciZcMove);
            dbQuery.addBindValue(ciZch.ci_zc_interface);
            dbQuery.addBindValue(ciZch.send_id_msg);
            dbQuery.addBindValue(ciZch.incept_id_msg);
            dbQuery.addBindValue(ciZch.edition_control_msg);
            dbQuery.addBindValue(ciZch.edition_check_msg);
            dbQuery.addBindValue(ciZch.msg_list);
            dbQuery.addBindValue(ciZch.com_cycle);
            dbQuery.addBindValue(ciZch.opposite_msg_list);
            dbQuery.addBindValue(ciZch.pro_edition);
            dbQuery.addBindValue(ciZch.smsg_self_list);
            dbQuery.addBindValue(ciZch.package_data_size);
            dbQuery.addBindValue(ciZch.package_data_type);
            dbQuery.addBindValue(ciZch.a_msg_num);
            dbQuery.addBindValue(ciZcRoute.route_num);
            dbQuery.addBindValue(ciZcRoute.route_state);
            dbQuery.addBindValue(ciZcRoute.signallight_state);
            dbQuery.addBindValue(ciZcRoute.switch_state);
            dbQuery.addBindValue(ciZcRoute.sectionlock_state1);
            dbQuery.addBindValue(ciZcRoute.sectionlock_state2);
            dbQuery.addBindValue(ciZcRoute.sectionlock_state3);
            dbQuery.addBindValue(ciZcRoute.sectionlock_state4);
            dbQuery.addBindValue(ciZcRoute.sectionlock_state5);
            dbQuery.addBindValue(ciZcRoute.proctectlock_info);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci route thread error"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ZC_MOVE");
                emit error(EntryInsertError);
            }
        }
            break;
        case CI_ZC_PSD://PSD STATE INFO
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_INTERFACE CI_ZC_PSD";
            }
            ci_zc_psdinfo ciZcPsd;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciZcPsd, ci_zc_psdinfo_convert_table, ci_zc_psdinfo_convert_table_len);
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_PSD len="<<len<<" datalen="<<headerOffset + dataOffset;
            }
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ZC_PSD");
                emit error(DataInvalid);
                break;
            }
            QString ciPsdSql = "insert into ci_zc_psdinfo("
                                "ci_zc_interface, send_id_msg, incept_id_msg, "
                                "edition_control_msg, edition_check_msg , "
                                "msg_list, com_cycle, opposite_msg_list, "
                                "smsg_self_list,"
                                "pro_edition, package_data_size,package_data_type, "
                                "psd_size,psd_state,bytedata)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            dbQuery.prepare(ciPsdSql);
            dbQuery.addBindValue(ciZch.ci_zc_interface);
            dbQuery.addBindValue(ciZch.send_id_msg);
            dbQuery.addBindValue(ciZch.incept_id_msg);
            dbQuery.addBindValue(ciZch.edition_control_msg);
            dbQuery.addBindValue(ciZch.edition_check_msg);
            dbQuery.addBindValue(ciZch.msg_list);
            dbQuery.addBindValue(ciZch.com_cycle);
            dbQuery.addBindValue(ciZch.opposite_msg_list);
            dbQuery.addBindValue(ciZch.smsg_self_list);
            dbQuery.addBindValue(ciZch.pro_edition);
            dbQuery.addBindValue(ciZch.package_data_size);
            dbQuery.addBindValue(ciZch.package_data_type);
            dbQuery.addBindValue(ciZch.a_msg_num);
            //dbQuery.addBindValue(ciZcPsd.psd_size);
            dbQuery.addBindValue(ciZcPsd.psd_state);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci route thread error"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ZC_PSD");
                emit error(EntryInsertError);
            }
        }
            break;
        case CI_ZC_ESB://ESB STATE INFO
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_INTERFACE CI_ZC_ESB";
            }
            ci_zc_esbbutton ciZcEsb;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciZcEsb, ci_zc_esbbutton_convert_table, ci_zc_esbbutton_convert_table_len);
            if(CI_DEBUG) qDebug()<<"ENTER CI_ATS_INTERFACE CI_ZC_ESB len="<<len<<" datalen="<<headerOffset + dataOffset;
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ZC_ESB");
                emit error(DataInvalid);
                break;
            }
            QString ciEsbSql = "insert into ci_zc_esbbutton("
                                "ci_zc_interface, send_id_msg, incept_id_msg, "
                                "edition_control_msg, edition_check_msg , "
                                "msg_list, com_cycle, opposite_msg_list,smsg_self_list, "
                                "pro_edition, package_data_size,package_data_type, "
                                "esb_emergency_size,esb_state,bytedata)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            dbQuery.prepare(ciEsbSql);
            dbQuery.addBindValue(ciZch.ci_zc_interface);
            dbQuery.addBindValue(ciZch.send_id_msg);
            dbQuery.addBindValue(ciZch.incept_id_msg);
            dbQuery.addBindValue(ciZch.edition_control_msg);
            dbQuery.addBindValue(ciZch.edition_check_msg);
            dbQuery.addBindValue(ciZch.msg_list);
            dbQuery.addBindValue(ciZch.com_cycle);
            dbQuery.addBindValue(ciZch.opposite_msg_list);
            dbQuery.addBindValue(ciZch.smsg_self_list);
            dbQuery.addBindValue(ciZch.pro_edition);
            dbQuery.addBindValue(ciZch.package_data_size);
            dbQuery.addBindValue(ciZch.package_data_type);
            //dbQuery.addBindValue(ciZcEsb.esb_emergency_size);
            dbQuery.addBindValue(ciZch.a_msg_num);
            dbQuery.addBindValue(ciZcEsb.esb_state);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci route thread error"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ZC_ESB");
                emit error(EntryInsertError);
            }
        }
            break;
        case CI_ZC_RETURN://RETURN BUTTON INFO
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_INTERFACE CI_ZC_RETURN";
            }
            ci_zc_returnbutton ciZcReturn;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciZcReturn, ci_zc_returnbutton_convert_table, ci_zc_returnbutton_convert_table_len);
            if(CI_DEBUG) qDebug()<<"ENTER CI_ATS_INTERFACE CI_ZC_RETURN len="<<len<<" datalen="<<headerOffset + dataOffset;
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ZC_RETURN");
                emit error(DataInvalid);
                break;
            }
            QString zcReturnSql = "insert into ci_zc_returnbutton("
                                   "ci_zc_interface, send_id_msg, incept_id_msg, "
                                   "edition_control_msg, edition_check_msg , "
                                   "msg_list, com_cycle, opposite_msg_list,smsg_self_list, "
                                   "pro_edition, package_data_size,package_data_type, "
                                   "returnbutton_size,returnbutton_state,bytedata)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            dbQuery.prepare(zcReturnSql);
            dbQuery.addBindValue(ciZch.ci_zc_interface);
            dbQuery.addBindValue(ciZch.send_id_msg);
            dbQuery.addBindValue(ciZch.incept_id_msg);
            dbQuery.addBindValue(ciZch.edition_control_msg);
            dbQuery.addBindValue(ciZch.edition_check_msg);
            dbQuery.addBindValue(ciZch.msg_list);
            dbQuery.addBindValue(ciZch.com_cycle);
            dbQuery.addBindValue(ciZch.opposite_msg_list);
            dbQuery.addBindValue(ciZch.smsg_self_list);
            dbQuery.addBindValue(ciZch.pro_edition);
            dbQuery.addBindValue(ciZch.package_data_size);
            dbQuery.addBindValue(ciZch.package_data_type);
            //dbQuery.addBindValue(ciZcReturn.returnbutton_size);
            dbQuery.addBindValue(ciZch.a_msg_num);
            dbQuery.addBindValue(ciZcReturn.returnbutton_state);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci route thread error"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ZC_RETURN");
                emit error(EntryInsertError);
            }
        }
            break;
        case CI_ZC_SECTION://SECTION USED INFO
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_INTERFACE CI_ZC_SECTION";
            }
            ci_zc_sectionused ciZcSection;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciZcSection, ci_zc_sectionused_convert_table, ci_zc_sectionused_convert_table_len);
            if(CI_DEBUG) qDebug()<<"ENTER CI_ATS_INTERFACE CI_ZC_SECTION len="<<len<<" datalen="<<headerOffset + dataOffset;
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ZC_SECTION");
                emit error(DataInvalid);
                break;
            }
            QString ci_zc_section = "insert into ci_zc_sectionused("
                                    "ci_zc_interface, send_id_msg, incept_id_msg, "
                                    "edition_control_msg, edition_check_msg , "
                                    "msg_list, com_cycle, opposite_msg_list, smsg_self_list,"
                                    "pro_edition, package_data_size,package_data_type, "
                                    "zc_size,zc_state,bytedata)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            dbQuery.prepare(ci_zc_section);
            dbQuery.addBindValue(ciZch.ci_zc_interface);
            dbQuery.addBindValue(ciZch.send_id_msg);
            dbQuery.addBindValue(ciZch.incept_id_msg);
            dbQuery.addBindValue(ciZch.edition_control_msg);
            dbQuery.addBindValue(ciZch.edition_check_msg);
            dbQuery.addBindValue(ciZch.msg_list);
            dbQuery.addBindValue(ciZch.com_cycle);
            dbQuery.addBindValue(ciZch.opposite_msg_list);
            dbQuery.addBindValue(ciZch.smsg_self_list);
            dbQuery.addBindValue(ciZch.pro_edition);
            dbQuery.addBindValue(ciZch.package_data_size);
            dbQuery.addBindValue(ciZch.package_data_type);
            //dbQuery.addBindValue(ciZcSection.zc_size);
            dbQuery.addBindValue(ciZch.a_msg_num);
            dbQuery.addBindValue(ciZcSection.zc_state);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebug()<<"ci route thread error"<<dbQuery.lastError();
                qDebugErrorInsert("CI_ZC_SECTION");
                emit error(EntryInsertError);
            }
        }
            break;
        case CI_ZC_REQU://MOVE REQUIREMENT
        {
            if(CI_DEBUG)
            {
                qDebug()<<"ENTER CI_ZC_INTERFACE CI_ZC_REQU";
            }
            ci_zc_approachunlock ciZcReq;
            dataOffset = b2v_bytes_to_var((quint8 *)buf + headerOffset, (quint8 *)&ciZcReq, ci_zc_approachunlock_convert_table, ci_zc_approachunlock_convert_table_len);
            if(CI_DEBUG) qDebug()<<"ENTER CI_ATS_INTERFACE CI_ZC_REQU len="<<len<<" datalen="<<headerOffset + dataOffset;
            if(len != headerOffset + dataOffset)
            {
                qDebugErrorValid("CI_ZC_REQU");
                emit error(DataInvalid);
                break;
            }
            QString zcReqSql = "insert into ci_zc_approachunlock_req("
                                "ci_zc_interface, send_id_msg, incept_id_msg, "
                                "edition_control_msg, edition_check_msg , "
                                "msg_list, com_cycle, opposite_msg_list, smsg_self_list,"
                                "pro_edition, package_data_size,package_data_type, "
                                "unlock_size,unlock_num,bytedata)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            dbQuery.prepare(zcReqSql);
            dbQuery.addBindValue(ciZch.ci_zc_interface);
            dbQuery.addBindValue(ciZch.send_id_msg);
            dbQuery.addBindValue(ciZch.incept_id_msg);
            dbQuery.addBindValue(ciZch.edition_control_msg);
            dbQuery.addBindValue(ciZch.edition_check_msg);
            dbQuery.addBindValue(ciZch.msg_list);
            dbQuery.addBindValue(ciZch.com_cycle);
            dbQuery.addBindValue(ciZch.opposite_msg_list);
            dbQuery.addBindValue(ciZch.smsg_self_list);
            dbQuery.addBindValue(ciZch.pro_edition);
            dbQuery.addBindValue(ciZch.package_data_size);
            dbQuery.addBindValue(ciZch.package_data_type);
            //dbQuery.addBindValue(ciZcReq.unlock_size);
            dbQuery.addBindValue(ciZch.a_msg_num);
            dbQuery.addBindValue(ciZcReq.unlock_num);
            dbQuery.addBindValue(QByteArray::fromRawData((char *)buf, headerOffset+dataOffset));
            if(!dbQuery.exec())
            {
                qDebugErrorInsert("CI_ZC_REQU");
                emit error(EntryInsertError);
            }
        }
            break;
        default:
        {
            qDebugErrorValid("Invalid CI_ZC_INTERFACE");
            emit error(DataInvalid);
        }
            break;
        }
    }
        break;
    default:
    {
        qDebugErrorValid("CI DATA Invalid data");
        emit error(DataInvalid);
    }
        break;
    }
    delete[] buf;
}
char bufUdpData[MAX_UDP_SIZE];
void CiService::receiveUdpData()
{
    if(CI_DEBUG)
    {
        qDebug()<<"receivedata_udp"<<QThread::currentThreadId();
    }
    quint64 len = 0;
    while (ciUdpClient->hasPendingDatagrams())
    {
        len = ciUdpClient->readDatagram(bufUdpData,MAX_UDP_SIZE);
        dealCiUdpData((quint8*)bufUdpData,len);
    }
}

void CiService::dealCiUdpData(quint8* buf,quint16 len)
{
    if(CI_DEBUG)
    {
        qDebug()<<"ci_ci_thread:receiveData_ci threadid="<<QThread::currentThreadId();
    }
    ci_ci_t ciUdpData;
    quint16 offset = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&ciUdpData, ci_ci_convert_table, ci_ci_convert_table_len);
    if(CI_DEBUG)
    {
        qDebug()<<"ci_ci_thread:len="<<len<<" offset="<<offset<<" moduleid_code"<<ciUdpData.moduleid_code;
    }
    if(len != offset || ciUdpData.moduleid_code!=ID_MESSAGE_CI)
    {
        //qDebug()<<"ci ci thread package might be lost!";
        qWarning("ci ci thread:Error data detected!!!");
        emit error(DataInvalid);
        return;
    }

    //send signals to ui
    emit sendToCiUi(&ciUdpData);

    //send alarm info
    if(ciUdpData.alarm_level > 0)
    {
        vobc_subsys_msg_t alarm;
        alarm.msg_type = 0x12;;
        alarm.sys_id =ciUdpData.moduleid_code;
        alarm.dev_type = ciUdpData.device_type;
        alarm.dev_id = ciUdpData.device_code;
        alarm.dev_local = ciUdpData.device_place;
        alarm.alarm_type = ciUdpData.alarm_type;
        alarm.alarm_subtype = ciUdpData.alarm_subtype;
        alarm.alarm_level = ciUdpData.alarm_level;//level = 1,2,3
        alarm.alarm_code = ciUdpData.detailinfo;
        emit ciAlarm(alarm);
    }
    //save to database
    if(CI_DEBUG)
    {
        qDebug()<<"ci_ci_thread "<<ciUdpData.moduleid_code << "  " <<ciUdpData.detailinfo;
    }
    QString udpSql = "insert into ci_ci_data(moduleid_code, device_type, device_code, device_state, device_place, alarm_type, alarm_subtype, alarm_level, detailinfo) values (?,?,?,?,?,?,?,?,?)";
    dbQuery.prepare(udpSql);
    dbQuery.addBindValue(ciUdpData.moduleid_code);
    dbQuery.addBindValue(ciUdpData.device_type);
    dbQuery.addBindValue(ciUdpData.device_code);
    dbQuery.addBindValue(ciUdpData.device_state);
    dbQuery.addBindValue(ciUdpData.device_place);
    dbQuery.addBindValue(ciUdpData.alarm_type);
    dbQuery.addBindValue(ciUdpData.alarm_subtype);
    dbQuery.addBindValue(ciUdpData.alarm_level);
    dbQuery.addBindValue(ciUdpData.detailinfo);
    if(!dbQuery.exec())
    {
        //qDebug()<<"ci ci thread error"<<dbQuery.lastError() <<" moduleid="<<ciUdpData.moduleid_code;
        qWarning("ci ci thread:Insert data Error!!!");
        emit error(EntryInsertError);
    }
}
void CiService::qDebugErrorValid(QString header)
{
    qWarning()<<"ci route thread "<<header<<" Error data detected!!!";
}
void CiService::qDebugErrorInsert(QString header)
{
    qWarning()<<"ci route thread"<<header<<"Insert data Error!!!";
}
