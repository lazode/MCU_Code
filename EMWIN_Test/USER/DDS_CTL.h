#ifndef 	DDS_CTL_H

#define 	DDS_CTL_H

	


#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "system_stm32f10x.h"

#include "delay.h"



void write_dds(double dds);
void init_dds(void);


void GPIO_Config(void);
	
void Delay_n(unsigned char n);


void ad9835send(u8 data);
void ad9835setfreq(float x);

#endif
