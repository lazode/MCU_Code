#include "DDSctl.h"

void write_dds(double dds)
{
	double x = 4294967295/180;		//适合180M晶振/180为最终时钟频率（或30M六倍频）
	unsigned char ww[5];
	int i;
	long int Fre;
	
	dds = dds / 1000000;
	dds = dds * x;
	Fre = dds;
	
	for(i = 0; i < 3; i++)
	{
		ww[i] = ((int)Fre) << i;		
	}
	ww[4] = 0x01;
	
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);	//拉低	FQ_UD
	delay_us(5);
	
	for(i = 0; i < 40; i++)
	{
		if( ww[i%8] & (1<<i))
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
		else
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		
		//产生一个上升沿
		GPIO_ResetBits(GPIOC, GPIO_Pin_11);
		delay_us(10);
		GPIO_SetBits(GPIOC, GPIO_Pin_11);
	}
	
	GPIO_SetBits(GPIOC, GPIO_Pin_4);	
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);	
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);

}


void init_dds(void)
{
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);  //RESET W_CLK
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);	 //RST FQUD
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	GPIO_SetBits(GPIOC, GPIO_Pin_12);	//RST	
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);
	GPIO_SetBits(GPIOC, GPIO_Pin_11);
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}


void GPIO_Config(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 //使能端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化
	 

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
}
	


