#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "AD9953.h"
#include "ADS822_.h"

void LED_Init(void);

int main(void)
{
	
	int freq = 0;
	char * s;
	
	
    HAL_Init();                     //初始化HAL库    
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz

	delay_init(180);
	uart_init(9600);
	LED_Init();
	
//	ADS822_Init();
	uint8_t USART_TX_BUF[10];
	int UART_TX_temp = 0;
	
	float v = 0.0;
	
	Init_AD9953();
	SetPLL_AD9953(10);
	while(1)
	{
//		if(freq == 10000)
//			freq++;
//		else
//			freq = 1;

		scanf("%s", s);
		printf("%s\n", s);
		SetPLL_AD9953(10);
		delay_ms(10);
		WriteFTW_AD9953(21474837);
		
		
//		UART_TX_temp = Read_ADS822() - 512;
//		v = (UART_TX_temp /1024) * 2.0;
//		printf("temp = %d\r\n", UART_TX_temp);
//		printf("v    = %f\r\n", v);
		
//		printf("%d%d%d%d%d%d%d%d%d%d\r\n", D9_PIN, D8_PIN, D7_PIN, D6_PIN, D5_PIN, D4_PIN, D	3_PIN, D2_PIN, D1_PIN, D0_PIN);
		
		delay_us(100);
			
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		delay_ms(300);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
		delay_ms(300);
	}
}



void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOC时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //PB1,0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB0置1 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB1置1  
}

