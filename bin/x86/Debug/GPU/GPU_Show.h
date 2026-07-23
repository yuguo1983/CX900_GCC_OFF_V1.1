/********************* COPYRIGHT  **********************
* File Name        : GPU_Show_H.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : ÏÔÊ¾¿ØÖÆÄ£¿é
********************************************************/

#ifndef __GPU_Show_H
#define __GPU_Show_H
#include "gd32f30x.h"
#include "GPU_DDR.h"
#include "GPU_PIC.h"
#include "gd25qxx.h"
//#define BASE_ASCII_8x16 0x90000
//#define BASE_CH_16x16   0x905F0
void GpuShowString(uint16_t x,uint16_t y,const char *p,uint8_t size,uint16_t fColor);
void GpuShowChar(uint16_t x,uint16_t y,uint16_t num,uint8_t size,uint16_t fColor);
void GpuShowHanzi(uint16_t x,uint16_t y,uint16_t num,uint8_t size,uint16_t fColor);

void GpuWritePoint(uint16_t x, uint16_t y, uint32_t color);
void Gpu_Mcu_Fill(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t *color);




#endif
