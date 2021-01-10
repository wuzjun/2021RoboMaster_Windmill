#include "Robot_control.h"

Robot_t Robot; //全局机器人对象。

ChassisWorkMode_e Last_ChassisWorkMode;
CloudWorkMode_e Last_CloudWorkMode;
void Robot_init(void) {

	Robot.Sport_ChassisWorkMode = ChassisWorkMode_Manual;
	Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
	Last_ChassisWorkMode = Robot.Sport_ChassisWorkMode;
	Last_CloudWorkMode = Robot.Sport_CloudWorkMode;

}



static void Chassis_control() {
	//超级电容通信计数器
	Chassis_processing(0, 0, DR16_Export_data.Robot_TargetValue.Yaw_Value);
}
static void Cloud_control()
{
	//	Cloud_processing_WithoutIMU(DR16_Export_data.Robot_TargetValue.Yaw_Value, DR16_Export_data.Robot_TargetValue.Pitch_Value);


}
void CAN_SendControl() {
	//解决一个报文发给不同电机的问题。

	// -------  CAN1
	CAN_0x200_SendData(&hcan1, M3508s[0].outCurrent, 0, 0, 0);
	// -------  CAN2  
}


void Robot_control(void) {

	Chassis_control();
	CAN_SendControl();
}


/**
	* @brief  更改机器人控制来源
  * @param	void
  * @retval None
  */
void Robot_ChangeControlSource(ControlSource_e controlSource)
{
	if (Robot.ControlSource != controlSource) //发生模式跳变，重置。
	{
		Robot_Reset();
	}
	Robot.ControlSource = controlSource;
}

/*************************************
* Method:    Robot_Reset
* Returns:   void
* Parameter: void
* Author: -Yvfneg
 复位机器人,重新初始化
************************************/
void Robot_Reset(void)
{
	//重新初始化机器人。
	Robot.Sport_ChassisWorkMode = ChassisWorkMode_Manual;
	Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
}

/*************************************
* Method:    Robot_Enable
* Returns:   void
* Parameter: void
* Author: -Yvfneg
全局使能接口，调用后机器人设备才能运转
************************************/
void Robot_Enable(void) {
	//if (Robot.WorkStatus == WorkStatus_Disable)//发生状态跳变，进行初始化工作。
	//{
		//Robot_Reset();
	Robot.WorkStatus = WorkStatus_Normal;
	//}
	//if (Robot.WorkStatus != WorkStatus_Prepare)
	//{
	//	Robot.WorkStatus = WorkStatus_Normal;
	//}
}

/*************************************
* Method:    Robot_Disable
* Returns:   void
* Parameter: void
* Author:  -Yvfneg
全局失能接口，调用后机器人设备全部失能（不伺服）。
************************************/
void Robot_Disable(void)
{
	Robot.WorkStatus = WorkStatus_Disable;

	DR16_Export_data.Robot_TargetValue.Forward_Back_Value = 0;
	DR16_Export_data.Robot_TargetValue.Left_Right_Value = 0;
	DR16_Export_data.Robot_TargetValue.Omega_Value = 0;
	DR16_Export_data.Robot_TargetValue.Pitch_Value = 0;
	DR16_Export_data.Robot_TargetValue.Yaw_Value = 0;
	Robot.Sport_ChassisWorkMode = ChassisWorkMode_Disable;
	Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
}





