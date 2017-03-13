#include "rsspisimulate.h"
#define UDPSOCKETPORT 45454
#define UDPSOCKETIP "127.0.0.1"

RsspiSimulate::RsspiSimulate(QObject *parent) : QObject(parent)
{

}

void RsspiSimulate::BindSend()
{
    qDebug()<<"BindSend()";
    pRsspiSend = new QUdpSocket(this);
    pRsspiSend->bind(UDPSOCKETPORT,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void RsspiSimulate:: SimulateMssRsspiData(quint8 *userData,quint16 len)
{
    connection_cfg_t T1_cfg = {
        0x0101,         /*-< source address */
        0x0102031C,     /*-< SID1 */
        0x0405061E,     /*-< SID2 */
        0x07080914,     /*-< DATAVER_1 */
        0x0A0B0C16,     /*-< DATAVER_2 */
        0xFF,           /*-< MAX msg loss */
        0xFF,           /*-< MAX msg err*/
        3000,
    };

    connection_cfg_t T2_cfg = {
        0x0202,
        0x1020302C,
        0x4050602E,
        0x70809024,
        0xA0B0C026,
        0x08,
        0x0C,
        3000,
    };

    flag_carrier_t T1_flagman = {
        0x01,
        0xAA,
        0xAA,
        0x00,
        0x00,
    };

    quint16 send_buf_len = 0;
    quint16 msg_len = 0;
    quint16 data_len = len;//vobc buf len
    RSSP_I_PACK_ENUM type_to_pack;
    RSSP_I_ERR ret_code;

    pRsspi = new RsspI();
    pRsspi->UpdataParam(&T1_cfg,&T2_cfg,T1_flagman);

    if (pRsspi->SSE_needed()){
        type_to_pack = ENUM_PACK_SSE;
        msg_len = SSE_LEN;
        send_buf_len = SSE_LEN;
    }else if (pRsspi->SSR_needed()){
        type_to_pack = ENUM_PACK_SSR;
        msg_len = SSR_LEN;
        send_buf_len = SSR_LEN;
    }else{//RSD Data
        type_to_pack = ENUM_PACK_RSD;
        data_len > 0 ? msg_len = RSD_LEN(data_len) : msg_len = 0;
        qDebug() << "need to pack rsd msg_len is " << msg_len;
    }

    if(msg_len > 0)
    {
         SimulateData.resize(data_len);
         memcpy(SimulateData.data(),userData,len);
         qDebug()<<"SimulateData: "<<SimulateData.toHex();

        sendBuf.resize(msg_len);
        ret_code = pRsspi->pack(type_to_pack, userData, data_len, sendBuf.data());
        qDebug()<<"ret_code = "<<ret_code;
        if((ERR_RSD_PACK_OK == ret_code) || (ERR_SSE_PACK_OK == ret_code) || (ERR_SSR_PACK_OK == ret_code)){
            pRsspiSend->writeDatagram(sendBuf.data(),sendBuf.size(),QHostAddress::Broadcast,UDPSOCKETPORT);
        }
    }
    delete[] userData;

}
