#include "powerprocess.h"
#include "mssdbconfig.h"
#include "power_data.h"

#include <QDebug>

static int HandleOfRealtime;

PowerProcess::PowerProcess(QObject *parent) : QObject(parent)
{
#ifdef USE_UDP
    udpSocketOfPowerReceive = new QUdpSocket(this);
    udpSocketOfPowerReceive->bind(QHostAddress::AnyIPv4, MSS_POWER_PORT);
    connect(udpSocketOfPowerReceive, &QUdpSocket::readyRead, this, &PowerProcess::receiveDataByUDP);
#endif
}

void PowerProcess::start()
{
    //1.init the Basic Functions of power Monitor system
    initPowerInfo();

    //2.open db
    openDB();

    //3.create table of info if not exists
    QString queryStr = "create table if not exists "
                       "psp_infomanage(id int auto_increment primary key,voltage float,current float, "
                       "frequency float,phase float,"
                       "handle int,type int,statue int,"
                       "level int,savetime datetime,rawdata varchar(255))";
    createTBOfInfo(queryStr);

    queryStr.clear();

    //4.create device table of device if not exists
    queryStr = "create table if not exists "
               "device(id int auto_increment primary key,devicename varchar(255),handle int)";
    if(createTBOfDevice(queryStr))
    {
        emit started();
    }

}

void PowerProcess::initPowerInfo()
{
    isNeedPressent = false;
}

void PowerProcess::openDB(){
    db = QSqlDatabase::addDatabase(MSS_DB_DRIVER,"power");
    db.setDatabaseName(MSS_DB_NAME);
    db.setHostName(MSS_DB_HOST_NAME);
    db.setPort(MSS_DB_PORT);
    db.setUserName(MSS_DB_USER);
    db.setPassword(MSS_DB_PASSWORD);
    bool openSuccess = db.open();
    if(!openSuccess)
    {
        qDebug()<<"[PowerProcess] Failed to connected db!";
        db.close();
        emit error(DBOpenError);
    }
    else
    {
        qDebug()<<"[PowerProcess] connect db.power success !!!";
    }
}

bool PowerProcess::createTBOfInfo(QString QueryStr)
{
    QSqlQuery query(db);
    bool success = query.exec(QueryStr);
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << "[PowerProcess] create the table of informanage error" << lastError.driverText();
        emit error(TBCreateError);
        return false;
    }
    return true;
}

bool PowerProcess::createTBOfDevice(QString QueryStr)
{
    QSqlQuery query(db);
    bool createSuccess = query.exec(QueryStr);

    if(!createSuccess)
    {
        QSqlError lastError = query.lastError();
        qDebug() << "[PowerProcess] create the table of informanage error" << lastError.driverText();
        emit error(TBCreateError);
        return false;
    }

    query.exec("insert into device (devicename,handle) values ('dc_001','1') ");
    query.exec("insert into device (devicename,handle) values ('dc_002','2') ");
    query.exec("insert into device (devicename,handle) values ('dc_003','3') ");
    query.exec("insert into device (devicename,handle) values ('dc_004','4') ");
    query.exec("insert into device (devicename,handle) values ('ac_001','5') ");
    query.exec("insert into device (devicename,handle) values ('ac_002','6') ");
    query.exec("insert into device (devicename,handle) values ('ac_003','7') ");
    return true;
}
void PowerProcess::closeDB()
{
    db.close();
    QSqlDatabase::removeDatabase(MSS_DB_NAME);
}

