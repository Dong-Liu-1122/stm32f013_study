#ifndef __PRJ_STM32F10X_DRVNRF2401_C__
#define __PRJ_STM32F10X_DRVNRF2401_C__

//---------------------------------------------------------------------------------------------------------------------------------------------
//平    台:				STM32F10X
//文    件:    		 	drvadc.c
//作    者:       		霁风AI
//库版 本:   			Vxxx
//文件版本:   			V1.0.0
//日   期:      		2020年03月11日
//说   明:      	 	ADC驱动实现
//----------------------------------------------------------------------------------------------------------------------------------------------

#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h" 
#include "stm32f10x_rcc.h"
#include "drvnrf2401.h"
#include "hardware_spi.h"
#include "delay.h"

//---------------------------------------------------------------------------------------------------------------------------------------------
//	函 数 名: nrf24l01_gpio_init
//	功能说明: nrf24l01 gpio 初始化
//	形    参: 无
//	返 回 值: 无
//	日    期: 2020-03-11
//  备    注: 
//	作    者: by 霁风AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_gpio_init(void)
{
    GPIO_InitTypeDef gpio_config_init;

	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO_CS, ENABLE);		//开启NRF CS GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO_CE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO_IRQ, ENABLE);

	gpio_config_init.GPIO_Pin 	= NRF_CS_IO;	//NRF_CS_IO IO初始化
	gpio_config_init.GPIO_Mode 	= GPIO_Mode_Out_PP;  //推挽输出
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_CS, &gpio_config_init);

	GPIO_SetBits(PORT_NRF_CS, NRF_CS_IO);	//IO初始状态都设置为高电平
	
	gpio_config_init.GPIO_Pin 	= NRF_CE_IO;
	gpio_config_init.GPIO_Mode 	= GPIO_Mode_Out_PP;
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_CE, &gpio_config_init);
	
	GPIO_SetBits(PORT_NRF_CE, NRF_CE_IO);
	
	gpio_config_init.GPIO_Pin 	= NRF_IRQ_IO;
	gpio_config_init.GPIO_Mode 	= GPIO_Mode_IPU;//上拉输入
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_IRQ, &gpio_config_init);
}

uint8_t nrf24l01_write_reg(uint8_t reg_no, uint8_t reg_val)
{
	uint8_t status = 0;
}

#endif /* __PRJ_STM32F10X_DRVNRF2401_C__ */
