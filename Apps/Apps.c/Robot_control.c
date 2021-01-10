#include "Robot_control.h"

Robot_t Robot; //ȫ�ֻ����˶���

ChassisWorkMode_e Last_ChassisWorkMode;
CloudWorkMode_e Last_CloudWorkMode;
void Robot_init(void) {

	Robot.Sport_ChassisWorkMode = ChassisWorkMode_Manual;
	Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
	Last_ChassisWorkMode = Robot.Sport_ChassisWorkMode;
	Last_CloudWorkMode = Robot.Sport_CloudWorkMode;

}



static void Chassis_control() {
	//��������ͨ�ż�����
	Chassis_processing(0, 0, DR16_Export_data.Robot_TargetValue.Yaw_Value);
}
static void Cloud_control()
{
	//	Cloud_processing_WithoutIMU(DR16_Export_data.Robot_TargetValue.Yaw_Value, DR16_Export_data.Robot_TargetValue.Pitch_Value);


}
void CAN_SendControl() {
	//���һ�����ķ�����ͬ��������⡣

	// -------  CAN1
	CAN_0x200_SendData(&hcan1, M3508s[0].outCurrent, 0, 0, 0);
	// -------  CAN2  
}


void Robot_control(void) {

	Chassis_control();
	CAN_SendControl();
}


/**
	* @brief  ���Ļ����˿�����Դ
  * @param	void
  * @retval None
  */
void Robot_ChangeControlSource(ControlSource_e controlSource)
{
	if (Robot.ControlSource != controlSource) //����ģʽ���䣬���á�
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
 ��λ������,���³�ʼ��
************************************/
void Robot_Reset(void)
{
	//���³�ʼ�������ˡ�
	Robot.Sport_ChassisWorkMode = ChassisWorkMode_Manual;
	Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
}

/*************************************
* Method:    Robot_Enable
* Returns:   void
* Parameter: void
* Author: -Yvfneg
ȫ��ʹ�ܽӿڣ����ú�������豸������ת
************************************/
void Robot_Enable(void) {
	//if (Robot.WorkStatus == WorkStatus_Disable)//����״̬���䣬���г�ʼ��������
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
ȫ��ʧ�ܽӿڣ����ú�������豸ȫ��ʧ�ܣ����ŷ�����
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





