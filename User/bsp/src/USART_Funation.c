#include "bsp.h"


u8  RxData1, RxData2;                                       //缓存一字节串口数据
u8  PC_RxHuanCun[5][2060], Slave_RxHuanCun[5][150];         //电脑和从机的数据缓存   
u16 PC_RxHuanCun_i[5], Slave_RxHuanCun_i[5];                //电脑和从机的数据缓存指针
u8  CRC_HuanCun[2060];                                      //CRC校验数据缓存
u16 PC_ProcessRecvData_i = 0, PC_ProcessRecvData_j = 0;     
u16 Slave_ProcessRecvData_i = 0,Slave_ProcessRecvData_j = 0;
u8  ZhongDuan_TX_Flag[4];
extern u16 AnWeiSouXun_Flag;
extern u16 AnWeiSouXun_Time;
extern u8 FenJi_XuLieHao_H1[5];
extern u8 GongNeng_HuanCun[2060], GongNeng2_HuanCun[150];
extern u16 ZhiLin_ChangDu[256], ZhiLin2_ChangDu[256];


/*********************** 初始化串口 *************************/
#if 1
void USART_InIt_PeiZhi(void)
{		
	u8 USART_InIt_i,USART_InIt_j;
    USART_InitTypeDef USART_InitStructure;
    
	for(USART_InIt_i=0;USART_InIt_i<5;USART_InIt_i++)
	{
		for(USART_InIt_j=0;USART_InIt_j<20;USART_InIt_j++)
		{
			PC_RxHuanCun[USART_InIt_i][USART_InIt_j]=0;
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
#endif



/************************ 串口1中断 *************************/
#if 1
void USART1_IRQHandler(void)    //host connect to PC
{
    u8 RX1_i;
    //判断现在的中断类型
    if(USART_GetITStatus(USART1,USART_IT_RXNE)== SET)
    {
			if(RxData1==0xa5)
			{
				if(USART_ReceiveData(USART1)==0x01)
				{
					for(RX1_i=0;RX1_i<5;RX1_i++)
					{
						if(PC_RxHuanCun_i[RX1_i]==0)
						{
							PC_RxHuanCun_i[RX1_i]=2;
							break;
						}
					}
				}
			}
      RxData1=USART_ReceiveData(USART1);												//读接收寄存器，系统自动清除接收中断标志位
			PC_RecvData(RxData1);
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);             //清除中断标志位
    }
    if(USART_GetITStatus(USART1,USART_IT_TC)== SET)
    {
      ZhongDuan_TX_Flag[0]=1;
			USART_ClearITPendingBit(USART1, USART_IT_TC);              	//清除中断标志位
    }
}
#endif
/********************* 串口1接收PC数据 **********************/
#if 1
void PC_RecvData(u8 ZhuJi_Data)
{
    u16 PC_RecvData_i;
	for(PC_RecvData_i=0;PC_RecvData_i<5;PC_RecvData_i++)//轮寻5个缓存数组
	{
		if(PC_RxHuanCun_i[PC_RecvData_i]>0)//如果数组中没有被填入则填入数据
		{
			if(PC_RxHuanCun_i[PC_RecvData_i]>2)
				PC_RxHuanCun[PC_RecvData_i][PC_RxHuanCun_i[PC_RecvData_i]-3]=ZhuJi_Data;
			PC_RxHuanCun_i[PC_RecvData_i]++;
		}
	}
}
#endif
/********************* 串口1处理PC数据 **********************/
#if 1
void PC_ProcessRecvData(void)
{
    u16 CRC_wcrc;
	for(PC_ProcessRecvData_i=0;PC_ProcessRecvData_i<5;PC_ProcessRecvData_i++)//轮询5个缓存通道
	{
		if(ZhiLin_ChangDu[PC_RxHuanCun[PC_ProcessRecvData_i][0]-1]>4)//收到的数据长度达到指令长度
		{
			if(PC_RxHuanCun_i[PC_ProcessRecvData_i]>ZhiLin_ChangDu[PC_RxHuanCun[PC_ProcessRecvData_i][0]-1])
			{
				CRC_wcrc = crc16(PC_RxHuanCun[PC_ProcessRecvData_i],ZhiLin_ChangDu[PC_RxHuanCun[PC_ProcessRecvData_i][0]-1]-4);
				if(PC_RxHuanCun[PC_ProcessRecvData_i][ZhiLin_ChangDu[PC_RxHuanCun[PC_ProcessRecvData_i][0]-1]-4]== (CRC_wcrc >> 8))
				{
					if(PC_RxHuanCun[PC_ProcessRecvData_i][ZhiLin_ChangDu[PC_RxHuanCun[PC_ProcessRecvData_i][0]-1]-3]== (CRC_wcrc & 0x00FF))
					{
						for(PC_ProcessRecvData_j=0;PC_ProcessRecvData_j<2060;PC_ProcessRecvData_j++)
						{
							GongNeng_HuanCun[PC_ProcessRecvData_j]=PC_RxHuanCun[PC_ProcessRecvData_i][PC_ProcessRecvData_j];  
						}
					}
				}
				PC_RxHuanCun_i[PC_ProcessRecvData_i]=0;
				for(PC_ProcessRecvData_j=0;PC_ProcessRecvData_j<2060;PC_ProcessRecvData_j++)
				{
					PC_RxHuanCun[PC_ProcessRecvData_i][PC_ProcessRecvData_j]=0;
				}
			}
		}else{
			PC_RxHuanCun_i[PC_ProcessRecvData_i]=0;
			for(PC_ProcessRecvData_j=0;PC_ProcessRecvData_j<2060;PC_ProcessRecvData_j++)
			{
				PC_RxHuanCun[PC_ProcessRecvData_i][PC_ProcessRecvData_j]=0;
			}
		}
	}
}
#endif

/************************ 串口2中断 *************************/
#if 1
void USART2_IRQHandler(void)    //host connect to slave
{
    u8 RX_i;
    //判断现在的中断类型
    if(USART_GetITStatus(USART2,USART_IT_RXNE)== SET)
    {
        /*  */
        if(AnWeiSouXun_Flag>0)//大于0时等待10ms未收到数据后启动下一次发送，如果收到返回数据则重新计时
        {
            AnWeiSouXun_Time=1;//收到返回数据则重新计时
            if(AnWeiSouXun_Flag>10000)//大于10000为等待分机返回模式，这里也表示还未收到过返回数据
            {
                AnWeiSouXun_Flag-=10000;//收到返回数据标志
            }
        }
        if(RxData2==0xa5)
        {
            for(RX_i=0;RX_i<5;RX_i++)
            {
                if(Slave_RxHuanCun_i[RX_i]==0)
                {
                    Slave_RxHuanCun_i[RX_i]=3;
                    break;
                }
            }
        }
        RxData2=USART_ReceiveData(USART2);												//读接收寄存器
        Slave_RecvData(RxData2); 
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);             //清除中断标志位
    }
    if(USART_GetITStatus(USART2,USART_IT_TC)== SET)
    {
      ZhongDuan_TX_Flag[1]=1;
			USART_ClearITPendingBit(USART2, USART_IT_TC);              	//清除中断标志位
    }
} 
#endif
/******************** 串口2接收从机数据 *********************/
#if 1
void Slave_RecvData(u8 ZhuJi2_Data)  //ZhuJi2_Data   --->    Slave_RxHuanCun
{
    u16 Slave_RecvData_i;
	for(Slave_RecvData_i=0;Slave_RecvData_i<5;Slave_RecvData_i++)
	{
		if(Slave_RxHuanCun_i[Slave_RecvData_i]>0)
		{
			if(Slave_RxHuanCun_i[Slave_RecvData_i]>2)
			{
				Slave_RxHuanCun[Slave_RecvData_i][Slave_RxHuanCun_i[Slave_RecvData_i]-3]=ZhuJi2_Data;
			}
			Slave_RxHuanCun_i[Slave_RecvData_i]++;
		}
	}
}
#endif
/******************** 串口2处理从机数据 *********************/
#if 1
void Slave_ProcessRecvData(void)  //Slave_RxHuanCun    --->    GongNeng2_HuanCun
{
    u16 CRC_wcrc;
	for(Slave_ProcessRecvData_i=0;Slave_ProcessRecvData_i<5;Slave_ProcessRecvData_i++)
	{  
		if(ZhiLin2_ChangDu[Slave_RxHuanCun[Slave_ProcessRecvData_i][0]-1]>4)
		{
			if(Slave_RxHuanCun_i[Slave_ProcessRecvData_i]>ZhiLin2_ChangDu[Slave_RxHuanCun[Slave_ProcessRecvData_i][0]-1])
			{
				CRC_wcrc = crc16(Slave_RxHuanCun[Slave_ProcessRecvData_i],ZhiLin2_ChangDu[Slave_RxHuanCun[Slave_ProcessRecvData_i][0]-1]-3);
				if(Slave_RxHuanCun[Slave_ProcessRecvData_i][ZhiLin2_ChangDu[Slave_RxHuanCun[Slave_ProcessRecvData_i][0]-1]-3]== (CRC_wcrc >> 8))
				{
					if(Slave_RxHuanCun[Slave_ProcessRecvData_i][ZhiLin2_ChangDu[Slave_RxHuanCun[Slave_ProcessRecvData_i][0]-1]-2]== (CRC_wcrc & 0x00FF))
					{
						for(Slave_ProcessRecvData_j=0;Slave_ProcessRecvData_j<150;Slave_ProcessRecvData_j++)
						{
							GongNeng2_HuanCun[Slave_ProcessRecvData_j]=Slave_RxHuanCun[Slave_ProcessRecvData_i][Slave_ProcessRecvData_j];  
						}
					}
				}
				Slave_RxHuanCun_i[Slave_ProcessRecvData_i]=0;
				for(Slave_ProcessRecvData_j=0;Slave_ProcessRecvData_j<150;Slave_ProcessRecvData_j++)
				{
					Slave_RxHuanCun[Slave_ProcessRecvData_i][Slave_ProcessRecvData_j]=0;
				}
			}
		}else{
			Slave_RxHuanCun_i[Slave_ProcessRecvData_i]=0;
			for(Slave_ProcessRecvData_j=0;Slave_ProcessRecvData_j<150;Slave_ProcessRecvData_j++)
			{
				Slave_RxHuanCun[Slave_ProcessRecvData_i][Slave_ProcessRecvData_j]=0;
			}
		}
	}
}
#endif
/************************ 发送字符串 ************************/
#if 1
void Str_Data(USART_TypeDef* USARTx,char *StrData)
{
	while(*StrData!='\0')
	{
		USART_SendData(USARTx,(uint16_t)*StrData); 
		StrData++;
	}
}
#endif
/********************* 发送带符号的数字 *********************/
#if 1
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
#endif
/*********************** 发送通信数据 ***********************/
#if 1
void TonXunFaSong(USART_TypeDef* USARTx,u8 DianNaoFaSong_HuanCun[],u16 DianNaoFaSong_START_ADDR,u8 DianNaoFaSong_Len)    
{
    u16 CRC_wcrc;
    u16 DianNaoFaSong_i;
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
#endif










