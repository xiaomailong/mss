#ifndef _RSSP_I_PROCESS
#define _RSSP_I_PROCESS

#include "RSSP_I_protocol.h"

#ifdef __cplusplus
extern "C"{
#endif

//#define DEBUG     /*-< TODO:DBUGģʽ�꿪�� */

/**
 * @file   RSSP_I_procee.h
 * @brief  ��ȫͨ��Э��RSSP-I���ýӿ�
 * @detail �����ⲿ�ӿ�
 * @author zhang.yi36@byd.com
 * @date   2016-12-16
 *
 * $Id$
 */

/*
 * @return ��ʼ���ɹ�: EER_INIT_OK
 *         ��ʼ��ʧ��: ERR_INIT_FAILED
 */
RSSP_I_ERR initConnection(
                           RSSP_I_helper_t *helper, 
                           connection_cfg_t *local, 
                           connection_cfg_t *remote, 
                           flag_carrier_t *flags
                         );

/*
 * @return ����ɹ�: ERR_RSD_PACK_OK
 *         ���ʧ��: ERR_RSD_PACK_FAILED
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
 * @return ��ϵ��ͨ: ERR_SECONDARY_SYS_OK
 *         RSD�����ɹ�: ERR_RSD_OK
 *         RSD����ʧ��: ERR_RSD_FAILED
 *         SSE�����ɹ�: ERR_SSE_OK
 *         SSR�����ɹ�: ERR_SSR_OK
 *         SSR�����쳣: ERR_SSR_FAILED
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
