#ifndef __M25P80_H__
#define	__M25P80_H__
#include "m25p80.h"
#include "stdint.h"
#include "systick.h"


#define SPIX SPI1

#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01
#define READ 0x03
#define FAST_READ 0x0b
#define PAGE_PROG 0x02
#define SECTOR_ERASER 0xD8
#define BULK_ERASER 0xC7
#define DEEP_SLEEP 0xB9
#define RES 0xAB

void M25P80_SPI_CSN(uint8_t value);
void M25P80_SPI_CLK(uint8_t value);
void M25P80_SPI_MOSI(uint8_t value);
uint8_t M25P80_SPI_MISO(void);
void GPIO_FLASH_Init(void);

void M25P80_OPEN(void);
void M25P80_Read_Bytes(uint32_t addr , uint8_t* re_buf_p , uint16_t no);
uint16_t SPI_FLASH_SendByte(uint8_t TxData8bit);

#endif
