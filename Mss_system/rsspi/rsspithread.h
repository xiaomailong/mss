#ifndef RSSPITHREAD_H
#define RSSPITHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QUdpSocket>
#include "rsspi.h"
#include "vobc_ats_parse.h"
#include "vobc_data.h"

#define RSSPI_CFG_SIZE 4

class RsspiThread : public QObject
{
    Q_OBJECT
public:
    explicit RsspiThread(QObject *parent = 0);
    void BindReceiver();//bind UDP Socket
    void Dispatch(quint8 *pArrayData,quint16 len);

    void DetectConnectCfg(char* data, connection_cfg_t &src_cfg, connection_cfg_t &dst_cfg);
    connection_cfg_t GetConnectCfg(uint16_t addr);

    static void DeleteRsspiData(quint8 *pData);
private:
    QUdpSocket *pRsspiUdpSocket;//bind UdpSocket
    RsspI *pRsspi;
    QByteArray rsspiData;
    static qint8 heapCount;

    static connection_cfg_t connect_cfg[];
    static flag_carrier_t connect_flagman;
signals:
    void SendToVobc(quint8 *pRsspiData,quint16 len);
    void SendToATS(quint8 *pRsspiData,quint16 len);
    void SendToCI(quint8 *pRsspiData,quint16 len);
    void SendToMSS(quint8 *pRsspiData,quint16 len);
    void SendToZC(quint8 *pRsspiData,quint16 len);

public slots:
    void readUdpReceiverData();//when get readReady read receiver data
};

#endif // RSSPITHREAD_H
