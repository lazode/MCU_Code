#include "AMP_CTL.h"


void AMP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //�ٳ�ʼ�� GPIOA

	
	//GPIO_SetBits(GPIOA,GPIO_Pin_4); //PA.4 �����
	//GPIO_SetBits(GPIOA,GPIO_Pin_5);
	
	DAC_InitType.DAC_Trigger=DAC_Trigger_None; //��ʹ�ô�������
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ; //DAC1 ��������
	DAC_Init(DAC_Channel_1,&DAC_InitType); //�۳�ʼ�� DAC ͨ�� 1
	DAC_Init(DAC_Channel_2,&DAC_InitType);
	
	DAC_Cmd(DAC_Channel_1, ENABLE); //ʹ�� DAC1
	DAC_Cmd(DAC_Channel_2, ENABLE); //ʹ�� DAC2
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);
	DAC_SetChannel2Data(DAC_Align_12b_R, 0);
	/*
		500/620   1000
		100   740
	*/
	
}

void AMP_CTL(unsigned char Gain)
{
	float Temp = (( Gain/GAIN_VOLTAG)* 4095/3.3 );
	
	uint16_t Data = Temp + 140;
	//�������ͻ���,����;
	
	
	DAC1_CTL(Data);
	

}

void DAC1_CTL(uint16_t Data)
{

	DAC_SetChannel1Data(DAC_Align_12b_R, Data);

}

void DAC2_CTL(uint16_t Data)
{
//	DAC_SetChannel2Data(DAC_Align_12b_R, Data);

}
