#ifndef __DEVICESMONITOR_H
#define __DEVICESMONITOR_H

#include "user_common.h"


//���صĴ������ǰ���޸�Alert_Times ʵ�ֱ�����
typedef enum
{
	Alert_Times_SoftWare = 20,//������������±�Խ�磬����Ƶ�ʴ��󡣵ȣ�
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
	//Ҫ����˳�����س̶�Խ�ߣ�����Խ���ұ�֤����0
}Alert_Times_t;



void Buzzer_On(bool on);
void DevicesMonitor_update(void);
void  DevicesMonitor_Init(void);
void  Device_setAlertType(Alert_Times_t time);
uint8_t FPS_Calculate(uint16_t deltaTime);
void Get_FPS(WorldTime_RxTypedef *time, uint8_t *FPS);

#endif /* __DEVICESMONITOR_H */




