#ifndef __FLASH_H__
#define __FLASH_H__

#include "bsp.h"

#define SlaveArrLen 511
#define NodeAddrArrLen 170

typedef struct {
    uint8_t     serialArr [ 5 ];              //��ʼ���к�
    uint8_t     assignArr [ 2 ];            //��ֵ���к�
    uint8_t     grogramArr [ 3 ];        //�豸�����׵�ַ���豸Ч��1�׵�ַ�ĵ�ַ��
}SlaveTypeDef;

typedef enum {
    slaveSize_addr        = 0x08010000,                                                       //�ӻ�������ʼ��ַ
    slaveArr_addr         = 0x08010002,                                                       //�ӻ��ṹ����ʼ��ַ
    packSize_addr        = 0x080113f8,                                                       //Ч������ʼ��ַ
    nodeSize_addr        = 0x08011400,                                                      //�ڵ�����ʼ��ַ
    nodeAddrArr_addr         = 0x08011401                                                       //�����ڵ��ַ����ʼ��ַ
}FlashAddr_typedef;



extern uint16_t            SlaveSize;                                                    //�ӻ�������0x02 �ֽ�
extern SlaveTypeDef    SlaveArr[ SlaveArrLen ];                               //128���ӻ��ṹ��
extern uint16_t            PackSize;                                                    //Ч������0x02 �ֽ�
extern uint8_t              NodeSize;                                                   //�ڵ�����0x01�ֽ�
extern uint8_t              NodeAddrArr[ NodeAddrArrLen ][ 3 ];         //�����ڵ��ַ

//�ӻ�����
uint16_t readSlaveSize( void );        //��flash --> ������
uint16_t writeSlaveSize( void );       //д���� --> flash
uint16_t clearSlaveSize( void );       //��������flash
//�ӻ��ṹ��
uint16_t readSlaveArr( void );         //��flash --> ������
uint16_t wirteSlaveArr( void );         //д���� --> flash 
uint16_t clearSlaveArr( void );         //��������flash
//��flash --> ������
uint16_t readPackSize( void );
uint8_t readNodeSize( void );
#endif

