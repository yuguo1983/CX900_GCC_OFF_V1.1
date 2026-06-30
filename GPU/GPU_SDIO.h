/********************* COPYRIGHT  **********************
* File Name        : delay.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : 硬件延时
********************************************************/

#ifndef __GPU_SDIO_H
#define __GPU_SDIO_H
#include "gd32f30x.h"
#include "systick.h"
#include "GPU_DDR.h"
#include "GPU_Cfg.h"
#define BMP_MAX_NUM 64
#define CMD0    0
#define CMD2    2
#define CMD3    3
#define CMD6    6
#define CMD7    7
#define CMD8    8
#define CMD9    9
#define CMD12   12
#define CMD24   24
#define CMD25   25
#define CMD17   17
#define CMD18   18

#define CMD55   55
#define ACMD41  41
#define ACMD51  51
#define ACMD6   6

#define GPU_SDIO_BASE  0x10

#define GPU_SDIO_CTRL  GPU_SDIO_BASE + 0x00
#define GPU_SDIO_CDIV  GPU_SDIO_BASE + 0x01
#define GPU_SDIO_CMD   GPU_SDIO_BASE + 0x02
#define GPU_SDIO_ARGL  GPU_SDIO_BASE + 0x03
#define GPU_SDIO_ARGH  GPU_SDIO_BASE + 0x04
#define GPU_SDIO_RXSEC GPU_SDIO_BASE + 0x05
#define GPU_SDIO_STATU GPU_SDIO_BASE + 0x06
#define GPU_SDIO_WDATA GPU_SDIO_BASE + 0x07
#define GPU_SDIO_RADDR GPU_SDIO_BASE + 0x08

uint8_t GPU_SDIO_INIT(void);
uint32_t GPU_SDIO_TX_CMD(uint8_t cmd,uint32_t arg);
uint8_t GPU_SDIO_ReadDisk(uint8_t *buf, uint32_t sector, uint8_t cnt);
uint8_t GPU_ReadDisk_TO_DDR(uint32_t sector, uint16_t cnt);
void GPU_FindBmp(void);
void GPU_LoadBMP(uint8_t num);
typedef struct {
	uint16_t ImageWidth; //用于记录该图像宽度
	uint16_t ImageHight; //用于记录该图像高度
	uint32_t ImageSize;  //用于记录该图像大小
	uint32_t ImageAddr; //用于记录该图像地址
} BMP_Table;


#endif
