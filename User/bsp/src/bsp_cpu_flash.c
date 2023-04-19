/*
*********************************************************************************************************
*
*	ģ������ : cpu�ڲ�falsh����ģ��
*	�ļ����� : bsp_cpu_flash.c
*	��    �� : V1.0
*	˵    �� : �ṩ��дCPU�ڲ�Flash�ĺ���
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2013-02-01 armfly  ��ʽ����
*
*	Copyright (C), 2023-2024, �ʸ�ʵ�����ֹ�˾
*
*********************************************************************************************************
*/

#include "bsp.h"
#include "bsp_cpu_flash.h"


/*
*********************************************************************************************************
*	�� �� ��: bsp_WriteCpuFlashStr
*	����˵��: д���ݵ�CPU �ڲ�Flash���ȶ�ȡҪ�޸ĵ�ҳ�����棬�޸Ļ������ݣ�Ȼ����д��flash �� ��ָ��flash��Χ�ڣ����������ַ�������ֽ����޸� ��
*	��    ��: _ulFlashAddr : Flash��ַ
*			 _ucpSrc : ���ݻ�����
*			 _ulSize : ���ݴ�С����λ���ֽڣ�
*	�� �� ֵ: 0-�ɹ���1-���ݳ��Ȼ��ַ�����2-дFlash����(����Flash������)
*********************************************************************************************************
*/
/* ������Чflash��ַ��Χ�����ο�д�����ҳ�� */

#define FLASH_STARTADDR 0X08020000      //��д��flash����ʼ��ַ
#define FLASH_WRITESIZE 0x10000         //��д��flash�Ĵ洢��С
#define PAGE_SIZE 4                     //���ο�д�����ҳ��
//const uint8_t flashArr[ FLASH_WRITESIZE ] __attribute__( ( at( FLASH_STARTADDR ) ) );       //�� FLASH_STARTADDR ��ʼ���ȶ��� FLASH_WRITESIZE �ɴ洢����
uint8_t Flash2k_PageArr[PAGE_SIZE][2048];                                                   //flash����ҳ�����һ��д�� PAGE_SIZE ����ҳ��flash

