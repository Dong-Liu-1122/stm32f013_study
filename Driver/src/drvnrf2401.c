#ifndef __PRJ_STM32F10X_DRVNRF2401_C__
#define __PRJ_STM32F10X_DRVNRF2401_C__

//---------------------------------------------------------------------------------------------------------------------------------------------
//ƽ    ̨:				STM32F10X
//��    ��:    		 	drvadc.c
//��    ��:       		����AI
//��� ��:   			Vxxx
//�ļ��汾:   			V1.0.0
//��   ��:      		2020��03��11��
//˵   ��:      	 	ADC����ʵ��
//----------------------------------------------------------------------------------------------------------------------------------------------

#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h" 
#include "stm32f10x_rcc.h"
#include "drvnrf2401.h"
#include "hardware_spi.h"
#include "delay.h"

const uint8_t TX_ADDRESS_X[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//���Ͷ˵�ַ
const uint8_t RX_ADDRESS_X[RX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};//���ն˵�ַ

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_gpio_init
//	����˵��: nrf24l01 gpio ��ʼ��
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-11
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_gpio_init(void)
{
    GPIO_InitTypeDef gpio_config_init;

	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO_CS, ENABLE);		//����NRF CS GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO_CE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO_IRQ, ENABLE);

	gpio_config_init.GPIO_Pin 	= NRF_CS_IO;	//NRF_CS_IO IO��ʼ��
	gpio_config_init.GPIO_Mode 	= GPIO_Mode_Out_PP;  //�������
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_CS, &gpio_config_init);

	GPIO_SetBits(PORT_NRF_CS, NRF_CS_IO);	//IO��ʼ״̬������Ϊ�ߵ�ƽ
	
	gpio_config_init.GPIO_Pin 	= NRF_CE_IO;
	gpio_config_init.GPIO_Mode 	= GPIO_Mode_Out_PP;
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_CE, &gpio_config_init);
	
	GPIO_SetBits(PORT_NRF_CE, NRF_CE_IO);
	
	gpio_config_init.GPIO_Pin 	= NRF_IRQ_IO;
	gpio_config_init.GPIO_Mode 	= GPIO_Mode_IPU;//��������
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_IRQ, &gpio_config_init);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_write_reg
//	����˵��: nrf24l01 д�Ĵ���
//	��    ��: 	reg_no���Ĵ���
//				reg_val��д��Ĵ�����ֵ
//	�� �� ֵ: 	status���Ĵ���״ֵ̬
//	��    ��: 2020-04-15
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_write_reg(uint8_t reg_no, uint8_t reg_val)
{
	uint8_t status = 0;
	
	NRF_CS_0();
	status = spi_master_send_recv_byte(1, reg_no);
	spi_master_send_recv_byte(1, reg_val);
	NRF_CS_1();
	
	return status;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_read_reg
//	����˵��: nrf24l01 ���Ĵ���
//	��    ��: 	reg_no���Ĵ���
//	�� �� ֵ: 	reg_val���Ĵ���ֵ
//	��    ��: 2020-04-15
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_read_reg(uint8_t reg_no)
{
	uint8_t reg_val = 0;
	
	NRF_CS_0();
	spi_master_send_recv_byte(1, reg_no);
	reg_val = spi_master_send_recv_byte(1, 0xff);	
	NRF_CS_1();
	
	return reg_val;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_read_buff
//	����˵��: nrf24l01 ������
//	��    ��: 	reg_no���Ĵ���
//				pbdata������ָ��
//				read_length����ȡ���ݳ���
//	�� �� ֵ: 	status���Ĵ���״ֵ̬
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_read_buff(uint8_t reg_no, uint8_t *pbdata, uint16_t read_length)
{
	uint8_t status = 0;
	uint16_t i = 0;
	
	NRF_CS_0();
	
	status = spi_master_send_recv_byte(1, reg_no);
	
	for (i = 0; i < read_length; i++)
	{
		*pbdata++ = spi_master_send_recv_byte(1, 0xff);	//����ff�õ�spi��ʱ��
	}
	
	NRF_CS_1();
	
	return status;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_write_buff
//	����˵��: nrf24l01 д����
//	��    ��: 	reg_no���Ĵ���
//				pbdata������ָ��
//				write_length����ȡ���ݳ���
//	�� �� ֵ: 	status���Ĵ���״ֵ̬
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_write_buff(uint8_t reg_no, uint8_t *pbdata, uint16_t write_length)
{
	uint8_t status = 0;
	uint16_t i = 0;
	
	NRF_CS_0();
	
	status = spi_master_send_recv_byte(1, reg_no);
	
	for (i = 0; i < write_length; i++)
	{
		spi_master_send_recv_byte(1, pbdata[i]);	//����д������
	}
	
	NRF_CS_1();
	
	return status;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_tx_mode
//	����˵��: nrf24l01 ����ģʽ����
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_tx_mode(void)
{
	NRF_CE_0();
	
	nrf24l01_write_buff(W_REGISTER + TX_ADDR, (uint8_t *)TX_ADDRESS_X, TX_ADR_WIDTH);	//дTX�ڵ��ַ
	nrf24l01_write_buff(W_REGISTER + RX_ADDR_P0, (uint8_t *) RX_ADDRESS_X, RX_ADR_WIDTH);	//дRX�ڵ��ַ,Ϊ���Զ�ʹ��ACK
	nrf24l01_write_reg(W_REGISTER + EN_AA, 0x01);	//ʹ��ͨ��0�Զ�Ӧ��
	nrf24l01_write_reg(W_REGISTER + EN_RXADDR, 0x01);	//ʹ��ͨ��0���յ�ַ
	nrf24l01_write_reg(W_REGISTER + SETUP_PETR, 0x1a);	//�����Զ��ط����ʱ��:500us+86us,����ش����:10��
	nrf24l01_write_reg(W_REGISTER + RF_CH, 40);	//����ͨ��Ϊ40
	nrf24l01_write_reg(W_REGISTER + RF_SETUP, 0x0f);	//���÷������:0dB����;2Mnps;���������濪��
	nrf24l01_write_reg(W_REGISTER + NRF24L01_CONFIG, 0x0e);	//��������:PWR_UP;EN_CRC;16BIT_CRC;����ģʽ;���������ж�
	
	NRF_CE_1();
	
	delay_us(12);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_rx_mode
//	����˵��: nrf24l01 ����ģʽ����
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_rx_mode(void)
{
	NRF_CE_0();
	
	nrf24l01_write_buff(W_REGISTER + RX_ADDR_P0, (uint8_t *) RX_ADDRESS_X, RX_ADR_WIDTH);	//дRX��ַ�ڵ�
	nrf24l01_write_reg(W_REGISTER + EN_AA, 0x01);	//ʹ��ͨ��0�Զ�Ӧ��
	nrf24l01_write_reg(W_REGISTER + EN_RXADDR, 0x01);	//ʹ��ͨ��0���յ�ַ
	nrf24l01_write_reg(W_REGISTER + RF_CH, 40);	//����RFͨ��Ƶ��
	nrf24l01_write_reg(W_REGISTER + RX_PW_P0, RX_PLOAD_WIDTH);	//ѡ��ͨ��0��Ч���ݿ��
	nrf24l01_write_reg(W_REGISTER + RF_SETUP, 0x0f); //����TX�������:0db����,2Mbps,���������濪��
	nrf24l01_write_reg(W_REGISTER + NRF24L01_CONFIG, 0x0f);	//��������:PWR_UP;EN_CRC;16BIT_CRC;����ģʽ;���������ж�
	
	NRF_CE_1();//CEΪ��,�������ģʽ
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_tx_packet
//	����˵��: nrf24l01 ������������
//	��    ��: 	tx_buff�����͵�����
//	�� �� ֵ: ����״̬(MAX_TX�����͵�������;TX_OK��������ɣ�TX_FAIL������ʧ��)
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_tx_packet(uint8_t *tx_buff)
{
	uint8_t ret_val = 0;

	NRF_CE_0();
	
	nrf24l01_write_buff(W_TX_PAYLOAD, tx_buff, TX_PLOAD_WIDTH);	//д���ݵ�txbuf,32�ֽ�
	
	NRF_CE_1();	//��������
	
	while (GET_NRF_IRQ_STATUS);//�ȴ��������
	
	ret_val = nrf24l01_read_reg(NRF24L01_STATUS);	//��ȡ״̬�Ĵ�����ֵ
	nrf24l01_write_reg(W_REGISTER + NRF24L01_STATUS, ret_val);	//���TX_DS or MAX_RT���жϱ�־
	
	if (ret_val & MAX_TX)	//�ﵽ����ط�����
	{
		nrf24l01_write_reg(FLUSH_TX, 0xff);	//���TX FIFO�Ĵ���
		
		return MAX_TX;
	}
	
	if(ret_val & TX_OK)	//�������
	{
		return TX_OK;
	}
	
	return TX_FAIL;//����ʧ��
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_rx_packet
//	����˵��: nrf24l01 ������������
//	��    ��: 	rx_buff�����͵�����
//	�� �� ֵ: ����״̬(RX_SUCCESS�����ճɹ�;RX_FAIL������ʧ��)
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_rx_packet(uint8_t *rx_buf)
{
	uint8_t ret_val = 0;

	NRF_CE_1();
	
	while(GET_NRF_IRQ_STATUS);
	
	NRF_CE_0();

	ret_val = nrf24l01_read_reg(NRF24L01_STATUS);	//��ȡ״̬�Ĵ�����ֵ
	nrf24l01_write_reg(W_REGISTER+NRF24L01_STATUS, ret_val);	//���TX_DS or MAX_RT���жϱ�־
	
	if(ret_val & RX_OK)	//���յ�����
	{
		nrf24l01_read_buff(R_RX_PAYLOAD, rx_buf, RX_PLOAD_WIDTH);	//��ȡ����
		nrf24l01_write_reg(FLUSH_RX, 0xff);	//���RX FIFO�Ĵ���
		
		return RX_SUCCESS;
	}
	
	return RX_FAIL;	//û�н��յ�����
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_check_state
//	����˵��: nrf24l01 ״̬���
//	��    ��: ��
//	�� �� ֵ: ����״̬(0��ok;1��fail)
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint8_t nrf24l01_check_state(void)
{
	uint8_t buff[5]={0xa5, 0xa5, 0xa5, 0xa5, 0xa5};
	uint8_t i = 0;

	nrf24l01_write_buff(W_REGISTER+TX_ADDR, buff, 5);//д��5�ֽڵĵ�ַ
	nrf24l01_read_buff(TX_ADDR, buff, 5);
	
	for(i = 0; i < 5; i++)
	{
		if(buff[i] != 0xa5)
		{
			break;
		}
	}
	
	if(i != 5)
	{
		return 1;
	}
	
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_power_down_mode
//	����˵��: nrf24l01 �����µ�ģʽ
//	��    ��: ��
//	�� �� ֵ: ����״̬(0��ok;1��fail)
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_power_down_mode(void)
{
	NRF_CS_0();
	nrf24l01_write_reg(NRF24L01_CONFIG, 0x00);
	NRF_CS_1();
	
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_init
//	����˵��: nrf24l01 ��ʼ��
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-04-16
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_init(void)
{
	nrf24l01_gpio_init();
	
	NRF_CS_1();
	NRF_CE_0();
}

#endif /* __PRJ_STM32F10X_DRVNRF2401_C__ */
