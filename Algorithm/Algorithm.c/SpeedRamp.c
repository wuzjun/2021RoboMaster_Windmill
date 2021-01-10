#include "SpeedRamp.h"


/**
	* @brief  斜坡函数计算
  * @param	斜坡函数结构体
  * @retval None
  */
 int16_t SpeedRampCalc(SpeedRamp_t *SpeedRamp)
{

	SpeedRamp->count += SpeedRamp->rate;
	VAL_LIMIT(SpeedRamp->count,
		SpeedRamp->mincount,
		SpeedRamp->maxcount);

	return SpeedRamp->count;
}


/**
	* @brief  斜坡计数值归零
  * @param	斜坡函数结构体
  * @retval None
  */
 void CountReset(SpeedRamp_t *SpeedRamp)
{
	 
	 if (abs(SpeedRamp->count)<abs(SpeedRamp->rate))
	 {
		 SpeedRamp->count = 0;
	 }
	 else
	 {

		SpeedRamp->count -= SpeedRamp->count*0.2f;
	 }
	//if (SpeedRamp->count > abs(SpeedRamp->rate))
	//{
	//	SpeedRamp->count -= abs(SpeedRamp->rate);
	//}
	//else if (SpeedRamp->count < -abs(SpeedRamp->rate))
	//{
	//	SpeedRamp->count += abs(SpeedRamp->rate);
	//}
	//else
	//{
	//	
	//}

}
