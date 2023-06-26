#include "bsp.h"
#include "ZongZhiXin.h"

u8 GongNeng_HuanCun[2060],GongNeng2_HuanCun[150];       //[0]:���ܺţ�[1 ~ x]:����
uint8_t FaSong_HuanCun[2060],FaSong2_HuanCun[150];           
u16 ZhiLin_ChangDu[256],ZongXunHuan_i=0,ZongXunHuan_j=0,ZhiLin2_ChangDu[256],ZongXunHuan2_i=0,ZongXunHuan2_j=0;
u16 AnWeiSouXun_Flag=0, AnWeiSouXun_Time=0,FenJi_Num=0,FenJiHuiYin_Flag=0;
u16 CheckSlaveState_Flag = 0, CheckSlaveState_Time = 0, CheckSlaveState_index = 0;
u16 CheckSlaveOnline_PeriodTime = 0, CheckSlaveOnline_PeriodFlag = 0, CheckSlaveOnline_Time = 0, CheckSlaveOnline_Flag = 0, CheckSlaveOnline_index = 0;
u8 CheckSlaveOnline_recordArr[ 64 ] = {0}, CheckSlaveOnline_bug = 0;
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
//����-����ָ��ȳ�ʼ��
	ZhiLin_ChangDu[0x01-1]=5;//��ȡ���дӻ�״̬����ţ����к�
	ZhiLin_ChangDu[0x02-1]=5;//��λ��Ѱ�ӻ����к�
	ZhiLin_ChangDu[0x03-1]=9;//�豸����
	ZhiLin_ChangDu[0x04-1]=7;//��������
	ZhiLin_ChangDu[0x05-1]=7;//����Ч��ִ��
	ZhiLin_ChangDu[0x06-1]=9;//��Ч����
	ZhiLin_ChangDu[0x07-1]=2056;//�������
	ZhiLin_ChangDu[0x08-1]=5;//����ӻ����к�
	ZhiLin_ChangDu[0x09-1]=5;//������дӻ�״̬
	ZhiLin_ChangDu[0xff-1]=5;//��ѯ�������к�
    
    ZhiLin_ChangDu[0x20-1]=9;//LEDͨ��
    ZhiLin_ChangDu[0x21-1]=9;//LED�ϵ�
    ZhiLin_ChangDu[0x22-1]=10;//LED�����趨
    ZhiLin_ChangDu[0x23-1]=14;//LED���ν���
    ZhiLin_ChangDu[0x24-1]=17;//LEDѭ������
    ZhiLin_ChangDu[0x25-1]=17;//LEDѭ����˸
    
    ZhiLin_ChangDu[0x30-1]=9;//LOCKͨ��
    ZhiLin_ChangDu[0x31-1]=9;//LOCK�ϵ�
    ZhiLin_ChangDu[0x32-1]=12;//LOCK�Ϻ�ͨ
    ZhiLin_ChangDu[0x33-1]=12;//LOCKͨ���
