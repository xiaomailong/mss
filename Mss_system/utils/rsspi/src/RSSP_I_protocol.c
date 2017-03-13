#include "unifw.h"
#include "b2v.h"
#include "crc.h"
#include "RSSP_I_cfg.h"
#include "RSSP_I_protocol.h"


/************************************************
 * @file    RSSP_I_protocol.c
 * @brief   处理协议报文封装、解析和通信管理
 * @detail
 * author zhang.yi36@byd.com
 * date 2016-12-16
 *
 * $Id$
 ************************************************
 */

/**发送端****************************************/

/*
 * @brief  封装报文头部数据
 * @detail 仅在本文件中使用，抽取对各类型报文共通的头部封装操作封装为单独的函数
 * @param  flags    通信状态数据结构体指针
 * @param  local    本地端通信参数结构体指针
 * @param  remote   远程端通信参数结构体指针
 * @param  header   待写入的报文头部数据结构体的指针
 * @return 0封装失败 1封装成功
 */
static uint16_t pack_header(flag_carrier_t *flags, connection_cfg_t *local, 
                            connection_cfg_t *remote, msg_head_t *header)
{
    uint16_t ret = 1;
    if (NULL == flags || NULL == local || NULL == remote)
    {
        ret = 0;
    }
    else{
        /* 设置主备系标志 */
        if (1 == flags->primary_sys_flag)
        {
            header->sys_type = 0x01;
        }
        else if (0 == flags->primary_sys_flag)
        {
            header->sys_type = 0x02;
        }

        /* 报文类型在各封装函数中另行设置 */
        /* 源地址和目的地址 */
        header->source_addr = local->source_address;
        header->dst_addr = remote->source_address;
    }
    return ret;
}

/*
 * @brief  校验安全数据报文头尾的有效性
 * @detail
 * @param  data   待检数据
 * @param  length 数据长度
 * @param  helper 协议参数管理结构体指针
 * @return CRC16校验错误 ERR_CRC16_FAILED
 *         源地址错误    ERR_SOURCE_ADDR_ERR
 *         目的地址错误  ERR_DST_ADDR_ERR
 *         校验成功      ERR_VALIDATION_OK
 */
RSSP_I_ERR validation_check(uint8_t *data, uint16_t data_len, RSSP_I_helper_t *helper)
{
    RSSP_I_ERR check_flag = ERR_VALIDATION_OK;
	
	uint8_t data_body[256];
    uint8_t get_CRC16[2];
    uint16_t crc16_val = 0;
    uint16_t src_addr_val = 0;
    uint16_t dst_addr_val = 0;
    uint16_t temp1;
    uint16_t temp2;

	uint16_t cal_CRC_16 = 0;

    if (NULL == data || 0 == data_len || NULL == helper)
    {
        check_flag = ERR_PARAM_INVALID;
    }

    memcpy(data_body, data, SAFETY_DATA_LEN(data_len));
    memcpy(get_CRC16, (data+SAFETY_DATA_LEN(data_len)), CRC16_LEN);

    temp1 = (uint16_t)get_CRC16[0];
    temp2 = (uint16_t)get_CRC16[1];
    temp2 = temp2 << 8;
    crc16_val = temp1 + temp2;

/*    cal_CRC_16 = cb_crc16_ccitt(data_body, SAFETY_DATA_LEN(data_len));

    if (crc16_val != cal_CRC_16)
    {
        check_flag = ERR_CRC16_FAILED;
    }
    else
*/    {
        /* 源地址校验 */
        temp1 = (uint16_t)data[2];
        temp2 = (uint16_t)data[3];
        temp2 = temp2 << 8;
        src_addr_val = temp1 + temp2;
        if (src_addr_val != helper->remote_cfg.source_address)
        {
            check_flag = ERR_SOURCE_ADDR_ERR;
        }
        else{}

        /* 目的地址校验*/
        temp1 = (uint16_t)data[4];
        temp2 = (uint16_t)data[5];
        temp2 = temp2 << 8;
        dst_addr_val = temp1+ temp2;
        if (dst_addr_val != helper->local_cfg.source_address)
        {
            check_flag = ERR_DST_ADDR_ERR;
        }
        else{}

        /*zyx if max msg loss is 0xff then ignore address missmatch
      if (helper->local_cfg.MAX_Msg_Loss == 0xFF){
            if ((check_flag == ERR_DST_ADDR_ERR) || (check_flag == ERR_SOURCE_ADDR_ERR))
            {
                check_flag = ERR_VALIDATION_OK;
            }
       }
            */
    }

    return ERR_VALIDATION_OK;
}

