#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

extern GPIO_InitTypeDef GPIO_InitStructure;
extern u8 CRC_L,CRC_H;
extern u8 GongNeng_HuanCun[2060],GongNeng2_HuanCun[150];
extern u16 ZhiLin_ChangDu[256],ZhiLin2_ChangDu[256];
USART_InitTypeDef USART_InitStructure;
uchar RxBuffer1,RxBuffer2,Rx_i,ZhongDuan_TX_Flag[4]={0,0,0,0};
u8 DianNaoJieShou_HuanCun[5][2060],RX1_i,DianNaoJieShou2_HuanCun[5][150],RX2_i;
u16 ZhuJi_ShuJuChuLi_i=0,DianNaoJieShou_HuanCun_i[5]={0,0,0,0,0},ZhuJi2_ShuJuChuLi_i=0,DianNaoJieShou2_HuanCun_i[5]={0,0,0,0,0};
u8 CRC_HuanCun[2060];
u16 ZhuJi_ShuJuChuLi2_i=0,ZhuJi_ShuJuChuLi2_j=0,ZhuJi2_ShuJuChuLi2_i=0,ZhuJi2_ShuJuChuLi2_j=0;
u16 DianNaoFaSong_i;
extern u16 AnWeiSouXun_Flag;
extern u16 AnWeiSouXun_Time;
extern u8 FenJi_XuLieHao_H1[5];

void USART_InIt_PeiZhi(void)
{		
	u8 USART_InIt_i,USART_InIt_j;
	for(USART_InIt_i=0;USART_InIt_i<5;USART_InIt_i++)
	{
		for(USART_InIt_j=0;USART_InIt_j<20;USART_InIt_j++)
		{
			DianNaoJieShou_HuanCun[USART_InIt_i][USART_InIt_j]=0;
		}
	}
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1 ,ENABLE);	//使能usart1时钟			
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);																					//使能usart2时钟	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2); 
	
	//	/*配置USART1模式*/
	USART_InitStructure.USART_BaudRate = 9600;                               	//波特率设置为9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;               //配置串口传输字节长度为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                    //配置停止位为1
	USART_InitStructure.USART_Parity = USART_Parity_No;                       //不设置奇偶校验位	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不采用硬件流
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//设置串口为全双工通讯
	USART_Init(USART1, &USART_InitStructure);																	//向寄存器写入配置参数
	USART_ITConfig(USART1, USART_IT_RXNE ,ENABLE);														//打开USART1的串口接收中断
	USART_ITConfig(USART1, USART_IT_TC ,ENABLE);															//打开USART1的串口发送中断
	USART_Cmd(USART1, ENABLE);																								//使能USART1外设
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);                           //清除中断标志位
	USART_ClearITPendingBit(USART1, USART_IT_TC);                           	//清除中断标志位
	
	USART_InitStructure.USART_BaudRate = 9600;                               	//波特率设置为9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;               //配置串口传输字节长度为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                    //配置停止位为1
	USART_InitStructure.USART_Parity = USART_Parity_No;                       //不设置奇偶校验位	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不采用硬件流
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//设置串口为全双工通讯
	USART_Init(USART2, &USART_InitStructure);																	//向寄存器写入配置参数
	USART_ITConfig(USART2, USART_IT_RXNE ,ENABLE);														//打开USART2的串口接收中断
	USART_ITConfig(USART2, USART_IT_TC ,ENABLE);															//打开USART2的串口发送中断
	USART_Cmd(USART2, ENABLE);																								//使能USART2外设
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);                           //清除中断标志位
	USART_ClearITPendingBit(USART2, USART_IT_TC);                           	//清除中断标志位
	
}
   