//����-�ӻ�ָ��ȳ�ʼ��
	ZhiLin2_ChangDu[0]=4;//ָ��ȳ�ʼ��
	ZhiLin2_ChangDu[1]=11;//ָ��ȳ�ʼ��
	ZhiLin2_ChangDu[0x0b-1]=6;//ָ��ȳ�ʼ��
    
    ZhiLin2_ChangDu[0x20-1]=8;//LEDͨ��
    ZhiLin2_ChangDu[0x21-1]=8;//LED�ϵ�
    ZhiLin2_ChangDu[0x22-1]=9;//LED�����趨
    ZhiLin2_ChangDu[0x23-1]=13;//LED���ν���
    ZhiLin2_ChangDu[0x24-1]=16;//LEDѭ������
    ZhiLin2_ChangDu[0x25-1]=16;//LEDѭ����˸
    
    ZhiLin2_ChangDu[0x30-1]=8;//LOCKͨ��
    ZhiLin2_ChangDu[0x31-1]=8;//LOCK�ϵ�
    ZhiLin2_ChangDu[0x32-1]=11;//LOCK�Ϻ�ͨ
    ZhiLin2_ChangDu[0x33-1]=11;//LOCKͨ���
}
#endif
/************************ ��ѭ�� *************************/
#if 1
void ZongXunHuan(void)
{
    Host_querySerialNum();  //�����������к�
    Host_checkSlaveState();//�������ӻ�״̬
    Host_checkSlaveOnline();//���ڼ��ӻ�����״̬
    Host_reponsePC();       //����Ӧ��PC
    Host_responseSlave();   //����Ӧ��ӻ�
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: Host_querySerialNum
*	����˵��: �����������к�
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
					SlaveArr[ SlaveSize ].serialArr[0] = ~FenJi_XuLieHao_H1[0];     //���õ��Ļ���ȡ���������к�
					SlaveArr[ SlaveSize ].serialArr[1] =~FenJi_XuLieHao_H1[1];
					SlaveArr[ SlaveSize ].serialArr[2] =~FenJi_XuLieHao_H1[2];
					SlaveArr[ SlaveSize ].serialArr[3] =~FenJi_XuLieHao_H1[3];
					SlaveArr[ SlaveSize ].serialArr[4] =~FenJi_XuLieHao_H1[4];
					FaSong_HuanCun[0]=0xff;
					FaSong_HuanCun[1]=0xff;
					FaSong_HuanCun[2]=0x02;
					FaSong_HuanCun[3]=SlaveArr[ SlaveSize ].serialArr[0];
					FaSong_HuanCun[4]=SlaveArr[ SlaveSize ].serialArr[1];
					FaSong_HuanCun[5]=SlaveArr[ SlaveSize ].serialArr[2];
					FaSong_HuanCun[6]=SlaveArr[ SlaveSize ].serialArr[3];
					FaSong_HuanCun[7]=SlaveArr[ SlaveSize ].serialArr[4];
					FaSong_HuanCun[8]= ( SlaveSize + 1 ) / 256;      //�ӻ���Ŵ�1��ʼ
					FaSong_HuanCun[9]= ( SlaveSize + 1 ) % 256;
					TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);               //�Դӻ���Ÿ�ֵ
					AnWeiSouXun_Flag=41;                                    //���븳ֵ��ȴ���Ӧģʽ
					AnWeiSouXun_Time=1;                                     //ʱ�ӿ�ʼ��ʱ��10msδ�յ���������Ϊû�д˴ӻ�
				}
                else //����δ��Ӧ�Ĵ�������3�Σ���������
                {
                    wirteSlaveArr();    //дram��flash
                    //���ؼ�⵽�Ĵӻ���
                    {
                        FaSong_HuanCun[ 0 ] = 0x00;//��ַ
                        FaSong_HuanCun[ 1 ] = 0x09;//����֡
                        FaSong_HuanCun[ 2 ] = SlaveSize / 256;
                        FaSong_HuanCun[ 3 ] = SlaveSize % 256;
                        TonXunFaSong( USART_PC, FaSong_HuanCun, 0, 4);  
                    }
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
/*
*********************************************************************************************************
*	�� �� ��: Host_checkSlaveState
*	����˵��: ������дӻ�״̬
*********************************************************************************************************
*/
void Host_checkSlaveState( void )
{
    //����������дӻ�״̬
    if( CheckSlaveState_Flag > 0 )
    {
        if( ( CheckSlaveState_Time < 200 && CheckSlaveState_Flag < 10000 ) || CheckSlaveState_Time > 200 )//δ��ʱ���ػ�ʱ������δ��ʱδ���أ�������
        {
            if( CheckSlaveState_Time < 200 && CheckSlaveState_Flag < 10000 ) //��ȷ���أ�δ��ʱ���أ�
            {
                SlaveArr[ CheckSlaveState_index ].state = 1;      //�ӻ�����
                //���ص��Լ�⵽�ľɴӻ���Ϣ��ֻ�������ߴӻ���
                FaSong_HuanCun[ 0 ] = 0x00;
                FaSong_HuanCun[ 1 ] = 0x02;
                FaSong_HuanCun[ 2 ] = SlaveArr[ CheckSlaveState_index ].serialArr[0];        //�ӻ����кţ������ֽ�
                FaSong_HuanCun[ 3 ] = SlaveArr[ CheckSlaveState_index ].serialArr[1];
                FaSong_HuanCun[ 4 ] = SlaveArr[ CheckSlaveState_index ].serialArr[2];
                FaSong_HuanCun[ 5 ] = SlaveArr[ CheckSlaveState_index ].serialArr[3];
                FaSong_HuanCun[ 6 ] = SlaveArr[ CheckSlaveState_index ].serialArr[4];
                FaSong_HuanCun[ 7 ] = SlaveArr[ CheckSlaveState_index ].assignArr[0];       //��ֵ��Ÿ��ֽ�
                FaSong_HuanCun[ 8 ] = SlaveArr[ CheckSlaveState_index ].assignArr[1];       //��ֵ��ŵ��ֽ�

                TonXunFaSong(USART_PC,FaSong_HuanCun,0,9); //���ص��ԣ����дӻ�״̬����ţ����к�
            }
            else if( CheckSlaveState_Time > 200 )//��ʱ
            {
                CheckSlaveState_Flag++;
                SlaveArr[ CheckSlaveState_index ].state = 0;      //�ӻ�����
            }
            if( SlaveArr[ CheckSlaveState_index ].state == 1 || CheckSlaveState_Flag >= 10003 )//�ӻ����ػ򳬹�����δ���أ������һ���ɴӻ�
            {
                CheckSlaveState_Flag = 10001;
                CheckSlaveState_index++;
            }
            if( CheckSlaveState_index < SlaveSize )
            {
                //1���Ծɴӻ���Ÿ�ֵ
                FaSong_HuanCun[0]=0xff;
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x02;
                FaSong_HuanCun[3]=SlaveArr[ CheckSlaveState_index ].serialArr[0];
                FaSong_HuanCun[4]=SlaveArr[ CheckSlaveState_index ].serialArr[1];
                FaSong_HuanCun[5]=SlaveArr[ CheckSlaveState_index ].serialArr[2];
                FaSong_HuanCun[6]=SlaveArr[ CheckSlaveState_index ].serialArr[3];
                FaSong_HuanCun[7]=SlaveArr[ CheckSlaveState_index ].serialArr[4];
                FaSong_HuanCun[8]=SlaveArr[ CheckSlaveState_index ].assignArr[0];      //�ӻ���Ŵ�1��ʼ
                FaSong_HuanCun[9]=SlaveArr[ CheckSlaveState_index ].assignArr[1];
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);             //�Դӻ���Ÿ�ֵ              
                CheckSlaveState_Time = 1;
            }
            else
            {
                //�������ɴӻ���Ϣ
                CheckSlaveState_Flag = 0;
                CheckSlaveState_Time = 0;
                CheckSlaveState_index = 0;
                //2����ʼ��λ��Ѱ�´ӻ���Ϣ        
                AnWeiSouXun_Flag=0;                                                       //���÷��ͱ�־λ
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
                AnWeiSouXun_Time=1;                                                       //ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
            }
        }
    }
}
/*
*********************************************************************************************************
*	�� �� ��: Host_checkSlaveOnline
*	����˵��: ���ӻ�����״̬
*********************************************************************************************************
*/

