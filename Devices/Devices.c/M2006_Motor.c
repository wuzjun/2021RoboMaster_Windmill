/**
  ******************************************************************************
  * @file    M2006_Motor.c
  * @author   Yvfneg
  * @version V1.0
  * @date
  * @brief   2006电机(拨弹用)，配套C610电调驱动应用函数接口
  ******************************************************************************
  */


#include "M2006_Motor.h"

M2006s_t M2006_Reload;//拨盘运输电机
M2006s_t *M2006_Array[] = { &M2006_Reload };
#define M2006_Amount  1 //对应上面。



/**
  * @brief  设置M2006电机电流值（id号为7）M2006与6623共用发送函数
  * @param  iqx (x:5) 对应id号电机的电流值，范围-10000~0~10000
  * @retval None
  */
void M2006_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

	uint8_t data[8];

	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;
	CAN_SendData(&hcan1, CAN_ID_STD, M2006_SENDID, data);

}


/**
  * @brief  从CAN报文中获取M2006电机信息
  * @param[in]  RxMessage 	CAN报文接收结构体
  * @retval None
  */


void M2006_getInfo(CAN_RxTypedef RxMessage) {
	//报文id确认
	uint32_t StdId;
	StdId = RxMessage.CAN_RxHeader.StdId - M2006_READID_START;
//	if (IndexOutofBounds(StdId, M2006_Amount))
//	{
//		Device_setAlertType(Alert_Times_SoftWare);
//		return;
//	}
	M2006_Array[StdId]->lastAngle = M2006_Array[StdId]->realAngle;
	//解包数据，数据格式详见C610电调说明书P9
	M2006_Array[StdId]->realAngle = (uint16_t)(RxMessage.CAN_RxMessage[0] << 8 | RxMessage.CAN_RxMessage[1]);
	M2006_Array[StdId]->realSpeed = (int16_t)(RxMessage.CAN_RxMessage[2] << 8 | RxMessage.CAN_RxMessage[3]);
	M2006_Array[StdId]->realTorque = (int16_t)(RxMessage.CAN_RxMessage[4] << 8 | RxMessage.CAN_RxMessage[5]);

	if (M2006_Array[StdId]->realAngle - M2006_Array[StdId]->lastAngle < -6000) {
		M2006_Array[StdId]->turnCount++;
	}

	if (M2006_Array[StdId]->lastAngle - M2006_Array[StdId]->realAngle < -6000) {
		M2006_Array[StdId]->turnCount--;
	}
	M2006_Array[StdId]->totalAngle = M2006_Array[StdId]->realAngle + (8192 * M2006_Array[StdId]->turnCount);
	M2006_Array[StdId]->lastAngle = M2006_Array[StdId]->realAngle;
	M2006_Array[StdId]->InfoUpdateFrame++;
	M2006_Array[StdId]->InfoUpdateFlag = 1;
}










