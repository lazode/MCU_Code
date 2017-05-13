#ifndef 	FILTER_H
#define 	FILTER_H

#endif

#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"


void filter_Config(void);

void filter_CTL(u16 Fre);


//根据传入的频率输出对应的时钟
void Pulse_Init(unsigned int Frequency);