//CheckSlaveOnline_Time, CheckSlaveOnline_Flag, CheckSlaveOnline_index;
void Host_checkSlaveOnline( void )
{
    /* ��ʼ���ӻ�����״̬ */
    if( CheckSlaveOnline_PeriodFlag == 1 )
    {
        CheckSlaveOnline_PeriodFlag = 0;
        readSlaveArr();                     //��flash��ram
        //��մӻ�����״̬��¼
        for( CheckSlaveOnline_index = 0; CheckSlaveOnline_index < 64; CheckSlaveOnline_index++)
        {
            CheckSlaveOnline_recordArr[ CheckSlaveOnline_index ] = 0;
        }
        CheckSlaveOnline_Flag = 10001;
        CheckSlaveOnline_Time = 0;
        CheckSlaveOnline_index = 0;
        //�Դӻ����ͼ������ָ��
        if( CheckSlaveOnline_index < SlaveSize )
        {
            FaSong_HuanCun[0]=SlaveArr[ CheckSlaveOnline_index ].assignArr[0];      //��ֵ��Ÿ��ֽ�
            FaSong_HuanCun[1]=SlaveArr[ CheckSlaveOnline_index ].assignArr[1];      //��ֵ��ŵ��ֽ�
            FaSong_HuanCun[2]=0x0b;

            TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);               
            CheckSlaveOnline_Time = 1;
        }
        else
        {
            //���ص��Լ��ɴӻ�����״̬
            FaSong_HuanCun[ 0 ] = 0x00;//��ַ
            FaSong_HuanCun[ 1 ] = 0x0b;//����֡
            for( CheckSlaveOnline_index = 0; CheckSlaveOnline_index < 64; CheckSlaveOnline_index++)
            {
                FaSong_HuanCun[ CheckSlaveOnline_index + 2 ] = CheckSlaveOnline_recordArr[ CheckSlaveOnline_index ];
            }
			TonXunFaSong(USART_PC,FaSong_HuanCun,0, 2 + 64); 
            //�������ɴӻ�����״̬
            CheckSlaveOnline_Flag = 0;
            CheckSlaveOnline_Time = 0;
            CheckSlaveOnline_index = 0;
            CheckSlaveOnline_PeriodTime = 1;
        }
    }
    /* ���ӻ�����״̬ */
	if(CheckSlaveOnline_Flag>0)
    {
        if( ( CheckSlaveOnline_Time < 500 && CheckSlaveOnline_Flag < 10000 ) || CheckSlaveOnline_Time > 500 )//δ��ʱ���ػ�ʱ������δ��ʱδ���أ�������
        {
            if( CheckSlaveOnline_Time < 500 && CheckSlaveOnline_Flag < 10000 ) //��ȷ���أ�δ��ʱ���أ�
            {
                SlaveArr[ CheckSlaveOnline_index ].state = 1;      //�ӻ�����
                CheckSlaveOnline_recordArr[ CheckSlaveOnline_index / 8 ] |= 1 << ( CheckSlaveOnline_index % 8 );     //�ӻ����߼�¼��־
            }
            else if( CheckSlaveOnline_Time > 500 )//��ʱ
            {
                CheckSlaveOnline_Flag++;
                SlaveArr[ CheckSlaveOnline_index ].state = 0;      //�ӻ�����
            }
            if( SlaveArr[ CheckSlaveOnline_index ].state == 1 || CheckSlaveOnline_Flag > 10003 )//�ӻ����ػ򳬹�����δ���أ������һ���ɴӻ�
            {
                CheckSlaveOnline_Flag = 10001;
                CheckSlaveOnline_index++;
            }
            if( CheckSlaveOnline_index < SlaveSize )
            {
                FaSong_HuanCun[0]=SlaveArr[ CheckSlaveOnline_index ].assignArr[0];      //��ֵ��Ÿ��ֽ�
                FaSong_HuanCun[1]=SlaveArr[ CheckSlaveOnline_index ].assignArr[1];      //��ֵ��ŵ��ֽ�
                FaSong_HuanCun[2]=0x0b;

                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);               
                CheckSlaveOnline_Time = 1;
            }
            else
            {
                //���ص��Լ��ɴӻ�����״̬
                FaSong_HuanCun[ 0 ] = 0x00;//��ַ
                FaSong_HuanCun[ 1 ] = 0x0b;//����֡
                for( CheckSlaveOnline_index = 0; CheckSlaveOnline_index < 64; CheckSlaveOnline_index++)
                {
                    FaSong_HuanCun[ CheckSlaveOnline_index + 2 ] = CheckSlaveOnline_recordArr[ CheckSlaveOnline_index ];
                }
                TonXunFaSong(USART_PC,FaSong_HuanCun,0, 2 + 64); 
                //�������ɴӻ�����״̬
                CheckSlaveOnline_Flag = 0;
                CheckSlaveOnline_Time = 0;
                CheckSlaveOnline_index = 0;
                CheckSlaveOnline_PeriodTime = 1;
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
/*ͨ�ÿ���*/
		case 0x01://��ȡ���дӻ�״̬����ţ����кš����Է���ָ�A5 01 01 80 7E���ӻ��������ݣ�
            readSlaveArr();                     //��flash��ram
			FaSong_HuanCun[ 0 ] = 0x00;//��ַ
			FaSong_HuanCun[ 1 ] = 0x01;//����֡
			FaSong_HuanCun[ 2 ] = SlaveSize / 256;
			FaSong_HuanCun[ 3 ] = SlaveSize % 256;
			TonXunFaSong( USART_PC, FaSong_HuanCun, 0, 4);  //���ؼ�⵽�Ĵӻ���
			for( ZongXunHuan_i = 0; ZongXunHuan_i < SlaveSize; ZongXunHuan_i++ )
			{
				FaSong_HuanCun[ 0 ] = 0x00;
				FaSong_HuanCun[ 1 ] = 0x01;
                FaSong_HuanCun[ 2 ] = SlaveArr[ ZongXunHuan_i ].state;                  //����״̬��1���ߣ�0����
				FaSong_HuanCun[ 3 ] = SlaveArr[ ZongXunHuan_i ].serialArr[0];        //�ӻ����кţ������ֽ�
				FaSong_HuanCun[ 4 ] = SlaveArr[ ZongXunHuan_i ].serialArr[1];
				FaSong_HuanCun[ 5 ] = SlaveArr[ ZongXunHuan_i ].serialArr[2];
				FaSong_HuanCun[ 6 ] = SlaveArr[ ZongXunHuan_i ].serialArr[3];
				FaSong_HuanCun[ 7 ] = SlaveArr[ ZongXunHuan_i ].serialArr[4];
                FaSong_HuanCun[ 8 ] = SlaveArr[ ZongXunHuan_i ].assignArr[0];       //��ֵ��Ÿ��ֽ�
				FaSong_HuanCun[ 9 ] = SlaveArr[ ZongXunHuan_i ].assignArr[1];       //��ֵ��ŵ��ֽ�

				TonXunFaSong(USART_PC,FaSong_HuanCun,0,10); //���ص��ԣ����дӻ�״̬����ţ����к�
			}
            break;
		case 0x02://��λ��Ѱ�ӻ����к� A5 01 02 81 3E                           
            //����������дӻ����
            {
                clearSlaveArr();                                                                //���ram��flash
                FaSong_HuanCun[0]=0xff;                                             
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x07;
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);
                CheckSlaveState_Time = 1;
                while( CheckSlaveState_Time < 500 );
                CheckSlaveState_Time = 0;
            }
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
            break;
		case 0x08://����ӻ����к� A5 01 08 86 BE
            clearSlaveArr();                                                                //���ram��flash
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x07;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);
			FaSong_HuanCun[0]=0x07;
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,1);
            break;
		case 0x09://������дӻ�״̬
            readSlaveArr();                     //��flash��ram
            //����������дӻ����
            {
                FaSong_HuanCun[0]=0xff;                                             
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x07;
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);
                CheckSlaveState_Time = 1;
                while( CheckSlaveState_Time < 500 );
            }
            CheckSlaveState_Flag = 10001;
            CheckSlaveState_Time = 0;
            CheckSlaveState_index = 0;
            //�Դӻ���Ÿ�ֵ
            if( CheckSlaveState_index < SlaveSize )
            {
                FaSong_HuanCun[0]=0xff;
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x02;
                FaSong_HuanCun[3]=SlaveArr[ CheckSlaveState_index ].serialArr[0];
                FaSong_HuanCun[4]=SlaveArr[ CheckSlaveState_index ].serialArr[1];
                FaSong_HuanCun[5]=SlaveArr[ CheckSlaveState_index ].serialArr[2];
                FaSong_HuanCun[6]=SlaveArr[ CheckSlaveState_index ].serialArr[3];
                FaSong_HuanCun[7]=SlaveArr[ CheckSlaveState_index ].serialArr[4];
                FaSong_HuanCun[8]=SlaveArr[ CheckSlaveState_index ].assignArr[0];      //�ӻ���Ŵ�1��ʼ
                FaSong_HuanCun[9]=SlaveArr[ CheckSlaveState_index ].assignArr[1];
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);               
                CheckSlaveState_Time = 1;
            }
            else
            {
                //�������ɴӻ���Ϣ
                CheckSlaveState_Flag = 0;
                CheckSlaveState_Time = 0;
                CheckSlaveState_index = 0;
                //��ʼ��λ��Ѱ�´ӻ���Ϣ        
                AnWeiSouXun_Flag=0;                                                       //���÷��ͱ�־λ
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
                AnWeiSouXun_Time=1;                                                       //ʱ�ӿ�ʼ��ʱ��10msδ�յ����ݺ�������һ�η���
            }
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
/*LEDģ�����*/
		case 0x20://LEDͨ��
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LEDִ��״̬
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x21://LED�ϵ�
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LEDִ��״̬
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x22://LED�����趨
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED����ֵ
            TonXunFaSong(USART2,FaSong_HuanCun,0,6);
            break;
		case 0x23://LED���ν���
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED��ʼ����ֵ
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];//LED����ʱ��
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];//LED��������ֵ
            TonXunFaSong(USART2,FaSong_HuanCun,0,10);
            break;
		case 0x24://LEDѭ������
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED�������ֵ
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];//LED�������ֵ
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];//LED��������
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];
            FaSong_HuanCun[10]=GongNeng_HuanCun[10];//LED��ʼʱ��
            FaSong_HuanCun[11]=GongNeng_HuanCun[11];
            FaSong_HuanCun[12]=GongNeng_HuanCun[12];
            TonXunFaSong(USART2,FaSong_HuanCun,0,13);
            break;
		case 0x25://LEDѭ����˸
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED��ʱ��
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];//LED��ʱ��
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];
            FaSong_HuanCun[10]=GongNeng_HuanCun[10];
            FaSong_HuanCun[11]=GongNeng_HuanCun[11];//LED�������
            FaSong_HuanCun[12]=GongNeng_HuanCun[12];//LED�������
            TonXunFaSong(USART2,FaSong_HuanCun,0,13);
            break;
