#include "AD8369.h"

void Init_AD8369(void)
{
	GPIO_InitTypeDef GPIO_Initure;
     
    __HAL_RCC_GPIOC_CLK_ENABLE();          
	
    GPIO_Initure.Pin   = SDA_PIN | SCK_PIN | DATA_EN; 
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull  = GPIO_PULLUP;          
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;     
    HAL_GPIO_Init(AD8369_PORT, &GPIO_Initure);
	
	HAL_GPIO_WritePin(AD8369_PORT, DATA_EN, GPIO_PIN_SET);
}


/*
	the parameter "gain" is used "dB" unit.
		
		gain = 20 * log(A(V/V)) (dB)

	ranged -5dB to 40dB, step of 3dB.
*/
void SetGain_AD8369(int gain)
{
	int steps = gain / 3;
	
	uint8_t size = sizeof(gain);
	
	HAL_GPIO_WritePin(AD8369_PORT, SCK_PIN, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(AD8369_PORT, DATA_EN, GPIO_PIN_RESET);
	delay_us(5);
	
	for(int i = 1; i <= size; i++)
	{

		HAL_GPIO_WritePin(AD8369_PORT, SCK_PIN, GPIO_PIN_RESET);
	
		if((steps >> (size - i)) & 0x01)
			HAL_GPIO_WritePin(AD8369_PORT, SDA_PIN, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(AD8369_PORT, SDA_PIN, GPIO_PIN_RESET);
		
		delay_us(10);
		HAL_GPIO_WritePin(AD8369_PORT, SCK_PIN, GPIO_PIN_SET);
		delay_us(10);
	}
	delay_us(10);
	HAL_GPIO_WritePin(AD8369_PORT, DATA_EN, GPIO_PIN_SET);
			
	HAL_GPIO_WritePin(AD8369_PORT, SCK_PIN, GPIO_PIN_RESET);

}


