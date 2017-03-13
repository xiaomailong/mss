#ifndef ZCDATATHREAD_H
#define ZCDATATHREAD_H

#include <QObject>
#include <QtSql>
#include <QThread>
#include "zcdata.h"
#include "zc_protocol_pub.h"
#include "zc/zcsimulatedatathread.h"
#include "vobc_data.h"

#include <QDebug>
#include <QUdpSocket>

class ZcDataThread : public QObject
{
    Q_OBJECT
public:
    explicit ZcDataThread(QString connectionName, QObject *parent = 0);
    ~ZcDataThread();
    enum AtsProcessError
    {
        DBOpenError         = 1,
        TBCreateError,
        InsertError,
        HeaderError,
        DataInvalid,
        DealDataError
    };

signals:
    void sendUiZcCiLs();
    void sendUiZcCiSp();
    void sendUiZcCiPslr();

    void sendUiZcAtsTvc();
    void sendUiZcAtsTec();
    void sendUiZcAtsTs();

    void sendUiZcVobcTc();
    void sendUiZcVobcArlr();
    void sendUiZcVobcAlr();
    void sendUiZcVobcScm();

    void sendUiZcAlarm(vobc_subsys_msg_t alarm);
    void receiveDataOk();
    void receiveAlarmDataOk();
    void error(int code);
public slots:
    void start();
    void receiveData(quint8 * buf, quint16 len);
    void receiveAlarmData();
public:
    bool openDB();
    bool createTB(QString QueryStr);
    void closeDB();

    bool insertData(stream_head_info_t *header, ci_header_info_t *ci_header, QByteArray l_status, quint8 *rawdata,  quint16 len);
    bool insertData_S(stream_head_info_t *header, ci_header_info_t *ci_header, QByteArray s_status, quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, ci_header_info_t *ci_header, protect_zone_lock_rsq_t *datagram,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, ats_header_info_t *ats_header, zc_tsr_exeute_frame_1_t *datagram1, zc_tsr_exeute_frame_2_t *datagram2,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, ats_header_info_t *ats_header, zc_status_frame_1_t *datagram1, zc_status_frame_2_t *datagram2,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, ats_header_info_t *ats_header, zc_tsr_verify_frame_1_t *datagram1, zc_tsr_verify_frame_2_t *datagram2,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, onboard_control_info *datagram,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, onboard_request_respond_t *datagram,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, onboard_unregister_rsq_t *datagram,  quint8 *rawdata,  quint16 len);
    bool insertData(stream_head_info_t *header, vobc_header_info_t *vobc_header, special_control_cmd_t *datagram,  quint8 *rawdata,  quint16 len);
    bool insertData(vobc_subsys_msg_t *monitor,  quint8 *rawdata,  quint16 len);

    bool dealZcCi(quint8 *buf, quint16 len, stream_head_info_t *header);
    bool dealZcAts(quint8 *buf, quint16 len, stream_head_info_t *header);
    bool dealZcVobc(quint8 *buf, quint16 len, stream_head_info_t *header);

    void sendSignalUiZcCiLs();
    void sendSignalUiZcCiSp();
    void sendSignalUiZcCiPslr();

    void sendSignalUiZcAtsTvc();
    void sendSignalUiZcAtsTec();
    void sendSignalUiZcAtsTs();

    void sendSignalUiZcVobcTc();
    void sendSignalUiZcVobcArlr();
    void sendSignalUiZcVobcAlr();
    void sendSignalUiZcVobcScm();

    void sendSignalUiZcAlarm(vobc_subsys_msg_t alarm);
    void sendReceiveDataOk();
    void sendReceiveAlarmDataOk();
    void sendError(int code);
    QSqlDatabase zcDb;
    QSqlQuery zcQuery;
    QString zcConnectname;
    QStringList zcTable;
    QStringList zcTableElement;
    QUdpSocket *zcUdpSocket;
};

#endif // ZCDATATHREAD_H
