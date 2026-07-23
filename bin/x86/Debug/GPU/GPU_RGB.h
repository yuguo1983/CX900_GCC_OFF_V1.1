/********************* COPYRIGHT  **********************
* File Name        : gpu_rgb.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : RGB¿ØÖÆÄ£¿é
********************************************************/

#ifndef __GPU_RGB_H
#define __GPU_RGB_H
#include "gd32f30x.h"
#include "systick.h"
#include "GPU_Cfg.h"
#include "stdio.h"

#define GPU_RGB_BASE 0x40
////////RGB offerset address
#define GPU_RGB_CTRL  GPU_RGB_BASE + 0x00
#define GPU_RGB_DCM   GPU_RGB_BASE + 0x01
#define GPU_RGB_WIDE  GPU_RGB_BASE + 0x02
#define GPU_RGB_HIGHT GPU_RGB_BASE + 0x03
#define GPU_RGB_HBP   GPU_RGB_BASE + 0x04
#define GPU_RGB_HFP   GPU_RGB_BASE + 0x05
#define GPU_RGB_HPW   GPU_RGB_BASE + 0x06
#define GPU_RGB_VBP   GPU_RGB_BASE + 0x07
#define GPU_RGB_VFP   GPU_RGB_BASE + 0x08
#define GPU_RGB_VPW   GPU_RGB_BASE + 0x09
#define GPU_RGB_HINC  GPU_RGB_BASE + 0x0A
#define GPU_RGB_VINC  GPU_RGB_BASE + 0x0B
#define GPU_RGB_COLORL1  GPU_RGB_BASE + 0x0C
#define GPU_RGB_COLORH1  GPU_RGB_BASE + 0x0D
#define GPU_RGB_COLORL2  GPU_RGB_BASE + 0x0E
#define GPU_RGB_COLORH2  GPU_RGB_BASE + 0x0F
////ctrl regist
#define GPU_RGB_CLK_INV  0x80
#define GPU_RGB_DE_INV 0x10
#define GPU_RGB_HS_INV 0x20
#define GPU_RGB_VS_INV 0x40
#define GPU_RGB_ENABLE 0x01
#define GPU_RGB_DDR  0x00
#define GPU_RGB_COLOR 0x02
#define GPU_RGB_PIC   0x04
#define GPU_RGB_RBG   0x06
#define GPU_RGB_GRB   0x08
#define GPU_RGB_GBR   0x0A
#define GPU_RGB_BRG   0x0C
#define GPU_RGB_BGR   0x0E

void RGB_Enable(void);
void RGB_Disable(void);
void RGB_CLK(uint8_t value);
void RGB_DE(uint8_t value);
void RGB_HS(uint8_t value);
void RGB_VS(uint8_t value);
void RGB_Dcm(uint8_t m,uint8_t d);
void RGB_Paramer(uint16_t wide,uint16_t hight,uint16_t hbp,uint16_t hfp,uint16_t hpw,uint16_t vbp,uint16_t vfp,uint16_t vpw);
void RGB_Pic(uint16_t hinc,uint16_t vinc,uint32_t color1,uint32_t color2);
void RGB_Mode(uint8_t mode);
void WriteRGBParameter(uint8_t addr,uint16_t value);
#endif
