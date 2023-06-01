#include "bsp.h"
#include "ZongZhiXin.h"

u8 GongNeng_HuanCun[2060],GongNeng2_HuanCun[150];       //[0]:���ܺţ�[1 ~ x]:����
uint8_t FaSong_HuanCun[2060],FaSong2_HuanCun[150];           
u16 ZhiLin_ChangDu[256],ZongXunHuan_i=0,ZongXunHuan_j=0,ZhiLin2_ChangDu[256],ZongXunHuan2_i=0,ZongXunHuan2_j=0;
u16 AnWeiSouXun_Flag=0,AnWeiSouXun_Time=0,FenJi_Num=0,FenJiHuiYin_Flag=0;
u8 XuLieHao[5]={0x01,0x02,0x03,0x04,0x05};
u8 FenJi_XuLieHao_H1[5]={0x00,0x00,0x00,0x00,0x00},FenJi_XuLieHao[10][5],FenJiHaoFuZhi_HuanCun=0;
//extern uint8_t ChengXu_Data[2048],Flash_ChengXu_Data[2048],Flash_ChengXu_Data2[2048];


/********************** ��ʼ������ ***********************/
#if 1
void Host_Init(void)
{
    u16 ZhuJi_Init_i=0;
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
		SlaveDeviceSerialNumArr[ ZhuJi_Init_i ][ 0 ]=0;
		SlaveDeviceSerialNumArr[ ZhuJi_Init_i ][ 1 ]=0;
		SlaveDeviceSerialNumArr[ ZhuJi_Init_i ][ 2 ]=0;
		SlaveDeviceSerialNumArr[ ZhuJi_Init_i ][ 3 ]=0;
		SlaveDeviceSerialNumArr[ ZhuJi_Init_i ][ 4 ]=0;
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
    ZhiLin_ChangDu[0x20-1]=9;           //LED����
    ZhiLin_ChangDu[0x21-1]=9;           //LED�����趨
    ZhiLin_ChangDu[0x22-1]=14;         //LEDѭ������
    ZhiLin_ChangDu[0x23-1]=13;         //LEDѭ�������Σ�����
    ZhiLin_ChangDu[0x24-1]=15;         //LEDѭ����˸
	ZhiLin2_ChangDu[0]=4;//ָ��ȳ�ʼ��
	ZhiLin2_ChangDu[1]=11;//ָ��ȳ�ʼ��
}
#endif
/************************ ��ѭ�� *************************/
#if 1
void ZongXunHuan(void)
{
    Host_querySerialNum();  //�����������к�
    Host_reponsePC();       //����Ӧ��PC
    Host_responseSlave();   //����Ӧ��ӻ�
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: Host_querySerialNum
*	����˵��: �����������к�
*           ���������Ĵӻ����������          SlaveDeviceCount
*           ���������Ĵӻ����кŴ�������      SlaveDeviceSerialNumArr
*           Ȼ����ú������뵽flash��         flash_WriteSlaveDeviceSerialNumArr()
*********************************************************************************************************
*/
#if 1
void Host_querySerialNum(void)
{
    /* �ӻ����кż��ģʽ */
	if(AnWeiSouXun_Flag>0)
	{
		if(((AnWeiSouXun_Time>10)&&(AnWeiSouXun_Flag!=41))||((AnWeiSouXun_Time>20)&&(AnWeiSouXun_Flag==41)))    //10msδ�յ����ݽ�����һ�η���ģʽ,��ֵ�������Ҫ����20ms����Ϊ�����������ݵ��ӻ����ղ������������ݸ����������յ������ʱ����10ms���ڣ���ֵ��Ҫ20ms�ôӻ��յ����������ݣ�
		{
			if(AnWeiSouXun_Flag>10000)                                      //����10000��ʾ�ȴ��ڼ�δ�յ�����������
			{
				AnWeiSouXun_Flag-=10000;
				FenJi_XuLieHao_H1[(AnWeiSouXun_Flag-1)/8]^=(0x80>>((AnWeiSouXun_Flag-1)%8));                    //���㼴�����͵�FenJi_XuLieHao_H1,����һ�η��͵�λ��Ϊ0
			}
            //���кż��������У���Ҫ����40�β����һ�μ���
			if((AnWeiSouXun_Flag%10000)<40) 
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
				AnWeiSouXun_Flag+=10001;                                    //�ƽ�һλ������δ�յ��ֻ�����ģʽ
				TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,8);                    //�Էֻ���������
				AnWeiSouXun_Time=1;                                         //ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
			}
            else if((AnWeiSouXun_Flag%10000)==40)   //���һ�����кż���
            {	
                //ͳ��δ�յ���Ӧ�ļ������������к�ȫ��Ϊδ�յ���Ӧ��
				if((FenJi_XuLieHao_H1[0]==0x00)&&(FenJi_XuLieHao_H1[1]==0x00)&&(FenJi_XuLieHao_H1[2]==0x00)&&(FenJi_XuLieHao_H1[3]==0x00)&&(FenJi_XuLieHao_H1[4]==0x00)) 
				{
					FenJiHuiYin_Flag++;
				}else
                {
					FenJiHuiYin_Flag=0;
				}
                //δ�յ���Ӧ�ļ�������С��3�Σ��Դӻ���ֵ����������
				if(FenJiHuiYin_Flag<=3)  
				{
					SlaveDeviceSerialNumArr[SlaveDeviceCount][0]=~FenJi_XuLieHao_H1[0];     //���õ��Ļ���ȡ���������к�
					SlaveDeviceSerialNumArr[SlaveDeviceCount][1]=~FenJi_XuLieHao_H1[1];
					SlaveDeviceSerialNumArr[SlaveDeviceCount][2]=~FenJi_XuLieHao_H1[2];
					SlaveDeviceSerialNumArr[SlaveDeviceCount][3]=~FenJi_XuLieHao_H1[3];
					SlaveDeviceSerialNumArr[SlaveDeviceCount][4]=~FenJi_XuLieHao_H1[4];
					FaSong_HuanCun[0]=0xff;
					FaSong_HuanCun[1]=0xff;
					FaSong_HuanCun[2]=0x02;
					FaSong_HuanCun[3]=SlaveDeviceSerialNumArr[SlaveDeviceCount][0];
					FaSong_HuanCun[4]=SlaveDeviceSerialNumArr[SlaveDeviceCount][1];
					FaSong_HuanCun[5]=SlaveDeviceSerialNumArr[SlaveDeviceCount][2];
					FaSong_HuanCun[6]=SlaveDeviceSerialNumArr[SlaveDeviceCount][3];
					FaSong_HuanCun[7]=SlaveDeviceSerialNumArr[SlaveDeviceCount][4];
					FaSong_HuanCun[8]= ( SlaveDeviceCount + 1 ) / 256;      //�ӻ���Ŵ�1��ʼ
					FaSong_HuanCun[9]= ( SlaveDeviceCount + 1 ) % 256;
//					TonXunFaSong(USART_PC,FaSong_HuanCun,0,10);               //�Դӻ���Ÿ�ֵ
					TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);               //�Դӻ���Ÿ�ֵ
					AnWeiSouXun_Flag=41;                                    //���븳ֵ��ȴ���Ӧģʽ
					AnWeiSouXun_Time=1;                                     //ʱ�ӿ�ʼ��ʱ��10msδ�յ���������Ϊû�д˴ӻ�
				}
                else //����δ��Ӧ�Ĵ�������3�Σ���������
                {
                    flash_WriteSlaveDeviceSerialNumArr();
					FaSong_HuanCun[0]=0;
					FaSong_HuanCun[1]=0;
					FaSong_HuanCun[2]=0;
					FaSong_HuanCun[3]=0;
					FaSong_HuanCun[4]=0;
					FaSong_HuanCun[5]=0;
					FaSong_HuanCun[6]=0;
					FaSong_HuanCun[7]=0;
					AnWeiSouXun_Flag=0;                                     //���÷��ͱ�־λ
					AnWeiSouXun_Time=0;
					FenJiHuiYin_Flag=0;                                     
					FenJi_XuLieHao_H1[0]=0;
					FenJi_XuLieHao_H1[1]=0;
					FenJi_XuLieHao_H1[2]=0;
					FenJi_XuLieHao_H1[3]=0;
					FenJi_XuLieHao_H1[4]=0;
				}
			}
            else    //������һ�μ���
            {
				FaSong_HuanCun[0]=0;
				FaSong_HuanCun[1]=0;
				FaSong_HuanCun[2]=0;
				FaSong_HuanCun[3]=0;
				FaSong_HuanCun[4]=0;
				FaSong_HuanCun[5]=0;
				FaSong_HuanCun[6]=0;
				FaSong_HuanCun[7]=0;
				AnWeiSouXun_Flag=0;                                         //���÷��ͱ�־λ
				FenJi_XuLieHao_H1[0]=0;
				FenJi_XuLieHao_H1[1]=0;
				FenJi_XuLieHao_H1[2]=0;
				FenJi_XuLieHao_H1[3]=0;
				FenJi_XuLieHao_H1[4]=0;
				FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));                                //���㼴�����͵�FenJi_XuLieHao_H1
				FaSong_HuanCun[0]=0xff;
				FaSong_HuanCun[1]=0xff;
				FaSong_HuanCun[2]=0x01;
				FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
				FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
				FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
				FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
				FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
				AnWeiSouXun_Flag=10001;                                     //����10000Ϊδ�յ��ֻ�����ģʽ,�ƽ�һλ������δ�յ��ֻ�����ģʽ
				AnWeiSouXun_Time=1;                                         //ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
				TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,8);                    //�Էֻ���������
			}
		}
	}
}
#endif
/********************** ����Ӧ��PC ***********************/
#if 1
void Host_reponsePC( void )
{
	switch( GongNeng_HuanCun[ 0 ] )
	{
		case 0x01://��ȡ���дӻ����к� A5 01 01 80 7E
			FaSong_HuanCun[ 0 ] = 0x00;//��ַ
			FaSong_HuanCun[ 1 ] = 0x01;//����֡
			FaSong_HuanCun[ 2 ] = SlaveDeviceCount / 256;
			FaSong_HuanCun[ 3 ] = SlaveDeviceCount % 256;
			TonXunFaSong( USART_PC, FaSong_HuanCun, 0, 4);  //���ؼ�⵽�Ĵӻ���
			for( ZongXunHuan_i = 0; ZongXunHuan_i < SlaveDeviceCount; ZongXunHuan_i++ )
			{
				FaSong_HuanCun[ 0 ] = 0x00;
				FaSong_HuanCun[ 1 ] = 0x02;
				FaSong_HuanCun[ 2 ] = SlaveDeviceSerialNumArr[ ZongXunHuan_i ][ 0 ];
				FaSong_HuanCun[ 3 ] = SlaveDeviceSerialNumArr[ ZongXunHuan_i ][ 1 ];
				FaSong_HuanCun[ 4 ] = SlaveDeviceSerialNumArr[ ZongXunHuan_i ][ 2 ];
				FaSong_HuanCun[ 5 ] = SlaveDeviceSerialNumArr[ ZongXunHuan_i ][ 3 ];
				FaSong_HuanCun[ 6 ] = SlaveDeviceSerialNumArr[ ZongXunHuan_i ][ 4 ];
				TonXunFaSong(USART_PC,FaSong_HuanCun,0,7); //���شӻ����к�
			}
            break;
		case 0x02://��λ��Ѱ�ӻ����к� A5 01 02 81 3E
            SlaveDeviceCount = 0;                                                   //��� ram ��ʷ�ӻ��豸��
            flash_WriteSlaveDeviceCount();                                          //��� flash ��ʷ�ӻ��豸��
			AnWeiSouXun_Flag=0;                                                     //���÷��ͱ�־λ
			FenJi_XuLieHao_H1[0]=0;
			FenJi_XuLieHao_H1[1]=0;
			FenJi_XuLieHao_H1[2]=0;
			FenJi_XuLieHao_H1[3]=0;
			FenJi_XuLieHao_H1[4]=0;
			FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));    //���㼴�����͵�FenJi_XuLieHao_H1
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x01;
			FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
			FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
			FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
			FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
			FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
			AnWeiSouXun_Flag=10001;                                                 //����10000Ϊδ�յ��ֻ�����ģʽ,�ƽ�һλ������δ�յ��ֻ�����ģʽ
			AnWeiSouXun_Time=1;                                                     //ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,8);                                //�Էֻ���������
            break;
		case 0x03://�豸����
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x03;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
			FaSong_HuanCun[5]=GongNeng_HuanCun[4];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,6); 
			FaSong_HuanCun[0]=GongNeng_HuanCun[1]*256+GongNeng_HuanCun[2];
			FaSong_HuanCun[1]=1;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,2);
            break;
		case 0x04://��������
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x04;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,4); 
            break;
		case 0x05://����Ч��ִ�� A5 01 05 00 01 01 A0
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x06;
			FaSong_HuanCun[3]=GongNeng_HuanCun[1];
			FaSong_HuanCun[4]=GongNeng_HuanCun[2];
            TonXunFaSong(USART2,FaSong_HuanCun,0,5); //�����ӻ�
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x05;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,4); 
            break;
		case 0x06://��Ч����
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x06;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
			FaSong_HuanCun[5]=GongNeng_HuanCun[4];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,4); 
            break;
		case 0x07://������� 
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x07;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
//			for(ZongXunHuan_i=0;ZongXunHuan_i<2048;ZongXunHuan_i++)
//			{
////				Flash_ChengXu_Data[ZongXunHuan_i]=GongNeng_HuanCun[ZongXunHuan_i+4];
//			}
//			Flash_Write_2K(0x08000000+GongNeng_HuanCun[1]*65536+GongNeng_HuanCun[2]*256+GongNeng_HuanCun[3]);
//			TonXunFaSong(USART_PC,FaSong_HuanCun,0,5); 
            break;
		case 0x08://����ӻ����к� A5 01 08 86 BE
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x07;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);
			FaSong_HuanCun[0]=0x07;
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,1);
            break;
		case 0xf0:
			for(ZongXunHuan_i=0;ZongXunHuan_i<4096;ZongXunHuan_i++)
			{
//				USART_SendData(USART_PC,ChengXu_Data[ZongXunHuan_i]);
			}
            break;
		case 0x64:
