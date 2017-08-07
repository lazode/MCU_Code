#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "AD9953.h"
#include "ADS822_.h"
#include "ADS788.h"
#include "AD8369.h"
#include "ADS1110_CTL.h"
#include "AD9851.h"
#include "AD9958.h"
#include "TLV5638.h"

#include "exti.h"

#include "math.h"


#include "stdlib.h"

void LED_Init(void);


int stepFreq = 0;
uint8_t scan = 0;

int main(void)
{
	u8 len;	
	u16 times=0; 
  HAL_Init();                     //初始化HAL库    
  Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
	delay_init(180);
	uart_init(9600);
	LED_Init();
	EXTI_Init();

//	ADS822_Init();

//	int t = 0;
//	double t = 0.0;
//	float v;	
	uint64_t t = 0;

//	const char * cc = (char *)USART_RX_BUF;

//	Init_ADS788();
	
//	ADS1110_Init();
	
//	Init_AD9851();x

	Init_AD9958(CHANNEL01, MODE_2_WIRE, MSB);

//	Init_AD8369();
//	Init_AD9953();
//	SetPLL_AD9953(0);
//	Init_TLV5638();

	while(1)
	{
//			t = ADS1110_ReadData();
//			v = t * 2.048 / 32768;
		

//		t = Read_ADS788();
//		v = (t* 5.0) / 1024;
//		
//		printf("t = %d\r\n", t);
//		
//		printf("v = %f\r\n", v);
//		Write_AD9851(0,1000);
		
//		SetGain_AD8369(10);
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//发送接收到的数据
			
			
			for(int i = 0; i < len; i++)
			{
	
				t += (USART_RX_BUF[i] - '0') * pow(10, len - i - 1);
//				printf("%c \r\n", USART_RX_BUF[i]);
				
			}

//			t = atof(cc);
//			t = atoi(cc);
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
//			
//			
//			printf("t = %f\r\n", t);
			printf("t = %lld\r\n", t);
			SetPLL_AD9958(10);
			WriteCFTW0_AD9958(t);

//			SetGain_AD8369(t);
			
//			Set_TLV5638(TODACA_UPB , REF1, t);
//			WriteFTW_AD9953(t);
//			SetPLL_AD9958(4);
//			Write_AD9851(0, t);
			t = 0;
		}
		else
		{
			times++;
			
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			
			delay_ms(10);   	
		} 

		
		
		delay_ms(100);
			
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
		delay_ms(300);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
		delay_ms(300);
		
		
	}
}



void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; 
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull=GPIO_PULLUP;          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	 
}