/*
 * @brief  发送端RSD报文封装
 * @detail 通过通信模块发送数据前，将待发送数据按照协议计算SVC并封装成RSD
 * @param  helper 协议参数结构体指针
 * @param  data   待封装数据指针
 * @param  data_len 待处理数据长度
 * @param  snd    储存封装后报文的字节数组
 * @return 失败返回0，成功返回封装完成的RSD报文长度
 */
uint16_t pack_RSD(RSSP_I_helper_t *helper, uint8_t *data, uint16_t data_len, uint8_t *snd)
{
    uint16_t    ret         = 0;
	uint16_t    package_len = 0;
    msg_head_t  header         ;
	RSD_check_t check_data     ;
	uint16_t    check_len   = 0;
	uint16_t    crc_16      = 0;

    if ((NULL == data) || (0 >= data_len) || (NULL == snd) || (NULL == helper))
    {
        ret = 0;
    }
    else
    {
        /* 步进时间参数，一个周期号对应一个RSD报文*/
        forwardTimer(&(helper->local_time_param));
        
        pack_header(&(helper->flagman), &(helper->local_cfg), 
                    &(helper->remote_cfg), &header);
        
        /* 设置AB机标志 */
        if (0xAA == (helper->flagman).local_AB_flag)
        {
            header.msg_type = 0x80;
        }
        else if (0xBB == (helper->flagman).local_AB_flag)
        {
            header.msg_type = 0x81;
        }
        package_len = b2v_var_to_bytes((uint8_t *)(&header), snd, tbl_headerLSB, 4);
        
        check_data.serial = helper->local_time_param.time_counter;
        check_data.safety_data_len = data_len + 8;
        /* TODO: SVC calculation algorithm */
        check_data.SVC_1 = 0;
        check_data.SVC_2 = 0;

        check_len = b2v_var_to_bytes((uint8_t *)(&check_data), (snd+package_len), tbl_RSD_check, 4);
        package_len = package_len + check_len;

        memcpy((snd+package_len), data, data_len);
        package_len = package_len + data_len;
        
        crc_16 = cb_crc16_ccitt(snd, package_len);
        snd[package_len] = (uint8_t)(crc_16 & 0xFF);
        crc_16 = crc_16 >> 8;
        snd[package_len+1] = (uint8_t)crc_16;
        package_len = package_len + CRC16_LEN;

        ret = package_len;
    }
    return ret;
}

/* @brief  发送端SSE报文封装
 * @detail 发起SSE时按照协议计算SEQENQ的值并封装成SSE
 * @param  helper 协议参数结构体指针
 * @param  snd    储存封装后报文的字节数组
 * @return 失败返回0，成功返回封装完成的SSE报文长度
 */
uint16_t pack_SSE(RSSP_I_helper_t *helper, uint8_t *snd)
{
    uint16_t    ret         = 0;
    uint16_t    package_len = 0;
    msg_head_t  header         ;
    SSE_check_t check_data     ;
    uint16_t    check_len   = 0;
    uint16_t    crc_16      = 0;

    if (NULL == helper)
    {
        ret = 0;
    }
    else
    {
        pack_header(&(helper->flagman), &(helper->local_cfg), 
                    &(helper->remote_cfg), &header);
        header.msg_type = 0x90;

        package_len = b2v_var_to_bytes((uint8_t *)(&header), snd, tbl_headerLSB, 4);

        check_data.serial = helper->local_time_param.time_counter;
        check_data.SEQENQ_1 = SEQENQ_calculator(
                                helper->local_cfg.SID_1,
                                helper->local_time_param.time_stamp_1
                                );
        check_data.SEQENQ_2 = SEQENQ_calculator(
                                helper->local_cfg.SID_2,
                                helper->local_time_param.time_stamp_2
                                );

        check_len = b2v_var_to_bytes((uint8_t *)(&check_data), (snd+package_len), tbl_SSE_check, 3);
        package_len = package_len + check_len;
        
        crc_16 = cb_crc16_ccitt(snd, package_len);
        snd[package_len] = (uint8_t)(crc_16 & 0xFF);
        crc_16 = crc_16 >> 8;
        snd[package_len+1] = (uint8_t)crc_16;
        package_len = package_len + CRC16_LEN;

        ret = package_len;
    }
    return ret;
}

/* @brief  发送端SSR报文封装
 * @detail 回复SSR时按照协议计算SEQINIT的值并封装成SSR
 * @param  helper 协议参数结构体指针
 * @param  snd    储存封装后报文的字节数组
 * @return 失败返回0，成功返回封装完成的SSR报文长度
 */
