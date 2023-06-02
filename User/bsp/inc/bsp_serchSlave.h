#ifndef __FLASH_H__
#define __FLASH_H__

#include "bsp.h"

#define SlaveArrLen 128    
#define packArrLen  16

typedef struct {
    uint32_t    packAddr;                      //效果包地址
    uint16_t    packLen;                       //效果包长度
}PackTypeDef;

typedef struct {
    uint8_t     serialArr [ 5 ];              //初始序列号
    uint8_t     assignArr [ 2 ];            //赋值序列号
    uint8_t              packSize;              //效果包数量
    PackTypeDef     packArr[ packArrLen ];              //16个效果包
}SlaveTypeDef;

typedef enum {
    slaveSize_addr        = 0x08020000,                                                       //从机总数地址
    slaveArr_addr         = 0x08020002,                                                       //从机结构体起始地址
}FlashAddr_typedef;



extern uint16_t            SlaveSize;                                     //从机总数，0x02 字节
extern SlaveTypeDef    SlaveArr[ SlaveArrLen ];               //128个从机结构体，0x4400 字节

//从机总数
uint16_t readSlaveSize( void );        //读flash --> 到缓存
uint16_t writeSlaveSize( void );       //写缓存 --> flash
uint16_t clearSlaveSize( void );       //清除缓存和flash
//从机结构体
uint16_t readSlaveArr( void );         //读flash --> 到缓存
uint16_t wirteSlaveArr( void );         //写缓存 --> flash 
uint16_t clearSlaveArr( void );         //清除缓存和flash

#endif

