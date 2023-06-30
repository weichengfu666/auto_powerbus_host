#include "bsp.h"
#include "bsp_serchSlave.h"


uint16_t            SlaveSize;                                                    //�ӻ�������0x02 �ֽ�
SlaveTypeDef    SlaveArr[ SlaveArrLen ] = {0};                       //511���ӻ��ṹ��
uint16_t            PackSize;                                                    //Ч������0x02 �ֽ�
uint8_t              NodeSize;                                                   //�ڵ�����0x01�ֽ�
uint8_t              NodeAddrArr[ NodeAddrArrLen ][ 3 ];         //170�������ڵ��ַ


uint16_t readPackSize( void )       //��flash --> ������
{
    readFlashStr( packSize_addr, (uint8_t*)& PackSize,  sizeof( PackSize ) ); 
    return PackSize; 
}

uint8_t readNodeSize( void )       //��flash --> ������
{
    readFlashStr( nodeSize_addr, (uint8_t*)& NodeSize,  sizeof( NodeSize ) );
    return NodeSize;
}

uint16_t readSlaveSize( void )     //��flash --> ������
{
    readFlashStr( slaveSize_addr, (uint8_t*)& SlaveSize,  sizeof( SlaveSize ) ); 
    return SlaveSize;
}

uint16_t writeSlaveSize( void )    //д���� --> flash
{
    writeFlashStr( slaveSize_addr, (uint8_t*)& SlaveSize,  sizeof( SlaveSize ) ); 
    return SlaveSize;
}

uint16_t clearSlaveSize( void )    //��������flash
{
    SlaveSize = 0;
    writeSlaveSize();
    readSlaveSize();
    return SlaveSize;
}

//�ӻ��ṹ��
uint16_t readSlaveArr( void )      //��flash --> ������
{
    uint16_t i;
    readSlaveSize();       
    for( i = 0; i < SlaveSize; i++)
    {
        readFlashStr( slaveArr_addr + i * sizeof( SlaveTypeDef ), ( uint8_t *)& SlaveArr[i], sizeof( SlaveTypeDef ) );
    }
    return SlaveSize;
}

uint16_t wirteSlaveArr( void )     //д���� --> flash
{
    uint16_t i;
    writeSlaveSize();              
    for( i = 0; i < SlaveSize; i++)
    {
        writeFlashStr( slaveArr_addr + i * sizeof( SlaveTypeDef ), ( uint8_t *)& SlaveArr[i], sizeof( SlaveTypeDef ) );
    }
    return SlaveSize;
}

uint16_t clearSlaveArr( void )     //��������flash
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

