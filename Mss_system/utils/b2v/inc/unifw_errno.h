#ifndef  _UNIFW_ERRNO_H
#define  _UNIFW_ERRNO_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @file unifw_errno.h
 * @brief define error no
 * @author 003
 * @version 
 * @date 2016-05-25
 */

/* define global err value*/
#define E_OK 			0	/**<  �޴��� */
#define E_ZERO_DIVIDER  1	/**<  ������� */
#define E_OVER_FLOW 	2	/**<  ������� */
#define E_INVALID_RANGE 3	/**<  ������ */
#define E_MIN 			4	/**<  ��Сֵ */
#define E_MAX 			5	/**<  ���ֵ */
#define E_NULL_PT 		6	/**<  ����ָ�� */
#define E_NOT_FOUND 	7	/**<  �޷��ҵ� */
#define E_NOT_END 		8	/**<  δ��β�� */
#define E_TYPE_FAULT	9	/**<  ���ʹ��� */
#define E_FULL	        10	/**<  ������ */
#define E_NOT_FULL	    11	/**<  ����δ�� */
#define E_CRC           12  /**<  CRCֵ���� */
#define E_LOST_CONFIG   13  /**<  ��ʧ���� */
#define E_INVALID_ADDR  14  /**<  ��ַ���� */
#define E_EMPTY         15  /**<  ����Ϊ�� */
#define E_RESERVED      18  /**<  ����Ϊ�� */
#define E_BUSY          20  /**<  �豸��æ */

#ifdef __cplusplus
}
#endif

#endif   /*_UNIFW_ERRNO_H*/

