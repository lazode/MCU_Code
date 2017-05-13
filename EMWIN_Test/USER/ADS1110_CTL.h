#ifndef _ADS1110_H
#define _ADS1110_H

#endif

#define ADS1110_ADDR (1<<6 + 1<<3)
#define WRITEDATA   1
#define READDATA    0

#define SINGLE	    1
#define CONTINUOUS  0

#define RATE_240SPS 0
#define RATE_60SPS  1
#define RATE_30SPS  2
#define RATE_15SPS  3
 
#define PGA_GAIN_1  0
#define PGA_GAIN_2  1
#define PGA_GAIN_4  2
#define PGA_GAIN_8  3

#define ACK 	    1
#define NACK	    0

#define DATA		1
#define BYTE		0

#include "stm32f10x.h"
#include "myiic.h"

void ADS1110_Init(void);
int  ADS1110_ReadData(void);
int ADS1110_WriteData(unsigned char Mode, unsigned char Data_Rate, unsigned char PGA_Gain);
