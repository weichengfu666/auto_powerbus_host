#include "bsp.h"
#include "ZongZhiXin.h"

u8 GongNeng_HuanCun[2060],GongNeng2_HuanCun[150];       //[0]:功能号，[1 ~ x]:数据
uint8_t FaSong_HuanCun[2060],FaSong2_HuanCun[150];           
u16 ZhiLin_ChangDu[256],ZongXunHuan_i=0,ZongXunHuan_j=0,ZhiLin2_ChangDu[256],ZongXunHuan2_i=0,ZongXunHuan2_j=0;
u16 AnWeiSouXun_Flag=0, AnWeiSouXun_Time=0,FenJi_Num=0,FenJiHuiYin_Flag=0;
u16 CheckSlaveState_Flag = 0, CheckSlaveState_Time = 0, CheckSlaveState_index = 0;
u16 CheckSlaveOnline_PeriodTime = 0, CheckSlaveOnline_PeriodFlag = 0, CheckSlaveOnline_Time = 0, CheckSlaveOnline_Flag = 0, CheckSlaveOnline_index = 0;
u8 CheckSlaveOnline_recordArr[ 64 ] = {0}, CheckSlaveOnline_bug = 0;
u8 XuLieHao[5]={0x01,0x02,0x03,0x04,0x05};
u8 FenJi_XuLieHao_H1[5]={0x00,0x00,0x00,0x00,0x00},FenJi_XuLieHao[10][5],FenJiHaoFuZhi_HuanCun=0;
//extern uint8_t ChengXu_Data[2048],Flash_ChengXu_Data[2048],Flash_ChengXu_Data2[2048];


/********************** 初始化主机 ***********************/
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
//电脑-主机指令长度初始化
	ZhiLin_ChangDu[0x01-1]=5;//读取已有从机状态，编号，序列号
	ZhiLin_ChangDu[0x02-1]=5;//按位搜寻从机序列号
	ZhiLin_ChangDu[0x03-1]=9;//设备控制
	ZhiLin_ChangDu[0x04-1]=7;//触发控制
	ZhiLin_ChangDu[0x05-1]=7;//联动效果执行
	ZhiLin_ChangDu[0x06-1]=9;//音效控制
	ZhiLin_ChangDu[0x07-1]=2056;//程序接收
	ZhiLin_ChangDu[0x08-1]=5;//清除从机序列号
	ZhiLin_ChangDu[0x09-1]=5;//检测所有从机状态
	ZhiLin_ChangDu[0xff-1]=5;//查询主机序列号
    
    ZhiLin_ChangDu[0x20-1]=9;//LED通电
    ZhiLin_ChangDu[0x21-1]=9;//LED断电
    ZhiLin_ChangDu[0x22-1]=10;//LED亮度设定
    ZhiLin_ChangDu[0x23-1]=14;//LED单次渐变
    ZhiLin_ChangDu[0x24-1]=17;//LED循环呼吸
    ZhiLin_ChangDu[0x25-1]=17;//LED循环闪烁
    
    ZhiLin_ChangDu[0x30-1]=9;//LOCK通电
    ZhiLin_ChangDu[0x31-1]=9;//LOCK断电
    ZhiLin_ChangDu[0x32-1]=12;//LOCK断后通
    ZhiLin_ChangDu[0x33-1]=12;//LOCK通后断
