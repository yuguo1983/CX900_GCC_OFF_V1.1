/********************* COPYRIGHT  **********************
* File Name        : delay.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : Ó²¼þÑÓÊ±
********************************************************/

#ifndef __GPU_I2C_H
#define __GPU_I2C_H
#include "gd32f30x.h"
#include "systick.h"
#include "GPU_DDR.h"
#include "GPU_PIC.h"
#include "bsp_lcd.h"
#include "timer.h"
#define GPU_IIC_BASE   0x60
#define GPU_IIC_BASE1  0x70
#define GPU_IIC_CTRL   0x00
#define GPU_IIC_DIV    0x01
#define GPU_IIC_LENTH  0x02
#define GPU_IIC_ADDR   0x03
#define GPU_IIC_DATA   0x04
uint8_t I2C_Find(uint8_t delay);
uint8_t I2C_Write(uint8_t slave,uint8_t *p,uint16_t length,uint8_t delay);
uint8_t I2C_WriteM(uint8_t slave,uint8_t *p,uint16_t length,uint8_t delay,uint8_t time);
uint8_t I2C_ReadM(uint8_t slave,uint8_t *p,uint16_t length,uint8_t delay,uint8_t time);
uint8_t I2C_Read(uint8_t slave,uint8_t *p,uint16_t length,uint8_t delay);
uint8_t getInt(uint8_t value);
void setInt(uint8_t value);
void ShowTpUI(uint32_t Width,uint32_t Hight,uint8_t hdiv,uint8_t vdiv);
void ShowTpFill(uint32_t Width,uint32_t Hight,uint16_t pointx,uint16_t pointy,uint8_t hdiv,uint8_t vdiv,uint32_t color);
uint8_t ShowTpCheck(uint8_t hdiv,uint8_t vdiv);
#endif
