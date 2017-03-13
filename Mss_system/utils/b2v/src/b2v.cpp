#include "unifw.h"
#include "unifw_errno.h"
#include "b2v.h"


/**
 * @brief b2v_var_set 设置指定类型的变量到指定地址
 * @param paddr 目标地址
 * @param value 变量值
 * @param size 指定的数据大小
 * @return 0表示正常执行  1表示执行错误
 */
int16_t b2v_var_set(quint8 *paddr, quint32 value, quint8 size)
{
    int16_t ret = 0;
    //printp("b2v_var_set: %lu %d \n", value, size);
    switch (size)
    {
        case 1:
            *((quint8 *)paddr) = (quint8)value;
            break;
        case 2:
            *((quint16 *)paddr) = (quint16)value;
            break;
        case 4:
            *((quint32 *)paddr) = (quint32)value;
            break;
        default:
            ret = 1;
            break;
    }
    return ret;
}

/**
 * @brief b2v_var_get 从指定地址获取指定类型的变量
 * @param paddr 目标地址
 * @param size 指定的数据大小
 * @return 解析变量值
 */
quint32 b2v_var_get(quint8 *paddr, quint8 size)
{
    quint32 value = 0;
    switch (size)
    {
        case 1:
            value = (quint32)(*((quint8 *)paddr));
            break;
        case 2:
            value = (quint32)(*((quint16 *)paddr));
            break;
        case 4:
            value = (quint32)(*((quint32 *)paddr));
            break;
        default:
            /** 解析类型正确由应用配置保证 */
            qDebug("b2v_var_get: size err [%u] \r\n", size);
            break;
    }
    return value;
}

/**
 * @brief b2v_stream_set_lsb 设置bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width bit位宽度
 * @return 解析偏移量
 */
int16_t b2v_stream_set_lsb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width)
{
    /*-  初始化 */
    quint16 i = 0U;
    quint16 index = 0U;
    quint16 ref = 0U;
    quint32 data1 = 0U;
    quint8  datas[5] = {0U};
    quint16 len = 0U;

    //printp("b2v_stream_set_lsb: %lx %u %lx %02x\n", paddr, roffset, value, width);

    /*- 将数据左对齐*/
    data1 = value << (32U - width);
    index = roffset / 8U;
    ref = roffset % 8U;
    datas[0] = (quint8)((data1>>ref)>>24);
    datas[1] = (quint8)((data1>>ref)>>16);
    datas[2] = (quint8)((data1>>ref)>>8 );
    datas[3] = (quint8)((data1>>ref)>>0 );
    datas[4] = (quint8)((data1<<(32U-ref))>>24);
    //printp("datas: %02x %02x %02x %02x %02x \n", datas[0], datas[1], datas[2], datas[3], datas[4]);
    //printp("size: %u %u %u\n", index, ref, width);

    /*-  判断地址指针是否有效 */
    if (paddr != NULL)
    {
        len = (ref + width + 7U) / 8U;
        /*- @alias 清除原数据中的width bit长度的数据*/
        if ((ref+width) <= 8)
        {
            data1 = paddr[index];
            paddr[index] = (data1&(0xff<<(8-ref))) + (data1&(0xff>>(width + ref)));
            //printp("set paddr: %u %u \n", index, paddr[index]);
        }
        else
        {
            data1 = paddr[index];
            paddr[index] = data1&(0xff<<(8-ref));
            for (i = 1U; i < (len-1); i++)
                {
                        ((quint8 *)paddr)[index+i] = 0;
                }
            if ((ref+width)%8 == 0)
            {
                ((quint8 *)paddr)[index+len-1] = 0;
            }
            else
            {
                data1 = paddr[index+len-1];
                paddr[index+len-1] = data1&(0xff>>((width + ref)%8));
            }

        }
        //printp("len = %u \n", len);
        /*- @alias 循环将当前数据压入目标地址 */
        for (i = 0U; i < len; i++)
        {
            /** 此处赋值体现LSB */
            ((quint8 *)paddr)[index+i] |= datas[len-1-i];
        }

        /*-  更新偏移量 */
        roffset += width;
    }
    else
    {
        /*-< do_nothing*/
    }

    /*-  解析结果 */
    return roffset;
}

