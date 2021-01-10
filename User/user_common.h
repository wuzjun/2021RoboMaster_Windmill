#ifndef __USER_COMMON_H
#define __USER_COMMON_H
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <Math.h>
#include <string.h>  //机器人的默认配置文件。
#include "stm32f4xx_hal.h"
#include "typedef.h"


#include "BSP_USART.h"
#include "BSP_TIM.h"
#include "BSP_CAN.h"


//Algorithm
#include "PID.h"
#include "AddMath.h"
#include "SpeedRamp.h"

//Devices
#include "DR16_Remote.h"
#include "Debug_DataScope.h"
#include "M3508_Motor.h"


//Apps
#include "Robot_control.h"
#include "Monitor_RM_CAN.h"
#include "Chassis_control.h"

#endif


