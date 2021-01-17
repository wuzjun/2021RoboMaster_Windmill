/*
******************************************************************************
* @file    Robot_control.c
* @author  -Yvfneg
* @version V1.0
* @date
* @brief   �����˿��ƺ�
*****************************************************************************
*/

#ifndef __Robot_CONTROL_H
#define __Robot_CONTROL_H
#include "user_common.h"


/************************************************************************/
/*
�ر�˵����
����ö�ٶ�����ǰ׺��ԭ�򣺷�ֹö�����ظ���ö�ٻ��ҵ��²���Ҫ�����⡣
*/
/************************************************************************/

//�����˿��Ƶ���Դ�����ź���Դ��
typedef enum
{
	ControlSource_RC = 0,	//ң����ģʽ
	ControlSource_Stop  //�رջ���
}ControlSource_e;


//���̹���ģʽ
typedef enum
{
	ChassisWorkMode_Auto = 0,		             //�Զ�ģʽ
	ChassisWorkMode_Manual,                    //�ֶ�ģʽ
	ChassisWorkMode_SmallAuto,                    //С����ģʽ
	ChassisWorkMode_Disable				         //ʧ��ģʽ
}ChassisWorkMode_e;

//��̨����ģʽ
typedef enum
{
	CloudWorkMode_Negative = 0,		//����ģʽ��360����̨��
	CloudWorkMode_Disable				//ʧ��
}CloudWorkMode_e;



//�����˹���״̬
typedef enum
{
	WorkStatus_Prepare,//��ʧ�ܽ��뵽����״̬�Ĺ��ɽ׶Σ�����ʱ���ʼ����׼��״̬
	WorkStatus_Disable,//ʧ��״̬��Ӧ�Խ�������Ϳ���������
	WorkStatus_Normal//��������״̬
}WorkStatus_e;


/**************************����Ϊö��**************************/

typedef struct
{
	//�������
	ControlSource_e ControlSource;//�����˵�ǰ��ʲô�豸����
	WorkStatus_e WorkStatus;//�������Ƿ���׼��״̬��

	//�˶����
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
