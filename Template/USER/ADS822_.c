#include "ADS822_.h"

int Read_ADS822(void)
{
	int Data = 0;
	
	//float volt = (Data * 5)/ 512;
	
//	HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_SET);
//	
//	delay_us(10);
	Data = ((D9_PIN)<<9) | (D8_PIN<<8) | (D7_PIN<<7) | (D6_PIN<<6) | (D5_PIN<<5) |
			(D4_PIN<<4) | (D3_PIN<<3) | (D2_PIN<<2) | (D1_PIN<<1) | (D0_PIN<<0);
		
	return Data;

}


void ADS822_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();           	 //开启PORTB的时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();           	 //开启PORTC的时钟
	

	GPIO_InitStructure.Pin  = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
 	GPIO_InitStructure.Mode = GPIO_MODE_INPUT; 		 
 	GPIO_InitStructure.Pull = GPIO_NOPULL;
 	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.Pin  = GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin  = CLK_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(CLK_PORT, &GPIO_InitStructure);

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
	
	__HAL_RCC_GPIOA_CLK_ENABLE();           	 //开启PORTA的时钟
	

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

int data_max(int data[], int length)
{
	int maxdata = 0;
	
	for(int i = 0; i < length; i++){
		if(maxdata < data[i])
		{	
			maxdata = data[i];
		}
	}
	
	return maxdata;
}
