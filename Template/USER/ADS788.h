#ifndef	_ADS788_H
#define	_ADS788_H

#include "sys.h"


#define	ADS788_PORT	GPIOC
#define	CLKPIN		GPIO_PIN_6
#define	DATAPIN		GPIO_PIN_7
#define	CSPIN		GPIO_PIN_8


void 	 Init_ADS788(void);
uint16_t Read_ADS788(void);

#endif

