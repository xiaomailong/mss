#ifndef B2V_H
#define B2V_H
#include <qglobal.h>
#ifdef __cplusplus
extern "C"{
#endif
/**
 * @file b2v.h
 * @brief header file for flexb2v module, which is a flexible protocol converter
 * @author 003
 * @version
 * @date 2016-05-10
  */

//extern mod_dscrp_t ver_b2v;

#define _SIZE_OFFSET(t,m) (quint32)((size_t)(&((t*)0)->m))
#define _SIZE_OFFSET_ARRAY(t,arr,index,m) (quint32)((size_t)(&(((t*)0)->arr[index].m)))

#define UNIFW_BIG_ENDIAN    (0) /*-< 字节序大端模式  */
#define UNIFW_LITTLE_ENDIAN (1) /*-< 字节序小端模式  */
/**
 * 待解析关键信息描述表
 * 根据type类型，将width中的数据存储到相关结构体
 * 无偏移量, 使用增量解析的方式，即：对于不需要的变量，也需要描述条目，且宽度不能超过32bit/4字节
  */
typedef struct _var_item_t
{
    quint8  endian   ; /*-< 数据流中的字节序: 0表示大端在前, 1表示小端在前  */
    quint8  width    ; /*-< 在bit域中表示数据的bit位宽度, 在整字节版本数据中则表示字节数 */
    quint8  size     ; /*-< 在目标结构体中的数据宽度 1/2/4分别8/16/32位(有符号无符号用统一的sizeof(type)) */
    quint32 offset_d ; /*-< 数据在目标地址的偏移量 */
} var_item_t          ;

/**
 * @brief b2v_stream_to_var 将得到的协议信息解析到关键数据结构体中
 *
 * @param pstream  变量地址
 * @param pdst  结构体地址
 * @param table  数据描述表
 * @param var_num 变量数目,范围：[1,255]
 *
 * @return 解析结果
 *  -   0 解析成功
 *  - 非0 解析失败
  */
qint16 b2v_stream_to_var_byoffset(quint8 *pstream, quint16 offset, quint8 * pdst, const var_item_t * table, quint8 var_num);
qint16 b2v_stream_to_var(quint8 *pstream, quint8 * pdst, const var_item_t * table, quint8 var_num);

/**
 * @brief b2v_var_to_stream 将关键数据转换为协议信息
 * @detail 不能改变数据流数组中已有部分的数据值
 *
 * @param psrc 目标数组
 * @param pstream 数据结构体
 * @param table 数据解析表
 * @param var_num 条目数量,范围：[1,255]
 *
 * @return 转换是否成功
 *  -   0 转换成功
 *  - 非0 转换失败
  */
qint16 b2v_var_to_stream_byoffset(quint8 * psrc, quint8 * pstream, quint16 offset, const var_item_t * table, quint8 var_num);
qint16 b2v_var_to_stream(quint8 * psrc, quint8 * pstream, const var_item_t * table, quint8 var_num);

/**
 * @brief b2v_var_set 设置指定类型的变量到指定地址
 * @param paddr 目标地址
 * @param value 数据值
 * @param size  数据size大小
  */
qint16 b2v_var_set(quint8 *paddr, quint32 value, quint8 size);

/**
 * @brief b2v_var_get 获取指定地址的变量
 * @param paddr 数据地址
 * @param size  数据size大小
  */
quint32 b2v_var_get(quint8 *paddr, quint8 size);

/**
 * @brief b2v_stream_set_lsb 设置bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @brief b2v_stream_set_msb 设置bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @brief stream_set 设置bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width bit位宽度
 * @param endian 字节序
 */


qint16 b2v_stream_set_lsb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width); /*-< 小端版  */
qint16 b2v_stream_set_msb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width); /*-< 大端版  */
qint16 b2v_stream_set(quint8 *paddr, quint16 roffset, quint32 value, quint8 width, quint8 endian);

/**
 * @brief  b2v_stream_get_lsb 读取bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @brief  b2v_stream_get_msb 读取bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @brief  stream_get 读取bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width bit位宽度
 * @param endian 字节序
 */
quint32 b2v_stream_get_lsb(quint8 *paddr, quint16 roffset, quint8 width); /*-< 小端版  */
quint32 b2v_stream_get_msb(quint8 *paddr, quint16 roffset, quint8 width); /*-< 大端版  */
quint32 b2v_stream_get(quint8 *paddr, quint16 roffset, quint8 width, quint8 endian);


/** 以下为整字节版本, 对于完全整字节对齐的协议可提高效率  */
/** 整字节版通用函数  */
/**
 * @brief b2v_bytes_set_lsb 设置bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @brief b2v_bytes_set_msb 设置bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @brief b2v_bytes_set 设置bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @brief b2v_bytes_get_lsb 读取bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @brief b2v_bytes_get_msb 读取bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @brief b2v_bytes_get 读取bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width 字节数
 * @param endian 字节序
 */
qint16 b2v_bytes_set_lsb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width); /*-< 小端版  */
qint16 b2v_bytes_set_msb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width); /*-< 大端版  */
qint16 b2v_bytes_set(quint8 *paddr, quint16 roffset, quint32 value, quint8 width, quint8 endian);
quint32 b2v_bytes_get_lsb(quint8 *paddr, quint16 roffset, quint8 width); /*-< 小端版  */
quint32 b2v_bytes_get_msb(quint8 *paddr, quint16 roffset, quint8 width); /*-< 大端版  */
quint32 b2v_bytes_get(quint8 *paddr, quint16 roffset, quint8 width, quint8 endian);

/** 整字节版接口函数  */
/**
 * @brief b2v_bytes_to_var 将得到的协议信息解析到关键数据结构体中
 * @brief b2v_var_to_bytes 将关键数据转换为字节数
 * @param pstream  变量地址
 * @param pdst  结构体地址
 * @param table  数据描述表
 * @param psrc 目标数组
 * @param pstream 数据结构体
 * @param table 数据解析表
 * @param var_num 条目数量,范围：[1,255]
 */
qint16 b2v_bytes_to_var(quint8 *pstream, quint8 * pdst, const var_item_t * table, quint8 var_num);
qint16 b2v_var_to_bytes(quint8 *psrc, quint8 * pstream, const var_item_t * table, quint8 var_num);

qint16 b2v_bytes_to_var_byoffset(quint8 *pstream, quint16 offset, quint8 * pdst, const var_item_t * table, quint8 var_num);
qint16 b2v_var_to_bytes_byoffset(quint8 *psrc, quint8 * pstream, quint16 offset, const var_item_t * table, quint8 var_num);

#ifdef __cplusplus
}
#endif
#endif // B2V_H
