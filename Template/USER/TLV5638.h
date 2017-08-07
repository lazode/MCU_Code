#ifndef	_TLV5638_H
#define	_TLV5638_H

#include "sys.h"
#include "delay.h"

#define	TLV5638_PORT	GPIOC
#define	DATPIN				GPIO_PIN_6
#define	CKPIN					GPIO_PIN_7
#define	CSPIN					GPIO_PIN_8


#define	FAST_MODE	 	 (0x01<<14)
#define	POWERDOWN	 	 (0X01<<13)

#define	TODACB_BUF		0x00
#define	TOBUF			 	 (0x01<<12)
#define	TODACA_UPB 	 (0x01<<15)

#define	VREF_SEL	 	 (0x01<<15 | 0x01<<12)
#define	EXTERNAL			0x00
#define	REF0					0x01
#define	REF1			 	 (0x01<<1)

#define	VREF_EXTERNAL	2

void Init_TLV5638(void);
void Write_TLV5638(uint16_t data);

void Set_TLV5638(uint16_t mode, uint8_t Ref, float volt);

#endif
