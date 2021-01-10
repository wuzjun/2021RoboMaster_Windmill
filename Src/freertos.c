/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  /* USER CODE END Header */

  /* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "user_common.h"
#include "bldc_can.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osMessageQId 	xQueueCanReceive;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LED_TaskHandle;
osThreadId Task_CanMsgReceHandle;
osThreadId Task_ControlHandle;
osThreadId Task_CAL_TIMEHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LED(void const * argument);
void CanRecevices(void const * argument);
void ControlTask(void const * argument);
void Calculat_time(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	  //创造CAN接收队列
	xQueueCanReceive = xQueueCreate(10, sizeof(CAN_RxTypedef));
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* definition and creation of LED_Task */
	osThreadDef(LED_Task, LED, osPriorityIdle, 0, 128);
	LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

	/* definition and creation of Task_CanMsgRece */
	osThreadDef(Task_CanMsgRece, CanRecevices, osPriorityHigh, 0, 256);
	Task_CanMsgReceHandle = osThreadCreate(osThread(Task_CanMsgRece), NULL);

	/* definition and creation of Task_Control */
	osThreadDef(Task_Control, ControlTask, osPriorityIdle, 0, 128);
	Task_ControlHandle = osThreadCreate(osThread(Task_Control), NULL);

	/* definition and creation of Task_CAL_TIME */
	osThreadDef(Task_CAL_TIME, Calculat_time, osPriorityIdle, 0, 128);
	Task_CAL_TIMEHandle = osThreadCreate(osThread(Task_CAL_TIME), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
  /* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;)
	{
		Chassis_Init();
		//		vesc_can_set_current(ID,current);
		osDelay(3);
		Debug_addData(M3508s[0].realSpeed, 1);
		Debug_addData(M3508s[0].spd * 100, 2);
		Debug_addData(M3508s[0].rad_S, 3);
		Debug_show(3);
		//    osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LED */
/**
* @brief Function implementing the LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED */
void LED(void const * argument)
{
	/* USER CODE BEGIN LED */
	/* Infinite loop */
	for (;;)
	{
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		osDelay(1000);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
		osDelay(1000);
		//	 vesc_can_set_duty(6,0.2f);
	}
	/* USER CODE END LED */
}

/* USER CODE BEGIN Header_CanRecevices */
/**
* @brief Function implementing the Task_CanMsgRece thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CanRecevices */
void CanRecevices(void const * argument)
{
	/* USER CODE BEGIN CanRecevices */
	/* Infinite loop */
	CAN_RxTypedef CanReceiveData;
	uint32_t ID;
	for (;;)
	{		//等待队列不为空
		xQueueReceive(xQueueCanReceive, &CanReceiveData, portMAX_DELAY);
		ID = CanReceiveData.CAN_RxHeader.StdId;

		if (CanReceiveData.CANx == 1)
		{
			if (ID == M3508_READID_START)
			{
				M3508_getInfo(CanReceiveData);
			}

		}

		osDelay(1);
	}
	/* USER CODE END CanRecevices */
}

/* USER CODE BEGIN Header_ControlTask */
/**
* @brief Function implementing the Task_Control thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ControlTask */
void ControlTask(void const * argument)
{
	/* USER CODE BEGIN ControlTask */
	/* Infinite loop */
	for (;;)
	{

		Robot_control();
		osDelay(2);
	}
	/* USER CODE END ControlTask */
}

/* USER CODE BEGIN Header_Calculat_time */
/**
* @brief Function implementing the Tak_CAL_TIME thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Calculat_time */


void Calculat_time(void const * argument)
{
	/* USER CODE BEGIN Calculat_time */
	/* Infinite loop */
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t TimeIncrement = pdMS_TO_TICKS(1);
	for (;;)
	{
		Time_rad += 1.884f / 1000.0f;
		vTaskDelayUntil(&xLastWakeTime, TimeIncrement);
		//    osDelay(1);
	}
	/* USER CODE END Calculat_time */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
