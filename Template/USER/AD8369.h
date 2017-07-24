#ifndef	_AD8369_H
#define	_AD8369_H

#include "sys.h"

#define	AD8369_PORT	GPIOC

#define	DATAPIN		GPIO_PIN_0
#define	CLKPIN		GPIO_PIN_1
#define	DATA_EN		GPIO_PIN_2

void Init_AD8369(void);
void SetGain_AD8369(int gain);


#endif

