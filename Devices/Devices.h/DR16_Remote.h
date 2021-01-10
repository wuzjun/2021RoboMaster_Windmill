#ifndef __DR16_RECEIVER_H
#define __DR16_RECEIVER_H

#include "user_common.h"
#pragma anon_unions

/*���ö���*/
#define DR16BufferNumber 22
#define DR16BufferTruthNumber 18
#define DR16BufferLastNumber 4

extern uint8_t DR16Buffer[DR16BufferNumber];

extern uint8_t  id ;

/*�ṹ���ʼ��*/

#define DR16_GroundInit \
{ \
{0,0,0,0,0,0,0}, \
{0,0,0,0,0}, \
{0}, \
0, \
0, \
&DR16_ReInit, \
&DR16_Process, \
&DR16_Handler, \
} \
/* =========================== Include&Define End=========================== */


/* =========================== Structure Begin =========================== */
/*ң�����ṹ��*/
typedef struct
{
	struct {
		int16_t ch0;//yaw
		int16_t ch1;//pitch
		int16_t ch2;//left_right
		int16_t ch3;//forward_back
		uint8_t s_left;
		uint8_t s_right;
		int16_t ch4_DW; //����
	}rc;//ң�������յ���ԭʼֵ��

	struct {
		int16_t x;
		int16_t y;
		int16_t z;

		uint8_t keyLeft;
		uint8_t keyRight;

	}mouse;

	union {//union�������÷�
		uint16_t key_code;
		struct { //λ���ʹ��
			bool press_W : 1;
			bool press_S : 1;
			bool press_A : 1;
			bool press_D : 1;

			bool press_Shift : 1;
			bool press_Ctrl : 1;
			bool press_Q : 1;
			bool press_E : 1;

			bool press_R : 1;
			bool press_F : 1;
			bool press_G : 1;
			bool press_Z : 1;

			bool press_X : 1;
			bool press_C : 1;
			bool press_V : 1;
			bool press_B : 1;
		};
	}keyBoard;



	uint16_t infoUpdateFrame;	//֡��
	uint8_t offLineFlag;		//�豸���߱�־

	/*ָ�뺯��*/
	void(*DR16_ReInit)(void);
	void(*DR16_Process)(uint8_t *pData);
	void(*DR16_Handler)(UART_HandleTypeDef *huart);

} DR16_t;

/**********************************************/
//ң�ز���λ��ѡ��,s1��s2�����á�
typedef enum
{
	RemotePole_UP = 1, //��
	RemotePole_MID = 3,	//��
	RemotePole_DOWM = 2	//��
}RemotePole_e;

typedef struct {
	RemotePole_e Left;
	RemotePole_e Right;

}ControlSwitch_t;//ң������s1��s2����


typedef struct
{

	struct
	{
		float Forward_Back_Value; //Vx
		float Omega_Value;//����ֵ��
		float Left_Right_Value;//Vy
		float Pitch_Value;
		float Yaw_Value;
	}Robot_TargetValue;//ң�ؼ����������˶��ٶ�
	ControlSwitch_t ControlSwitch;
}DR16_Export_Data_t; //�������ļ�ʹ�õ�������ݡ�



/* =========================== Structure End=========================== */


/* =========================== Extern Begin =========================== */
/*���⿪��API�ͽṹ��*/
extern DR16_t DR16;
extern DR16_Export_Data_t DR16_Export_data;
/* =========================== Extern End=========================== */

/* =========================== Function Begin =========================== */
/* =========================== Function End=========================== */

#endif /* __DR16_RECEIVER_H */
