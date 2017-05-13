#include "FreqMeasure.h"


TIM_ICInitTypeDef  TIM2_ICInitStructure;

u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ

unsigned int CaptureCount1 = 0;
unsigned int CaptureCount2 = 0;
unsigned int CaptureCnt = 0;

unsigned int OldCaptureCount1 = 0;
int Frequence = 0;

unsigned char flag = 0;

void FreqMeasure_Init()
{
	
}


int FreqMeasure()
{
	
	
	if(CaptureCnt != 0)
	{
		Frequence = 1000000 / (2*CaptureCnt);
	}	
	
	return Frequence;
}

//��ʱ��2ͨ��1���벶������



void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ��TIM2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
	
	//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x04;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
	TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��2
 
}

//��ʱ��5�жϷ������	 
void TIM2_IRQHandler(void)
{ 
	
	
 	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)
	{
		if(flag == 0)
		{	
			OldCaptureCount1 = CaptureCount1;
			CaptureCount1 = TIM_GetCapture1(TIM2);
			
			TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);
			flag = 1;
		}
		else
		{
			CaptureCount2 = TIM_GetCapture1(TIM2);
			CaptureCnt = CaptureCount2 - CaptureCount1;
			
			TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);	
			flag = 0;
		}

	}
 
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		flag = 0;
		if(OldCaptureCount1 == CaptureCount1)
			Frequence = 0;
	}
	
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}





//void FreqTest()
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	
//	NVIC_InitTypeDef NVIC_InitStructure;

//	EXTI_InitTypeDef EXTI_InitStructure;


//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

//	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
//	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;  //PA0 ���֮ǰ����  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);						 //PA0 ����
//	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//}