//			Flash_Write_Str(0x080107fd,GongNeng_HuanCun,0,7); 
            break;
		case 0x20://LED����
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            TonXunFaSong(USART1,FaSong_HuanCun,0,5);
            break;
		case 0x21://LED�����趨
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            TonXunFaSong(USART1,FaSong_HuanCun,0,5);
            break;
		case 0x22://LEDѭ������
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];
            TonXunFaSong(USART2,FaSong_HuanCun,0,10);
            TonXunFaSong(USART1,FaSong_HuanCun,0,10);
            break;
		case 0x23://LEDѭ�������Σ�����
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            TonXunFaSong(USART2,FaSong_HuanCun,0,9);
            TonXunFaSong(USART1,FaSong_HuanCun,0,9);
            break;
		case 0x24://LEDѭ����˸
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];
            FaSong_HuanCun[10]=GongNeng_HuanCun[10];
            TonXunFaSong(USART2,FaSong_HuanCun,0,11);
            TonXunFaSong(USART1,FaSong_HuanCun,0,11);
            break;
		case 0xff://��ѯ�������к� A5 01 FF 00 FF
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=XuLieHao[0];
			FaSong_HuanCun[3]=XuLieHao[1];
			FaSong_HuanCun[4]=XuLieHao[2];
			FaSong_HuanCun[5]=XuLieHao[3];
			FaSong_HuanCun[6]=XuLieHao[4];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,7); 
            break;
	}
	for(ZongXunHuan_i=0;ZongXunHuan_i<2060;ZongXunHuan_i++)
	{
		GongNeng_HuanCun[ZongXunHuan_i]=0;
	}
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: Host_responseSlave
*	����˵��: ����Ӧ��ӻ�
*********************************************************************************************************
*/
#if 1
void Host_responseSlave(void)
{
    switch(GongNeng2_HuanCun[0])
	{
		case 1://��λ��Ѱģ�����к�
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x01;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,2);  
		break;
		case 2://�յ��ֻ��Ÿ�ֵ�ɹ�����
            FaSong_HuanCun[0]=GongNeng2_HuanCun[1];
            FaSong_HuanCun[1]=GongNeng2_HuanCun[2];
            FaSong_HuanCun[2]=GongNeng2_HuanCun[3];
            FaSong_HuanCun[3]=GongNeng2_HuanCun[4];
            FaSong_HuanCun[4]=GongNeng2_HuanCun[5];
            FaSong_HuanCun[5]=GongNeng2_HuanCun[6];
            FaSong_HuanCun[6]=GongNeng2_HuanCun[7];
            FaSong_HuanCun[7]=0x00;
            SlaveDeviceCount++;
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,8);//��������һ�����к�
		break;
	}
	for(ZongXunHuan2_i=0;ZongXunHuan2_i<150;ZongXunHuan2_i++)
	{
		GongNeng2_HuanCun[ZongXunHuan2_i]=0;
	}
}
#endif


