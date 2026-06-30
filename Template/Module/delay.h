/********************* COPYRIGHT  **********************
* File Name        : delay.h
* Author           : synopsts
* Version          : V1.0
* Date             : 2018-7-10
* Description      : Ó²¼þÑÓÊ±
********************************************************/

#ifndef __DELAY_H
#define __DELAY_H
#include "gd32f30x.h"
//#include "misc.h"

void delay_init(void);
void delay_us(uint32_t nus);
void delay_s(unsigned int s);

#endif
