#ifndef __FCAN_FUNATION_H
#define __FCAN_FUNATION_H

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

void Can_Init_PeiZhi(void);
void CAN_HuiHuanCeShi(void);
u8 CAN_SetMsg(u32 MoKuaiHao,u32 ZhiLingMoShi,u8 XiaoGuoMoShi,u8 XiaoGuoWei_1,u8 XiaoGuoWei_2);
u8 CAN_ShuJuFaSong(u8 DATA_1,u8 DATA_2,u8 DATA_3,u8 DATA_4,u8 DATA_5,u8 DATA_6,u8 DATA_7,u8 DATA_8);
void USB_LP_CAN_RX0_IRQHandler(void);
#endif
