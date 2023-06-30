#ifndef __FLASH_H__
#define __FLASH_H__

#include "bsp.h"

#define SlaveArrLen 511
#define NodeAddrArrLen 170

typedef struct {
    uint8_t     serialArr [ 5 ];              //初始序列号
    uint8_t     assignArr [ 2 ];            //赋值序列号
    uint8_t     grogramArr [ 3 ];        //设备程序首地址（设备效果1首地址的地址）
}SlaveTypeDef;

typedef enum {
    slaveSize_addr        = 0x08010000,                                                       //从机总数起始地址
    slaveArr_addr         = 0x08010002,                                                       //从机结构体起始地址
    packSize_addr        = 0x080113f8,                                                       //效果数起始地址
    nodeSize_addr        = 0x08011400,                                                      //节点数起始地址
    nodeAddrArr_addr         = 0x08011401                                                       //触发节点地址的起始地址
}FlashAddr_typedef;



extern uint16_t            SlaveSize;                                                    //从机总数，0x02 字节
extern SlaveTypeDef    SlaveArr[ SlaveArrLen ];                               //128个从机结构体
extern uint16_t            PackSize;                                                    //效果数，0x02 字节
extern uint8_t              NodeSize;                                                   //节点数，0x01字节
extern uint8_t              NodeAddrArr[ NodeAddrArrLen ][ 3 ];         //触发节点地址

//从机总数
uint16_t readSlaveSize( void );        //读flash --> 到缓存
uint16_t writeSlaveSize( void );       //写缓存 --> flash
uint16_t clearSlaveSize( void );       //清除缓存和flash
//从机结构体
uint16_t readSlaveArr( void );         //读flash --> 到缓存
uint16_t wirteSlaveArr( void );         //写缓存 --> flash 
uint16_t clearSlaveArr( void );         //清除缓存和flash
//读flash --> 到缓存
uint16_t readPackSize( void );
uint8_t readNodeSize( void );
#endif

