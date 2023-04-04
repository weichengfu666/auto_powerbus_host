#ifndef __ZONGZHIXIN_H
#define __ZONGZHIXIN_H
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

#define Read_ShuRu1 (uchar)GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)			//						
	
#define Write_ShuChu1_Set GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_RESET)			//
	
#define Write_ShuChu1_ReSet GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_SET)

void ZhuJi_Init(void);
void ZongXunHuan(void);
#endif

