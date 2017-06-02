#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "tftlcd.h"
#include "timer.h"
#include "sdram.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "WM.h"

#include "FramewinDLG.h"

/************************************************

issue:
	
	1���������ݸ�Ϊ���ɶ�ʱ����һ��Ƶ��ˢ��buffer��Ȼ����Sample Button��ֱ�Ӷ�ȡ��ʱbuffer����
	//2��ADS822�����Լ��ܽ�
	
	3������������֮ǰ��ADS1110���Բ�����ʾ������ �޻������������ܣ�
	4�����Ȼ���
	5�����ݲ�ͬƵ�ʵ���ʱ���ᱶ��
	
	
	//�ط��źŲ���Ӧ������ʧ�棬����û�����Ե�ë�̺�̨�ס�����Ӧ���ȶ�����Ӧ�����ԵĹ������󣩡�
											|	   |						   |		
											|	��ֵ����						   |		
										   �˲�?							���о�
		
	
																			
************************************************/


int main(void)
{
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz   
    HAL_Init();                     //��ʼ��HAL��
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    SDRAM_Init();                   //SDRAM��ʼ��
    TFTLCD_Init();  		        //LCD��ʼ��
    TP_Init();				        //��������ʼ��
    TIM3_Init(999,89);              //1KHZ ��ʱ��3����Ϊ1ms
    TIM4_Init(999,899);             //������ɨ���ٶ�,100HZ.
    my_mem_init(SRAMIN);		    //��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		    //��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMCCM);		    //��ʼ��CCM�ڴ��
	__HAL_RCC_CRC_CLK_ENABLE();		//ʹ��CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);//����STemWin�洢�豸
	GUI_Init();
    WM_MULTIBUF_Enable(1);			//����STemWin�໺�壬RGB�����ܻ��õ�
	
	CreateFramewin();
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	
    while(1)
    {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		GUI_Delay(300);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		GUI_Delay(300);
		
	}
}
