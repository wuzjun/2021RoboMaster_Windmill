#include "Monitor_RM_CAN.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"




/*************************************
* Method:    CAN_0x1FF_SendData
* Returns:   void
* Parameter: int16_t iq1������ֵ��
* ˵����0x1FF���ĵ�ͳһ���ͺ������� ����3508��ID��5-8�����6020��1-4��2006��5-8
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
* Parameter: int16_t iq1������ֵ��
* ˵����0x200���ĵ�ͳһ���ͺ������� ����3508��ID��1-4�����2006��1-4
************************************/
void CAN_0x200_SendData(CAN_HandleTypeDef* CAN_Num,int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

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

	CAN_SendData(CAN_Num, CAN_ID_STD, 0x200, data);

}


/*************************************
* Method:    CAN_0x2FF_SendData
* Returns:   void
* Parameter: int16_t iq1������ֵ��
* ˵����0x200���ĵ�ͳһ���ͺ������� ����6020��ID��5-7���
************************************/
void CAN_0x2FF_SendData(CAN_HandleTypeDef* CAN_Num, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4) {

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

	CAN_SendData(CAN_Num, CAN_ID_STD, 0x2FF, data);

}




uint8_t FPS_Calculate(uint16_t deltaTime) { //FPS���㺯����
	return (1.0f / (double)(deltaTime)) * 1000.0f; // ��������ת��Ϊ��������������о��ȶ�ʧ
}


void Get_FPS(WorldTime_RxTypedef *time, uint8_t *FPS)  //��ȡ��ǰϵͳʱ�ӽ��Ĳ����FPS
{
	time->WorldTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
	*FPS = FPS_Calculate(time->WorldTime - time->Last_WorldTime);
	time->Last_WorldTime = time->WorldTime;

}