void USART1_IRQHandler(void)
{
    //判断现在的中断类型
    if(USART_GetITStatus(USART1,USART_IT_RXNE)== SET)
    {
			if(RxBuffer1==0xa5)
			{
				if(USART_ReceiveData(USART1)==0x01)
				{
					for(RX1_i=0;RX1_i<5;RX1_i++)
					{
						if(DianNaoJieShou_HuanCun_i[RX1_i]==0)
						{
							DianNaoJieShou_HuanCun_i[RX1_i]=2;
							break;
						}
					}
				}
			}
      RxBuffer1=USART_ReceiveData(USART1);												//读接收寄存器，系统自动清除接收中断标志位
			ZhuJi_ShuJuChuLi(RxBuffer1);
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);             //清除中断标志位
    }
    if(USART_GetITStatus(USART1,USART_IT_TC)== SET)
    {
      ZhongDuan_TX_Flag[0]=1;
			USART_ClearITPendingBit(USART1, USART_IT_TC);              	//清除中断标志位
    }
}
void USART2_IRQHandler(void)
{
    //判断现在的中断类型
    if(USART_GetITStatus(USART2,USART_IT_RXNE)== SET)
    {
			if(AnWeiSouXun_Flag>0)//大于0时等待10ms未收到数据后启动下一次发送，如果收到返回数据则重新计时
			{
				AnWeiSouXun_Time=1;//收到返回数据则重新计时
				if(AnWeiSouXun_Flag>10000)//大于10000为等待分机返回模式，这里也表示还未收到过返回数据
				{
					AnWeiSouXun_Flag-=10000;//收到返回数据标志
				}
			}
			if(RxBuffer2==0xa5)
			{
				for(RX2_i=0;RX2_i<5;RX2_i++)
				{
					if(DianNaoJieShou2_HuanCun_i[RX2_i]==0)
					{
						DianNaoJieShou2_HuanCun_i[RX2_i]=3;
						break;
					}
				}
			}
      RxBuffer2=USART_ReceiveData(USART2);												//读接收寄存器
			ZhuJi2_ShuJuChuLi(RxBuffer2); 
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);             //清除中断标志位
    }
    if(USART_GetITStatus(USART2,USART_IT_TC)== SET)
    {
      ZhongDuan_TX_Flag[1]=1;
			USART_ClearITPendingBit(USART2, USART_IT_TC);              	//清除中断标志位
    }
} 

void Str_Data(USART_TypeDef* USARTx,char *StrData)
{
	while(*StrData!='\0')
	{
		USART_SendData(USARTx,(uint16_t)*StrData); 
		StrData++;
	}
}

void Num_Data(USART_TypeDef* USARTx,long num) 
{
  long n=0,num1=0,c=0,js=1,js1;
  if(num<0)
  {
    num=-num;
    num1=num;  
		USART_SendData(USARTx,45);  
  }else{
    num1=num;
  }
  
  if(num==0) 
  {     
		USART_SendData(USARTx,48);        
  }
  while(num1!=0) 
  {
    num1 = num1/10;
    n++;
  }
  for(js1=n-1;js1>0;js1--) 
  {
    js=js*10;
  }
	if(USARTx==USART1)
		ZhongDuan_TX_Flag[0]=0;
	if(USARTx==USART2)
		ZhongDuan_TX_Flag[1]=0;
	if(USARTx==USART3)
		ZhongDuan_TX_Flag[2]=0;
  while (n!=0)
  { 
    c =num/js;
  	num=num-c*js;
  	c=c+48;  
		USART_SendData(USARTx,c);  
  	js=js/10;	
  	n--;
  }
}
void TonXunFaSong(USART_TypeDef* USARTx,u8 DianNaoFaSong_HuanCun[],u16 DianNaoFaSong_START_ADDR,u8 DianNaoFaSong_Len)    
{
    u16 CRC_wcrc;
	for(DianNaoFaSong_i=0;DianNaoFaSong_i<DianNaoFaSong_Len;DianNaoFaSong_i++)
	{
		CRC_HuanCun[DianNaoFaSong_i]=DianNaoFaSong_HuanCun[DianNaoFaSong_START_ADDR+DianNaoFaSong_i];
	}
	USART_SendData(USARTx,0xa5);
	for(DianNaoFaSong_i=0;DianNaoFaSong_i<=DianNaoFaSong_Len-1;DianNaoFaSong_i++)
	{
		USART_SendData(USARTx,CRC_HuanCun[DianNaoFaSong_i]);
	}
    CRC_wcrc = crc16(CRC_HuanCun,DianNaoFaSong_Len);
	USART_SendData(USARTx,CRC_wcrc >> 8);
	USART_SendData(USARTx,CRC_wcrc & 0x00FF);
}
void ZhuJi_ShuJuChuLi(u8 ZhuJi_Data)
{
	for(ZhuJi_ShuJuChuLi_i=0;ZhuJi_ShuJuChuLi_i<5;ZhuJi_ShuJuChuLi_i++)//轮寻5个缓存数组
	{
		if(DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi_i]>0)//如果数组中没有被填入则填入数据
		{
			if(DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi_i]>2)
				DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi_i][DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi_i]-3]=ZhuJi_Data;
			DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi_i]++;
		}
	}
}
void ZhuJi_ShuJuChuLi2(void)
{
    u16 CRC_wcrc;
	for(ZhuJi_ShuJuChuLi2_i=0;ZhuJi_ShuJuChuLi2_i<5;ZhuJi_ShuJuChuLi2_i++)//轮询5个缓存通道
	{
		if(ZhiLin_ChangDu[DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][0]-1]>4)//收到的数据长度达到指令长度
		{
			if(DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi2_i]>ZhiLin_ChangDu[DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][0]-1])
			{
				CRC_wcrc = crc16(DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i],ZhiLin_ChangDu[DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][0]-1]-4);
				if(DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][ZhiLin_ChangDu[DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][0]-1]-4]== (CRC_wcrc >> 8))
				{
					if(DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][ZhiLin_ChangDu[DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][0]-1]-3]== (CRC_wcrc & 0x00FF))
					{
						for(ZhuJi_ShuJuChuLi2_j=0;ZhuJi_ShuJuChuLi2_j<2060;ZhuJi_ShuJuChuLi2_j++)
						{
							GongNeng_HuanCun[ZhuJi_ShuJuChuLi2_j]=DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][ZhuJi_ShuJuChuLi2_j];  
						}
					}
				}
				DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi2_i]=0;
				for(ZhuJi_ShuJuChuLi2_j=0;ZhuJi_ShuJuChuLi2_j<2060;ZhuJi_ShuJuChuLi2_j++)
				{
					DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][ZhuJi_ShuJuChuLi2_j]=0;
				}
			}
		}else{
			DianNaoJieShou_HuanCun_i[ZhuJi_ShuJuChuLi2_i]=0;
			for(ZhuJi_ShuJuChuLi2_j=0;ZhuJi_ShuJuChuLi2_j<2060;ZhuJi_ShuJuChuLi2_j++)
			{
				DianNaoJieShou_HuanCun[ZhuJi_ShuJuChuLi2_i][ZhuJi_ShuJuChuLi2_j]=0;
			}
		}
	}
}

