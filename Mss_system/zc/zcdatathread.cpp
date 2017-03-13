#include "zc/zcdatathread.h"
#include "mssdbconfig.h"

bool zcDataDEBUG = false;

ZcDataThread::ZcDataThread(QString connectionName, QObject *parent) : QObject(parent)
{
    zcConnectname = connectionName;
    zcUdpSocket = new QUdpSocket(this);
    zcUdpSocket->bind(QHostAddress::AnyIPv4, MSS_ZC_PORT);
    connect(zcUdpSocket, &QUdpSocket::readyRead, this, &ZcDataThread::receiveAlarmData);
}
void ZcDataThread::start()
{
    if(!zcDb.isOpen())
    {
        if(openDB())
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]Succeed to openDB!";
        }
        else
        {
            qDebug()<<"[ZcDataThread]Failed to openDB!";
            return;
        }
    }

    zcTable << "zc_ci_ls" << "zc_ci_sp" << "zc_ci_pslr"
             << "zc_ats_tvc" << "zc_ats_tec" << "zc_ats_ts"
             << "zc_vobc_tc" << "zc_vobc_arlr" << "zc_vobc_alr" << "zc_vobc_scm"
             << "zc_monitor";
    zcTableElement <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "c_msg_len smallint unsigned, c_msg_type smallint unsigned, "
                        "c_msg_num smallint unsigned, l_status blob, "
                        "rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "c_msg_len smallint unsigned, c_msg_type smallint unsigned, "
                        "c_msg_num smallint unsigned, s_status blob, "
                        "rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "c_msg_len smallint unsigned, c_msg_type smallint unsigned, "
                        "c_msg_num smallint unsigned, p_seri smallint unsigned, "
                        "rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "a_msg_len smallint unsigned, a_msg_type smallint unsigned, "
                        "z_verify_outcome tinyint unsigned, z_faile_reason tinyint unsigned, "
                        "z_temp_rate_limit tinyint unsigned, z_logic_tracknum smallint unsigned, "
                        "z_logic_track_id smallint unsigned, rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "a_msg_len smallint unsigned, a_msg_type smallint unsigned, "
                        "z_verify_outcome tinyint unsigned, z_alarm_info tinyint unsigned, "
                        "z_temp_rate_limit tinyint unsigned, z_logic_tracknum smallint unsigned, "
                        "z_logic_track_id smallint unsigned, rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "a_msg_len smallint unsigned, a_msg_type smallint unsigned, "
                        "z_power_on_rsq tinyint unsigned, z_logic_tracknum smallint unsigned, "
                        "z_temp_rate_limit smallint unsigned, rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "v_msg_len smallint unsigned, v_msg_type smallint unsigned, "
                        "next_zc_id int unsigned, ma_info_len smallint unsigned, "
                        "ma_dir tinyint unsigned, stop_response tinyint unsigned, "
                        "stop_response_tk_id smallint unsigned, stop_response_tk_offset int unsigned, "
                        "stop_response_obstacles_tk_id smallint unsigned, stop_response_obstacles_tk_offset int unsigned, "
                        "stop_response_overlap tinyint unsigned, ma_start_zone_id smallint unsigned, "
                        "ma_start_zone_offset int unsigned, tk_id smallint unsigned, "
                        "tk_offset int unsigned, obstacles_tk_id smallint unsigned, "
                        "obstacles_tk_offset int unsigned, overlap_valid tinyint unsigned, "
                        "switch_num smallint unsigned, switch_status blob, "
                        "psd_num smallint unsigned, psd_status blob, "
                        "esb_num smallint unsigned, esb_status blob, "
                        "auto_back_button_status tinyint unsigned, temp_speed_limit_num smallint unsigned, "
                        "temp_speed_info blob, destination_status tinyint unsigned, "
                        "rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "v_msg_len smallint unsigned, v_msg_type smallint unsigned, "
                        "request_return tinyint unsigned, unregister_reason tinyint unsigned, "
                        "reserv smallint unsigned, rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "v_msg_len smallint unsigned, v_msg_type smallint unsigned, "
                        "cmd tinyint unsigned, unregister_reason tinyint unsigned, "
                        "reserv smallint unsigned, rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp,"
                        "interface_type smallint unsigned, sender_id int unsigned, "
                        "receiver_id int unsigned, map_version tinyint unsigned, "
                        "map_version_crc32 int unsigned, send_num int unsigned, "
                        "com_period tinyint unsigned, opposite_num int unsigned, "
                        "rcv_num int unsigned, protocol_version tinyint unsigned, "
                        "v_msg_len smallint unsigned, v_msg_type smallint unsigned, "
                        "cmd tinyint unsigned, zc_ci_status tinyint unsigned, "
                        "ma_gener_status_1 tinyint unsigned, ma_gener_status_2 tinyint unsigned, "
                        "train_error_info tinyint unsigned, auto_back_hold_status tinyint unsigned, "
                        "rawdata blob) "
                     <<
                        "(id int auto_increment primary key, time timestamp, "
                        "msg_type smallint unsigned, sys_id smallint unsigned, dev_type tinyint unsigned, "
                        "dev_id smallint unsigned, dev_local tinyint unsigned, "
                        "alarm_type tinyint unsigned, alarm_subtype tinyint unsigned, "
                        "alarm_level tinyint unsigned, alarm_code smallint unsigned, "
                        "rawdata blob) ";


    //create table if not exists
    //zc_ci_logical_section_t
    QString queryStr = "create table if not exists ";
    queryStr.append(zcTable.at(ZC_CI_LS));
    queryStr.append(zcTableElement.at(ZC_CI_LS));
    createTB(queryStr);

    //zc_ci_signal_proximity_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_CI_SP));
    queryStr.append(zcTableElement.at(ZC_CI_SP));
    createTB(queryStr);

    //zc_ci_protect_section_lock_request_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_CI_PSLR));
    queryStr.append(zcTableElement.at(ZC_CI_PSLR));
    createTB(queryStr);

    //zc_ats_tsr_verify_cmd_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_ATS_TVC));
    queryStr.append(zcTableElement.at(ZC_ATS_TVC));
    createTB(queryStr);

    //zc_ats_tsr_execute_cmd_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_ATS_TEC));
    queryStr.append(zcTableElement.at(ZC_ATS_TEC));
    createTB(queryStr);

    //zc_ats_tsr_status_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_ATS_TS));
    queryStr.append(zcTableElement.at(ZC_ATS_TS));
    createTB(queryStr);

    //zc_vobc_train_control_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_VOBC_TC));
    queryStr.append(zcTableElement.at(ZC_VOBC_TC));
    createTB(queryStr);

    //zc_vobc_app_register_logout_response_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_VOBC_ARLR));
    queryStr.append(zcTableElement.at(ZC_VOBC_ARLR));
    createTB(queryStr);

    //zc_vobc_app_logout_request_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_VOBC_ALR));
    queryStr.append(zcTableElement.at(ZC_VOBC_ALR));
    createTB(queryStr);

    //zc_vobc_special_control_msg_t
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_VOBC_SCM));
    queryStr.append(zcTableElement.at(ZC_VOBC_SCM));
    createTB(queryStr);

    //zc_monitor
    queryStr.clear();
    queryStr.append("create table if not exists ");
    queryStr.append(zcTable.at(ZC_MONITOR));
    queryStr.append(zcTableElement.at(ZC_MONITOR));
    createTB(queryStr);
}
ZcDataThread::~ZcDataThread()
{
    qDebug()<<"~ZcDataThread";
    closeDB();
}
bool ZcDataThread::openDB()
{
    zcDb = QSqlDatabase::addDatabase(MSS_DB_DRIVER,zcConnectname);//add MySql driver
    zcDb.setHostName(MSS_DB_HOST_NAME);//hostname
    zcDb.setPort(MSS_DB_PORT);//port
    zcDb.setUserName(MSS_DB_USER);
    zcDb.setPassword(MSS_DB_PASSWORD);
    zcDb.setDatabaseName(MSS_DB_NAME);//database name
    if( zcDb.open() )
    {
        zcQuery = QSqlQuery(zcDb);
        return true;
    }
    else
    {
        qDebug()<<"[ZcDataThread]Failed to connected db!";
        zcDb.close();
        return false;
    }
}
void ZcDataThread::closeDB()
{
    zcDb.close();
}
bool ZcDataThread::createTB(QString QueryStr)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool success = zcQuery.exec(QueryStr);
    if(!success){
        qDebug() << "[ZcDataThread]Create table error" << zcQuery.lastError();
        return false;
    }else{
       // qDebug() << "[ZcDataThread]Create table success";
    }
    return true;
}
bool ZcDataThread::insertData(stream_head_info_t *header, ci_header_info_t *ci_header, QByteArray l_status, quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_ci_ls(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "c_msg_len, c_msg_type, "
                  "c_msg_num, l_status,"
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(ci_header->c_msg_len);
    zcQuery.addBindValue(ci_header->c_msg_type);
    zcQuery.addBindValue(ci_header->c_msg_num);
    zcQuery.addBindValue(l_status);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData_S(stream_head_info_t *header,  ci_header_info_t *ci_header, QByteArray s_status,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_ci_sp(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "c_msg_len, c_msg_type, "
                  "c_msg_num, s_status,"
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(ci_header->c_msg_len);
    zcQuery.addBindValue(ci_header->c_msg_type);
    zcQuery.addBindValue(ci_header->c_msg_num);
    zcQuery.addBindValue(s_status);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, ci_header_info_t *ci_header, protect_zone_lock_rsq_t *datagram,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_ci_pslr(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "c_msg_len, c_msg_type, "
                  "c_msg_num, p_seri, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(ci_header->c_msg_len);
    zcQuery.addBindValue(ci_header->c_msg_type);
    zcQuery.addBindValue(ci_header->c_msg_num);
    zcQuery.addBindValue(datagram->p_seri);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, ats_header_info_t *ats_header, zc_tsr_verify_frame_1_t *datagram1, zc_tsr_verify_frame_2_t *datagram2,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_ats_tvc(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "a_msg_len, a_msg_type, "
                  "z_verify_outcome, z_faile_reason, "
                  "z_temp_rate_limit, z_logic_tracknum, "
                  "z_logic_track_id, rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(ats_header->a_msg_len);
    zcQuery.addBindValue(ats_header->a_msg_type);
    zcQuery.addBindValue(datagram1->z_verify_outcome);
    zcQuery.addBindValue(datagram1->z_faile_reason);
    zcQuery.addBindValue(datagram1->z_temp_rate_limit);
    zcQuery.addBindValue(datagram1->z_logic_tracknum);
    zcQuery.addBindValue(datagram2->z_logic_track_id);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, ats_header_info_t *ats_header, zc_tsr_exeute_frame_1_t *datagram1, zc_tsr_exeute_frame_2_t *datagram2,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_ats_tec(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "a_msg_len, a_msg_type, "
                  "z_verify_outcome, z_alarm_info, "
                  "z_temp_rate_limit, z_logic_tracknum, "
                  "z_logic_track_id, rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(ats_header->a_msg_len);
    zcQuery.addBindValue(ats_header->a_msg_type);
    zcQuery.addBindValue(datagram1->z_verify_outcome);
    zcQuery.addBindValue(datagram1->z_alarm_info);
    zcQuery.addBindValue(datagram1->z_temp_rate_limit);
    zcQuery.addBindValue(datagram1->z_logic_tracknum);
    zcQuery.addBindValue(datagram2->z_logic_track_id);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, ats_header_info_t *ats_header, zc_status_frame_1_t *datagram1, zc_status_frame_2_t *datagram2,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_ats_ts(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "a_msg_len, a_msg_type, "
                  "z_power_on_rsq, z_logic_tracknum, "
                  "z_temp_rate_limit, rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(ats_header->a_msg_len);
    zcQuery.addBindValue(ats_header->a_msg_type);
    zcQuery.addBindValue(datagram1->z_power_on_rsq);
    zcQuery.addBindValue(datagram1->z_logic_tracknum);
    zcQuery.addBindValue(datagram2->z_temp_rate_limit);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, onboard_control_info *datagram,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_vobc_tc(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "v_msg_len, v_msg_type, "
                  "next_zc_id, ma_info_len, "
                  "ma_dir, stop_response, "
                  "stop_response_tk_id, stop_response_tk_offset, "
                  "stop_response_obstacles_tk_id, stop_response_obstacles_tk_offset, "
                  "stop_response_overlap, ma_start_zone_id, "
                  "ma_start_zone_offset, tk_id, "
                  "tk_offset, obstacles_tk_id, "
                  "obstacles_tk_offset, overlap_valid, "
                  "switch_num, switch_status, "
                  "psd_num, psd_status, "
                  "esb_num, esb_status, "
                  "auto_back_button_status, temp_speed_limit_num, "
                  "temp_speed_info, destination_status, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);

    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);

    zcQuery.addBindValue(vobc_header->v_msg_len);
    zcQuery.addBindValue(vobc_header->v_msg_type);
    zcQuery.addBindValue(datagram->next_zc_id);
    zcQuery.addBindValue(datagram->ma_info_len);
    zcQuery.addBindValue(datagram->ma_dir);

    zcQuery.addBindValue(datagram->stop_response);
    zcQuery.addBindValue(datagram->stop_response_tk_id);
    zcQuery.addBindValue(datagram->stop_response_tk_offset);
    zcQuery.addBindValue(datagram->stop_response_obstacles_tk_id);
    zcQuery.addBindValue(datagram->stop_response_obstacles_tk_offset);

    zcQuery.addBindValue(datagram->stop_response_overlap);
    zcQuery.addBindValue(datagram->ma_start_zone_id);
    zcQuery.addBindValue(datagram->ma_start_zone_offset);
    zcQuery.addBindValue(datagram->tk_id);
    zcQuery.addBindValue(datagram->tk_offset);

    zcQuery.addBindValue(datagram->obstacles_tk_id);
    zcQuery.addBindValue(datagram->obstacles_tk_offset);
    zcQuery.addBindValue(datagram->overlap_valid);
    zcQuery.addBindValue(datagram->switch_num);
    zcQuery.addBindValue(0);

    zcQuery.addBindValue(datagram->psd_num);
    zcQuery.addBindValue(0);
    zcQuery.addBindValue(datagram->esb_num);
    zcQuery.addBindValue(0);
    zcQuery.addBindValue(datagram->auto_back_button_status);

    zcQuery.addBindValue(datagram->temp_speed_limit_num);
    zcQuery.addBindValue(0);
    zcQuery.addBindValue(datagram->destination_status);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, onboard_request_respond_t *datagram,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_vobc_arlr(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "v_msg_len, v_msg_type, "
                  "request_return, unregister_reason, "
                  "reserv, rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(vobc_header->v_msg_len);
    zcQuery.addBindValue(vobc_header->v_msg_type);
    zcQuery.addBindValue(datagram->request_return);
    zcQuery.addBindValue(datagram->unregister_reason);
    zcQuery.addBindValue(datagram->reserv);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, onboard_unregister_rsq_t *datagram,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_vobc_alr(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "v_msg_len, v_msg_type, "
                  "cmd, unregister_reason, "
                  "reserv, rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(vobc_header->v_msg_len);
    zcQuery.addBindValue(vobc_header->v_msg_type);
    zcQuery.addBindValue(datagram->cmd);
    zcQuery.addBindValue(datagram->unregister_reason);
    zcQuery.addBindValue(datagram->reserv);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, special_control_cmd_t *datagram,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_vobc_scm(interface_type, sender_id, "
                  "receiver_id, map_version, "
                  "map_version_crc32, send_num, "
                  "com_period, opposite_num, "
                  "rcv_num, protocol_version, "
                  "v_msg_len, v_msg_type, "
                  "cmd, zc_ci_status, "
                  "ma_gener_status_1, ma_gener_status_2, "
                  "train_error_info, auto_back_hold_status, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(header->interface_type);
    zcQuery.addBindValue(header->sender_id);
    zcQuery.addBindValue(header->receiver_id);
    zcQuery.addBindValue(header->map_version);
    zcQuery.addBindValue(header->map_version_crc32);
    zcQuery.addBindValue(header->send_num);
    zcQuery.addBindValue(header->com_period);
    zcQuery.addBindValue(header->opposite_num);
    zcQuery.addBindValue(header->rcv_num);
    zcQuery.addBindValue(header->protocol_version);
    zcQuery.addBindValue(vobc_header->v_msg_len);
    zcQuery.addBindValue(vobc_header->v_msg_type);
    zcQuery.addBindValue(datagram->cmd);
    zcQuery.addBindValue(datagram->zc_ci_status);
    zcQuery.addBindValue(datagram->ma_gener_status_1);
    zcQuery.addBindValue(datagram->ma_gener_status_2);
    zcQuery.addBindValue(datagram->train_error_info);
    zcQuery.addBindValue(datagram->auto_back_hold_status);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
        qDebug() <<"[ZcDataThread]insertData error" << zcQuery.lastError();
    }
    return result;
}
bool ZcDataThread::insertData(vobc_subsys_msg_t *monitor,  quint8 *rawdata,  quint16 len)
{
    if(!zcDb.isOpen())
    {
        openDB();
    }

    bool result = true;
    QString sql = "insert into "
                  "zc_monitor(msg_type, sys_id, dev_type, "
                  "dev_id, dev_local, "
                  "alarm_type, alarm_subtype, "
                  "alarm_level, alarm_code, "
                  "rawdata) "
                  "values(?,?,?,?,?,?,?,?,?,?)";
    zcQuery.prepare(sql);

    zcQuery.addBindValue(monitor->msg_type);
    zcQuery.addBindValue(monitor->sys_id);
    zcQuery.addBindValue(monitor->dev_type);
    zcQuery.addBindValue(monitor->dev_id);
    zcQuery.addBindValue(monitor->dev_local);
    zcQuery.addBindValue(monitor->alarm_type);
    zcQuery.addBindValue(monitor->alarm_subtype);
    zcQuery.addBindValue(monitor->alarm_level);
    zcQuery.addBindValue(monitor->alarm_code);
    zcQuery.addBindValue(QByteArray::fromRawData((char *)rawdata,len));

    result = zcQuery.exec();
    if(!result){
         qDebug() <<"[ZcDataThread]InsertData2 error" << zcQuery.lastError();
    }
    return result;
}

void ZcDataThread::sendSignalUiZcCiLs( )
{
    emit sendUiZcCiLs();
}
void ZcDataThread::sendSignalUiZcCiSp()
{
    emit sendUiZcCiSp();
}
void ZcDataThread::sendSignalUiZcCiPslr()
{
    emit sendUiZcCiPslr();
}
void ZcDataThread::sendSignalUiZcAtsTvc()
{
    emit sendUiZcAtsTvc();
}
void ZcDataThread::sendSignalUiZcAtsTec()
{
    emit sendUiZcAtsTec();
}
void ZcDataThread::sendSignalUiZcAtsTs()
{
    emit sendUiZcAtsTs();
}
void ZcDataThread::sendSignalUiZcVobcTc()
{
    emit sendUiZcVobcTc();
}
void ZcDataThread::sendSignalUiZcVobcArlr()
{
    emit sendUiZcVobcArlr();
}
void ZcDataThread::sendSignalUiZcVobcAlr()
{
    emit sendUiZcVobcAlr();
}
void ZcDataThread::sendSignalUiZcVobcScm()
{
    emit sendUiZcVobcScm();
}
void ZcDataThread::sendSignalUiZcAlarm(vobc_subsys_msg_t alarm)
{
    emit sendUiZcAlarm(alarm);
}
void ZcDataThread::sendReceiveDataOk()
{
    emit receiveDataOk();
}
void ZcDataThread::sendReceiveAlarmDataOk()
{
    emit receiveAlarmDataOk();
}
void ZcDataThread::sendError(int code)
{
    emit error(code);
}
bool ZcDataThread::dealZcCi(quint8 *buf, quint16 len, stream_head_info_t *header)
{
    if(buf == NULL || len < STREAM_HEAD_LEN + CI_HEAD_LEN)
    {
        qDebug()<<"[ZcDataThread]dealZcCi: unknown data";
        sendError(DataInvalid);
        return false;
    }
    quint16 msgOffset,check_len;
    QByteArray qba;
    ci_header_info_t m_ci_header_info_t;
    msgOffset = b2v_bytes_to_var_byoffset(buf,
                                         STREAM_HEAD_LEN,
                                         (quint8 *)&m_ci_header_info_t,
                                          ci_header_destbl_table,
                                          ci_header_destbl_table_len);
    check_len = msgOffset;
    if(zcDataDEBUG) qDebug("[ZcDataThread]msg_type(INTERFACE_ZC_CI):0x%x", m_ci_header_info_t.c_msg_type);
    switch (m_ci_header_info_t.c_msg_type)
    {
    case LOGIC_ZONE_STATUS:
    {
        if(len < STREAM_HEAD_LEN + CI_HEAD_LEN + LOGIC_TRACK)
        {
            qDebug()<<"[ZcDataThread]dealZcCi(LOGIC_ZONE_STATUS): unknown data";
            sendError(DataInvalid);
            return false;
        }
        logic_track_info_t m_logic_track_info_t;
        qba.resize(m_ci_header_info_t.c_msg_num);
        for(int i=0;i<m_ci_header_info_t.c_msg_num*0.5;i++)
        {
            msgOffset = b2v_bytes_to_var_byoffset(buf,
                                                  check_len,
                                                  (quint8 *)&m_logic_track_info_t,
                                                  logicTrack_destbl_table,
                                                  logicTrack_destbl_table_len);
            check_len = msgOffset;
            qba[i*2] = m_logic_track_info_t.l_status&0x0f;
            if( (i*2+1) < m_ci_header_info_t.c_msg_num ) qba[i*2+1] = (m_logic_track_info_t.l_status&0xf0)>>4;
        }

        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]LOGIC_ZONE_STATUS check_len == len";
            if(insertData(header, &m_ci_header_info_t, qba, buf, len))
            {
                sendSignalUiZcCiLs();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]LOGIC_ZONE_STATUS insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]LOGIC_ZONE_STATUS check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case SIGNAL_NEAR_INFO:
    {
        if(len < STREAM_HEAD_LEN + CI_HEAD_LEN + SIGNAL_CLOSE)
        {
            qDebug()<<"[ZcDataThread]dealZcCi(SIGNAL_NEAR_INFO): unknown data";
            sendError(DataInvalid);
            return false;
        }
        signal_close_info_t m_signal_close_info_t;
        qba.resize(m_ci_header_info_t.c_msg_num);
        for(int i=0;i<m_ci_header_info_t.c_msg_num;i++)
        {
            msgOffset = b2v_bytes_to_var_byoffset(buf,
                                                  check_len,
                                                  (quint8 *)&m_signal_close_info_t,
                                                  signalClose_destbl_table,
                                                  signalClose_destbl_table_len);
            check_len = msgOffset;
            qba[i] = m_signal_close_info_t.s_status;
        }

        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]SIGNAL_NEAR_INFO check_len == len";
            if(insertData_S(header, &m_ci_header_info_t, qba, buf, len))
            {
                sendSignalUiZcCiSp();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]SIGNAL_NEAR_INFO insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]SIGNAL_NEAR_INFO check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case PROTECT_ZONE_LOCK_ASK:
    {
        if(len < STREAM_HEAD_LEN + CI_HEAD_LEN + ROUTE_UNLOCK_RSQ)
        {
            qDebug()<<"[ZcDataThread]dealZcCi(PROTECT_ZONE_LOCK_ASK): unknown data";
            sendError(DataInvalid);
            return false;
        }
        protect_zone_lock_rsq_t m_protect_zone_lock_rsq_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_protect_zone_lock_rsq_t,
                                              routeUnlockRsq_destbl_table,
                                              routeUnlockRsq_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]PROTECT_ZONE_LOCK_ASK check_len == len";
            if( insertData(header, &m_ci_header_info_t, &m_protect_zone_lock_rsq_t, buf, len) )
            {
                sendSignalUiZcCiPslr();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]PROTECT_ZONE_LOCK_ASK insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]PROTECT_ZONE_LOCK_ASK check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    default:
    {
        qDebug()<<"[ZcDataThread]unknown meg type";
        sendError(DataInvalid);
    }
        break;
    }
    return false;
}
bool ZcDataThread::dealZcAts(quint8 *buf, quint16 len, stream_head_info_t *header)
{
    if(buf == NULL || len < STREAM_HEAD_LEN + ATS_HEAD_LEN)
    {
        qDebug()<<"[ZcDataThread]dealZcAts: unknown data";
        sendError(DataInvalid);
        return false;
    }
    quint16 msgOffset,check_len;
    ats_header_info_t m_ats_header_info_t;
    msgOffset = b2v_bytes_to_var_byoffset(buf,
                                         STREAM_HEAD_LEN,
                                         (quint8 *)&m_ats_header_info_t,
                                          ats_header_destbl_table,
                                          ats_header_destbl_table_len);
    check_len = msgOffset;
    if(zcDataDEBUG) qDebug("[ZcDataThread]msg_type(INTERFACE_ZC_ATS):0x%x", m_ats_header_info_t.a_msg_type);
    switch (m_ats_header_info_t.a_msg_type)
    {
    case ZC_TSR_VERIFY_FRAME:
    {
        if(len < STREAM_HEAD_LEN + ATS_HEAD_LEN + ZC_TSR_VERIFY_FRAME_1 + ZC_TSR_VERIFY_FRAME_2)
        {
            qDebug()<<"[ZcDataThread]dealZcAts(ZC_TSR_VERIFY_FRAME): unknown data";
            sendError(DataInvalid);
            return false;
        }
        zc_tsr_verify_frame_1_t m_zc_tsr_verify_frame_1_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_zc_tsr_verify_frame_1_t,
                                              zc_tsr_verify_frame_1_destbl_table,
                                              zc_tsr_verify_frame_1_destbl_table_len);
        check_len = msgOffset;
        zc_tsr_verify_frame_2_t m_zc_tsr_verify_frame_2_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_zc_tsr_verify_frame_2_t,
                                              zc_tsr_verify_frame_2_destbl_table,
                                              zc_tsr_verify_frame_2_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_TSR_VERIFY_FRAME check_len == len";
            if( insertData(header, &m_ats_header_info_t, &m_zc_tsr_verify_frame_1_t, &m_zc_tsr_verify_frame_2_t, buf, len) )
            {
                sendSignalUiZcAtsTvc();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_TSR_VERIFY_FRAME insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_TSR_VERIFY_FRAME check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case ZC_TSR_EXEUTE_FRAME:
    {
        if(len < STREAM_HEAD_LEN + ATS_HEAD_LEN + ZC_TSR_EXEUTE_FRAME_1 + ZC_TSR_EXEUTE_FRAME_2)
        {
            qDebug()<<"[ZcDataThread]dealZcAts(ZC_TSR_EXEUTE_FRAME): unknown data";
            sendError(DataInvalid);
            return false;
        }
        zc_tsr_exeute_frame_1_t m_zc_tsr_exeute_frame_1_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_zc_tsr_exeute_frame_1_t,
                                              zc_tsr_exeute_frame_1_destbl_table,
                                              zc_tsr_exeute_frame_1_destbl_table_len);
        check_len = msgOffset;
        zc_tsr_exeute_frame_2_t m_zc_tsr_exeute_frame_2_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_zc_tsr_exeute_frame_2_t,
                                              zc_tsr_exeute_frame_2_destbl_table,
                                              zc_tsr_exeute_frame_2_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_TSR_EXEUTE_FRAME check_len == len";
            if( insertData(header, &m_ats_header_info_t, &m_zc_tsr_exeute_frame_1_t, &m_zc_tsr_exeute_frame_2_t, buf, len) )
            {
                sendSignalUiZcAtsTec();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_TSR_EXEUTE_FRAME insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_TSR_EXEUTE_FRAME check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case ZC_STATUS_INFO_FRAME:
    {
        if(len < STREAM_HEAD_LEN + ATS_HEAD_LEN + ZC_STATUS_FRAME_1 + ZC_STATUS_FRAME_2)
        {
            qDebug()<<"[ZcDataThread]dealZcAts(ZC_STATUS_INFO_FRAME): unknown data";
            sendError(DataInvalid);
            return false;
        }
        zc_status_frame_1_t m_zc_status_frame_1_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_zc_status_frame_1_t,
                                              zc_status_frame_1_destbl_table,
                                              zc_status_frame_1_destbl_table_len);
        check_len = msgOffset;
        zc_status_frame_2_t m_zc_status_frame_2_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_zc_status_frame_2_t,
                                              zc_status_frame_2_destbl_table,
                                              zc_status_frame_2_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_STATUS_INFO_FRAME check_len == len";
            if( insertData(header, &m_ats_header_info_t, &m_zc_status_frame_1_t, &m_zc_status_frame_2_t, buf, len) )
            {
                sendSignalUiZcAtsTs();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_STATUS_INFO_FRAME insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_STATUS_INFO_FRAME check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    default:
    {
        qDebug()<<"[ZcDataThread]unknown meg type";
        sendError(DataInvalid);
    }
        break;
    }
    return false;
}
bool ZcDataThread::dealZcVobc(quint8 *buf, quint16 len, stream_head_info_t *header)
{
    if(buf == NULL || len < STREAM_HEAD_LEN + VOBC_HEAD_LEN)
    {
        qDebug()<<"[ZcDataThread]dealZcVobc: unknown data";
        sendError(DataInvalid);
        return false;
    }
    quint16 msgOffset,check_len;
    vobc_header_info_t m_vobc_header_info_t;
    msgOffset = b2v_bytes_to_var_byoffset(buf,
                                         STREAM_HEAD_LEN,
                                         (quint8 *)&m_vobc_header_info_t,
                                          vobc_header_destbl_table,
                                          vobc_header_destbl_table_len);
    check_len = msgOffset;
    if(zcDataDEBUG) qDebug("[ZcDataThread]msg_type(INTERFACE_ZC_VOBC):0x%x", m_vobc_header_info_t.v_msg_type);
    switch (m_vobc_header_info_t.v_msg_type)
    {
    case ZC_CONTROLTRAIN:
    {
        if(len < STREAM_HEAD_LEN + VOBC_HEAD_LEN + ONBOARD_CONTROL)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_CONTROLTRAIN): unknown data";
            sendError(DataInvalid);
            return false;
        }
        onboard_control_info_t m_onboard_control_info_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              onboard_control_1_destbl_table,
                                              onboard_control_1_destbl_table_len);
        check_len = msgOffset;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              switch_num_destbl_table,
                                              switch_num_destbl_table_len);
        check_len = msgOffset;
        if(m_onboard_control_info_t.switch_num > MA_SWITCH_NUM_MAX)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_CONTROLTRAIN): unknown data";
            sendError(DataInvalid);
            return false;
        }
        switch_status_t m_switch_status_t;
        for(int i=0;i<m_onboard_control_info_t.switch_num;i++)
        {
            msgOffset = b2v_bytes_to_var_byoffset(buf,
                                                  check_len,
                                                  (quint8 *)&m_switch_status_t,
                                                  switch_status_destbl_table,
                                                  switch_status_destbl_table_len);
            check_len = msgOffset;
            m_onboard_control_info_t.switch_status[i] = m_switch_status_t;
        }
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              psd_num_destbl_table,
                                              psd_num_destbl_table_len);
        check_len = msgOffset;
        if(m_onboard_control_info_t.psd_num > MA_PSD_NUM_MAX)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_CONTROLTRAIN): unknown data";
            sendError(DataInvalid);
            return false;
        }
        PSD_status_t m_PSD_status_t;
        for(int i=0;i<m_onboard_control_info_t.psd_num;i++)
        {
            msgOffset = b2v_bytes_to_var_byoffset(buf,
                                                  check_len,
                                                  (quint8 *)&m_PSD_status_t,
                                                  psd_status_destbl_table,
                                                  psd_status_destbl_table_len);
            check_len = msgOffset;
            m_onboard_control_info_t.psd_status[i] = m_PSD_status_t;
        }
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              esb_num_destbl_table,
                                              esb_num_destbl_table_len);
        check_len = msgOffset;
        if(m_onboard_control_info_t.esb_num > MA_ESB_NUM_MAX)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_CONTROLTRAIN): unknown data";
            sendError(DataInvalid);
            return false;
        }
        ESB_status_t m_ESB_status_t;
        for(int i=0;i<m_onboard_control_info_t.esb_num;i++)
        {
            msgOffset = b2v_bytes_to_var_byoffset(buf,
                                                  check_len,
                                                  (quint8 *)&m_ESB_status_t,
                                                  esb_status_destbl_table,
                                                  esb_status_destbl_table_len);
            check_len = msgOffset;
            m_onboard_control_info_t.esb_status[i] = m_ESB_status_t;
        }
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              onboard_control_2_destbl_table,
                                              onboard_control_2_destbl_table_len);
        check_len = msgOffset;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              temp_speed_num_destbl_table,
                                              temp_speed_num_destbl_table_len);
        check_len = msgOffset;
        if(m_onboard_control_info_t.temp_speed_limit_num > MA_LIMIT_NUM_MAX)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_CONTROLTRAIN): unknown data";
            sendError(DataInvalid);
            return false;
        }
        temp_speed_limit_info_t m_temp_speed_limit_info_t;
        for(int i=0;i<m_onboard_control_info_t.temp_speed_limit_num;i++)
        {
            msgOffset = b2v_bytes_to_var_byoffset(buf,
                                                  check_len,
                                                  (quint8 *)&m_temp_speed_limit_info_t,
                                                  temp_speed_status_destbl_table,
                                                  temp_speed_status_destbl_table_len);
            check_len = msgOffset;
            m_onboard_control_info_t.temp_speed_info[i] = m_temp_speed_limit_info_t;
        }
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_control_info_t,
                                              onboard_control_3_destbl_table,
                                              onboard_control_3_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_CONTROLTRAIN check_len == len";
            if( insertData(header, &m_vobc_header_info_t, &m_onboard_control_info_t, buf, len) )
            {
                sendSignalUiZcVobcTc();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_CONTROLTRAIN insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_CONTROLTRAIN check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case ZC_RESPOND_RSQ:
    {
        if(len < STREAM_HEAD_LEN + VOBC_HEAD_LEN + ONBOARD_REQUEST_RESPOND_LEN)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_RESPOND_RSQ): unknown data";
            sendError(DataInvalid);
            return false;
        }
        onboard_request_respond_t m_onboard_request_respond_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_request_respond_t,
                                              onboard_request_respond_destbl_table,
                                              onboard_request_respond_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_RESPOND_RSQ check_len == len";
            if( insertData(header, &m_vobc_header_info_t, &m_onboard_request_respond_t, buf, len) )
            {
                sendSignalUiZcVobcArlr();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_RESPOND_RSQ insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_RESPOND_RSQ check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case ZC_UNREGISTER_RSQ:
    {
        if(len < STREAM_HEAD_LEN + VOBC_HEAD_LEN + ONBOARD_UNREGISTER_RSQ_LEN)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_UNREGISTER_RSQ): unknown data";
            sendError(DataInvalid);
            return false;
        }
        onboard_unregister_rsq_t m_onboard_unregister_rsq_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_onboard_unregister_rsq_t,
                                              onboard_unregister_rsq_destbl_table,
                                              onboard_unregister_rsq_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_UNREGISTER_RSQ check_len == len";
            if( insertData(header, &m_vobc_header_info_t, &m_onboard_unregister_rsq_t, buf, len) )
            {
                sendSignalUiZcVobcAlr();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_UNREGISTER_RSQ insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_UNREGISTER_RSQ check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    case ZC_SPECIAL_MSG:
    {
        if(len < STREAM_HEAD_LEN + VOBC_HEAD_LEN + SPECIAL_CONTROL_LEN)
        {
            qDebug()<<"[ZcDataThread]dealZcVobc(ZC_SPECIAL_MSG): unknown data";
            sendError(DataInvalid);
            return false;
        }
        special_control_cmd_t m_special_control_cmd_t;
        msgOffset = b2v_bytes_to_var_byoffset(buf,
                                              check_len,
                                              (quint8 *)&m_special_control_cmd_t,
                                              special_control_destbl_table,
                                              special_control_destbl_table_len);
        check_len = msgOffset;
        if(check_len == len)
        {
            if(zcDataDEBUG) qDebug()<<"[ZcDataThread]ZC_SPECIAL_MSG check_len == len";
            if( insertData(header, &m_vobc_header_info_t, &m_special_control_cmd_t, buf, len) )
            {
                sendSignalUiZcVobcScm();
                return true;
            }
            else
            {
                qDebug()<<"[ZcDataThread]ZC_SPECIAL_MSG insertData error";
                sendError(InsertError);
                return false;
            }
        }
        else
        {
            qDebug()<<"[ZcDataThread]ZC_SPECIAL_MSG check_len != len";
            sendError(DataInvalid);
            return false;
        }
    }
        break;
    default:
    {
        qDebug()<<"[ZcDataThread]unknown meg type";
        sendError(DataInvalid);
    }
        break;
    }
    return false;
}
void ZcDataThread::receiveData(quint8* buf, quint16 len)
{
    if(buf == NULL || len < STREAM_HEAD_LEN)
    {
        qDebug()<<"[ZcDataThread]onReceiveData: unknown data";
        sendError(DataInvalid);
        return;
    }
    if(zcDataDEBUG) qDebug()<<"[ZcDataThread]onReceiveData len:"<<len;
    stream_head_info_t m_stream_head_info_t;
    quint16 msgOffset;
    msgOffset = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&m_stream_head_info_t, stream_header_destbl_table, stream_header_destbl_table_len);
    if(zcDataDEBUG) qDebug("[ZcDataThread]onReceiveData header:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",m_stream_head_info_t.interface_type,
                           m_stream_head_info_t.sender_id, m_stream_head_info_t.receiver_id, m_stream_head_info_t.map_version,
                           m_stream_head_info_t.map_version_crc32, m_stream_head_info_t.send_num, m_stream_head_info_t.com_period,
                           m_stream_head_info_t.opposite_num, m_stream_head_info_t.rcv_num, m_stream_head_info_t.protocol_version);

    if(msgOffset != STREAM_HEAD_LEN)
    {
        qDebug()<<"[ZcDataThread]onReceiveData: HeaderError";
        sendError(HeaderError);
        return;
    }

    switch (m_stream_head_info_t.interface_type)
    {
    case INTERFACE_ZC_CI:
    {
        if( dealZcCi(buf, len, &m_stream_head_info_t))
        {
            sendReceiveDataOk();
        }
        else
        {
            qDebug()<<"[ZcDataThread]dealZcCi error";
            sendError(DealDataError);
        }
    }
        break;
    case INTERFACE_ZC_ATS:
    {
        if(dealZcAts(buf, len, &m_stream_head_info_t))
        {
            sendReceiveDataOk();
        }
        else
        {
            qDebug()<<"[ZcDataThread]dealZcAts error";
            sendError(DealDataError);
        }
    }
        break;
    case INTERFACE_ZC_VOBC:
    {
        if(dealZcVobc(buf, len, &m_stream_head_info_t))
        {
            sendReceiveDataOk();
        }
        else
        {
            qDebug()<<"[ZcDataThread]dealZcVobc error";
            sendError(DealDataError);
        }
    }
        break;
    default:
    {
        qDebug()<<"[ZcDataThread]unknown interface error";
        sendError(DataInvalid);
    }
        break;
    }
}
void ZcDataThread::receiveAlarmData()
{
    char buf[256] = {0};
    QHostAddress clientAddr;
    quint16 clientPort;
    quint16 len = zcUdpSocket->readDatagram(buf, sizeof(buf), &clientAddr, &clientPort);
    if(buf == NULL || len < ZC_MONITOR_LEN)
    {
        qDebug()<<"[ZcDataThread]receiveAlarmData: unknown data";
        sendError(DataInvalid);
        return;
    }
    vobc_subsys_msg_t m_vobc_subsys_msg_t;
    quint16 msgOffset;
    msgOffset = b2v_bytes_to_var((quint8 *)buf, (quint8 *)&m_vobc_subsys_msg_t, vobc_subsys_cv_table, vobc_subsys_cv_table_len);
    if(zcDataDEBUG) qDebug("[ZcDataThread]receiveAlarmData:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x",m_vobc_subsys_msg_t.sys_id, m_vobc_subsys_msg_t.dev_type, m_vobc_subsys_msg_t.dev_id, m_vobc_subsys_msg_t.dev_local, m_vobc_subsys_msg_t.alarm_type, m_vobc_subsys_msg_t.alarm_subtype, m_vobc_subsys_msg_t.alarm_level, m_vobc_subsys_msg_t.alarm_code);
    if(zcDataDEBUG) qDebug()<<"[ZcDataThread]receiveAlarmData len:"<<len;
    if(msgOffset == len)
    {
        if(insertData(&m_vobc_subsys_msg_t, (quint8 *)buf, len))
        {
            sendSignalUiZcAlarm(m_vobc_subsys_msg_t);
            sendReceiveAlarmDataOk();
        }
        else
        {
            qDebug()<<"[ZcDataThread]receiveAlarmData insertData error";
            sendError(InsertError);
        }
    }
    else
    {
        qDebug()<<"[ZcDataThread]receiveAlarmData msgOffset != len";
        sendError(DataInvalid);
    }
}
