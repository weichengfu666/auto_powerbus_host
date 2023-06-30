#include "bsp.h"
#include "bsp_serchSlave.h"


uint16_t            SlaveSize;                                                    //从机总数，0x02 字节
SlaveTypeDef    SlaveArr[ SlaveArrLen ] = {0};                       //511个从机结构体
uint16_t            PackSize;                                                    //效果数，0x02 字节
uint8_t              NodeSize;                                                   //节点数，0x01字节
uint8_t              NodeAddrArr[ NodeAddrArrLen ][ 3 ];         //170个触发节点地址


uint16_t readPackSize( void )       //读flash --> 到缓存
{
    readFlashStr( packSize_addr, (uint8_t*)& PackSize,  sizeof( PackSize ) ); 
    return PackSize; 
}

uint8_t readNodeSize( void )       //读flash --> 到缓存
{
    readFlashStr( nodeSize_addr, (uint8_t*)& NodeSize,  sizeof( NodeSize ) );
    return NodeSize;
}

uint16_t readSlaveSize( void )     //读flash --> 到缓存
{
    readFlashStr( slaveSize_addr, (uint8_t*)& SlaveSize,  sizeof( SlaveSize ) ); 
    return SlaveSize;
}

uint16_t writeSlaveSize( void )    //写缓存 --> flash
{
    writeFlashStr( slaveSize_addr, (uint8_t*)& SlaveSize,  sizeof( SlaveSize ) ); 
    return SlaveSize;
}

uint16_t clearSlaveSize( void )    //清除缓存和flash
{
    SlaveSize = 0;
    writeSlaveSize();
    readSlaveSize();
    return SlaveSize;
}

//从机结构体
uint16_t readSlaveArr( void )      //读flash --> 到缓存
{
    uint16_t i;
    readSlaveSize();       
    for( i = 0; i < SlaveSize; i++)
    {
        readFlashStr( slaveArr_addr + i * sizeof( SlaveTypeDef ), ( uint8_t *)& SlaveArr[i], sizeof( SlaveTypeDef ) );
    }
    return SlaveSize;
}

uint16_t wirteSlaveArr( void )     //写缓存 --> flash
{
    uint16_t i;
    writeSlaveSize();              
    for( i = 0; i < SlaveSize; i++)
    {
        writeFlashStr( slaveArr_addr + i * sizeof( SlaveTypeDef ), ( uint8_t *)& SlaveArr[i], sizeof( SlaveTypeDef ) );
    }
    return SlaveSize;
}

uint16_t clearSlaveArr( void )     //清除缓存和flash
{
    uint16_t i;
    SlaveTypeDef clear_SlaveArr = { 0 };
    readSlaveSize();
    for( i = 0; i < SlaveSize; i++)
    {
        SlaveArr[i] = clear_SlaveArr;
        writeFlashStr( slaveArr_addr + i * sizeof( SlaveTypeDef ), ( uint8_t *)& SlaveArr[i], sizeof( SlaveTypeDef ) );
    }
    return clearSlaveSize();
}

