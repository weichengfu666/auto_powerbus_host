#ifndef __FLISH_FUNATION_H
#define __FLISH_FUNATION_H

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

void Flash_Write_2K(uint32_t WRITE_START_ADDR);
void FLASH_ReadByte(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void flash_write2(void);
void Flash_Write_Str(uint32_t WRITE_START_ADDR,u8 Flash_Write_Data[],u32 First_address,u32 Flash_Write_Len);

#endif
