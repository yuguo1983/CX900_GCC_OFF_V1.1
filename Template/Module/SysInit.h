#ifndef __SYSINIT_H
#define __SYSINIT_H



#include "UserGpioDefine.h"
//#include "MCU_GPU_fsmc.h"
#include "pport_spi.h"
#include "GPU_Cfg.h"
#include "usart_pc.h"
#include "GPU_PIC.h"
#include "GPU_SDIO.h"
#include "display.h"
void SysInit(void);
void SysInitErrorProcess(void);

#define RGB565(r, g, b) ((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3))

#define RED   RGB565(255,0,0)		//╨Ли╚
#define GREEN RGB565(0,255,0)		//бли╚
#define BLUE  RGB565(0,0,255)		//ю╤и╚
#define BLACK RGB565(0,0,0)			//╨зи╚
#define WHITE RGB565(255,255,255)	//╟ви╚
#define DimGrey RGB565(105,105,105)	//╩ри
#define Yellow1 RGB565(255,255,0)	//╩ри╚╚

#endif /* __SYSINIT_H */
