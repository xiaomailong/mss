#ifndef POWERPROCESS_H
#define POWERPROCESS_H
#include "power_data.h"
#include "mssdbconfig.h"

#include <QObject>
#include <QThread>
#include <QtSql>
#ifdef USE_UDP
#include <QUdpSocket>
#endif


#define LEVEL1 0.5
#define LEVEL2 0.3
#define LEVEL3 0.1
#define VOLTAGE_BASE 220
#define CURRENT_BASE 0.5

class PowerProcess : public QObject
{
    Q_OBJECT
public:
    explicit PowerProcess(QObject *parent = 0);

    enum AtsProcessError
    {
        DBOpenError         = 1,
        TBCreateError,
        InsertError,
        //HeaderError,
        DataInvalid,
        //DealDataError
    };
    QSqlDatabase db;
    infomanage_t ims;

public slots:
    void receiveData(quint8* buf, quint16 len);
    /**
     * @brief receiveData :a slot used to perform actions by connect with the signal of sendPowerSimulateData in msssystem.cpp
     *                     Once the sendPowerSimulateData send data ,receiveData start ,begain receive data,judge alarmLevel and save data to the database
     *
     * @param buf :the real data which sendPowerSimulateData send
     * @param len :the len of data
     * @return ims
      */

    void onSendPresentDataService(int handle);
    /**
     * @brief onSendPresentDataService :a slot used to perform actions by connect with signal of PowerRealTimeCurveWidget
     *                                  start send present data to PowerRealTimeCurveWidget
     *
     * @param handle :the device which should been send
     * @return ims
      */

    void getPresentInfo(int handle);
    /**
     * @brief setPresentInfo :a slot used to perform actions by connect with the signal of PowerRealTimeCurveWidget
     *                        Once the PowerRealTimeCurveWidget send the singal want to get this device real-time data ,we receive this singal
     *
     * @param handle :the handle of the needed device
     * @return isNeedPressent true
      */

    void closeGetPresentInfo();
    /**
     * @brief closeGetPresentInfo :a slot used to perform actions by connect with the signal of PowerRealTimeCurveWidget
     *                             Once the PowerRealTimeCurveWidget doesn't want to get the real-time data ,we receive this singal
     *
     * @param null
     * @return isNeedPressent false
      */
      
    void start();
    /**
     * @brief start :a slot used to perform actions by connect with the signal of msssystem
     *               init the base function of powerprocess ,first it should set the base info of powerSubSystem which will get from the suppliers of power
     *               second it connect the DB and create the table if the table doesn't exixts
      */

signals:

    void sendAlarm(alarm_t* alarm);
    /**
     * @brief send_alarm :a signal used to tell the alarm of UI ,this record of data is a alram
     *
     * @param alarm :the struct about alarm info
     * @return
      */

    void sendRealtimeData(infomanage_t* ims);
    /**
     * @brief sendRealtimeData :a signal used to send the real-time data of PowerRealTimeCurveWidget
     *
     * @param ims :the struct about the real-time data
     *
      */

    void started();

    void dataReceived();
    /**
     * @brief dataReceived :a signal used to tell the data has been received success
     *
     * @param
     * @return
      */

    void error(int code);

public:
    /*  database manipulation
     *  include: openDB,createTB,insertData,closeDB
     * */
    void openDB();
    /**
     * @brief openDB :open the DB
     *
      */

    bool createTBOfInfo(QString QueryStr);
    /**
     * @brief createTBOfInfo :create the table of info,
     *                        table of info used to save the real-time data from suppliers and also save the alarm info of this record
     *
     * @param QueryStr :the  database statements
      */

    bool createTBOfDevice(QString QueryStr);
    /**
     * @brief createTBOfDevice :create the table of device,
     *                          table of device used to save the info about device from suppliers
     * @param QueryStr :the  database statements
      */

    void closeDB();
    /**
     * @brief closeDB :close the DB
     *
      */

    bool insertData(PspTb tbname,void *rawdata);
    /**
     * @brief insertData :insert data into DB,
     *
     * @param tbname :the name of DB
     * @param rawdata :the rawdata
     * @return  true :success
     *          false: fail
      */

    //interface about alarm
    bool isAlarm(infomanage_t* infomanage);
    /**
     * @brief isAlarm :judge whether the valueOfVoltage and valueOfCurrent need alarm and calculate the alarmLevel
     *
     * @param infomanage :the data of the record
     * @return  isNeedAlarm = true :this record is a alarm
     *          isNeedAlarm = false:this record isn't a alarm
      */

    void pollAlarm(alarm_t* alarm);
    /**
     * @brief pollAlarm :poll alarm to UI,
     *                   send a signal of sendAlarm
     *
     * @param alarm :the struct about alarm info
      */

    infomanage_t analyInfo(power_data_header_t *data);
    /**
     * @brief analyInfo :analy the data from UDP and convert the data into the struct of infomanage_t,
     *
     * @param data :the raw data from simulate
     * @return ims :the data after convert
      */

private:
    QSqlQueryModel *model2;

    char panelName[SNS_MAX_NAME_SIZE];
    int handle;                 //设备编号
    int device_flag;            //设备类型
    device_state state;         //设备状态
    bool isNeedPressent;        //是否需要实时上报数据

    //base info of device
    device_info_t deviceInfo;

    //info of alarm
    alarm_t alarm;

    //receive the data from sender
    infomanage_t infomanage;

    //backup device
    device_info_t backupDeviceInfo;
protected:
    void initPowerInfo();
    /**
     * @brief initPowerInfo :init the info about power from the suppliers ,
     *                       it will not be complete until get the info from the supplier
      */

    void pollPresentData(infomanage_t* infomanage);
    /**
     * @brief pollPresentData :poll the real-time data to UI by handle,
     *
      */

#ifdef USE_UDP
public slots:
    void receiveDataByUDP();
    /**
     * @brief receiveDataByUDP :receive data from UDP,if we define USE_UDP,the function is similar to receiveData
     *
      */
private:
    QUdpSocket *udpSocketOfPowerReceive; 
#endif

};

#endif // POWERPROCESS_H
