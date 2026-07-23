#ifndef _CHIP_DRIVER_AT24C64D_H_
#define _CHIP_DRIVER_AT24C64D_H_

#include <stdint.h>

int AT24C64D_Init(void);
int AT24C64D_WriteByte(uint32_t uiAddr,uint8_t ucData);
int AT24C64D_WriteDWord(uint32_t uiAddr,uint32_t uiData);
int AT24C64D_WriteDWords(uint32_t uiAddr,uint32_t *puiFrame,uint32_t uiLen);
int AT24C64D_ClearArea(uint32_t uiAddr,uint32_t uiLen);
int AT24C64D_WriteBytes(uint32_t uiAddr,unsigned char *pucFrame,uint32_t uiLen);

uint8_t AT24C64D_ReadByte(uint32_t uiAddr);
uint32_t AT24C64D_ReadDWord(uint32_t uiAddr);
int AT24C64D_ReadBytes(uint32_t uiAddr,	unsigned char *pucFrame,uint32_t uiLen);
int AT24C64D_ReadDWords(uint32_t uiAddr,uint32_t *puiFrame,uint32_t uiLen);

#endif
