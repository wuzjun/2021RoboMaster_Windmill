/**
  ******************************************************************************
  * @file    BSP_CAN.c
  * @author  Wu Zhuojun
  * @version V1.0
  * @date
  * @brief   can函数编写
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
CAN_t Monitor_CAN2; //用于线路检测
/* =========================== Variable End=========================== */

/* =========================== Macor Begin =========================== */
/* =========================== Macor End=========================== */

/**
  * @Data   2019-01-07
  * @brief  CAN筛选器初始化
  * @param   进入参数
  * @retval  返回参数
  */
void CAN1_FILTER_Init(CAN_FilterTypeDef CAN1_Filter)
{
	CAN1_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;         //筛选器被关联到FIFO0
	CAN1_Filter.FilterBank = 0;                                                              //筛选器组0
	CAN1_Filter.SlaveStartFilterBank = 0;
	CAN1_Filter.FilterMode = CAN_FILTERMODE_IDMASK;           //工作在ID掩码模式
	CAN1_Filter.FilterScale = CAN_FILTERSCALE_32BIT;                 //筛选器位宽为单个32位。
	CAN1_Filter.FilterActivation = CAN_FILTER_ENABLE;               //使能筛选器
		/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
	CAN1_Filter.FilterIdHigh = 0x0000;                                                //要筛选的ID高位 
	CAN1_Filter.FilterIdLow = 0x0000;                                                //要筛选的ID低位 
	CAN1_Filter.FilterMaskIdHigh = 0x0000;                                     //筛选器高16位每位不须匹配
	CAN1_Filter.FilterMaskIdLow = 0x0000;                                      //筛选器低16位每位不须匹配
	HAL_CAN_ConfigFilter(&hcan1, &CAN1_Filter);
}


/**
  * @Data   2019-01-07
  * @brief  CAN筛选器初始化
  * @param   进入参数
  * @retval  返回参数
  */
//void CAN2_FILTER_Init(CAN_FilterTypeDef CAN2_Filter)
//{
//	CAN2_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;         //筛选器被关联到FIFO0
//	CAN2_Filter.FilterBank = 0;                                                              //筛选器组0
//	CAN2_Filter.SlaveStartFilterBank = 0;
//	CAN2_Filter.FilterMode = CAN_FILTERMODE_IDMASK;           //工作在ID掩码模式
//	CAN2_Filter.FilterScale = CAN_FILTERSCALE_32BIT;                 //筛选器位宽为单个32位。
//	CAN2_Filter.FilterActivation = CAN_FILTER_ENABLE;               //使能筛选器
//		/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
//	CAN2_Filter.FilterIdHigh = 0x0000;                                                //要筛选的ID高位 
//	CAN2_Filter.FilterIdLow = 0x0000;                                                //要筛选的ID低位 
//	CAN2_Filter.FilterMaskIdHigh = 0x0000;                                     //筛选器高16位每位不须匹配
//	CAN2_Filter.FilterMaskIdLow = 0x0000;                                      //筛选器低16位每位不须匹配
//	HAL_CAN_ConfigFilter(&hcan2, &CAN2_Filter);
//}


/**
  * @Data   2019-01-07
  * @brief   can1中断启动
  * @param   进入参数
  * @retval  返回参数
  */
void CAN1_IT_Init(void)
{
	/*使能滤波器*/
	CAN1_FILTER_Init(CAN1_Filter);
	/*启用CAN*/
	HAL_CAN_Start(&hcan1);
	/*使能CAN的IT中断*/
	__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);         //  CAN_IT_FMP0

}


/**
  * @Data   2019-01-07
  * @brief   can2中断启动
  * @param   进入参数
  * @retval  返回参数
  */
//void CAN2_IT_Init(void)
//{
//	/*使能滤波器*/
//	CAN2_FILTER_Init(CAN2_Filter);
//	/*启用CAN*/
//	HAL_CAN_Start(&hcan2);
//	/*使能CAN的IT中断*/
//	__HAL_CAN_ENABLE_IT(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);         //  CAN_IT_FMP0

//}


/**
  * @brief  CAN发送数据
  * @param  CANx 		CAN编号
  * 		id_type ·	id类型 CAN_ID_STD， CAN_ID_EXT
  *			id			id号
  * 		data[8]		8个数据
  * @retval None
  */
void CAN_SendData(CAN_HandleTypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8])  
{	  
	CAN_TxHeaderTypeDef TxMessage;
	
	if(id_type == CAN_ID_STD){
		TxMessage.StdId = id;						 
	}
	else{
		TxMessage.ExtId = id;					 //ID号
	}
	
	TxMessage.IDE = id_type;					 //ID类型
	TxMessage.RTR = CAN_RTR_DATA;				 //发送的为数据
	TxMessage.DLC = 0x08;						 //数据长度为8字节
	TxMessage.TransmitGlobalTime = DISABLE;
	
	HAL_CAN_AddTxMessage(CANx,&TxMessage,data,(uint32_t*)CAN_TX_MAILBOX0);
}



/*-----------------------------------file of end------------------------------*/


