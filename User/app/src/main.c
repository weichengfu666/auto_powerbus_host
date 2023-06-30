#include "bsp.h"

extern uchar Time_500Ms_Flag,RxData1,RxData2,ZhongDuan_TX_Flag[4];

void bsp_init(void)
{
    GPIO_Init_PeiZhi();
	Tim_Init_PeiZhi();
	NVIC_Init_PeiZhi();
	USART_InIt_PeiZhi();
	Host_Init(); 
    readSlaveArr();
}

int main(void)
{
    bsp_init();
	USART_SendData( USART_PC, 0x52 );
	USART_SendData( USART_PC, 0x61 );
	USART_SendData( USART_SLAVE, 0x52);
	USART_SendData( USART_SLAVE, 0x61);
    
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



