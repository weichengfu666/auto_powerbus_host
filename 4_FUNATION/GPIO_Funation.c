#include "stm32f10x.h"
#include <stdio.h>

GPIO_InitTypeDef GPIO_InitStructure;
uchar GPIO_i=0;
void GPIO_Init_PeiZhi(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD , ENABLE);
	GPIO_PinRemapConfig(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //2MHz
	for(GPIO_i=0;GPIO_i<8;GPIO_i++)
	{
		GPIO_InitStructure.GPIO_Pin=0x00;	
		switch(GPIO_i)
		{
			case 0:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;break; 													
			case 1:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;break; 												
			case 2:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;break; 												
			case 3:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;break; 													
			case 4:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;break; 														
			case 5:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;break; 													
			case 6:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;break; 														
			case 7:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;break; 															
		}
		if(PA0_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_0;
		if(PA1_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_1;
		if(PA2_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_2;
		if(PA3_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_3;
		if(PA4_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_4;
		if(PA5_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_5;
		if(PA6_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_6;
		if(PA7_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_7;
		if(PA8_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_8;
		if(PA9_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_9;
		if(PA10_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_10;
		if(PA11_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_11;
		if(PA12_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_12;
		if(PA13_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_13;
		if(PA14_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_14;
		if(PA15_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_15;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin=0x00;	
		if(PB0_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_0;
		if(PB1_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_1;
		if(PB2_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_2;
		if(PB3_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_3;
		if(PB4_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_4;
		if(PB5_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_5;
		if(PB6_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_6;
		if(PB7_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_7;
		if(PB8_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_8;
		if(PB9_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_9;
		if(PB10_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_10;
		if(PB11_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_11;
		if(PB12_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_12;
		if(PB13_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_13;
		if(PB14_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_14;
		if(PB15_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_15;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin=0x00;	
		if(PC0_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_0;
		if(PC1_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_1;
		if(PC2_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_2;
		if(PC3_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_3;
		if(PC4_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_4;
		if(PC5_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_5;
		if(PC6_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_6;
		if(PC7_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_7;
		if(PC8_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_8;
		if(PC9_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_9;
		if(PC10_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_10;
		if(PC11_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_11;
		if(PC12_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_12;
		if(PC13_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_13;
		if(PC14_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_14;
		if(PC15_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_15;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin=0x00;	
		if(PD0_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_0;
		if(PD1_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_1;
		if(PD2_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_2;
		if(PD3_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_3;
		if(PD4_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_4;
		if(PD5_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_5;
		if(PD6_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_6;
		if(PD7_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_7;
		if(PD8_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_8;
		if(PD9_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_9;
		if(PD10_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_10;
		if(PD11_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_11;
		if(PD12_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_12;
		if(PD13_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_13;
		if(PD14_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_14;
		if(PD15_MoShi==GPIO_i)
			GPIO_InitStructure.GPIO_Pin = GPIO_InitStructure.GPIO_Pin | GPIO_Pin_15;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		
		Write_ShuChu1_ReSet;
	}
} 
