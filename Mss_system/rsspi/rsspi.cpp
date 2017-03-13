#include "rsspi.h"
/*
RsspI::RsspI()
{
    initConnection(&T1, &T1_cfg, &T2_cfg, &T1_flagman);
}

RsspI::RsspI(connection_cfg_t &T1_c, connection_cfg_t &T2_c, flag_carrier_t flag):
    T1_cfg(T1_c),T2_cfg(T2_c),T1_flagman(flag)
{
    initConnection(&T1, &T1_cfg, &T2_cfg, &T1_flagman);
}
*/

RsspI::RsspI()
{

}

RSSP_I_ERR RsspI::UpdataParam(connection_cfg_t* T1_cfg, connection_cfg_t* T2_cfg, flag_carrier_t flag_in)
{
    return initConnection(&T1, T1_cfg, T2_cfg, &flag_in);
}

RSSP_I_ERR RsspI::Depack(char *data,
       uint16_t data_len,
       char *rcv)
{
    qint32 curr_time = 0;
    RSSP_I_ERR result = RSSP_I_Depack((uint8_t *)data, data_len, (uint8_t *)rcv, &T1, curr_time);
    return result;
}

RSSP_I_ERR RsspI::pack(RSSP_I_PACK_ENUM type_to_pack,
                       quint8 *data,
                       quint16 data_len,
                       char *snd)
{
    qint32 curr_time = 0;
    return RSSP_I_Pack(type_to_pack, (uint8_t *)data, data_len, (uint8_t *)snd, &T1, curr_time);
}

bool RsspI::SSE_needed(){
    return T1.flagman.SSE_built_flag;
}
bool RsspI::SSR_needed(){
    return T1.flagman.SSR_built_flag;
}