/**
 * @brief b2v_stream_set_msb 设置bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width bit位宽度
 * @return 解析偏移量
 */
int16_t b2v_stream_set_msb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width)
{
    /*-  初始化 */
    quint16 i = 0U;
    quint16 index = 0U;
    quint16 ref = 0U;
    quint32 data1 = 0U;
    quint8  datas[5] = {0U};
    quint16 len = 0U;

    /*- 将数据左对齐*/
    data1 = value << (32U - width);
    index = roffset / 8U;
    ref = roffset % 8U;
    datas[0] = (quint8)((data1>>ref)>>24);
    datas[1] = (quint8)((data1>>ref)>>16);
    datas[2] = (quint8)((data1>>ref)>>8 );
    datas[3] = (quint8)((data1>>ref)>>0 );
    datas[4] = (quint8)((data1<<(32U-ref))>>24);

    /*-  判断地址指针是否有效 */
    if (paddr != NULL)
    {
        len = (ref + width + 7U) / 8U;
        /*- @alias 清除原数据中的width bit长度的数据*/
        if ((ref+width) <= 8)
        {
            data1 = paddr[index];
            paddr[index] = (data1&(0xff<<(8-ref))) + (data1&(0xff>>(width + ref)));
        }
        else
        {
            data1 = paddr[index];
            paddr[index] = data1&(0xff<<(8-ref));
            for (i = 1U; i < (len-1); i++)
                {
                        ((quint8 *)paddr)[index+i] = 0;
                }
            if ((ref+width)%8 == 0)
            {
                ((quint8 *)paddr)[index+len-1] = 0;
            }
            else
            {
                data1 = paddr[index+len-1];
                paddr[index+len-1] = data1&(0xff>>((width + ref)%8));
            }

        }
        /*- @alias 循环将当前数据压入目标地址 */
        for (i = 0U; i < len; i++)
        {
            ((quint8 *)paddr)[index+i] |= datas[i];
        }

        /*-  更新偏移量 */
        roffset += width;
    }
    else
    {
        /*-< do_nothing*/
    }

    /*-  解析结果 */
    return roffset;
}

/**
 * @brief b2v_stream_set 设置bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width bit位宽度
 * @param endian 字节序
 */
int16_t b2v_stream_set(quint8 *paddr, quint16 roffset, quint32 value, quint8 width, quint8 endian)
{
    if (UNIFW_BIG_ENDIAN == endian)
    {
        /*- 大端模式 */
        b2v_stream_set_msb(paddr, roffset, value, width);
    }
    else if (UNIFW_LITTLE_ENDIAN == endian)
    {
        /*- 小端模式 */
        b2v_stream_set_lsb(paddr, roffset, value, width);
    }
    return 0;
}
/**
 * @brief  b2v_stream_get_lsb 读取bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width bit位宽度
 * @return 解析数据值
 */
