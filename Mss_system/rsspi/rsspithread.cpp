#include "rsspithread.h"

#define UDPSOCKETPORT 45454
#define RSSPIHEADLEN 22

qint8 RsspiThread::heapCount = 0;
connection_cfg_t RsspiThread::connect_cfg[] = {
    {   0x0101,         /*-< source address */
        0x0102031C,     /*-< SID1 */
        0x0405061E,     /*-< SID2 */
        0x07080914,     /*-< DATAVER_1 */
        0x0A0B0C16,     /*-< DATAVER_2 */
        0xFF,           /*-< MAX msg loss */
        0xFF,           /*-< MAX_Err_Count*/
        3000,
    },
    {   0x0202,
        0x1020302C,
        0x4050602E,
        0x70809024,
        0xA0B0C026,
        0xFF,
        0xFF,
        3000,
    },
    {   0x0303,
        0x0203045C,
        0x0506078E,
        0x08090A24,
        0x0B0C0D26,
        0xFF,
        0xFF,
        3000,
    },
    {   0x4040,
        0x45613546,
        0x78631256,
        0x12358456,
        0x4523684D,
        0xFF,
        0xFF,
        3000,
    },
};


flag_carrier_t RsspiThread::connect_flagman = {
    0x01,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0x00,
};

RsspiThread::RsspiThread(QObject *parent) : QObject(parent)
{

}

connection_cfg_t RsspiThread::GetConnectCfg(uint16_t addr)
{
    connection_cfg_t ret ;
    memset(&ret,0,sizeof(connection_cfg_t));
    for (int i=0;i<sizeof(connect_cfg)/sizeof(connection_cfg_t);i++)
    {
        if(connect_cfg[i].source_address==addr)
        {
            qDebug()<<"!!!!!!!!!!!!!!!!!!!!! GetConnectCfg addr="<<addr;
            ret = connect_cfg[i];
        }
    }
    return ret;
}

void RsspiThread::DetectConnectCfg(char* data, connection_cfg_t &src_cfg, connection_cfg_t &dst_cfg)
{
    quint16 temp1;
    quint16 temp2;
    uint16_t src_addr_val = 0;
    uint16_t dst_addr_val = 0;

  //  char* data = data_in;

    qDebug()<<"!!!!!!!!!!!!!!!!!!!!! DetectConnectCfg ";
    /*get source_add/target_addr */
    temp1 = (quint16)data[2];
    temp2 = (quint16)data[3];
    temp2 = temp2 << 8;
    src_addr_val= temp1 + temp2;
    src_cfg=GetConnectCfg(src_addr_val);

    temp1 = (quint16)data[4];
    temp2 = (quint16)data[5];
    temp2 = temp2 << 8;
    dst_addr_val= temp1+temp2;
    dst_cfg=GetConnectCfg(dst_addr_val);
}

void RsspiThread::BindReceiver()
{
    qDebug()<<" BindReceiver! ";
    pRsspiUdpSocket = new QUdpSocket(this);
    pRsspiUdpSocket->bind(UDPSOCKETPORT,QUdpSocket::ShareAddress);
    connect(pRsspiUdpSocket,&QUdpSocket::readyRead,this,&RsspiThread::readUdpReceiverData);
}

