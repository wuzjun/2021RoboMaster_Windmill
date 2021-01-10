/**
  ******************************************************************************
  * @file    BSP_USART.c
  * @author  Wu Zhuojun
  * @version V1.0
  * @date
  * @brief   USART������д
  ******************************************************************************
  */
/* =========================== Include Begin =========================== */
#include "BSP_USART.h"
#include "DR16_Remote.h"
/* =========================== Include End=========================== */

/* =========================== In_Function Begin =========================== */

/*�ڵ��ú���*/
static int USART_Receive_DMA_NO_IT(UART_HandleTypeDef* huart, uint8_t* pData, uint32_t Size);
/* =========================== In_Function End=========================== */

/* =========================== Variable Begin =========================== */

/* =========================== Variable End=========================== */

/* =========================== Macor Begin =========================== */

/* =========================== Macor End=========================== */

/**
  * @Data    2019-02-19 15:46
  * @brief   DR16�жϳ�ʼ��
  * @param   void
  * @retval  void
  */
void DR16_USART1_IT_Init(void)
{
	/*��ձ�־λȻ��ʹ��USART���ж�*/
	__HAL_UART_CLEAR_IDLEFLAG(&huart1);
	__HAL_UART_ENABLE(&huart1);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	/*����DMA���䣨���ǲ�����DMA�жϣ�*/
	USART_Receive_DMA_NO_IT(&huart1,DR16Buffer,DR16BufferNumber);

}





/**
  * @Data    2020-08-27 18:26
  * @brief   ����6����
  * @param   void
  * @retval  void
  */
void USART6_IT_Init(void)
{
	/*��ձ�־λȻ��ʹ��USART���ж�*/
	__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	__HAL_UART_ENABLE(&huart6);
}





/**
  * @Data    2019-02-19 15:46
  * @brief   USART_DMA���տ������ض���
  * @param   void
  * @retval  void
  */
static int USART_Receive_DMA_NO_IT(UART_HandleTypeDef* huart, uint8_t* pData, uint32_t Size)
{

		/*��⵱ǰhuart״̬*/
		if(huart->RxState == HAL_UART_STATE_READY)
		{
			/*����ĵ�ַ��������������Ļ�*/
			if((pData == NULL) || (Size == 0))
			{
					return HAL_ERROR;
			}
			
			/*huart�����Ӧ��Rx�����ض���*/
			huart->pRxBuffPtr = pData;
			huart->RxXferSize = Size;
			huart->ErrorCode = HAL_UART_ERROR_NONE;
			
			/*����huart1�ϵ�RX_DMA*/
			HAL_DMA_Start(huart->hdmarx,(uint32_t)&huart->Instance->DR,(uint32_t)pData,Size);
			
			/*ֻ������ӦDMA�����Rx���ܣ�����ǿ���Tx�Ļ�����USART_CR3_DMAT��*/
			SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);
			
			
		}
		else
		{
			return HAL_BUSY;
		}

		return HAL_OK;
}




/*-----------------------------------file of end------------------------------*/
