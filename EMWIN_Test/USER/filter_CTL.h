#ifndef 	FILTER_H
#define 	FILTER_H

#endif

#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"


void filter_Config(void);

void filter_CTL(u16 Fre);


//���ݴ����Ƶ�������Ӧ��ʱ��
void Pulse_Init(unsigned int Frequency);


