#ifndef _RSSP_I_CFG
#define _RSSP_I_CFG

#include "unifw.h"
#include "b2v.h"

#ifdef __cplusplus
extern "C"{
#endif
typedef quint8 uint8_t;
typedef quint16 uint16_t;
typedef quint32 uint32_t;

#define SYSCKW_1 0xAE390B5A
#define SYSCKW_2 0xC103589C

#define MASK_1 0x0FC22F87
#define MASK_2 0XC3E887E1

#define HEADER_LEN          (6)         /*-< 共通报文头长度 */
#define VITAL_CHECK_LEN(s)  (s-6-2)     /*-< 安全检验域长度 */
#define SAFETY_DATA_LEN(s)  (s-2)       /*-< 安全数据除报文尾长度 */
#define CRC16_LEN           (2)         /*-< 报文尾CRC16长度 */

#define RSD_LEN(s)          (6+14+s+2)  /*-< RSD报文长度 */
#define RSD_CHECK_LEN       (14)        /*-< RSD检验域（不包括用户数据）长度 */
#define SSE_LEN             (20)        /*-< SSE报文长度 */
#define SSE_CHECK_LEN       (12)        /*-< SSE安全检验域长度 */
#define SSR_LEN             (25)        /*-< SSR报文长度 */
#define SSR_CHECK_LEN       (17)        /*-< SSR安全检验域长度 */

#if 0
uint8_t  sse_msg[SSE_LEN];      /*-< 本地发起SSE的报文存储数组 */
uint8_t  ssr_msg[SSR_LEN];      /*-< 本地回复SSR的报文存储数据 */
#endif

/**通信参数结构体***********************************/
/*可配置常量通信参数*/
typedef struct
{
    uint16_t source_address;/*-< 本端地址，通信双方互为接收发送端 */
    uint32_t SID_1;         /*-< 源标识*/
    uint32_t SID_2;
    uint32_t DataVer_1;     /*-< 数据版本,32位固定值 */
    uint32_t DataVer_2;
    uint8_t  MAX_Msg_Loss;  /*-< 最大容忍序列差值 */
    uint8_t  MAX_Err_Count; /*-< 最大可容忍连续RSD错误 */
    uint32_t  MIN_SSE_Period;
}connection_cfg_t;

/* 本地时间相关参数 */
typedef struct
{
    uint32_t time_counter;      /*-< 自增周期数 */
    uint32_t time_stamp_1;      /*-< 时间戳 */
    uint32_t time_stamp_2;
    uint32_t sse_start;         /*-< 发起SSE的开始时间 */
    uint32_t sse_timeout;       /*-< SSE超时计时 */
}local_time_param_t;

/* 远程端时间相关参数 */
typedef struct
{
    uint32_t last_time_counter;         /*-< 最近一次有效RSD报文序列号*/
    uint32_t enquirer_tc;
    uint32_t remote_SEQENQ[2];          /*-< 远程端请求方的SEQENQ值*/
    uint8_t  err_count;                 /*-< 连续RSD校验错误 */
}remote_time_param_t;

/*本地计算预存参数*/
typedef struct
{
    uint32_t last_SINIT_SID_Time;       /*-< 最近一次存储的有效时序值*/
    uint32_t last_SINIT_SID_SID[2];     /*-< 最近一次存储的有效时序校正参数 */
    uint32_t SINIT[2];                  /*-< 时序计算参数 */
    uint32_t precalc_Sinit[2];          /*-< 预计算SINIT*/
}vital_key_t;

/* 通信状态参数 */
typedef struct
{
    uint8_t primary_sys_flag;   /*-<0：备系 1：主系*/
    uint8_t local_AB_flag;      /*-<0xAA： A系，0xBB： B系*/
    uint8_t remote_AB_flag;     /*-<远程通信端的AB系flag*/
    uint8_t SSE_built_flag;      /*-<0：未生成SSE， 1：已生成SSE */
    uint8_t SSE_sent_flag;       /*-<0: 未发出SSE， 1：已发出SSE */
    uint8_t SSR_built_flag;     /*-<0：SSR未产生， 1：SSR已产生待发送 */
}flag_carrier_t;

/* 通信参数管理 */
typedef struct
{
    connection_cfg_t    local_cfg        ;    /*-< 本地端通信参数 */
    connection_cfg_t    remote_cfg       ;    /*-< 远程端通信参数 */
    local_time_param_t  local_time_param ;    /*-< 本地端时间参数 */
    remote_time_param_t remote_time_param;    /*-< 远程端时间参数 */
    vital_key_t         vital_key        ;    /*-< 加密计算相关参数 */
    flag_carrier_t      flagman          ;    /*-< 通信状态参数 */
}RSSP_I_helper_t;

/* 错误代码枚举类型 */
typedef enum
{
    ERR_PARAM_INVALID,
    ERR_INIT_OK,
    ERR_SECONDARY_SYS_OK,
    ERR_VALIDATION_OK,
    ERR_CRC16_FAILED,
    ERR_SOURCE_ADDR_ERR,
    ERR_DST_ADDR_ERR,
    ERR_VALIDATION_FAILED,
    ERR_SSR_UNSENT,
    ERR_SSE_UNSENT,
    ERR_RSD_PACK_OK,
    ERR_RSD_PACK_FAILED,
    ERR_SSE_PACK_OK,
    ERR_SSE_PACK_FAILED,
    ERR_SSR_PACK_OK,
    ERR_SSR_PACK_FAILED,
    ERR_PACK_FAILED,
    ERR_EXCEED_LIFETIME_SSE,
    ERR_EXCEED_LIFETIME_SSE_FAILED,
    ERR_EXCEED_LIFETIME,
    ERR_SSE_RSD_DISCARD,
    ERR_RSD_OK,
    ERR_RSD_FAILED_SSE,
    ERR_RSD_SERIAL_FAILED,
    ERR_RSD_FAILED,
    ERR_RSD_REDUNDANCY,
    ERR_SSE_OK_SSR,
    ERR_SSE_OK_NO_SSR,
    ERR_SSE_FAILED,
    ERR_SSR_OK,
    ERR_SSR_FAILED,
    ERR_SSR_SERIAL_ERR,
    ERR_SSE_TIMEOUT,
    ERR_NO_SSE_BUILT,
    ERR_DATA_ERR,
}RSSP_I_ERR;

/* 封装类型 */
typedef enum
{
    ENUM_PACK_RSD,
    ENUM_PACK_SSE,
    ENUM_PACK_SSR,
}RSSP_I_PACK_ENUM;

/**报文结构体*****************************************/

/* 通用报文头 */
typedef struct
{
    uint8_t  sys_type;      /*-< 协议交互类别, 0x01主系，0x02备系*/
    uint8_t  msg_type;      /*-< 报文类型*/
    uint16_t source_addr;   /*-< 源地址*/
    uint16_t dst_addr;      /*-< 目标地址*/
}msg_head_t;

/* RSD安全检验域 */
typedef struct
{
    uint32_t serial;            /*-< 序列号*/
    uint16_t safety_data_len;   /*-< 安全数据长度*/
    uint32_t SVC_1;             /*-< 安全检验通道*/
    uint32_t SVC_2;             /*-< 安全检验通道*/
}RSD_check_t;

/* RSD报文 */
typedef struct
{
    msg_head_t msg_header;
    RSD_check_t check_field;
    uint16_t CRC_16;
}RSD_t;

/* SSE安全检验域 */
typedef struct {
    uint32_t serial;    /*-< 序列号*/
    uint32_t SEQENQ_1;    /*-< 时序校正请求通道*/
    uint32_t SEQENQ_2;    /*-< 时序校正请求通道*/
}SSE_check_t;

/* SSE报文 */
typedef struct {
    msg_head_t msg_header;
    SSE_check_t check_field;
    uint16_t CRC_16;
} SSE_t;

/* SSR安全检验域 */
typedef struct
{
    uint32_t serial_r;  /*-< 应答方序列号*/
    uint32_t serial_e;  /*-< 请求方序列号*/
    uint32_t SEQINIT_1;   /*-< 时序初始化通道*/
    uint32_t SEQINIT_2;   /*-< 时序初始化通道*/
    uint8_t  dataver;   /*-< 数据版本*/
}SSR_check_t;

/* SSR报文 */
typedef struct
{
    msg_head_t msg_header;
    SSR_check_t check_field;
    uint16_t CRC_16;
} SSR_t;

/* 报文头和各安全检验域的b2v转换配置表 */
extern const var_item_t tbl_headerLSB[4];
extern const var_item_t tbl_RSD_check[4];
extern const var_item_t tbl_SSE_check[3];
extern const var_item_t tbl_SSR_check[5];

#ifdef __cplusplus
}
#endif

#endif //_RSSP_I_CFG
