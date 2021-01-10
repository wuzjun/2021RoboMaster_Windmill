/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无                               |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)      |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Control_Cloud.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                        
  |--Date        : 2019-03-27               
  |--Libsupports : 
  |--Description :                                                       
  |--FunctionList                                                       
  |-------1. ....                                                       
  |          <version>:                                                       
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#ifndef __BSP_CAN
#define __BSP_CAN
/* =========================== Include&Define Begin =========================== */
#include "can.h"
#include "user_common.h"
/* =========================== Include&Define End=========================== */

/* =========================== Structure Begin =========================== */
//用于检测CAN线路异常
typedef struct
{
	uint8_t  InfoUpdateFlag;		//信息读取更新标志
	uint16_t InfoUpdateFrame;	//帧率
	uint8_t  OffLineFlag;		  //离线故障标志
} CAN_t;


/* =========================== Structure End=========================== */

/* =========================== Extern Begin =========================== */
extern CAN_t Monitor_CAN1;
extern CAN_t Monitor_CAN2; //用于线路检测
/* =========================== Extern End=========================== */

/* =========================== Function Begin =========================== */
/*CAN1中断启动*/
void CAN1_IT_Init(void);
/*CAN2中断启动*/
void CAN2_IT_Init(void);

/*can发送函数*/
void CAN_SendData(CAN_HandleTypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);


/* =========================== Function End=========================== */
#endif
/*-----------------------------------file of end------------------------------*/
