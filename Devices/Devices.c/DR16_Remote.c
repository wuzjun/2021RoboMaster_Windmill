/**
  ******************************************************************************
  * @file    DR16_Remote.c
  * @author  -Yvfneg
  * @version V1.0
  * @date
  * @brief   DR16 Զ�̿��ƽӿ�
  ******************************************************************************
  */



#include "DR16_Remote.h"
#include "bldc_can.h"


  /*�궨�����*/
uint8_t DR16Buffer[DR16BufferNumber];

/*�ڵ��ú���(�����⿪��)*/
void DR16_ReInit(void);
void DR16_Process(uint8_t *pData);
void DR16_Handler(UART_HandleTypeDef *huart);


/*ң�����ṹ���ʼ��*/
DR16_t DR16 = DR16_GroundInit;
DR16_Export_Data_t DR16_Export_data;


/**
  * @Data    2019-02-19 15:46
  * @brief   DR16���ݳ�ʼ��
  * @param   void
  * @retval  void
  */
void DR16_ReInit(void)
{
	DR16.rc.ch0 = 0;
	DR16.rc.ch1 = 0;
	DR16.rc.ch2 = 0;
	DR16.rc.ch3 = 0;
	DR16.rc.s_left = 0;
	DR16.rc.s_right = 0;
	DR16.mouse.x = 0;
	DR16.mouse.y = 0;
	DR16.mouse.z = 0;
	DR16.mouse.keyLeft = 0;
	DR16.mouse.keyRight = 0;
	DR16.keyBoard.key_code = 0;
	DR16.rc.ch4_DW = 0;

}

void RemoteControl_RC_Update(void) {

	//���ö����Ŀ��ֵ��

	if (Robot.Sport_ChassisWorkMode == ChassisWorkMode_Manual)//�ֶ�ģʽ
	{
		DR16_Export_data.Robot_TargetValue.Yaw_Value = DR16.rc.ch0 *10.0f;
	}
	else
	{
		DR16_Export_data.Robot_TargetValue.Yaw_Value = 0.0f;
	}

}


void RemoteControl_Update(void) { //����ң�������յĿ������ݡ�

	switch (Robot.ControlSource)
	{
	case ControlSource_RC:		//ң��������ģʽ��ʼ��
		Robot_Enable();
		if (Robot.WorkStatus == WorkStatus_Normal) //�����˿�����ʼ����ϲŽ��봦��
		{
			RemoteControl_RC_Update();
		}

		break;
	case ControlSource_Stop:
		/*SetWorkStatus(Prepare_Status);*/
		Robot_Disable();
		break;
	default:
		break;

	}
}




void RemoteMode_Update(void)
{

	switch (DR16.rc.s_left)
	{
	case RemotePole_UP: //-----�󲦸� Ϊ��--------------PC���ơ�������
		Robot_Disable();
		Time_rad = -1.6624f;
		Robot_ChangeControlSource(ControlSource_Stop);

		break;
	case RemotePole_MID://-------�󲦸� Ϊ��	------------ң��������ģʽ

		switch (DR16.rc.s_right)
		{
		case RemotePole_UP:
			Robot.Sport_ChassisWorkMode = ChassisWorkMode_Auto;
			Robot.Sport_CloudWorkMode = CloudWorkMode_Negative;
			break;
		case RemotePole_MID://����====����
			Robot.Sport_ChassisWorkMode = ChassisWorkMode_Auto;
			Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
			break;

		case RemotePole_DOWM://����====����

			Robot.Sport_ChassisWorkMode = ChassisWorkMode_Manual;
			Robot.Sport_CloudWorkMode = CloudWorkMode_Disable;
			Time_rad = -1.6624f;

			break;
		}
		//���Ŀ�����Դ��
		Robot_ChangeControlSource(ControlSource_RC);
		break;


	case RemotePole_DOWM://----------�󲦸� Ϊ��

		Robot_Disable();
		Time_rad = -1.6624f;
		Robot_ChangeControlSource(ControlSource_Stop);
		break;
	}

}

