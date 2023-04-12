#include "bsp.h"

#define DISPLAYPACKETVECTORARR_LEN  200     //效果包向量数组长度
#define SLAVESERIALNUMARR_LEN       512     //从机序列号数组长度

//主机读写flash的地址全局变量
FlashAddr_t FlashAddr = {
    .slaveDeviceCount = 0x08020000,
    .displayPacketCount = 0x08020002,
    .displayPacketVectorArr = 0x08020004,
    .slaveSerialNumArr = 0x08020800
};

uint16_t SlaveDeviceCount;          //从机数
uint16_t DisplayPacketCount;        //效果包数
uint32_t DisplayPacketVectorArr[DISPLAYPACKETVECTORARR_LEN];        //效果包向量数组
uint8_t  SlaveSerialNumArr[SLAVESERIALNUMARR_LEN][5];               //从机序列号数组,每组序列号5字节

/*
*********************************************************************************************************
*	函 数 名: flash_Test
*	功能说明: 测试读写数据到CPU 内部Flash。
*********************************************************************************************************
*/
void flash_Test(void)
{
    uint16_t temp;
    //测试读写从机数到CPU 内部Flash
    flash_WriteSlaveDeviceCount();
    temp = flash_ReadSlaveDeviceCount();
    DEBUG_Num(1,1,temp,10);
    //测试读写效果包数到CPU 内部Flash
    flash_WriteDisplayPacketCount();
    temp = flash_ReadDisplayPacketCount();
    DEBUG_Num(2,1,temp,10);
    
}

/*
*********************************************************************************************************
*	函 数 名: flash_WriteSlaveDeviceCount
*	功能说明: 写从机数到CPU 内部Flash。
*	返 回 值: 0-成功，1-错误
*********************************************************************************************************
*/
uint8_t flash_WriteSlaveDeviceCount(void)
{
    if(bsp_WriteCpuFlash(FlashAddr.slaveDeviceCount, (uint8_t *)(&SlaveDeviceCount), 2) == 0)
    {
        return 0; 
    }
    else
    {
        return 1; 
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_ReadSlaveDeviceCount
*	功能说明: 读取CPU Flash的从机数
*	返 回 值: 从机数
*********************************************************************************************************
*/
uint16_t flash_ReadSlaveDeviceCount(void)
{
    uint16_t temp = 0;
    bsp_ReadCpuFlash(FlashAddr.slaveDeviceCount, (uint8_t *)&temp, 2);
    SlaveDeviceCount = temp;
    return temp;
}

/*
*********************************************************************************************************
*	函 数 名: flash_WriteDisplayPacketCount
*	功能说明: 写效果包数到CPU 内部Flash。
*	返 回 值: 0-成功，1-错误
*********************************************************************************************************
*/
uint8_t flash_WriteDisplayPacketCount(void)
{
    if(bsp_WriteCpuFlash(FlashAddr.displayPacketCount, (uint8_t *)(&DisplayPacketCount), 2) == 0)
    {
        return 0; 
    }
    else
    {
        return 1; 
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_ReadDisplayPacketCount
*	功能说明: 读取CPU Flash的效果包数
*	返 回 值: 效果包数
*********************************************************************************************************
*/
uint16_t flash_ReadDisplayPacketCount(void)
{
    uint16_t temp = 0;
    bsp_ReadCpuFlash(FlashAddr.displayPacketCount, (uint8_t *)&temp, 2);
    DisplayPacketCount = temp;
    return temp;
}