//主机-从机指令长度初始化
	ZhiLin2_ChangDu[0]=4;//指令长度初始化
	ZhiLin2_ChangDu[1]=11;//指令长度初始化
	ZhiLin2_ChangDu[0x0b-1]=6;//指令长度初始化
    
    ZhiLin2_ChangDu[0x20-1]=8;//LED通电
    ZhiLin2_ChangDu[0x21-1]=8;//LED断电
    ZhiLin2_ChangDu[0x22-1]=9;//LED亮度设定
    ZhiLin2_ChangDu[0x23-1]=13;//LED单次渐变
    ZhiLin2_ChangDu[0x24-1]=16;//LED循环呼吸
    ZhiLin2_ChangDu[0x25-1]=16;//LED循环闪烁
    
    ZhiLin2_ChangDu[0x30-1]=8;//LOCK通电
    ZhiLin2_ChangDu[0x31-1]=8;//LOCK断电
    ZhiLin2_ChangDu[0x32-1]=11;//LOCK断后通
    ZhiLin2_ChangDu[0x33-1]=11;//LOCK通后断
}
#endif
/************************ 总循环 *************************/
#if 1
void ZongXunHuan(void)
{
    Host_querySerialNum();  //主机搜索序列号
    Host_checkSlaveState();//主机检测从机状态
    Host_checkSlaveOnline();//周期检测从机在线状态
    Host_reponsePC();       //主机应答PC
    Host_responseSlave();   //主机应答从机
}
#endif
/*
*********************************************************************************************************
*	函 数 名: Host_querySerialNum
*	功能说明: 主机搜索序列号
*********************************************************************************************************
*/
#if 1
void Host_querySerialNum(void)
{
    /* 从机序列号检测模式 */
	if(AnWeiSouXun_Flag>0)
	{
		if(((AnWeiSouXun_Time>10)&&(AnWeiSouXun_Flag!=41))||((AnWeiSouXun_Time>20)&&(AnWeiSouXun_Flag==41)))    //10ms未收到数据进入下一次发送模式,赋值编号是需要大于20ms（因为主机发送数据到从机接收并解析返回数据给主机并接收到的这段时间是10ms以内，赋值需要20ms让从机收到并处理数据）
		{
			if(AnWeiSouXun_Flag>10000)                                      //大于10000表示等待期间未收到过返回数据
			{
				AnWeiSouXun_Flag-=10000;
				FenJi_XuLieHao_H1[(AnWeiSouXun_Flag-1)/8]^=(0x80>>((AnWeiSouXun_Flag-1)%8));                    //计算即将发送的FenJi_XuLieHao_H1,将上一次发送的位置为0
			}
            //序列号检索进行中，需要发送40次才完成一次检索
			if((AnWeiSouXun_Flag%10000)<40) 
			{
				FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));//将下一位置为1
				FaSong_HuanCun[0]=0xff;
				FaSong_HuanCun[1]=0xff;
				FaSong_HuanCun[2]=0x01;
				FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
				FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
				FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
				FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
				FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
				AnWeiSouXun_Flag+=10001;                                    //推进一位并进入未收到分机返回模式
				TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,8);                    //对分机发送数据
				AnWeiSouXun_Time=1;                                         //时钟开始计时，10ms未收到数据后启动下一次发送
			}
            else if((AnWeiSouXun_Flag%10000)==40)   //完成一次序列号检索
            {	
                //统计未收到回应的检索次数（序列号全零为未收到回应）
				if((FenJi_XuLieHao_H1[0]==0x00)&&(FenJi_XuLieHao_H1[1]==0x00)&&(FenJi_XuLieHao_H1[2]==0x00)&&(FenJi_XuLieHao_H1[3]==0x00)&&(FenJi_XuLieHao_H1[4]==0x00)) 
				{
					FenJiHuiYin_Flag++;
				}else
                {
					FenJiHuiYin_Flag=0;
				}
                //未收到回应的检索次数小于3次，对从机赋值，继续检索
				if(FenJiHuiYin_Flag<=3)  
				{
					SlaveArr[ SlaveSize ].serialArr[0] = ~FenJi_XuLieHao_H1[0];     //将得到的缓存取反存入序列号
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
					FaSong_HuanCun[8]= ( SlaveSize + 1 ) / 256;      //从机编号从1开始
					FaSong_HuanCun[9]= ( SlaveSize + 1 ) % 256;
					TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);               //对从机编号赋值
					AnWeiSouXun_Flag=41;                                    //进入赋值后等待回应模式
					AnWeiSouXun_Time=1;                                     //时钟开始计时，10ms未收到返回则认为没有此从机
				}
                else //检索未回应的次数超过3次，结束检索
                {
                    wirteSlaveArr();    //写ram到flash
                    //返回检测到的从机数
                    {
                        FaSong_HuanCun[ 0 ] = 0x00;//地址
                        FaSong_HuanCun[ 1 ] = 0x09;//功能帧
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
					AnWeiSouXun_Flag=0;                                     //重置发送标志位
					AnWeiSouXun_Time=0;
					FenJiHuiYin_Flag=0;                                     
					FenJi_XuLieHao_H1[0]=0;
					FenJi_XuLieHao_H1[1]=0;
					FenJi_XuLieHao_H1[2]=0;
					FenJi_XuLieHao_H1[3]=0;
					FenJi_XuLieHao_H1[4]=0;
				}
			}
            else    //进入下一次检索
            {
				FaSong_HuanCun[0]=0;
				FaSong_HuanCun[1]=0;
				FaSong_HuanCun[2]=0;
				FaSong_HuanCun[3]=0;
				FaSong_HuanCun[4]=0;
				FaSong_HuanCun[5]=0;
				FaSong_HuanCun[6]=0;
				FaSong_HuanCun[7]=0;
				AnWeiSouXun_Flag=0;                                         //重置发送标志位
				FenJi_XuLieHao_H1[0]=0;
				FenJi_XuLieHao_H1[1]=0;
				FenJi_XuLieHao_H1[2]=0;
				FenJi_XuLieHao_H1[3]=0;
				FenJi_XuLieHao_H1[4]=0;
				FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));                                //计算即将发送的FenJi_XuLieHao_H1
				FaSong_HuanCun[0]=0xff;
				FaSong_HuanCun[1]=0xff;
				FaSong_HuanCun[2]=0x01;
				FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
				FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
				FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
				FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
				FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
				AnWeiSouXun_Flag=10001;                                     //大于10000为未收到分机返回模式,推进一位并进入未收到分机返回模式
				AnWeiSouXun_Time=1;                                         //时钟开始计时，10ms未收到数据后启动下一次发送
				TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,8);                    //对分机发送数据
			}
		}
	}
}
/*
*********************************************************************************************************
*	函 数 名: Host_checkSlaveState
*	功能说明: 检测所有从机状态
*********************************************************************************************************
*/
void Host_checkSlaveState( void )
{
    //主机检测所有从机状态
    if( CheckSlaveState_Flag > 0 )
    {
        if( ( CheckSlaveState_Time < 200 && CheckSlaveState_Flag < 10000 ) || CheckSlaveState_Time > 200 )//未超时返回或超时：处理；未超时未返回：不处理；
        {
            if( CheckSlaveState_Time < 200 && CheckSlaveState_Flag < 10000 ) //正确返回（未超时返回）
            {
                SlaveArr[ CheckSlaveState_index ].state = 1;      //从机在线
                //返回电脑检测到的旧从机信息（只返回在线从机）
                FaSong_HuanCun[ 0 ] = 0x00;
                FaSong_HuanCun[ 1 ] = 0x02;
                FaSong_HuanCun[ 2 ] = SlaveArr[ CheckSlaveState_index ].serialArr[0];        //从机序列号：共五字节
                FaSong_HuanCun[ 3 ] = SlaveArr[ CheckSlaveState_index ].serialArr[1];
                FaSong_HuanCun[ 4 ] = SlaveArr[ CheckSlaveState_index ].serialArr[2];
                FaSong_HuanCun[ 5 ] = SlaveArr[ CheckSlaveState_index ].serialArr[3];
                FaSong_HuanCun[ 6 ] = SlaveArr[ CheckSlaveState_index ].serialArr[4];
                FaSong_HuanCun[ 7 ] = SlaveArr[ CheckSlaveState_index ].assignArr[0];       //赋值编号高字节
                FaSong_HuanCun[ 8 ] = SlaveArr[ CheckSlaveState_index ].assignArr[1];       //赋值编号低字节

                TonXunFaSong(USART_PC,FaSong_HuanCun,0,9); //返回电脑：已有从机状态，编号，序列号
            }
            else if( CheckSlaveState_Time > 200 )//超时
            {
                CheckSlaveState_Flag++;
                SlaveArr[ CheckSlaveState_index ].state = 0;      //从机离线
            }
            if( SlaveArr[ CheckSlaveState_index ].state == 1 || CheckSlaveState_Flag >= 10003 )//从机返回或超过三次未返回，检测下一个旧从机
            {
                CheckSlaveState_Flag = 10001;
                CheckSlaveState_index++;
            }
            if( CheckSlaveState_index < SlaveSize )
            {
                //1、对旧从机编号赋值
                FaSong_HuanCun[0]=0xff;
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x02;
                FaSong_HuanCun[3]=SlaveArr[ CheckSlaveState_index ].serialArr[0];
                FaSong_HuanCun[4]=SlaveArr[ CheckSlaveState_index ].serialArr[1];
                FaSong_HuanCun[5]=SlaveArr[ CheckSlaveState_index ].serialArr[2];
                FaSong_HuanCun[6]=SlaveArr[ CheckSlaveState_index ].serialArr[3];
                FaSong_HuanCun[7]=SlaveArr[ CheckSlaveState_index ].serialArr[4];
                FaSong_HuanCun[8]=SlaveArr[ CheckSlaveState_index ].assignArr[0];      //从机编号从1开始
                FaSong_HuanCun[9]=SlaveArr[ CheckSlaveState_index ].assignArr[1];
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);             //对从机编号赋值              
                CheckSlaveState_Time = 1;
            }
            else
            {
                //结束检测旧从机信息
                CheckSlaveState_Flag = 0;
                CheckSlaveState_Time = 0;
                CheckSlaveState_index = 0;
                //2、开始按位搜寻新从机信息        
                AnWeiSouXun_Flag=0;                                                       //重置发送标志位
                FenJi_XuLieHao_H1[0]=0;
                FenJi_XuLieHao_H1[1]=0;
                FenJi_XuLieHao_H1[2]=0;
                FenJi_XuLieHao_H1[3]=0;
                FenJi_XuLieHao_H1[4]=0;
                FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));    //计算即将发送的FenJi_XuLieHao_H1
                FaSong_HuanCun[0]=0xff;
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x01;
                FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
                FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
                FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
                FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
                FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
                AnWeiSouXun_Flag=10001;                                                 //大于10000为未收到分机返回模式,推进一位并进入未收到分机返回模式
                AnWeiSouXun_Time=1;                                                       //时钟开始计时，10ms未收到数据后启动下一次发送
            }
        }
    }
}
/*
*********************************************************************************************************
*	函 数 名: Host_checkSlaveOnline
*	功能说明: 检测从机在线状态
*********************************************************************************************************
*/

