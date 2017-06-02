#include "ADS822_.h"

int Read_ADS822(void)
{
	int Data = 0;
	
	Data = (D9_PIN<<9) | (D8_PIN<<8) | (D7_PIN<<7) | (D6_PIN<<6) | (D5_PIN<<5) |
		   (D4_PIN<<4) | (D3_PIN<<3) | (D2_PIN<<2) | (D1_PIN<<1) | (D0_PIN<<0);
	
	return Data;
}

void Amp_SetGain(int Gain)
{
	switch(Gain)
	{
		
		case 1:
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A1, GPIO_PIN_RESET);
		
			break;
		
		case 10:
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A1, GPIO_PIN_RESET);
		
			break;
		
		case 100:
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A1, GPIO_PIN_SET);
		
			break;
		
		case 1000:
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PGA202_PORT, PGA202_A1, GPIO_PIN_SET);
		
			break;
		
	}
}

void Amp_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();           	 //¿ªÆôPORTAµÄÊ±ÖÓ
	

	GPIO_InitStructure.Pin = PGA202_A0 | PGA202_A1;
 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 
 	GPIO_InitStructure.Pull = GPIO_PULLUP;
 	HAL_GPIO_Init(PGA202_PORT, &GPIO_InitStructure);

	HAL_GPIO_WritePin(PGA202_PORT,PGA202_A0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PGA202_PORT,PGA202_A1,GPIO_PIN_RESET);
}	


short data_map(int data, int min, int max, int dest_Min, int dest_Max)
{
	short mapdata = (short)data * (dest_Max - dest_Min)/(max - min);
	return mapdata;
}