/*�����ģ�����*/
		case 0x30://�����ͨ��
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCKִ��״̬
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x31://������ϵ�
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCKִ��״̬
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x32://������Ϻ�ͨ
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCKִ��״̬
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//��ʱʱ��
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            TonXunFaSong(USART2,FaSong_HuanCun,0,8);
            break;
		case 0x33://�����ͨ���
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//���H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//���L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//����֡
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//����˿�
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCKִ��״̬
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//��ʱʱ��
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            TonXunFaSong(USART2,FaSong_HuanCun,0,8);
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

    CheckSlaveOnline_bug = GongNeng2_HuanCun[0];
    switch(GongNeng2_HuanCun[0])
	{
		case 1://��λ��Ѱģ�����к�
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x01;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,2);  
		break;
		case 2://�ֻ��Ÿ�ֵ�ɹ�����
            if( AnWeiSouXun_Flag > 0 )//��λ��Ѱ�ӻ�,
            {
                SlaveArr[ SlaveSize ].assignArr[ 0 ] = ( SlaveSize + 1 ) / 256;      //�ӻ���Ŵ�1��ʼ
                SlaveArr[ SlaveSize ].assignArr[ 1 ] = ( SlaveSize + 1) % 256;
                SlaveArr[ SlaveSize ].state = 1;        
				FaSong_HuanCun[0] = 0x00;//��ַ
				FaSong_HuanCun[1] = 0x02;//����֡
                FaSong_HuanCun[2]=SlaveArr[ SlaveSize ].serialArr[ 0 ];//���кŹ����ֽ�
                FaSong_HuanCun[3]=SlaveArr[ SlaveSize ].serialArr[ 1 ];
                FaSong_HuanCun[4]=SlaveArr[ SlaveSize ].serialArr[ 2 ];
                FaSong_HuanCun[5]=SlaveArr[ SlaveSize ].serialArr[ 3 ];
                FaSong_HuanCun[6]=SlaveArr[ SlaveSize ].serialArr[ 4 ];
                FaSong_HuanCun[7]=SlaveArr[ SlaveSize ].assignArr[ 0 ];//���H
                FaSong_HuanCun[8]=SlaveArr[ SlaveSize ].assignArr[ 1 ];//���L
                SlaveSize++;
                TonXunFaSong(USART_PC,FaSong_HuanCun,0,9);//���ص���һ�����к�
            }
            if( CheckSlaveState_Flag > 0 )//������дӻ�״̬
            {
                if ( CheckSlaveState_Flag > 10000 ) //��ȷ����
                {
                    CheckSlaveState_Time = 1;
                    CheckSlaveState_Flag-=10000;
                }
            }
		break;
		case 0x0b://���ӻ�����״̬
            if( CheckSlaveOnline_Flag > 0 )//���ӻ�����״̬
            {
                if ( CheckSlaveOnline_Flag > 10000 ) //��ȷ����
                {
                    CheckSlaveOnline_Time = 1;
                    CheckSlaveOnline_Flag-=10000;
                }
            }
		break;
        case 0x20://LEDͨ�� �����ص���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LEDִ��״̬
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//���ص���һ��ȷ����Ϣ
        break;
        case 0x21://LED�ϵ� �����ص���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LEDִ��״̬
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//���ص���һ��ȷ����Ϣ
        break;
        case 0x22://LED�����趨 �����ص���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED����ֵ
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,7);//���ص���һ��ȷ����Ϣ
        break;
        case 0x23://LED���ν��� �����ص���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED��ʼ����ֵ
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//LED����ʱ��
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];
            FaSong_HuanCun[9]=  GongNeng2_HuanCun[8];
            FaSong_HuanCun[10]=  GongNeng2_HuanCun[9];//LED��������ֵ
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,11);//���ص���һ��ȷ����Ϣ
        break;
        case 0x24://LEDѭ������ �����ص���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED�������ֵ
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//LED�������ֵ
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];//LED��������
            FaSong_HuanCun[9]=  GongNeng2_HuanCun[8];
            FaSong_HuanCun[10]=GongNeng2_HuanCun[9];
            FaSong_HuanCun[11]=GongNeng2_HuanCun[10];//LED��ʼʱ��
            FaSong_HuanCun[12]=GongNeng2_HuanCun[11];
            FaSong_HuanCun[13]=GongNeng2_HuanCun[12];
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,14);//���ص���һ��ȷ����Ϣ
        break;
        case 0x25://LEDѭ����˸ �����ص���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LEDִ��״̬
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED��ʱ��
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];
            FaSong_HuanCun[9]=  GongNeng2_HuanCun[8];//LED��ʱ��
            FaSong_HuanCun[10]=GongNeng2_HuanCun[9];
            FaSong_HuanCun[11]=GongNeng2_HuanCun[10];
            FaSong_HuanCun[12]=GongNeng2_HuanCun[11];//LED�������
            FaSong_HuanCun[13]=GongNeng2_HuanCun[12];//LED�������
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,14);//���ص���һ��ȷ����Ϣ
        break;
		case 0x30://�����ͨ��
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//�������
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//���ص���һ��ȷ����Ϣ
            break;
		case 0x31://������ϵ�
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//�������
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//���ص���һ��ȷ����Ϣ
            break;
		case 0x32://������Ϻ�ͨ
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//�������
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//��ʱʱ��1
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//��ʱʱ��2
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];//��ʱʱ��3
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,9);//���ص���һ��ȷ����Ϣ
            break;
		case 0x33://�����ͨ���
            FaSong_HuanCun[0] = 0x00;//��ַ
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//����֡
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//���H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//���L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//����˿�
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//�������
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//��ʱʱ��1
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//��ʱʱ��2
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];//��ʱʱ��3
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,9);//���ص���һ��ȷ����Ϣ
            break;
	}
	for(ZongXunHuan2_i=0;ZongXunHuan2_i<150;ZongXunHuan2_i++)
	{
		GongNeng2_HuanCun[ZongXunHuan2_i]=0;
	}
}
#endif