//CheckSlaveOnline_Time, CheckSlaveOnline_Flag, CheckSlaveOnline_index;
void Host_checkSlaveOnline( void )
{
    /* 开始检测从机在线状态 */
    if( CheckSlaveOnline_PeriodFlag == 1 )
    {
        CheckSlaveOnline_PeriodFlag = 0;
        readSlaveArr();                     //读flash到ram
        //清空从机在线状态记录
        for( CheckSlaveOnline_index = 0; CheckSlaveOnline_index < 64; CheckSlaveOnline_index++)
        {
            CheckSlaveOnline_recordArr[ CheckSlaveOnline_index ] = 0;
        }
        CheckSlaveOnline_Flag = 10001;
        CheckSlaveOnline_Time = 0;
        CheckSlaveOnline_index = 0;
        //对从机发送检测在线指令
        if( CheckSlaveOnline_index < SlaveSize )
        {
            FaSong_HuanCun[0]=SlaveArr[ CheckSlaveOnline_index ].assignArr[0];      //赋值编号高字节
            FaSong_HuanCun[1]=SlaveArr[ CheckSlaveOnline_index ].assignArr[1];      //赋值编号低字节
            FaSong_HuanCun[2]=0x0b;

            TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);               
            CheckSlaveOnline_Time = 1;
        }
        else
        {
            //返回电脑检测旧从机在线状态
            FaSong_HuanCun[ 0 ] = 0x00;//地址
            FaSong_HuanCun[ 1 ] = 0x0b;//功能帧
            for( CheckSlaveOnline_index = 0; CheckSlaveOnline_index < 64; CheckSlaveOnline_index++)
            {
                FaSong_HuanCun[ CheckSlaveOnline_index + 2 ] = CheckSlaveOnline_recordArr[ CheckSlaveOnline_index ];
            }
			TonXunFaSong(USART_PC,FaSong_HuanCun,0, 2 + 64); 
            //结束检测旧从机在线状态
            CheckSlaveOnline_Flag = 0;
            CheckSlaveOnline_Time = 0;
            CheckSlaveOnline_index = 0;
            CheckSlaveOnline_PeriodTime = 1;
        }
    }
    /* 检测从机在线状态 */
	if(CheckSlaveOnline_Flag>0)
    {
        if( ( CheckSlaveOnline_Time < 500 && CheckSlaveOnline_Flag < 10000 ) || CheckSlaveOnline_Time > 500 )//未超时返回或超时：处理；未超时未返回：不处理；
        {
            if( CheckSlaveOnline_Time < 500 && CheckSlaveOnline_Flag < 10000 ) //正确返回（未超时返回）
            {
                SlaveArr[ CheckSlaveOnline_index ].state = 1;      //从机在线
                CheckSlaveOnline_recordArr[ CheckSlaveOnline_index / 8 ] |= 1 << ( CheckSlaveOnline_index % 8 );     //从机在线记录标志
            }
            else if( CheckSlaveOnline_Time > 500 )//超时
            {
                CheckSlaveOnline_Flag++;
                SlaveArr[ CheckSlaveOnline_index ].state = 0;      //从机离线
            }
            if( SlaveArr[ CheckSlaveOnline_index ].state == 1 || CheckSlaveOnline_Flag > 10003 )//从机返回或超过三次未返回，检测下一个旧从机
            {
                CheckSlaveOnline_Flag = 10001;
                CheckSlaveOnline_index++;
            }
            if( CheckSlaveOnline_index < SlaveSize )
            {
                FaSong_HuanCun[0]=SlaveArr[ CheckSlaveOnline_index ].assignArr[0];      //赋值编号高字节
                FaSong_HuanCun[1]=SlaveArr[ CheckSlaveOnline_index ].assignArr[1];      //赋值编号低字节
                FaSong_HuanCun[2]=0x0b;

                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);               
                CheckSlaveOnline_Time = 1;
            }
            else
            {
                //返回电脑检测旧从机在线状态
                FaSong_HuanCun[ 0 ] = 0x00;//地址
                FaSong_HuanCun[ 1 ] = 0x0b;//功能帧
                for( CheckSlaveOnline_index = 0; CheckSlaveOnline_index < 64; CheckSlaveOnline_index++)
                {
                    FaSong_HuanCun[ CheckSlaveOnline_index + 2 ] = CheckSlaveOnline_recordArr[ CheckSlaveOnline_index ];
                }
                TonXunFaSong(USART_PC,FaSong_HuanCun,0, 2 + 64); 
                //结束检测旧从机在线状态
                CheckSlaveOnline_Flag = 0;
                CheckSlaveOnline_Time = 0;
                CheckSlaveOnline_index = 0;
                CheckSlaveOnline_PeriodTime = 1;
            }
        }
    }
}
    

