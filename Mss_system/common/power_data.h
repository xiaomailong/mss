#ifndef POWERBASE_H
#define POWERBASE_H
#define SNS_MAX_NAME_SIZE 40

#include "unifw.h"
#include "b2v.h"
#include <QDateTime>
#include <QString>
#define POWER_HEARTBEAT_MSG_TYPE     (0x01)
#define POWER_HEADER_LEN 8

typedef enum {
    ON_MODE,                        /* the device is on */
    OFF_MODE,                       /* the device is off */
    ACTIVATE_MODE,                  /* the device is activate */
    STANDBY_MODE,                   /* the device is standby */
    NORMAL_MODE,                    /* the device is normal */
    ABNORMAL_MODE,                  /* the device is abnormal */
    UNKNOW_MODE,                    /* the device is error */
} device_state;

struct device_info_t
{
    char panelName[SNS_MAX_NAME_SIZE];
    int handle;                 //设备编号
    int state;                  //设备状态
    int deviceFlag;            //设备类型

    QString supplier ;          //供应商、
    QDateTime  startDate;       //投入使用时间、
    QDateTime  endDate;         //推荐使用年限、
    QString  location;          //设备所处区域
    QString ownNetwork;        //设备所属网络（如果有冗余需求，需标注A还是B）、
};

struct alarm_t
{
    int handle;                         //设备编号
    QDateTime alarmStartDate;         //报警开始时间
    QDateTime alarmEndDate;          //报警结束时间
    int alarmLevel;                    //报警级别
    QString place;                      //报警位置
    QString alarmDetailInfo;          //详细信息
    int reviewed;                       //该报警是否被查阅过，yes为1，否则为0

};

struct electric_devices_t
{
    /* reserved */
    int32_t reserved0;

    /* type.
    * 电压type 为0
    * 电流type 为1
    */
    int   type;

    /* statue.
    * 交流statue 为1
    * 直流statue 为0
    */
    int   statue;

    /* averageOfValue.
    *  平均值
    */
    float averageOfValue;

    int32_t  dateOfVoltage;
    int32_t  dateOfCuurent;
    /* the frequency of ac*/
    float frequency;
    /* the phase of data*/
    float phase;

    //获取平均值
    float getAverage();
    //获取当前值
    float getValue();
};

struct infomanage_t
{
    int handle;                 //设备编号

    int level;                  //报警级别

    float valueOfVoltage;           //the data of voltage

    float valueOfCurrent;           //the data of current

    /* the frequency of ac*/
    float frequencyOfAC;
    /* the phase of data*/
    float phaseOfAC;

    int owner;

    int type;
} ;

typedef struct {
quint8 handle;   //handle
quint8 voltage;      //电压
quint8 current;        //电流值
quint8 owner;       //属于哪个子系统
quint8 type;     //直流或者交流
quint8 angle;         //相位角
quint8 hz;    //频率
quint8 resevied2;   //保留2
}power_data_header_t;

typedef struct {
    quint16     msg_len;
    quint16     msg_type;
}power_app_header_t;

//heart beat data
typedef struct
{
    //quint16     msg_type;//0x0201
    quint8      year;
    quint8      month;
    quint8      date;
    quint8      hour;
    quint8      minute;
    quint8      second;
}power_heartbeat_t;

typedef enum psptable{
    PSP_INFORMATION,
    PSP_ALARM,
}PspTb;


DCLR_TAB(power_data_header_cv, var_item_t);
DCLR_TAB(power_app_header_cv, var_item_t);
DCLR_TAB(power_heartbeat_cv, var_item_t);

#endif // POWERBASE_H
