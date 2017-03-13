#include <QString>
#include <QtTest>
#include <QDebug>
#include "ciservice.h"
#include <Qtsql>
#include <QByteArray>
#include "ci_data.h"
#include "mssdatadefine.h"
#include <QDebug>
#include <QDir>
Q_DECLARE_METATYPE(quint8*)
Q_DECLARE_METATYPE(ci_ci_t*)
#define TEST_BUF_LEN 500
#define TEST_HEADER_LEN 10
int const TEST_CI_VOBC = 8;
int const TEST_CI_CI = 9;
class CiProcessUnitTest : public QObject
{
    Q_OBJECT

public:
    CiProcessUnitTest();
    enum ModuleType
    {
        TestCiAtsAlarm,
        TestCiAtsStationyard,
        TestCiZcMove,
        TestCiZcPsd,
        TestCiZcEsb,
        TestCiZcReturn,
        TestCiZcSection,
        TestCiZcRequ
    };
    enum DataType
    {
        TestDataNull,
        TestDataLowModule,
        TestDataEqualModule,
        TestDataLowHeader,
        TestDataEqualHeader,
        TestDataHightHeaderLowLen,
        TestDataEqualLen,
        TestDataHightLen
    };
private:
    CiService* ciRoute;
    QByteArray readFile(QString filename);
    void createDataRoute(int moduletype, int datatype, quint8**,quint16*);
    void createDataCi(int moduletype,int datatype, quint8**,quint16*);
    quint8 deleteAlltable();
    QString titleModule[8] = {"CI_ATS_ALARM","CI_ATS_STATIONYARD","CI_ZC_MOVE","CI_ZC_PSD",
                               "CI_ZC_ESB", "CI_ZC_RETURN","CI_ZC_SECTION","CI_ZC_REQU"};
    QString titleType[8] = {"data is null", "buf len < len(module type header)","buf len = len(module type  header)","buf len < len(common header)",
                             "buf len = len(common header)","buf len < len(common header + app data)","buf len = len(common header + app data)","buf len > len(common header + app data)"};
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testStart();
    void testReceiveUdpData();
    void testReceiveUdpData_data();
    void testReceiveRouteData();
    void testReceiveRouteData_data();
};
Q_DECLARE_METATYPE(CiProcessUnitTest::DataType)
CiProcessUnitTest::CiProcessUnitTest()
{

}

