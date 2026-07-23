/********************* COPYRIGHT  **********************
* File Name        : delay.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : Ó²¼þÑÓÊ±
********************************************************/

#ifndef __GPU_DAC_H
#define __GPU_DAC_H
#include "gd32f30x.h"
#include "systick.h"
#include "GPU_DDR.h"
#include "GPU_Cfg.h"
#define GPU_DAC_BASE  0x90

////////DDR offerset address
#define GPU_DAC_CTRL    GPU_DAC_BASE + 0x00
#define GPU_DAC_CLR    	GPU_DAC_BASE + 0x01
#define GPU_DAC_DATAL   GPU_DAC_BASE + 0x02
#define GPU_DAC_DATAH   GPU_DAC_BASE + 0x03

#define DLALL 	0x02//UPDATA SELECTET REGISTER
#define DLSUP 		0x03//UPDATA SELECTET REGISTER
#define PWDN		0X04


#define REF_CMD			0X08
#define REF_CMD1		0X09


#define PWN1KO			0X01
#define PWN100KO		0X02
#define PWNHZ				0X03


void Start_DAC(void);
void Clear_DAC(void);
void Enable_REF(void);
void InitDac(void);
void Set_DACVol(uint8_t ch,uint16_t voltege);
void init_powerset(void);


#endif
