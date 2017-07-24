#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "AD9953.h"
#include "ADS822_.h"
#include "ADS788.h"

#include "exti.h"

#include "math.h"

void LED_Init(void);


int stepFreq = 0;


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
		
		 if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//发送接收到的数据
			
			printf("len = %d \r\n", len);
			for(int i = 0; i < len; i++)
			{
				t += (USART_RX_BUF[i] - '0') * pow(10, len - i - 1);
				//printf("%c \r\n", USART_RX_BUF[i]);
				
			}
			
			//printf("\r\n t = %d", t);
			
			
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
			
			WriteFTW_AD9953(t);
		}
		else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK 阿波罗STM32F429开发板 串口实验\r\n");
//				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
//			//if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
//			delay_ms(10);   
//		} 
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