quint32 b2v_stream_get_lsb(quint8 *paddr, quint16 roffset, quint8 width)
{
   /*-  初始化 */
    quint16 index = 0U;
    quint8 offset = 0U;
    quint32 data = 0U;

    /** 判断源数据指针有效 */
    if ((paddr != NULL))
    {
        /*-  获取待解析数据的起始字节和起始位 */
        index = (quint16)(roffset / 8U);
        offset = (quint8)(roffset % 8U);
        data = 0U;

        /*- 先解析32bit数据 */
        data = (quint32)(paddr[index])  << (24U + offset);
        data += (quint32)(paddr[index+1U]) << (16U + offset);
        data += (quint32)(paddr[index+2U]) << (8U + offset);
        data += (quint32)(paddr[index+3U]) << (offset);
        data += (quint32)(paddr[index+4U]) >> (8U - offset);
        /*- 截取低地址位的有效width长度数据 */
        data = data >> (32U - width);
        switch (width)
        {
            case 8:
                data = data;
                break;
            case 16:
                data = ((data<<8)&0x00ff00) + ((data>>8)&0xff);
                break;
            case 24:
                data = ((data<<16)&0xff0000) + ((data)&0x00ff00) + ((data>>16)&0x0000ff);
                break;
            case 32:
                data = ((data<<24)&0xff000000) + ((data<<8)&0x00ff0000) + ((data>>8)&0xff00) + ((data>>24)&0xff);
                break;
            default:
                break;
        }
    }
    else
    {
        /*-  do_nothing */
    }

    /*-  解析结果 */
    return data;
}

/**
 * @brief  b2v_stream_get_msb 读取bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width bit位宽度
 * @return 解析数据值
 */
quint32 b2v_stream_get_msb(quint8 *paddr, quint16 roffset, quint8 width)
{
   /*-  初始化 */
    quint16 index = 0U;
    quint8 offset = 0U;
    quint32 data = 0U;

    /*- 判断源数据指针有效 */
    if ((paddr != NULL))
    {
        /*-  获取待解析数据的起始字节和起始位 */
        index = (quint16)(roffset / 8U);
        offset = (quint8)(roffset % 8U);
        data = 0U;

        /*- 先解析32bit数据 */
        data = (quint32)(paddr[index])  << (24U + offset);
        data += (quint32)(paddr[index+1U]) << (16U + offset);
        data += (quint32)(paddr[index+2U]) << (8U + offset);
        data += (quint32)(paddr[index+3U]) << (offset);
        data += (quint32)(paddr[index+4U]) >> (8U - offset);
        /*- 截取低地址位的有效width长度数据 */
        data = data >> (32U - width);
    }
    else
    {
        ;/*-  do_nothing */
    }

    /*-  解析结果 */
    return data;
}

/**
 * @brief  b2v_stream_get 读取bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width bit位宽度
 * @param endian 字节序
 */
quint32 b2v_stream_get(quint8 *paddr, quint16 roffset, quint8 width, quint8 endian)
{
    quint32 ret = 0;
    if (UNIFW_BIG_ENDIAN == endian)
    {
        /*- 大端模式 */
        ret = b2v_stream_get_msb(paddr, roffset, width);
    }
    else if (UNIFW_LITTLE_ENDIAN == endian)
    {
        /*- 小端模式 */
        ret = b2v_stream_get_lsb(paddr, roffset, width);
    }
    return ret;
}

/**
 * @brief b2v_stream_to_var_byoffset 将得到的协议信息解析到关键数据结构体中
 * @param pstream  变量地址
 * @param offset   偏移量
 * @param pdst  结构体地址
 * @param table  数据描述表
 * @param var_num 变量数目,范围：[1,255]
 *
 * @return 解析结果
 *  -  -E_INVALID_RANGE 解析失败
 *  -  当前解析成功的位置
 */
int16_t b2v_stream_to_var_byoffset(quint8 * pstream, quint16 offset, quint8 * pdst, const var_item_t * table, quint8 var_num)
{
    quint8 i = 0;
    quint16 bits_offset = 0;
    quint8 * pdst_var = NULL;
    quint32 value = 0;
    /*- 有效性检查 */
    if((NULL == pstream) || (NULL == pdst) || (NULL == table) || (0 == var_num))
    {
        return -E_INVALID_RANGE;
    }
    bits_offset = offset; /*-< 初始解析位置 */
    for(i=0; i<var_num; i++)
    {
        /*- 目的地址 */
        pdst_var = pdst + table[i].offset_d;
        /*- 从数据流得到变量值   */
        value = b2v_stream_get(pstream, bits_offset, table[i].width, table[i].endian);

        /*- 设置变量值到存储地址 */
        b2v_var_set(pdst_var, value, table[i].size);
        /*- 下一个变量解析偏移量 */
        bits_offset = bits_offset + table[i].width;
    }
    return bits_offset;
}

