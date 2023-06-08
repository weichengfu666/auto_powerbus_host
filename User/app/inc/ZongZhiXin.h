#ifndef __ZONGZHIXIN_H
#define __ZONGZHIXIN_H
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

#define Read_ShuRu1 (uchar)GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)			//						
	
#define Write_ShuChu1_Set GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_RESET)			//
	
#define Write_ShuChu1_ReSet GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_SET)

extern u16 AnWeiSouXun_Flag, AnWeiSouXun_Time, FenJi_Num, FenJiHuiYin_Flag;
extern u16 CheckSlaveState_Flag, CheckSlaveState_Time, CheckSlaveState_index;

void Host_Init(void);
void Host_querySerialNum(void);
void Host_checkSlaveState( void );
void ZongXunHuan(void);
void Host_reponsePC(void);
void Host_responseSlave(void);
#endif

