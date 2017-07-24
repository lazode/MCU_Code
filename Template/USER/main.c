#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "AD9953.h"
#include "ADS822_.h"
#include "ADS788.h"

#include "exti.h"

void LED_Init(void);

int main(void)
{
	
    HAL_Init();                     //初始化HAL库    
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz

	delay_init(180);
	uart_init(9600);
	LED_Init();
	EXTI_Init();
	
	Init_ADS788();
	
//	ADS822_Init();
//	uint8_t USART_TX_BUF[10];
//	int UART_TX_temp = 0;
	
//	uart_rxTemp.temp = 0;
	int t = 0;
//	float v;	
	
//	__HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_IDLE);
	
//	Init_ADS788();
	
	Init_AD9953();
//	SetPLL_AD9953(0);
	while(1)
	{
		
//		WriteFTW_AD9953(100000);

//		t = Read_ADS788();
//		v = ((float)t / 1024) * 5.0;
//		
//		printf("t = %d\n", t);
//		
//		printf("v = %f\n", v);
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



