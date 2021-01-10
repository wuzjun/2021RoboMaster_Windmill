#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#pragma anon_unions

/*�������ٽ�����ŵ����ļ����淶�ķŵ�ģ���ļ����档*/

/* PID���� */
typedef struct {
	float Target; 			        //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						      //����ƫ��ֵ
	float err_last; 				    //��һ��ƫ��
	float err_beforeLast; 			//���ϴ�ƫ��
	float Kp, Ki, Kd;				    //Kp, Ki, Kd����ϵ��
	float p_out, i_out, d_out;//���������ֵ
	float pwm; 						      //pwm���
	uint32_t MaxOutput;				  //����޷�
	uint32_t IntegralLimit;			//�����޷� 
}incrementalpid_t;

typedef struct {
	float Target; 					    //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						      //����ƫ��ֵ
	float err_last; 				    //��һ��ƫ��
	float err_change; 				    //���仯��
	float Kp, Ki, Kd;				    //Kp, Ki, Kd����ϵ��
	float p_out, i_out, d_out;//���������ֵ
	float pwm; 						      //pwm���
	uint32_t MaxOutput;				  //����޷�
	uint32_t IntegralLimit;			//�����޷� 
}positionpid_t;



/* ������ */
typedef struct {
		float x;                 //������pitch��ķ�������
		float y;                 //������Y�᷽������
		float z;                 //������yaw���ת���ٶ�
}Vector_t;

typedef struct {
	float Roll;                 //ROLL�᷽�򣬵�ǰ�ĽǶ�ֵ
	float Pitch;                //PITCH�᷽��
	float Yaw;                  //YAW�᷽��
}Eular_t;



typedef struct
{
	uint8_t     CANx;               //CAN���     1 CAN1      2 CAN2
	uint8_t CAN_RxMessage[8];
	CAN_RxHeaderTypeDef CAN_RxHeader;
}CAN_RxTypedef;


typedef struct
{
	uint32_t WorldTime;               //����ʱ��
	uint32_t Last_WorldTime;     //��һ������ʱ��
}WorldTime_RxTypedef;


#endif /* __TYPEDEFS_H */
