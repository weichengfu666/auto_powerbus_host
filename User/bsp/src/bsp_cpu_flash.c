/*
*********************************************************************************************************
*
*	模块名称 : cpu内部falsh操作模块
*	文件名称 : bsp_cpu_flash.c
*	版    本 : V1.0
*	说    明 : 提供读写CPU内部Flash的函数
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-02-01 armfly  正式发布
*
*	Copyright (C), 2023-2024, 皇甫实景娱乐公司
*
*********************************************************************************************************
*/

#include "bsp.h"
#include "bsp_cpu_flash.h"


/*
*********************************************************************************************************
*	函 数 名: bsp_WriteCpuFlashStr
*	功能说明: 写数据到CPU 内部Flash。先读取要修改的页到缓存，修改缓存数据，然后再写回flash （ 在指定flash范围内，可以任意地址，任意字节数修改 ）
*	形    参: _ulFlashAddr : Flash地址
*			 _ucpSrc : 数据缓冲区
*			 _ulSize : 数据大小（单位是字节）
*	返 回 值: 0-成功，1-数据长度或地址溢出，2-写Flash出错(估计Flash寿命到)
*********************************************************************************************************
*/
/* 设置有效flash地址范围，单次可写入最大页数 */

#define FLASH_STARTADDR 0X08020000      //可写入flash的起始地址
#define FLASH_WRITESIZE 0x10000         //可写入flash的存储大小
#define PAGE_SIZE 4                     //单次可写入最大页数
//const uint8_t flashArr[ FLASH_WRITESIZE ] __attribute__( ( at( FLASH_STARTADDR ) ) );       //从 FLASH_STARTADDR 开始，先定义 FLASH_WRITESIZE 可存储数据
uint8_t Flash2k_PageArr[PAGE_SIZE][2048];                                                   //flash缓存页，最多一次写入 PAGE_SIZE 缓存页到flash

