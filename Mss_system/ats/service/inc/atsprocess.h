#ifndef ATSPROCESS_H
#define ATSPROCESS_H

#include <QObject>
#include <QtSql>
#include "ats_data.h"
#include "vobc_data.h"
class AtsProcess : public QObject
{
    Q_OBJECT
public:
    explicit AtsProcess(QObject *parent = 0);
    ~AtsProcess();
    enum AtsProcessError
    {
        DataBaseOpenError         = 1,
        TableCreateError,
        EntryInsertError,
        DataInvalidError
    };
private:
    bool openDataBase();
    void closeDataBase();
    bool createTable(const QString& queryStr);
    bool isDataBaseReady();
    void printDataBaseError();
    static bool isBufValid(quint8* buf, quint16 len);
    bool insertAtsZcHeartBeatEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_zc_heartbeat_t& atsZcHeartBeat,
                                                   const quint8* buf, quint16 len);
    bool insertAtsCiHeartBeatEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_ci_heartbeat_t& atsCiHeartBeat,
                                                   const quint8* buf, quint16 len);
    bool insertAtsVobcHeartBeatEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_vobc_heartbeat_t& atsVobcHeartBeat,
                                                   const quint8* buf, quint16 len);
    bool insertAtsZcTsrValidateEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_zc_tsr_validate_t& atsZcTsrValidateHeader,
                                                   const ats_zc_tsr_logic_track_data_t& atsZcTsrLogicTrackData,
                                                   const quint8* buf, quint16 len);
    bool insertAtsZcTsrExecCmdEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_zc_tsr_exec_cmd_t& atsZcTsrExecCmdHeader,
                                                   const ats_zc_tsr_logic_track_data_t& atsZcTsrLogicTrackData,
                                                   const quint8* buf, quint16 len);
    bool insertAtsZcTsrOnConfirmEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_zc_tsr_on_confirm_t& atsZcTsrOnConfirm,
                                                   const quint8* buf, quint16 len);
    bool insertAtsCiCmdEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_ci_cmd_t& atsCiCmdHeader,
                                                   const ats_ci_cmd_data_t& atsCiCmdData,
                                                   const quint8* buf, quint16 len);
    bool insertAtsCiStatusEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_ci_status_t& atsCiStatus,
                                                   const quint8* buf, quint16 len);
    bool insertAtsVobcAtoCmdEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_vobc_ato_cmd_t& atsVobcAtoCmd,
                                                   const quint8* buf, quint16 len);
    bool insertAtsMssAlarmEntry(const ats_common_header_t& atsCommonHeader,
                                                   const ats_app_header_t& atsAppHeader,
                                                   const ats_mss_alarm_t& atsMssAlarm,
                                                   const quint8* buf, quint16 len);

private:
    QSqlDatabase *dataBaseHandler;
    QSqlQuery *queryHandler;
    QString connectName;
public slots:
    void start();
    void stop();
    void onReceiveData(quint8* buf, quint16 len);
    void onDeviceDataReceived(quint8* buf, quint16 len);
signals:
    void dataReceived();
    void deviceDataReceived(ats_mss_alarm_t* alarmInfo);
    void deviceDataReceived1(vobc_subsys_msg_t alarmInfo);
    void vobcDeviceDataReceived(quint8* buf, quint16 len);
    void error(int code);
    void started();
};

#endif // ATSPROCESS_H
