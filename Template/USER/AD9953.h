#ifndef	_AD9953_H

#define	_AD9953_H

#define AD9953_PORT	GPIOC
#define	DATA_PIN	GPIO_PIN_8
#define	CLK_PIN		GPIO_PIN_9

#define	RESET_PIN	GPIO_PIN_7
#define	UPDATE_PIN	GPIO_PIN_6

#define	CFR1_ADDR	0x00
#define	CFR2_ADDR	0x01
#define FTW0_ADDR	0x04
#define	POW0_ADDR	0X05
#define	FTW1_ADDR	0X06

#define WRITE		0
#define	READ		1
#define	isPLL		numPLL

#include "sys.h"
#include "delay.h"

static int numPLL = 0;

static uint32_t CFR0;
static uint32_t CFR1;


void Init_AD9953(void);
void Reset_AD9953(void);

int  WriteRead_AD9953(unsigned char WR, unsigned char addr, int data, int dataWidth);
void WriteFTW_AD9953(int frequence);	
void WritePOW_AD9953(int phase);

void SetPLL_AD9953(int multi);


int  Read_AD9953(unsigned char addr, int dataWidth);
void GPIO_Config(void);

#endif

