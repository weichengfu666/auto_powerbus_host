#include "bsp.h"
#include "NVIC.h"

/********************** ��ʼ��NVIC ***********************/
#if 1
void NVIC_Init_PeiZhi(void)
{	
	NVIC_InitTypeDef nvic;										//�����жϽṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  			//���ȼ�����
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;							//�ж�ͨ����
	nvic.NVIC_IRQChannelPreemptionPriority = 2;				    //��ռ���ȼ�2
	nvic.NVIC_IRQChannelSubPriority = 2;						//�����ȼ�2
	nvic.NVIC_IRQChannelCmd= ENABLE;							//IRQͨ����ʹ��
	NVIC_Init(&nvic);											//�������ò�������VIC�Ĵ���
	/*����USART1�ж����ȼ�*/	
    nvic.NVIC_IRQChannel = USART1_IRQn;							//�ж�ͨ����
    nvic.NVIC_IRQChannelPreemptionPriority = 2;                 //��ռ���ȼ�2
    nvic.NVIC_IRQChannelSubPriority = 2;                        //�����ȼ�2
    nvic.NVIC_IRQChannelCmd = ENABLE;                           //IRQͨ����ʹ��
    NVIC_Init(&nvic);                                           //�������ò�������VIC�Ĵ���
    /*����USART2�ж����ȼ�*/
    nvic.NVIC_IRQChannel = USART2_IRQn;                         //�ж�ͨ����
    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//��ռ���ȼ�2
    nvic.NVIC_IRQChannelSubPriority = 2;						//�����ȼ�2
    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
    NVIC_Init(&nvic);											//�������ò�������VIC�Ĵ���
//    /*����USART3�ж����ȼ�*/
//    nvic.NVIC_IRQChannel = USART3_IRQn;                         //�ж�ͨ����
//    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//��ռ���ȼ�2
//    nvic.NVIC_IRQChannelSubPriority = 2;						//�����ȼ�2
//    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
//    NVIC_Init(&nvic);											//�������ò�������VIC�Ĵ���
//    /*����USART4�ж����ȼ�*/
//    nvic.NVIC_IRQChannel = UART4_IRQn;                         //�ж�ͨ����
//    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//��ռ���ȼ�2
//    nvic.NVIC_IRQChannelSubPriority = 2;						//�����ȼ�2
//    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
//    NVIC_Init(&nvic);											//�������ò�������VIC�Ĵ���
//    /*����USART5�ж����ȼ�*/
//    nvic.NVIC_IRQChannel = UART5_IRQn;                         //�ж�ͨ����
//    nvic.NVIC_IRQChannelPreemptionPriority = 2;					//��ռ���ȼ�2
//    nvic.NVIC_IRQChannelSubPriority = 2;						//�����ȼ�2
//    nvic.NVIC_IRQChannelCmd = ENABLE;							//IRQͨ����ʹ��
//    NVIC_Init(&nvic);											//�������ò�������VIC�Ĵ���
	
	nvic.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 2;
	nvic.NVIC_IRQChannelSubPriority = 2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);	
}
#endif
