#ifndef __TOUCHPOINT_H
#define __TOUCHPOINT_H

#include "gd32f30x.h"
#include "GPU_I2C.h"
#include "user_config.h"
#include "userGpioDefine.h"
#include "systick.h"
#include "GPU_CFG.h"
#include "GPU_PIC.h"
#include "timer.h"
uint8_t TP_Main(void);
void TP_Drow(void);
void TP_Init(void);
uint8_t TP_Read(uint8_t ts_x,uint8_t ts_y);
#endif /* __TOUCHPOINT_H */
