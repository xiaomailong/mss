#ifndef RSSPI_H
#define RSSPI_H

#include "RSSP_I_cfg.h"
#include "RSSP_I_protocol.h"
#include "RSSP_I_process.h"
#include <QDebug>

class RsspI
{
public:
    RsspI();
    RSSP_I_ERR Depack(char *data,
                      quint16 data_len,
                      char *rcv);
    RSSP_I_ERR pack(RSSP_I_PACK_ENUM type_to_pack,
                           quint8 *data,
                           quint16 data_len,
                           char *snd);
    bool SSE_needed();
    bool SSR_needed();
    quint16 getRsspLen(){return HEADER_LEN + RSD_CHECK_LEN + CRC16_LEN;}
    RSSP_I_ERR UpdataParam(connection_cfg_t *T1_cfg, connection_cfg_t *T2_cfg, flag_carrier_t flag_in);
private:
    RSSP_I_helper_t T1;
};

#endif // RSSPI_H