#endif
/********************** 主机应答PC ***********************/
#if 1
void Host_reponsePC( void )
{
	switch( GongNeng_HuanCun[ 0 ] )
	{
/*通用控制*/
		case 0x01://读取已有从机状态，编号，序列号。电脑发送指令：A5 01 01 80 7E。从机返回数据：
            readSlaveArr();                     //读flash到ram
			FaSong_HuanCun[ 0 ] = 0x00;//地址
			FaSong_HuanCun[ 1 ] = 0x01;//功能帧
			FaSong_HuanCun[ 2 ] = SlaveSize / 256;
			FaSong_HuanCun[ 3 ] = SlaveSize % 256;
			TonXunFaSong( USART_PC, FaSong_HuanCun, 0, 4);  //返回检测到的从机数
			for( ZongXunHuan_i = 0; ZongXunHuan_i < SlaveSize; ZongXunHuan_i++ )
			{
				FaSong_HuanCun[ 0 ] = 0x00;
				FaSong_HuanCun[ 1 ] = 0x01;
                FaSong_HuanCun[ 2 ] = SlaveArr[ ZongXunHuan_i ].state;                  //在线状态：1在线，0离线
				FaSong_HuanCun[ 3 ] = SlaveArr[ ZongXunHuan_i ].serialArr[0];        //从机序列号：共五字节
				FaSong_HuanCun[ 4 ] = SlaveArr[ ZongXunHuan_i ].serialArr[1];
				FaSong_HuanCun[ 5 ] = SlaveArr[ ZongXunHuan_i ].serialArr[2];
				FaSong_HuanCun[ 6 ] = SlaveArr[ ZongXunHuan_i ].serialArr[3];
				FaSong_HuanCun[ 7 ] = SlaveArr[ ZongXunHuan_i ].serialArr[4];
                FaSong_HuanCun[ 8 ] = SlaveArr[ ZongXunHuan_i ].assignArr[0];       //赋值编号高字节
				FaSong_HuanCun[ 9 ] = SlaveArr[ ZongXunHuan_i ].assignArr[1];       //赋值编号低字节

				TonXunFaSong(USART_PC,FaSong_HuanCun,0,10); //返回电脑：已有从机状态，编号，序列号
			}
            break;
		case 0x02://按位搜寻从机序列号 A5 01 02 81 3E                           
            //主机清除所有从机编号
            {
                clearSlaveArr();                                                                //清空ram和flash
                FaSong_HuanCun[0]=0xff;                                             
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x07;
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);
                CheckSlaveState_Time = 1;
                while( CheckSlaveState_Time < 500 );
                CheckSlaveState_Time = 0;
            }
			AnWeiSouXun_Flag=0;                                                     //重置发送标志位
			FenJi_XuLieHao_H1[0]=0;
			FenJi_XuLieHao_H1[1]=0;
			FenJi_XuLieHao_H1[2]=0;
			FenJi_XuLieHao_H1[3]=0;
			FenJi_XuLieHao_H1[4]=0;
			FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));    //计算即将发送的FenJi_XuLieHao_H1
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x01;
			FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
			FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
			FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
			FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
			FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
			AnWeiSouXun_Flag=10001;                                                 //大于10000为未收到分机返回模式,推进一位并进入未收到分机返回模式
			AnWeiSouXun_Time=1;                                                     //时钟开始计时，10ms未收到数据后启动下一次发送
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,8);                                //对分机发送数据
            break;
		case 0x03://设备控制
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
		case 0x04://触发控制
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x04;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,4); 
            break;
		case 0x05://联动效果执行 A5 01 05 00 01 01 A0
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x06;
			FaSong_HuanCun[3]=GongNeng_HuanCun[1];
			FaSong_HuanCun[4]=GongNeng_HuanCun[2];
            TonXunFaSong(USART2,FaSong_HuanCun,0,5); //发给从机
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x05;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,4); 
            break;
		case 0x06://音效控制
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x06;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
			FaSong_HuanCun[5]=GongNeng_HuanCun[4];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,4); 
            break;
		case 0x07://程序接收 
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x07;
			FaSong_HuanCun[2]=GongNeng_HuanCun[1];
			FaSong_HuanCun[3]=GongNeng_HuanCun[2];
			FaSong_HuanCun[4]=GongNeng_HuanCun[3];
            break;
		case 0x08://清除从机序列号 A5 01 08 86 BE
            clearSlaveArr();                                                                //清空ram和flash
			FaSong_HuanCun[0]=0xff;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=0x07;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,3);
			FaSong_HuanCun[0]=0x07;
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,1);
            break;
		case 0x09://检测所有从机状态
            readSlaveArr();                     //读flash到ram
            //主机清除所有从机编号
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
            //对从机编号赋值
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
                FaSong_HuanCun[8]=SlaveArr[ CheckSlaveState_index ].assignArr[0];      //从机编号从1开始
                FaSong_HuanCun[9]=SlaveArr[ CheckSlaveState_index ].assignArr[1];
                TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,10);               
                CheckSlaveState_Time = 1;
            }
            else
            {
                //结束检测旧从机信息
                CheckSlaveState_Flag = 0;
                CheckSlaveState_Time = 0;
                CheckSlaveState_index = 0;
                //开始按位搜寻新从机信息        
                AnWeiSouXun_Flag=0;                                                       //重置发送标志位
                FenJi_XuLieHao_H1[0]=0;
                FenJi_XuLieHao_H1[1]=0;
                FenJi_XuLieHao_H1[2]=0;
                FenJi_XuLieHao_H1[3]=0;
                FenJi_XuLieHao_H1[4]=0;
                FenJi_XuLieHao_H1[AnWeiSouXun_Flag/8]|=(0x80>>(AnWeiSouXun_Flag%8));    //计算即将发送的FenJi_XuLieHao_H1
                FaSong_HuanCun[0]=0xff;
                FaSong_HuanCun[1]=0xff;
                FaSong_HuanCun[2]=0x01;
                FaSong_HuanCun[3]=FenJi_XuLieHao_H1[0];
                FaSong_HuanCun[4]=FenJi_XuLieHao_H1[1];
                FaSong_HuanCun[5]=FenJi_XuLieHao_H1[2];
                FaSong_HuanCun[6]=FenJi_XuLieHao_H1[3];
                FaSong_HuanCun[7]=FenJi_XuLieHao_H1[4];
                AnWeiSouXun_Flag=10001;                                                 //大于10000为未收到分机返回模式,推进一位并进入未收到分机返回模式
                AnWeiSouXun_Time=1;                                                       //时钟开始计时，10ms未收到数据后启动下一次发送
            }
            break;
		case 0xff://查询主机序列号 A5 01 FF 00 FF
			FaSong_HuanCun[0]=0;
			FaSong_HuanCun[1]=0xff;
			FaSong_HuanCun[2]=XuLieHao[0];
			FaSong_HuanCun[3]=XuLieHao[1];
			FaSong_HuanCun[4]=XuLieHao[2];
			FaSong_HuanCun[5]=XuLieHao[3];
			FaSong_HuanCun[6]=XuLieHao[4];
			TonXunFaSong(USART_PC,FaSong_HuanCun,0,7); 
            break;
