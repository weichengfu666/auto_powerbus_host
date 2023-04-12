#ifndef APP_FLASH_H
#define APP_FALSH_H

#include "bsp.h"

typedef struct FlashAddr_t
{
    uint32_t slaveDeviceCount;//�ӻ�����ַ
    uint32_t displayPacketCount;//Ч��������ַ
    uint32_t displayPacketVectorArr;//Ч�����������׵�ַ
    uint32_t slaveSerialNumArr;//�ӻ����к��׵�ַ
}FlashAddr_t;

extern FlashAddr_t FlashAddr;

void flash_Test(void);//���Գ���
uint8_t flash_WriteSlaveDeviceCount(void);//д�ӻ�����flash
uint16_t flash_ReadSlaveDeviceCount(void);//��flash���ӻ���
uint8_t flash_WriteDisplayPacketCount(void);//дЧ��������flash
uint16_t flash_ReadDisplayPacketCount(void);//��flash��Ч������


#endif

