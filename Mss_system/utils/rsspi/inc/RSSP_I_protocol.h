#ifndef _RSSP_I_PROTOCOL
#define _RSSP_I_PROTOCOL

#include "RSSP_I_unibase.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @file RSSP_I_safety_protocol.h
 * @brief 安全通信协议RSSP-I
 * @detail 基于RSSP-I规范开发的安全通信协议，用于对发送数据进行封装和检验
 * @author zhang.yi36@byd.com
 * @date 2016-12-16
 *
 * $Id$
 */

#define DELAY       (5)   /*-<同一周期内连续的两个RSD帧的发送间隔 */
#define TIMEOUT     (250) /*-< 报文有效时间段 */
#define SSE_PERIOD  (250)

/**Support Funcs******************************/

RSSP_I_ERR validation_check(uint8_t *data, uint16_t data_len, RSSP_I_helper_t *helper);

/**发送端*************************************/

uint16_t pack_RSD(RSSP_I_helper_t *helper, uint8_t *data, uint16_t data_len, uint8_t *snd);

uint16_t pack_SSE(RSSP_I_helper_t *helper, uint8_t *snd);

uint16_t pack_SSR(RSSP_I_helper_t *helper, uint8_t *snd);
 

/**接收端************************************/

uint8_t RSD_verify(RSD_check_t check, RSSP_I_helper_t *helper);

uint8_t SSE_parser(SSE_check_t check, remote_time_param_t *remote_time);

uint8_t SSR_processor(SSR_check_t check, RSSP_I_helper_t *helper);

#ifdef __cplusplus
}
#endif

#endif //_RSSP_I_PROTOCOL
