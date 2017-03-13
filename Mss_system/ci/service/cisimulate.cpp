#include "cisimulate.h"
#include "ci_data.h"
#include "mssdatadefine.h"
#include "b2v.h"
#include <QDebug>
CiSimulate::CiSimulate(QObject *parent) : QObject(parent)
{
    if(CI_DEBUG) qDebug()<<"CiSimulate: run thread id: "<<QThread::currentThreadId();

}
void CiSimulate::start()
{
    if(CI_DEBUG)
    {
        qDebug()<<"CiSimulate: start: "<<QThread::currentThreadId();
    }
    ciUdpService = new QUdpSocket(this);
    ciUdpTimer = new QTimer(this);
    connect(ciUdpTimer, &QTimer::timeout, this, &CiSimulate::sendCiUdpData);
    ciUdpTimer->start(1000);

    ciRouteTimer = new QTimer(this);
    connect(ciRouteTimer, &QTimer::timeout, this,  &CiSimulate::sendCiRouteData);
    ciRouteTimer->start(1000);
}
quint8* bufUdp;
quint8* bufRoute;
void CiSimulate::sendCiUdpData()
{
    if(CI_DEBUG)
    {
        qDebug()<<"sendciudpdata threadid="<<QThread::currentThreadId();
    }
    quint16 dataoffset = 0;
    bufUdp = new quint8[MAX_UDP_SIZE];
    ci_ci_t ciUdpData;
    ciUdpData.moduleid_code = ID_MESSAGE_CI;
    ciUdpData.device_type = rand()%5;
    ciUdpData.device_code = rand()%16;//0=signal lamp 1=branch road
    ciUdpData.device_state = rand()%2;
    ciUdpData.device_place = rand()%2;
    ciUdpData.alarm_type = rand()%3;
    ciUdpData.alarm_subtype = 0;
    ciUdpData.alarm_level = rand()%4;
    ciUdpData.detailinfo = 1;
    dataoffset = b2v_var_to_bytes((quint8 *)&ciUdpData, bufUdp, ci_ci_convert_table,ci_ci_convert_table_len);
    ciUdpService->writeDatagram(QByteArray::fromRawData((char *)bufUdp,dataoffset), QHostAddress(CI_ADRESS), CI_PORT);
}
void CiSimulate::sendCiRouteData()
{
    if(CI_DEBUG)
    {
        qDebug()<<"sendCiRoutedata threadid="<<QThread::currentThreadId();
    }
    quint16 headeroffset = 0;
    quint16 dataoffset = 0;
    int type = rand()%9;
    if(CI_DEBUG)
    {
        qDebug("CiSimulate run start type %d", type);
    }
    bufRoute = new quint8[MAX_ROUTE_SIZE];
    if(0==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci vobc data ");
        }
        ci_vobc_data_t ciVobc;
        ciVobc.ci_vobc_interface = CI_VOBC_INTERFACE;
        ciVobc.send_id_msg = ID_MESSAGE_CI;
        ciVobc.incept_id_msg=1;
        ciVobc.edition_control_msg=1;
        ciVobc.edition_check_msg=1;
        ciVobc.msg_list=1;
        ciVobc.com_cycle=50;
        ciVobc.opposite_msg_list=1;
        ciVobc.smsg_self_list=1;
        ciVobc.pro_edition=1;
        ciVobc.nc_data=1;
        ciVobc.dir_train=rand()%2;
        ciVobc.n_psd=rand()%2;
        ciVobc.nid_psd_1=rand()%2;
        ciVobc.nc_psd_1=rand()%2;
        ciVobc.r_nc_psd_1=rand()%2;
        ciVobc.nid_psd_2=rand()%2;
        ciVobc.q_psd_2=rand()%2;
        ciVobc.r_nc_psd_2=rand()%2;
        ciVobc.q_signal_aspect=0xEE;
        dataoffset = b2v_var_to_bytes((quint8 *)&ciVobc, bufRoute, ci_vobc_convert_table,ci_vobc_convert_table_len);
        if(CI_DEBUG)
        {
            qDebug()<<"CiSimulate CI VOBC dataoffset="<<dataoffset;
        }
        emit sendCiRoute(bufRoute,dataoffset);

    } else if(1==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci ats alarm data ");
        }
        ci_ats_data_h ciatsh;
        ci_ats_data_alarm ciatsalarm;
        ciatsh.ci_ats_interface = CI_ATS_INTERFACE;
        ciatsh.send_id_msg = ID_MESSAGE_CI;
        ciatsh.incept_id_msg=1;
        ciatsh.edition_control_msg=rand()%2;
        ciatsh.edition_check_msg=1;
        ciatsh.msg_list=1;
        ciatsh.com_cycle=50;
        ciatsh.opposite_msg_list=1;
        ciatsh.smsg_self_list=1;
        ciatsh.pro_edition=rand()%2;
        ciatsh.package_data_size=0x08;
        ciatsh.package_data_type=CI_ATS_ALARM;//package type
        //ciatsh.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&ciatsh, bufRoute, ci_ats_h_convert_table,ci_ats_h_convert_table_len);
        ciatsalarm.filament_burnout=0x1;
        ciatsalarm.filament_fuse=0x1;
        ciatsalarm.power_panel=0x1;
        ciatsalarm.signal_fault_shutdown=0x1;
        ciatsalarm.ci_device_alarm=0x1;
        ciatsalarm.railway_alarm=0x1;
        ciatsalarm.ups_fault=0x1;
        ciatsalarm.leu_communication_state=0x1;
        ciatsalarm.ci_zc_state=0x1;
        ciatsalarm.ci1_state=0x1;
        ciatsalarm.ci2_state=0x1;
        ciatsalarm.power1_state=0x1;
        ciatsalarm.power2_state=0x1;
        ciatsalarm.ci_count=0x1;
        ciatsalarm.ci_communication_state=0x1;
        ciatsalarm.unmanned_reentry=0x1;
        ciatsalarm.turnout_turnout=0x1;
        ciatsalarm.check_num=0x1;
        ciatsalarm.check_condition=0x1;
        ciatsalarm.psd_count=0x1;
        ciatsalarm.psd_x_state=rand()%2;
        ciatsalarm.station_mode=0x1;
        ciatsalarm.station_block=0x1;
        ciatsalarm.electrolytic_lock=0x1;
        ciatsalarm.autonomy_request=0x1;
        dataoffset = b2v_var_to_bytes((quint8 *)&ciatsalarm, bufRoute + headeroffset, ci_ats_data_alarm_covert_table,ci_ats_data_alarm_covert_table_len);
        if(CI_DEBUG)
        {
            qDebug()<<"CiSimulate CI ATS ALARM dataoffset="<<headeroffset+dataoffset;
        }
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }else if(2==type)
    {
        //ci zc
        if(CI_DEBUG)
        {
            qDebug("send ci zc route data ");
        }
        ci_zc_data_h cizcdataheader;
        ci_zc_route cizcroute;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = ID_MESSAGE_CI;
        cizcdataheader.incept_id_msg=1;
        cizcdataheader.edition_control_msg=rand()%2;
        cizcdataheader.edition_check_msg=1;
        cizcdataheader.msg_list=1;
        cizcdataheader.com_cycle=50;
        cizcdataheader.opposite_msg_list=1;
        cizcdataheader.smsg_self_list=1;
        cizcdataheader.pro_edition=rand()%2;
        cizcdataheader.package_data_size=0x09;
        cizcdataheader.package_data_type=CI_ZC_MOVE;//package type
        cizcdataheader.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, bufRoute, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcroute.route_size = 0x03;
        cizcroute.route_num = 8;
        cizcroute.route_state = rand()%2;
        cizcroute.signallight_state = 0x03;
        cizcroute.switch_state = 0x03;
        cizcroute.sectionlock_state1 = 0x03;
        cizcroute.sectionlock_state2 = 0x03;
        cizcroute.sectionlock_state3 = 0x03;
        cizcroute.sectionlock_state4 = 0x03;
        cizcroute.sectionlock_state5 = 0x03;
        cizcroute.proctectlock_info = 0x03;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcroute, bufRoute + headeroffset, ci_zc_route_convert_table,ci_zc_route_convert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    } else if(3==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci zc psd data ");
        }
        ci_zc_data_h cizcdataheader;
        ci_zc_psdinfo cizcpsdinfo;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = ID_MESSAGE_CI;
        cizcdataheader.incept_id_msg=1;
        cizcdataheader.edition_control_msg=rand()%2;
        cizcdataheader.edition_check_msg=1;
        cizcdataheader.msg_list=1;
        cizcdataheader.com_cycle=50;
        cizcdataheader.opposite_msg_list=1;
        cizcdataheader.smsg_self_list=1;
        cizcdataheader.pro_edition=rand()%2;
        cizcdataheader.package_data_size=0x08;
        cizcdataheader.package_data_type=CI_ZC_PSD;//package type
        cizcdataheader.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, bufRoute, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcpsdinfo.psd_size = 0x05;
        cizcpsdinfo.psd_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcpsdinfo, bufRoute + headeroffset, ci_zc_psdinfo_convert_table,ci_zc_psdinfo_convert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }else if(4==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci zc esb data ");
        }
        ci_zc_data_h cizcdataheader;
        ci_zc_esbbutton cizcesb;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = ID_MESSAGE_CI;
        cizcdataheader.incept_id_msg=1;
        cizcdataheader.edition_control_msg=rand()%2;
        cizcdataheader.edition_check_msg=1;
        cizcdataheader.msg_list=1;
        cizcdataheader.com_cycle=50;
        cizcdataheader.opposite_msg_list=1;
        cizcdataheader.smsg_self_list=1;
        cizcdataheader.pro_edition=rand()%2;
        cizcdataheader.package_data_size=0x08;
        cizcdataheader.package_data_type=CI_ZC_ESB;//package type
        cizcdataheader.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, bufRoute, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcesb.esb_emergency_size = 0x05;
        cizcesb.esb_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcesb, bufRoute + headeroffset, ci_zc_esbbutton_convert_table,ci_zc_esbbutton_convert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }else if(5==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci zc return data ");
        }
        ci_zc_data_h cizcdataheader;
        ci_zc_returnbutton cizcreturn;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = ID_MESSAGE_CI;
        cizcdataheader.incept_id_msg=1;
        cizcdataheader.edition_control_msg=rand()%2;
        cizcdataheader.edition_check_msg=1;
        cizcdataheader.msg_list=1;
        cizcdataheader.com_cycle=50;
        cizcdataheader.opposite_msg_list=1;
        cizcdataheader.smsg_self_list=1;
        cizcdataheader.pro_edition=rand()%2;
        cizcdataheader.package_data_size=0x08;
        cizcdataheader.package_data_type=CI_ZC_RETURN;//package type
        cizcdataheader.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, bufRoute, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcreturn.returnbutton_size = 0x05;
        cizcreturn.returnbutton_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcreturn, bufRoute + headeroffset, ci_zc_returnbutton_convert_table,ci_zc_returnbutton_convert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }else if(6==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci zc section data ");
        }
        ci_zc_data_h cizcdataheader;
        ci_zc_sectionused cizcsection;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = ID_MESSAGE_CI;
        cizcdataheader.incept_id_msg=1;
        cizcdataheader.edition_control_msg=rand()%2;
        cizcdataheader.edition_check_msg=1;
        cizcdataheader.msg_list=1;
        cizcdataheader.com_cycle=50;
        cizcdataheader.opposite_msg_list=1;
        cizcdataheader.smsg_self_list=1;
        cizcdataheader.pro_edition=rand()%2;
        cizcdataheader.package_data_size=0x08;
        cizcdataheader.package_data_type=CI_ZC_SECTION;//package type
        cizcdataheader.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, bufRoute, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcsection.zc_size = 0x05;
        cizcsection.zc_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcsection, bufRoute + headeroffset, ci_zc_sectionused_convert_table,ci_zc_sectionused_convert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }else if(7==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci zc requ data ");
        }
        ci_zc_data_h cizcdataheader;
        ci_zc_approachunlock cizcreq;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = ID_MESSAGE_CI;
        cizcdataheader.incept_id_msg=1;
        cizcdataheader.edition_control_msg=rand()%2;
        cizcdataheader.edition_check_msg=1;
        cizcdataheader.msg_list=1;
        cizcdataheader.com_cycle=50;
        cizcdataheader.opposite_msg_list=1;
        cizcdataheader.smsg_self_list=1;
        cizcdataheader.pro_edition=rand()%2;
        cizcdataheader.package_data_size=0x08;
        cizcdataheader.package_data_type=CI_ZC_REQU;//package type
        cizcdataheader.a_msg_num=0x1;
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, bufRoute, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcreq.unlock_size = 0x05;
        cizcreq.unlock_num = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcreq, bufRoute + headeroffset, ci_zc_approachunlock_convert_table,ci_zc_approachunlock_convert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }else if(8==type)
    {
        if(CI_DEBUG)
        {
            qDebug("send ci ats station data ");
        }
        ci_ats_data_h ciatsh;
        ci_ats_data_stationyard ciatsyard;
        ciatsh.ci_ats_interface = CI_ATS_INTERFACE;
        ciatsh.send_id_msg = ID_MESSAGE_CI;
        ciatsh.incept_id_msg=1;
        ciatsh.edition_control_msg=rand()%2;
        ciatsh.edition_check_msg=1;
        ciatsh.msg_list=1;
        ciatsh.com_cycle=50;
        ciatsh.opposite_msg_list=1;
        ciatsh.smsg_self_list=1;
        ciatsh.pro_edition=rand()%2;
        ciatsh.package_data_size=0x08;
        ciatsh.package_data_type=CI_ATS_STATIONYARD;//package type
        //ciatsh.a_msg_num=8;//package type
        headeroffset = b2v_var_to_bytes((quint8 *)&ciatsh, bufRoute, ci_ats_h_convert_table,ci_ats_h_convert_table_len);
        //ciatsyard.deviceinfo_len=0x1;
        //uint8_t a[50] = {0x00, 0x01, 0x02};
        ciatsyard.c_signal[0] = 0x11;
        ciatsyard.c_switch[0]= 0x11;
        ciatsyard.c_phy_track[0]= 2;
        ciatsyard.c_logic_track[0]= 3;
        ciatsyard.c_route_info[0]= 4;
        ciatsyard.c_auto_route[0]= 5;
        ciatsyard.c_shield_door[0]= 6;
        ciatsyard.c_esp_button[0]= 7;
        ciatsyard.c_remain_car[0]= 8;
        ciatsyard.c_half_autoback[0]= 9;
        ciatsyard.c_autoback[0]= 10;
        ciatsyard.c_spks[0]= 11;
        ciatsyard.c_auto_trigger[0]= 0x11;
        dataoffset = b2v_var_to_bytes((quint8 *)&ciatsyard, bufRoute + headeroffset, ci_ats_data_stationyard_covert_table,ci_ats_data_stationyard_covert_table_len);
        emit sendCiRoute(bufRoute,headeroffset+dataoffset);
    }
}
CiSimulate::~CiSimulate()
{
    if(CI_DEBUG)
    {
        qDebug()<<"CiSimulate:~CiSimulate";
    }
    delete[] bufUdp;
    delete[] bufRoute;
}
