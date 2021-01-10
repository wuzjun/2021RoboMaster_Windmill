#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#pragma anon_unions

/*尽量减少将定义放到此文件，规范的放到模块文件里面。*/

/* PID参数 */
typedef struct {
	float Target; 			        //设定目标值
	float Measured; 				    //测量值
	float err; 						      //本次偏差值
	float err_last; 				    //上一次偏差
	float err_beforeLast; 			//上上次偏差
	float Kp, Ki, Kd;				    //Kp, Ki, Kd控制系数
	float p_out, i_out, d_out;//各部分输出值
	float pwm; 						      //pwm输出
	uint32_t MaxOutput;				  //输出限幅
	uint32_t IntegralLimit;			//积分限幅 
}incrementalpid_t;

typedef struct {
	float Target; 					    //设定目标值
	float Measured; 				    //测量值
	float err; 						      //本次偏差值
	float err_last; 				    //上一次偏差
	float err_change; 				    //误差变化率
	float Kp, Ki, Kd;				    //Kp, Ki, Kd控制系数
	float p_out, i_out, d_out;//各部分输出值
	float pwm; 						      //pwm输出
	uint32_t MaxOutput;				  //输出限幅
	uint32_t IntegralLimit;			//积分限幅 
}positionpid_t;



/* 陀螺仪 */
typedef struct {
		float x;                 //浮点数pitch轴的方向向量
		float y;                 //浮点数Y轴方向向量
		float z;                 //浮点数yaw轴的转动速度
}Vector_t;

typedef struct {
	float Roll;                 //ROLL轴方向，当前的角度值
	float Pitch;                //PITCH轴方向
	float Yaw;                  //YAW轴方向
}Eular_t;



typedef struct
{
	uint8_t     CANx;               //CAN编号     1 CAN1      2 CAN2
	uint8_t CAN_RxMessage[8];
	CAN_RxHeaderTypeDef CAN_RxHeader;
}CAN_RxTypedef;


typedef struct
{
	uint32_t WorldTime;               //世界时间
	uint32_t Last_WorldTime;     //上一次世界时间
}WorldTime_RxTypedef;


#endif /* __TYPEDEFS_H */
