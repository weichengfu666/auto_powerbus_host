#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
extern u8 Rx_flag,ShuChuZhuangTai_H,ShuChuZhuangTai_L;
extern uchar RxBuffer1,RxBuffer2,Time_500Ms_Flag;
CAN_InitTypeDef        	CAN_InitStructure;
CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
NVIC_InitTypeDef 				NVIC_InitStructure;
u8 TransmitMailbox=0,Rx_flag=0;
u32 CAN_ID=0,CAN_MoKuaiHao=0;
CanTxMsg   TxMessage;
CanRxMsg   RxMessage;
uchar CAN_RXD_HuanCun[10][9]={{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0},
															{0,0,0,0,0,0,0,0,0}};
void Can_Init_PeiZhi(void)
{    
	CAN_MoKuaiHao=1;
	CAN_ID=1;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
/* enabling interrupt */
	
	CAN_DeInit(CAN1); 																							//将外设CAN的全部寄存器重设为省缺值
	CAN_StructInit(&CAN_InitStructure);															//把CAN_InitStructure的值写入
	
	CAN_InitStructure.CAN_TTCM=DISABLE;															//没有使能事件触发模式
	CAN_InitStructure.CAN_ABOM=ENABLE;															//没有使能自动离线管理
	CAN_InitStructure.CAN_AWUM=DISABLE;															//没有使能自动唤醒模式
	CAN_InitStructure.CAN_NART=DISABLE; 														//没有使能非自动重传模式
	CAN_InitStructure.CAN_RFLM=DISABLE;															//没有使能接收FIFO模式
	CAN_InitStructure.CAN_TXFP=DISABLE;															//没有使能发送FIFO优先级
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;											//CAN设置为正常模式
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;													//重新同步跳跃宽度1个时间单位
	CAN_InitStructure.CAN_BS1=CAN_BS1_3tq;      										//时间段1为3个时间单位
	CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;													//时间段2位2个时间单位
	CAN_InitStructure.CAN_Prescaler=60;															//时间单位长度为60
	CAN_Init(CAN1,&CAN_InitStructure);															//波特率为：72/2/60(1+2+3)=0.1既波特率为100KBPS
	
	//CAN过滤器，注意，只接收主机发送过来的数据，屏蔽其他数据
	
//	CAN_FilterInitStructure.CAN_FilterNumber=0;
//	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
//	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
//	CAN_FilterInitStructure.CAN_FilterIdHigh=0x00AA<<3;
//	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x00FF<<3;
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
//	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
//	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
//	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=1;											//指定过滤器为1
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;		//指定过滤器为标识符列表模式 CAN_FilterMode_IdMask CAN_FilterMode_IdList
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	//过滤器位宽为32位
	CAN_FilterInitStructure.CAN_FilterIdHigh=((((u32)CAN_ID)<<3)&0xffff0000)>>16;								//要过滤的ID高位
	CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)CAN_ID)<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xffff;		 							//要过滤ID低位
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;						//过滤器标识符的高16位值（主题号）
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x07ff;							//过滤器标识符的低16位值（机关盒号）
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;			//设定了指向FIFO为0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;						//使能过滤器
	CAN_FilterInit(&CAN_FilterInitStructure);												//按照上面的参数初始化过滤器
	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);													//使能FIFO0消息挂号中断
	
}
u8 CAN_ShuJuFaSong(u8 DATA_1,u8 DATA_2,u8 DATA_3,u8 DATA_4,u8 DATA_5,u8 DATA_6,u8 DATA_7,u8 DATA_8)
{
	u32 Can_i_Wr=0;
	TxMessage.StdId=0x0000;																						//主题号高4位，机关盒号低4位
	TxMessage.ExtId=00000001;																					//主题号高4位，机关盒号低4位
	TxMessage.RTR=CAN_RTR_Data;																				//代表发送数据帧 
	TxMessage.IDE=CAN_ID_EXT;																					//使用标准标识符+扩展标识符					
	TxMessage.DLC=8;																									//发送8位数据
	TxMessage.Data[0]=DATA_1;
	TxMessage.Data[1]=DATA_2;
	TxMessage.Data[2]=DATA_3;
	TxMessage.Data[3]=DATA_4;
	TxMessage.Data[4]=DATA_5;
	TxMessage.Data[5]=DATA_6;
	TxMessage.Data[6]=DATA_7;
	TxMessage.Data[7]=DATA_8;
	TransmitMailbox=CAN_Transmit(CAN1,&TxMessage);
	while((CAN_TransmitStatus(CAN1,TransmitMailbox)!=CAN_TxStatus_Ok)&&(Can_i_Wr<0x200000))
		Can_i_Wr++;
	if(Can_i_Wr>=0x200000)
	{
		Can_i_Wr=0;
		return 0;
	}else{
		Can_i_Wr=0;
		return 1;
	}
}
u8 CAN_SetMsg(u32 MiShiHao,u32 MoKuaiHao,u8 XiaoGuoMoShi,u8 XiaoGuoWei_1,u8 XiaoGuoWei_2)    
{ 
	u32 Can_i_Wr=0;
	TxMessage.StdId=0x0000;																						//主题号高4位，机关盒号低4位
	TxMessage.ExtId=(u32)CAN_ID+((u32)MoKuaiHao<<8);																						//主题号高4位，机关盒号低4位
	TxMessage.RTR=CAN_RTR_Data;																				//代表发送数据帧 
	TxMessage.IDE=CAN_ID_EXT;																					//使用标准标识符+扩展标识符					
	TxMessage.DLC=8;																									//发送8位数据
	TxMessage.Data[0]=XiaoGuoMoShi;
	TxMessage.Data[1]=XiaoGuoWei_1;
	TxMessage.Data[2]=XiaoGuoWei_2;
	if((XiaoGuoMoShi==0x80)||(XiaoGuoMoShi==0x82))
	{
		TxMessage.Data[3]=CAN_MoKuaiHao;
	}else{
		TxMessage.Data[3]=0;
	}
	TxMessage.Data[4]=0;
	TxMessage.Data[5]=0;
	TxMessage.Data[6]=0;
	TxMessage.Data[7]=0;
	TransmitMailbox=CAN_Transmit(CAN1,&TxMessage);
	while((CAN_TransmitStatus(CAN1,TransmitMailbox)!=CAN_TxStatus_Ok)&&(Can_i_Wr<0x200000))
		Can_i_Wr++;
	if(Can_i_Wr>=0x200000)
	{
		Can_i_Wr=0;
		return 0;
	}else{
		Can_i_Wr=0;
		return 1;
	}
}

