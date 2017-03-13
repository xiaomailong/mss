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

/** VOBC发给ATS通用信息包头*/
typedef struct _vobc_ats_header_t
{
	uint16_t vobc_ats_interface;	/*VOBC-ATS接口 */
	uint32_t send_id_msg;			/*发送方标识信息 */
	uint32_t incept_id_msg;			/*接收方标识信息 */
	uint8_t  edition_control_msg;	/*版本控制信息,版本号 */
	uint32_t edition_check_msg;		/*版本校验信息 */
	uint32_t msg_list;				/*消息序列号 */
	uint8_t  com_cycle;				/*设备通讯周期，单位：50ms */
	uint32_t opposite_msg_list;		/*对方消息序列号:记录收到对方上一条消息中的对方消息序列号 */
	uint32_t smsg_self_list;		/*收到上一条消息时本方序列号 */
	uint8_t  pro_edition;			/*协议版本号 */
}vobc_ats_header_t;

/** VOBC发送给ATS的ATO状态信息帧*/
typedef struct _vobc_ats_ato_t
{
	uint16_t msg_type;				/*消息类型*/
	uint16_t service_id;			/*服务号*/
	uint16_t line_id;				/*线路编号*/
	uint16_t cargroup_line_id;	    /*车组号所属线路号*/
	uint16_t cargroup_id;			/*车组号*/
	uint16_t sourceline_id;			/*源线路号*/
	uint16_t trainnum_id;			/*车次号*/
	uint16_t destination_track_id;	/*目的地线路编号*/
	uint32_t destination_id;		/*目的地号*/
	uint16_t driver_id;				/*司机号*/
	uint8_t  mode_ato;				/*ATO工作模式*/
	uint16_t nc_interval_operation;	/*区间运行调整命令*/
	uint8_t  status_skipstop;		/*跳停状态*/
	uint8_t  status_detain;			/*扣车状态*/
	uint16_t nextstation_id;		/*下一停车站台ID*/
	uint32_t reserved_field;		/*预留字段*/
}vobc_ats_ato_t;

/** VOBC发送给ATS的列车信息帧*/
typedef struct _vobc_ats_trainmsg_t
{
	uint16_t msg_type;				/*消息类型*/
	uint16_t train_id;				/*列车识别号VID*/
	uint16_t line_id;				/*线路编号*/
	uint8_t  status_train_pos;   	/*列车定位状态*/
	uint8_t  dir_train; 			/*运行方向*/
	uint8_t  dir_whell;     	 	/*车轮转向*/
	uint16_t head_estimate_logic_id;/*车头估计位置所在逻辑区段ID*/
	uint32_t head_estimate_offset;	/*车头估计位置在逻辑区段内偏移量*/
	uint16_t tail_estimate_logic_id;/*车尾估计位置所在逻辑区段ID*/
	uint32_t tail_estimate_offset;	/*车尾估计位置在逻辑区段内偏移量*/
	uint16_t over_read;				/*过读测距误差*/
	uint16_t lack_read;				/*欠读测距误差*/
	uint8_t  mode_atp;				/*车载ATP当前模式*/
	uint8_t  mode_cbtc;				/*车载工作模式*/
	uint8_t  status_train_complete;	/*列车完整性*/
	uint8_t  status_emerg_brake;	/*列车紧急制动状态*/
	uint8_t  status_ar;				/*列车AR状态*/
	uint16_t vel_msg;				/*列车速度信息*/
	uint8_t  status_psd;			/*车门状态*/
	uint8_t  status_trainstoparea;	/*列车停稳状态*/
	uint8_t  status_stoptrain;		/*停车保证状态*/
	uint8_t  status_unmanned_reentry;/*无人折返状态*/
	uint8_t  mode_preselect;		/*预选模式*/
	uint8_t  reasonof_emerg_brake;	/*紧急制动原因*/
	uint16_t vel_emerg_brake;		/*当前紧急制动触发速度*/
	uint16_t vel_recommend;			/*当前推荐速度*/
	uint32_t pos_security;			/*安全防护点位置*/
	uint16_t sec_track_id;			/*轨道区段ID*/
	uint32_t sec_track_offset;		/*区段内偏移量*/
	uint32_t pos_obstacle;			/*障碍点位置*/
	uint16_t obs_track_id;			/*轨道区段ID*/
	uint32_t obs_track_offset;		/*区段内偏移量*/
	uint32_t reserved_field;		/*预留字段*/
}vobc_ats_trainmsg_t;

/** VOBC发送给ATS的车载设备报警信息帧(待定)*/
//typedef struct _vobc_ats_alarmmsg_t
//{
//	
//}vobc_ats_alarmmsg_t;



#ifdef __cplusplus
}
#endif
#endif
