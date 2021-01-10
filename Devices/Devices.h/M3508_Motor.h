#ifndef __M3508_MOTOR_H
#define __M3508_MOTOR_H

#include "user_common.h"

#define M3508_READID_START	0x201
#define M3508_READID_END	  0x204
#define M3508_SENDID		    0x200
#define M3508_MaxOutput 16384 //���͸������������ֵ
#define M3508_CurrentRatio	819.2f	//16384/20A = 819.2->1A

typedef struct {
	uint16_t realAngle;			    //�������Ļ�е�Ƕ�
	int16_t  realSpeed;			    //���������ٶ�
	int16_t  realCurrent;		    //��������ʵ�ʵ���
	uint8_t  temperture;        //�������ĵ���¶�

	int16_t  targetSpeed;			  //Ŀ���ٶ�
	uint16_t targetAngle;			  //Ŀ��Ƕ�
	uint16_t lastAngle;			//�ϴεĽǶ�
	int32_t  totalAngle;			//�ۻ��ܹ��Ƕ�
	int16_t  turnCount;			//ת����Ȧ��

	int16_t  outCurrent;				//�������

	incrementalpid_t pid;		    //���pid
	positionpid_t pid_angle;		//�Ƕȵ��pid

	uint8_t  InfoUpdateFlag;		  //��Ϣ��ȡ���±�־
	uint16_t InfoUpdateFrame;	  //֡��
	uint8_t  OffLineFlag;		    //�豸���߱�־
	float spd;
  float rad_S;
}M3508s_t;

extern M3508s_t M3508s[4];


void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
void M3508_getInfo(CAN_RxTypedef RxMessage);



#endif /* __M3508_MOTOR_H */



