#include "DSP_func.h"

#define	FREQ1				10000.0f
#define	FREQ2 			20000.0f
#define	AMP1				2.0f
#define	AMP2				10.0f

#define	SAMPLE_FRQ	200000.0f
#define	FIR_NUM			37
#define	BLOCK_SIZE	32

#define	RESAMPLE_D	5

const float fL = 10000.0f;
const float fH = 100000.0f;

static float32_t firStatebuf[BLOCK_SIZE + FIR_NUM - 1];

static float32_t input_srcAB[_FFT_LEN];
static float32_t input_srcB[_FFT_LEN];

static float32_t output_AB[_FFT_LEN / 2];
static float32_t output_B[_FFT_LEN / 2];

static float32_t last_outAB[_FFT_LEN / 2];
static float32_t last_outB[_FFT_LEN / 2];
static float32_t sub_result[_FFT_LEN / 2];

static float32_t after_filter[_FFT_LEN / 2];
static float32_t resample_src[_FFT_LEN];

static float32_t zoomfft_out[_FFT_LEN/RESAMPLE_D];

int fft_size = _FFT_LEN / 2;

const float32_t fir_num_f32[FIR_NUM] = {
  -0.001348412246,-0.001552450703,-0.001262641861,1.106597881e-18, 0.002512856154,
   0.005701863207, 0.007837646641,  0.00652304152,-3.595113471e-18, -0.01125042234,
   -0.02350831777, -0.03022352234, -0.02406340279,6.529515188e-18,  0.04183190316,
    0.09489839524,   0.1474881172,    0.186196655,   0.2004373968,    0.186196655,
     0.1474881172,  0.09489839524,  0.04183190316,6.529515188e-18, -0.02406340279,
   -0.03022352234, -0.02350831777, -0.01125042234,-3.595113471e-18,  0.00652304152,
   0.007837646641, 0.005701863207, 0.002512856154,1.106597881e-18,-0.001262641861,
  -0.001552450703,-0.001348412246
};




void fft_test(void)
{
	int i = 0;
	
	arm_cfft_radix4_instance_f32 cfftrad4_f32;
	arm_cfft_radix4_instance_f32 cfftrad4_f32_1;
	
	/*
		ģ�����fft����������
		����ʵ����������ʵ�����������ĸ�ʽ�洢.
	
	*/

	arm_cfft_radix4_init_f32(&cfftrad4_f32, fft_size, 0, 1);
	arm_cfft_radix4_init_f32(&cfftrad4_f32_1, fft_size, 0, 1);
	
	for(i = 0; i < fft_size ; i++)
	{
		input_srcAB[2*i + 1] = 0;
		input_srcAB[2*i] = AMP1*arm_sin_f32(2*PI*i * FREQ1 / SAMPLE_FRQ) + AMP2*arm_sin_f32(2*PI*i * FREQ2 / SAMPLE_FRQ);
		
		input_srcB[2*i + 1] = 0;
		input_srcB[2*i] = AMP1*arm_sin_f32(2*PI*i * FREQ1 / SAMPLE_FRQ);
		
	}

	//fft�任.
	arm_cfft_radix4_f32(&cfftrad4_f32, input_srcAB);
	arm_cfft_radix4_f32(&cfftrad4_f32_1, input_srcB);

	//����fft�����ģֵ.
	arm_cmplx_mag_f32(input_srcAB, last_outAB, fft_size);
	arm_cmplx_mag_f32(input_srcB, last_outB, fft_size);

//	for(i = 0; i < fft_size; i++)
//	{
//		printf("%f\r\n", last_outAB[i]);
//	}
//	
	for(i = 0; i < fft_size; i++)
	{
		sub_result[i] = last_outAB[i] - last_outB[i];
	
	}
	
	//���������
	printf("result of sub:\r\n");
	for(i = 0; i < fft_size; i++)
	{
		printf("%f\r\n", sub_result[i]);
	}
}
/*
**
	fft_sub()��������"pSrc1"��"pSrc2"��ʱ����Ϣ������fft������Ľ����������Ľ���洢������"*pDest_fft"  ��

	�ú��� find_zoom() �ҵ�����zoomfft��Ƶ�Σ����ʹ��zoomfft�ڹ涨�ֱ�����ȷ����Դ��Ƶ��

*/

void fft_sub(float *pSrc1, float *pSrc2, float *pDest_fft)
{


}


void find_zoom(float *pDest_fft)
{
	
}


void zoom_fft(float freq1, float freq2, float *pDest_zoom)
{


}


void zoom_ffttest()
{

	int i = 0;
	
	arm_fir_instance_f32 firS;
	arm_cfft_instance_f32 cfftS;
	

	//����ģ�������ź�.
	for(i = 0; i < _FFT_LEN ; i++)
	{
		input_srcAB[2*i + 1] = 0;
		input_srcAB[2*i] = AMP1*arm_sin_f32(2*PI*i * FREQ1 / SAMPLE_FRQ) + AMP2*arm_sin_f32(2*PI*i * FREQ2 / SAMPLE_FRQ);
//		printf("before zoom fft: %f\r\n", input_srcAB[i]);
	}
	
	arm_fir_init_f32(&firS, FIR_NUM,	(float32_t*)fir_num_f32, firStatebuf, BLOCK_SIZE);
	

	//Ƶ��.
	for(i = 0; i < _FFT_LEN; i++)
	{
		input_srcAB[i] *= arm_cos_f32(2*PI * i/fft_size);
	}	

	//�˲�.
	for(i = 0; i < _FFT_LEN/BLOCK_SIZE; i++)
	{ 
		arm_fir_f32(&firS, input_srcAB + (i*BLOCK_SIZE), after_filter + (i*BLOCK_SIZE), BLOCK_SIZE);
	}	
	
	//��ӡ�˲��������.
//	printf("after filter:\r\n");
//	for(i = 0; i < fft_size; i++)
//	{
//		printf("%f\r\n", output_AB[i]);
//	}										
	
	//�ز���...D������
	for(i = 0; i < fft_size/RESAMPLE_D; i++)
	{
		resample_src[i] = output_AB[RESAMPLE_D*i];
	}
	//fft.
	arm_cfft_f32(&cfftS, resample_src, 0, 1);
	
	arm_cmplx_conj_f32(resample_src, zoomfft_out, fft_size);
	
	printf("after zoom fft: \r\n");
	for(i = 0; i < fft_size/RESAMPLE_D; i++)
	{
		printf("%f\r\n", zoomfft_out[i]);
	}
	
	
}