/**
 * @brief b2v_stream_to_var 将得到的协议信息解析到关键数据结构体中，默认偏移量为0
 * @param pstream  变量地址
 * @param offset   偏移量
 * @param pdst  结构体地址
 * @param table  数据描述表
 * @param var_num 变量数目,范围：[1,255]
 *
 * @return 解析结果
 *  -  -E_INVALID_RANGE 解析失败
 *  -  当前解析成功的位置
 */
int16_t b2v_stream_to_var(quint8 * pstream, quint8 * pdst, const var_item_t * table, quint8 var_num)
{
    return b2v_stream_to_var_byoffset(pstream, 0, pdst, table, var_num);
}

/**
 * @brief b2v_var_to_stream_byoffset 将数据结构体变量转换为协议信息数组
 *
 * @param psrc 源数据结构体
 * @param pstream 目标数据流数组
 * @param offset 偏移量
 * @param table 数据解析表
 * @param var_num 条目数量,范围：[1,255]
 *
 * @return 转换是否成功
 *  -  -E_INVALID_RANGE 解析失败
 *  -  当前解析成功的位置
 */
int16_t b2v_var_to_stream_byoffset(quint8 * psrc, quint8 * pstream, quint16 offset, const var_item_t * table, quint8 var_num)
{
    quint8 i = 0;
    quint32 value = 0;
    quint16 bits_offset = 0;
    quint8 * pdst_var = NULL;

    /*- 入参有效性检查 */
    if((NULL == psrc) || (NULL == pstream) || (NULL == table) || (0 == var_num))
    {
        return -E_INVALID_RANGE;
    }
    bits_offset = offset; /*-< 初始解析位置 */
    for(i=0; i<var_num; i++)
    {
        /*- 源结构体变量地址 */
        pdst_var = psrc + table[i].offset_d;
        /*- 从数据结构体得到变量值   */
        value = b2v_var_get(pdst_var, table[i].size);
        /*- 转换变量到bit数据流 */
        b2v_stream_set(pstream, bits_offset, value, table[i].width, table[i].endian);
        /*- 下一个变量转换偏移量 */
        bits_offset = bits_offset + table[i].width;
    }

    return bits_offset;
}

/**
 * @brief b2v_var_to_stream 将数据结构体变量转换为协议信息数组，默认偏移量为0
 *
 * @param psrc 源数据结构体
 * @param pstream 目标数据流数组
 * @param table 数据解析表
 * @param var_num 条目数量,范围：[1,255]
 *
 * @return 转换是否成功
 *  -  -E_INVALID_RANGE 解析失败
 *  -  当前解析成功的位置
 */
int16_t b2v_var_to_stream(quint8 * psrc, quint8 * pstream, const var_item_t * table, quint8 var_num){
    return b2v_var_to_stream_byoffset(psrc, pstream, 0, table, var_num);
}


/** 整字节版本: 可提高效率 */
/**
 * @brief b2v_bytes_set_lsb 设置bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width 字节数
 */
int16_t b2v_bytes_set_lsb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width)
{
    switch (width)
    {
        case 1:
            paddr[roffset] = value;
            break;
        case 2:
            paddr[roffset+0] = (value>>0)&0xff;
            paddr[roffset+1] = (value>>8)&0xff;
            break;
        case 4:
            paddr[roffset+0] = (value>>0 )&0xff;
            paddr[roffset+1] = (value>>8 )&0xff;
            paddr[roffset+2] = (value>>16)&0xff;
            paddr[roffset+3] = (value>>24)&0xff;
            break;
        default:
            break;
    }
    return 0;
}

/**
 * @brief b2v_bytes_set_msb 设置bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width 字节数
 */
