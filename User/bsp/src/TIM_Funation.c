#include "bsp.h"
#include "TIM_Funation.h"

ulong Time3=0;  
uchar Time_500Ms_Flag=0;
extern u16 AnWeiSouXun_Time;


/********************** ��ʼ��Timer ***********************/
#if 1
void Tim_Init_PeiZhi(void)
{	
	TIM_TimeBaseInitTypeDef tim;									//����ʱ�ӽṹ��
																											
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	            //ʹ��TIM3
	tim.TIM_Period = 1000-1;										//��������
	tim.TIM_Prescaler = 72 - 1;										//Ԥ��Ƶ��
	tim.TIM_ClockDivision = TIM_CKD_DIV1;							//ʱ�ӷ�Ƶ�����ö�ʱ��ʱ��CK_INTƵ���������˲�������ʱ��Ƶ�ʷ�Ƶ�ȣ�������ʱ��û�д˹���
	tim.TIM_CounterMode = TIM_CounterMode_Up;						//��ʱ��������ʽ�����������ϼ��������¼��������Ķ���ģʽ��������ʱ��ֻ�������ϼ�����
	tim.TIM_RepetitionCounter = 0;								    //�ظ������������ڸ߼����ƼĴ���ר�üĴ���λ�����ﲻ�����á�
																	
	TIM_TimeBaseInit(TIM3,&tim);									//��ʼ��
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);							//����жϱ�־
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);						//�����ж�
	TIM_Cmd(TIM3,ENABLE);											//TIM3ʱ��ʹ��
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,DISABLE);          //�ر�TIM3ʱ�ӣ�����Ҫʱ��
}
#endif
/********************** ��ʱ��3�ж� ***********************/
#if 1
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET)
	{
		Time3++;
		if(AnWeiSouXun_Time>0)
			AnWeiSouXun_Time++;
		if(Time3%500==0)
		{
			Time_500Ms_Flag=1;
		}
		if(Time3>360000000)
		{
			Time3=0;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);			        //����жϱ�־λ
}
#endif


