#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "malloc.h"
#include "GUI.h"
#include "GUIDemo.h"

#include "FrameWinDLG.h"

#include "DAC_CTL.h"
#include "Exti.h"
#include "key.h"
#include "DDS_CTL.h"
#include "DDSctl.h"

#include "DIALOG.h"

#include "myiic.h"
#include "ADS1110_CTL.h"
#include "AmpGain_CTL.h"
#include "FreqMeasure.h"

extern int OldFreq;

int main(void)
{	 			
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	delay_init();	    	//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			    //LED�˿ڳ�ʼ��
	TFTLCD_Init();			//LCD��ʼ��	
	KEY_Init();	 			//������ʼ��
 	TP_Init();					//��������ʼ��
	TIM3_Int_Init(999,71);	//1KHZ ��ʱ��1ms 
	TIM6_Int_Init(999,719);	//10ms�ж�

	mem_init(); 			//��ʼ���ڲ��ڴ��
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//ʹ��CRCʱ�ӣ�����STemWin����ʹ�� 
	WM_SetCreateFlags(WM_CF_MEMDEV);
	
	GUI_Init();
	
	
	// Set The Skin
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
	
	CreateFramewin();
	
	TIM2_Cap_Init(0xFFFF, 71);
	
	ADS1110_Init();
	Amp_Init();
	Amp_SetGain(1);
	
	//EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	//EDIT_SetFont(hItem, &GUI_Font8x16);
	while(1)
	{

		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GUI_Delay(300);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		GUI_Delay(300);
	}
}



