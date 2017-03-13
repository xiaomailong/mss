#ifndef  _VOBC_CI_PARSE_H
#define  _VOBC_CI_PARSE_H

#ifdef __cplusplus
extern "C"{
#endif

/*VOBC发给CI的数据结构体 */
typedef struct _vobc_ci_data_t
{
	uint16_t	vobc_ci_interface;		/*VOBC-CI接口 */
	uint32_t	send_id_msg;			/*发送方标识信息 */
	uint32_t	incept_id_msg;			/*接收方标识信息 */
	uint8_t		edition_control_msg;	/*版本控制信息,版本号 */
	uint32_t	edition_check_msg;		/*版本校验信息 */
	uint32_t	msg_list;				/*消息序列号 */
	uint8_t		com_cycle;				/*设备通讯周期，单位：50ms */
	uint32_t	opposite_msg_list;		/*对方消息序列号:记录收到对方上一条消息中的对方消息序列号 */
	uint32_t	smsg_self_list;			/*收到上一条消息时本方序列号 */
	uint8_t		pro_edition;			/*协议版本号 */
	uint8_t		nc_data;				/*报文类型 */
	uint8_t		dir_train;				/*列车运行方向 */
	uint8_t		s_trainstoparea;	    /*列车停稳停准状态 */
	uint8_t		n_psd_type;				/*列车编组类型 */
	uint8_t		n_psd;					/*需要控制的PSD的数量 */
	uint16_t	nid_psd_1;				/*PSD_1的ID */
	uint8_t		nc_psd_1;				/*PSD_1的控制命令 */
	uint16_t	nid_psd_2;				/*PSD_2的ID */
	uint8_t		nc_psd_2;				/*PSD_2的控制命令 */
}vobc_ci_data_t;

///*CI发给VOBC的数据结构体 */
//typedef struct _ci_vobc_data_t
//{
//	uint16_t	vobc_ci_interface;		/*VOBC-CI接口 */
//	uint32_t	send_id_msg;			/*发送方标识信息 */
//	uint32_t	incept_id_msg;			/*接收方标识信息 */
//	uint8_t		edition_control_msg;	/*版本控制信息,版本号 */
//	uint32_t	edition_check_msg;		/*版本校验信息 */
//	uint32_t	msg_list;				/*消息序列号 */
//	uint8_t		com_cycle;				/*设备通讯周期，单位：50ms */
//	uint32_t	opposite_msg_list;		/*对方消息序列号:记录收到对方上一条消息中的对方消息序列号 */
//	uint32_t	smsg_self_list;			/*收到上一条消息时本方序列号 */
//	uint8_t		pro_edition;			/*协议版本号 */
//	uint8_t		nc_data;				/*报文类型 */
//	uint8_t		dir_train;				/*列车运行方向 */
//	uint8_t		n_psd;					/*回复状态的PSD的数量 */
//	uint16_t	nid_psd_1;				/*PSD_1的ID */
//	uint8_t		nc_psd_1;				/*PSD_1的状态 */
//	uint8_t		r_nc_psd_1;				/*PSD_1的控制命令 */
//	uint16_t	nid_psd_2;				/*PSD_2的ID */
//	uint8_t		q_psd_2;				/*PSD_2的状态 */
//	uint8_t		r_nc_psd_2;				/*PSD_2的控制命令 */
//	uint8_t		q_signal_aspect;		/*出站信号机的状态 */
//}ci_vobc_data_t;



#ifdef __cplusplus
}
#endif
#endif
