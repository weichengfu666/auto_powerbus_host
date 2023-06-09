#include "bsp.h"
#include "TIM.h"

ulong Time3=0;  
uchar Time_500Ms_Flag=0;
extern u16 AnWeiSouXun_Time;


/********************** 初始化Timer ***********************/
#if 1
void Tim_Init_PeiZhi(void)
{	
	TIM_TimeBaseInitTypeDef tim;									//定义时钟结构体
																											
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	            //使能TIM3
	tim.TIM_Period = 1000-1;										//计数周期
	tim.TIM_Prescaler = 72 - 1;										//预分频数
	tim.TIM_ClockDivision = TIM_CKD_DIV1;							//时钟分频，设置定时器时钟CK_INT频率与数字滤波器采样时钟频率分频比，基本定时器没有此功能
	tim.TIM_CounterMode = TIM_CounterMode_Up;						//定时器基础方式，可以是向上计数，向下计数，中心对齐模式。基本定时器只能是向上计数。
	tim.TIM_RepetitionCounter = 0;								    //重复计数器，属于高级控制寄存器专用寄存器位，这里不用设置。
																	
	TIM_TimeBaseInit(TIM3,&tim);									//初始化
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);							//清除中断标志
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);						//开启中断
	TIM_Cmd(TIM3,ENABLE);											//TIM3时钟使能
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,DISABLE);          //关闭TIM3时钟，等需要时打开
}
#endif
/********************** 定时器3中断 ***********************/
#if 1
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET)
	{
		Time3++;
		if(AnWeiSouXun_Time>0)
			AnWeiSouXun_Time++;
        if(CheckSlaveState_Time>0)
            CheckSlaveState_Time++;
        if(CheckSlaveOnline_Time>0)
            CheckSlaveOnline_Time++;
        if(CheckSlaveOnline_PeriodTime>0)
            CheckSlaveOnline_PeriodTime++;
		if(Time3%500==0)
		{
			Time_500Ms_Flag=1;
		}
		if(Time3>360000000)
		{
			Time3=0;
		}
		if(CheckSlaveOnline_PeriodTime>10000)  //大概每10秒刷新一次：因为开始刷新时，要关闭定时器，要等刷新完后，再开启定时10秒。
		{
			CheckSlaveOnline_PeriodTime=0;//关闭检测从机在线状态的定时器
            CheckSlaveOnline_PeriodFlag = 1;//开始检测从机在线状态
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);			        //清除中断标志位
}
#endif