void CiProcessUnitTest::initTestCase()
{
    ciRoute = new CiService();
}
void CiProcessUnitTest::cleanupTestCase()
{
    //deleteAlltable();
    if(ciRoute != NULL)
    {
        delete ciRoute;
        ciRoute = NULL;
    }
}
void CiProcessUnitTest::testStart()
{
    QSignalSpy spyStarted(ciRoute, &CiService::started);
    QSignalSpy spyError(ciRoute, &CiService::error);
    ciRoute->start();
    QCOMPARE(spyError.count()+spyStarted.count(),1);
    if(spyError.count()==1)
    {
        QList<QVariant> arguments=spyError.takeFirst();
        int err=arguments.at(0).toInt();
        QVERIFY(err==CiService::DbOpenError || err==CiService::TbCreateError);
    }
}
void CiProcessUnitTest::testReceiveRouteData()
{
    QFETCH(quint8*,data);
    QFETCH(quint16,len);
    QFETCH(int,datatype);
    if(datatype==TestDataEqualLen)
    {
        QSignalSpy errorSpy(ciRoute, &CiService::error);
        ciRoute->receiveRouteData(data,len);
        if(errorSpy.count()==1)
        {
            QList<QVariant> arguments = errorSpy.takeFirst();
            QVERIFY(arguments.at(0).toInt() == CiService::EntryInsertError);
        }else if(errorSpy.count()>1)
        {
            qDebug()<<"two errors= "<<errorSpy.takeAt(0).at(0).toInt()<<" ="<<errorSpy.takeAt(1).at(0).toInt();
            qDebug()<<"errorSpy.count()="<<errorSpy.count();
            QCOMPARE(errorSpy.count(),1);
        }
    }else
    {
        QSignalSpy errorspy(ciRoute, &CiService::error);
        ciRoute->receiveRouteData(data,len);
        QCOMPARE(errorspy.count(),1);
    }
}
void CiProcessUnitTest::testReceiveRouteData_data()
{
    quint8* buf = NULL;
    quint16 len = 0;
    QTest::addColumn<quint8*>("data");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<int>("datatype");

    QList<DataType> testTypes;
    testTypes.append(TestDataNull);
    testTypes.append(TestDataLowModule);
    testTypes.append(TestDataEqualModule);
    testTypes.append(TestDataLowHeader);
    testTypes.append(TestDataEqualHeader);
    testTypes.append(TestDataHightHeaderLowLen);
    testTypes.append(TestDataEqualLen);
    testTypes.append(TestDataHightLen);
    QList<ModuleType> testModules;
    //testModules.append(TEST_CI_VOBC);
    testModules.append(TestCiAtsAlarm);
    testModules.append(TestCiAtsStationyard);
    testModules.append(TestCiZcMove);
    testModules.append(TestCiZcPsd);
    testModules.append(TestCiZcEsb);
    testModules.append(TestCiZcReturn);
    testModules.append(TestCiZcSection);
    testModules.append(TestCiZcRequ);
    //testModules.append(TEST_CI_CI);

    //vobc
    createDataCi(TEST_CI_VOBC,(int)TestDataNull,&buf,&len);
    QTest::newRow("TEST_CI_VOBC:data is null")<<buf<<len<<(int)TestDataNull;

    createDataCi(TEST_CI_VOBC,(int)TestDataHightHeaderLowLen,&buf,&len);
    QTest::newRow("TEST_CI_VOBC:buf len < len(real data)")<<buf<<len<<(int)TestDataHightHeaderLowLen;

    createDataCi(TEST_CI_VOBC,(int)TestDataEqualLen,&buf,&len);
    QTest::newRow("TEST_CI_VOBC:buf len = len(real data)")<<buf<<len<<(int)TestDataEqualLen;

    createDataCi(TEST_CI_VOBC,(int)TestDataHightLen,&buf,&len);
    QTest::newRow("TEST_CI_VOBC:buf len > len(real data)")<<buf<<len<<(int)TestDataHightLen;
    QList<DataType>::iterator type = testTypes.begin();
    QList<ModuleType>::iterator module = testModules.begin();
    ModuleType testModule;
    DataType testType;
    for(; module != testModules.end(); module++)
    {
        testModule = *module;
        type = testTypes.begin();
        for(; type != testTypes.end(); type++)
        {
            testType = *type;
            createDataRoute((int)testModule,(int)testType,&buf,&len);
            QString header = titleModule[(int)testModule] +":"+ titleType[(int)testType];
            const char* title = header.toLatin1().data();
            QTest::newRow(title)<<buf<<len<<(int)testType;
        }
    }

}

void CiProcessUnitTest::testReceiveUdpData()
{
    QFETCH(quint8*,data);
    QFETCH(quint16,len);
    QFETCH(int,datatype);
    if(datatype==TestDataEqualLen)
    {
        QSignalSpy spy(ciRoute, &CiService::sendToCiUi);
        QSignalSpy errorspy(ciRoute, &CiService::error);
        QSignalSpy spy_alarm(ciRoute, &CiService::ciAlarm);
        ciRoute->dealCiUdpData(data,len);
        QCOMPARE(spy.count(),1);
        if(errorspy.count() == 1)
        {//insert fail
            QList<QVariant> arguments = errorspy.takeFirst();
            QVERIFY(arguments.at(0).toInt() == CiService::EntryInsertError);
        }else if(errorspy.count()>1)
        {
            QCOMPARE(errorspy.count(),1);
        }
        QCOMPARE(spy_alarm.count(), 1);
    }else
    {
        QSignalSpy errorspy(ciRoute, &CiService::error);
        ciRoute->dealCiUdpData(data,len);
        QCOMPARE(errorspy.count(),1);
        QVERIFY(errorspy.takeFirst().at(0).toInt() == CiService::DataInvalid);
    }
}
void CiProcessUnitTest::testReceiveUdpData_data()
{
    QTest::addColumn<quint8*>("data");
    QTest::addColumn<quint16>("len");
    QTest::addColumn<int>("datatype");

    quint8* buf = NULL;
    quint16 len = 0;
    createDataCi(TEST_CI_CI,(int)TestDataNull,&buf,&len);
    QTest::newRow("TEST_CI_CI:data is null")<<buf<<len<<(int)TestDataNull;

    createDataCi(TEST_CI_CI,(int)TestDataHightHeaderLowLen,&buf,&len);
    QTest::newRow("TEST_CI_CI:buf len < len(real data)")<<buf<<len<<(int)TestDataHightHeaderLowLen;

    createDataCi(TEST_CI_CI,(int)TestDataEqualLen,&buf,&len);
    QTest::newRow("TEST_CI_CI:buf len = len(real data)")<<buf<<len<<(int)TestDataEqualLen;

    createDataCi(TEST_CI_CI,(int)TestDataHightLen,&buf,&len);
    QTest::newRow("TEST_CI_CI:buf len > len(real data)")<<buf<<len<<(int)TestDataHightLen;

}