void RsspiThread::readUdpReceiverData()
{
    qDebug()<<" readUdpReceiverData() ";

    connection_cfg_t src_cfg;
    connection_cfg_t dst_cfg;
    memset(&src_cfg,0,sizeof(connection_cfg_t));
    memset(&dst_cfg,0,sizeof(connection_cfg_t));

    RSSP_I_ERR nRet;
    QHostAddress addr;
    quint16 port;
    pRsspi = new RsspI();

    while (pRsspiUdpSocket->hasPendingDatagrams())
    {
        QByteArray *readData = new QByteArray();//need to delete
        if(NULL == readData)
        {
            qDebug()<<"new QByteArray readData error in readUdpReceiverData";
            return;
        }

        readData->resize(pRsspiUdpSocket->pendingDatagramSize());
//        rsspiData.resize(pRsspiUdpSocket->pendingDatagramSize()- RSSPIHEADLEN);//remove head len(22)

//        QByteArray *pRsspiData = new QByteArray();//need to delete
        quint8 *pRsspiReadData = new quint8[512];
        if(NULL == pRsspiReadData)
        {
            qDebug()<<"new QByteArray error in readUdpReceiverData,heapCount = "<<heapCount;
            delete readData;
            return;
        }
//        if(NULL == pRsspiData)
//        {
//            qDebug()<<"new QByteArray error in readUdpReceiverData,heapCount = "<<heapCount;
//            delete readData;
//            return;
//        }
        else
        {
//            heapCount += 1;// new:heapCount + 1;delete heapCount - 1;init heapCount = 0
//            qDebug()<<"new pData in readUdpReceiverData,heapCount = "<<heapCount;
        }
//        pRsspiData->resize(pRsspiUdpSocket->pendingDatagramSize() - RSSPIHEADLEN);

        pRsspiUdpSocket->readDatagram(readData->data(),readData->size(),&addr,&port);
        qDebug()<<"receiver client addr:"<<addr<<"receiver client port:"<<port;
        qDebug()<<"receiver data:"<<readData->toHex();

        DetectConnectCfg(readData->data(),src_cfg,dst_cfg);

  //NOTE:      we act as rsspi reciver, depack need swicth dst&src
        nRet = pRsspi ->UpdataParam(&dst_cfg,&src_cfg,connect_flagman);

        if(nRet == ERR_INIT_OK)
        {

//            nRet = pRsspi->Depack(readData.data(),readData.size(),rsspiData.data());
            nRet = pRsspi->Depack(readData->data(),readData->size(),(char *)(pRsspiReadData));

            if(ERR_RSD_OK == nRet)
            {
//                qDebug()<<"Depack return data:"<<pRsspiData->toHex();
//                qDebug()<<"Depack return data:"<<QByteArray::fromRawData((char *)(pRsspiReadData),pRsspiUdpSocket->pendingDatagramSize() - RSSPIHEADLEN);
                Dispatch(pRsspiReadData,pRsspiUdpSocket->pendingDatagramSize() - RSSPIHEADLEN);
            }
            else
            {
                qDebug()<<"Depack Err:"<<nRet;
            }

        }
        else
        {
            qDebug()<<"Update Err:"<<nRet;
        }
        delete readData;

    }//while end

     delete pRsspi;
}

void RsspiThread::DeleteRsspiData(quint8 *pData)
{
    if(NULL == pData)
    {
        qDebug()<<"error:pData is NULL in DeleteRsspiData!";
    }
    else
    {
        delete []pData;
        heapCount -= 1;
    }
    qDebug()<<"delete pData in DeleteRsspiData,heapCount = "<<heapCount;
}

void RsspiThread::Dispatch(quint8 *pArrayData,quint16 len)
{
    qDebug()<<"Dispatch data";
    vobc_ats_header_t Header;
    quint16 msgOffset = 0;

    if(NULL == pArrayData || 0 >= len)
    {
        qDebug() << "NULL pointer!!! Exit.";
        return;
    }
    msgOffset = b2v_bytes_to_var(pArrayData, (quint8 *)&Header, vobc_common_header_cv_table, vobc_common_header_cv_table_len);
    if(msgOffset == vobc_common_header_cv_table_len)
    {
        qDebug() << "parse header error!!!";
        return;
    }
    qDebug()<<"Header.vobc_ats_interface is "<<Header.vobc_ats_interface;
    qDebug()<<"Header.send_id_msg is "<<Header.send_id_msg;
    switch(Header.vobc_ats_interface)
    {
        case(CI_ZC_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_ZC)
            {
                emit SendToZC(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_CI)
            {
                emit SendToCI(pArrayData,len);
            }
            break;
        }
        case(ATS_ZC_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_ZC)
            {
                emit SendToZC(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_ATS)
            {
                emit SendToATS(pArrayData,len);
            }
            break;
        }
        case(ATS_VOBC_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_VOBC)
            {
                emit SendToVobc(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_ATS)
            {
                emit SendToATS(pArrayData,len);
            }
            break;
        }
        case(VOBC_ZC_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_VOBC)
            {
                emit SendToVobc(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_ZC)
            {
                emit SendToZC(pArrayData,len);
            }
            break;
        }
        case(ATS_MSS_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_MSS)
            {
                emit SendToMSS(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_ATS)
            {
                emit SendToATS(pArrayData,len);
            }
            break;
        }
        case(VOBC_CI_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_VOBC)
            {
                emit SendToVobc(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_CI)
            {
                emit SendToCI(pArrayData,len);
            }
            break;
        }
        case(ATS_CI_INTERFACE):
        {
            if(Header.send_id_msg==ID_MESSAGE_CI)
            {
                emit SendToCI(pArrayData,len);
            }
            else if(Header.send_id_msg==ID_MESSAGE_ATS)
            {
                emit SendToATS(pArrayData,len);
            }
            break;
        }
        default:
        {
            qDebug()<<"receiver error interface!";
            break;
        }
    }
}
