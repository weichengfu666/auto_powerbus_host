#ifndef __FLASH_H__
#define __FLASH_H__

#include "bsp.h"

typedef enum FlashAddr{
    slaveDeviceCount_addr           = 0x08020000,                                                       //从机数地址
    displayPacketCount_addr         = 0x08020002,                                                       //效果包数地址
    displayPacketVectorArr_addr     = 0x08020004,   displayPacketVectorArr_len     = 200,               //效果包向量表首地址，数组长度
    slaveDeviceSerialNumArr_addr    = 0x08020800,   slaveDeviceSerialNumArr_len    = 512                //从机序列号首地址，数组长度
}FlashAddr_typedef;

extern uint16_t  SlaveDeviceCount;
extern uint16_t  DisplayPacketCount;
extern uint8_t   DisplayPacketVectorArr[displayPacketVectorArr_len][4];
extern uint8_t   SlaveDeviceSerialNumArr[slaveDeviceSerialNumArr_len][5];

void    flash_Test(void);//测试程序
int8_t  flash_WriteSlaveDeviceCount(void);          //写从机数到flash
int16_t flash_ReadSlaveDeviceCount(void);           //读从机数从flash
int8_t  flash_WriteDisplayPacketCount(void);        //写效果包数到flash
int16_t flash_ReadDisplayPacketCount(void);         //读效果包数从flash
int8_t  flash_WriteSlaveDeviceSerialNumArr(void);   //写从机序列号到flash
int8_t  flash_ReadSlaveDeviceSerialNumArr(void);    //读从机序列号从flash


#endif

