#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
u8 GongNeng_HuanCun[2060],FaSong_HuanCun[2060],GongNeng2_HuanCun[150],FaSong2_HuanCun[150];
u16 ZhiLin_ChangDu[256],ZongXunHuan_i=0,ZongXunHuan_j=0,ZhiLin2_ChangDu[256],ZongXunHuan2_i=0,ZongXunHuan2_j=0;
u16 ZhuJi_Init_i=0;
u16 SheBeiShu=5;
u16 AnWeiSouXun_Flag=0,AnWeiSouXun_Time=0,FenJi_Num=0,FenJiHuiYin_Flag=0;
u8 XuLieHao[5]={0x01,0x02,0x03,0x04,0x05};
u8 FenJi_XuLieHao_H1[5]={0x00,0x00,0x00,0x00,0x00},FenJi_XuLieHao[10][5],FenJiHaoFuZhi_HuanCun=0;
extern uint8_t ChengXu_Data[2048],Flash_ChengXu_Data[2048],Flash_ChengXu_Data2[2048];
void ZhuJi_Init(void)
{
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<2048;ZhuJi_Init_i++)
	{
		Flash_ChengXu_Data[ZhuJi_Init_i]=0;
		Flash_ChengXu_Data2[ZhuJi_Init_i]=0;
	}
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<2060;ZhuJi_Init_i++)
	{
		GongNeng_HuanCun[ZhuJi_Init_i]=0;
	}
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<150;ZhuJi_Init_i++)
	{
		GongNeng2_HuanCun[ZhuJi_Init_i]=0;
	}
	
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<256;ZhuJi_Init_i++)
	{
		ZhiLin_ChangDu[ZhuJi_Init_i]=0;
	}
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<256;ZhuJi_Init_i++)
	{
		ZhiLin2_ChangDu[ZhuJi_Init_i]=0;
	}
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<10;ZhuJi_Init_i++)
	{
		FenJi_XuLieHao[ZhuJi_Init_i][0]=0;
		FenJi_XuLieHao[ZhuJi_Init_i][1]=0;
		FenJi_XuLieHao[ZhuJi_Init_i][2]=0;
		FenJi_XuLieHao[ZhuJi_Init_i][3]=0;
		FenJi_XuLieHao[ZhuJi_Init_i][4]=0;
	}
	ZhiLin_ChangDu[0]=5;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[1]=5;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[2]=9;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[3]=7;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[4]=7;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[5]=9;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[6]=2056;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[7]=5;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[0xf0-1]=5;//ָ��ȳ�ʼ��
	ZhiLin_ChangDu[254]=5;//ָ��ȳ�ʼ��
	
	ZhiLin2_ChangDu[0]=4;//ָ��ȳ�ʼ��
	ZhiLin2_ChangDu[1]=11;//ָ��ȳ�ʼ��
	
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<30;ZhuJi_Init_i++)
	{
		Flash_ChengXu_Data[1024+ZhuJi_Init_i]=ZhuJi_Init_i+1;
	}
	Flash_Write_2K(0x08010000);
	
	Flash_ChengXu_Data2[0]=0x00;
	Flash_ChengXu_Data2[1]=0x06;
	Flash_Write_Str(0x08010000,Flash_ChengXu_Data2,0,2); 
}
void ZongXunHuan(void)
{
	if(AnWeiSouXun_Flag>0)//�ֻ����кż��ģʽ
	{
		if(((AnWeiSouXun_Time>10)&&(AnWeiSouXun_Flag!=41))||((AnWeiSouXun_Time>20)&&(AnWeiSouXun_Flag==41)))//10msδ�յ����ݽ�����һ�η���ģʽ,��ֵ�������Ҫ����20ms
		{
			if(AnWeiSouXun_Flag>10000)//����10000��ʾ�ȴ��ڼ�δ�յ�����������
			{
				AnWeiSouXun_Flag-=10000;
				FenJi_XuLieHao_H1[(AnWeiSouXun_Flag-1)/8]^=(0x80>>((AnWeiSouXun_Flag-1)%8));//���㼴�����͵�FenJi_XuLieHao_H1,����һ�η��͵�λ��Ϊ0
			}
			if((AnWeiSouXun_Flag%10000)<40)//δ������5�ֽڣ��������
			{
				FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));//����һλ��Ϊ1
				FaSong_HuanCun[0]=0xff;
				FaSong_HuanCun[1]=0xff;
				FaSong_HuanCun[2]=0x01;
				FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
				FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
				FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
				FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
				FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
				AnWeiSouXun_Flag+=10001;//�ƽ�һλ������δ�յ��ֻ�����ģʽ
				AnWeiSouXun_Time=1;//ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
				TonXunFaSong(USART2,FaSong_HuanCun,0,8);//�Էֻ���������
			}else if((AnWeiSouXun_Flag%10000)==40){//����һ�����кż���		
				if((FenJi_XuLieHao_H1[0]==0x00)&&(FenJi_XuLieHao_H1[1]==0x00)&&(FenJi_XuLieHao_H1[2]==0x00)&&(FenJi_XuLieHao_H1[3]==0x00)&&(FenJi_XuLieHao_H1[4]==0x00))
				{
					FenJiHuiYin_Flag++;
				}else{
					FenJiHuiYin_Flag=0;
				}
				if(FenJiHuiYin_Flag<=3)
				{
					FenJi_XuLieHao[FenJi_Num][0]=~FenJi_XuLieHao_H1[0];//���õ��Ļ���ȡ���������к�
					FenJi_XuLieHao[FenJi_Num][1]=~FenJi_XuLieHao_H1[1];
					FenJi_XuLieHao[FenJi_Num][2]=~FenJi_XuLieHao_H1[2];
					FenJi_XuLieHao[FenJi_Num][3]=~FenJi_XuLieHao_H1[3];
					FenJi_XuLieHao[FenJi_Num][4]=~FenJi_XuLieHao_H1[4];
					FenJiHaoFuZhi_HuanCun=FenJi_Num+1;
					FaSong_HuanCun[0]=0xff;
					FaSong_HuanCun[1]=0xff;
					FaSong_HuanCun[2]=0x02;
					FaSong_HuanCun[3]=FenJi_XuLieHao[FenJi_Num][0];
					FaSong_HuanCun[4]=FenJi_XuLieHao[FenJi_Num][1];
					FaSong_HuanCun[5]=FenJi_XuLieHao[FenJi_Num][2];
					FaSong_HuanCun[6]=FenJi_XuLieHao[FenJi_Num][3];
					FaSong_HuanCun[7]=FenJi_XuLieHao[FenJi_Num][4];
					FaSong_HuanCun[8]=FenJiHaoFuZhi_HuanCun/256;
					FaSong_HuanCun[9]=FenJiHaoFuZhi_HuanCun%256;
//					TonXunFaSong(USART1,FaSong_HuanCun,0,10);//�Էֻ���ֵ
					TonXunFaSong(USART2,FaSong_HuanCun,0,10);//�Էֻ���ֵ
					AnWeiSouXun_Flag=41;//���븳ֵ��ȴ���Ӧģʽ
					AnWeiSouXun_Time=1;//ʱ�ӿ�ʼ��ʱ��10msδ�յ���������Ϊû�д˴ӻ�
				}else{
					FaSong_HuanCun[0]=0;
					FaSong_HuanCun[1]=0;
					FaSong_HuanCun[2]=0;
					FaSong_HuanCun[3]=0;
					FaSong_HuanCun[4]=0;
					FaSong_HuanCun[5]=0;
					FaSong_HuanCun[6]=0;
					FaSong_HuanCun[7]=0;
					AnWeiSouXun_Flag=0;//���÷��ͱ�־λ
					AnWeiSouXun_Time=0;
					FenJiHuiYin_Flag=0;
					FenJi_XuLieHao_H1[0]=0;
					FenJi_XuLieHao_H1[1]=0;
					FenJi_XuLieHao_H1[2]=0;
					FenJi_XuLieHao_H1[3]=0;
					FenJi_XuLieHao_H1[4]=0;
				}
			}else{
				FaSong_HuanCun[0]=0;
				FaSong_HuanCun[1]=0;
				FaSong_HuanCun[2]=0;
				FaSong_HuanCun[3]=0;
				FaSong_HuanCun[4]=0;
				FaSong_HuanCun[5]=0;
				FaSong_HuanCun[6]=0;
				FaSong_HuanCun[7]=0;
				AnWeiSouXun_Flag=0;//���÷��ͱ�־λ
				FenJi_XuLieHao_H1[0]=0;
				FenJi_XuLieHao_H1[1]=0;
				FenJi_XuLieHao_H1[2]=0;
				FenJi_XuLieHao_H1[3]=0;
				FenJi_XuLieHao_H1[4]=0;
				FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));//���㼴�����͵�FenJi_XuLieHao_H1
				FaSong_HuanCun[0]=0xff;
				FaSong_HuanCun[1]=0xff;
				FaSong_HuanCun[2]=0x01;
				FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
				FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
				FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
				FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
				FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
				AnWeiSouXun_Flag=10001;//����10000Ϊδ�յ��ֻ�����ģʽ,�ƽ�һλ������δ�յ��ֻ�����ģʽ
				AnWeiSouXun_Time=1;//ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
				TonXunFaSong(USART2,FaSong_HuanCun,0,8);//�Էֻ���������
			}
		}
	}
	switch(GongNeng_HuanCun[0])
	{
		case 1://��ȡ����ģ�����к�
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=1;
			FaSong_HuanCun[2]=ChengXu_Data[0];
			FaSong_HuanCun[3]=ChengXu_Data[1];
			TonXunFaSong(USART1,ChengXu_Data,0,4);  
			for(ZongXunHuan_i=0;ZongXunHuan_i<ChengXu_Data[0]*256+ChengXu_Data[1];ZongXunHuan_i++)
			{
				FaSong_HuanCun[0]=0;
				FaSong_HuanCun[1]=2;
				FaSong_HuanCun[2]=ChengXu_Data[0x400+ZongXunHuan_i*5];
				FaSong_HuanCun[3]=ChengXu_Data[0x401+ZongXunHuan_i*5];
				FaSong_HuanCun[4]=ChengXu_Data[0x402+ZongXunHuan_i*5];
				FaSong_HuanCun[5]=ChengXu_Data[0x403+ZongXunHuan_i*5];
				FaSong_HuanCun[6]=ChengXu_Data[0x404+ZongXunHuan_i*5];
				TonXunFaSong(USART1,FaSong_HuanCun,0,7); 
			}
		break;
		case 2://��λ��Ѱģ�����к� a5 01 02 81 3e
			AnWeiSouXun_Flag=0;//���÷��ͱ�־λ
			FenJi_XuLieHao_H1[0]=0;
			FenJi_XuLieHao_H1[1]=0;
			FenJi_XuLieHao_H1[2]=0;
			FenJi_XuLieHao_H1[3]=0;
			FenJi_XuLieHao_H1[4]=0;
			FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));//���㼴�����͵�FenJi_XuLieHao_H1
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x01;
			FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
			FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
			FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
			FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
			FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
			AnWeiSouXun_Flag=10001;//����10000Ϊδ�յ��ֻ�����ģʽ,�ƽ�һλ������δ�յ��ֻ�����ģʽ
			AnWeiSouXun_Time=1;//ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
			TonXunFaSong(USART2,FaSong_HuanCun,0,8);//�Էֻ���������
		break;
		case 3://�豸����
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=3;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
			FaSong_HuanCun[5]=GongNeng_HuanCun[4];
			TonXunFaSong(USART1,FaSong_HuanCun,0,6); 
			FaSong_HuanCun[0]=GongNeng_HuanCun[1]*256+GongNeng_HuanCun[2];
			FaSong_HuanCun[1]=1;
			TonXunFaSong(USART2,FaSong_HuanCun,0,2);
		break;
		case 4://��������
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=4;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			TonXunFaSong(USART1,FaSong_HuanCun,0,4); 
		break;
		case 5://����Ч��ִ��
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=5;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			TonXunFaSong(USART1,FaSong_HuanCun,0,4); 
		break;
		case 6://��Ч����
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=6;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
			FaSong_HuanCun[5]=GongNeng_HuanCun[4];
			TonXunFaSong(USART1,FaSong_HuanCun,0,4); 
		break;
		case 7://�������
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=7;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
			for(ZongXunHuan_i=0;ZongXunHuan_i<2048;ZongXunHuan_i++)
			{
				Flash_ChengXu_Data[ZongXunHuan_i]=GongNeng_HuanCun[ZongXunHuan_i+4];
			}
			Flash_Write_2K(0x08000000+GongNeng_HuanCun[1]*65536+GongNeng_HuanCun[2]*256+GongNeng_HuanCun[3]);
			TonXunFaSong(USART1,FaSong_HuanCun,0,5); 
		break;
		case 8://���ģ�����к�
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x07;
			TonXunFaSong(USART2,FaSong_HuanCun,0,3);
			FaSong_HuanCun[0]=0x07;
			TonXunFaSong(USART1,FaSong_HuanCun,0,1);
		break;
		case 0xf0:
			for(ZongXunHuan_i=0;ZongXunHuan_i<4096;ZongXunHuan_i++)
			{
				USART_SendData(USART1,ChengXu_Data[ZongXunHuan_i]);
			}
		break;
		case 100:
			Flash_Write_Str(0x080107fd,GongNeng_HuanCun,0,7); 
		break;
		case 255://�������кŲ�ѯ
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=XuLieHao[0];
			FaSong_HuanCun[3]=XuLieHao[1];
			FaSong_HuanCun[4]=XuLieHao[2];
			FaSong_HuanCun[5]=XuLieHao[3];
			FaSong_HuanCun[6]=XuLieHao[4];
			TonXunFaSong(USART1,FaSong_HuanCun,0,7); 
		break;
	}
	for(ZongXunHuan_i=0;ZongXunHuan_i<2060;ZongXunHuan_i++)
	{
		GongNeng_HuanCun[ZongXunHuan_i]=0;
	}
	
	switch(GongNeng2_HuanCun[0])
	{
		case 1://��λ��Ѱģ�����к�
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=1;
			TonXunFaSong(USART2,FaSong_HuanCun,0,2);  
		break;
		case 2://�յ��ֻ��Ÿ�ֵ�ɹ�����
//			if((GongNeng2_HuanCun[1]*256+GongNeng2_HuanCun[2])==FenJiHaoFuZhi_HuanCun)//���ص���֮ǰ��ֵ�ķֻ�
//			{
//				FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][0]=GongNeng2_HuanCun[3];
//				FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][1]=GongNeng2_HuanCun[4];
//				FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][2]=GongNeng2_HuanCun[5];
//				FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][3]=GongNeng2_HuanCun[6];
//				FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][4]=GongNeng2_HuanCun[7];
//				
//				FaSong_HuanCun[0]=0x00;
//				FaSong_HuanCun[1]=0x02;
//				FaSong_HuanCun[2]=FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][0];
//				FaSong_HuanCun[3]=FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][1];
//				FaSong_HuanCun[4]=FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][2];
//				FaSong_HuanCun[5]=FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][3];
//				FaSong_HuanCun[6]=FenJi_XuLieHao[FenJiHaoFuZhi_HuanCun-1][4];
//				FaSong_HuanCun[7]=FenJiHaoFuZhi_HuanCun/256;
//				FaSong_HuanCun[8]=FenJiHaoFuZhi_HuanCun%256;
		
				FaSong_HuanCun[0]=GongNeng2_HuanCun[1];
				FaSong_HuanCun[1]=GongNeng2_HuanCun[2];
				FaSong_HuanCun[2]=GongNeng2_HuanCun[3];
				FaSong_HuanCun[3]=GongNeng2_HuanCun[4];
				FaSong_HuanCun[4]=GongNeng2_HuanCun[5];
				FaSong_HuanCun[5]=GongNeng2_HuanCun[6];
				FaSong_HuanCun[6]=GongNeng2_HuanCun[7];
				FaSong_HuanCun[7]=0x00;
				TonXunFaSong(USART1,FaSong_HuanCun,0,8);//��������һ�����к�
//			}
		break;
	}
	for(ZongXunHuan2_i=0;ZongXunHuan2_i<150;ZongXunHuan2_i++)
	{
		GongNeng2_HuanCun[ZongXunHuan2_i]=0;
	}
}

