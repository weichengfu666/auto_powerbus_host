/*
*********************************************************************************************************
*
*	ģ������ : cpu�ڲ�falsh����ģ��
*	�ļ����� : bsp_cpu_flash.h
*	��    �� : V1.0
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _BSP_CPU_FLASH_H_
#define _BSP_CPU_FLASH_H_

#include "bsp.h"

#define FLASH_BASE_ADDR	0x08000000			/* Flash����ַ */
#define	FLASH_SIZE		(512*1024)		/* Flash ���� */
#define SECTOR_MASK			0xFFFFF800  /* ����F103��  512K FLASH , ÿ��PAGE = 2K �ֽڣ��ܹ� 256�� PAGE  */
#define FLASH_IS_EQU		0   /* Flash���ݺʹ�д���������ȣ�����Ҫ������д���� */
#define FLASH_REQ_WRITE		1	/* Flash����Ҫ������ֱ��д */
#define FLASH_REQ_ERASE		2	/* Flash��Ҫ�Ȳ���,��д */
#define FLASH_PARAM_ERR		3	/* ������������ */

//����flash���ԣ�������Чflash��ַ��Χ�����ο�д�����ҳ�� 
#define FLASH_STARTADDR 0X08010000      //��д��flash����ʼ��ַ
#define PAGE_SIZE 4                     //���ο�д�����ҳ��

uint8_t readFlashStr ( uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize );    //��Flash
uint8_t writeFlashStr ( uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize );    // дFlash�� �����ò�����flash��Χ����ָ��flash��Χ�ڣ����������ַ�������ֽ����޸� ���Ƽ�ʹ��

#if 0
uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize);
uint8_t readFlashStr(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize);
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize);       // �� BUG: ��֧��д���ַ��д���ֽ���Ϊ������д��ĳҳʱ�������Ҫ����������ƻ���ҳ���� ��������ʹ��
#endif

#endif


/***************************** ���������� www.armfly.com (END OF FILE) *********************************/

