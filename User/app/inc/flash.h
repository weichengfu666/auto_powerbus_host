#ifndef APP_FLASH_H
#define APP_FALSH_H

#include "bsp.h"

typedef struct FlashAddr_t
{
    uint32_t slaveDeviceCount;//从机数地址
    uint32_t displayPacketCount;//效果包数地址
    uint32_t displayPacketVectorArr;//效果包向量表首地址
    uint32_t slaveSerialNumArr;//从机序列号首地址
}FlashAddr_t;

extern FlashAddr_t FlashAddr;

void flash_Test(void);//测试程序
uint8_t flash_WriteSlaveDeviceCount(void);//写从机数到flash
uint16_t flash_ReadSlaveDeviceCount(void);//从flash读从机数
uint8_t flash_WriteDisplayPacketCount(void);//写效果包数到flash
uint16_t flash_ReadDisplayPacketCount(void);//从flash读效果包数


#endif

