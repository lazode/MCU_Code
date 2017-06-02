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
	
	1、接受数据改为，由定时器用一定频率刷新buffer，然后在Sample Button里直接读取当时buffer数据
	//2、ADS822驱动以及管脚
	
	3、板子做出来之前用ADS1110测试波形显示（测试 无换挡等其他功能）
	4、幅度换挡
	5、根据不同频率调整时间轴倍乘
	
	
	//回放信号波形应无明显失真，而且没有明显的毛刺和台阶。波形应当稳定（不应有明显的滚动现象）。
											|	   |						   |		
											|	插值法？						   |		
										   滤波?							待研究
		
	
																			
************************************************/


int main(void)
{
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz   
    HAL_Init();                     //初始化HAL库
    delay_init(180);                //初始化延时函数
    uart_init(115200);              //初始化USART
    LED_Init();                     //初始化LED 
    KEY_Init();                     //初始化按键
    SDRAM_Init();                   //SDRAM初始化
    TFTLCD_Init();  		        //LCD初始化
    TP_Init();				        //触摸屏初始化
    TIM3_Init(999,89);              //1KHZ 定时器3设置为1ms
    TIM4_Init(999,899);             //触摸屏扫描速度,100HZ.
    my_mem_init(SRAMIN);		    //初始化内部内存池
	my_mem_init(SRAMEX);		    //初始化外部内存池
	my_mem_init(SRAMCCM);		    //初始化CCM内存池
	__HAL_RCC_CRC_CLK_ENABLE();		//使能CRC时钟
	WM_SetCreateFlags(WM_CF_MEMDEV);//开启STemWin存储设备
	GUI_Init();
    WM_MULTIBUF_Enable(1);			//开启STemWin多缓冲，RGB屏可能会用到
	
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
