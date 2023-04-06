#include "bsp.h"


u8  RxData1, RxData2;                                       //����һ�ֽڴ�������
u8  PC_RxHuanCun[5][2060], Slave_RxHuanCun[5][150];         //���Ժʹӻ������ݻ���   
u16 PC_RxHuanCun_i[5], Slave_RxHuanCun_i[5];                //���Ժʹӻ������ݻ���ָ��
u8  CRC_HuanCun[2060];                                      //CRCУ�����ݻ���
u16 PC_ProcessRecvData_i = 0, PC_ProcessRecvData_j = 0;     
u16 Slave_ProcessRecvData_i = 0,Slave_ProcessRecvData_j = 0;
u8  ZhongDuan_TX_Flag[4];
extern u16 AnWeiSouXun_Flag;
extern u16 AnWeiSouXun_Time;
extern u8 FenJi_XuLieHao_H1[5];
extern u8 GongNeng_HuanCun[2060], GongNeng2_HuanCun[150];
extern u16 ZhiLin_ChangDu[256], ZhiLin2_ChangDu[256];


/*********************** ��ʼ������ *************************/
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1 ,ENABLE);	//ʹ��usart1ʱ��			
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);																					//ʹ��usart2ʱ��	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2); 
	
	//	/*����USART1ģʽ*/
	USART_InitStructure.USART_BaudRate = 9600;                               	//����������Ϊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;               //���ô��ڴ����ֽڳ���Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                    //����ֹͣλΪ1
	USART_InitStructure.USART_Parity = USART_Parity_No;                       //��������żУ��λ	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //������Ӳ����
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���ô���Ϊȫ˫��ͨѶ
	USART_Init(USART1, &USART_InitStructure);																	//��Ĵ���д�����ò���
	USART_ITConfig(USART1, USART_IT_RXNE ,ENABLE);														//��USART1�Ĵ��ڽ����ж�
	USART_ITConfig(USART1, USART_IT_TC ,ENABLE);															//��USART1�Ĵ��ڷ����ж�
	USART_Cmd(USART1, ENABLE);																								//ʹ��USART1����
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);                           //����жϱ�־λ
	USART_ClearITPendingBit(USART1, USART_IT_TC);                           	//����жϱ�־λ
	
	USART_InitStructure.USART_BaudRate = 9600;                               	//����������Ϊ9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;               //���ô��ڴ����ֽڳ���Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                    //����ֹͣλΪ1
	USART_InitStructure.USART_Parity = USART_Parity_No;                       //��������żУ��λ	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //������Ӳ����
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���ô���Ϊȫ˫��ͨѶ
	USART_Init(USART2, &USART_InitStructure);																	//��Ĵ���д�����ò���
	USART_ITConfig(USART2, USART_IT_RXNE ,ENABLE);														//��USART2�Ĵ��ڽ����ж�
	USART_ITConfig(USART2, USART_IT_TC ,ENABLE);															//��USART2�Ĵ��ڷ����ж�
	USART_Cmd(USART2, ENABLE);																								//ʹ��USART2����
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);                           //����жϱ�־λ
	USART_ClearITPendingBit(USART2, USART_IT_TC);                           	//����жϱ�־λ
}
#endif



/************************ ����1�ж� *************************/
#if 1
void USART1_IRQHandler(void)    //host connect to PC
{
    u8 RX1_i;
    //�ж����ڵ��ж�����
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
      RxData1=USART_ReceiveData(USART1);												//�����ռĴ�����ϵͳ�Զ���������жϱ�־λ
			PC_RecvData(RxData1);
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);             //����жϱ�־λ
    }
    if(USART_GetITStatus(USART1,USART_IT_TC)== SET)
    {
      ZhongDuan_TX_Flag[0]=1;
			USART_ClearITPendingBit(USART1, USART_IT_TC);              	//����жϱ�־λ
    }
}
#endif
/********************* ����1����PC���� **********************/
#if 1
void PC_RecvData(u8 ZhuJi_Data)
{
    u16 PC_RecvData_i;
	for(PC_RecvData_i=0;PC_RecvData_i<5;PC_RecvData_i++)//��Ѱ5����������
	{
		if(PC_RxHuanCun_i[PC_RecvData_i]>0)//���������û�б���������������
		{
			if(PC_RxHuanCun_i[PC_RecvData_i]>2)
				PC_RxHuanCun[PC_RecvData_i][PC_RxHuanCun_i[PC_RecvData_i]-3]=ZhuJi_Data;
			PC_RxHuanCun_i[PC_RecvData_i]++;
		}
	}
}
#endif
/********************* ����1����PC���� **********************/
#if 1
void PC_ProcessRecvData(void)
{
    u16 CRC_wcrc;
	for(PC_ProcessRecvData_i=0;PC_ProcessRecvData_i<5;PC_ProcessRecvData_i++)//��ѯ5������ͨ��
	{
		if(ZhiLin_ChangDu[PC_RxHuanCun[PC_ProcessRecvData_i][0]-1]>4)//�յ������ݳ��ȴﵽָ���
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

/************************ ����2�ж� *************************/
#if 1
void USART2_IRQHandler(void)    //host connect to slave
{
    u8 RX_i;
    //�ж����ڵ��ж�����
    if(USART_GetITStatus(USART2,USART_IT_RXNE)== SET)
    {
        /*  */
        if(AnWeiSouXun_Flag>0)//����0ʱ�ȴ�10msδ�յ����ݺ�������һ�η��ͣ�����յ��������������¼�ʱ
        {
            AnWeiSouXun_Time=1;//�յ��������������¼�ʱ
            if(AnWeiSouXun_Flag>10000)//����10000Ϊ�ȴ��ֻ�����ģʽ������Ҳ��ʾ��δ�յ�����������
            {
                AnWeiSouXun_Flag-=10000;//�յ��������ݱ�־
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
        RxData2=USART_ReceiveData(USART2);												//�����ռĴ���
        Slave_RecvData(RxData2); 
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);             //����жϱ�־λ
    }
    if(USART_GetITStatus(USART2,USART_IT_TC)== SET)
    {
      ZhongDuan_TX_Flag[1]=1;
			USART_ClearITPendingBit(USART2, USART_IT_TC);              	//����жϱ�־λ
    }
} 
#endif
/******************** ����2���մӻ����� *********************/
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
/******************** ����2����ӻ����� *********************/
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
/************************ �����ַ��� ************************/
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
/********************* ���ʹ����ŵ����� *********************/
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
/*********************** ����ͨ������ ***********************/
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










