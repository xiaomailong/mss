//#include "unifw.h"
#include "RSSP_I_cfg.h"
#include "RSSP_I_protocol.h"
#include "RSSP_I_process.h"

#define TRUE 1
#define FALSE 0

uint8_t  sse_msg[SSE_LEN];      /*-< 本地发起SSE的报文存储数组 */
uint8_t  ssr_msg[SSR_LEN];      /*-< 本地回复SSR的报文存储数据 */
/************************************************
 * @file    RSSP_I_process.c
 * @brief   面向外部接口函数
 * @detail
 * author zhang.yi36@byd.com
 * date 2016-12-16
 *
 * $Id$
 ************************************************
 *TODO:
 ************************************************
 */

/*
 * @brief  从字节流数据构建RSD的安全校验域结构体
 * @detail
 * @param  src   待转换的字节流
 * @param  check 用于存储结果的结构体指针
 * @return 失败返回0， 成功返回数据长度
 */
static uint16_t RSD_check_build(uint8_t *src, RSD_check_t *check)
{
    uint16_t ret = 0;
    
    if(NULL == src)
    {
        ret = 0;
    }
    else
    {
        ret = b2v_bytes_to_var(src, (uint8_t*)check, tbl_RSD_check, 4);
    }
    return ret;
}

/*
 * @brief  从字节流数据构建SSE的安全校验域结构体
 * @detail
 * @param  src   待转换的字节流
 * @param  check 用于存储结果的结构体指针
 * @return 失败返回0， 成功返回数据长度
 */
static uint16_t SSE_check_build(uint8_t *src, SSE_check_t *check)
{
    uint16_t ret = 0;

    if(NULL == src)
    {
        ret = 0;
    }
    else
    {
        ret = b2v_bytes_to_var(src, (uint8_t *)check, tbl_SSE_check, 3);
    }
    return ret;
}

/*
 * @brief  从字节流数据构建SSE的安全校验域结构体
 * @detail
 * @param  src   待转换的字节流
 * @param  check 用于存储结果的结构体指针
 * @return 失败返回0， 成功返回数据长度
 */
static uint16_t SSR_check_build(uint8_t *src, SSR_check_t *check)
{
    uint16_t ret = 0;

    if(NULL == src)
    {
        ret = 0;
    }
    else
    {
        ret = b2v_bytes_to_var(src, (uint8_t *)check, tbl_SSR_check, 5);
    }
    return ret;
}

/*
 * @brief  协议初始化
 * @detail 连接建立时初始化协议所需各值
 * @param  helper 协议参数结构体指针
 * @param  local  本地端通信参数结构体指针
 * @param  remote 远程端通信参数结构体指针
 * @return 初始化成功: EER_INIT_OK
 *         初始化失败: ERR_INIT_FAILED
 */
RSSP_I_ERR initConnection(RSSP_I_helper_t *helper, connection_cfg_t *local, connection_cfg_t *remote, flag_carrier_t *flags)
{
    RSSP_I_ERR ret = ERR_INIT_OK;
    if (NULL == helper || NULL == local || NULL == remote)
    {
        ret = ERR_PARAM_INVALID;
    }
    else
    {
        /* remove by zyx
        local->MAX_Msg_Loss = 0x08;
        local->MAX_Err_Count = 0x0C;
        */
        //local->MIN_SSE_Period = 3000;
       /* remove by litao
        remote->MAX_Msg_Loss = 0x08;
        remote->MAX_Err_Count = 0x0C;
        remote->MIN_SSE_Period = 3000;
        */
        flags->SSE_built_flag = 0;
        flags->SSE_sent_flag = 0;
        flags->SSR_built_flag = 0;

        helper->local_cfg=*local;
        helper->remote_cfg = *remote;
        helper->flagman = *flags;

        helper->local_time_param.time_counter = 0;
        helper->local_time_param.time_stamp_1 = helper->local_cfg.SID_1;
        helper->local_time_param.time_stamp_2 = helper->local_cfg.SID_2;

        helper->remote_time_param.last_time_counter = 0;
        helper->remote_time_param.enquirer_tc = 0;
        helper->remote_time_param.remote_SEQENQ[0] = 0;
        helper->remote_time_param.remote_SEQENQ[1] = 0;
        helper->remote_time_param.err_count= 0;

        helper->vital_key.last_SINIT_SID_Time = 0;
        helper->vital_key.last_SINIT_SID_SID[0] = 0;
        helper->vital_key.last_SINIT_SID_SID[1] = 0;
        helper->vital_key.SINIT[0] = 0x437A1418;
        helper->vital_key.SINIT[1] = 0x239DE41A;
        helper->vital_key.precalc_Sinit[0] = 0x437A1418;
        helper->vital_key.precalc_Sinit[1] = 0x239DE41A;

    }

    return ret;
}

