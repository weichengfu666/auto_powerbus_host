#include "stm32f10x.h"
#include <stdio.h>



void NVIC_Init_PeiZhi(void)
{	
	NVIC_InitTypeDef nvic;																			//�����жϽṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  						//���ȼ�����
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;														//�ж�ͨ����
	nvic.NVIC_IRQChannelPreemptionPriority = 2;									//��ռ���ȼ�1
	nvic.NVIC_IRQChannelSubPriority = 2;												//�����ȼ�0
	nvic.NVIC_IRQChannelCmd= ENABLE;														//IRQͨ����ʹ��
	NVIC_Init(&nvic);																						//�������ò�������VIC�Ĵ���
		
  nvic.NVIC_IRQChannel = USART1_IRQn;													//�ж�ͨ����
  nvic.NVIC_IRQChannelPreemptionPriority = 2;									//��ռ���ȼ�0
  nvic.NVIC_IRQChannelSubPriority = 2;												//�����ȼ�0
  nvic.NVIC_IRQChannelCmd = ENABLE;														//IRQͨ����ʹ��
  NVIC_Init(&nvic);																						//�������ò�������VIC�Ĵ���
		
  nvic.NVIC_IRQChannel = USART2_IRQn;													//�ж�ͨ����
  nvic.NVIC_IRQChannelPreemptionPriority = 2;									//��ռ���ȼ�3
  nvic.NVIC_IRQChannelSubPriority = 2;												//�����ȼ�3
  nvic.NVIC_IRQChannelCmd = ENABLE;														//IRQͨ����ʹ��
  NVIC_Init(&nvic);																						//�������ò�������VIC�Ĵ���
	
	nvic.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 2;
	nvic.NVIC_IRQChannelSubPriority = 2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);	
}
