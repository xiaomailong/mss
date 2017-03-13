#include "powersimulatedataservice.h"
#include "mssdbconfig.h"

PowerSimulateDataService::PowerSimulateDataService()
{
#ifdef USE_UDP
    udpSocketOfPowersend = new QUdpSocket(this);
    udpSocketOfPowersend->bind(QHostAddress::AnyIPv4, 8888);
#endif
}

void PowerSimulateDataService::run()
{
    while(1)
    {
        quint8 buf[256];
        quint16 pad_len = 0;
        power_data_header_t s;
        s.type = rand()%2;
        s.voltage = 220.0+(rand())%10;
        s.owner = rand()%4;
        s.current = rand()%6;
        s.angle = rand()%180;
        s.hz = rand()%1000;
        s.handle = rand()%4;
        s.resevied2 = 0;
        quint16 offset;
        offset = b2v_var_to_bytes((quint8 *)&s, buf, power_data_header_cv_table, power_data_header_cv_table_len);
#ifdef USE_UDP
        pad_len += offset;
        udpSocketOfPowersend->writeDatagram(QByteArray::fromRawData((char *)buf,pad_len), QHostAddress(MSS_POWER_IP), MSS_POWER_PORT);
#else
        emit sendPowerSimulateData(buf);
#endif
        PowerSimulateDataService::msleep(2000);
    }
}
