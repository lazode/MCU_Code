#ifndef	_FREQMEASURE_H
#define _FREQMEASURE_H

#endif


#include "stm32f10x.h"
#include "stm32f10x_exti.h"

#include "DIALOG.h"



void FreqMeasure_Init(void);
int FreqMeasure(void);


void TIM2_Cap_Init(u16 arr,u16 psc);
//void TIM2_IRQHandler(void);

