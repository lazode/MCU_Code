#include "timer.h"
#include "led.h"
#include "GUI.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ս��������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

extern __IO int32_t OS_TimeMS;
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//����TIM3ʱ�� 

	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;   //��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	   //����ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;		   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//��������ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3,ENABLE);		  //ʹ��TIM3
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{	
		OS_TimeMS++;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��6!
void TIM6_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //��ʱ��6ʱ��ʹ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //���÷�Ƶֵ��10khz�ļ���Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;  //�Զ���װ��ֵ ������5000Ϊ500ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0; //ʱ�ӷָ�:TDS=Tck_Tim
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE); //ʹ��TIM6�ĸ����ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn; //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM6,ENABLE); //��ʱ��6ʹ��
}


void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
	{
		GUI_TOUCH_Exec();
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update); //����жϱ�־λ
}


//��ѯ�����Ƿ���²�ˢ��

void TIM4_Init_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //��ʱ��6ʱ��ʹ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler = 719;  //���÷�Ƶֵ��10khz�ļ���Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period = 999;  //�Զ���װ��ֵ ������5000Ϊ500ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; //ʱ�ӷָ�:TDS=Tck_Tim
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE); //ʹ��TIM6�ĸ����ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4,ENABLE); //��ʱ��6ʹ��
	
}

void TIM4_IRQHandler(void)
{
	;

}

