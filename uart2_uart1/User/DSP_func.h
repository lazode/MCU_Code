#ifndef	_DSP_FUNC_H
#define	_DSP_FUNC_H


#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include "uart2io.h"


#define	SAMPLE_RATE		1000000.0f
#define	SIGNAL_FREQ		10000.0f
#define	_FFT_LEN			2048

void fft_test(void);
	
void zoom_ffttest(void);

#endif
