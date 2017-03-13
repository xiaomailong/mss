#ifndef  _VOBC_ATS_PARSE_H
#define  _VOBC_ATS_PARSE_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 *@file  vobc_ats_parse.h
 *@brief  
 *@author 
 *@data  2017-01-04 09:41
 *
 * $Id$
 */

/** VOBC����ATSͨ����Ϣ��ͷ*/
typedef struct _vobc_ats_header_t
{
	uint16_t vobc_ats_interface;	/*VOBC-ATS�ӿ� */
	uint32_t send_id_msg;			/*���ͷ���ʶ��Ϣ */
	uint32_t incept_id_msg;			/*���շ���ʶ��Ϣ */
	uint8_t  edition_control_msg;	/*�汾������Ϣ,�汾�� */
	uint32_t edition_check_msg;		/*�汾У����Ϣ */
	uint32_t msg_list;				/*��Ϣ���к� */
	uint8_t  com_cycle;				/*�豸ͨѶ���ڣ���λ��50ms */
	uint32_t opposite_msg_list;		/*�Է���Ϣ���к�:��¼�յ��Է���һ����Ϣ�еĶԷ���Ϣ���к� */
	uint32_t smsg_self_list;		/*�յ���һ����Ϣʱ�������к� */
	uint8_t  pro_edition;			/*Э��汾�� */
}vobc_ats_header_t;

/** VOBC���͸�ATS��ATO״̬��Ϣ֡*/
typedef struct _vobc_ats_ato_t
{
	uint16_t msg_type;				/*��Ϣ����*/
	uint16_t service_id;			/*�����*/
	uint16_t line_id;				/*��·���*/
	uint16_t cargroup_line_id;	    /*�����������·��*/
	uint16_t cargroup_id;			/*�����*/
	uint16_t sourceline_id;			/*Դ��·��*/
	uint16_t trainnum_id;			/*���κ�*/
	uint16_t destination_track_id;	/*Ŀ�ĵ���·���*/
	uint32_t destination_id;		/*Ŀ�ĵغ�*/
	uint16_t driver_id;				/*˾����*/
	uint8_t  mode_ato;				/*ATO����ģʽ*/
	uint16_t nc_interval_operation;	/*�������е�������*/
	uint8_t  status_skipstop;		/*��ͣ״̬*/
	uint8_t  status_detain;			/*�۳�״̬*/
	uint16_t nextstation_id;		/*��һͣ��վ̨ID*/
	uint32_t reserved_field;		/*Ԥ���ֶ�*/
}vobc_ats_ato_t;

/** VOBC���͸�ATS���г���Ϣ֡*/
typedef struct _vobc_ats_trainmsg_t
{
	uint16_t msg_type;				/*��Ϣ����*/
	uint16_t train_id;				/*�г�ʶ���VID*/
	uint16_t line_id;				/*��·���*/
	uint8_t  status_train_pos;   	/*�г���λ״̬*/
	uint8_t  dir_train; 			/*���з���*/
	uint8_t  dir_whell;     	 	/*����ת��*/
	uint16_t head_estimate_logic_id;/*��ͷ����λ�������߼�����ID*/
	uint32_t head_estimate_offset;	/*��ͷ����λ�����߼�������ƫ����*/
	uint16_t tail_estimate_logic_id;/*��β����λ�������߼�����ID*/
	uint32_t tail_estimate_offset;	/*��β����λ�����߼�������ƫ����*/
	uint16_t over_read;				/*����������*/
	uint16_t lack_read;				/*Ƿ��������*/
	uint8_t  mode_atp;				/*����ATP��ǰģʽ*/
	uint8_t  mode_cbtc;				/*���ع���ģʽ*/
	uint8_t  status_train_complete;	/*�г�������*/
	uint8_t  status_emerg_brake;	/*�г������ƶ�״̬*/
	uint8_t  status_ar;				/*�г�AR״̬*/
	uint16_t vel_msg;				/*�г��ٶ���Ϣ*/
	uint8_t  status_psd;			/*����״̬*/
	uint8_t  status_trainstoparea;	/*�г�ͣ��״̬*/
	uint8_t  status_stoptrain;		/*ͣ����֤״̬*/
	uint8_t  status_unmanned_reentry;/*�����۷�״̬*/
	uint8_t  mode_preselect;		/*Ԥѡģʽ*/
	uint8_t  reasonof_emerg_brake;	/*�����ƶ�ԭ��*/
	uint16_t vel_emerg_brake;		/*��ǰ�����ƶ������ٶ�*/
	uint16_t vel_recommend;			/*��ǰ�Ƽ��ٶ�*/
	uint32_t pos_security;			/*��ȫ������λ��*/
	uint16_t sec_track_id;			/*�������ID*/
	uint32_t sec_track_offset;		/*������ƫ����*/
	uint32_t pos_obstacle;			/*�ϰ���λ��*/
	uint16_t obs_track_id;			/*�������ID*/
	uint32_t obs_track_offset;		/*������ƫ����*/
	uint32_t reserved_field;		/*Ԥ���ֶ�*/
}vobc_ats_trainmsg_t;

/** VOBC���͸�ATS�ĳ����豸������Ϣ֡(����)*/
//typedef struct _vobc_ats_alarmmsg_t
//{
//	
//}vobc_ats_alarmmsg_t;



#ifdef __cplusplus
}
#endif
#endif