void CiProcessUnitTest::createDataCi(int moduletype, int datatype, quint8** bufPtr, quint16* lenPtr)
{
    quint8* buf = NULL;
    buf = new quint8[TEST_BUF_LEN];
    quint8* bufForInvalid = NULL;
    quint16 lenForInvalid = 0;
    quint16 len = 0;
    *bufPtr = buf;
    switch(moduletype)
    {
    case TEST_CI_VOBC:
    {
        ci_vobc_data_t ciVobc;
        ciVobc.ci_vobc_interface = CI_VOBC_INTERFACE;
        ciVobc.send_id_msg = 0;
        ciVobc.incept_id_msg=1;
        ciVobc.edition_control_msg=1;
        ciVobc.edition_check_msg=1;
        ciVobc.msg_list=1;
        ciVobc.com_cycle=50;
        ciVobc.opposite_msg_list=1;
        ciVobc.smsg_self_list=1;
        ciVobc.pro_edition=1;
        ciVobc.nc_data=1;
        ciVobc.dir_train=1;
        ciVobc.n_psd=1;
        ciVobc.nid_psd_1=1;
        ciVobc.nc_psd_1=1;
        ciVobc.r_nc_psd_1=1;
        ciVobc.nid_psd_2=1;
        ciVobc.q_psd_2=1;
        ciVobc.r_nc_psd_2=1;
        ciVobc.q_signal_aspect=0xEE;
        len = b2v_var_to_bytes((quint8 *)&ciVobc, buf, ci_vobc_convert_table,ci_vobc_convert_table_len);
        if(CI_DEBUG) qDebug()<<"create data ci vobc  len="<<len;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len - 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            //*bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TEST_CI_CI:
    {
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
        len = b2v_var_to_bytes((quint8 *)&ciUdpData, buf, ci_ci_convert_table,ci_ci_convert_table_len);
        if(CI_DEBUG) qDebug()<<"create data ci cici len="<<len;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len - 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            //*bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    }
}
void CiProcessUnitTest::createDataRoute(int moduletype, int datatype, quint8** bufPtr, quint16* lenPtr)
{
    quint8* buf = NULL;
    quint8* bufForInvalid = NULL;
    quint16 lenForInvalid = 0;
    quint16 headeroffset = 0;
    quint16 dataoffset = 0;
    buf = new quint8[TEST_BUF_LEN];
    quint16 len = 0;
    *bufPtr = buf;
    *lenPtr = len;
    switch(moduletype)
    {
    case TestCiAtsAlarm:
    {
        ci_ats_data_h ciatsh;
        ci_ats_data_alarm ciatsalarm;
        ciatsh.ci_ats_interface = CI_ATS_INTERFACE;
        ciatsh.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&ciatsh, buf, ci_ats_h_convert_table,ci_ats_h_convert_table_len);
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
        dataoffset = b2v_var_to_bytes((quint8 *)&ciatsalarm, buf + headeroffset, ci_ats_data_alarm_covert_table,ci_ats_data_alarm_covert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiAtsStationyard:
    {
        ci_ats_data_h ciatsh;
        ci_ats_data_stationyard ciatsyard;
        ciatsh.ci_ats_interface = CI_ATS_INTERFACE;
        ciatsh.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&ciatsh, buf, ci_ats_h_convert_table,ci_ats_h_convert_table_len);
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
        dataoffset = b2v_var_to_bytes((quint8 *)&ciatsyard, buf + headeroffset, ci_ats_data_stationyard_covert_table,ci_ats_data_stationyard_covert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiZcMove:
    {
        ci_zc_data_h cizcdataheader;
        ci_zc_route cizcroute;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, buf, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
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
        dataoffset =  b2v_var_to_bytes((quint8 *)&cizcroute, buf + headeroffset, ci_zc_route_convert_table,ci_zc_route_convert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiZcPsd:
    {
        ci_zc_data_h cizcdataheader;
        ci_zc_psdinfo cizcpsdinfo;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, buf, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcpsdinfo.psd_size = 0x05;
        cizcpsdinfo.psd_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcpsdinfo, buf + headeroffset, ci_zc_psdinfo_convert_table,ci_zc_psdinfo_convert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            qDebug()<< "CI ZC PSD TestDataHightHeaderLowLen lenForInvalid="<<lenForInvalid <<" HEADEROFFSET="<<headeroffset << "len="<<len;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiZcEsb:
    {
        ci_zc_data_h cizcdataheader;
        ci_zc_esbbutton cizcesb;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, buf, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcesb.esb_emergency_size = 0x05;
        cizcesb.esb_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcesb, buf + headeroffset, ci_zc_esbbutton_convert_table,ci_zc_esbbutton_convert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiZcReturn:
    {
        ci_zc_data_h cizcdataheader;
        ci_zc_returnbutton cizcreturn;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, buf, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcreturn.returnbutton_size = 0x05;
        cizcreturn.returnbutton_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcreturn, buf + headeroffset, ci_zc_returnbutton_convert_table,ci_zc_returnbutton_convert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:{
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiZcSection:
    {
        ci_zc_data_h cizcdataheader;
        ci_zc_sectionused cizcsection;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, buf, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcsection.zc_size = 0x05;
        cizcsection.zc_state = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcsection, buf + headeroffset, ci_zc_sectionused_convert_table,ci_zc_sectionused_convert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    case TestCiZcRequ:
    {
        ci_zc_data_h cizcdataheader;
        ci_zc_approachunlock cizcreq;
        cizcdataheader.ci_zc_interface = CI_ZC_INTERFACE;
        cizcdataheader.send_id_msg = 0;
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
        headeroffset = b2v_var_to_bytes((quint8 *)&cizcdataheader, buf, ci_zc_data_h_convert_table,ci_zc_data_h_convert_table_len);
        //cizcreq.unlock_size = 0x05;
        cizcreq.unlock_num = rand()%2;
        dataoffset = b2v_var_to_bytes((quint8 *)&cizcreq, buf + headeroffset, ci_zc_approachunlock_convert_table,ci_zc_approachunlock_convert_table_len);
        len = headeroffset + dataoffset;
        switch (datatype)
        {
        case TestDataNull:
        {
            *bufPtr = NULL;
            *lenPtr = 0;
            delete[] buf;
        }
            break;
        case TestDataLowModule:
        {
            lenForInvalid = MODULE_HEADER_LEN-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualModule:
        {
            lenForInvalid = MODULE_HEADER_LEN;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataLowHeader:
        {
            lenForInvalid =MODULE_HEADER_LEN+1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualHeader:
        {
            lenForInvalid = headeroffset;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataHightHeaderLowLen:
        {
            lenForInvalid = len-1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        case TestDataEqualLen:
        {
            *bufPtr = buf;
            *lenPtr = len;
        }
            break;
        case TestDataHightLen:
        {
            lenForInvalid = len + 1;
            bufForInvalid = new quint8[lenForInvalid];
            memcpy(bufForInvalid, buf, lenForInvalid);
            *bufPtr = bufForInvalid;
            *lenPtr = lenForInvalid;
            delete[] buf;
        }
            break;
        }
    }
        break;
    }
}

quint8 CiProcessUnitTest::deleteAlltable()
{
    //delete data table
    QString connectName = "ciroute";
    QSqlDatabase dbConnInit;
    if(!QSqlDatabase::contains(connectName))
    {
        dbConnInit = QSqlDatabase::addDatabase("QMYSQL", connectName);
    }
    dbConnInit.setHostName("127.0.0.1");
    dbConnInit.setPort(3306);
    dbConnInit.setUserName("root");
    dbConnInit.setPassword("123456");
    dbConnInit.setDatabaseName("mss");
    QSqlDatabase dbConn = QSqlDatabase::database(connectName);
    int dbresult = dbConn.open();
    if(1 != dbresult)
    {
        dbConn.close();
        return -1;
    }
    QSqlQuery query = (QSqlQuery)QSqlDatabase::database(connectName);
    QString drop = "select concat('drop table ',table_name,';') from information_schema.TABLES where table_schema='mss'";
    if(!query.exec(drop))
    {
        return -1;
    }
    QString sqlDel =  "";
    while(query.next())
        sqlDel += query.value(0).toString();
    //if(CI_DEBUG) qDebug()<<"clean up testcase:sqlDel="<<sqlDel;
    if(sqlDel.compare("")==0)
    {
        return 0;
    }
    if(!query.exec(sqlDel))
    {
        qDebug()<<"CiProcessUnitTest::deleteAlltable fail";
        return -1;
    }
    dbConn.close();
    return 0;
}
QTEST_GUILESS_MAIN(CiProcessUnitTest)

#include "tst_ciprocess.moc"
