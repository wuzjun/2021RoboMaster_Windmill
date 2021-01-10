#ifndef __SpeedRamp_H
#define __SpeedRamp_H


#include "user_common.h"

typedef struct
{
	float count;//当前的总速度值
	float rate;//每一次叠加的速度值
	int16_t mincount;
	int16_t maxcount;
}SpeedRamp_t;
void CountReset(SpeedRamp_t *SpeedRamp);
int16_t SpeedRampCalc(SpeedRamp_t *SpeedRamp);

#endif 




