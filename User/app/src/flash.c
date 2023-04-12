#include "bsp.h"

#define DISPLAYPACKETVECTORARR_LEN  200     //Ч�����������鳤��
#define SLAVESERIALNUMARR_LEN       512     //�ӻ����к����鳤��

//������дflash�ĵ�ַȫ�ֱ���
FlashAddr_t FlashAddr = {
    .slaveDeviceCount = 0x08020000,
    .displayPacketCount = 0x08020002,
    .displayPacketVectorArr = 0x08020004,
    .slaveSerialNumArr = 0x08020800
};

uint16_t SlaveDeviceCount;          //�ӻ���
uint16_t DisplayPacketCount;        //Ч������
uint32_t DisplayPacketVectorArr[DISPLAYPACKETVECTORARR_LEN];        //Ч������������
uint8_t  SlaveSerialNumArr[SLAVESERIALNUMARR_LEN][5];               //�ӻ����к�����,ÿ�����к�5�ֽ�

/*
*********************************************************************************************************
*	�� �� ��: flash_Test
*	����˵��: ���Զ�д���ݵ�CPU �ڲ�Flash��
*********************************************************************************************************
*/
void flash_Test(void)
{
    uint16_t temp;
    //���Զ�д�ӻ�����CPU �ڲ�Flash
    flash_WriteSlaveDeviceCount();
    temp = flash_ReadSlaveDeviceCount();
    DEBUG_Num(1,1,temp,10);
    //���Զ�дЧ��������CPU �ڲ�Flash
    flash_WriteDisplayPacketCount();
    temp = flash_ReadDisplayPacketCount();
    DEBUG_Num(2,1,temp,10);
    
}

/*
*********************************************************************************************************
*	�� �� ��: flash_WriteSlaveDeviceCount
*	����˵��: д�ӻ�����CPU �ڲ�Flash��
*	�� �� ֵ: 0-�ɹ���1-����
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
*	�� �� ��: flash_ReadSlaveDeviceCount
*	����˵��: ��ȡCPU Flash�Ĵӻ���
*	�� �� ֵ: �ӻ���
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
*	�� �� ��: flash_WriteDisplayPacketCount
*	����˵��: дЧ��������CPU �ڲ�Flash��
*	�� �� ֵ: 0-�ɹ���1-����
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
*	�� �� ��: flash_ReadDisplayPacketCount
*	����˵��: ��ȡCPU Flash��Ч������
*	�� �� ֵ: Ч������
*********************************************************************************************************
*/
uint16_t flash_ReadDisplayPacketCount(void)
{
    uint16_t temp = 0;
    bsp_ReadCpuFlash(FlashAddr.displayPacketCount, (uint8_t *)&temp, 2);
    DisplayPacketCount = temp;
    return temp;
}

