/**
  ******************************************************************************
  * @file    M3508_Motor.c
  * @author  -Yvfneg
  * @version V2.0
  * @date
  * @brief   M3508无刷电机，配套C620电调驱动应用函数接口
  ******************************************************************************
  */


#include "M3508_Motor.h"

M3508s_t M3508s[4];
#define  M3508_Amount 4

/**
  * @brief  设置M3508电机电流值（id号为1~4）
  * @param  iqx (x:1~4) 对应id号电机的电流值，范围-16384~0~16384
  * @retval None
  */
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

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

	CAN_SendData(&hcan1, CAN_ID_STD, M3508_SENDID, data);

}



/**
  * @brief  从CAN报文中获取M3508电机信息
  * @param  RxMessage 	CAN报文接收结构体
  * @retval None
  */
void M3508_getInfo(CAN_RxTypedef RxMessage) {
	//报文id确认
	if ((RxMessage.CAN_RxHeader.StdId < M3508_READID_START) || (RxMessage.CAN_RxHeader.StdId > M3508_READID_END))
		return;
	int32_t StdId;
	StdId = (int32_t)(RxMessage.CAN_RxHeader.StdId - M3508_READID_START);
	//解包数据，数据格式详见C620电调说明书P33
	M3508s[StdId].realAngle = (uint16_t)(RxMessage.CAN_RxMessage[0] << 8 | RxMessage.CAN_RxMessage[1]);
	M3508s[StdId].realSpeed = (int16_t)(RxMessage.CAN_RxMessage[2] << 8 | RxMessage.CAN_RxMessage[3]);
	M3508s[StdId].realCurrent = (int16_t)(RxMessage.CAN_RxMessage[4] << 8 | RxMessage.CAN_RxMessage[5]);
	M3508s[StdId].temperture = RxMessage.CAN_RxMessage[6];

	//帧率统计，数据更新标志位
	M3508s[StdId].InfoUpdateFrame++;
	M3508s[StdId].InfoUpdateFlag = 1;
}





