/**
  ******************************************************************************
  * @file    Chassis_control.c
  * @author  Liang Yuhao
  * @version V1.0
  * @date
  * @brief   底盘控制函数接口
  ******************************************************************************
  */


#include "Chassis_control.h"

Chassis_t Chassis;



/**
  * @brief  底盘初始化，配置参数
  * @param  None
  * @retval None
  */
void Chassis_Init(void) {

	Chassis.LpfAttFactor = 0.05f;

	/*-----正常使用PID-----*/
	//底盘电机PID
	for (int i = 0; i < 4; i++) {
		IncrementalPID_paraReset(&M3508s[i].pid, 2.5f, 0.8f, 0.0f, M3508_MaxOutput, 1000);
	}

}


/**
  * @brief  麦克纳姆轮速度解算
  * @param[in]  Vx		x轴速度
  *				Vy		y轴速度
  *				VOmega	自转速度
  * @param[out]	Speed	速度
  * @retval None
  */
void MecanumCalculate(float Vx, float Vy, float VOmega, int16_t *Speed)
{
	float tempSpeed[4];
	float MaxSpeed = 0.0f;
	float Param = 1.0f;

	//速度限制
	VAL_LIMIT(Vx, -Chassis_MaxSpeed_X, Chassis_MaxSpeed_X);
	VAL_LIMIT(Vy, -Chassis_MaxSpeed_Y, Chassis_MaxSpeed_Y);
	VAL_LIMIT(VOmega, -Chassis_MaxSpeed_W, Chassis_MaxSpeed_W);

	//四轮速度分解
	tempSpeed[0] = Vx - Vy + VOmega;
	tempSpeed[1] = Vx + Vy + VOmega;
	tempSpeed[2] = -Vx + Vy + VOmega;
	tempSpeed[3] = -Vx - Vy + VOmega;

	//寻找最大速度
	for (uint8_t i = 0; i < 4; i++)
	{
		if (abs(tempSpeed[i]) > MaxSpeed)
		{
			MaxSpeed = abs(tempSpeed[i]);
		}
	}


	//速度分配
	if (MaxSpeed > WheelMaxSpeed)
	{
		Param = (float)WheelMaxSpeed / MaxSpeed;
	}

	Speed[0] = tempSpeed[0] * Param;
	Speed[1] = tempSpeed[1] * Param;
	Speed[2] = tempSpeed[2] * Param;
	Speed[3] = tempSpeed[3] * Param;

}
void Get_Rad_s(M3508s_t *M3508)
{

	M3508->rad_S = sin(Time_rad);

	return;

}


/**
  * @brief  底盘控制处理-跟随云台
  * @param[in]  Vx		x轴速度
  *				Vy		y轴速度
  *				Omega	偏向角
*				mode	模式 - 除Status_ControlOFF外，其他正常控制
  * @retval None
  */

  //底盘遥控左右转斜坡
SpeedRamp_t ChassisRamp_Rotate = { \
  0,\
	0,\
	-9900,\
	9900,\
};

double Time_rad = 0;
float Turn = 1;
void Chassis_processing(float Vx, float Vy, float VOmega) {
	if (Robot.Sport_ChassisWorkMode == ChassisWorkMode_Disable || DR16.infoUpdateFrame < 20) {
		for (int i = 0; i < 4; i++)
		{
			M3508s[i].outCurrent = 0;
			M3508s[i].spd = 0;
			Time_rad = -1.6624f;
		}

		return;
	}

	int16_t speed[4];

	if (Last_ChassisWorkMode != Robot.Sport_ChassisWorkMode || Last_CloudWorkMode != Robot.Sport_CloudWorkMode)
	{
		ChassisRamp_Rotate.count = M3508s[0].targetSpeed;
		if (M3508s[0].targetSpeed > 0)
		{
			ChassisRamp_Rotate.rate = -10;
		}
		else if (M3508s[0].targetSpeed < 0)
		{
			ChassisRamp_Rotate.rate = 10;
		}
		else if (M3508s[0].targetSpeed == 0)
		{
			ChassisRamp_Rotate.rate = 0;
			M3508s[0].targetSpeed = 0;
			Last_ChassisWorkMode = Robot.Sport_ChassisWorkMode;
			Last_CloudWorkMode = Robot.Sport_CloudWorkMode;
		}

		M3508s[0].targetSpeed =  SpeedRampCalc(&ChassisRamp_Rotate);
		Time_rad = -1.6624f;
	}
	else
	{
		switch (Robot.Sport_ChassisWorkMode)
		{
		case ChassisWorkMode_Auto:
			Get_Rad_s(&M3508s[0]);

			M3508s[0].spd = (0.785 * M3508s[0].rad_S) + 1.305;
			if (Robot.Sport_CloudWorkMode == CloudWorkMode_Negative)
			{
				Turn = -1;
			}
			else
			{
				Turn = 1;
			}

			for (int i = 0; i < 4; i++) {
				speed[i] = Rad_To_Rpm * M3508s[0].spd * 5.18f*1.55f;
				M3508s[i].targetSpeed = speed[i] * 40 * Turn;
				//M3508s[i].targetSpeed *= (0.89f/1.8339f);
			}

			break;

		case ChassisWorkMode_Manual:

			//麦轮解算
			MecanumCalculate(Vx, Vy, VOmega, speed);

			for (int i = 0; i < 4; i++) {
				M3508s[i].targetSpeed = speed[i];
			}

			break;

		case ChassisWorkMode_Disable:

			break;

		}
	}




	for (int i = 0; i < 4; i++) {
		if (M3508s[i].InfoUpdateFlag == 1) {//避免在赋值多次而电机才读取了一次数据的情况。

			//PID计算
			M3508s[i].outCurrent = Incremental_PID(&M3508s[i].pid, M3508s[i].targetSpeed, M3508s[i].realSpeed);
			//清标志位
			M3508s[i].InfoUpdateFlag = 0;
			M3508s[i].InfoUpdateFrame++;
		}
	}

}