int16_t b2v_bytes_set_msb(quint8 *paddr, quint16 roffset, quint32 value, quint8 width)
{
    switch (width)
    {
        case 1:
            paddr[roffset] = value;
            break;
        case 2:
            paddr[roffset+0] = (value>>8)&0xff;
            paddr[roffset+1] = (value>>0)&0xff;
            break;
        case 4:
            paddr[roffset+0] = (value>>24)&0xff;
            paddr[roffset+1] = (value>>16)&0xff;
            paddr[roffset+2] = (value>>8 )&0xff;
            paddr[roffset+3] = (value>>0 )&0xff;
            break;
        default:
            break;
    }
    return 0;
}

/**
 * @brief b2v_bytes_set 设置bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param value 变量值
 * @param width 字节数
 * @param endian 字节序
 */
int16_t b2v_bytes_set(quint8 *paddr, quint16 roffset, quint32 value, quint8 width, quint8 endian)
{
    if (UNIFW_BIG_ENDIAN == endian)
    {
        /*- 大端模式 */
        b2v_bytes_set_msb(paddr, roffset, value, width);
    }
    else if (UNIFW_LITTLE_ENDIAN == endian)
    {
        /*- 小端模式 */
        b2v_bytes_set_lsb(paddr, roffset, value, width);
    }
    return 0;
}

/**
 * @brief b2v_bytes_get_lsb 读取bit数据流中指定数据宽度的变量值(按照指定字小端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width 字节数
 * @return 解析变量值
 */
quint32 b2v_bytes_get_lsb(quint8 *paddr, quint16 roffset, quint8 width)
{
    quint32 value = 0;
    switch (width)
    {
        case 1:
            value = paddr[roffset];
            break;
        case 2:
            value = ((paddr[roffset+1]<<8)&0xff00) + paddr[roffset];
            break;
        case 4:
            value = ((paddr[roffset+3]<<24)&0xff000000) + ((paddr[roffset+2]<<16)&0xff0000) +
                    ((paddr[roffset+1]<<8)&0xff00) + paddr[roffset];
            break;
        default:
            break;
    }
    return value;
}

/**
 * @brief  b2v_bytes_get_msb 读取bit数据流中指定数据宽度的变量值(按照指定字大端节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width 字节数
 * @return 解析变量值
 */
quint32 b2v_bytes_get_msb(quint8 *paddr, quint16 roffset, quint8 width)
{
    quint32 value = 0;
    switch (width)
    {
        case 1:
            value = paddr[roffset];
            break;
        case 2:
            value = ((paddr[roffset]<<8)&0xff00) + paddr[roffset+1];
            break;
        case 4:
            value = ((paddr[roffset]<<24)&0xff000000) + ((paddr[roffset+1]<<16)&0xff0000) +
                    ((paddr[roffset+2]<<8)&0xff00) + paddr[roffset+3];
            break;
        default:
            break;
    }
    return value;
}

/**
 * @brief  b2v_bytes_get 读取bit数据流中指定数据宽度的变量值(按照指定字节序)
 * @param paddr 目标地址
 * @param roffset 偏移量
 * @param width 字节数
 * @param endian 字节序
 */
quint32 b2v_bytes_get(quint8 *paddr, quint16 roffset, quint8 width, quint8 endian)
{
    quint32 ret = 0;
    if (UNIFW_BIG_ENDIAN == endian)
    {
        /*- 大端模式 */
        ret = b2v_bytes_get_msb(paddr, roffset, width);
    }
    else if (UNIFW_LITTLE_ENDIAN == endian)
    {
        /*- 小端模式 */
        ret = b2v_bytes_get_lsb(paddr, roffset, width);
    }
    return ret;
}

/**
 * @brief b2v_bytes_to_var_byoffset 将得到的协议信息解析到关键数据结构体中
 * @param pstream  变量地址
 * @param pdst  结构体地址
 * @param table  数据描述表
 * @param var_num 变量数目,范围：[1,255]
 *
 * @return 解析结果
 *  -  -E_INVALID_RANGE 转换失败
 *  -  执行结束后最新的bit偏移量
 */
