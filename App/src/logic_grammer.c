#ifndef __PRJ_STM32F10X_LOGIC_GRAMMER_C__
#define __PRJ_STM32F10X_LOGIC_GRAMMER_C__

#include "Typedef.h"
#include "logic_grammer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//--------------------------------------------------------------------------------------------------------
//	�� �� ��: sprintf_test
//	����˵��: sprintf���ܲ���
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-21
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void sprintf_test(void)
{
	char buf[100] = {0};
	double data = 3.141593;
	uint16_t len = 0;
	uint8_t test_buff[5] = {55, 22, 66, 77, 99};
	
	len = sprintf((char *)buf, "%f", data);
	printf("----------------------------------------------------------------- \r\n");
	printf("buf is %s \r\n", buf);
	printf("sprintf return len is %d \r\n", len);
	
	len = 0;
	
	for (uint16_t i = 0; i < sizeof(test_buff); i++)
	{
		len += sprintf((char *)buf + i * 2, "%d", test_buff[i]);	//��������ת��Ϊ�ַ���
	}
	printf("test_buff val is %s \r\n", buf);
	printf("sprintf return len is %d \r\n", len);
	printf("----------------------------------------------------------------- \r\n");
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: My_Memcpy
//	����˵��: memcpy ԭ��ʵ��
//	��    ��: 	dest��Ŀ�ĵ�ַ
//				src��Դ��ַ
//				count�����ݳ���
//	�� �� ֵ: ��
//	��    ��: 2020-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void *My_Memcpy(void *dest, const void *src, unsigned int count)
{
	char *pdest = (char *)dest;
	char *psrc = (char *)src;

	if (pdest == NULL || psrc == NULL)
	{
		return NULL;
	}

	if (pdest == psrc)
	{
		return 0;
	}

	if (pdest > psrc)	//Ŀ�ĵ�ַ��Դ��ַ�����ص������
	{
		while (count--)
		{
			*(pdest + count) = *(psrc + count);
		}
	}
	else
	{
		while (count--)
		{
			*pdest++ = *psrc++;
		}
	}
	return pdest;
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: My_Memset
//	����˵��: memset ԭ��ʵ��
//	��    ��: 	dest��Ŀ�ĵ�ַ
//				src��Դ��ַ
//				len�����ݳ���
//	�� �� ֵ: ��
//	��    ��: 2020-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void *My_Memset(void *dest, int n, unsigned int len)
{
	if (dest == NULL)
		return NULL;
	char *pdest = (char *)dest;
	while (len--)
	{
		*pdest++ = n;
	}

	return dest;
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: My_Memcmp
//	����˵��: memcmp ԭ��ʵ��
//	��    ��: 	dest��Ŀ�ĵ�ַ
//				src��Դ��ַ
//				count�����ݳ���
//	�� �� ֵ: ��
//	��    ��: 2020-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
int My_Memcmp(void *str1, void *str2, int count)
{
	char *ptr1 = (char *)str1;
	char *ptr2 = (char *)str2;

	if (!count)
	{
		return 0;
	}

	while (count--)
	{
		if (*ptr1 == *ptr2)
		{
			ptr1 = ptr1 + 1;
			ptr2 = ptr2 + 1;
		}
		else
		{
			return *ptr1 - *ptr2;
		}
	}
	return *ptr1 - *ptr2;
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: My_Strlen
//	����˵��: strlen ԭ��ʵ��
//	��    ��: 	src������Ŀ�ĵ�ַ
//	�� �� ֵ: ��
//	��    ��: 2020-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
unsigned int My_Strlen(const char *str)
{
	int str_len = 0;

	while (*str++ != '\0')
	{
		str_len++;
	}
	
	return str_len;
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: My_Strcpy
//	����˵��: strcpy ԭ��ʵ��
//	��    ��: 	src������Ŀ�ĵ�ַ
//	�� �� ֵ: ��
//	��    ��: 2020-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
char *My_Strcpy(char *dest, const char *src)
{
	char *tmp = (char *)dest;
	
	if ((dest == NULL) || (src == NULL))
	{
		return 0;
	}
	
	while (*src != '\0')
	{
		*tmp++ = *src++;
	}
	
	*tmp = '\0';	//�ַ�����������'\0'
	
	return tmp;
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: My_Strcmp
//	����˵��: strcmp ԭ��ʵ��
//	��    ��: 	src������Ŀ�ĵ�ַ
//	�� �� ֵ: ��
//	��    ��: 2020-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
int My_Strcmp(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		return NULL;
	}
	
	while (*str1 == *str2)
	{
		str1++;
		str2++;
		
		if (*str1 == '\0' || *str2 == '\0')
		{
			break;
		}
	}
	
	return *str1 - *str2;
}

void strcmp_test(void)
{
	int ret = 0;
//	char test_buf1[6] = "ABCBE";
//	char test_buf2[3] = "AB";
	char test_buf1[6] = {1, 2, 3, 4, 5, 6};
	char test_buf2[6] = {1, 2, 3, 7, 5, 6};
	
	ret = My_Strcmp(test_buf1, test_buf2);
	printf("ret val is %d \r\n", ret);
}
	
void strcpy_test(void)
{
	char test_buf1[6] = "ABCDE";
	char test_buf2[100] = {0};
	
	My_Strcpy(test_buf2, test_buf1);
	printf("strcpy test %s \r\n", test_buf2);
}

void memcmp_test(void)
{
	char str1[] = "abcd";
	char str2[] = "abcd";
	int ret = 0;

	ret = My_Memcmp(str1, str2, 4);
	printf("ret val is %d \r\n", ret);

	memcpy(str1, "abce", 4);
	ret = My_Memcmp(str1, str2, 4);
	printf("ret val is %d \r\n", ret);

	memcpy(str1, "abcc", 4);
	ret = My_Memcmp(str1, str2, 4);
	printf("ret val is %d \r\n", ret);
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: cpu_mem_endian
//	����˵��: ��С�˲���
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2019-03-22
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void cpu_mem_endian(void)
{
	union un_test 
	{
		uint8_t x;
		uint16_t y;
	}un_endian_test;
	
	un_endian_test.y = 0x1234;
	
	if (un_endian_test.x == 0x34)
	{
		printf("cpu is little endian \r\n");
	}
	if (un_endian_test.x == 0x12)
	{
		printf("cpu is big endian \r\n");
	}
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: Crc_B16
//	����˵��: CRC����
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2019-03-28
//  ��    ע: ��
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
uint16_t Crc_B16(uint8_t *Indata, uint16_t len, uint16_t CrcTmp)
{
	uint16_t y = 0;
	uint16_t yy = 0;
	uint8_t x = 0;
	uint32_t i = 0;
	uint32_t j = 0;

     y = ~CrcTmp & 0xffff;
	
	for(i = 0; i < len; i++)
	{
		x = Indata[i];
		for (j = 0; j < 8; j++)
		{
			if (((y^x) & 1) !=0) 
			{
				yy= 0x8408;
			}
			else 
			{
				yy=0;
			}
		x >>= 1;
		y >>= 1;
		y ^= yy;
		}
	}
	
	return (~y & 0xffff);
}

void bubble_sort(uint32_t *pbdata, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint32_t temp_value = 0;
	uint8_t sort_flag = 0;
	
	for (i = 0; i < length-1; i++)
	{
		sort_flag = 1;
		
		for (j = 0; j < length-1-i; j++)
		{
			if (pbdata[j] > pbdata[j+1])
			{
				temp_value	= pbdata[j];
				pbdata[j]	= pbdata[j+1];
				pbdata[j+1]	= temp_value;
				
				sort_flag = 0;
			}
		}
		
		if (sort_flag == 1)
		{
			goto exit;
		}
	}
	
exit:	
	return;
}

#endif	//__PRJ_STM32F10X_LOGIC_GRAMMER_C__
