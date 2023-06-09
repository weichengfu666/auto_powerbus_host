#include "bsp.h"
#include "NVIC.h"

/********************** 初始化NVIC ***********************/
#if 1
void NVIC_Init_PeiZhi(void)
{	
	NVIC_InitTypeDef nvic;										//定义中断结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  			//优先级设置
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;							//中断通道名
	nvic.NVIC_IRQChannelPreemptionPriority = 2;				    //抢占优先级2
	nvic.NVIC_IRQChannelSubPriority = 2;						//子优先级2
	nvic.NVIC_IRQChannelCmd= ENABLE;							//IRQ通道是使能
	NVIC_Init(&nvic);											//根据配置参数定义VIC寄存器
	/*配置USART1中断优先级*/	
    nvic.NVIC_IRQChannel = USART1_IRQn;							//中断通道名
    nvic.NVIC_IRQChannelPreemptionPriority = 2;                 //抢占优先级2
    nvic.NVIC_IRQChannelSubPriority = 2;                        //子优先级2
    nvic.NVIC_IRQChannelCmd = ENABLE;                           //IRQ通道是使能
    NVIC_Init(&nvic);                                           //根据配置参数定义VIC寄存器
    /*配置USART2中断优先级*/
    nvic.NVIC_IRQChannel = USART2_IRQn;                         //中断通道名
    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//抢占优先级2
    nvic.NVIC_IRQChannelSubPriority = 2;						//子优先级2
    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道是使能
    NVIC_Init(&nvic);											//根据配置参数定义VIC寄存器
//    /*配置USART3中断优先级*/
//    nvic.NVIC_IRQChannel = USART3_IRQn;                         //中断通道名
//    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//抢占优先级2
//    nvic.NVIC_IRQChannelSubPriority = 2;						//子优先级2
//    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道是使能
//    NVIC_Init(&nvic);											//根据配置参数定义VIC寄存器
//    /*配置USART4中断优先级*/
//    nvic.NVIC_IRQChannel = UART4_IRQn;                         //中断通道名
//    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//抢占优先级2
//    nvic.NVIC_IRQChannelSubPriority = 2;						//子优先级2
//    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道是使能
//    NVIC_Init(&nvic);											//根据配置参数定义VIC寄存器
//    /*配置USART5中断优先级*/
//    nvic.NVIC_IRQChannel = UART5_IRQn;                         //中断通道名
//    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//抢占优先级2
//    nvic.NVIC_IRQChannelSubPriority = 2;						//子优先级2
//    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQ通道是使能
//    NVIC_Init(&nvic);											//根据配置参数定义VIC寄存器
	
	nvic.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 2;
	nvic.NVIC_IRQChannelSubPriority = 2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);	
}
#endif
