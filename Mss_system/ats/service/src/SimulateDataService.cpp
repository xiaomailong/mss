#include "SimulateDataService.h"
#include <QThread>
#include "ats_data.h"
#include "mssdatadefine.h"
#include "b2v.h"
#include <QDate>
#include <QTime>
#define BUF_SIZE 256
#define ATS_PROCESS_MIN_ROWDATA_LEN (0x1d + 0x2 + 0x2)
#define ATS_SIMULATE_DEBUG_ENABLED 0
#if ATS_SIMULATE_DEBUG_ENABLED
#define ATS_SIMULATE_LOG_ENTRY() qDebug("Entry")
#else
#define ATS_SIMULATE_LOG_ENTRY()
#endif

SimulateDataService::SimulateDataService(QObject *parent) : QObject(parent)
{
    ATS_SIMULATE_LOG_ENTRY();
    m_timer_ats_ci = NULL;
    m_timer_ats_zc = NULL;
    m_timer_ats_vobc = NULL;
    m_receiver = NULL;
}

SimulateDataService::~SimulateDataService()
{
    ATS_SIMULATE_LOG_ENTRY();
}

void SimulateDataService::start()
{
    ATS_SIMULATE_LOG_ENTRY();
    m_ats_vobc_msg_list = rand() % 0xFFFF;
    m_ats_ci_msg_list = rand() % 0xFFFF;
    m_ats_zc_msg_list = rand() % 0xFFFF;
    m_ats_mss_msg_list = rand() % 0xFFFF;
    m_timer_ats_ci = new QTimer();
    m_timer_ats_zc = new QTimer();
    m_timer_ats_vobc = new QTimer();
    m_timer_ats_ci->setSingleShot(false);
    m_timer_ats_zc->setSingleShot(false);
    m_timer_ats_vobc->setSingleShot(false);
    connect(m_timer_ats_ci, &QTimer::timeout, this, &SimulateDataService::onTimeout, Qt::AutoConnection);
    connect(m_timer_ats_zc, &QTimer::timeout, this, &SimulateDataService::onTimeout, Qt::AutoConnection);
    connect(m_timer_ats_vobc, &QTimer::timeout, this, &SimulateDataService::onTimeout, Qt::AutoConnection);
    //m_timer_ats_zc->start(250);
    //m_timer_ats_ci->start(400);
    //m_timer_ats_vobc->start(250);
    m_receiver = new QUdpSocket();
    connect(m_receiver, &QUdpSocket::readyRead, this, &SimulateDataService::onReadyRead,Qt::AutoConnection);
    m_receiver->bind(12345, QUdpSocket::ShareAddress);
}

void SimulateDataService::stop()
{
    ATS_SIMULATE_LOG_ENTRY();
    if(m_receiver){
        m_receiver->close();
        delete m_receiver;
        m_receiver = NULL;
    }
    if(m_timer_ats_ci){
        m_timer_ats_ci->stop();
        delete m_timer_ats_ci;
        m_timer_ats_ci = NULL;
    }
    if(m_timer_ats_zc){
        m_timer_ats_zc->stop();
        delete m_timer_ats_zc;
        m_timer_ats_zc = NULL;
    }
    if(m_timer_ats_vobc){
        m_timer_ats_vobc->stop();
        delete m_timer_ats_vobc;
        m_timer_ats_vobc = NULL;
    }
}