void CAN_HuiHuanCeShi(void)																								
{																																									
		if(RxBuffer1!=0)															
		{ 																																								
//			CAN_SetMsg(RxBuffer1); 								
			RxBuffer1=0;                                   
//			YingXiao(1,1,1); 																						
//			Str_Data(USART1,"CAN_0:");																								
//			Num_Data(USART1,CAN_RXD_HuanCun[0][0]);														
//			Str_Data(USART1,"\r\n");																																												
		}																																	
}																																			
		 
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	Rx_flag=1;
	RxMessage.StdId=0x00;
	RxMessage.IDE=CAN_ID_EXT;																					//使用标准标识符+扩展标识符		
	RxMessage.DLC=0;
	RxMessage.Data[0]=0x00;
	RxMessage.Data[1]=0x00;
	RxMessage.Data[2]=0x00;
	RxMessage.Data[3]=0x00;
	RxMessage.Data[4]=0x00;
	RxMessage.Data[5]=0x00;
	RxMessage.Data[6]=0x00;
	RxMessage.Data[7]=0x00;
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	CAN_RXD_HuanCun[0][0]=RxMessage.Data[0];
	CAN_RXD_HuanCun[0][1]=RxMessage.Data[1];
	CAN_RXD_HuanCun[0][2]=RxMessage.Data[2];
	CAN_RXD_HuanCun[0][3]=RxMessage.Data[3];
	CAN_RXD_HuanCun[0][4]=RxMessage.Data[4];
	CAN_RXD_HuanCun[0][5]=RxMessage.Data[5];
	CAN_RXD_HuanCun[0][6]=RxMessage.Data[6];
	CAN_RXD_HuanCun[0][7]=RxMessage.Data[7];
	CAN_RXD_HuanCun[0][8]=(u8)(RxMessage.ExtId>>8);
	CAN_FIFORelease(CAN1,CAN_FIFO0);
}
