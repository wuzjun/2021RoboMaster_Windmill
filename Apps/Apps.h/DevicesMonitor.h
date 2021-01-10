#ifndef __DEVICESMONITOR_H
#define __DEVICESMONITOR_H

#include "user_common.h"


//严重的错误放在前，修改Alert_Times 实现报警。
typedef enum
{
	Alert_Times_SoftWare = 20,//代码错误（数组下标越界，运行频率错误。等）
	Alert_Times_CAN1 = 10,
	Alert_Times_CAN2 = 9,
	Alert_Times_DR16 = 8,

	Alert_Times_ChassisIMU = 6,
	Alert_Times_CloudIMU = 5,
	Alert_Times_M6020 = 4,
	Alert_Times_M3508 = 3,
	Alert_Times_M2006 = 2,
	Alert_Times_Vision = 1,
	Alert_Times_None = 0,
	//要按照顺序，严重程度越高，数字越大，且保证大于0
}Alert_Times_t;



void Buzzer_On(bool on);
void DevicesMonitor_update(void);
void  DevicesMonitor_Init(void);
void  Device_setAlertType(Alert_Times_t time);
uint8_t FPS_Calculate(uint16_t deltaTime);
void Get_FPS(WorldTime_RxTypedef *time, uint8_t *FPS);

#endif /* __DEVICESMONITOR_H */




