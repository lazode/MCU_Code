#include "uart2io.h"

int fputc(int ch, FILE *f)
{
	while((USART1->SR&0x40) == 0);   
	USART1->DR = (uint8_t)ch;      
	return ch;

}