/**
  * @Data    2019-03-23 20:07
  * @brief   DR16ң�������뺯��
  * @param   uint8_t *pData
  * @retval  void
  */
void DR16_Process(uint8_t *pData)
{
	if (pData == NULL)
	{
		return;
	}
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	DR16.keyBoard.key_code = pData[14] | (pData[15] << 8);

	//your control code ��.
	DR16.rc.ch4_DW = (pData[16] | (pData[17] << 8)) & 0x07FF;
	DR16.infoUpdateFrame++;
	DR16.rc.ch0 -= 1024;
	DR16.rc.ch1 -= 1024;
	DR16.rc.ch2 -= 1024;
	DR16.rc.ch3 -= 1024;
	DR16.rc.ch4_DW -= 1024;

	/* prevent remote control zero deviation */
	if (DR16.rc.ch0 <= 20 && DR16.rc.ch0 >= -20)
		DR16.rc.ch0 = 0;
	if (DR16.rc.ch1 <= 20 && DR16.rc.ch1 >= -20)
		DR16.rc.ch1 = 0;
	if (DR16.rc.ch2 <= 20 && DR16.rc.ch2 >= -20)
		DR16.rc.ch2 = 0;
	if (DR16.rc.ch3 <= 20 && DR16.rc.ch3 >= -20)
		DR16.rc.ch3 = 0;
	if (DR16.rc.ch4_DW <= 20 && DR16.rc.ch4_DW >= -20)
		DR16.rc.ch4_DW = 0;

	DR16_Export_data.ControlSwitch.Left = (RemotePole_e)DR16.rc.s_left;
	DR16_Export_data.ControlSwitch.Right = (RemotePole_e)DR16.rc.s_right;

	RemoteMode_Update();//�Կ�����Դ���˶�ģʽ���и��¡�
	RemoteControl_Update();//����������˶�Ŀ��ֵ��
}



/**
  * @Data    2019-03-23 20:07
* @brief   ��ȡ��Ӧhdma����ķ��ͺ�ʣ���ֽ�����
  * @param   uint8_t *pData
  * @retval  void
  */
uint16_t DMA_GET_COUNTER(DMA_Stream_TypeDef* __HAL_DMA_Get)
{
	return ((uint16_t)(__HAL_DMA_Get->NDTR));
}


/*һ���Ƕ�ȡSR�Ĵ�����һ���Ƕ�ȡ��Ӧ��CR���ƼĴ���*/
		/*���������CR����SR���������Ҫ��ȡ��Ӧ�ı�־λ�Ļ����ȿ��Դ�CR��ȡҲ���Դ�SR��ȡ*/
		/*__HAL_UART_GET_FLAG�ǻ�ȡSR�Ĵ�������������Ҳ���Ƕ�ȡ��CR����������֮��Ķ�Ӧ״̬*/
		/*__HAL_UART_GET_IT_SOURCE��ֱ�Ӷ�ȡ���ƼĴ��������CRx��־λ�����*/
		/*�����DMA_GET_COUNTER�ǻ�ȡ��û����ȥ���ַ���������֮ǰ�Ĳ�ͬ*/
		/*��������������ĶԱȣ�����ϸ�Ķ�*/
/**
  * @Data    2019-03-23 20:07
  * @brief   DR16������
  * @param   uint8_t *pData
  * @retval  void
  */

void DR16_Handler(UART_HandleTypeDef *huart)
{

	if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) &&
		__HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);
		__HAL_DMA_DISABLE(huart->hdmarx);

		//if(DR16BufferNumber - DMA_GET_COUNTER(huart->hdmarx->Instance) == DR16BufferTruthNumber)
		if (__HAL_DMA_GET_COUNTER(huart->hdmarx) == DR16BufferLastNumber)
		{
			DR16.DR16_Process(DR16Buffer);
		}

		__HAL_DMA_SET_COUNTER(huart->hdmarx, DR16BufferNumber);
		__HAL_DMA_ENABLE(huart->hdmarx);
	}
}
