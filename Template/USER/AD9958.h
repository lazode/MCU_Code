#ifndef	_AD9958_H
#define	_AD9958_H

#include "sys.h"
#include "delay.h"

#define	AD9958_PORT	GPIOC
#define	SDA_PIN			GPIO_PIN_6
#define	SCK_PIN			GPIO_PIN_7
#define	UPIO_PIN		GPIO_PIN_8
#define	RST_PIN			GPIO_PIN_9
#define	SYNC_IO			GPIO_PIN_10

#define	READ				1
#define	WRITE				0

#define	IsPLL				NumPLL

#define	CSR_ADDR		0x00
#define	FR1_ADDR		0x01
#define	FR2_ADDR		0x02
#define	CFR_ADDR		0x03
#define	CFTW0_ADDR	0x04
#define	CPOW0_ADDR	0x05
#define	ACR_ADDR		0x06
#define	LSRR_ADDR		0x07
#define	RDW_ADDR		0x08
#define	FDW_ADDR		0x09

#define	CHANNEL0	 (0x01<<6)
#define	CHANNEL1	 (0x02<<6)
#define	CHANNEL01	 (0x03<<6)

#define	MODE_2_WIRE	0x00
#define	MODE_3_WIRE	0x01

#define	LSB					1
#define	MSB					0

static int NumPLL = 0;


void Init_AD9958(uint8_t channel, uint8_t IOMode, uint8_t bitMode);
int  WriteRead_AD9958(unsigned char WR, unsigned char addr, int data, int dataWidth);
void ChannelSel_AD9958(uint8_t channel);

void WriteCFTW0_AD9958(uint64_t frequence);

void SetPLL_AD9958(int multi);
void SetAMP_AD9958(uint16_t amp);

void PhModul_AD9958(float phase1, float phase2);

void Reset_AD9958(void);

#endif

