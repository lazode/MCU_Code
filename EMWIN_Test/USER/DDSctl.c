#include "DDSctl.h"

void write_dds(double dds)
{
	double x = 4294967295/180;		//�ʺ�180M����/180Ϊ����ʱ��Ƶ�ʣ���30M����Ƶ��
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
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);	//����	FQ_UD
	delay_us(5);
	
	for(i = 0; i < 40; i++)
	{
		if( ww[i%8] & (1<<i))
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
		else
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		
		//����һ��������
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
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ�ܶ˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;				 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��
	 

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
}
	