void ZhuJi2_ShuJuChuLi(u8 ZhuJi2_Data)
{
	for(ZhuJi2_ShuJuChuLi_i=0;ZhuJi2_ShuJuChuLi_i<5;ZhuJi2_ShuJuChuLi_i++)
	{
		if(DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi_i]>0)
		{
			if(DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi_i]>2)
			{
				DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi_i][DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi_i]-3]=ZhuJi2_Data;
			}
			DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi_i]++;
		}
	}
}

void ZhuJi2_ShuJuChuLi2(void)
{
    u16 CRC_wcrc;
	for(ZhuJi2_ShuJuChuLi2_i=0;ZhuJi2_ShuJuChuLi2_i<5;ZhuJi2_ShuJuChuLi2_i++)
	{  
		if(ZhiLin2_ChangDu[DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][0]-1]>4)
		{
			if(DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi2_i]>ZhiLin2_ChangDu[DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][0]-1])
			{
				CRC_wcrc = crc16(DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i],ZhiLin2_ChangDu[DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][0]-1]-3);
				if(DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][ZhiLin2_ChangDu[DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][0]-1]-3]== (CRC_wcrc >> 8))
				{
					if(DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][ZhiLin2_ChangDu[DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][0]-1]-2]== (CRC_wcrc & 0x00FF))
					{
						for(ZhuJi2_ShuJuChuLi2_j=0;ZhuJi2_ShuJuChuLi2_j<150;ZhuJi2_ShuJuChuLi2_j++)
						{
							GongNeng2_HuanCun[ZhuJi2_ShuJuChuLi2_j]=DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][ZhuJi2_ShuJuChuLi2_j];  
						}
					}
				}
				DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi2_i]=0;
				for(ZhuJi2_ShuJuChuLi2_j=0;ZhuJi2_ShuJuChuLi2_j<150;ZhuJi2_ShuJuChuLi2_j++)
				{
					DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][ZhuJi2_ShuJuChuLi2_j]=0;
				}
			}
		}else{
			DianNaoJieShou2_HuanCun_i[ZhuJi2_ShuJuChuLi2_i]=0;
			for(ZhuJi2_ShuJuChuLi2_j=0;ZhuJi2_ShuJuChuLi2_j<150;ZhuJi2_ShuJuChuLi2_j++)
			{
				DianNaoJieShou2_HuanCun[ZhuJi2_ShuJuChuLi2_i][ZhuJi2_ShuJuChuLi2_j]=0;
			}
		}
	}
}




