#ifndef __GPU_PIC_H
#define __GPU_PIC_H

#include "gd32f30x.h"
#include "GPU_RGB.h"
#include "GPU_I2C.h"
#include "GPU_DDR.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#define GPU_SYS_BASE  0x00


#define GPU_I2C_BASE  0x60
void GPU_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t pSize,uint32_t color);
void AreaFilling(uint16_t startx,uint16_t starty,uint16_t endx,uint16_t endy,uint32_t color);
void AreaGradient(uint16_t startx,uint16_t starty,uint16_t endx,uint16_t endy,uint32_t color,uint16_t incr,uint16_t incg, uint16_t incb,uint8_t type);
void ColorBarRow1(uint16_t Width,uint16_t Hight,uint16_t div);
void ColorBarCol1(uint16_t Width,uint16_t Hight,uint16_t div);
void BlackWight1(uint16_t startx,uint16_t starty,uint16_t endx,uint16_t endy,uint16_t Width,uint16_t Hight,uint32_t color1,uint32_t color2);
void Checkerboard1(uint16_t Width,uint16_t Hight,uint16_t div);
void ColorGradientRow(uint16_t Width,uint16_t Hight,uint32_t color,uint16_t div);
void ColorGradientCol(uint16_t Width,uint16_t Hight,uint32_t color,uint16_t div);
void AutoFlink(uint16_t dot,uint32_t color1,uint32_t color2);
void AutoFlinkRow(uint16_t Width,uint16_t dot,uint32_t color1,uint32_t color2);
void AutoFlinkCol(uint16_t Hight,uint16_t dot,uint32_t color1,uint32_t color2);
void Lcd_ShowPureColor(uint16_t Width,uint16_t Hight,uint32_t color);
void DisplayBMP(uint8_t num);
uint32_t GPU_PIC_Init(void);
void UG_DrawLine( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t pSize, uint32_t c );
void WriteKuang(uint16_t Width,uint16_t Hight,uint32_t color);
void FLINK(uint16_t Width, uint16_t Hight,uint32_t color1,uint32_t color2);
#endif
