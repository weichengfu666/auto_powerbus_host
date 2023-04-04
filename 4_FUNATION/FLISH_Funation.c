#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

uint32_t EraseCounter=0x00,Address=0x00; 							//擦除计数，写入地址
uint32_t NbrOfPage = 0x00;														//记录要擦除的页数
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;		//擦除完成标志
const uint8_t ChengXu_Data[6144] __attribute__((at(0X08010000)));
uint8_t Flash_ChengXu_Data[2048],Flash_ChengXu_Data2[2048];

u32 WRITE_START_ADDR2,Flash_Write_Str_i=0;
u8 Flash_Write_Data2[2048];
u16 Flash_Write_Str_j=0;
/*******************************************************************************************************************
flash单页写入函数
WRITE_START_ADDR 写入起始地址
Flash_Data_Write写入数据
********************************************************************************************************************/
void Flash_Write_2K(uint32_t WRITE_START_ADDR)	 		 		
{
	uint16_t Flash_i=0;
	uint16_t HalfWord=0;
	__set_PRIMASK(1);
	FLASH_Unlock();																														//解锁flash
  FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(WRITE_START_ADDR);																				//擦除flash
	for(Flash_i=0;Flash_i<1024;Flash_i++)
	{
		HalfWord=Flash_ChengXu_Data[Flash_i*2]+Flash_ChengXu_Data[Flash_i*2+1]*256;
		FLASH_ProgramHalfWord(WRITE_START_ADDR, HalfWord);
		WRITE_START_ADDR+=2;
	}
	FLASH_Lock();																															//锁定flash
	__set_PRIMASK(0);
}
/*******************************************************************************************************************
flash			读取函数
addr 			读取地址
*p  			读取后的储存数组
Byte_Num	读取的位数   
********************************************************************************************************************/
void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num)
{
	while(Byte_Num--)
	{
		*(p++)=*((uint8_t*)addr++);
	}
}

void flash_write2(void)
{
	u16 cnt = 0;
	
	u16 data[2]={5261,0x5678};

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(0x0800f800);
	for(cnt=0;cnt<2;cnt++)
		FLASH_ProgramHalfWord((0x0800f800 +cnt*2),data[cnt]);  
	FLASH_Lock();
}

void Flash_Write_Str(uint32_t WRITE_START_ADDR,u8 Flash_Write_Data[],u32 First_address,u32 Flash_Write_Len)//01 02 03 的话len=3
{
	WRITE_START_ADDR2=WRITE_START_ADDR-WRITE_START_ADDR%0x800;
	if(WRITE_START_ADDR2>=0X08010000)
	{
		for(Flash_Write_Str_i=0;Flash_Write_Str_i<2048;Flash_Write_Str_i++)
		{
			Flash_ChengXu_Data[Flash_Write_Str_i]=ChengXu_Data[WRITE_START_ADDR2-0X08010000+Flash_Write_Str_i];
		}
		for(Flash_Write_Str_i=WRITE_START_ADDR%0x800;Flash_Write_Str_i<WRITE_START_ADDR%0x800+Flash_Write_Len;Flash_Write_Str_i++)
		{
			if(Flash_Write_Str_i<2048)
			{
				Flash_ChengXu_Data[Flash_Write_Str_i]=Flash_Write_Data[Flash_Write_Str_i-WRITE_START_ADDR%0x800+First_address];
			}else{
				Flash_Write_Data2[Flash_Write_Str_i-2048]=Flash_Write_Data[Flash_Write_Str_i-WRITE_START_ADDR%0x800+First_address];
				Flash_Write_Str_j=Flash_Write_Str_i-2048;
			}
		}
		Flash_Write_2K(WRITE_START_ADDR2);
		if(Flash_Write_Str_j>0)
		{
			for(Flash_Write_Str_i=0;Flash_Write_Str_i<2048;Flash_Write_Str_i++)
			{
				if(Flash_Write_Str_i<=Flash_Write_Str_j)
				{
					Flash_ChengXu_Data[Flash_Write_Str_i]=Flash_Write_Data2[Flash_Write_Str_i];
				}else{
					Flash_ChengXu_Data[Flash_Write_Str_i]=ChengXu_Data[WRITE_START_ADDR2-0X0800F800+Flash_Write_Str_i];
				}
			}
			Flash_Write_2K(WRITE_START_ADDR2+0X800);
		}
	}
}

