#include "stm32f10x.h"
#include <stdio.h>

u8 cs_i=0,cs_j=0;
extern u8  DianNaoJieShou2_HuanCun_i[5];
extern uchar Time_500Ms_Flag,RxData1,RxData2,ZhongDuan_TX_Flag[4];


int main(void)
{
	GPIO_Init_PeiZhi();
	Tim_Init_PeiZhi();
	NVIC_Init_PeiZhi();
	USART_InIt_PeiZhi();
	Host_Init(); 
	USART_SendData(USART1,0x52);
	USART_SendData(USART1,0x61);
	USART_SendData(USART2,0x52);
	USART_SendData(USART2,0x61);
  while (1) 
  {
		ZongXunHuan(); 
		PC_ProcessRecvData(); 
		Slave_ProcessRecvData(); 
		if(Time_500Ms_Flag==1)
		{	
			if((uchar)GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==1)
			{
				GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_RESET);
			}else{
				GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_SET);
			}
			Time_500Ms_Flag=0;
		}
  }
}
#if 1

//
#endif