int16_t b2v_bytes_to_var_byoffset(quint8 *pstream, quint16 offset, quint8 * pdst, const var_item_t * table, quint8 var_num)
{
    quint8 i = 0;
    quint8 * pdst_var = NULL;
    quint32 value = 0;
    /*- 入参有效性检查 */
    if((NULL == pstream) || (NULL == pdst) || (NULL == table) || (0 == var_num))
    {
        return -E_INVALID_RANGE;
    }
    for(i=0; i<var_num; i++)
    {
        /*- 目的地址 */
        pdst_var = pdst + table[i].offset_d;
        /*- 从数据流得到变量值   */
        value = b2v_bytes_get(pstream, offset, table[i].width, table[i].endian);

        /*- 设置变量值到存储地址 */
        b2v_var_set(pdst_var, value, table[i].size);
        /*- 下一个变量解析偏移量 */
        offset = offset + table[i].width;
    }
    return offset; /*-< 返回最终的offset */
}

/**
 * @brief b2v_bytes_to_var 将得到的协议信息解析到关键数据结构体中，默认偏移量为0
 * @param pstream  变量地址
 * @param pdst  结构体地址
 * @param table  数据描述表
 * @param var_num 变量数目,范围：[1,255]
 *
 * @return 解析结果
 *  -  -E_INVALID_RANGE 转换失败
 *  -  执行结束后最新的bit偏移量
 */
int16_t b2v_bytes_to_var(quint8 *pstream, quint8 * pdst, const var_item_t * table, quint8 var_num)
{
    return b2v_bytes_to_var_byoffset(pstream, 0, pdst, table ,var_num);
}

/**
 * @brief b2v_var_to_bytes_byoffset 将变量结构体转换为数据流，数据流可指定偏移量
 *
 * @param psrc 目标数组
 * @param pstream 数据结构体
 * @param table 数据解析表
 * @param var_num 条目数量,范围：[1,255]
 *
 * @return 转换是否成功
 *  -  -E_INVALID_RANGE 转换失败
 *  -  执行结束后最新的bit偏移量
 */
int16_t b2v_var_to_bytes_byoffset(quint8 *psrc, quint8 * pstream, quint16 offset, const var_item_t * table, quint8 var_num)
{
    quint8 i = 0;
    quint32 value = 0;
    quint8 * pdst_var = NULL;

    /*- 入参有效性检查 */
    if((NULL == psrc) || (NULL == pstream) || (NULL == table) || (0 == var_num))
    {
        return -E_INVALID_RANGE;
    }
    /*- 遍历解析表解析数据 */
    for(i=0; i<var_num; i++)
    {
        /*- 源结构体变量地址 */
        pdst_var = psrc + table[i].offset_d;
        /*- 从数据结构体得到变量值   */
        value = b2v_var_get(pdst_var, table[i].size);
        /*- 转换变量到bit数据流 */
        b2v_bytes_set(pstream, offset, value, table[i].width, table[i].endian);
        /*- 下一个变量转换偏移量 */
        offset = offset + table[i].width;
    }

    return offset;
}

/**
 * @brief b2v_var_to_bytes 将关键数据转换为字节数，默认偏移量为0
 *
 * @param psrc 目标数组
 * @param pstream 数据结构体
 * @param table 数据解析表
 * @param var_num 条目数量,范围：[1,255]
 *
 * @return 转换是否成功
 *  -  -E_INVALID_RANGE 转换失败
 *  -  执行结束后最新的bit偏移量
 */
int16_t b2v_var_to_bytes(quint8 *psrc, quint8 * pstream, const var_item_t * table, quint8 var_num)
{
    return b2v_var_to_bytes_byoffset(psrc, pstream, 0, table, var_num);
}



