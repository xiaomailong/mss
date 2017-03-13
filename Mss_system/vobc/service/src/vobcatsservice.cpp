#include "vobcatsservice.h"
#include "../../vobcuicommon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mssdbconfig.h"

VobcAtsService::VobcAtsService(QObject *parent) : QObject(parent),
    connectName("VobcAtsDB"),
    isInstDisplay(false)
{

}

VobcAtsService::~VobcAtsService()
{

}
bool VobcAtsService::openDatabase()
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

bool VobcAtsService::createTable(const QString &queryStr)
{
    return query.exec(queryStr);
}

void VobcAtsService::closeDatabase()
{
    db.close();
}

void VobcAtsService::printDatabaseError()
{
    if(!db.isOpen())
    {
        VOBC_WARN() << "DB is NOT ready!";
        VOBC_WARN() << db.lastError().text();
    }
    else
    {
        VOBC_WARN()<< query.lastError().text();
    }
}
void VobcAtsService::startService()
{
    bool ret = false;
    if(openDatabase())
    {
        ret = createTable("create table if not exists "
                          "vobc_subsys_alarm(id int unsigned primary key auto_increment,"
                          "time timestamp not null default current_timestamp, "
                          "interface_type smallint unsigned,send_id_msg int unsigned,incept_id_msg int unsigned, "
                          "edition_control_msg tinyint unsigned, edition_check_msg int unsigned, msg_list int unsigned, "
                          "com_cycle tinyint unsigned, opposite_msg_list int unsigned, smsg_self_list int unsigned, "
                          "pro_edition tinyint unsigned, "
                          "msg_len smallint unsigned, msg_type smallint unsigned, "
                          "sys_id int, dev_type int, dev_id int, "
                          "dev_local int, alarm_type int, alarm_subtype int, "
                          "alarm_level int, alarm_code int, "
                          "rawdata blob)");
        if (!ret)
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

void VobcAtsService::stopService()
{
    closeDatabase();
}
void VobcAtsService::handleAtsData(quint8* buf, quint16 len)
{
    vobc_ats_header_t commonHeader;
    quint16 msgOffset = 0;
    quint16 bufSize = 0;
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

    if((commonHeader.vobc_ats_interface != ATS_MSS_INTERFACE)
     ||(commonHeader.send_id_msg != ID_MESSAGE_VOBC))
    {
        VOBC_WARN() << "not vobc alarm info";
        emit castError(ErrInvalidArgument);
        return;
    }

    vobc_app_header_len_t appLength;
    bufSize = b2v_bytes_to_var_byoffset(buf,
                                        msgOffset,
                                        (quint8 *)&appLength,
                                        vobc_msg_len_cv_table,
                                        vobc_msg_len_cv_table_len);
    //get subsys msg_type
    uint16_t msgType;
    b2v_bytes_to_var_byoffset(buf,
                              bufSize,
                              (quint8 *)&msgType,
                              vobc_subsys_msg_type_cv_table,
                              vobc_subsys_msg_type_cv_table_len);

    switch (msgType) {
    case ATS_MSS_ALARM_MSG_TYPE:
    {
        MssSubSysVobc totalMsg;
        totalMsg.common_header = commonHeader;
        totalMsg.app_len = appLength;
        bufSize= b2v_bytes_to_var_byoffset(buf,
                                           bufSize,
                                           (quint8 *)&totalMsg.datagram,
                                           vobc_subsys_cv_table,
                                           vobc_subsys_cv_table_len);

        if(bufSize == len)
        {
            ret = insertData(TableSubsysVobcAlarm, &totalMsg, buf, bufSize);
            if(!ret)
            {
                printDatabaseError();
                emit castError(ErrInsertTable);
            }
            else
            {
                if(true == isInstDisplay)
                {
                    emit reportAlarmMsg(totalMsg.datagram);
                }
            }
        }
        else
        {
            VOBC_WARN("Length is NOT equal! bufsize(0x%x) inputlength(0x%x) type = 0x%x",
                      bufSize, len, commonHeader.vobc_ats_interface);
            emit castError(ErrInvalidArgument);
        }
    }
        break;
    default:
    {
    }
        break;
    }

    delete[] buf;

}
void VobcAtsService::setInstFlag(bool flag)
{
    isInstDisplay = flag;
}

bool VobcAtsService::insertData(EVobcTb tableName, void *data, void *rawData, quint16 length)
{
    bool ret = false;

    if(!db.isOpen())
    {
        return false;
    }

    switch (tableName) {
    case TableSubsysVobcAlarm:
    {
        MssSubSysVobc *datagram = (MssSubSysVobc *)data;
        query.prepare("insert into vobc_subsys_alarm(interface_type, send_id_msg, incept_id_msg, "
                      "edition_control_msg, edition_check_msg, msg_list, "
                      "com_cycle, opposite_msg_list, smsg_self_list, pro_edition,"
                      "msg_len, msg_type, "
                      "sys_id, dev_type, dev_id, "
                      "dev_local, alarm_type, alarm_subtype, "
                      "alarm_level, alarm_code, "
                      "rawdata) "
                      "values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
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
        query.addBindValue(datagram->datagram.sys_id);
        query.addBindValue(datagram->datagram.dev_type);
        query.addBindValue(datagram->datagram.dev_id);
        query.addBindValue(datagram->datagram.dev_local);
        query.addBindValue(datagram->datagram.alarm_type);
        query.addBindValue(datagram->datagram.alarm_subtype);
        query.addBindValue(datagram->datagram.alarm_level);
        query.addBindValue(datagram->datagram.alarm_code);
        query.addBindValue(QByteArray::fromRawData((char *)rawData,length));

        ret = query.exec();
    }
        break;
    case TableSubsysVobcState:
    {

    }
        break;
    default:
    {

    }
        break;
    }

    return ret;
}
