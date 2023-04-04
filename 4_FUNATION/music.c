#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>

u8 ShangCiBoFang[2]={0,0};
extern u32 GongNengTanShi_Time[60];

void YingXiao(u8 BoFangKou,u8 WenJianJiaHao,u8 GeMinHao)	
{
	if(BoFangKou==1)										 		//播放口1
	{
		if(WenJianJiaHao==100)						  	//停止播放
		{	
			USART_SendData(USART1,0x7e);
			USART_SendData(USART1,0x03);
			USART_SendData(USART1,0x0e);
			USART_SendData(USART1,0x0d);
			USART_SendData(USART1,0xef);
		}else if((WenJianJiaHao>100)&&(WenJianJiaHao<135)){					//音量设置
			USART_SendData(USART1,0x7e);
			USART_SendData(USART1,0x04);
			USART_SendData(USART1,0x31);
			USART_SendData(USART1,WenJianJiaHao-100);
			USART_SendData(USART1,0x35^(WenJianJiaHao-100));
			USART_SendData(USART1,0xef);
		}else if(WenJianJiaHao<100){																//播放歌曲
			USART_SendData(USART1,0x7e);
			USART_SendData(USART1,0x05);
			USART_SendData(USART1,0x42);
			USART_SendData(USART1,WenJianJiaHao);
			USART_SendData(USART1,GeMinHao);
			USART_SendData(USART1,(0x47^WenJianJiaHao)^GeMinHao);
			USART_SendData(USART1,0xef);
		}else if(WenJianJiaHao==140){
			USART_SendData(USART1,0x7e);
			USART_SendData(USART1,0x03);
			USART_SendData(USART1,0x05);
			USART_SendData(USART1,0x06);
			USART_SendData(USART1,0xef);
		}else if(WenJianJiaHao==141){
			USART_SendData(USART1,0x7e);
			USART_SendData(USART1,0x03);
			USART_SendData(USART1,0x06);
			USART_SendData(USART1,0x05);
			USART_SendData(USART1,0xef);
		}
	}else if(BoFangKou==2){	 
		if(WenJianJiaHao==100)
		{
			USART_SendData(USART2,0x7e);
			USART_SendData(USART2,0x03);
			USART_SendData(USART2,0x0e);
			USART_SendData(USART2,0x0d);
			USART_SendData(USART2,0xef);
		}else if((WenJianJiaHao>100)&&(WenJianJiaHao<135)){
			USART_SendData(USART2,0x7e);
			USART_SendData(USART2,0x04);
			USART_SendData(USART2,0x31);
			USART_SendData(USART2,WenJianJiaHao-100);
			USART_SendData(USART2,0x35^(WenJianJiaHao-100));
			USART_SendData(USART2,0xef);
		}else if(WenJianJiaHao<100){
			USART_SendData(USART2,0x7e);
			USART_SendData(USART2,0x05);
			USART_SendData(USART2,0x42);
			USART_SendData(USART2,WenJianJiaHao);
			USART_SendData(USART2,GeMinHao);
			USART_SendData(USART2,(0x47^WenJianJiaHao)^GeMinHao);
			USART_SendData(USART2,0xef);
			if(GeMinHao==9)
			{
				GongNengTanShi_Time[7]=1;
			}else{
				ShangCiBoFang[1]=GeMinHao;
			}
		}else if(WenJianJiaHao==140){
			USART_SendData(USART2,0x7e);
			USART_SendData(USART2,0x03);
			USART_SendData(USART2,0x05);
			USART_SendData(USART2,0x06);
			USART_SendData(USART2,0xef);
		}else if(WenJianJiaHao==141){
			USART_SendData(USART2,0x7e);
			USART_SendData(USART2,0x03);
			USART_SendData(USART2,0x06);
			USART_SendData(USART2,0x05);
			USART_SendData(USART2,0xef);
		}
	}
}