/*LED模块控制*/
		case 0x20://LED通电
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LED执行状态
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x21://LED断电
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LED执行状态
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x22://LED亮度设定
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LED执行状态
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED亮度值
            TonXunFaSong(USART2,FaSong_HuanCun,0,6);
            break;
		case 0x23://LED单次渐变
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LED执行状态
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED初始亮度值
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];//LED渐变时间
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];//LED结束亮度值
            TonXunFaSong(USART2,FaSong_HuanCun,0,10);
            break;
		case 0x24://LED循环呼吸
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LED执行状态
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED最高亮度值
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];//LED最低亮度值
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];//LED呼吸周期
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];
            FaSong_HuanCun[10]=GongNeng_HuanCun[10];//LED起始时间
            FaSong_HuanCun[11]=GongNeng_HuanCun[11];
            FaSong_HuanCun[12]=GongNeng_HuanCun[12];
            TonXunFaSong(USART2,FaSong_HuanCun,0,13);
            break;
		case 0x25://LED循环闪烁
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LED执行状态
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//LED亮时间
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            FaSong_HuanCun[8]=GongNeng_HuanCun[8];//LED灭时间
            FaSong_HuanCun[9]=GongNeng_HuanCun[9];
            FaSong_HuanCun[10]=GongNeng_HuanCun[10];
            FaSong_HuanCun[11]=GongNeng_HuanCun[11];//LED最高亮度
            FaSong_HuanCun[12]=GongNeng_HuanCun[12];//LED最低亮度
            TonXunFaSong(USART2,FaSong_HuanCun,0,13);
            break;
