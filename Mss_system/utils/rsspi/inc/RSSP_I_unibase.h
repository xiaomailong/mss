#ifndef _RSSP_I_UNIBASE_
#define _RSSP_I_UNIBASE_

#include "RSSP_I_cfg.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @file RSSP_I_unibase.h
 * @brief
 * @detail
 * author zhang.yi36@byd.com
 * date 2016-12-06
 *
 * $Id$
 */
/*长度s的数据x循环左移n位 */
#define ROTATE_LEFT(x, s, n) (((x)<<(n)) | ((x)>>((-n) & (s-1))))
/*长度s的数据x循环右移n位 */
#define ROTATE_RIGHT(x, s, n) (((x)>>(n)) |((x)<<((-n) & (s-1)))

/*
 * @brief  LFSR左移算法
 * @detail 利用LFSR特性，左移32位，每逢输出位为1时与多项式异或
 * @param  x    操作数1
 * @param  y    操作数2
 * @param  mask 附加输入多项式
 * @return 结果值
 */
uint32_t LFSR_Add(uint32_t x, uint32_t y, uint32_t mask);

/*
 * @brief  LFSR左移算法
 * @detail 利用LFSR特性，右移32位后与多项式异或
 * @param  x    操作数1
 * @param  y    操作数2
 * @param  mask 附加输入多项式
 * @return 结果值
 */
uint32_t LFST_Post(uint32_t x, uint32_t y, uint32_t mask);

/*
 * @brief  检验序列号
 * @detail 比较收到的RSD序列号和最近一次有效的序列号，并将差值与最大可容忍序列差比较
 * @param  last_counter 最近一次存储的序列号
 * @param  rcv_counter  收到的RSD报文中的序列号
 * @param  max_loss     最大可容忍差值
 * @return 序列号错序或超过最大可容忍差值返回0，否则返回序列号差值
 */
uint8_t compareCounters(uint32_t last_counter, uint32_t rcv_counter, uint8_t max_loss);

/*
 * @brief  CRC32计算器
 * @detail 用于生成计算SVC所需的CRC32的接口，在函数中调用相关的函数计算并查表实现
 * @param  data 需要被计算的数据指针
 * @return 返回CRC32码
 */
uint32_t CRC32_calculator(uint32_t *data);

/*
 * @brief  时间自增
 * @detail 时间相关参数自增
 * @param  时间相关参数数据结构体指针
 * @return 参数无效返回0，自增成功返回1
 */
uint16_t forwardTimer(local_time_param_t *timer);

void set_tick_timer(local_time_param_t *local, uint32_t now);

void reset_tick_timer(local_time_param_t *local);

void stop_tick_timer(local_time_param_t *local, uint32_t now);
/*
 * @brief  时序校正请求通道计算器
 * @detail 当请求时序校正时生成时序校正请求码
 * @param  sid  SID源标识
 * @param  ts_e 请求方时间戳
 * @return 时序校正请求通道
 */
uint32_t SEQENQ_calculator(uint32_t sid, uint32_t ts_e);

/**
 * @brief  时序初始化通道计算器
 * @detail 计算时序初始化通道，多用于SVC检验中计算时序校正参数
 * @param  senq     时序校正请求通道
 * @param  sid      SID源标识
 * @param  ts_r     应答方时间戳
 * @param  dataver  数据版本
 * @return 时序初始化通道
 */
uint32_t SEQINIT_calculator(uint32_t senq, uint32_t sid, uint32_t ts_r, uint32_t dataver);

/*
 * @brief  SVC计算器
 * @detail 计算SVC安全通道
 * @param  crc  CRC32
 * @param  scw  SCW系统检验字
 * @param  sid  SID源标识
 * @param  ts   时间戳
 */
uint32_t SVC_calculator(uint32_t crc, uint32_t scw, uint32_t sid, uint32_t ts);

/*
 * @brief  计算本地最近一次存储的时序有效值
 * @detail 用于SVC校验算法过程和更新本地最近时序有效值
 * @param  sinit    时序初始化通道
 * @param  sid      SID源标识
 * @param  ts       时间戳
 * @param  gaps     现序列号和最近有效序列号的间隔，gaps=0则没有间隔，更新时序有效值
 * @return 返回时序有效值计算机过
 */
uint32_t last_calculator(uint32_t sinit, uint32_t sid, uint32_t ts, uint32_t gaps);

#ifdef __cplusplus
}
#endif

#endif //_RSSP_I_UNIBASE_
