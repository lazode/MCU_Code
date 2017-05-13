#ifndef _AMPGAIN_H
#define _AMPGAIN_H

#define PGA202_PORT	GPIOA
#define PGA202_A0  	GPIO_Pin_1
#define PGA202_A1  	GPIO_Pin_2

#endif

#include "stm32f10x.h"

void Amp_Init(void);
void Amp_SetGain(int Gain);
