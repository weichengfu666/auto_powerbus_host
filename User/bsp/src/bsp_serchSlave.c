#include "bsp.h"
#include "bsp_serchSlave.h"


uint16_t            SlaveSize;                       //�ӻ�����
SlaveTypeDef    SlaveArr[ SlaveArrLen ] = {0};

//�ӻ�����
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
