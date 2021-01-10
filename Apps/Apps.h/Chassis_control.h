#ifndef __CHIASSIS_CONTROL_H
#define __CHIASSIS_CONTROL_H

#include "user_common.h"


#define WheelMaxSpeed        9000.0f		//单轮最大速度

#define Chassis_MaxSpeed_Y	9000.0f		//底盘前后最快速度
#define Chassis_MaxSpeed_X	9000.0f		//底盘平移最快速度
#define Chassis_MaxSpeed_W	9000.0f		//底盘自旋最快速度



/* 底盘运动 */
typedef struct {
	float targetXRaw;		//底盘x轴原始数据
	float targetYRaw;		//底盘y轴原始数据
	float targetZRaw;		//底盘z轴原始数据
	float LpfAttFactor;		//底盘滤波系数
	float targetXLPF;		//底盘x轴滤波后数据
	float targetYLPF;		//底盘y轴滤波后数据
	float targetZLPF;		//底盘z轴滤波后数据
	float speedLimit;		//底盘速度限制
	float FollowtargetYawRaw;	//底盘目标Yaw轴跟随云台原始数据
	float FollowtargetYawLPF;	//底盘Yaw轴跟随云台滤波后数据

	positionpid_t FollowYawAttitude_pid;		//底盘Yaw轴跟随云台pid
	uint8_t mode;								//底盘控制模式
	uint8_t swingFlag;							//扭腰标志位
	float swingSpeed;					//扭腰速度
	uint8_t PowerOverflowFlag;					//超功率标志位
  WorldTime_RxTypedef Chassis_TIME;
	uint8_t Chassis_FPS;
}Chassis_t;



extern Chassis_t Chassis;
extern double Time_rad;
void Chassis_Init(void);
void MecanumCalculate(float Vx, float Vy, float VOmega, int16_t *Speed);
void Chassis_processing(float Vx, float Vy, float VOmega);

 
#endif /* __CHIASSIS_CONTROL_H */



