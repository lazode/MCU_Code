#include "ADS1110_CTL.h"

const unsigned char ADS1110_ADDR = 72;
//static int i = 0;

void ADS1110_Init()
{
	IIC_Init();
	
}

int ADS1110_ReadData()
{

	int Byte = 0;
	
	unsigned char Byte_H,
				  Byte_L;
	
		
	//发送ADS1110地址以及读写信号
	//ADS1110_WriteData(SINGLE, RATE_15SPS, PGA_GAIN_1);
	//delay_us(5);

	//开始读数据的IIC会话
	IIC_Start();
	
	IIC_Send_Byte(( (ADS1110_ADDR ) << 1) + READDATA);
	if(IIC_Wait_Ack())
	{

		return 0;
	}
	else{
		
		Byte_H = IIC_Read_Byte(ACK);
		Byte_L = IIC_Read_Byte(ACK);
		
		IIC_Stop();
		
		Byte = (Byte_H<<8) + Byte_L;
		
		return Byte;
	}
}


int ADS1110_WriteData(unsigned char Mode, unsigned char Data_Rate, unsigned char PGA_Gain)
{
	unsigned int Data_Bytes = 0;
	
	//
	IIC_Start();
	IIC_Send_Byte(((ADS1110_ADDR )<< 1) + WRITEDATA);
	if(IIC_Wait_Ack())
	{	
		return 1;
	}
	else
	{
		Data_Bytes = (1<<7) + (Mode<<4) + (Data_Rate <<2) + PGA_Gain;
		IIC_Send_Byte(Data_Bytes);
		if(IIC_Wait_Ack())
			return 1;
		else
		{
			IIC_Stop();
			return 0;
		}
	}
}
