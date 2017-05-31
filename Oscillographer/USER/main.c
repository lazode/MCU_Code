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
	
    while(1)
    {
	}
}
