#include "Monitor_RM_CAN.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"




/*************************************
* Method:    CAN_0x1FF_SendData
* Returns:   void
* Parameter: int16_t iq1，参数值。
* 说明：0x1FF报文的统一发送函数—— 控制3508的ID：5-8电机，6020的1-4，2006的5-8
************************************/
void CAN_0x1FF_SendData(CAN_HandleTypeDef* CAN_Num, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

	uint8_t data[8];

	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;

	CAN_SendData(CAN_Num, CAN_ID_STD, 0x1FF, data);
}


/*************************************
* Method:    CAN_0x200_SendData
* Returns:   void
* Parameter: int16_t iq1，参数值。
* 说明：0x200报文的统一发送函数—— 控制3508的ID：1-4电机，2006的1-4
************************************/
void CAN_0x200_SendData(CAN_HandleTypeDef* CAN_Num,int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

	uint8_t data[8];

	//数据格式详见说明书P32
	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;

	CAN_SendData(CAN_Num, CAN_ID_STD, 0x200, data);

}


/*************************************
* Method:    CAN_0x2FF_SendData
* Returns:   void
* Parameter: int16_t iq1，参数值。
* 说明：0x200报文的统一发送函数—— 控制6020的ID：5-7电机
************************************/
void CAN_0x2FF_SendData(CAN_HandleTypeDef* CAN_Num, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

	uint8_t data[8];

	//数据格式详见说明书P32
	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;

	CAN_SendData(CAN_Num, CAN_ID_STD, 0x2FF, data);

}




uint8_t FPS_Calculate(uint16_t deltaTime) { //FPS计算函数。
	return (1.0f / (double)(deltaTime)) * 1000.0f; // 别忘了先转换为浮点数，否则会有精度丢失
}


void Get_FPS(WorldTime_RxTypedef *time, uint8_t *FPS)  //获取当前系统时钟节拍并算出FPS
{
	time->WorldTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
	*FPS = FPS_Calculate(time->WorldTime - time->Last_WorldTime);
	time->Last_WorldTime = time->WorldTime;

}