/*
 * @brief  对外封装报文接口
 * @detail 提供给外部调用，封装RSSP-I报文用的接口
 * @param  type_to_pack 枚举类型，指定要封装的报文类型
 * @param  data  待发送数据
 * @param  data_len 待发送数据长度
 * @param  snd   储存封装后报文的数组
 * @param  helper 通信参数结构体指针
 * @return 封装成功: ERR_RSD_PACK_OK
 *         封装失败: ERR_RSD_PACK_FAILED
 */
RSSP_I_ERR RSSP_I_Pack(
                        RSSP_I_PACK_ENUM type_to_pack, 
                        uint8_t *data, 
                        uint16_t data_len, 
                        uint8_t *snd, 
                        RSSP_I_helper_t *helper, 
                        uint32_t now_time
                      )
{
    RSSP_I_ERR ret          ;
    uint16_t   pack_RSD_flag;
    uint16_t   sse_length   ;
    uint16_t   ssr_length   ;

    if ((NULL == data) || (0 >= data_len) || (NULL == helper))
    {
        ret = ERR_PARAM_INVALID;
    }
    else
    {
        if (ENUM_PACK_RSD == type_to_pack)
        {
            /* 发起了SSE或SSR并且未发送，停发RSD */
            if (TRUE == helper->flagman.SSR_built_flag)
            {
                ret = ERR_SSR_UNSENT;
            }
            else if ((TRUE == helper->flagman.SSE_built_flag) & (FALSE == helper->flagman.SSE_sent_flag))
            {
                ret = ERR_SSE_UNSENT;
            }
            /*else if (TRUE == helper->flagman.SSE_sent_flag)
            {
                ret = ERR_WAIT_FOR_SSR;
            }*/
            else
            {
                pack_RSD_flag = pack_RSD(helper, data, data_len, snd);
                if (RSD_LEN(data_len) == pack_RSD_flag)
                {
                    ret = ERR_RSD_PACK_OK;
                }
                else
                {
                    ret = ERR_RSD_PACK_FAILED; 
                }
            }
        }
        else if (ENUM_PACK_SSE == type_to_pack)
        {
            if (FALSE == helper->flagman.SSE_built_flag)
            {/*-< 没有生成过SSE，外部调用生成 */
                /* 仅在Depack中返回ERR_RSD_FAILED和ERR_SSE_PACK_FAILED，
                 * 协议自动发起SSE但封装失败的情况下，才允许在SSE_built_flag=FALSE的
                 * 前提下调用此封装接口。
                 * 否则外部不应手动发起SSE。
                 */
                sse_length = pack_SSE(helper, snd);
                if(SSE_LEN == sse_length)
                {
                    helper->flagman.SSE_built_flag = TRUE;  /*-< 发起SSE，下周期停发RSD*/
                    ret = ERR_SSE_PACK_OK;
                }
                else
                {
                    ret = ERR_SSE_PACK_FAILED;   /*-< 需要外部自行处理封装失败的情况 */
                }
            }
            else
            {
                /* SSE已生成，返回已在主流程中封装好的SSE */
                stop_tick_timer(&(helper->local_time_param), now_time);
                /* 检查SSE是否在等待周期内 */
                if (helper->local_time_param.sse_timeout > helper->local_cfg.MIN_SSE_Period)
                {
                    memcpy(snd, sse_msg, SSE_LEN);
                    helper->flagman.SSE_sent_flag = TRUE;
                    ret = ERR_SSE_PACK_OK;
                }
                else
                {
                    /* SSR解析失败，SSE需重发时，有可能依然在等待周期内，返回封装失败*/
                    ret = ERR_SSE_PACK_FAILED;
                }
            }
        }
        else if (ENUM_PACK_SSR == type_to_pack)
        {
            if (FALSE == helper->flagman.SSR_built_flag)
            {/* 没有生成过SSR，外部调用生成 */
                /* 仅在Depack中返回ERR_SSE_OK_NO_SSR，协议自动发起SSR但封装失败的情况下，
                 * 才允许在SSR_built_flag=FALSE的前提下调用此封装接口。
                 * 否则外部不应手动发起SSE。
                 */
                ssr_length = pack_SSR(helper, snd);
                if (SSR_LEN == ssr_length)
                {
                    /* SSR成功生成并返回，不需要设置状态flag*/
                    ret = ERR_SSR_PACK_OK;
                }
                else
                {
                    ret = ERR_SSR_PACK_FAILED;   /*-< 需要外部自行处理封装失败的情况 */
                }
            }
            else
            {
                /* 返回已在主流程中封装好的SSR */
                memcpy(snd, ssr_msg, SSR_LEN);
                /* 重置SSR flag，允许继续发送RSD */
                helper->flagman.SSR_built_flag = FALSE;
                ret = ERR_SSR_PACK_OK;
            }
        }
        else
        {
            ret = ERR_PACK_FAILED;
        }
    }
    return ret;
}

