#ifndef __PRJ_STM32F10X_DRVEXTI_C__
#define __PRJ_STM32F10X_DRVEXTI_C__

#include "Typedef.h"
#include "drvexti.h"
#include "drvled.h"
#include "delay.h"
#include "stm32f10x_conf.h"

volatile uint8_t g_exti_cnt = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: exti_gpio_config
//	����˵��: �ⲿ�ж�GPIO��������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-25
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
static void exti_gpio_config(void)
{
	GPIO_InitTypeDef gpio_init_config;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��
	
	gpio_init_config.GPIO_Pin  		= GPIO_Pin_0;//PA0
	gpio_init_config.GPIO_Mode 		= GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &gpio_init_config);//��ʼ��GPIOA.0
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: exti_config
//	����˵��: �ⲿ�жϲ�������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-25
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
static void exti_config(void)
{
	EXTI_InitTypeDef exti_init_config;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);	//PA0����Ϊ�ⲿ�ж�
	
	exti_init_config.EXTI_Line		= EXTI_Line0;
  	exti_init_config.EXTI_Mode 		= EXTI_Mode_Interrupt;	
  	exti_init_config.EXTI_Trigger 	= EXTI_Trigger_Rising;//�����ش���
  	exti_init_config.EXTI_LineCmd 	= ENABLE;
  	
	EXTI_Init(&exti_init_config);	 	//����EXTI_InitTypeDef��ָ���Ĳ�����ʼ������EXTI�Ĵ���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: exit_nvic_config
//	����˵��: �ж�������������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-25
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
static void exti_nvic_config(void)
{
	NVIC_InitTypeDef nvic_init_config;
	
	nvic_init_config.NVIC_IRQChannel 					= EXTI0_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	nvic_init_config.NVIC_IRQChannelPreemptionPriority 	= 0x02;//��ռ���ȼ�2
	nvic_init_config.NVIC_IRQChannelSubPriority 		= 0x02;//�����ȼ�1
	nvic_init_config.NVIC_IRQChannelCmd 				= ENABLE;
	
	NVIC_Init(&nvic_init_config);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: exti_init
//	����˵��: �ⲿ�жϳ�ʼ��
//	��    ��: 	exti_no���жϺ�
//	�� �� ֵ: ��
//	��    ��: 2020-04-25
//  ��    ע: �ⲿ���ô˺���,ʵ��EXTI�ĳ�ʼ������
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void exti_init(uint8_t exti_no)
{
	if (exti_no == 0)
	{
		exti_gpio_config();
		exti_config();
		exti_nvic_config();
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: EXTI0_IRQHandler
//	����˵��: �ⲿ�ж�0������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-25
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)  
	{
		g_exti_cnt++;
		
		if (g_exti_cnt % 2)
		{
			Bsp_LedOn(0);	//����OLED0
		}
		else 
		{
			Bsp_LedOff(0);	//Ϩ��OLED0
		}
		
		if (g_exti_cnt > 200)
		{
			g_exti_cnt = 0;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line0);	//���EXTI0��·����
	}
}

#endif	//__PRJ_STM32F10X_DRVEXTI_C__
