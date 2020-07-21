#ifndef __PRJ_STM32F10X_DRVFREQ_C__
#define __PRJ_STM32F10X_DRVFREQ_C__

#include "drvfreq.h"
#include "delay.h"



//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: freq_gpio_input_config
//	����˵��: Ƶ������ GPIO ��������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-07-21
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void freq_gpio_input_config(void)
{
	GPIO_InitTypeDef gpio_config;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��Ƶ������GPIOA�˿�ʱ��
	
	gpio_config.GPIO_Pin	= FREQ_INPUT_IO;	//����GPIOA PA0
	gpio_config.GPIO_Mode	= GPIO_Mode_IPD;	//PA0 ����Ϊ��������
	
	GPIO_Init(FREQ_GPIO_PORT, &gpio_config);	//��ʼ��GPIO����
	
	GPIO_ResetBits(FREQ_GPIO_PORT, FREQ_INPUT_IO);	//���� PA0 ��ʼ״̬Ϊ�͵�ƽ
	
	return;
}
	
//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: timer_counter_config
//	����˵��: ��ʱ����������
//	��    ��: 	timer_no����ʱ�����
//				timer_arr����ʱ����װֵ
//				timer_psc����ʱ����Ƶֵ
//	�� �� ֵ: ��
//	��    ��: 2020-07-21
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void timer_counter_config(uint8_t timer_no, uint16_t timer_arr, uint16_t timer_psc)
{
	uint8_t temp_value = timer_no;
	
	TIM_TimeBaseInitTypeDef timer_init;
	
	switch (temp_value)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��2��ʱ��
			
			TIM_DeInit(TIM2);	//��λ��ʱ��2�Ĳ���ֵ
			
			timer_init.TIM_Period			= timer_arr;	//������װ��ֵ
			timer_init.TIM_Prescaler		= timer_psc;	//���÷�Ƶ��ֵ
			timer_init.TIM_ClockDivision	= TIM_CKD_DIV1;	//ʱ�ӷָ�
			timer_init.TIM_CounterMode		= TIM_CounterMode_Up;	//������ʽ�����ϼ���
			
			TIM_TimeBaseInit(TIM2, &timer_init);	//��ʼ����ʱ��2�Ĳ���
			
			TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);	//�ⲿ������ʽ
			TIM_SelectInputTrigger(TIM2, TIM_TS_ETRF);	//�ⲿ��������Դ����
			TIM_SetCounter(TIM2, 0);	//��ʱ���ļ�����ֵ����Ϊ0
			
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//ʹ�ܶ�ʱ���ж�
			
			TIM_Cmd(TIM2, ENABLE);	//��ʱ��ʹ��
		}
		break;
		case 3:
		{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3��ʱ��
			
			TIM_DeInit(TIM3);	//��λ��ʱ��2�Ĳ���ֵ
			
			timer_init.TIM_Period			= timer_arr;	//������װ��ֵ
			timer_init.TIM_Prescaler		= timer_psc;	//���÷�Ƶ��ֵ
			timer_init.TIM_ClockDivision	= TIM_CKD_DIV1;	//ʱ�ӷָ�
			timer_init.TIM_CounterMode		= TIM_CounterMode_Up;	//������ʽ�����ϼ���
			
			TIM_TimeBaseInit(TIM3, &timer_init);	//��ʼ����ʱ��2�Ĳ���
			
		#if 0
			TIM_ETRClockMode2Config(TIM3, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);	//�ⲿ������ʽ
			TIM_SelectInputTrigger(TIM3, TIM_TS_ETRF);	//�ⲿ��������Դ����
			TIM_SetCounter(TIM3, 0);	//��ʱ���ļ�����ֵ����Ϊ0
			
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	//ʹ�ܶ�ʱ���ж�
		#endif
			TIM_Cmd(TIM3, ENABLE);	//��ʱ��ʹ��
		}
		
		default:
			break;
	}
	return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: timer_counter_nvic_config
//	����˵��: ��ʱ���ж�������������
//	��    ��: 	timer_no����ʱ�����
//	�� �� ֵ: ��
//	��    ��: 2020-07-21
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void timer_counter_nvic_config(uint8_t timer_no)
{
	uint8_t temp_value = timer_no;
	
	NVIC_InitTypeDef nvic_config;
	
	if (temp_value == 2)
	{
		nvic_config.NVIC_IRQChannel						= TIM2_IRQn;	//TIM2�ж�
		nvic_config.NVIC_IRQChannelPreemptionPriority	= 0;	//��ռ���ȼ�
		nvic_config.NVIC_IRQChannelSubPriority			= 0;	//�����ȼ�
		nvic_config.NVIC_IRQChannelCmd					= ENABLE;	//ʹ���ж�ͨ��
		
		NVIC_Init(&nvic_config);	//��ʼ��NVIC���ò���
	}
	else if (temp_value == 3)
	{
		nvic_config.NVIC_IRQChannel						= TIM3_IRQn;	//TIM3�ж�
		nvic_config.NVIC_IRQChannelPreemptionPriority	= 0;	//��ռ���ȼ�
		nvic_config.NVIC_IRQChannelSubPriority			= 1;	//�����ȼ�
		nvic_config.NVIC_IRQChannelCmd					= ENABLE;	//ʹ���ж�ͨ��
		
		NVIC_Init(&nvic_config);	//��ʼ��NVIC���ò���
	}
	
	return;
}

#endif	//__PRJ_STM32F10X_DRVFREQ_C__