void SimulateDataService::onTimeout()
{
    ATS_SIMULATE_LOG_ENTRY();
    QTimer* time_sender = qobject_cast<QTimer *>(sender());
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    quint8 * buf;
    quint16 pad_len = 0;
    quint16 check_len = 0;
    quint16 app_header_offset = 0;
    if(time_sender == m_timer_ats_ci){
        buf = new quint8[BUF_SIZE];
        ats_common_header_t ats_header;
        ats_app_header_t ats_app_header;
        ats_ci_heartbeat_t heartbeat;
        ats_header.interface_type = ATS_CI_INTERFACE;
        ats_header.send_id_msg = ID_MESSAGE_ATS;
        ats_header.incept_id_msg = ID_MESSAGE_CI;
        ats_header.edition_control_msg = 0xFF;
        ats_header.edition_check_msg = 0xFFFFFFFF;
        ats_header.msg_list = m_ats_ci_msg_list;
        m_ats_ci_msg_list++;
        ats_header.com_cycle = 8;
        ats_header.pro_edition = 3;
        check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        pad_len += check_len;
        app_header_offset = pad_len;
        ats_app_header.msg_type = ATS_CI_HEARTBEAT_MSG_TYPE;
        ats_app_header.msg_len = 0;
        check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
        pad_len += check_len;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, ats_ci_heartbeat_cv_table, ats_ci_heartbeat_cv_table_len);
        pad_len += check_len;
        ats_app_header.msg_len = 2 + check_len;
        check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        emit msgPacked(buf, pad_len);

    } else if (time_sender == m_timer_ats_zc){
        buf = new quint8[BUF_SIZE];
        ats_common_header_t ats_header;
        ats_app_header_t ats_app_header;
        ats_zc_heartbeat_t heartbeat;
        ats_header.interface_type = ATS_ZC_INTERFACE;
        ats_header.send_id_msg = ID_MESSAGE_ATS;
        ats_header.incept_id_msg = ID_MESSAGE_ZC;
        ats_header.edition_control_msg = 0xFF;
        ats_header.edition_check_msg = 0xFFFFFFFF;
        ats_header.msg_list = m_ats_zc_msg_list;
        m_ats_zc_msg_list++;
        ats_header.com_cycle = 5;
        ats_header.pro_edition = 3;
        check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        pad_len += check_len;
        app_header_offset = pad_len;
        ats_app_header.msg_type = ATS_ZC_HEARTBEAT_MSG_TYPE;
        ats_app_header.msg_len = 0;
        check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
        pad_len += check_len;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, ats_zc_heartbeat_cv_table, ats_zc_heartbeat_cv_table_len);
        pad_len += check_len;
        ats_app_header.msg_len = 2 + check_len;
        check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        emit msgPacked(buf, pad_len);
    } else if (time_sender == m_timer_ats_vobc){
        buf = new quint8[BUF_SIZE];
        ats_common_header_t ats_header;
        ats_app_header_t ats_app_header;
        ats_vobc_heartbeat_t heartbeat;
        ats_header.interface_type = ATS_VOBC_INTERFACE;
        ats_header.send_id_msg = ID_MESSAGE_ATS;
        ats_header.incept_id_msg = ID_MESSAGE_VOBC;
        ats_header.edition_control_msg = 0xFF;
        ats_header.edition_check_msg = 0xFFFFFFFF;
        ats_header.msg_list = m_ats_vobc_msg_list;
        m_ats_vobc_msg_list++;
        ats_header.com_cycle = 5;
        ats_header.pro_edition = 3;
        check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
        pad_len += check_len;
        app_header_offset = pad_len;
        ats_app_header.msg_type = ATS_VOBC_HEARTBEAT_MSG_TYPE;
        ats_app_header.msg_len = 0;
        check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
        pad_len += check_len;
        heartbeat.year = date.year() - 2000;
        heartbeat.month = date.month();
        heartbeat.date = date.day();
        heartbeat.hour = time.hour();
        heartbeat.minute = time.minute();
        heartbeat.second = time.second();
        check_len = b2v_var_to_bytes((quint8*)(&heartbeat), buf + pad_len, ats_vobc_heartbeat_cv_table, ats_vobc_heartbeat_cv_table_len);
        pad_len += check_len;
        ats_app_header.msg_len = 2 + check_len;
        check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
        emit msgPacked(buf, pad_len);

    } else {


    }
}