bool PowerProcess::insertData(PspTb tbname,void *rawdata)
{
    bool insertSuccess = true;
    QSqlQuery query(db);

    if(!db.isOpen())
    {
        openDB();
        if(!db.isOpen())
        {
            qWarning() << "DB is NOT ready!";
            qWarning() << db.lastError().text();
            return false;
        }

        if(!db.tables().contains("psp_infomanage"))
        {
            QString queryStr = "create table if not exists "
                               "psp_infomanage(id int auto_increment primary key,voltage float,current float, "
                               "frequency float,phase float,"
                               "handle int,type int,statue int,"
                               "level int,savetime datetime,rawdata varchar(255))";
            createTBOfInfo(queryStr);
        }
    }

    switch (tbname)
    {
    case PSP_INFORMATION:
    {
        query.prepare("insert into psp_infomanage(voltage,"
                      "current,frequency,phase,handle,type,statue,level,savetime,rawdata)"
                      "values(?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(ims.valueOfVoltage);
        query.addBindValue(ims.valueOfCurrent);
        query.addBindValue(ims.frequencyOfAC);
        query.addBindValue(ims.phaseOfAC);
        query.addBindValue(ims.handle);
        query.addBindValue(ims.type);
        query.addBindValue(ims.owner);
        query.addBindValue(ims.level);
        QDateTime time = QDateTime::currentDateTime();
        query.addBindValue(time);
        query.addBindValue(*(quint8 *)rawdata);
        insertSuccess = query.exec();
    }
        break;
    default:
        break;
    }


    if(!insertSuccess)
    {
        QSqlError lastError = query.lastError();
        qDebug() <<"[PowerProcess] "<< lastError.driverText() << "insert error";
        emit error(InsertError);
        return false;
    }
    return insertSuccess;
}


/*  connect slots
 *  reveive the data from sender
 *
 * */
void PowerProcess::receiveData(quint8* buf, quint16 len)
{
    //infomanage_t infomag;
    if(buf == NULL || len < POWER_HEADER_LEN)
    {
        qDebug()<<"[PowerProcess] receiveData: unknown data";
        emit error(DataInvalid);
        return;
    }
    power_data_header_t a;
    b2v_bytes_to_var((quint8 *)buf, (quint8 *)&a, power_data_header_cv_table, power_data_header_cv_table_len);

    //receive and analy data
    ims = analyInfo(&a);

    if(ims.handle == 0)
    {
        qDebug()<<"[PowerProcess] receiveData: DataInvalid";
        emit error(DataInvalid);
        return;
    }
    else
    {
        emit dataReceived();
    }

    if(isAlarm(&ims))
    {
        // poll the alarm information
        pollAlarm(&alarm);
    }

    //judge whether need pool real-time data
    if(isNeedPressent)
    {
         pollPresentData(&ims);
    }

    insertData(PSP_INFORMATION, buf);
}

#ifdef USE_UDP
void PowerProcess::receiveDataByUDP()
{
    char buf[256] = {0};
    QHostAddress cliAddr;
    quint16 port;
    quint16 len = udpSocketOfPowerReceive->readDatagram(buf, sizeof(buf), &cliAddr, &port);

    if(buf == NULL || len < POWER_HEADER_LEN)
    {
        qDebug()<<"[PowerProcess] receiveDataByUDP: unknown data";
        emit error(DataInvalid);
        return;
    }

    power_data_header_t a;
    b2v_bytes_to_var((quint8 *)buf, (quint8 *)&a, power_data_header_cv_table, power_data_header_cv_table_len);

    //receive and analy data
    ims = analyInfo(&a);

    if(ims.handle == 0)
    {
        qDebug()<<"[PowerProcess] receiveData: DataInvalid";
        emit error(DataInvalid);
        return;
    }
    else
    {
        emit dataReceived();
    }

    if(isAlarm(&ims))
    {
        //poll the alarm information
        pollAlarm(&alarm);
    }

    if(isNeedPressent)
    {
         pollPresentData(&ims);
    }

    insertData(PSP_INFORMATION, buf);
}
#endif

infomanage_t PowerProcess::analyInfo(power_data_header_t *data)
{
    //convert the data from the thread of sending ...
    infomanage_t ims;
    ims.handle = data->handle;
    ims.owner = data->owner;
    ims.type = data->type;
    ims.valueOfVoltage = data->voltage;
    ims.valueOfCurrent = data->current;

    if(ims.type)
    {
        //data of ac
        ims.phaseOfAC = data->angle;
        ims.frequencyOfAC = data->hz;
    }
    else
    {
        //data of dc
        ims.phaseOfAC = 0;
        ims.frequencyOfAC = 0;
    }
    return ims;
}


bool PowerProcess::isAlarm(infomanage_t *imfo)
{
    bool isNeedAlarm = false;
    //judge whether the valueOfVoltage is a alarm
    if((((float)abs(imfo->valueOfVoltage - VOLTAGE_BASE))/VOLTAGE_BASE) > LEVEL1)
    {
        isNeedAlarm = true;
        imfo->level = 1;
        ims.level = imfo->level;
        alarm.alarmLevel = 1;
        alarm.handle = ims.handle;
        return isNeedAlarm;
    }
    else if((((float)abs(imfo->valueOfVoltage - VOLTAGE_BASE))/VOLTAGE_BASE) > LEVEL2)
    {
        isNeedAlarm = true;
        imfo->level = 2;
        ims.level = imfo->level;
        alarm.alarmLevel = 2;
        alarm.handle = ims.handle;
        return isNeedAlarm;
    }
    else if(((float)abs(imfo->valueOfVoltage - VOLTAGE_BASE)/VOLTAGE_BASE) > LEVEL3)
    {
        isNeedAlarm = true;
        imfo->level = 3;
        ims.level = imfo->level;
        alarm.alarmLevel = 3;
        alarm.handle = ims.handle;
        return isNeedAlarm;
    }
    else
    {
        isNeedAlarm = false;
        ims.level = 0;
        return isNeedAlarm;
    }

    //judge whether the valueOfCurrent is a alarm
    if(((float)abs((imfo->valueOfCurrent - CURRENT_BASE)/CURRENT_BASE)>LEVEL1))
    {
        isNeedAlarm = true;
        imfo->level = 1;
        ims.level = imfo->level;
        alarm.alarmLevel = 1;
        alarm.handle = ims.handle;
        return isNeedAlarm;
    }
    else if(((float)abs((imfo->valueOfCurrent - CURRENT_BASE)/CURRENT_BASE)>LEVEL2))
    {
        isNeedAlarm = true;
        imfo->level = 2;
        ims.level = imfo->level;
        alarm.alarmLevel = 2;
        alarm.handle = ims.handle;
        return isNeedAlarm;
    }
    else if(((float)abs((imfo->valueOfCurrent - CURRENT_BASE)/CURRENT_BASE)>LEVEL3))
    {
        isNeedAlarm = true;
        imfo->level = 3;
        ims.level = imfo->level;
        alarm.alarmLevel = 3;
        alarm.handle = ims.handle;
        return isNeedAlarm;
    }
    else
    {
        isNeedAlarm = false;
        ims.level = 0;
        return isNeedAlarm;
    }
}

void PowerProcess::pollAlarm(alarm_t* alarm)
{
    emit sendAlarm(alarm);
}

void PowerProcess::pollPresentData(infomanage_t* ims)
{
    if(HandleOfRealtime == ims->handle)
    {
        emit sendRealtimeData(ims);
    }
    else
    {
        qDebug("[PowerProcess] pollPresentData can't find : ims.handle :%d ",ims->handle);
    }
}


void PowerProcess::getPresentInfo(int handle)
{
    HandleOfRealtime = handle;
    isNeedPressent = true;
    qDebug("[PowerProcess] getPresentInfo success,isNeedPressent : %d",isNeedPressent);
}

void PowerProcess::closeGetPresentInfo()
{
    isNeedPressent = false;
}

void PowerProcess::onSendPresentDataService(int handle)
{
    infomanage_t info;
    //here is the handle received from the UI ,we should complete the code by wanted
    if(handle == ims.handle){
        qDebug("[PowerProcess] getPresentInfo success,show present info");
    }else{
        info.handle = ims.handle;
        qDebug("[PowerProcess] PresentInfo info.handle : %d ",info.handle);
    }
}

