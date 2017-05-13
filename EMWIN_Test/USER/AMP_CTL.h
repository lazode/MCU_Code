#ifndef		AMP_H
#define 	AMP_H



#define 	GAIN_VOLTAG 	80.0

#include "stm32f10x_gpio.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_rcc.h"

void AMP_Init(void);

void AMP_CTL(unsigned char Gain);


void DAC1_CTL(uint16_t Data);
void DAC2_CTL(uint16_t Data);

#endif
