/**
  ******************************************************************************
  * @file    M3508_Motor.c
  * @author  -Yvfneg
  * @version V2.0
  * @date
  * @brief   M3508��ˢ���������C620�������Ӧ�ú����ӿ�
  ******************************************************************************
  */


#include "M3508_Motor.h"

M3508s_t M3508s[4];
#define  M3508_Amount 4

/**
  * @brief  ����M3508�������ֵ��id��Ϊ1~4��
  * @param  iqx (x:1~4) ��Ӧid�ŵ���ĵ���ֵ����Χ-16384~0~16384
  * @retval None
  */
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

	uint8_t data[8];

	//���ݸ�ʽ���˵����P32
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
  * @brief  ��CAN�����л�ȡM3508�����Ϣ
  * @param  RxMessage 	CAN���Ľ��սṹ��
  * @retval None
  */
void M3508_getInfo(CAN_RxTypedef RxMessage) {
	//����idȷ��
	if ((RxMessage.CAN_RxHeader.StdId < M3508_READID_START) || (RxMessage.CAN_RxHeader.StdId > M3508_READID_END))
		return;
	int32_t StdId;
	StdId = (int32_t)(RxMessage.CAN_RxHeader.StdId - M3508_READID_START);
	//������ݣ����ݸ�ʽ���C620���˵����P33
	M3508s[StdId].realAngle = (uint16_t)(RxMessage.CAN_RxMessage[0] << 8 | RxMessage.CAN_RxMessage[1]);
	M3508s[StdId].realSpeed = (int16_t)(RxMessage.CAN_RxMessage[2] << 8 | RxMessage.CAN_RxMessage[3]);
	M3508s[StdId].realCurrent = (int16_t)(RxMessage.CAN_RxMessage[4] << 8 | RxMessage.CAN_RxMessage[5]);
	M3508s[StdId].temperture = RxMessage.CAN_RxMessage[6];

	//֡��ͳ�ƣ����ݸ��±�־λ
	M3508s[StdId].InfoUpdateFrame++;
	M3508s[StdId].InfoUpdateFlag = 1;
}