uint8_t bsp_WriteCpuFlashStr(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize) /* ��ȡҳ�����棬�޸����ݣ���д��flash  */
{
    int32_t i;
    uint16_t usTemp;                            //�������
    FLASH_Status status = FLASH_COMPLETE;       //����flash�ɹ���״̬
    uint8_t* flash2k_PageArr_p;                 //ָ��flash����ҳ��ָ��
    uint8_t page_index;                         //��Ҫ��������ҳ������
    uint32_t ulFlashAddr_pageStart;             //��ҳ��ʼ��ַ
    uint32_t ulFlashAddr_pageOffset;            //��ҳƫ�Ƶ�ַ
    uint32_t ulFlashAddr_pageNum;               //��Ҫ�޸ĵ�ҳ��
    uint32_t ulFlashAddr_pageNum_HalfWords;     //��Ҫ�޸ĵİ�����
        
	if(_ulFlashAddr >= FLASH_STARTADDR)
	{
        /* ������Ҫ������ҳ��ʼ��ַ��ҳƫ�Ƶ�ַ��ҳ�� */
        ulFlashAddr_pageOffset = (uint32_t) _ulFlashAddr % 0x800;           
        ulFlashAddr_pageStart = _ulFlashAddr - ulFlashAddr_pageOffset ;     
        if( ( _ulSize + ulFlashAddr_pageOffset ) % 2048 == 0)               //����Ҫ�޸Ķ���ҳ
        {
            ulFlashAddr_pageNum = ( _ulSize + ulFlashAddr_pageOffset ) / 2048;
        }
        else
        {
            ulFlashAddr_pageNum = ( ( _ulSize + ulFlashAddr_pageOffset) / 2048 ) + 1;          
        }
        /* �����������д��ҳ�������ش������ */
        if( ulFlashAddr_pageNum > PAGE_SIZE )
        {
            return 1;   
        }  
        /* ��ʼԭ�Ӳ��� */
        {
            __set_PRIMASK(1);  		/* ���ж� */
            FLASH_Unlock();         /* FLASH ���� */
            FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);  	/* Clear pending flags (if any) */
        }
        /* ��ȡflashҪ�޸ĵ�ҳ������ҳ Flash2k_PageArr */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            for( i = 0; i < 2048; i++ )
            {
//                Flash2k_PageArr[ page_index ][ i ] = flashArr[ ulFlashAddr_pageStart - FLASH_STARTADDR + i + page_index * 2048 ]; 
                Flash2k_PageArr[ page_index ][ i ] = *(uint8_t *) ( ulFlashAddr_pageStart + i + page_index * 2048 ); 
            }
        }
        /* ��Ҫ�޸ĵ����ݱ��浽����ҳ Flash2k_PageArr */
        flash2k_PageArr_p = & Flash2k_PageArr[ 0 ][ ulFlashAddr_pageOffset ];
        for(i = 0; i < _ulSize; i++)
        {
            flash2k_PageArr_p[i] = _ucpSrc[i];
        }
        /* ����Ҫ�޸ĵ�ҳ */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            status = FLASH_ErasePage(ulFlashAddr_pageStart + page_index * 2048);
            if (status != FLASH_COMPLETE)
            {
                return 2;
            }
        }
        /* ������д��flash�����ֽ�ģʽ��̣�Ϊ���Ч�ʣ����԰��ֱ�̣�һ��д��4�ֽڣ� */
        flash2k_PageArr_p = &Flash2k_PageArr[0][0];
        ulFlashAddr_pageNum_HalfWords = ulFlashAddr_pageNum * 2048 / 2;
        for (i = 0; i < ulFlashAddr_pageNum_HalfWords ; i++)
        {		
            usTemp = flash2k_PageArr_p[2 * i];
            usTemp |= (flash2k_PageArr_p[2 * i + 1] << 8);
            status = FLASH_ProgramHalfWord(ulFlashAddr_pageStart, usTemp);
            if (status != FLASH_COMPLETE)
            {
                return 2;
            }
            ulFlashAddr_pageStart += 2;
        }
        /* ����ԭ�Ӳ��� */
        {
        FLASH_Lock();  	/* Flash ��������ֹдFlash���ƼĴ��� */
        __set_PRIMASK(0);  		/* ���ж� */
        }
        if (status == FLASH_COMPLETE)
        {
            return 0;
        }
    }
    return 1;
}
/*
*********************************************************************************************************
*	�� �� ��: bsp_GetSector
*	����˵��: ���ݵ�ַ���������׵�ַ
*	��    �Σ���
*	�� �� ֵ: �����׵�ַ
*********************************************************************************************************
*/
uint32_t bsp_GetSector(uint32_t _ulWrAddr)
{
	uint32_t sector = 0;

	sector = _ulWrAddr & SECTOR_MASK;

	return sector;
}
/*
*********************************************************************************************************
*	�� �� ��: bsp_ReadCpuFlash
*	����˵��: ��ȡCPU Flash������
*	��    �Σ�_ucpDst : Ŀ�껺����
*			 _ulFlashAddr : ��ʼ��ַ
*			 _ulSize : ���ݴ�С����λ���ֽڣ�
*	�� �� ֵ: 0=�ɹ���1=ʧ��
*********************************************************************************************************
*/
uint8_t bsp_ReadCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize)
{
	uint32_t i;

	/* ���ƫ�Ƶ�ַ����оƬ�������򲻸�д��������� */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	/* ����Ϊ0ʱ����������,������ʼ��ַΪ���ַ����� */
	if (_ulSize == 0)
	{
		return 1;
	}

	for (i = 0; i < _ulSize; i++)
	{
		*_ucpDst++ = *(uint8_t *)_ulFlashAddr++;
	}

	return 0;
}
/*
*********************************************************************************************************
*	�� �� ��: bsp_WriteCpuFlash
*	����˵��: д���ݵ�CPU �ڲ�Flash��
*	��    ��: _ulFlashAddr : Flash��ַ
*			 _ucpSrc : ���ݻ�����
*			 _ulSize : ���ݴ�С����λ���ֽڣ�
*	�� �� ֵ: 0-�ɹ���1-���ݳ��Ȼ��ַ�����2-дFlash����(����Flash������)
*********************************************************************************************************
*/
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucRet;
	uint16_t usTemp;
	FLASH_Status status = FLASH_COMPLETE;

	/* ���ƫ�Ƶ�ַ����оƬ�������򲻸�д��������� */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	/* ����Ϊ0 ʱ����������  */
	if (_ulSize == 0)
	{
		return 0;
	}

	/* ����Ϊ����ʱ,ֱ�ӷ���  */
	if ((_ulSize % 2) != 0)
	{
		return 1;
	}	

	ucRet = bsp_CmpCpuFlash(_ulFlashAddr, _ucpSrc, _ulSize);

	if (ucRet == FLASH_IS_EQU)
	{
		return 0;
	}

	__set_PRIMASK(1);  		/* ���ж� */

	/* FLASH ���� */
	FLASH_Unlock();

  	/* Clear pending flags (if any) */
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	/* ��Ҫ���� */
	if (ucRet == FLASH_REQ_ERASE)
	{
		status = FLASH_ErasePage(bsp_GetSector(_ulFlashAddr));
		if (status != FLASH_COMPLETE)
		{
			return 2;
		}		
	}

	/* ���ֽ�ģʽ��̣�Ϊ���Ч�ʣ����԰��ֱ�̣�һ��д��4�ֽڣ� */
	for (i = 0; i < _ulSize / 2; i++)
	{
		//FLASH_ProgramByte(_ulFlashAddr++, *_ucpSrc++);		
		usTemp = _ucpSrc[2 * i];
		usTemp |= (_ucpSrc[2 * i + 1] << 8);
		status = FLASH_ProgramHalfWord(_ulFlashAddr, usTemp);
		if (status != FLASH_COMPLETE)
		{
			break;
		}
		
		_ulFlashAddr += 2;
	}

  	/* Flash ��������ֹдFlash���ƼĴ��� */
  	FLASH_Lock();

  	__set_PRIMASK(0);  		/* ���ж� */

	if (status == FLASH_COMPLETE)
	{
		return 0;
	}
	return 2;
}
/*
*********************************************************************************************************
*	�� �� ��: bsp_CmpCpuFlash
*	����˵��: �Ƚ�Flashָ����ַ������.
*	��    ��: _ulFlashAddr : Flash��ַ
*			 _ucpBuf : ���ݻ�����
*			 _ulSize : ���ݴ�С����λ���ֽڣ�
*	�� �� ֵ:
*			FLASH_IS_EQU		0   Flash���ݺʹ�д���������ȣ�����Ҫ������д����
*			FLASH_REQ_WRITE		1	Flash����Ҫ������ֱ��д
*			FLASH_REQ_ERASE		2	Flash��Ҫ�Ȳ���,��д
*			FLASH_PARAM_ERR		3	������������
*********************************************************************************************************
*/
uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucIsEqu;	/* ��ȱ�־ */
	uint8_t ucByte;

	/* ���ƫ�Ƶ�ַ����оƬ�������򲻸�д��������� */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return FLASH_PARAM_ERR;		/*��������������*/
	}

	/* ����Ϊ0ʱ������ȷ */
	if (_ulSize == 0)
	{
		return FLASH_IS_EQU;		/* Flash���ݺʹ�д���������� */
	}

	ucIsEqu = 1;			/* �ȼ��������ֽںʹ�д���������ȣ���������κ�һ������ȣ�������Ϊ 0 */
	for (i = 0; i < _ulSize; i++)
	{
		ucByte = *(uint8_t *)_ulFlashAddr;

		if (ucByte != *_ucpBuf)
		{
			if (ucByte != 0xFF)
			{
				return FLASH_REQ_ERASE;		/* ��Ҫ��������д */
			}
			else /* Ϊ0xFF���ò��� */
			{
				ucIsEqu = 0;	/* ����ȣ���Ҫд */
			}
		}

		_ulFlashAddr++;
		_ucpBuf++;
	}

	if (ucIsEqu == 1)
	{
		return FLASH_IS_EQU;	/* Flash���ݺʹ�д���������ȣ�����Ҫ������д���� */
	}
	else
	{
		return FLASH_REQ_WRITE;	/* Flash����Ҫ������ֱ��д */
	}
}

/***************************** �ʸ�ʵ�����ֹ�˾ (END OF FILE) *********************************/
