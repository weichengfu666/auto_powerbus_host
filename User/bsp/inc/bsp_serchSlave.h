#ifndef __FLASH_H__
#define __FLASH_H__

#include "bsp.h"

#define SlaveArrLen 128    
#define packArrLen  16

typedef struct {
    uint32_t    packAddr;                      //Ч������ַ
    uint16_t    packLen;                       //Ч��������
}PackTypeDef;

typedef struct {
    uint8_t     serialArr [ 5 ];              //��ʼ���к�
    uint8_t     assignArr [ 2 ];            //��ֵ���к�
    uint8_t              packSize;              //Ч��������
    PackTypeDef     packArr[ packArrLen ];              //16��Ч����
}SlaveTypeDef;

typedef enum {
    slaveSize_addr        = 0x08020000,                                                       //�ӻ�������ַ
    slaveArr_addr         = 0x08020002,                                                       //�ӻ��ṹ����ʼ��ַ
}FlashAddr_typedef;



extern uint16_t            SlaveSize;                                     //�ӻ�������0x02 �ֽ�
extern SlaveTypeDef    SlaveArr[ SlaveArrLen ];               //128���ӻ��ṹ�壬0x4400 �ֽ�

//�ӻ�����
uint16_t readSlaveSize( void );        //��flash --> ������
uint16_t writeSlaveSize( void );       //д���� --> flash
uint16_t clearSlaveSize( void );       //��������flash
//�ӻ��ṹ��
uint16_t readSlaveArr( void );         //��flash --> ������
uint16_t wirteSlaveArr( void );         //д���� --> flash 
uint16_t clearSlaveArr( void );         //��������flash

#endif

