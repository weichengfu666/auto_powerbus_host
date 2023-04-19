#ifndef __FLASH_H__
#define __FLASH_H__

#include "bsp.h"

typedef enum FlashAddr{
    slaveDeviceCount_addr           = 0x08020000,                                                       //�ӻ�����ַ
    displayPacketCount_addr         = 0x08020002,                                                       //Ч��������ַ
    displayPacketVectorArr_addr     = 0x08020004,   displayPacketVectorArr_len     = 200,               //Ч�����������׵�ַ�����鳤��
    slaveDeviceSerialNumArr_addr    = 0x08020800,   slaveDeviceSerialNumArr_len    = 512                //�ӻ����к��׵�ַ�����鳤��
}FlashAddr_typedef;

extern uint16_t  SlaveDeviceCount;
extern uint16_t  DisplayPacketCount;
extern uint8_t   DisplayPacketVectorArr[displayPacketVectorArr_len][4];
extern uint8_t   SlaveDeviceSerialNumArr[slaveDeviceSerialNumArr_len][5];

void    flash_Test(void);//���Գ���
int8_t  flash_WriteSlaveDeviceCount(void);          //д�ӻ�����flash
int16_t flash_ReadSlaveDeviceCount(void);           //���ӻ�����flash
int8_t  flash_WriteDisplayPacketCount(void);        //дЧ��������flash
int16_t flash_ReadDisplayPacketCount(void);         //��Ч��������flash
int8_t  flash_WriteSlaveDeviceSerialNumArr(void);   //д�ӻ����кŵ�flash
int8_t  flash_ReadSlaveDeviceSerialNumArr(void);    //���ӻ����кŴ�flash


#endif

