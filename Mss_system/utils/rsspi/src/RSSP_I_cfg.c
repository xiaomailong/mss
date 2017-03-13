#include "RSSP_I_cfg.h"

extern const var_item_t tbl_headerLSB[4] =
{
    {UNIFW_LITTLE_ENDIAN,1,1,_SIZE_OFFSET(msg_head_t, sys_type),},
    {UNIFW_LITTLE_ENDIAN,1,1,_SIZE_OFFSET(msg_head_t, msg_type),},
    {UNIFW_LITTLE_ENDIAN,2,2,_SIZE_OFFSET(msg_head_t, source_addr),},
    {UNIFW_LITTLE_ENDIAN,2,2,_SIZE_OFFSET(msg_head_t, dst_addr),},
};

extern const var_item_t tbl_RSD_check[4] =
{
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(RSD_check_t, serial),},
    {UNIFW_LITTLE_ENDIAN,2,2,_SIZE_OFFSET(RSD_check_t, safety_data_len),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(RSD_check_t, SVC_1),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(RSD_check_t, SVC_2),},
};

extern const var_item_t tbl_SSE_check[3] =
{
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSE_check_t, serial),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSE_check_t, SEQENQ_1),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSE_check_t, SEQENQ_2),},
};

extern const var_item_t tbl_SSR_check[5] =
{
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSR_check_t,serial_r),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSR_check_t,serial_e),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSR_check_t,SEQINIT_1),},
    {UNIFW_LITTLE_ENDIAN,4,4,_SIZE_OFFSET(SSR_check_t,SEQINIT_2),},
    {UNIFW_LITTLE_ENDIAN,1,1,_SIZE_OFFSET(SSR_check_t,dataver),},
};
