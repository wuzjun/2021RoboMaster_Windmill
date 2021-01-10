#ifndef _HANDLE_H
#define _HANDLE_H

#include "RTOSInclude.h"

#define _HANDLE_EXT extern

//队列句柄
_HANDLE_EXT  osMessageQId 	xQueueCanReceive;
_HANDLE_EXT  osMessageQId 	xQueueCanReceive_2;

//二值信号量句柄
//_HANDLE_EXT  SemaphoreHandle_t  xBinarySemaphore;

//互斥信号量
//_HANDLE_EXT QueueHandle_t xMutex;

#endif