/*电磁锁模块控制*/
		case 0x30://电磁锁通电
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCK执行状态
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x31://电磁锁断电
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCK执行状态
            TonXunFaSong(USART2,FaSong_HuanCun,0,5);
            break;
		case 0x32://电磁锁断后通
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCK执行状态
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//延时时间
            FaSong_HuanCun[6]=GongNeng_HuanCun[6];
            FaSong_HuanCun[7]=GongNeng_HuanCun[7];
            TonXunFaSong(USART2,FaSong_HuanCun,0,8);
            break;
		case 0x33://电磁锁通后断
            FaSong_HuanCun[0]=GongNeng_HuanCun[1];//编号H
			FaSong_HuanCun[1]=GongNeng_HuanCun[2];//编号L
            FaSong_HuanCun[2]=GongNeng_HuanCun[0];//功能帧
            FaSong_HuanCun[3]=GongNeng_HuanCun[3];//输出端口
            FaSong_HuanCun[4]=GongNeng_HuanCun[4];//LOCK执行状态
            FaSong_HuanCun[5]=GongNeng_HuanCun[5];//延时时间
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
*	函 数 名: Host_responseSlave
*	功能说明: 主机应答从机
*********************************************************************************************************
*/
#if 1
void Host_responseSlave(void)
{

    CheckSlaveOnline_bug = GongNeng2_HuanCun[0];
    switch(GongNeng2_HuanCun[0])
	{
		case 1://按位搜寻模块序列号
			FaSong_HuanCun[0]=0x00;
			FaSong_HuanCun[1]=0x01;
			TonXunFaSong(USART_SLAVE,FaSong_HuanCun,0,2);  
		break;
		case 2://分机号赋值成功返回
            if( AnWeiSouXun_Flag > 0 )//按位搜寻从机,
            {
                SlaveArr[ SlaveSize ].assignArr[ 0 ] = ( SlaveSize + 1 ) / 256;      //从机编号从1开始
                SlaveArr[ SlaveSize ].assignArr[ 1 ] = ( SlaveSize + 1) % 256;
                SlaveArr[ SlaveSize ].state = 1;        
				FaSong_HuanCun[0] = 0x00;//地址
				FaSong_HuanCun[1] = 0x02;//功能帧
                FaSong_HuanCun[2]=SlaveArr[ SlaveSize ].serialArr[ 0 ];//序列号共五字节
                FaSong_HuanCun[3]=SlaveArr[ SlaveSize ].serialArr[ 1 ];
                FaSong_HuanCun[4]=SlaveArr[ SlaveSize ].serialArr[ 2 ];
                FaSong_HuanCun[5]=SlaveArr[ SlaveSize ].serialArr[ 3 ];
                FaSong_HuanCun[6]=SlaveArr[ SlaveSize ].serialArr[ 4 ];
                FaSong_HuanCun[7]=SlaveArr[ SlaveSize ].assignArr[ 0 ];//编号H
                FaSong_HuanCun[8]=SlaveArr[ SlaveSize ].assignArr[ 1 ];//编号L
                SlaveSize++;
                TonXunFaSong(USART_PC,FaSong_HuanCun,0,9);//返回电脑一条序列号
            }
            if( CheckSlaveState_Flag > 0 )//检测所有从机状态
            {
                if ( CheckSlaveState_Flag > 10000 ) //正确返回
                {
                    CheckSlaveState_Time = 1;
                    CheckSlaveState_Flag-=10000;
                }
            }
		break;
		case 0x0b://检测从机在线状态
            if( CheckSlaveOnline_Flag > 0 )//检测从机在线状态
            {
                if ( CheckSlaveOnline_Flag > 10000 ) //正确返回
                {
                    CheckSlaveOnline_Time = 1;
                    CheckSlaveOnline_Flag-=10000;
                }
            }
		break;
        case 0x20://LED通电 ，返回电脑
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LED执行状态
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//返回电脑一条确认信息
        break;
        case 0x21://LED断电 ，返回电脑
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LED执行状态
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//返回电脑一条确认信息
        break;
        case 0x22://LED亮度设定 ，返回电脑
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LED执行状态
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED亮度值
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,7);//返回电脑一条确认信息
        break;
        case 0x23://LED单次渐变 ，返回电脑
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LED执行状态
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED初始亮度值
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//LED渐变时间
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];
            FaSong_HuanCun[9]=  GongNeng2_HuanCun[8];
            FaSong_HuanCun[10]=  GongNeng2_HuanCun[9];//LED结束亮度值
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,11);//返回电脑一条确认信息
        break;
        case 0x24://LED循环呼吸 ，返回电脑
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LED执行状态
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED最高亮度值
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//LED最低亮度值
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];//LED呼吸周期
            FaSong_HuanCun[9]=  GongNeng2_HuanCun[8];
            FaSong_HuanCun[10]=GongNeng2_HuanCun[9];
            FaSong_HuanCun[11]=GongNeng2_HuanCun[10];//LED起始时间
            FaSong_HuanCun[12]=GongNeng2_HuanCun[11];
            FaSong_HuanCun[13]=GongNeng2_HuanCun[12];
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,14);//返回电脑一条确认信息
        break;
        case 0x25://LED循环闪烁 ，返回电脑
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//LED执行状态
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//LED亮时间
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];
            FaSong_HuanCun[9]=  GongNeng2_HuanCun[8];//LED灭时间
            FaSong_HuanCun[10]=GongNeng2_HuanCun[9];
            FaSong_HuanCun[11]=GongNeng2_HuanCun[10];
            FaSong_HuanCun[12]=GongNeng2_HuanCun[11];//LED最高亮度
            FaSong_HuanCun[13]=GongNeng2_HuanCun[12];//LED最低亮度
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,14);//返回电脑一条确认信息
        break;
		case 0x30://电磁锁通电
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//输出类型
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//返回电脑一条确认信息
            break;
		case 0x31://电磁锁断电
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//输出类型
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,6);//返回电脑一条确认信息
            break;
		case 0x32://电磁锁断后通
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//输出类型
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//延时时间1
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//延时时间2
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];//延时时间3
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,9);//返回电脑一条确认信息
            break;
		case 0x33://电磁锁通后断
            FaSong_HuanCun[0] = 0x00;//地址
            FaSong_HuanCun[1] = GongNeng2_HuanCun[0];//功能帧
            FaSong_HuanCun[2]=  GongNeng2_HuanCun[1];//编号H
            FaSong_HuanCun[3]=  GongNeng2_HuanCun[2];//编号L  
            FaSong_HuanCun[4]=  GongNeng2_HuanCun[3];//输出端口
            FaSong_HuanCun[5]=  GongNeng2_HuanCun[4];//输出类型
            FaSong_HuanCun[6]=  GongNeng2_HuanCun[5];//延时时间1
            FaSong_HuanCun[7]=  GongNeng2_HuanCun[6];//延时时间2
            FaSong_HuanCun[8]=  GongNeng2_HuanCun[7];//延时时间3
            TonXunFaSong(USART_PC,FaSong_HuanCun,0,9);//返回电脑一条确认信息
            break;
	}
	for(ZongXunHuan2_i=0;ZongXunHuan2_i<150;ZongXunHuan2_i++)
	{
		GongNeng2_HuanCun[ZongXunHuan2_i]=0;
	}
}
#endif


