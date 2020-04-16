#ifndef __DRVNRF2401_H__
#define __DRVNRF2401_H__

#define RCC_PCLK_NRF_GPIO_CS	RCC_APB2Periph_GPIOC
#define RCC_PCLK_NRF_GPIO_CE	RCC_APB2Periph_GPIOA
#define RCC_PCLK_NRF_GPIO_IRQ	RCC_APB2Periph_GPIOA

#define NRF_CS_IO     			(GPIO_Pin_4)	//CS:PC4
#define PORT_NRF_CS				GPIOC
#define NRF_CS_0()				(GPIO_ResetBits(PORT_NRF_CS, NRF_CS_IO))		
#define NRF_CS_1() 				(GPIO_SetBits(PORT_NRF_CS, NRF_CS_IO))

#define NRF_CE_IO     			(GPIO_Pin_4)	//CE:PA4
#define PORT_NRF_CE				GPIOA
#define NRF_CE_0()				(GPIO_ResetBits(PORT_NRF_CE, NRF_CE_IO))		
#define NRF_CE_1() 				(GPIO_SetBits(PORT_NRF_CE, NRF_CE_IO))

#define NRF_IRQ_IO     			(GPIO_Pin_1)	//CE:PA1
#define PORT_NRF_IRQ			GPIOA
#define NRF_IRQ_0()				(GPIO_ResetBits(PORT_NRF_IRQ, NRF_IRQ_IO))		
#define NRF_IRQ_1() 			(GPIO_SetBits(PORT_NRF_IRQ, NRF_IRQ_IO))
#define GET_NRF_IRQ_STATUS		(GPIO_ReadInputDataBit(PORT_NRF_IRQ, NRF_IRQ_IO))

//����궨��
#define R_REGISTER			0x00
#define W_REGISTER			0x20
#define R_RX_PAYLOAD		0x61
#define W_TX_PAYLOAD		0XA0
#define FLUSH_TX			0xE1
#define FLUSH_RX			0xE2
#define RESUE_TX_PL			0xE3
#define ACTIVATE			0x50
#define R_RX_PL_WID			0x60
#define W_AC_PAYLOAD		0xA8
#define W_TX_PAYLOAD_NOACK	0xB0
#define NRF24L01_NOP		0xFF

//NRF24L01�Ĵ���
#define	NRF24L01_CONFIG		0x00	//���üĴ���:bit0:0-TX;1-RX;bit1:�ϵ�ʹ��ѡ��;bit2:CRCģʽ;bit3:CRCʹ��
									//bit4:����ط������ж�(MAX_RT)ʹ��;bit5:�ж�TX_DSʹ��;bit6:�ж�RX_DRʹ��
#define EN_AA				0x01
#define EN_RXADDR			0x02
#define SETUP_AW			0x03
#define SETUP_PETR			0x04
#define RF_CH				0x05
#define RF_SETUP			0x06
#define NRF24L01_STATUS		0x07
#define OBSERVE_TX			0x08
#define RPD					0X09			
#define RX_ADDR_P0			0x0A
#define RX_ADDR_P1			0x0B
#define RX_ADDR_P2			0x0C
#define RX_ADDR_P3			0x0D
#define RX_ADDR_P4			0x0E
#define RX_ADDR_P5			0x0F
#define TX_ADDR				0x10
#define RX_PW_P0			0x11
#define RX_PW_P1			0x12
#define RX_PW_P2			0x13
#define RX_PW_P3			0x14
#define RX_PW_P4			0x15
#define RX_PW_P5			0x16
#define FIFO_STATUS			0x17
#define DYNPD				0x1C
#define NRF24L01_FEATURE	0x1D

//nrf24l01�������ݿ�ȶ���
#define TX_ADR_WIDTH		5	//5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH		5	//5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH		5//32	//32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH		5//32	//32�ֽڵ��û����ݿ��

#define MAX_TX				0x10	//�ﵽ����ʹ����ж�
#define TX_OK				0x20	//��������ж�
#define RX_OK				0x40	//���������ж�
#define TX_FAIL				0xff	//�ﵽ����ʹ����ж�
#define RX_FAIL				0xff	//�ﵽ����ʹ����ж�
#define RX_SUCCESS			0x00	//�ﵽ����ʹ����ж�

extern void nrf24l01_gpio_init(void);

#endif	//__DRVNRF2401_H__

