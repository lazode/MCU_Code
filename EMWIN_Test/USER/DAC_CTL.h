#ifndef 	DACCTL 
#define 	DACCTL

#include "stm32f10x_gpio.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_rcc.h"

#define		VREF 	5

void DAC_Config(void);
void DAC_CTL(float Vol);

void DAC_Drive(float Vout);

void Dac1_Init(void);
void Dac1_Set_Vol(u16 vol);

#endif
