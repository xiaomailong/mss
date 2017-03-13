#ifndef  _VOBC_CI_PARSE_H
#define  _VOBC_CI_PARSE_H

#ifdef __cplusplus
extern "C"{
#endif

/*VOBC����CI�����ݽṹ�� */
typedef struct _vobc_ci_data_t
{
	uint16_t	vobc_ci_interface;		/*VOBC-CI�ӿ� */
	uint32_t	send_id_msg;			/*���ͷ���ʶ��Ϣ */
	uint32_t	incept_id_msg;			/*���շ���ʶ��Ϣ */
	uint8_t		edition_control_msg;	/*�汾������Ϣ,�汾�� */
	uint32_t	edition_check_msg;		/*�汾У����Ϣ */
	uint32_t	msg_list;				/*��Ϣ���к� */
	uint8_t		com_cycle;				/*�豸ͨѶ���ڣ���λ��50ms */
	uint32_t	opposite_msg_list;		/*�Է���Ϣ���к�:��¼�յ��Է���һ����Ϣ�еĶԷ���Ϣ���к� */
	uint32_t	smsg_self_list;			/*�յ���һ����Ϣʱ�������к� */
	uint8_t		pro_edition;			/*Э��汾�� */
	uint8_t		nc_data;				/*�������� */
	uint8_t		dir_train;				/*�г����з��� */
	uint8_t		s_trainstoparea;	    /*�г�ͣ��ͣ׼״̬ */
	uint8_t		n_psd_type;				/*�г��������� */
	uint8_t		n_psd;					/*��Ҫ���Ƶ�PSD������ */
	uint16_t	nid_psd_1;				/*PSD_1��ID */
	uint8_t		nc_psd_1;				/*PSD_1�Ŀ������� */
	uint16_t	nid_psd_2;				/*PSD_2��ID */
	uint8_t		nc_psd_2;				/*PSD_2�Ŀ������� */
}vobc_ci_data_t;

///*CI����VOBC�����ݽṹ�� */
//typedef struct _ci_vobc_data_t
//{
//	uint16_t	vobc_ci_interface;		/*VOBC-CI�ӿ� */
//	uint32_t	send_id_msg;			/*���ͷ���ʶ��Ϣ */
//	uint32_t	incept_id_msg;			/*���շ���ʶ��Ϣ */
//	uint8_t		edition_control_msg;	/*�汾������Ϣ,�汾�� */
//	uint32_t	edition_check_msg;		/*�汾У����Ϣ */
//	uint32_t	msg_list;				/*��Ϣ���к� */
//	uint8_t		com_cycle;				/*�豸ͨѶ���ڣ���λ��50ms */
//	uint32_t	opposite_msg_list;		/*�Է���Ϣ���к�:��¼�յ��Է���һ����Ϣ�еĶԷ���Ϣ���к� */
//	uint32_t	smsg_self_list;			/*�յ���һ����Ϣʱ�������к� */
//	uint8_t		pro_edition;			/*Э��汾�� */
//	uint8_t		nc_data;				/*�������� */
//	uint8_t		dir_train;				/*�г����з��� */
//	uint8_t		n_psd;					/*�ظ�״̬��PSD������ */
//	uint16_t	nid_psd_1;				/*PSD_1��ID */
//	uint8_t		nc_psd_1;				/*PSD_1��״̬ */
//	uint8_t		r_nc_psd_1;				/*PSD_1�Ŀ������� */
//	uint16_t	nid_psd_2;				/*PSD_2��ID */
//	uint8_t		q_psd_2;				/*PSD_2��״̬ */
//	uint8_t		r_nc_psd_2;				/*PSD_2�Ŀ������� */
//	uint8_t		q_signal_aspect;		/*��վ�źŻ���״̬ */
//}ci_vobc_data_t;



#ifdef __cplusplus
}
#endif
#endif
