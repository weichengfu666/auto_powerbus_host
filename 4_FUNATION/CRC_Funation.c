#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
/********************** 16位CRC校验 ***********************/
#if 1
u16 crc16(unsigned char *ptr,unsigned int len) 
{ 
    u16 CRC_wcrc=0XFFFF;	                    //预置16位crc寄存器，初值全部为1 
    u8 CRC_temp;					            //定义中间变量 
    int CRC_i=0,CRC_j=0;			            //定义计数 
    
	for(CRC_i=0;CRC_i<len;CRC_i++)			    //循环计算每个数据 
	{ 
		CRC_temp=*ptr&0X00FF;				    //将八位数据与crc寄存器亦或 
		ptr++;								    //指针地址增加，指向下个数据 
		CRC_wcrc^=CRC_temp;					    //将数据存入crc寄存器 
		for(CRC_j=0;CRC_j<8;CRC_j++)		        //循环计算数据的 
		{ 
			if(CRC_wcrc&0X0001)			        //判断右移出的是不是1，如果是1则与多项式进行异或。 
			{ 
				CRC_wcrc>>=1;					//先将数据右移一位 
				CRC_wcrc^=0XA001;				//与上面的多项式进行异或 
			}else{								//如果不是1，则直接移出 
			 	CRC_wcrc>>=1;					//直接移出 
			} 
		} 
	} 
    return CRC_wcrc;
}		
#endif
