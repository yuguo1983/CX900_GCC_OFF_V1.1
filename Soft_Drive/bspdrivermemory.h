#ifndef _BSP_DRIVER_MEMORY_H_
#define _BSP_DRIVER_MEMORY_H_


#include <stdint.h>

#define		WORD_OFFSET				    (2)
#define		DWORD_OFFSET				(4)

#define		MEMORY_BASE_ADDR			(0)                                 //0

//platform information
#define 	PLATFORM_BASE_ADDR			(MEMORY_BASE_ADDR + DWORD_OFFSET)   //4
#define 	PLATFORM_ADDR				(PLATFORM_BASE_ADDR + DWORD_OFFSET) //8

#define		CAL_DATA_CHANNEL			(3)
#define		CAL_DATA_OFFSET				(24)

//SDC CALIB parameter information
#define 	CAL_PARAM_BASE_ADDR		    (PLATFORM_ADDR + DWORD_OFFSET)      //12
#define 	CAL_PARAM_ADDR(x,y)			(CAL_PARAM_BASE_ADDR + ((CAL_DATA_OFFSET * DWORD_OFFSET * (x)) + DWORD_OFFSET * (y)))

#define		DCDC_CAL_CHANNEL			(5)
#define		DCDC_CAL_OFFSET				(24)

//DCDC CALIB parameter information
#define 	DCDC_CAL_BASE_ADDR		    (CAL_PARAM_ADDR(CAL_DATA_CHANNEL,0) + DWORD_OFFSET)
#define 	DCDC_CAL_ADDR(x,y)			(DCDC_CAL_BASE_ADDR + ((DCDC_CAL_OFFSET * DWORD_OFFSET * (x)) + DWORD_OFFSET * (y)))

#define		DCDC_CAL_IOFFSET_COUNT		(300)

#define 	DCDC_CAL_IOFFSET_BASE       (DCDC_CAL_ADDR(DCDC_CAL_CHANNEL,0) + DWORD_OFFSET)
#define 	DCDC_CAL_IOFFSET_ADDR(x,y)  (DCDC_CAL_IOFFSET_BASE + ((DCDC_CAL_IOFFSET_COUNT * DWORD_OFFSET * (x)) + DWORD_OFFSET * (y)))


#define     UART_PARA_BASE_ADDR         (DCDC_CAL_IOFFSET_ADDR(DCDC_CAL_CHANNEL,0) + DWORD_OFFSET)
#define     UART_PARA_ADDR(x)           (UART_PARA_BASE_ADDR + (DWORD_OFFSET * (x)))

int MEMORY_Init(void);

uint8_t MEMORY_ReadByte(uint32_t uiAddr);
uint32_t MEMORY_ReadDWord(uint32_t uiAddr);
void MEMORY_ReadDWords(uint32_t uiAddr,uint32_t *puiFrame,uint32_t uiLen);
void MEMORY_ReadBytes(uint32_t uiAddr,	unsigned char *pucFrame,uint32_t uiLen);

void MEMORY_WriteByte(uint32_t uiAddr,uint8_t ucData);
void MEMORY_WriteDWord(uint32_t uiAddr,uint32_t uiData);
void MEMORY_WriteBytes(uint32_t uiAddr,unsigned char *pucFrame,uint32_t uiLen);
void MEMORY_ClearArea(uint32_t uiAddr,uint32_t uiLen);
void MEMORY_WriteDWords(uint32_t uiAddr,uint32_t *puiFrame,uint32_t uiLen);

#endif