void SimulateDataService::onReadyRead()
{
    quint8 * buf;
    quint16 pad_len = 0;
    quint16 check_len = 0;
    quint16 app_header_offset = 0;
    ATS_SIMULATE_LOG_ENTRY();
    while (m_receiver->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_receiver->pendingDatagramSize());
        m_receiver->readDatagram(datagram.data(), datagram.size());
        if(datagram.contains("ats_vobc_ato_cmd")){
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_vobc_ato_cmd_t ats_vobc_ato_cmd;
            ats_header.interface_type = ATS_VOBC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_VOBC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_vobc_msg_list;
            m_ats_vobc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_VOBC_ATO_CMD_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_vobc_ato_cmd.service_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.line_id =  ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.next_zc_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.next_ci_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.next_ats_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.cargroupline_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.cargroup_id = (((quint16)(rand())) % 999 ) + 1;
            ats_vobc_ato_cmd.sourceline_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.trainnum_id = (((quint16)(rand())) % 9999 ) + 1;
            ats_vobc_ato_cmd.destination_track_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.destination_id = ((quint32)(rand())) % 0xFFFFFFFF;
            ats_vobc_ato_cmd.plan_traffic_direction = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.next_skip_stop_id = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.station_stop_time = ((quint16)(rand())) % 0xFFFF;
            ats_vobc_ato_cmd.next_skip_stop_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.nc_interval_operation = 0;
            ats_vobc_ato_cmd.detain_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.reentry_operation = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.back_indication = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_vobc_ato_cmd.gating_strategy = ((rand() % 2 ) == 0) ? 0x55 : 0xCC;
            ats_vobc_ato_cmd.reserved_field = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_vobc_ato_cmd), buf + pad_len, ats_vobc_ato_cmd_cv_table, ats_vobc_ato_cmd_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit msgPacked(buf, pad_len);
        } else if (datagram.contains("ats_ci_cmd_cv")) {
            quint16 temp_len = 0;
            int i = 0;
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_ci_cmd_t ats_ci_cmd;
            ats_ci_cmd_data_t ats_ci_cmd_data;
            ats_header.interface_type = ATS_CI_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_CI;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_ci_msg_list;
            m_ats_ci_msg_list++;
            ats_header.com_cycle = 8;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_CI_CMD_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_ci_cmd.cmd_cnt = (((quint8) (rand())) % 4) + 1;
            check_len = b2v_var_to_bytes((quint8*)(&ats_ci_cmd), buf + pad_len, ats_ci_cmd_cv_table, ats_ci_cmd_cv_table_len);
            pad_len += check_len;
            temp_len += check_len;
            for(i = 0; i < ats_ci_cmd.cmd_cnt; i++){
                ats_ci_cmd_data.cmd_type = (((quint8) (rand())) % 0x37) + 1;
                ats_ci_cmd_data.device_id = ((quint32)(rand())) % 0xFFFFFFFF;
                ats_ci_cmd_data.device_type = (((quint8) (rand())) % 0x11) + 1;
                ats_ci_cmd_data.reserved_field = 0xFF;
                check_len = b2v_var_to_bytes((quint8*)(&ats_ci_cmd_data), buf + pad_len, ats_ci_cmd_data_cv_table, ats_ci_cmd_data_cv_table_len);
                temp_len += check_len;
                pad_len += check_len;
            }
            ats_app_header.msg_len = 2 + temp_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit msgPacked(buf, pad_len);
        } else if (datagram.contains("ats_ci_status")) {
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_ci_status_t ats_ci_status;
            ats_header.interface_type = ATS_CI_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_CI;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_ci_msg_list;
            m_ats_ci_msg_list++;
            ats_header.com_cycle = 8;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_CI_RUNNING_STS_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_ci_status.main_standby_sts = ((rand() % 2 ) == 0) ? 0x55 : 0xAA;
            ats_ci_status.ato_req_rsp = ((rand() % 2 ) == 0) ? 0x55 : 0xCC;
            check_len = b2v_var_to_bytes((quint8*)(&ats_ci_status), buf + pad_len, ats_ci_status_cv_table, ats_ci_status_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit msgPacked(buf, pad_len);
        } else if (datagram.contains("ats_zc_tsr_validate")) {
            quint16 temp_len = 0;
            int i = 0;
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_tsr_validate_t ats_zc_tsr_validate;
            ats_zc_tsr_logic_track_data_t ats_zc_tsr_logic_track_data;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_TSR_VALIDATE_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_zc_tsr_validate.tmp_speed_limit = ((rand() % 2 ) == 0) ? 2 : 0xFF;
            ats_zc_tsr_validate.logic_track_cnt = (((quint8) (rand())) % 4) + 1;
            check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_validate), buf + pad_len, ats_zc_tsr_validate_cv_table, ats_zc_tsr_validate_cv_table_len);
            pad_len += check_len;
            temp_len += check_len;
            for(i = 0; i < ats_zc_tsr_validate.logic_track_cnt; i++){
                ats_zc_tsr_logic_track_data.logic_track_id = ((quint16)(rand())) % 0xFFFF;
                check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_logic_track_data), buf + pad_len, ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
                temp_len += check_len;
                pad_len += check_len;
            }
            ats_app_header.msg_len = 2 + temp_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit msgPacked(buf, pad_len);
        } else if (datagram.contains("ats_zc_tsr_exec_cmd")) {
            quint16 temp_len = 0;
            int i = 0;
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_tsr_exec_cmd_t ats_zc_tsr_exec_cmd;
            ats_zc_tsr_logic_track_data_t ats_zc_tsr_logic_track_data;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_TSR_EXEC_CMD_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_zc_tsr_exec_cmd.tmp_speed_limit = ((rand() % 2 ) == 0) ? 2 : 0xFF;
            ats_zc_tsr_exec_cmd.logic_track_cnt = (((quint8) (rand())) % 4) + 1;
            check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_exec_cmd), buf + pad_len, ats_zc_tsr_exec_cmd_cv_table, ats_zc_tsr_exec_cmd_cv_table_len);
            pad_len += check_len;
            temp_len += check_len;
            for(i = 0; i < ats_zc_tsr_exec_cmd.logic_track_cnt; i++){
                ats_zc_tsr_logic_track_data.logic_track_id = ((quint16)(rand())) % 0xFFFF;
                check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_logic_track_data), buf + pad_len, ats_zc_tsr_logic_track_data_cv_table, ats_zc_tsr_logic_track_data_cv_table_len);
                temp_len += check_len;
                pad_len += check_len;
            }
            ats_app_header.msg_len = 2 + temp_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit msgPacked(buf, pad_len);
        } else if (datagram.contains("ats_zc_tsr_on_confirm")) {
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_zc_tsr_on_confirm_t ats_zc_tsr_on_confirm;
            ats_header.interface_type = ATS_ZC_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_ZC;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_zc_msg_list;
            m_ats_zc_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_ZC_TSR_ON_CONFIRM_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_zc_tsr_on_confirm.zc_id = ((quint16)(rand())) % 0xFFFF;
            check_len = b2v_var_to_bytes((quint8*)(&ats_zc_tsr_on_confirm), buf + pad_len, ats_zc_tsr_on_confirm_cv_table, ats_zc_tsr_on_confirm_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit msgPacked(buf, pad_len);
        } else if (datagram.contains("ats_mss_alarm")) {
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_mss_alarm_t ats_mss_alarm;
            ats_header.interface_type = ATS_MSS_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_ATS;
            ats_header.incept_id_msg = ID_MESSAGE_MSS;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_mss_msg_list;
            m_ats_mss_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_MSS_ALARM_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
            ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.dev_id = ((quint16)(rand())) % 0x12;
            ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
            ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
            ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0x2;
            check_len = b2v_var_to_bytes((quint8*)(&ats_mss_alarm), buf + pad_len, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit deviceDataReceived(buf, pad_len);
        } else if (datagram.contains("vobc_mss_alarm")) {
            buf = new quint8[BUF_SIZE];
            ats_common_header_t ats_header;
            ats_app_header_t ats_app_header;
            ats_mss_alarm_t ats_mss_alarm;
            ats_header.interface_type = ATS_MSS_INTERFACE;
            ats_header.send_id_msg = ID_MESSAGE_VOBC;
            ats_header.incept_id_msg = ID_MESSAGE_MSS;
            ats_header.edition_control_msg = 0xFF;
            ats_header.edition_check_msg = 0xFFFFFFFF;
            ats_header.msg_list = m_ats_mss_msg_list;
            m_ats_mss_msg_list++;
            ats_header.com_cycle = 5;
            ats_header.pro_edition = 3;
            check_len = b2v_var_to_bytes((quint8*)(&ats_header), buf, ats_common_header_cv_table, ats_common_header_cv_table_len);
            pad_len += check_len;
            app_header_offset = pad_len;
            ats_app_header.msg_type = ATS_MSS_ALARM_MSG_TYPE;
            ats_app_header.msg_len = 0;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + pad_len, ats_app_header_cv_table, ats_app_header_cv_table_len);
            pad_len += check_len;
            ats_mss_alarm.sys_id = ID_MESSAGE_ATS;
            ats_mss_alarm.dev_type = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.dev_id = ((quint16)(rand())) % 0x12;
            ats_mss_alarm.dev_local = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_type = ((quint8)(rand())) % 0x02;
            ats_mss_alarm.alarm_subtype = ((quint8)(rand())) % 0x04;
            ats_mss_alarm.alarm_level = (((quint8)(rand())) % 0x03) + 1;
            ats_mss_alarm.alarm_code = ((quint16)(rand())) % 0x2;
            check_len = b2v_var_to_bytes((quint8*)(&ats_mss_alarm), buf + pad_len, ats_mss_alarm_cv_table, ats_mss_alarm_cv_table_len);
            pad_len += check_len;
            ats_app_header.msg_len = 2 + check_len;
            check_len = b2v_var_to_bytes((quint8*)(&ats_app_header), buf + app_header_offset, ats_app_header_cv_table, ats_app_header_cv_table_len);
            emit deviceDataReceived(buf, pad_len);
        } else {
            if(datagram.size() > ATS_PROCESS_MIN_ROWDATA_LEN){
                ats_common_header_t ats_common_header;
                buf = new quint8[BUF_SIZE];
                memcpy(buf, datagram.data(), datagram.size());
                pad_len = datagram.size();
                check_len = b2v_bytes_to_var(buf, (quint8 *)(&ats_common_header), ats_common_header_cv_table, ats_common_header_cv_table_len);
                if(ats_common_header.interface_type == ATS_MSS_INTERFACE){
                    emit deviceDataReceived(buf, pad_len);
                } else {
                    emit dataReceived(buf, pad_len);
                }
            }
        }

    }
}
