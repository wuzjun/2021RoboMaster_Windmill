/**
  ******************************************************************************
  * @file    BSP_CAN.c
  * @author  Wu Zhuojun
  * @version V1.0
  * @date
  * @brief   can������д
  ******************************************************************************
  */
 /* =========================== Include Begin =========================== */
#include "BSP_CAN.h"
/* =========================== Include End=========================== */

/* =========================== In_Function Begin =========================== */
/* =========================== In_Function End=========================== */

/* =========================== Variable Begin =========================== */
CAN_FilterTypeDef CAN1_Filter;
CAN_FilterTypeDef CAN2_Filter;

CAN_t Monitor_CAN1;
CAN_t Monitor_CAN2; //������·���
/* =========================== Variable End=========================== */

/* =========================== Macor Begin =========================== */
/* =========================== Macor End=========================== */

/**
  * @Data   2019-01-07
  * @brief  CANɸѡ����ʼ��
  * @param   �������
  * @retval  ���ز���
  */
void CAN1_FILTER_Init(CAN_FilterTypeDef CAN1_Filter)
{
	CAN1_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;         //ɸѡ����������FIFO0
	CAN1_Filter.FilterBank = 0;                                                              //ɸѡ����0
	CAN1_Filter.SlaveStartFilterBank = 0;
	CAN1_Filter.FilterMode = CAN_FILTERMODE_IDMASK;           //������ID����ģʽ
	CAN1_Filter.FilterScale = CAN_FILTERSCALE_32BIT;                 //ɸѡ��λ��Ϊ����32λ��
	CAN1_Filter.FilterActivation = CAN_FILTER_ENABLE;               //ʹ��ɸѡ��
		/* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */
	CAN1_Filter.FilterIdHigh = 0x0000;                                                //Ҫɸѡ��ID��λ 
	CAN1_Filter.FilterIdLow = 0x0000;                                                //Ҫɸѡ��ID��λ 
	CAN1_Filter.FilterMaskIdHigh = 0x0000;                                     //ɸѡ����16λÿλ����ƥ��
	CAN1_Filter.FilterMaskIdLow = 0x0000;                                      //ɸѡ����16λÿλ����ƥ��
	HAL_CAN_ConfigFilter(&hcan1, &CAN1_Filter);
}


/**
  * @Data   2019-01-07
  * @brief  CANɸѡ����ʼ��
  * @param   �������
  * @retval  ���ز���
  */
//void CAN2_FILTER_Init(CAN_FilterTypeDef CAN2_Filter)
//{
//	CAN2_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;         //ɸѡ����������FIFO0
//	CAN2_Filter.FilterBank = 0;                                                              //ɸѡ����0
//	CAN2_Filter.SlaveStartFilterBank = 0;
//	CAN2_Filter.FilterMode = CAN_FILTERMODE_IDMASK;           //������ID����ģʽ
//	CAN2_Filter.FilterScale = CAN_FILTERSCALE_32BIT;                 //ɸѡ��λ��Ϊ����32λ��
//	CAN2_Filter.FilterActivation = CAN_FILTER_ENABLE;               //ʹ��ɸѡ��
//		/* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */
//	CAN2_Filter.FilterIdHigh = 0x0000;                                                //Ҫɸѡ��ID��λ 
//	CAN2_Filter.FilterIdLow = 0x0000;                                                //Ҫɸѡ��ID��λ 
//	CAN2_Filter.FilterMaskIdHigh = 0x0000;                                     //ɸѡ����16λÿλ����ƥ��
//	CAN2_Filter.FilterMaskIdLow = 0x0000;                                      //ɸѡ����16λÿλ����ƥ��
//	HAL_CAN_ConfigFilter(&hcan2, &CAN2_Filter);
//}


/**
  * @Data   2019-01-07
  * @brief   can1�ж�����
  * @param   �������
  * @retval  ���ز���
  */
void CAN1_IT_Init(void)
{
	/*ʹ���˲���*/
	CAN1_FILTER_Init(CAN1_Filter);
	/*����CAN*/
	HAL_CAN_Start(&hcan1);
	/*ʹ��CAN��IT�ж�*/
	__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);         //  CAN_IT_FMP0

}


/**
  * @Data   2019-01-07
  * @brief   can2�ж�����
  * @param   �������
  * @retval  ���ز���
  */
//void CAN2_IT_Init(void)
//{
//	/*ʹ���˲���*/
//	CAN2_FILTER_Init(CAN2_Filter);
//	/*����CAN*/
//	HAL_CAN_Start(&hcan2);
//	/*ʹ��CAN��IT�ж�*/
//	__HAL_CAN_ENABLE_IT(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);         //  CAN_IT_FMP0

//}


/**
  * @brief  CAN��������
  * @param  CANx 		CAN���
  * 		id_type ��	id���� CAN_ID_STD�� CAN_ID_EXT
  *			id			id��
  * 		data[8]		8������
  * @retval None
  */
void CAN_SendData(CAN_HandleTypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8])  
{	  
	CAN_TxHeaderTypeDef TxMessage;
	
	if(id_type == CAN_ID_STD){
		TxMessage.StdId = id;						 
	}
	else{
		TxMessage.ExtId = id;					 //ID��
	}
	
	TxMessage.IDE = id_type;					 //ID����
	TxMessage.RTR = CAN_RTR_DATA;				 //���͵�Ϊ����
	TxMessage.DLC = 0x08;						 //���ݳ���Ϊ8�ֽ�
	TxMessage.TransmitGlobalTime = DISABLE;
	
	HAL_CAN_AddTxMessage(CANx,&TxMessage,data,(uint32_t*)CAN_TX_MAILBOX0);
}



/*-----------------------------------file of end------------------------------*/


