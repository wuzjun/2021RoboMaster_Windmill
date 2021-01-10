/**
  ******************************************************************************
  * @file    BSP_TIM.c
  * @author  Wu Zhuojun
  * @version V1.0
  * @date
  * @brief   TIMº¯Êý±àÐ´
  ******************************************************************************
  */


 /* =========================== Include Begin =========================== */
#include "BSP_TIM.h"
/* =========================== Include End=========================== */

/* =========================== In_Function Begin =========================== */
/* =========================== In_Function End=========================== */

/* =========================== Variable Begin =========================== */

/* =========================== Variable End=========================== */

/* =========================== Macor Begin =========================== */
/* =========================== Macor End=========================== */




/**
  * @brief  Sets the TIMx Capture Compare1 Register value
  * @param  TIMx: where x can be 1 to 14 except 6 and 7, to select the TIM peripheral.
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1)
{
  /* Set the Capture Compare1 Register value */
  TIMx->CCR1 = Compare1;
}


/**
  * @brief  Sets the TIMx Capture Compare2 Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM 
  *         peripheral.
  * @param  Compare2: specifies the Capture Compare2 register new value.
  * @retval None
  */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2)
{
  /* Set the Capture Compare2 Register value */
  TIMx->CCR2 = Compare2;
}


/**
  * @brief  Sets the TIMx Capture Compare3 Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  Compare3: specifies the Capture Compare3 register new value.
  * @retval None
  */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3)
{
  /* Set the Capture Compare2 Register value */
  TIMx->CCR2 = Compare3;
}
