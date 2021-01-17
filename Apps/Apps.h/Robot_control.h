/*
******************************************************************************
* @file    Robot_control.c
* @author  -Yvfneg
* @version V1.0
* @date
* @brief   机器人控制宏
*****************************************************************************
*/

#ifndef __Robot_CONTROL_H
#define __Robot_CONTROL_H
#include "user_common.h"


/************************************************************************/
/*
特别说明：
以下枚举都带有前缀的原因：防止枚举名重复，枚举混乱导致不必要的问题。
*/
/************************************************************************/

//机器人控制的来源，非信号来源。
typedef enum
{
	ControlSource_RC = 0,	//遥控器模式
	ControlSource_Stop  //关闭机器
}ControlSource_e;


//底盘工作模式
typedef enum
{
	ChassisWorkMode_Auto = 0,		             //自动模式
	ChassisWorkMode_Manual,                    //手动模式
	ChassisWorkMode_SmallAuto,                    //小能量模式
	ChassisWorkMode_Disable				         //失能模式
}ChassisWorkMode_e;

//云台工作模式
typedef enum
{
	CloudWorkMode_Negative = 0,		//正常模式（360°云台）
	CloudWorkMode_Disable				//失能
}CloudWorkMode_e;



//机器人工作状态
typedef enum
{
	WorkStatus_Prepare,//从失能进入到正常状态的过渡阶段，开机时候初始化的准备状态
	WorkStatus_Disable,//失能状态，应对紧急情况和开机启动。
	WorkStatus_Normal//正常运行状态
}WorkStatus_e;


/**************************以上为枚举**************************/

typedef struct
{
	//控制相关
	ControlSource_e ControlSource;//机器人当前受什么设备控制
	WorkStatus_e WorkStatus;//机器人是否处于准备状态。

	//运动相关
	ChassisWorkMode_e Sport_ChassisWorkMode;
	CloudWorkMode_e Sport_CloudWorkMode;

}Robot_t;


void Robot_Enable(void);
void Robot_Disable(void);


void CAN_SendControl(void);
void Robot_Reset(void);
void Robot_control(void);
void Robot_ChangeControlSource(ControlSource_e controlSource);
void Robot_setChassisWorkMode(ChassisWorkMode_e mode);
void Robot_init(void);

extern	Robot_t Robot;
extern ChassisWorkMode_e Last_ChassisWorkMode;
extern CloudWorkMode_e Last_CloudWorkMode;

#endif
