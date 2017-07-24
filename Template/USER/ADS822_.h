#ifndef		_ADS822_H
#define 	_ADS822_H

#define 	D0_PIN		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)
#define 	D1_PIN		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)
#define 	D2_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)
#define 	D3_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)
#define 	D4_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)
#define 	D5_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9)
#define 	D6_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)
#define 	D7_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)
#define 	D8_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)
#define 	D9_PIN		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)
#define		CLK_PIN		GPIO_PIN_1
#define		CLK_PORT	GPIOB

#define 	PGA202_PORT	GPIOA
#define	 	PGA202_A0  	GPIO_PIN_1
#define 	PGA202_A1  	GPIO_PIN_2


#include "sys.h"
#include "delay.h"
//#include "stm32f4xx_hal.h"

int Read_ADS822(void);
void  ADS822_Init(void);

void  Amp_Init(void);
void  Amp_SetGain(int Gain);

short data_map(int data, int min, int max, int dest_Min, int dest_Max);

#endif
