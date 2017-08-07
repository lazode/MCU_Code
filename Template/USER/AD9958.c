#include "AD9958.h"

void Init_AD9958(uint8_t channel, uint8_t IOMode, uint8_t bitMode)
{
//	uint8_t CSRW = 0;
//	
	GPIO_InitTypeDef GPIO_Initure;
     
	__HAL_RCC_GPIOC_CLK_ENABLE();          

	GPIO_Initure.Pin   = SDA_PIN | SCK_PIN | RST_PIN | UPIO_PIN | SYNC_IO; 
	GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  
	GPIO_Initure.Pull  = GPIO_PULLUP;          
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;     
	HAL_GPIO_Init(AD9958_PORT,&GPIO_Initure);
	
	Reset_AD9958();
	
//	CSRW |= (channel<<6) | (IOMode<<1) | bitMode;
// 	
//	WriteRead_AD9958(WRITE, CSR_ADDR, CSRW, 1);
	
}


void Reset_AD9958()
{
	HAL_GPIO_WritePin(AD9958_PORT, RST_PIN, GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, RST_PIN, GPIO_PIN_SET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, RST_PIN, GPIO_PIN_RESET);
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
int WriteRead_AD9958(unsigned char WR, unsigned char addr, int data, int dataWidth)
{
	int reData = 0;
	
	int size = sizeof(addr) * 8;
	
	//Set the WriteRead byte of Instruction Word.
	if(WR == READ)
		addr |=   0x01<<(size - 1);
	else
		addr &= ~(0x01<<(size - 1));
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	
	//Write the address bytes of Instruction Word.
	//WriteInstruction:{
	
		for(int i = 1; i <= size; i++ )
		{			
			HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_RESET);
			
			if((addr >> (size - i)) & 0x01)
				HAL_GPIO_WritePin(AD9958_PORT, SDA_PIN, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(AD9958_PORT, SDA_PIN, GPIO_PIN_RESET);
			
			delay_us(10);
			HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_SET);
			
			delay_us(10);
			
		}
		HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_RESET);
		delay_us(10);
	//}
	
	size = dataWidth * 8;
	
	//Write the register data.
	if(WR == WRITE)
	{
		
		//WriteData:     { 
			
			for(int i = 1; i <= size; i++)
			{
				HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_RESET);
			
				if((data >> (size - i)) & 0x01)
					HAL_GPIO_WritePin(AD9958_PORT, SDA_PIN, GPIO_PIN_SET);
				else
					HAL_GPIO_WritePin(AD9958_PORT, SDA_PIN, GPIO_PIN_RESET);
				
				delay_us(10);
				HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_SET);
				delay_us(10);
			}
			HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_RESET);
			delay_us(10);
			HAL_GPIO_WritePin(AD9958_PORT, SDA_PIN, GPIO_PIN_RESET);

	
		//}
	}
	else
	{
		
		//ReadData:	 {
			
			for(int i = 0; i < size; i++ )
			{ 
				HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_SET);
			
				if(GPIO_PIN_SET == HAL_GPIO_ReadPin(AD9958_PORT, SDA_PIN))
					reData |=  (0x01 << (size - i));
				else
					reData &= ~(0x01 << (size - i));
				
				delay_us(10);
				HAL_GPIO_WritePin(AD9958_PORT, SCK_PIN, GPIO_PIN_RESET);
			}
		//}
	}
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_SET);
	delay_us(5); 
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	
	return reData;
	
}


void ChannelSel_AD9958(uint8_t channel)
{
	//WriteRead_AD9958(WRITE, );
	
}

//set the frequence and others...
void WriteCFTW0_AD9958(uint64_t frequence)
{
	
	int FTW;
	//int FTW = frequence;	
	
	if(IsPLL)
	{
		frequence /= NumPLL;
	}
	
	FTW = frequence * 4294967296 / 40000000.0f;
	
	printf("FTW = %d\r\n", FTW);
	uint8_t CSRW = 0;
	uint32_t ACR = 0x80; 
	
// 	CSRW |= (CHANNEL01<<6) | (MODE_2_WIRE<<1) | MSB;
 	 
	HAL_GPIO_WritePin(AD9958_PORT, SDA_PIN, GPIO_PIN_RESET);	
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
		
	//select channel
	WriteRead_AD9958(WRITE, CSR_ADDR, CHANNEL01, 1);
	WriteRead_AD9958(WRITE, CFTW0_ADDR, FTW, 4);
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_SET);
	delay_us(5); 
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	
}


//set the PLL Multiplier Control bits.
void SetPLL_AD9958(int multi)
{
	int FR1Word = 0;
	
	//FR1Word  = Read_AD9958(FR1_ADDR, 3);
	
	FR1Word |= multi << 18;
	
	if(multi < 4 || multi > 20)
		NumPLL = 0;
	else
	{
		FR1Word |= 0x01<<23;	
		NumPLL   = multi;
	}
	
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);

	//select channel
	WriteRead_AD9958(WRITE, CSR_ADDR, CHANNEL01, 1);
	WriteRead_AD9958(WRITE, FR1_ADDR, FR1Word, 3);
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_SET);
	delay_us(5); 
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);

}


//Set channels phase...
void PhModul_AD9958(float phase1, float phase2)
{
	uint16_t C1POW, C2POW;
	
	C1POW = (phase1/360.0f) * 16384;
	C2POW = (phase2/360.0f) * 16384;

	printf("C1POW = %d\r\n", C1POW);
	printf("C2POW = %d\r\n", C2POW);
	
	//Set channel 0 phase
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	//select channel
	WriteRead_AD9958(WRITE, CSR_ADDR, CHANNEL0, 1);
	//set phase
	WriteRead_AD9958(WRITE, CPOW0_ADDR, C1POW, 2);
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_SET);
	delay_us(5); 
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);


	//set channel 1 phase..
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);

	//select channel
	WriteRead_AD9958(WRITE, CSR_ADDR, CHANNEL1, 1);
	//set phase
	WriteRead_AD9958(WRITE, CPOW0_ADDR, C2POW, 2);
	
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_SET);
	delay_us(1);
	HAL_GPIO_WritePin(AD9958_PORT, SYNC_IO, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);
	delay_us(5);
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_SET);
	delay_us(5); 
	HAL_GPIO_WritePin(AD9958_PORT, UPIO_PIN, GPIO_PIN_RESET);

}



void SetAMP_AD9958(uint16_t amp)
{
	
}
	