uint8_t bsp_WriteCpuFlashStr(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize) /* 读取页到缓存，修改内容，再写回flash  */
{
    int32_t i;
    uint16_t usTemp;                            //缓存半字
    FLASH_Status status = FLASH_COMPLETE;       //操作flash成功的状态
    uint8_t* flash2k_PageArr_p;                 //指向flash缓存页的指针
    uint8_t page_index;                         //需要操作缓存页的索引
    uint32_t ulFlashAddr_pageStart;             //首页起始地址
    uint32_t ulFlashAddr_pageOffset;            //首页偏移地址
    uint32_t ulFlashAddr_pageNum;               //需要修改的页数
    uint32_t ulFlashAddr_pageNum_HalfWords;     //需要修改的半字数
        
	if(_ulFlashAddr >= FLASH_STARTADDR)
	{
        /* 计算需要操作的页起始地址，页偏移地址，页数 */
        ulFlashAddr_pageOffset = (uint32_t) _ulFlashAddr % 0x800;           
        ulFlashAddr_pageStart = _ulFlashAddr - ulFlashAddr_pageOffset ;     
        if( ( _ulSize + ulFlashAddr_pageOffset ) % 2048 == 0)               //计算要修改多少页
        {
            ulFlashAddr_pageNum = ( _ulSize + ulFlashAddr_pageOffset ) / 2048;
        }
        else
        {
            ulFlashAddr_pageNum = ( ( _ulSize + ulFlashAddr_pageOffset) / 2048 ) + 1;          
        }
        /* 超过单次最大写入页数，返回错误代码 */
        if( ulFlashAddr_pageNum > PAGE_SIZE )
        {
            return 1;   
        }  
        /* 开始原子操作 */
        {
            __set_PRIMASK(1);  		/* 关中断 */
            FLASH_Unlock();         /* FLASH 解锁 */
            FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);  	/* Clear pending flags (if any) */
        }
        /* 读取flash要修改的页到缓存页 Flash2k_PageArr */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            for( i = 0; i < 2048; i++ )
            {
//                Flash2k_PageArr[ page_index ][ i ] = flashArr[ ulFlashAddr_pageStart - FLASH_STARTADDR + i + page_index * 2048 ]; 
                Flash2k_PageArr[ page_index ][ i ] = *(uint8_t *) ( ulFlashAddr_pageStart + i + page_index * 2048 ); 
            }
        }
        /* 将要修改的数据保存到缓存页 Flash2k_PageArr */
        flash2k_PageArr_p = & Flash2k_PageArr[ 0 ][ ulFlashAddr_pageOffset ];
        for(i = 0; i < _ulSize; i++)
        {
            flash2k_PageArr_p[i] = _ucpSrc[i];
        }
        /* 擦除要修改的页 */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            status = FLASH_ErasePage(ulFlashAddr_pageStart + page_index * 2048);
            if (status != FLASH_COMPLETE)
            {
                return 2;
            }
        }
        /* 将缓存写入flash，按字节模式编程（为提高效率，可以按字编程，一次写入4字节） */
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
        /* 结束原子操作 */
        {
        FLASH_Lock();  	/* Flash 加锁，禁止写Flash控制寄存器 */
        __set_PRIMASK(0);  		/* 开中断 */
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
*	函 数 名: bsp_GetSector
*	功能说明: 根据地址计算扇区首地址
*	形    参：无
*	返 回 值: 扇区首地址
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
*	函 数 名: bsp_ReadCpuFlash
*	功能说明: 读取CPU Flash的内容
*	形    参：_ucpDst : 目标缓冲区
*			 _ulFlashAddr : 起始地址
*			 _ulSize : 数据大小（单位是字节）
*	返 回 值: 0=成功，1=失败
*********************************************************************************************************
*/
uint8_t bsp_ReadCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize)
{
	uint32_t i;

	/* 如果偏移地址超过芯片容量，则不改写输出缓冲区 */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	/* 长度为0时不继续操作,否则起始地址为奇地址会出错 */
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
*	函 数 名: bsp_WriteCpuFlash
*	功能说明: 写数据到CPU 内部Flash。
*	形    参: _ulFlashAddr : Flash地址
*			 _ucpSrc : 数据缓冲区
*			 _ulSize : 数据大小（单位是字节）
*	返 回 值: 0-成功，1-数据长度或地址溢出，2-写Flash出错(估计Flash寿命到)
*********************************************************************************************************
*/
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpSrc, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucRet;
	uint16_t usTemp;
	FLASH_Status status = FLASH_COMPLETE;

	/* 如果偏移地址超过芯片容量，则不改写输出缓冲区 */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	/* 长度为0 时不继续操作  */
	if (_ulSize == 0)
	{
		return 0;
	}

	/* 长度为奇数时,直接返回  */
	if ((_ulSize % 2) != 0)
	{
		return 1;
	}	

	ucRet = bsp_CmpCpuFlash(_ulFlashAddr, _ucpSrc, _ulSize);

	if (ucRet == FLASH_IS_EQU)
	{
		return 0;
	}

	__set_PRIMASK(1);  		/* 关中断 */

	/* FLASH 解锁 */
	FLASH_Unlock();

  	/* Clear pending flags (if any) */
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	/* 需要擦除 */
	if (ucRet == FLASH_REQ_ERASE)
	{
		status = FLASH_ErasePage(bsp_GetSector(_ulFlashAddr));
		if (status != FLASH_COMPLETE)
		{
			return 2;
		}		
	}

	/* 按字节模式编程（为提高效率，可以按字编程，一次写入4字节） */
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

  	/* Flash 加锁，禁止写Flash控制寄存器 */
  	FLASH_Lock();

  	__set_PRIMASK(0);  		/* 开中断 */

	if (status == FLASH_COMPLETE)
	{
		return 0;
	}
	return 2;
}
/*
*********************************************************************************************************
*	函 数 名: bsp_CmpCpuFlash
*	功能说明: 比较Flash指定地址的数据.
*	形    参: _ulFlashAddr : Flash地址
*			 _ucpBuf : 数据缓冲区
*			 _ulSize : 数据大小（单位是字节）
*	返 回 值:
*			FLASH_IS_EQU		0   Flash内容和待写入的数据相等，不需要擦除和写操作
*			FLASH_REQ_WRITE		1	Flash不需要擦除，直接写
*			FLASH_REQ_ERASE		2	Flash需要先擦除,再写
*			FLASH_PARAM_ERR		3	函数参数错误
*********************************************************************************************************
*/
uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucIsEqu;	/* 相等标志 */
	uint8_t ucByte;

	/* 如果偏移地址超过芯片容量，则不改写输出缓冲区 */
	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return FLASH_PARAM_ERR;		/*　函数参数错误　*/
	}

	/* 长度为0时返回正确 */
	if (_ulSize == 0)
	{
		return FLASH_IS_EQU;		/* Flash内容和待写入的数据相等 */
	}

	ucIsEqu = 1;			/* 先假设所有字节和待写入的数据相等，如果遇到任何一个不相等，则设置为 0 */
	for (i = 0; i < _ulSize; i++)
	{
		ucByte = *(uint8_t *)_ulFlashAddr;

		if (ucByte != *_ucpBuf)
		{
			if (ucByte != 0xFF)
			{
				return FLASH_REQ_ERASE;		/* 需要擦除后再写 */
			}
			else /* 为0xFF不用擦除 */
			{
				ucIsEqu = 0;	/* 不相等，需要写 */
			}
		}

		_ulFlashAddr++;
		_ucpBuf++;
	}

	if (ucIsEqu == 1)
	{
		return FLASH_IS_EQU;	/* Flash内容和待写入的数据相等，不需要擦除和写操作 */
	}
	else
	{
		return FLASH_REQ_WRITE;	/* Flash不需要擦除，直接写 */
	}
}

/***************************** 皇甫实景娱乐公司 (END OF FILE) *********************************/
