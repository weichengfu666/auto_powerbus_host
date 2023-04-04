#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
/********************** 16λCRCУ�� ***********************/
#if 1
u16 crc16(unsigned char *ptr,unsigned int len) 
{ 
    u16 CRC_wcrc=0XFFFF;	                    //Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1 
    u8 CRC_temp;					            //�����м���� 
    int CRC_i=0,CRC_j=0;			            //������� 
    
	for(CRC_i=0;CRC_i<len;CRC_i++)			    //ѭ������ÿ������ 
	{ 
		CRC_temp=*ptr&0X00FF;				    //����λ������crc�Ĵ������ 
		ptr++;								    //ָ���ַ���ӣ�ָ���¸����� 
		CRC_wcrc^=CRC_temp;					    //�����ݴ���crc�Ĵ��� 
		for(CRC_j=0;CRC_j<8;CRC_j++)		        //ѭ���������ݵ� 
		{ 
			if(CRC_wcrc&0X0001)			        //�ж����Ƴ����ǲ���1�������1�������ʽ������� 
			{ 
				CRC_wcrc>>=1;					//�Ƚ���������һλ 
				CRC_wcrc^=0XA001;				//������Ķ���ʽ������� 
			}else{								//�������1����ֱ���Ƴ� 
			 	CRC_wcrc>>=1;					//ֱ���Ƴ� 
			} 
		} 
	} 
    return CRC_wcrc;
}		
#endif
