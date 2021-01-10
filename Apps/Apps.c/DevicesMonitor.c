/**
  ******************************************************************************
  * @file    DevicesMonitor.c
  * @author  Hare
  * @version V1.0
  * @date
  * @brief   外部设备帧率检测函数接口
  ******************************************************************************
  */


#include "DevicesMonitor.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

#define  Buzzer_DefaultPWM 270 //蜂鸣器报警的音量，270最大。
  /************************************************************************/
  /* 模块离线检测思路：
	  特殊的：遥控器离线 == 机器人进入失能模式。
	  其他：部分设备离线 == 将该功能模块进行失能或切换。
	  如：自瞄识别、陀螺仪、裁判系统、
  */
  /************************************************************************/



Alert_Times_t Alert_Times = Alert_Times_None; //当前报警次数，对应下面的枚举类型。
//枚举类型。



void  Device_setAlertType(Alert_Times_t time) {
	Alert_Times = max(time, Alert_Times);//数字越大，严重程度越高，避免被优先级低的覆盖。
}

/**
  * @brief  外接设备帧率清零，每200ms清零一次
  * @param  None
  * @retval None
  */
void DevicesMonitor_update(void) {
	Alert_Times = (Alert_Times_t)0;//进行重置。
	//-------------------  检测开始 -----------------

	//M3508
	for (int i = 0; i < 4; i++) {
		if (M3508s[i].InfoUpdateFrame < 1) {
			M3508s[i].OffLineFlag = 1;
			Device_setAlertType(Alert_Times_M3508);
		}
		else {
			M3508s[i].OffLineFlag = 0;
		}
		M3508s[i].InfoUpdateFrame = 0;
	}

	//CAN线路检测 ---------------------------
	if (Monitor_CAN1.InfoUpdateFrame < 1) {
		Monitor_CAN1.OffLineFlag = 1;
		Device_setAlertType(Alert_Times_CAN1);
	}
	else {
		Monitor_CAN1.OffLineFlag = 0;
	}
	Monitor_CAN1.InfoUpdateFrame = 0;

	if (Monitor_CAN2.InfoUpdateFrame < 1) {
		Monitor_CAN2.OffLineFlag = 1;
		Device_setAlertType(Alert_Times_CAN2);
	}
	else {
		Monitor_CAN2.OffLineFlag = 0;
	}
	Monitor_CAN2.InfoUpdateFrame = 0;

	//云台陀螺仪检测 ---------------------------
	if (IMU_Cloud.InfoUpdateFrame < 1) {
		IMU_Cloud.OffLineFlag = 1;
		Device_setAlertType(Alert_Times_CloudIMU);

	}
	else {
		IMU_Cloud.OffLineFlag = 0;
	}
	IMU_Cloud.InfoUpdateFrame = 0;

	//底盘陀螺仪检测 ---------------------------
	if (IMU_Chassis.InfoUpdateFrame < 1) {
		IMU_Chassis.OffLineFlag = 1;
		Device_setAlertType(Alert_Times_CloudIMU);

	}
	else {
		IMU_Chassis.OffLineFlag = 0;
	}
	IMU_Chassis.InfoUpdateFrame = 0;


	//遥控器 ---------------------------
	if (DR16.infoUpdateFrame < 1) {
		DR16.offLineFlag = 1;
		Robot_Disable();//遥控器离线，机器人全局失能。
		Device_setAlertType(Alert_Times_DR16);

	}
	else {
		DR16.offLineFlag = 0;
		Robot_Enable();

	}
	DR16.infoUpdateFrame = 0;


	//视觉自瞄 ---------------------------
	if (VisionData.InfoUpdateFrame < 1) {
		VisionData.OffLineFlag = 1;
	}
	else {
		VisionData.OffLineFlag = 0;
	}
	VisionData.InfoUpdateFrame = 0;

	VisionData.OffLineFlag = 0;  //没有视觉情况下，暂时先默认视觉在线绕过检测系统
}

void  DevicesMonitor_Init(void) {

	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);

}

//控制蜂鸣器的开关接口。
void Buzzer_On(bool on) {

	int pwm = Buzzer_DefaultPWM;
	if (on == 0)
	{
		pwm = 0;
	}

	TIM_SetCompare1(TIM12, pwm);
}

uint8_t FPS_Calculate(uint16_t deltaTime) { //FPS计算函数。
	return (1.0f / (double)(deltaTime)) * 1000.0f; // 别忘了先转换为浮点数，否则会有精度丢失
}

void Get_FPS(WorldTime_RxTypedef *time, uint8_t *FPS)  //获取当前系统时钟节拍并算出FPS
{
	time->WorldTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
	*FPS = FPS_Calculate(time->WorldTime - time->Last_WorldTime);
	time->Last_WorldTime = time->WorldTime;
}