/*
 * @brief  对外解析报文接口
 * @detail 协议的主逻辑函数，解析收到的报文，并根据解析情况执行发起SSE或回复SSR等流程
 * @param  data  待解析的数据
 * @param  data_len 带解析的数据的长度
 * @param  rcv   解析成功后用户数据存储数组
 * @param  helper 通信参数结构体指针
 * @return 备系连通: ERR_SECONDARY_SYS_OK
 *         RSD解析成功: ERR_RSD_OK
 *         RSD解析失败: ERR_RSD_FAILED_SSE
 *         SSE解析成功: ERR_SSE_OK_SSR
 *         SSR解析成功: ERR_SSR_OK
 *         SSR处理异常: ERR_SSR_FAILED
 */
RSSP_I_ERR RSSP_I_Depack(
                           uint8_t *data, 
                           uint16_t data_len, 
                           uint8_t *rcv, 
                           RSSP_I_helper_t *helper, 
                           uint32_t now_time
                        )
{
    RSSP_I_ERR  ret               ;
    RSSP_I_ERR  valid_flag        ;
    uint8_t     msg_type       = 0;
    uint8_t     strck[256]        ;
    RSD_check_t RSD_check         ;
    uint16_t    RSD_check_flag = 0;
    uint8_t     msg_loss       = 0;
    uint16_t    sse_length     = 0;
    SSE_check_t SSE_check;
    uint8_t     parse_SSE_flag = 0;
    uint16_t    ssr_length     = 0;
    SSR_check_t SSR_check         ;
    uint8_t     parse_SSR_flag = 0;

    if (NULL == data || 0 == data_len || NULL == helper)
    {/* invalid parametres*/
        ret = ERR_PARAM_INVALID;
    }
    else
    {
        valid_flag = validation_check(data, data_len, helper);  /*-< 头尾有效性校验 */
        if (ERR_VALIDATION_OK == valid_flag)
        {
            if (0x01 == data[0])
            {/* 主系 */
                msg_type = data[1];
                memcpy(strck, (data+HEADER_LEN), VITAL_CHECK_LEN(data_len));


                if ((0x80 == msg_type) || (0x81 == msg_type))   /*-< RSD */
                {
                    if (TRUE == helper->flagman.SSE_built_flag)
                    {/* 等待SSR，忽略RSD */
                        ret = ERR_SSE_RSD_DISCARD;
                    }
                    else
                    {/* 未发起过SSE */
                        /* 记录远程端是A机还是B机*/
                        if (0x80 == msg_type)
                        {
                            helper->flagman.remote_AB_flag = 0xAA;
                        }
                        else if (0x81 == msg_type)
                        {
                            helper->flagman.remote_AB_flag = 0XBB;
                        }

                        RSD_check_build(strck, &(RSD_check));

                        if (RSD_check.serial != helper->remote_time_param.last_time_counter)
                        {/* 不是冗余RSD */
                            msg_loss = compareCounters(helper->remote_time_param.last_time_counter, 
                                    RSD_check.serial, 
                                    helper->local_cfg.MAX_Msg_Loss);

                            if (0 == msg_loss)
                            {/* 序列号检验错误 */
                                helper->remote_time_param.err_count = helper->remote_time_param.err_count + 1;
                                if (helper->remote_time_param.err_count > helper->local_cfg.MAX_Err_Count)
                                {
                                    /* 连续错误数超出上限， RSD超过有效保持时间 */
                                    /* 未发起过SSE， 不对SSE超时进行判断 */
                                    sse_length = pack_SSE(helper, sse_msg);
                                    if(SSE_LEN == sse_length)
                                    {
                                        helper->flagman.SSE_built_flag = TRUE;
                                        set_tick_timer(&(helper->local_time_param), now_time);
                                        ret = ERR_EXCEED_LIFETIME_SSE;
                                    }
                                    else
                                    {
                                        ret = ERR_EXCEED_LIFETIME;
                                    }
                                }
                                else
                                {
                                    /* 没有超过连续错误上限， 就错误RSD发起SSE */
                                    /* 未发起过SSE， 不对SSE超时进行判断 */
                                    sse_length = pack_SSE(helper, sse_msg);
                                    if(SSE_LEN == sse_length)
                                    {
                                        helper->flagman.SSE_built_flag = TRUE;
                                        set_tick_timer(&(helper->local_time_param), now_time);
                                        ret = ERR_RSD_FAILED_SSE;
                                    }
                                    else
                                    {
                                        ret = ERR_RSD_SERIAL_FAILED;   /*-< 生成SSE失败，需要外部手动重建*/
                                    }
                                 }
                            }
                            else    
                            {/* 序列号检验通过*/
                                /* 存储最近一次有效RSD的序列号 */
                                helper->remote_time_param.last_time_counter = RSD_check.serial;

                                RSD_check_flag = RSD_verify(RSD_check, helper);
                                if(0 == RSD_check_flag)
                                {/* RSD安全校验失败 */
                                    helper->remote_time_param.err_count = helper->remote_time_param.err_count + 1;

                                    if (helper->remote_time_param.err_count > helper->local_cfg.MAX_Err_Count)
                                    {
                                        /* 连续错误数超出上限， RSD超过有效保持时间 */
                                        /* 未发起过SSE， 不对SSE超时进行判断 */
                                        sse_length = pack_SSE(helper, sse_msg);
                                        if(SSE_LEN == sse_length)
                                        {
                                            helper->flagman.SSE_built_flag = TRUE;
                                            set_tick_timer(&(helper->local_time_param), now_time);
                                            ret = ERR_EXCEED_LIFETIME_SSE;
                                        }
                                        else
                                        {
                                            ret = ERR_EXCEED_LIFETIME;
                                        }
                                    }
                                    else
                                    {
                                        /* 没有超过连续错误上限， 就错误RSD发起SSE */
                                        /* 未发起过SSE， 不对SSE超时进行判断 */
                                        sse_length = pack_SSE(helper, sse_msg);
                                        if(SSE_LEN == sse_length)
                                        {
                                            helper->flagman.SSE_built_flag = TRUE;
                                            set_tick_timer(&(helper->local_time_param), now_time);
                                            ret = ERR_RSD_FAILED_SSE;
                                        }
                                        else
                                        {
                                            ret = ERR_RSD_FAILED;   /*-< 生成SSE失败，需要外部手动重建*/
                                        }
                                    }
                                }
                                else
                                {
                                    /* RSD安全校验成功，清除连续错误数*/
                                    helper->remote_time_param.err_count = 0;
                                    memcpy(rcv, (data+HEADER_LEN+RSD_CHECK_LEN), 
                                                (VITAL_CHECK_LEN(data_len)-RSD_CHECK_LEN));

                                    ret = ERR_RSD_OK;
                                }
                            }
                        }
                        else
                        {
                            ret = ERR_RSD_REDUNDANCY;
                        }  /*-< 丢弃冗余RSD不处理 */
                    }
                }
                else if (0x90 == msg_type)      /*-< SSE */
                {
                    SSE_check_build(strck, &(SSE_check));
                    parse_SSE_flag = SSE_parser(SSE_check, &(helper->remote_time_param));
                    if (0 == parse_SSE_flag)
                    {
                        ret = ERR_SSE_FAILED;
                    }
                    else
                    {
                        ssr_length = pack_SSR(helper, ssr_msg);
                        if (SSR_LEN == ssr_length)
                        {
                            helper->flagman.SSR_built_flag = TRUE;
                            ret = ERR_SSE_OK_SSR;
                        }
                        else
                        {
                            ret = ERR_SSE_OK_NO_SSR;    /*-< 需要外部手动重建SSR */
                        }
                    }
                }
                else if (0x91 == msg_type)
                {
                    /* 收到SSR，更新SSE超时计时 */
                    stop_tick_timer(&(helper->local_time_param), now_time);

                    if (TRUE == helper->flagman.SSE_built_flag)
                    {
                        if (helper->local_time_param.sse_timeout <= helper->local_cfg.MIN_SSE_Period)
                        {/*SSE发起过且等待未超时*/
                            SSR_check_build(strck, &(SSR_check));

                            if (SSR_check.serial_e == helper->local_time_param.time_counter)
                            {
                                /* SSR的请求方序列号和本地序列号一致 */
                                /* 发起SSE后停发RSD，序列号应保持在发起SSE时的值 */
                                parse_SSR_flag = SSR_processor(SSR_check, helper);
                                if (TRUE == parse_SSR_flag)
                                {
                                    helper->flagman.SSE_built_flag = FALSE;  /*-< SSR已收，重置SSE flag */
                                    helper->flagman.SSE_sent_flag = FALSE;
                                    helper->remote_time_param.err_count = 0;  /*-< 校正完成，错误数清零*/
                                    reset_tick_timer(&(helper->local_time_param));  /*-< 时钟清零 */
                                    ret = ERR_SSR_OK;
                                }
                                else
                                {
                                    ret = ERR_SSR_FAILED;
                                }
                            }
                            else
                            {
                                /* 请求方序列号不一致，丢弃SSR */
                                ret = ERR_SSR_SERIAL_ERR;
                            }
                        }
                        else
                        {/* SSE等待超时 */
                            ret = ERR_SSE_TIMEOUT;
                        }
                    }
                    else
                    {/* 未发起过SSE，丢弃SSR */
                        ret = ERR_NO_SSE_BUILT;
                    }
                }
                else
                {
                    ret = ERR_DATA_ERR;
                }
            }
            else if(0x02 == data[0])
            {/*secondary sys*/
                ret = ERR_SECONDARY_SYS_OK;   /*-< 备系连通 */
            }
            else
            {
                ret = ERR_DATA_ERR;     /*-< 数据错误，无法解析*/
            }
        }
        else
        {/* 头尾有效性检验失败，返回相应错误码*/
#ifdef DEBUG
                printp("头尾有效性校验错误: %d\n", valid_flag);
#endif
            ret = ERR_VALIDATION_FAILED;
        }
    }
    return ret;
}
