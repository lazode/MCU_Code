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
    HAL_Init();                     //��ʼ��HAL��    
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz

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
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
			
			printf("len = %d \r\n", len);
			for(int i = 0; i < len; i++)
			{
				t += (USART_RX_BUF[i] - '0') * pow(10, len - i - 1);
				//printf("%c \r\n", USART_RX_BUF[i]);
				
			}
			
			//printf("\r\n t = %d", t);
			
			
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
			
			WriteFTW_AD9953(t);
		}
		else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK ������STM32F429������ ����ʵ��\r\n");
//				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("����������,�Իس�������\r\n");  
//			//if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
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
    __HAL_RCC_GPIOB_CLK_ENABLE();           //����GPIOCʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //PB1,0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB0��1 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB1��1  
}



