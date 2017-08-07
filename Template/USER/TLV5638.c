#include "TLV5638.h"


void Init_TLV5638(void)
{
	 GPIO_InitTypeDef GPIO_Initure;
	
	//set gpio of the control tlv5638.
    __HAL_RCC_GPIOC_CLK_ENABLE();           
	
    GPIO_Initure.Pin   = DATPIN | CKPIN | CSPIN; 
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull  = GPIO_PULLUP;          
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;     
    HAL_GPIO_Init(TLV5638_PORT,&GPIO_Initure);
	
    HAL_GPIO_WritePin(TLV5638_PORT, CSPIN, GPIO_PIN_SET);	
		HAL_GPIO_WritePin(TLV5638_PORT, CKPIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(TLV5638_PORT, DATPIN, GPIO_PIN_RESET);
	
}

void Write_TLV5638(uint16_t data)
{
	int size = sizeof(data) * 8;
	
	HAL_GPIO_WritePin(TLV5638_PORT, CSPIN, GPIO_PIN_RESET);
	delay_us(2);
	
	for(int i = 1; i <= size; i++)
	{
		HAL_GPIO_WritePin(TLV5638_PORT, CKPIN, GPIO_PIN_SET);
		
		if(data & (0x01<<(size - i)))
			HAL_GPIO_WritePin(TLV5638_PORT, DATPIN, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(TLV5638_PORT, DATPIN, GPIO_PIN_RESET);
		
		delay_us(2);
		HAL_GPIO_WritePin(TLV5638_PORT, CKPIN, GPIO_PIN_RESET);
		delay_us(2);
		
	}
	
	HAL_GPIO_WritePin(TLV5638_PORT, CSPIN, GPIO_PIN_SET);
	delay_us(3);

}



/*
mode:	
	
0
	FAST_MODE	
	POWERDOWN

1
	TODACB_BUF		
	TOBUF			
	TODACA_UPB
	VREF_SEL
	
	use the operator "|" to make a combination with the "0" mode and "1" mode
 	

volt:

	when you selected the "VREF_SEL" mode, you can set "EXTERNAL", "REF0"(1.024V), "REF1"(2.048V)
	when you selected other modes, you can set it at range of 0x000 - 0xFFF 

*/

void Set_TLV5638(uint16_t mode, uint8_t Ref, float volt)
{
	uint16_t word = 0;
	float Vref;
	
	if(Ref == REF0)
	{
		Vref = 1.024;		
	}
	else if(Ref == REF1)
		Vref = 2.048;
	else
		Vref = VREF_EXTERNAL;

	word = VREF_SEL | Ref;
	Write_TLV5638(word);
	delay_us(2);
	
	word = TODACB_BUF | (((uint16_t)((volt / (2*Vref)) * 0x1000)));	
	Write_TLV5638(word);

	delay_us(2);
	word = mode | (((uint16_t)((volt / (2*Vref)) * 0x1000)));	
	
//	printf("volt = %f\r\n", volt);
//	printf("word = %d\r\n", word);
	
	Write_TLV5638(word);
	
}


