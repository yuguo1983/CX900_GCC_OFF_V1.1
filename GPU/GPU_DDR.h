/********************* COPYRIGHT  **********************
* File Name        : ddr.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : 配置DDR寄存器
********************************************************/

#ifndef __GPU_DDR_H
#define __GPU_DDR_H
#include "gd32f30x.h"
#include "systick.h"


#define GPU_DDR_BASE  0x20

////////DDR offerset address
#define GPU_DDR_CTRL    GPU_DDR_BASE + 0x00
#define GPU_DDR_WSTATU  GPU_DDR_BASE + 0x01
#define GPU_DDR_WXS     GPU_DDR_BASE + 0x02
#define GPU_DDR_WYS     GPU_DDR_BASE + 0x03
#define GPU_DDR_WXE     GPU_DDR_BASE + 0x04
#define GPU_DDR_WYE     GPU_DDR_BASE + 0x05
#define GPU_DDR_WPAGE   GPU_DDR_BASE + 0x06
#define GPU_DDR_COLORL  GPU_DDR_BASE + 0x07
#define GPU_DDR_COLORH  GPU_DDR_BASE + 0x08
#define GPU_DDR_INCR    GPU_DDR_BASE + 0x09
#define GPU_DDR_INCG    GPU_DDR_BASE + 0x0A
#define GPU_DDR_INCB    GPU_DDR_BASE + 0x0B
#define GPU_DDR_RSTATU1 GPU_DDR_BASE + 0x10
#define GPU_DDR_RXS1    GPU_DDR_BASE + 0x11
#define GPU_DDR_RYS1    GPU_DDR_BASE + 0x12
#define GPU_DDR_RXE1    GPU_DDR_BASE + 0x13
#define GPU_DDR_RYE1    GPU_DDR_BASE + 0x14
#define GPU_DDR_RPAGE1  GPU_DDR_BASE + 0x15
#define GPU_DDR_RSTATU2 GPU_DDR_BASE + 0x18
#define GPU_DDR_RXS2    GPU_DDR_BASE + 0x19
#define GPU_DDR_RYS2    GPU_DDR_BASE + 0x1A
#define GPU_DDR_RXE2    GPU_DDR_BASE + 0x1B
#define GPU_DDR_RYE2    GPU_DDR_BASE + 0x1C
#define GPU_DDR_RPAGE2  GPU_DDR_BASE + 0x1D

#define GPU_DDR_ENABLE  0x01;
#define GPU_DDR_FILL    0x02;
#define GPU_DDR_LRSW    0x04;
#define GPU_DDR_TDSW    0x08;
#define GPU_DDR_MCUST    0x10;
#define GPU_DDR_BUSY    0x01;
void SetDdrRdRLSwarp(uint8_t value);
void SetDdrRdTDSwarp(uint8_t value);
void SetDdrRLSwarp(uint8_t value);
void SetDdrTDSwarp(uint8_t value);
void SetDdrWrStart(void);
void SetDdrWrEnable(void);
void SetDdrWrDisable(void);
void SetDdrWrPageA(void);
void SetDdrRdPageA(void);
void SetDdrFillStart(void);
void SetDdrWrPage(uint16_t page);
void SetDdrRdPage1(uint16_t page);
void SetDdrRdPage2(uint16_t page);
void SetDdrWrSize(uint16_t wxs,uint16_t wys,uint16_t wxe,uint16_t wye);
void SetDdrRdSize1(uint16_t rxs,uint16_t rys,uint16_t rxe,uint16_t rye);
void SetDdrRdSize2(uint16_t rxs,uint16_t rys,uint16_t rxe,uint16_t rye);
void SetDdrWrFill(uint32_t color);
void SetDdrRdCtrl(uint16_t page);
void test_ddr(void);
void drawsolidcolor(void);
#endif
