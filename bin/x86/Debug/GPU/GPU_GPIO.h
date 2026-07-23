/********************* COPYRIGHT  **********************
* File Name        : delay.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : Ó²¼þÑÓÊ±
********************************************************/

#ifndef __GPU_GPIO_H
#define __GPU_GPIO_H
#include "gd32f30x.h"
#include "systick.h"
#include "GPU_DDR.h"
#include "GPU_Cfg.h"
#define GPU_GPIO_BASE  0xb0

////////DDR offerset address
#define GPU_VCC1_UP    		GPU_GPIO_BASE + 0x00
#define GPU_VCC1_DN    		GPU_GPIO_BASE + 0x0A

#define GPU_VCC2_UP    		GPU_GPIO_BASE + 0x01
#define GPU_VCC2_DN    		GPU_GPIO_BASE + 0x0B

#define GPU_VCC3_UP    		GPU_GPIO_BASE + 0x02
#define GPU_VCC3_DN    		GPU_GPIO_BASE + 0x0C

#define GPU_VCC4_UP    		GPU_GPIO_BASE + 0x03
#define GPU_VCC4_DN    		GPU_GPIO_BASE + 0x0D

#define GPU_VCC5_UP    		GPU_GPIO_BASE + 0x04
#define GPU_VCC5_DN    		GPU_GPIO_BASE + 0x0E

#define GPU_VCC6_UP    		GPU_GPIO_BASE + 0x05
#define GPU_VCC6_DN    		GPU_GPIO_BASE + 0x0F

#define GPU_VSP_UP    		GPU_GPIO_BASE + 0x06
#define GPU_VSP_DN    		GPU_GPIO_BASE + 0x10

#define GPU_VSN_UP    		GPU_GPIO_BASE + 0x07
#define GPU_VSN_DN    		GPU_GPIO_BASE + 0x11

#define GPU_BL_UP    			GPU_GPIO_BASE + 0x08
#define GPU_BL_DN    			GPU_GPIO_BASE + 0x12

#define	GPU_VCC_SW				GPU_GPIO_BASE+0x14

#define	GPU_EXGPIO_BASE		0x05



typedef enum 
{
	VCC1=1,
	VCC2,
	VCC3,
	VCC4,
	VCC5,
	VCC6,
	VSP,
	VSN,
	BL,
}POWER_ENUM;



void SetVcc1(uint16_t uptimes,uint16_t downtimes);
void SetVcc2(uint16_t uptimes,uint16_t downtimes);
void SetVcc3(uint16_t uptimes,uint16_t downtimes);
void SetVcc4(uint16_t uptimes,uint16_t downtimes);
void SetVcc5(uint16_t uptimes,uint16_t downtimes);
void SetVcc6(uint16_t uptimes,uint16_t downtimes);
void SetVSP(uint16_t uptimes,uint16_t downtimes);
void SetVSN(uint16_t uptimes,uint16_t downtimes);
void SetBL(uint16_t uptimes,uint16_t downtimes);
void SetGpuExgpio(uint8_t ch,uint8_t value);
void EnableVCC(uint8_t ch ,uint8_t enable);
void BeepOn(void);


#endif
