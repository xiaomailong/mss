/**
 * @file main_pub.h
 * @brief header file for zc data parser
 * @author xue.chuance@163.com
 * @version 
 * @date 2016-12-15
  */


#ifndef  _MAIN_PUB_H
#define  _MAIN_PUB_H

#ifdef __cplusplus
extern "C"{
#endif

/*- 单字节对齐 */
#pragma pack (1)


#include "unifw.h"

/*******************************************************************************
 * 宏定义:接口信息类型
 ******************************************************************************/
#define INTERFACE_ZC_CI				0x9002U		/**< zc和ci之间的通信编号 */
#define INTERFACE_ZC_ATS			0x9004U		/**< zc和ATS之间的通信编号 */
#define INTERFACE_ZC_VOBC			0x9006U		/**< zc和VOBC之间的通信编号 */
#define INTERFACE_ZC_ZC				0x9008U		/**< zc和ZC之间的通信编号,这个为自定义? */

/*******************************************************************************
 * 宏定义:模块编号
 ******************************************************************************/
#define  MODULE_ZC					0X02U		/**< ZC模块在数据报文中的编码代号 */
#define  MODULE_CI					0X04U		/**< CI模块在数据报文中的编码代号 */
#define  MODULE_VOBC				0X01U		/**< VOBC模块在数据报文中的编码代号 */
#define  MODULE_ATS					0X03U		/**< ATS模块在数据报文中的编码代号 */


/*******************************************************************************
 * 宏定义:ci和zc的应用层信息类型
 ******************************************************************************/
#define  LOGIC_ZONE_STATUS			0X0202U		/**< 逻辑区段状态信息,ZC->CI,周期发送 */
#define  SIGNAL_NEAR_INFO			0X0204U 	/**< 信号机接近信息,ZC->CI，周期发送 */
#define  PROTECT_ZONE_LOCK_ASK		0X020AU 	/**< 保护区段锁闭请求,ZC->CI，周期发送 */
#define  ROUTE_INFO					0X0201U 	/**< 进路信息,CI->ZC，周期发送 */
#define  PSD_STATUS_INFO			0X0203U 	/**< PSD状态信息,CI->ZC，周期发送 */
#define  ESB_STATUS_INFO			0X0205U 	/**< ESB状态信息,CI->ZC，周期发送 */
#define  AUTO_BACK_BUTTON_STATUS	0X0207U 	/**< 无人折返按钮状态信息,CI->ZC，周期发送 */
#define  PHY_ZONE_OCCUPY_INFO		0X0209U 	/**< 物理区段占用信息,CI->ZC，周期发送 */
#define  ROUTE_UNLOCK_ASK			0X020bU 	/**< 进路解锁请求,CI->ZC，周期发送 */

/*******************************************************************************
 * 宏定义:vobc和zc的应用层信息类型
 ******************************************************************************/
#define  ZC_CONTROLTRAIN			0X0201U		/**< 列车控制信息,ZC->VOBC,周期发送 */
#define  TRAIN_LOCATION_INFO		0X0202U		/**< 列车位置信息,VOBC->ZC,周期发送 */
#define  ZC_RESPOND_RSQ				0X0205U		/**< 应用层注册/注销响应,zc->vobc,非周期发送 */
#define  TRAIN_RSQ					0X0206U		/**< 应用层注册/注销请求,vobc->zc,非周期发送 */
#define  ZC_UNREGISTER_RSQ			0X0207U		/**< 应用层注销请求,zc->vobc,非周期发送 */
#define  ZC_SPECIAL_MSG				0x0209U		/**< 特殊报文,zc->vobc,非周期发送 */

/*******************************************************************************
 * 宏定义:ats 和 zc 的应用层信息类型
 ******************************************************************************/
#define  ATS_TICK_FRAME				0X0201U		/**< ATS时钟信息帧,ATS->ZC,周期发送 */
#define  TSR_VERIFY_FRAME			0X0203U		/**< TSR验证命令帧,ATS->ZC,非周期发送 */
#define  TSR_EXEUTE_FRAME			0X0205U		/**< TSR执行命令帧,ATS->ZC,非周期发送 */
#define  POWER_ON_FRAME				0X0207U		/**< 上电TSR确认帧,ATS->ZC,非周期发送 */
#define  ZC_TSR_VERIFY_FRAME		0X0202U		/**< TSR验证命令确认帧	,ZC->ATS,非周期发送 */
#define  ZC_TSR_EXEUTE_FRAME		0X0204U		/**< TSR执行命令确认帧	,ZC->ATS,非周期发送 */
#define  ZC_STATUS_INFO_FRAME		0X0206U		/**< TSR状态信息帧,ZC->ATS,周期发送 */


/*******************************************************************************
 * 宏定义:其他
 ******************************************************************************/
#define DATA_RESERVE		0xFFU				/**< 数据报文中默认充填0xff */
#define MAP_CRC_POLY 		0X04C11DB7U  		/**< 电子地图版本校验CRC生成多项式 */
#define MAP_CRC_RSV			0XFFFFFFFFU  		/**< CRC寄存器初始值 */
#define COMMU_PERIOD		50U					/**< 设备通信周期,单位ms */


/*- 定义数据解析过程中的错误枚举变量 */
enum ZC_Parser_Err{
    ZC_CI_DATA_LEN_ERR 		= -2, 				/**< CI传输给ZC的数据长度有误  */ 
    ZC_CI_DATA_TYPE_ERR 	= -3,				/**< CI传输给ZC的数据类型未定义 */ 

    ZC_VOBC_DATA_LEN_ERR 	= -12, 				/**< CI传输给VOBC的数据长度有误  */ 
    ZC_VOBC_DATA_TYPE_ERR 	= -13,				/**< CI传输给VOBC的数据类型未定义 */ 

    ZC_DATA_OUT_NUL_ERR 	= -13,				/**< ZC数据解析后，存储输出数据指针为空，主要是单元测试用到  */ 
};

/*- 定义zc提供给ci的逻辑区段状态信息 */
enum ZC_LOGIC_TRACK_STATUS{
    Z_L_TRACK_DEFAULT		= 0U,	/**< 未配置 */ 
    Z_L_NORMAL_CLEAN		= 0X01,	/**< 计轴正常情况下的计轴空闲 */ 
    Z_L_NORMAL_AT			= 0X02,	/**< 计轴正常情况下的AT占用 */ 
    Z_L_NORMAL_UT			= 0X03,	/**< 计轴正常情况下的UT占用 */ 

    Z_L_FAULT_CLEAN			= 0X09,	/**< 计轴故障情况下的计轴空闲 */ 
    Z_L_FAULT_AT			= 0X0a,	/**< 计轴故障情况下的AT占用 */ 
    Z_L_FAULT_UT			= 0X0b,	/**< 计轴故障情况下的UT占用 */ 

};



/*- 定义ci提供给zc的进路状态枚举变量 */
enum ZC_route_status{
    C_ROUTE_OPEN			= 0x01U,			/**< 进路开放 */ 
    C_ROUTE_NOT_OPEN		= 0x02U,			/**< 进路未开放 */
    C_ROUTE_RSQ_CANCEL		= 0x80U,			/**< 进路请求取消 */  

};


/*- 定义ci提供给zc的道岔状态枚举变量 */
enum ZC_switch_status{
    C_SWITCH_NORMAL		= 0x01U,				/**< 道岔正位 */
    C_SWITCH_ANTI		= 0x02U,				/**< 道岔反位 */
    C_SWITCH_TROUBLE	= 0x03U,				/**< 道岔故障 */

};

/*- 定义ci提供给zc的区段锁闭状态枚举变量 */
enum ZC_track_status{
    C_TRACK_LOCK		= 0x01U,				/**< 区段锁闭 */ 
    C_TRACK_UNLOCK		= 0x02U,				/**< 区段未锁闭 */
    C_TRACK_INVALID		= 0x03U,				/**< 无效 */
};

/*- 定义ci提供给zc的保护区段锁闭状态枚举变量 */
enum ZC_protect_track_status{
    C_PROTECT_T_LOCK	= 0x55U,				/**< 保护区段锁闭 */
    C_PROTECT_T_UNLOCK	= 0xAAU,				/**< 保护区段未锁闭或保护区段道岔故障 */

};

/*- 定义ci提供给zc的站台门状态枚举变量 */
enum ZC_PSD_status{
    C_PSD_B_NOMAL		= 0x01U,				/**< 站台门的旁路状态为：未旁路 */	
    C_PSD_B_BYPASS		= 0x02U,				/**< 站台门的旁路状态为：旁路 */
    C_PSD_B_ILLEGAL		= 0x00U,				/**< 站台门的旁路状态为：非法值 */
    C_PSD_B_DEFAULT		= 0x03U,				/**< 站台门的旁路状态为：默认值 */

    C_PSD_S_OPEN		= 0x01U,				/**< 站台门的开关状态为：开门 */
    C_PSD_S_CLOSE		= 0x02U,				/**< 站台门的开关状态为：关门 */
    C_PSD_S_ILLEGAL		= 0x00U,				/**< 站台门的开关状态为：非法值 */
    C_PSD_S_DEFAULT		= 0x03U,				/**< 站台门的开关状态为：默认值 */

};

/*- 定义ci提供给zc的站台门紧急关闭按钮枚举变量 */
enum ZC_ESB_status{
    C_ESB_PRESSED		= 0x01U,				/**< ESB按钮状态为：按下 */	
    C_ESB_UNPRESSED		= 0x02U,				/**< ESB按钮状态为：未按下 */
    C_ESB_ILLEGAL		= 0x00U,				/**< ESB按钮状态为：非法 */
    C_ESB_DEFAULT		= 0x03U,				/**< ESB按钮状态为：默认值 */

};

/*- 定义ci提供给zc的无人折返按钮枚举变量 */
enum ZC_autoBack_b_status{
    C_AUTOBACK_B_PRESSED		= 0x01U,		/**< 自动折返按钮状态为：按下 */	
    C_AUTOBACK_B_UNPRESSED		= 0x02U,		/**< 自动折返按钮状态为：未按下 */
    C_AUTOBACK_B_ILLEGAL		= 0x00U,		/**< 自动折返按钮状态为：非法 */
    C_AUTOBACK_B_DEFAULT		= 0x03U,		/**< 自动折返按钮状态为：默认值 */

};

/*- 定义ci提供给zc的计轴区段状态枚举变量 */
enum ZC_di_track_status{
    C_DI_TRACK_L_LOCK			= 0x01U,		/**< 计轴区段锁闭状态为：锁闭 */	
    C_DI_TRACK_L_UNLOCK			= 0x02U,		/**< 计轴区段锁闭状态为：未锁闭 */
    C_DI_TRACK_L_ILLEGAL		= 0x00U,		/**< 计轴区段锁闭状态为：非法值 */
    C_DI_TRACK_L_DEFAULT		= 0x03U,		/**< 计轴区段锁闭状态为：默认值 */

    C_DI_TRACK_O_OCCUPY			= 0x01U,		/**< 计轴区段占用状态为：占用 */	
    C_DI_TRACK_O_UNOCCUPY		= 0x02U,		/**< 计轴区段占用状态为：未占用 */
    C_DI_TRACK_O_ILLEGAL		= 0x00U,		/**< 计轴区段占用状态为：非法值 */
    C_DI_TRACK_O_DEFAULT		= 0x03U,		/**< 计轴区段占用状态为：默认值 */

};

/**
 *  接收到的报文包头信息结构体
  */
typedef struct  _stream_header{ 
/* 1  */uint16_t  interface_type  ; 			/**< 接口信息类型 */
/* 2  */uint32_t  sender_id ;	   				/**< 发送方标识ID */
/* 3  */uint32_t  receiver_id ;	    			/**< 接收方标识ID */
/* 4  */uint8_t   map_version ;	    			/**< 电子地图版本,不使用时默认值为0xff */
/* 5  */uint32_t  map_version_crc32 ;	    	/**< 电子地图版本crc32循环冗余校验 */
/* 6  */uint32_t  send_num ;		    		/**< 消息序列号*/
/* 7  */uint8_t   com_period ;	    			/**< 设备通讯周期，单位50ms */
/* 8  */uint32_t  opposite_num ;	    		/**< 记录收到对方上一条消息中的对方消息序列号 */
/* 9  */uint32_t  rcv_num ;	    				/**< 记录收到对方上一条消息时，本方的周期计数 */
/* 10  */uint8_t   protocol_version ;	    	/**< ZC-CI的协议版本号 */
}stream_head_info_t;


/************************************************************************
*ZC-CI通信协议
************************************************************************/

/**
 *@brief ci信息头
 */
typedef struct _ci_header_info{
/* 1  */uint16_t    c_msg_len;		/**< 报文长度,报文类型-报文结束 */
/* 2  */uint16_t    c_msg_type;		/**< zc-ci通信的信息报文头类型 */
/* 3  */uint16_t    c_msg_num;		/**< 对应信息类型数据的数目 */

}ci_header_info_t;

/**
 *@brief 逻辑区段状态信息(ZC->CI)
 */
typedef struct logic_track_info{
/* 1  */uint8_t    l_status;		/**<  逻辑区段状态信息 */
/*		uint8_t	 status[num*0.5]   逻辑区段1状态（B3-B0),逻辑区段2状态（B7-B4）
                                    无，未配置：0000b
                                    空闲（计轴正常）：0001b
                                    AT占用（计轴正常）：0010b
                                    UT占用（计轴正常）0011b
                                    空闲（计轴故障）：1001b
                                    AT占用（计轴故障）：1010b
                                    UT占用（计轴故障）1111b
*/
}logic_track_info_t;

/**
 *@brief 信号机接近信息(ZC->CI)
 */
typedef struct _signal_close_info{
/* 1 */uint8_t	 s_status;	/**< 信号机1AT接近信息(B7-B6) */
/*	uint8_t	 status[num]		否：01b；是：10b；无效：00b；非法值：11b
                                信号机1AT停车保证信息(B3-B2)
                                不能停下：01b；能停下：10b；无效：00b；非法：11b
                                信号机1UT接近信息(B5-B4)
                                否：01b；是：10b；无效：00b；非法值：11b
                                信号机1AT跨压信息（B1-B0）
                                未跨压：01b；有跨压：10b；其他无效 */
}signal_close_info_t;

/**
 *@brief 保护区段锁闭请求(ZC->CI)
 */
typedef struct protect_zone_lock_rsq{
/* 1  */uint16_t     p_seri;				/**<  需要锁闭保护区段的进路编号 */
}protect_zone_lock_rsq_t;

/**
 *@brief 进路信息(CI->ZC)
 */
typedef struct route_info{
/* 1  */uint16_t   	r_seri;					/**<  进路编号 */
/* 2  */uint8_t   	r_route_status;			/**<  进路状态:0x01:开放，
                                                0x02:未开放，
                                                0x80:请求取消 */
                                    
/* 3  */uint8_t   	r_signal_status;			/**<  信号机状态:0x81:亮红灯-停车，
                                                  0x82:亮黄灯-允许行车，道岔侧向，
                                                  0x84:亮绿灯-运行行车，道岔直向,
                                                  0x11:灭红灯，停车,
                                                  0x12:灭黄灯，运行行车，道岔侧向,
                                                  0x14:灭绿灯，允许行车，道岔直向, */
                                    
/* 4 */uint16_t   	r_switch_status;  		/**<  道岔状态:定位：01b；反位：10b；故障：11b
                                              道岔4状态（B7-B6）道岔3状态（B5-B4）道岔2状态（B3-B2）道岔1状态（B1-B0）
                                              道岔8状态（B15-B14）道岔7状态（B13-B12）道岔6状态（B11-B10）道岔5状态（B9-B8）*/
                                    
/* 5 */uint8_t      r_zone_lock_status_1; 	/**<  区段锁闭状态:锁闭：01b；未锁闭：10b；其他无效 
                                                区段4锁闭状态（B7-B6）区段3锁闭状态（B5-B4）区段2锁闭状态（B3-B2）区段1锁闭状态（B1-B0）
                                                第2至5个字节分别为区段5至区段20的锁闭状态. */
/* 6 */uint8_t      r_zone_lock_status_2; 
/* 7 */uint8_t      r_zone_lock_status_3; 
/* 8 */uint8_t      r_zone_lock_status_4; 
/* 9 */uint8_t      r_zone_lock_status_5; 

/* 10 */uint8_t 	r_protect_zone_lock_status; 	/**<  保护区段锁闭信息,0x55:进路路径有保护区段已锁闭
                                                        0xAA:全部保护区段未锁闭或保护区段内道岔故障 */
}route_info_t;


/**
 *@brief 站台门状态信息(CI->ZC)
 */
typedef struct psd_info{
        uint8_t p_status;
/**<	uint8_t	 status[num*0.5]   站台门1旁路状态（B3-B2）,站台门2旁路状态（B7-B6）,								   
                                   未旁路：01b,旁路：10b,非法值：00b,默认值：11b 

                                   站台门1开关状态（B1-B0）,站台门2开关状态（B5-B4）
                                   开门：01b,关门：10b,非法值：00b,默认值：11b */
}psd_info_t;


/**
 *@brief  站台紧急关闭按钮状态(CI->ZC)
 */
typedef struct esb_info{
        uint8_t e_status;
/**<	uint8_t	 status[num*0.25]   按下：01b,未按下：10b,非法状态：00b,默认值：11b
                                    紧急关闭按钮4状态（B7-B6）
                                    紧急关闭按钮3状态（B5-B4）
                                    紧急关闭按钮2状态（B3-B2）
                                    紧急关闭按钮1状态（B1-B0）*/
}esb_info_t;

/**
 *@brief  无人折返按钮状态信息 (CI->ZC)
 */
typedef struct auto_back_button_info{
        uint8_t a_button_status;
/**<		uint8_t	 status[num*0.25]   按下：01b,未按下：10b,非法状态：00b,默认值：11b
                                    无人折返按钮4状态（B7-B6）
                                    无人折返按钮3状态（B5-B4）
                                    无人折返按钮2状态（B3-B2）
                                    无人折返按钮1状态（B1-B0）*/
}auto_back_button_info_t;

/**
 *@brief  计轴区段状态信息 (CI->ZC)
 */
typedef struct di_zone_status_info{
        uint8_t d_zone_status;
/**<		uint8_t	 status[num*0.5]   计轴区段1锁闭状态（B3-B2）,计轴区段2锁闭状态（B7-B6）
                                    区段锁闭：01b,区段未锁闭：10b,非法状态：00b,默认值：11b 

                                   计轴区段1占用状态（B1-B0）,计轴区段2占用状态（B5-B4）
                                    区段占用：01b；区段空闲：10b；非法状态：00b；默认值：11b；*/
}di_zone_status_t;

/**
 *@brief 进路解锁请求(ZC->CI)
 */
typedef struct route_unlock_rsq{
/* 1  */uint16_t     r_seri;					/**<  进路编号 */
}route_unlock_rsq_t;



/************************************************************************
*ZC-VOBC通信协议
************************************************************************/

/**
 *@brief vobc的信息类型
 */
typedef struct vobc_header_info{
/* 1  */uint16_t     v_msg_len;				/**<  vobc发送过来的报文长度,报文类型-报文结束 */
/* 2  */uint16_t     v_msg_type;			/**<  vobc的报文类型 */
}vobc_header_info_t;

/**
 *@brief 列车位置信息 (VOBC->ZC)
 */
typedef struct onboard_location{
/* 1  */uint8_t     ob_direction;            /**<  运行方向 上行:0x55 ，下行:0xAA，其他非法 */
/* 2  */uint8_t     ob_active_point ;        /**<  激活端：0x55，非激活端0xAA，其他非法 */
/* 3  */uint16_t    ob_head_pos_tk_id;       /**<  车头所在轨道区段ID（车头估计位置，车头列车最大安全前端） */
/* 4  */uint32_t    tk_head_offset;          /**<  轨道区段内偏移量 单位：cm */
/* 5  */uint16_t    ob_tail_pos_tk_id;       /**<  车尾所在轨道区段ID（车尾估计位置，车尾最小安全末端） */
/* 6  */uint32_t    tk_tail_offset;          /**<  轨道区段内偏移量 单位：cm */
/* 7  */uint16_t    under_read_error;        /**<  欠读误差 单位：cm */
/* 8  */uint16_t    over_read_error;         /**<  过读误差 单位：cm */
/* 9  */uint16_t    ob_length;               /**<  列车长度 单位：cm */
/* 10 */uint16_t    ob_suspension_length;    /**<  第一轮对至车头长度 单位：cm*/
/* 11 */uint8_t     ob_work_mode;            /**<  车载工作模式 CBTC：0x01，点式：0x02，联锁控制级别：0x03，其他非法 */
/* 12 */uint8_t     ob_driver_mode;          /**<  车载驾驶模式 AM：0x01，CM：0x02，RM：0x03，其他非法 */
/* 13 */uint8_t     stop_response;           /**<  停车保证响应 可以停车：0x55，无法停车：0xAA，无效：0xFF，其他非法 */
/* 14 */uint16_t    stop_response_tk_id;     /**<  停车保证对应的安全防护点轨道区段ID，停车保证响应无效时：0xFFFF */
/* 15 */uint32_t    stop_response_tk_offset; /**<  停车保证对应的安全防护点轨道区段偏移量，停车保证响应无效时：0xFFFFFFFF */
/* 16 */uint16_t    stop_response_obstacles_tk_id;         /**<  停车保证对应的障碍点轨道区段ID，停车保证响应无效时：0xFFFF */
/* 17 */uint32_t    stop_response_obstacles_tk_offset;     /**<  停车保证对应的障碍点轨道区段偏移量，停车保证响应无效时：0xFFFFFFFF */
/* 18 */uint8_t     stop_response_overlap_valid;             
/* 19 */uint8_t     ar_status;               /**<  折返状态 AR状态：0x55，非AR状态：0xAA，其他非法 */
/* 20 */uint8_t     ob_integrity;            /**<  列车完整性 列车分离：0x55，列车完整：0xAA，其他非法 */
/* 21 */uint8_t     ar_led_status;           /**<  无人折返状态指示灯 折返指示灯常亮：0x55，折返指示灯常灭：0xAA，折返指示灯闪烁：0xCC，其他非法 */
/* 22 */uint8_t     esb_status;              /**<  紧急制动状态 有紧急制动输出：0x55，无紧急制动输出：0xAA，其他非法 */
/* 23 */uint16_t    ob_speed;                /**<  列车速度 0~65535，单位cm/s */
/* 24 */uint8_t     speed_dir;               /**<  速度方向 向前：0x55，向后：0xAA，其他非法 */
/* 25 */uint16_t    backing_out_dis;         /**<  退行距离 0~65535，单位cm */
/* 26 */uint8_t     stop_info;               /**<  停稳信息 停稳：0x55，未停稳：0xAA */
/* 27 */uint32_t    zc_id;                   /**<  受控ZC ID */
}onboard_location_t;

/**
 *@brief VOBC注册/注销请求 (VOBC->ZC)
 */
typedef struct onboard_request{
/* 1  */uint8_t     request_info;            /**<  注册/注销请求 注册请求:0x55 ，注销请求:0xCC，其他非法 */
/* 2  */uint8_t     unregister_reason ;      /**<  注销原因代码：0x**(根据业主要求定义) */
}onboard_request_t;

/**
 *@brief 道岔状态信息
 */
typedef struct switch_status{
/* 1  */uint16_t	switch_id; 				/**<  道岔id */
/* 2  */uint8_t		switch_statu;			/**<  道岔状态,定位：0x55,反位：0xAA,其他无效 */
}switch_status_t;

/**
 *@brief PSD状态信息
 */
typedef struct PSD_status{
/* 1  */uint16_t	psd_id; 				/**<  PSDid*/
/* 2  */uint8_t		psd_status;				/**<  PSD状态,非关闭且锁闭：0x55,关闭且锁闭：0xAA,互锁解除：0xCC,其他非法  */
}PSD_status_t;

/**
 *@brief ESB状态信息
 */
typedef struct ESB_status{
/* 1  */uint16_t	esb_id; 				/**<  ESB id*/
/* 2  */uint8_t		esb_status;				/**<  ESB状态,ESB按下：0x55,   ESB未按下：0xAA,其他非法  */
}ESB_status_t;

/**
 *@brief 临时限速信息
 */
typedef struct temp_speed_limit_info{
/* 1  */uint16_t	start_zone_id; 				/**<  始端位置轨道区段ID */
/* 2  */uint32_t	start_zone_offset;			/**<  始端位置区段内偏移量（单位：cm）  */
/* 3  */uint16_t	end_zone_id; 				/**<  终端位置轨道区段ID */
/* 4  */uint32_t	end_zone_offset;			/**<  终端位置区段内偏移量（单位：cm）  */
/* 5  */uint8_t		reserv;						/**<  预留 */	
/* 6  */uint8_t		speed_limit_value;			/**<  临时限速值 ,单位：km/h,（0km/h~254km/h） */	
}temp_speed_limit_info_t;



/* 定义MA范围内包含的最大道岔个数 为20  */
#define MA_SWITCH_NUM_MAX  20

/* 定义MA范围内包含的最大PSD个数，为10 */
#define MA_PSD_NUM_MAX  10

/* 定义MA范围内包含的最大ESB个数，为10 */
#define MA_ESB_NUM_MAX  10

/* 定义临时限速信息的最大个数，为10 */
#define MA_LIMIT_NUM_MAX  10

/**
 *@brief 列车控制信息(ZC->VOBC)
 */
typedef struct onboard_control_info{
/* 1  */ //uint16_t    msg_type;							/**<  报文类型 0x0201 */
/* 2  */uint32_t    next_zc_id; 						/**<   下一个ZC ID,默认值:0xFFFFFFFF, */
/* 3  */uint16_t    ma_info_len ; 						/**<  从“MA方向”位到“运行目的地属性”所有字节的长度 */
/* 4  */uint8_t     ma_dir ; 							/**<  在MA起点朝向MA终点的方向,上行：0x55，下行：0xAA,其他非法 */
/* 5  */uint8_t     stop_response;						/**<  停车保证请求,有：0x55，无：0xAA,其他非法 */ 		
/* 6  */uint16_t    stop_response_tk_id;				/**<  停车保证请求的安全防护点轨道区段ID,仅park_guard_rsq为0x55时有效 */
/* 7  */uint32_t    stop_response_tk_offset;			/**<  停车保证请求的安全防护点区段偏移量,仅park_guard_rsq为0x55时有效 */
/* 8  */uint16_t    stop_response_obstacles_tk_id;		/**<  停车保证请求的安全障碍点轨道区段ID,仅park_guard_rsq为0x55时有效 */
/* 9  */uint32_t    stop_response_obstacles_tk_offset;	/**<  停车保证请求的安全障碍点区段偏移量,仅park_guard_rsq为0x55时有效 */
/* 10 */uint8_t     stop_response_overlap;	    		/**<  停车保证对应的保护区段有效性 有效：0x55，无效：0xAA，默认：0xFF */
/* 11 */uint16_t    ma_start_zone_id;					/**<  MA起点轨道区段ID	 */
/* 12 */uint32_t    ma_start_zone_offset;				/**<  区段内偏移量（单位：cm） */
/* 13 */uint16_t    tk_id;								/**<  安全防护点逻辑区段ID	 */
/* 14 */uint32_t    tk_offset;							/**<  区段内偏移量（单位：cm） */
/* 15 */uint16_t    obstacles_tk_id;					/**<  障碍点轨道区段ID	 */
/* 16 */uint32_t    obstacles_tk_offset;				/**<  区段内偏移量（单位：cm） */
/* 17 */uint8_t     overlap_valid;						/**<  保护区段有效性,有效：0x55,无效：0xAA,默认值：0xFF */
/* 18 */uint16_t    switch_num;							/**<  MA范围内包含的道岔个数，最大值20 */
/* 19 */switch_status_t  switch_status[MA_SWITCH_NUM_MAX];		/**<  道岔相关信息 */
/* 23 */uint16_t    psd_num;							/**<  MA范围内包含的PSD个数，最大值10 */
/* 24 */PSD_status_t     psd_status[MA_PSD_NUM_MAX];			/**<  PSD相关信息 */
/* 28 */uint16_t    esb_num;							/**<  MA范围内包含的ESB个数，最大值10 */
/* 29 */ESB_status_t     esb_status[MA_ESB_NUM_MAX];			/**<  ESB相关信息 */
/* 33 */uint8_t     auto_back_button_status;			/**<  无人折返按钮状态,按下：0x55,未按下：0xAA ,状态默认值为0xAA */
/* 34 */uint16_t    temp_speed_limit_num;				/**<  临时限速信息的个数，最大值10 */
/* 35 */temp_speed_limit_info_t     temp_speed_info[MA_LIMIT_NUM_MAX];			/**<  临时限速状态 */
/* 47 */uint8_t     destination_status;					/**<  运行目的地属性信息, 通过：0x55,折返：0xAA,回段：0xCC,默认值：0xFF */

}onboard_control_info_t;


/**
 *@brief ZC对VOBC注册/注销请求的应答 (ZC->VOBC)
 */
typedef struct onboard_request_respond{
/* 1  */ //uint16_t    msg_type;                	/**<  报文类型 0x0205*/
/* 2  */uint8_t     request_return;            	/**<  zc的应答信息，注册成功：0x55,注册失败：0xAA,注销成功：0xCC,其他非法 */
/* 3  */uint8_t     unregister_reason ;      	/**<  注册失败原因：0x**(根据业主要求定义),0x00：默认值，注册成功时填写 */
/* 4  */uint16_t	reserv;						/**<  预留 */
}onboard_request_respond_t;

/**
 *@brief ZC主动注销车载的条件成立时，发送该信息 (ZC->VOBC)
 */
typedef struct onboard_unregister_rsq{
/* 1  */ //uint16_t    msg_type;                	/**<  报文类型 0x0207*/
/* 2  */uint8_t     cmd;            			/**<  注销命令,注销请求：0x55,其他非法 */
/* 3  */uint8_t     unregister_reason ;      	/**<  注销原因，0x**(根据业主要求定义) */
/* 4  */uint16_t	reserv;						/**<  预留 */
}onboard_unregister_rsq_t;

/**
 *@brief 特殊控制命令 (ZC->VOBC)
 */
typedef struct special_control_cmd{
/* 1  */ //uint16_t    msg_type;                	/**<  报文类型 0x0209*/
/* 2  */uint8_t     cmd;            			/**<  紧急制动命令 ,有紧急制动命令：0x55,无紧急制动命令：0xAA */
/* 3  */uint8_t     zc_ci_status ;      		/**<  ZC与CI通信状态,有故障：0x55,无故障：0xAA,其他非法 */
/* 4  */uint8_t		ma_gener_status_1;			/**<  MA生成状态1,无法计算：0x55,已计算：0xAA,其他：0xFF */
/* 5  */uint8_t		ma_gener_status_2;			/**<  MA生成状态2,无法计算：0x55,已计算：0xAA,其他：0xFF */
/* 6  */uint8_t		train_error_info;			/**<  有错误：0x55,无错误：0xAA,其他非法 */
/* 7  */uint8_t		auto_back_hold_status;		/**<  折返过程尾端安全连接保持, 保持：0x55,不保持：0xAA,其他非法*/

}special_control_cmd_t;

/**
 *@brief zc_ats信息头
 */
typedef struct _ats_header_info{
/* 1  */uint16_t    a_msg_len;		/**< 报文长度,报文类型-报文结束 */
/* 2  */uint16_t    a_msg_type;		/**< zc-ats通信的信息报文头类型 */

}ats_header_info_t;


/**
 *@brief TSR验证命令确认1 (ZC->ATS)
 */
typedef struct _zc_tsr_verify_frame_1{
/* 1  */uint8_t    z_verify_outcome;                /**<  确认结果 成功:0x55,失败:0xaa */
/* 2  */uint8_t    z_faile_reason;                	/**<  失败原因:
                                                                    0x00:无报警信息,
                                                                    0x01:命令参数不合法,
                                                                    0x02:限速区域有重叠,
                                                                    0x03:限速区域与列车MA区域有重叠,
                                                                    0x04:未收到联锁的确认,
                                                                    0x05:验证消息结果超时，
                                                                    0x07:验证消息不存在的限速，
                                                                    0xaa:未知原因*/
/* 3  */uint8_t    z_temp_rate_limit;               /**< 临时限速信息, 每5km/h一个等级，不考虑线路限速
                                                                       4-16：20km/h-80km/h
                                                                       无限速：0xFF;
                                                                       其他非法	*/
/* 4  */uint16_t    z_logic_tracknum;               /**< TSR区域所包含的逻辑区段的数量 */
                
}zc_tsr_verify_frame_1_t;


/**
 *@brief TSR验证命令确认2 (ZC->ATS )
 */
typedef struct _zc_tsr_verify_frame_2{
/* 1  */uint16_t    z_logic_track_id;               /**< TSR起点至终点逻辑区段的的ID */
                
}zc_tsr_verify_frame_2_t;


/**
 *@brief TSR执行命令确认1 (ZC->ATS)
 */
typedef struct _zc_tsr_exeute_frame_1{
/* 1  */uint8_t    z_verify_outcome;                /**<  确认结果 成功:0x55,失败:0xaa */
/* 2  */uint8_t    z_alarm_info;                	/**<  报警信息:
                                                                    0x00:无报警信息,
                                                                    0x01:命令参数不合法,
                                                                    0x02:限速区域有重叠,
                                                                    0x03:限速区域与列车MA区域有重叠,
                                                                    0x05:验证消息结果超时，
                                                                    0x06:未经过验证的执行请求，*/
/* 3  */uint8_t    z_temp_rate_limit;               /**< 临时限速信息, 每5km/h一个等级，不考虑线路限速
                                                                       4-16：20km/h-80km/h
                                                                       无限速：0xFF;
                                                                       其他非法	*/
/* 4  */uint16_t    z_logic_tracknum;               /**< TSR区域所包含的逻辑区段的数量 */

}zc_tsr_exeute_frame_1_t;

/**
 *@brief TSR执行命令确认2 (ZC->ATS )
 */
typedef struct _zc_tsr_exeute_frame_2{
/* 1  */uint16_t    z_logic_track_id;               /**< TSR起点至终点逻辑区段的的ID */
                
}zc_tsr_exeute_frame_2_t;


/**
 *@brief TSR状态帧1 (ZC->ATS )
 */
typedef struct _zc_status_frame_1{
/* 1  */uint8_t    z_power_on_rsq;               /**< 上电TSR确认请求	,有效：0x55  无效：0xaa */
/* 2  */uint16_t   z_logic_tracknum;             /**< ZC管辖范围内全部逻辑区段的数量	*/

}zc_status_frame_1_t;


/**
 *@brief TSR状态帧2 (ZC->ATS )
 */
typedef struct _zc_status_frame_2{
/* 1  */uint16_t    z_temp_rate_limit;               /**< 临时限速信息, 每5km/h一个等级，不考虑线路限速
                                                                       4-16：20km/h-80km/h
                                                                       无限速：0xFF;	*/				
}zc_status_frame_2_t;


/**
 *@brief ATS时钟信息 (ATS->ZC )
 */
typedef struct _ats_tick_frame{
/* 1  */uint8_t    a_year;              /**< 年 */ 
/* 2  */uint8_t    a_month;             /**< 月 */ 
/* 3  */uint8_t    a_day; 				/**< 日 */ 
/* 4  */uint8_t    a_hour; 				/**< 时 */ 
/* 5  */uint8_t    a_minute; 		    /**< 分 */ 
/* 6  */uint8_t    a_second; 		    /**< 秒 */ 

}ats_tick_frame_t;

/**
 *@brief TSR验证命令--1 (ATS->ZC )
 */
typedef struct _ats_tsr_verify_frame_1{
/* 1  */uint8_t    a_temp_rate_limit;               /**< 临时限速信息, 每5km/h一个等级，不考虑线路限速
                                                                       4-16：20km/h-80km/h
                                                                       无限速：0xFF; */ 
/* 2  */uint16_t   a_logic_tracknum;                /**< TSR区域所包含的逻辑区段的数量 */

}ats_tsr_verify_frame_1_t;

/**
 *@brief TSR验证命令--2 (ATS->ZC )
 */
typedef struct _ats_tsr_verify_frame_2{
/* 1 */uint16_t   a_logic_id;                       /**< TSR起点至终点逻辑区段的的ID */

}ats_tsr_verify_frame_2_t;


/**
 *@brief TSR执行命令--1 (ATS->ZC )
 */
typedef struct _ats_tsr_exeute_frame_1{
/* 1  */uint8_t    a_temp_rate_limit;               /**< 临时限速信息, 每5km/h一个等级，不考虑线路限速
                                                                       4-16：20km/h-80km/h
                                                                       无限速：0xFF; */ 
/* 2  */uint16_t   a_logic_tracknum;                /**< TSR区域所包含的逻辑区段的数量 */

}ats_tsr_exeute_frame_1_t;

/**
 *@brief TSR执行命令--2 (ATS->ZC )
 */
typedef struct _ats_tsr_exeute_frame_2{
/* 1 */uint16_t   a_logic_id;                       /**< TSR起点至终点逻辑区段的的ID */

}ats_tsr_exeute_frame_2_t;

/**
 *@brief 上电TSR确认 (ATS->ZC )
 */
typedef struct _ats_power_on_frame{
/* 1 */uint16_t   a_zc_id;                       /**< ZC编号	 */

}ats_power_on_frame_t;




/** 定义调试信息:调试总开关 */
//#define PARSER_DEBUG
#ifdef PARSER_DEBUG
    #define d_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define d_printf(fmt,...) 
#endif

/*- 进路信息调试接口  */
//#define ROUTE_INFO_DEBUG
#if (defined PARSER_DEBUG) && (defined ROUTE_INFO_DEBUG )
    #define route_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define route_printf(fmt,...) 
#endif

/*- 计轴区段状态信息调试接口  */
//#define DI_ZONE_INFO_DEBUG
#if (defined PARSER_DEBUG) && (defined DI_ZONE_INFO_DEBUG )
    #define di_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define di_printf(fmt,...) 
#endif

/*- 逻辑区段状态信息调试接口  */
//#define L_TRACK_INFO_DEBUG
#if (defined PARSER_DEBUG) && (defined L_TRACK_INFO_DEBUG )
    #define ltrack_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define ltrack_printf(fmt,...) 
#endif

/*- 信号机接近信息调试接口  */
//#define SIGNAL_CLOSE_DEBUG
#if (defined PARSER_DEBUG) && (defined SIGNAL_CLOSE_DEBUG )
    #define signal_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define signal_printf(fmt,...) 
#endif

/** 定义ats调试信息:调试总开关 */
//#define ATS_PARSER_DEBUG
#ifdef ATS_PARSER_DEBUG
    #define ats_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define ats_printf(fmt,...) 
#endif

/** 定义ats 时钟帧 调试信息:调试总开关 */
//#define ATS_TICK_DEBUG
#if (defined ATS_PARSER_DEBUG) && (defined ATS_TICK_DEBUG )
    #define tick_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define tick_printf(fmt,...) 
#endif

/** 定义ats tsr验证命令帧 调试信息:调试总开关 */
//#define ATS_VERIFY_DEBUG
#if (defined ATS_PARSER_DEBUG) && (defined ATS_VERIFY_DEBUG )
    #define verify_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define verify_printf(fmt,...) 
#endif

/** 定义ats tsr执行命令帧 调试信息:调试总开关 */
//#define ATS_EXEUTE_DEBUG
#if (defined ATS_PARSER_DEBUG) && (defined ATS_EXEUTE_DEBUG )
    #define exeute_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define exeute_printf(fmt,...) 
#endif

/** 定义ats 上电TSR确认 调试信息:调试总开关 */
//#define ATS_POWER_DEBUG
#if (defined ATS_PARSER_DEBUG) && (defined ATS_POWER_DEBUG )
    #define power_printf(fmt,...) do{ printp("[%s ,%d]: " fmt "\n",__FUNCTION__,__LINE__,__VA_ARGS__);}while(0)
#else
    #define power_printf(fmt,...) 
#endif



/*- CBTC列车数据传输所用包头 */
extern const var_item_t stream_header_destbl[10];

/*- CI信息数据解析时的b2v表格定义 */
extern const var_item_t ci_header_destbl[3];
extern const var_item_t ci_route_destbl[10];
extern const var_item_t psd_destbl[1];
extern const var_item_t esb_destbl[1];
extern const var_item_t autoBackButton_destbl[1];
extern const var_item_t diZoneStatus_destbl[1];
extern const var_item_t routeUnlockRsq_destbl[1];

/*- VOBC信息数据解析时的b2v表格定义 */
extern const var_item_t vobc_header_destbl[2];
extern const var_item_t trainLocation_destbl[27];
extern const var_item_t register_info_destbl[2];

/*- ATS信息数据解析时的b2v表格定义 */
extern const var_item_t ats_header_destbl[2];
extern const var_item_t zc_tsr_verify_frame_1_destbl[4];
extern const var_item_t zc_tsr_verify_frame_2_destbl[1];
extern const var_item_t zc_tsr_exeute_frame_1_destbl[4];
extern const var_item_t zc_tsr_exeute_frame_2_destbl[1];
extern const var_item_t zc_status_frame_1_destbl[2];
extern const var_item_t zc_status_frame_2_destbl[1];
extern const var_item_t ats_tick_frame_destbl[6];
extern const var_item_t ats_tsr_verify_1_destbl[2];
extern const var_item_t ats_tsr_verify_2_destbl[1];
extern const var_item_t ats_tsr_exeute_1_destbl[2];
extern const var_item_t ats_tsr_exeute_2_destbl[1];
extern const var_item_t ats_power_on_destbl[1];

/*- 数据流解析函数 */
extern int16_t data_parser(uint8_t *data,int32_t len,void *data_out);


#pragma pack ()


#ifdef __cplusplus
}
#endif

#endif   /* _ZC_PUB_H */
