#include "AmpGain_CTL.h"


void Amp_SetGain(int Gain)
{
	switch(Gain)
	{
		
		case 1:
			GPIO_ResetBits(PGA202_PORT, PGA202_A0);
			GPIO_ResetBits(PGA202_PORT, PGA202_A1);
		
			break;
		
		case 10:
			GPIO_SetBits(PGA202_PORT, PGA202_A0);
			GPIO_ResetBits(PGA202_PORT, PGA202_A1);
		
			break;
		
		case 100:
			GPIO_ResetBits(PGA202_PORT, PGA202_A0);
			GPIO_SetBits(PGA202_PORT, PGA202_A1);
		
			break;
		
		case 1000:
			GPIO_SetBits(PGA202_PORT, PGA202_A0);
			GPIO_SetBits(PGA202_PORT, PGA202_A1);
		
			break;
		
	}
}

void Amp_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}	
