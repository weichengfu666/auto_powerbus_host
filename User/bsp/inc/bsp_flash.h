/*
*********************************************************************************************************
*
*	模块名称 : cpu内部falsh操作模块
*	文件名称 : bsp_cpu_flash.h
*	版    本 : V1.0
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _BSP_CPU_FLASH_H_
#define _BSP_CPU_FLASH_H_

#include "bsp.h"

#define FLASH_BASE_ADDR	0x08000000			/* Flash基地址 */
#define	FLASH_SIZE		(512*1024)		/* Flash 容量 */
#define SECTOR_MASK			0xFFFFF800  /* 对于F103，  512K FLASH , 每个PAGE = 2K 字节，总共 256个 PAGE  */
#define FLASH_IS_EQU		0   /* Flash内容和待写入的数据相等，不需要擦除和写操作 */
#define FLASH_REQ_WRITE		1	/* Flash不需要擦除，直接写 */
#define FLASH_REQ_ERASE		2	/* Flash需要先擦除,再写 */
#define FLASH_PARAM_ERR		3	/* 函数参数错误 */

//配置flash属性：设置有效flash地址范围，单次可写入最大页数 
#define FLASH_STARTADDR 0X08010000      //可写入flash的起始地址
#define PAGE_SIZE 4                     //单次可写入最大页数

uint8_t readFlashStr ( uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize );    //读Flash
uint8_t writeFlashStr ( uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize );    // 写Flash（ 可配置操作的flash范围，在指定flash范围内，可以任意地址，任意字节数修改 ）推荐使用

#if 0
uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize);
uint8_t readFlashStr(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize);
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize);       // （ BUG: 不支持写入地址和写入字节数为奇数，写入某页时，如果需要擦除，则会破坏整页数据 ）不建议使用
#endif

#endif


/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/

