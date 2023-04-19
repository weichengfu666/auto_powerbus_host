#include "bsp.h"
#include "flash.h"

uint16_t    SlaveDeviceCount;
uint16_t    DisplayPacketCount;
uint8_t     DisplayPacketVectorArr[displayPacketVectorArr_len][4];
uint8_t     SlaveDeviceSerialNumArr[slaveDeviceSerialNumArr_len][5];


/*
*********************************************************************************************************
*	函 数 名: flash_ReadSlaveDeviceSerialNumArr
*	功能说明: 从CPU 内部Flash读从机序列号。
*	返 回 值: 0-成功，-1-读失败，-2-没有从机可读
*********************************************************************************************************
*/
int8_t flash_ReadSlaveDeviceSerialNumArr(void)
{
    if( ( SlaveDeviceCount = flash_ReadSlaveDeviceCount() ) > 0)//先从flash读从机数到ram的 SlaveDeviceCount，如果大于0，就将从机序列号从flash读到ram的 SlaveDeviceSerialNumArr
    {
        if( bsp_ReadCpuFlash( slaveDeviceSerialNumArr_addr, ( uint8_t * ) SlaveDeviceSerialNumArr, SlaveDeviceCount * 5 ) == 0 )
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -2;//没有从机可读
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_WriteSlaveDeviceSerialNumArr
*	功能说明: 写从机序列号到CPU 内部Flash。
*	返 回 值: 0-成功，-1-写失败，-2-没有从机可写
*********************************************************************************************************
*/
int8_t flash_WriteSlaveDeviceSerialNumArr(void)
{
    if( SlaveDeviceCount > 0 )//先从ram的 SlaveDeviceCount 读从机数，如果大于0，就将从机序列号从ram的 SlaveDeviceSerialNumArr 写入flash
    {
        flash_WriteSlaveDeviceCount();//写从机数到flash
        if( bsp_WriteCpuFlashStr( slaveDeviceSerialNumArr_addr, (uint8_t *) SlaveDeviceSerialNumArr, SlaveDeviceCount * 5) == 0 )
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -2;//没有从机可写
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_WriteSlaveDeviceCount
*	功能说明: 写从机数到CPU 内部Flash。
*	返 回 值: 0-成功，-1-写失败
*********************************************************************************************************
*/
int8_t flash_WriteSlaveDeviceCount( void )
{
    if( bsp_WriteCpuFlashStr( slaveDeviceCount_addr, ( uint8_t * ) &SlaveDeviceCount, sizeof( SlaveDeviceCount ) ) == 0 )
    {
        return 0; 
    }
    else
    {
        return -1; 
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_ReadSlaveDeviceCount
*	功能说明: 读取CPU Flash的从机数
*	返 回 值: 从机数-成功, -1-读失败
*********************************************************************************************************
*/
int16_t flash_ReadSlaveDeviceCount( void )
{
    if( bsp_ReadCpuFlash( slaveDeviceCount_addr, ( uint8_t * ) &SlaveDeviceCount, sizeof( SlaveDeviceCount ) ) == 0 )
    {
        if( SlaveDeviceCount == 0xFFFF)     //flash擦除后的值为0xFFFF
        {
            SlaveDeviceCount = 0;
        }
        return SlaveDeviceCount;
    }
    else
    {
        return -1;
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_WriteDisplayPacketCount
*	功能说明: 写效果包数到CPU 内部Flash。
*	返 回 值: 0-成功，-1-写失败
*********************************************************************************************************
*/
int8_t flash_WriteDisplayPacketCount( void )
{
    if( bsp_WriteCpuFlashStr( displayPacketCount_addr, ( uint8_t * ) &DisplayPacketCount, sizeof( DisplayPacketCount ) ) == 0 )
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
/*
*********************************************************************************************************
*	函 数 名: flash_ReadDisplayPacketCount
*	功能说明: 读取CPU Flash的效果包数
*	返 回 值: 效果包数-成功，-1-读失败
*********************************************************************************************************
*/
int16_t flash_ReadDisplayPacketCount( void )
{
    if(bsp_ReadCpuFlash( displayPacketCount_addr, ( uint8_t * ) &DisplayPacketCount, sizeof( DisplayPacketCount ) ) == 0 )
    {
        return DisplayPacketCount;
    }
    else
    {
        return -1;
    }
}

/*
*********************************************************************************************************
*	函 数 名: flash_Test
*	功能说明: 测试读写数据到CPU 内部Flash。
*********************************************************************************************************
*/
void flash_Test( void )
{
    uint16_t temp;
   
    flash_WriteSlaveDeviceCount();           //测试读写从机数到CPU 内部Flash
    temp = flash_ReadSlaveDeviceCount();
    DEBUG_Num( 1, 1, temp, 10);
    
    flash_WriteDisplayPacketCount();        //测试读写效果包数到CPU 内部Flash
    temp = flash_ReadDisplayPacketCount();
    DEBUG_Num( 2, 1, temp, 10 );
    
}
