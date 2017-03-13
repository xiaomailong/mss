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
/*����s������xѭ������nλ */
#define ROTATE_LEFT(x, s, n) (((x)<<(n)) | ((x)>>((-n) & (s-1))))
/*����s������xѭ������nλ */
#define ROTATE_RIGHT(x, s, n) (((x)>>(n)) |((x)<<((-n) & (s-1)))

/*
 * @brief  LFSR�����㷨
 * @detail ����LFSR���ԣ�����32λ��ÿ�����λΪ1ʱ�����ʽ���
 * @param  x    ������1
 * @param  y    ������2
 * @param  mask �����������ʽ
 * @return ���ֵ
 */
uint32_t LFSR_Add(uint32_t x, uint32_t y, uint32_t mask);

/*
 * @brief  LFSR�����㷨
 * @detail ����LFSR���ԣ�����32λ�������ʽ���
 * @param  x    ������1
 * @param  y    ������2
 * @param  mask �����������ʽ
 * @return ���ֵ
 */
uint32_t LFST_Post(uint32_t x, uint32_t y, uint32_t mask);

/*
 * @brief  �������к�
 * @detail �Ƚ��յ���RSD���кź����һ����Ч�����кţ�������ֵ�������������в�Ƚ�
 * @param  last_counter ���һ�δ洢�����к�
 * @param  rcv_counter  �յ���RSD�����е����к�
 * @param  max_loss     �������̲�ֵ
 * @return ���кŴ���򳬹��������̲�ֵ����0�����򷵻����кŲ�ֵ
 */
uint8_t compareCounters(uint32_t last_counter, uint32_t rcv_counter, uint8_t max_loss);

/*
 * @brief  CRC32������
 * @detail �������ɼ���SVC�����CRC32�Ľӿڣ��ں����е�����صĺ������㲢���ʵ��
 * @param  data ��Ҫ�����������ָ��
 * @return ����CRC32��
 */
uint32_t CRC32_calculator(uint32_t *data);

/*
 * @brief  ʱ������
 * @detail ʱ����ز�������
 * @param  ʱ����ز������ݽṹ��ָ��
 * @return ������Ч����0�������ɹ�����1
 */
uint16_t forwardTimer(local_time_param_t *timer);

void set_tick_timer(local_time_param_t *local, uint32_t now);

void reset_tick_timer(local_time_param_t *local);

void stop_tick_timer(local_time_param_t *local, uint32_t now);
/*
 * @brief  ʱ��У������ͨ��������
 * @detail ������ʱ��У��ʱ����ʱ��У��������
 * @param  sid  SIDԴ��ʶ
 * @param  ts_e ����ʱ���
 * @return ʱ��У������ͨ��
 */
uint32_t SEQENQ_calculator(uint32_t sid, uint32_t ts_e);

/**
 * @brief  ʱ���ʼ��ͨ��������
 * @detail ����ʱ���ʼ��ͨ����������SVC�����м���ʱ��У������
 * @param  senq     ʱ��У������ͨ��
 * @param  sid      SIDԴ��ʶ
 * @param  ts_r     Ӧ��ʱ���
 * @param  dataver  ���ݰ汾
 * @return ʱ���ʼ��ͨ��
 */
uint32_t SEQINIT_calculator(uint32_t senq, uint32_t sid, uint32_t ts_r, uint32_t dataver);

/*
 * @brief  SVC������
 * @detail ����SVC��ȫͨ��
 * @param  crc  CRC32
 * @param  scw  SCWϵͳ������
 * @param  sid  SIDԴ��ʶ
 * @param  ts   ʱ���
 */
uint32_t SVC_calculator(uint32_t crc, uint32_t scw, uint32_t sid, uint32_t ts);

/*
 * @brief  ���㱾�����һ�δ洢��ʱ����Чֵ
 * @detail ����SVCУ���㷨���̺͸��±������ʱ����Чֵ
 * @param  sinit    ʱ���ʼ��ͨ��
 * @param  sid      SIDԴ��ʶ
 * @param  ts       ʱ���
 * @param  gaps     �����кź������Ч���кŵļ����gaps=0��û�м��������ʱ����Чֵ
 * @return ����ʱ����Чֵ�������
 */
uint32_t last_calculator(uint32_t sinit, uint32_t sid, uint32_t ts, uint32_t gaps);

#ifdef __cplusplus
}
#endif

#endif //_RSSP_I_UNIBASE_
