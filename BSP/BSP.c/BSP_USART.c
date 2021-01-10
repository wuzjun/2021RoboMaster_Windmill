/**
  ******************************************************************************
  * @file    BSP_USART.c
  * @author  Wu Zhuojun
  * @version V1.0
  * @date
  * @brief   USART函数编写
  ******************************************************************************
  */
/* =========================== Include Begin =========================== */
#include "BSP_USART.h"
#include "DR16_Remote.h"
/* =========================== Include End=========================== */

/* =========================== In_Function Begin =========================== */

/*内调用函数*/
static int USART_Receive_DMA_NO_IT(UART_HandleTypeDef* huart, uint8_t* pData, uint32_t Size);
/* =========================== In_Function End=========================== */

/* =========================== Variable Begin =========================== */

/* =========================== Variable End=========================== */

/* =========================== Macor Begin =========================== */

/* =========================== Macor End=========================== */

/**
  * @Data    2019-02-19 15:46
  * @brief   DR16中断初始化
  * @param   void
  * @retval  void
  */
void DR16_USART1_IT_Init(void)
{
	/*清空标志位然后使能USART的中断*/
	__HAL_UART_CLEAR_IDLEFLAG(&huart1);
	__HAL_UART_ENABLE(&huart1);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	/*开启DMA传输（但是不开启DMA中断）*/
	USART_Receive_DMA_NO_IT(&huart1,DR16Buffer,DR16BufferNumber);

}





/**
  * @Data    2020-08-27 18:26
  * @brief   串口6启动
  * @param   void
  * @retval  void
  */
void USART6_IT_Init(void)
{
	/*清空标志位然后使能USART的中断*/
	__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	__HAL_UART_ENABLE(&huart6);
}





/**
  * @Data    2019-02-19 15:46
  * @brief   USART_DMA接收开启和重定向
  * @param   void
  * @retval  void
  */
static int USART_Receive_DMA_NO_IT(UART_HandleTypeDef* huart, uint8_t* pData, uint32_t Size)
{

		/*检测当前huart状态*/
		if(huart->RxState == HAL_UART_STATE_READY)
		{
			/*输入的地址或者数据有问题的话*/
			if((pData == NULL) || (Size == 0))
			{
					return HAL_ERROR;
			}
			
			/*huart里面对应的Rx变量重定向*/
			huart->pRxBuffPtr = pData;
			huart->RxXferSize = Size;
			huart->ErrorCode = HAL_UART_ERROR_NONE;
			
			/*开启huart1上的RX_DMA*/
			HAL_DMA_Start(huart->hdmarx,(uint32_t)&huart->Instance->DR,(uint32_t)pData,Size);
			
			/*只开启对应DMA上面的Rx功能（如果是开启Tx的话就是USART_CR3_DMAT）*/
			SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);
			
			
		}
		else
		{
			return HAL_BUSY;
		}

		return HAL_OK;
}




/*-----------------------------------file of end------------------------------*/
