#include "ADS788.h"

void Init_ADS788()
{
	GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();          
	
    GPIO_Initure.Pin   = DATAPIN | CLKPIN | CSPIN; 
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;  
    GPIO_Initure.Pull  = GPIO_PULLDOWN;          
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;     
    HAL_GPIO_Init(ADS788_PORT,&GPIO_Initure);
}



uint16_t Read_ADS788()
{
	uint16_t data = 0;
	int size = sizeof(data);
	
	HAL_GPIO_WritePin(ADS788_PORT, CSPIN, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(ADS788_PORT, CSPIN, GPIO_PIN_RESET);
	
	
	for(int i = 0; i < size; i++ )
	{
		HAL_GPIO_WritePin(ADS788_PORT, CLKPIN, GPIO_PIN_SET);
		
		if(GPIO_PIN_SET == HAL_GPIO_ReadPin(ADS788_PORT, DATAPIN))
			data |=  (0x01 << (size - i));
		else
			data &= ~(0x01 << (size - i));
				
		delay_us(2);
		HAL_GPIO_WritePin(ADS788_PORT, CLKPIN, GPIO_PIN_RESET);
		
	}
	
	return (data>>2);
	
}

