#ifndef _RSSP_I_PROCESS
#define _RSSP_I_PROCESS

#include "RSSP_I_protocol.h"

#ifdef __cplusplus
extern "C"{
#endif

//#define DEBUG     /*-< TODO:DBUG模式宏开关 */

/**
 * @file   RSSP_I_procee.h
 * @brief  安全通信协议RSSP-I调用接口
 * @detail 面向外部接口
 * @author zhang.yi36@byd.com
 * @date   2016-12-16
 *
 * $Id$
 */

/*
 * @return 初始化成功: EER_INIT_OK
 *         初始化失败: ERR_INIT_FAILED
 */
RSSP_I_ERR initConnection(
                           RSSP_I_helper_t *helper, 
                           connection_cfg_t *local, 
                           connection_cfg_t *remote, 
                           flag_carrier_t *flags
                         );

/*
 * @return 组包成功: ERR_RSD_PACK_OK
 *         组包失败: ERR_RSD_PACK_FAILED
 */
RSSP_I_ERR RSSP_I_Pack(
                        RSSP_I_PACK_ENUM type_to_pack, 
                        uint8_t *data, 
                        uint16_t data_len, 
                        uint8_t *snd, 
                        RSSP_I_helper_t *helper, 
                        uint32_t now_time
                      );

/*
 * @return 备系连通: ERR_SECONDARY_SYS_OK
 *         RSD解析成功: ERR_RSD_OK
 *         RSD解析失败: ERR_RSD_FAILED
 *         SSE解析成功: ERR_SSE_OK
 *         SSR解析成功: ERR_SSR_OK
 *         SSR处理异常: ERR_SSR_FAILED
 */
RSSP_I_ERR RSSP_I_Depack(
                          uint8_t *data, 
                          uint16_t data_len, 
                          uint8_t *rcv, 
                          RSSP_I_helper_t *helper, 
                          uint32_t now_time
                        );


#ifdef __cplusplus
}
#endif

#endif //_RSSP_I_PROCESS
