#ifndef __USART_FUNATION_H
#define __USART_FUNATION_H
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

void USART_InIt_PeiZhi(void);
void Num_Data(USART_TypeDef* USARTx,long num);
void Str_Data(USART_TypeDef* USARTx,char *StrData);
void TonXunFaSong(USART_TypeDef* USARTx,u8 DianNaoFaSong_HuanCun[],u16 DianNaoFaSong_START_ADDR,u8 DianNaoFaSong_Len);
void PC_RecvData(u8 ZhuJi_Data);
void PC_ProcessRecvData(void);
void Slave_RecvData(u8 ZhuJi_Data2);
void Slave_ProcessRecvData(void);

#endif