uint16_t pack_SSR(RSSP_I_helper_t *helper, uint8_t *snd)
{
    uint16_t    ret         = 0;
    uint16_t    package_len = 0;
    msg_head_t  header         ;
    SSR_check_t check_data     ;
    uint16_t    check_len   = 0;
    uint16_t    crc_16      = 0;
    uint32_t    senq        = 0;
    uint32_t    sid         = 0;
    uint32_t    ts          = 0;
    uint32_t    dv          = 0;

    if (NULL == helper)
    {
        ret = 0;
    }
    else
    {
        pack_header(&(helper->flagman), &(helper->local_cfg), 
                    &(helper->remote_cfg), &header);
        header.msg_type = 0x91;

        package_len = b2v_var_to_bytes((uint8_t *)(&header), snd, tbl_headerLSB, 4);

        check_data.serial_r = helper->local_time_param.time_counter;
        check_data.serial_e = helper->remote_time_param.enquirer_tc;
        /*TODO: SEQINIT calculation */
        //senq = helper->remote_time_param.remote_SEQENQ[0];
        //sid = helper->local_cfg.SID_1;
        //ts = helper->local_time.time_stamp_1;
        //dv = helper->local_cfg.Dataver_1;
        //check_data.SEQINIT_1 = SEQINIT_calculator(senq, sid, ts, dv);

        //senq = helper->remote_time_param.remote_SEQENQ[1];
        //sid = helper->local_cfg.SID_2;
        //ts = helper->local_time.time_stamp_2;
        //dv = helper->local_cfg.Dataver_2;
        //check_data.SEQINIT_2 = SEQINIT_calculator(senq, sid, ts, dv);
        
        check_data.SEQINIT_1 = 0;
        check_data.SEQINIT_2 = 0;
        check_data.dataver = 0x01;
        
        check_len = b2v_var_to_bytes((uint8_t *)(&check_data), (snd+package_len), tbl_SSR_check, 5);
        package_len = package_len + check_len;

        crc_16 = cb_crc16_ccitt(snd, package_len);
        snd[package_len] = (uint8_t)(crc_16 & 0xFF);
        crc_16 = crc_16 >> 8;
        snd[package_len+1] = (uint8_t)crc_16;
        package_len = package_len + CRC16_LEN;

        ret = package_len;
    }
    return ret;
}

/*
 * @brief  检验收到的RSD报文
 * @detail 根据协议校验SVC值
 * @param  check  RSD安全检验域数据结构体
 * @param  helper 协议参数结构体指针
 * @return 检验成功1， 失败0
 */
uint8_t RSD_verify(RSD_check_t check, RSSP_I_helper_t *helper)
{
    uint8_t ret = 1;
    if (NULL == helper)
    {
        ret = 0;
    }
    else
    {
        //printp("\nRSD Verification:\n");
        //printp("%2x %2x %2x %2x\n", check.serial, check.safety_data_len, check.SVC_1, check.SVC_2);
        /*TODO: this is a fake verification for udp test */
        /*if (1 != check.SVC_1)
        {
            ret = 0;
        }
        else{}
        */

    }

    return ret;
}

/*
 * @brief  解析收到的SSE报文
 * @detail 解析报文得到请求方的SEQENQ值
 * @param  check  SSE报文安全检验域数据结构体
 * @param  key    加密算法关键值结构指针
 * @param  remote_time 远程通信端的时间相关参数结构体
 * @return 检验成功1， 失败0
 */
uint8_t SSE_parser(SSE_check_t check, remote_time_param_t *remote_time)
{
    uint8_t ret = TRUE;
    if (NULL == &(check) || NULL == remote_time)
    {
        ret = FALSE;
    }
    else
    {
        //printp("\nSSE parser.\n");
        remote_time->enquirer_tc = check.serial;
        remote_time->remote_SEQENQ[0] = check.SEQENQ_1;
        remote_time->remote_SEQENQ[1] = check.SEQENQ_2;
    }
    
    return ret;
}

/*
 * @brief  检验收到的SSR报文
 * @detail 根据协议校验SEQINIT值，校正时序
 * @param  check  RSD安全检验域数据结构体
 * @param  helper 协议参数结构体指针
 * @return 检验成功1， 失败0
 */
uint8_t SSR_processor(SSR_check_t check, RSSP_I_helper_t *helper)
{
    uint8_t ret = 1;
    if (NULL == helper)
    {
        ret = 0;
    }
    else
    {
        //printp("\nSSR processor.\n");
        helper->remote_time_param.last_time_counter = check.serial_r;
    }
    return ret;
}
