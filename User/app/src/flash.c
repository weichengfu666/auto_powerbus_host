#include "bsp.h"
#include "flash.h"

uint16_t    SlaveDeviceCount;
uint16_t    DisplayPacketCount;
uint8_t     DisplayPacketVectorArr[displayPacketVectorArr_len][4];
uint8_t     SlaveDeviceSerialNumArr[slaveDeviceSerialNumArr_len][5];


/*
*********************************************************************************************************
*	�� �� ��: flash_ReadSlaveDeviceSerialNumArr
*	����˵��: ��CPU �ڲ�Flash���ӻ����кš�
*	�� �� ֵ: 0-�ɹ���-1-��ʧ�ܣ�-2-û�дӻ��ɶ�
*********************************************************************************************************
*/
int8_t flash_ReadSlaveDeviceSerialNumArr(void)
{
    if( ( SlaveDeviceCount = flash_ReadSlaveDeviceCount() ) > 0)//�ȴ�flash���ӻ�����ram�� SlaveDeviceCount���������0���ͽ��ӻ����кŴ�flash����ram�� SlaveDeviceSerialNumArr
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
        return -2;//û�дӻ��ɶ�
    }
}
/*
*********************************************************************************************************
*	�� �� ��: flash_WriteSlaveDeviceSerialNumArr
*	����˵��: д�ӻ����кŵ�CPU �ڲ�Flash��
*	�� �� ֵ: 0-�ɹ���-1-дʧ�ܣ�-2-û�дӻ���д
*********************************************************************************************************
*/
int8_t flash_WriteSlaveDeviceSerialNumArr(void)
{
    if( SlaveDeviceCount > 0 )//�ȴ�ram�� SlaveDeviceCount ���ӻ������������0���ͽ��ӻ����кŴ�ram�� SlaveDeviceSerialNumArr д��flash
    {
        flash_WriteSlaveDeviceCount();//д�ӻ�����flash
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
        return -2;//û�дӻ���д
    }
}
/*
*********************************************************************************************************
*	�� �� ��: flash_WriteSlaveDeviceCount
*	����˵��: д�ӻ�����CPU �ڲ�Flash��
*	�� �� ֵ: 0-�ɹ���-1-дʧ��
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
*	�� �� ��: flash_ReadSlaveDeviceCount
*	����˵��: ��ȡCPU Flash�Ĵӻ���
*	�� �� ֵ: �ӻ���-�ɹ�, -1-��ʧ��
*********************************************************************************************************
*/
int16_t flash_ReadSlaveDeviceCount( void )
{
    if( bsp_ReadCpuFlash( slaveDeviceCount_addr, ( uint8_t * ) &SlaveDeviceCount, sizeof( SlaveDeviceCount ) ) == 0 )
    {
        if( SlaveDeviceCount == 0xFFFF)     //flash�������ֵΪ0xFFFF
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
*	�� �� ��: flash_WriteDisplayPacketCount
*	����˵��: дЧ��������CPU �ڲ�Flash��
*	�� �� ֵ: 0-�ɹ���-1-дʧ��
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
*	�� �� ��: flash_ReadDisplayPacketCount
*	����˵��: ��ȡCPU Flash��Ч������
*	�� �� ֵ: Ч������-�ɹ���-1-��ʧ��
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
*	�� �� ��: flash_Test
*	����˵��: ���Զ�д���ݵ�CPU �ڲ�Flash��
*********************************************************************************************************
*/
void flash_Test( void )
{
    uint16_t temp;
   
    flash_WriteSlaveDeviceCount();           //���Զ�д�ӻ�����CPU �ڲ�Flash
    temp = flash_ReadSlaveDeviceCount();
    DEBUG_Num( 1, 1, temp, 10);
    
    flash_WriteDisplayPacketCount();        //���Զ�дЧ��������CPU �ڲ�Flash
    temp = flash_ReadDisplayPacketCount();
    DEBUG_Num( 2, 1, temp, 10 );
    
}
