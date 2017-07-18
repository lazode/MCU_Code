#include "AD9953.h"

void Init_AD9953()
{
	GPIO_Config();
	
	Reset_AD9953();
}
	
/****************************************************************
	
	WR:
	if you want to Write data set it to be Logic 1, to Read set it Logic 0
	
	addr:
	the address of register that you want to access

	data:
	the data you want to put in the dest register 

	dataWidth :
	is how many bits the data have, or how many bits of the register you want to write

*************************************************************/

int WriteRead_AD9953(unsigned char WR, unsigned char addr, int data, int dataWidth)
{
	int reData = 0;
	
	int size   = sizeof(addr) * 8;
	
	//Set the WriteRead byte of Instruction Word.
	if(WR == READ)
		addr |=   0x01<<(size - 1);
	else
		addr &= ~(0x01<<(size - 1));
	
	//Write the address bytes of Instruction Word.
	WriteInstruction:{
		
		for(int i = 1; i <= size; i++ )
		{			
			HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_RESET);
			
			if((addr >> (size - i)) & 0x01)
				HAL_GPIO_WritePin(AD9953_PORT, DATA_PIN, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(AD9953_PORT, DATA_PIN, GPIO_PIN_RESET);
			
			delay_us(10);
			HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_SET);
			
			delay_us(10);
			
		}
		HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_RESET);
		delay_us(50);
	}
	
	size = dataWidth * 8;
	
	//Write the register data.
	if(WR == WRITE)
	{
		
		WriteData:     { 
			
			for(int i = 1; i <= size; i++)
			{
				HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_RESET);
			
				if((data >> (size - i)) & 0x01)
					HAL_GPIO_WritePin(AD9953_PORT, DATA_PIN, GPIO_PIN_SET);
				else
					HAL_GPIO_WritePin(AD9953_PORT, DATA_PIN, GPIO_PIN_RESET);
				
				delay_us(10);
				HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_SET);
				delay_us(10);
			}
			HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_RESET);
			delay_us(50);
			
	
		}
	}
	else
	{
		
		ReadData:	 {
			
			for(int i = 0; i < size; i++ )
			{ 
				HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_SET);
			
				if(GPIO_PIN_SET == HAL_GPIO_ReadPin(AD9953_PORT, DATA_PIN))
					reData |=  (0x01 << (size - i));
				else
					reData &= ~(0x01 << (size - i));
				
				delay_us(10);
				HAL_GPIO_WritePin(AD9953_PORT, CLK_PIN, GPIO_PIN_RESET);
			}
		}
	}
	
	
	return reData;

}


/***********************************************

	Application functions for convenient operation
	use the "WriteRead_AD9953()" function
		
	From datasheet:

		fo = (FTW)*(fs)/2^32	with  0 <= FTW <= 2^31
		fo = fs*(1-(FTW/2^32))  with  2^32 < FTW < 2^32 - 1
	
	

*********************************************/
void WriteFTW_AD9953(int frequence)
{
	//int FTW = frequence * 4294967296 / 20000000;
	int FTW = frequence;	
	
	WriteRead_AD9953(WRITE, FTW0_ADDR, FTW, 4);
	

	HAL_GPIO_WritePin(AD9953_PORT, UPDATE_PIN, GPIO_PIN_RESET);
	delay_us(100);
	HAL_GPIO_WritePin(AD9953_PORT, UPDATE_PIN, GPIO_PIN_SET);
	delay_us(50); 
	HAL_GPIO_WritePin(AD9953_PORT, UPDATE_PIN, GPIO_PIN_RESET);
}

//set the PLL Multiplier Control bits.
void SetPLL_AD9953(int multi)
{
	int CFR2Word = 0;
	
	//CFR2Word  = Read_AD9953(CFR2_ADDR, 3);
	
	CFR2Word &= ~((32 - 1) << 3);
	CFR2Word |= multi << 3;
	//	CFR2Word &= ~(multi << 3);
	
	WriteRead_AD9953(WRITE, CFR2_ADDR, CFR2Word, 3);
	HAL_GPIO_WritePin(AD9953_PORT, UPDATE_PIN, GPIO_PIN_RESET);
	delay_us(100);
	HAL_GPIO_WritePin(AD9953_PORT, UPDATE_PIN, GPIO_PIN_SET);
	delay_us(50); 
	HAL_GPIO_WritePin(AD9953_PORT, UPDATE_PIN, GPIO_PIN_RESET);	
}

//set the phase offset word
void WritePOW_AD9953(int phase)
{
	int POW = (phase * 16384) / 360;
	
	POW &= ~(0x01 << 14);
	POW &= ~(0x01 << 15);
	
	WriteRead_AD9953(WRITE, POW0_ADDR, POW, 2);
}

int  Read_AD9953(unsigned char addr, int dataWidth)
{
	int data = 0;
	
	GPIO_InitTypeDef GPIO_Initure;

	GPIO_Initure.Pin  = DATA_PIN; 
    GPIO_Initure.Mode = GPIO_MODE_INPUT;  
    GPIO_Initure.Pull = GPIO_NOPULL;               
    HAL_GPIO_Init(AD9953_PORT,&GPIO_Initure);
	
	data = WriteRead_AD9953(READ, addr, 0, dataWidth);
	GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull  = GPIO_PULLUP;                
    HAL_GPIO_Init(AD9953_PORT,&GPIO_Initure);
	
	
	return data;
}


//reset the AD9953 chip
void Reset_AD9953()
{
	HAL_GPIO_WritePin(AD9953_PORT, RESET_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9953_PORT, RESET_PIN, GPIO_PIN_SET);
	delay_us(10);
	
	HAL_GPIO_WritePin(AD9953_PORT, RESET_PIN, GPIO_PIN_RESET);
	
}



//Config the GPIO whcih the AD9953 used.
void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOC_CLK_ENABLE();          
	
    GPIO_Initure.Pin   = DATA_PIN | CLK_PIN | RESET_PIN | UPDATE_PIN; 
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull  = GPIO_PULLUP;          
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;     
    HAL_GPIO_Init(AD9953_PORT,&GPIO_Initure);
}

