
#ifndef __screenUI__
#define __screenUI__

#include "gd32f30x.h"
#include "bsp_lcd.h"
#include "gd25qxx.h"


void openInterface(void );
void mainInterface(void );
void UpdateInterface(void);
void SdSlect(uint8_t value);
void FindInterface(void);
#define CodeVersion  0 //1 is x850 
#define CodeVersion1 0 //1 is S860 0 is x810  
#if CodeVersion
	#define CodeMaxNum  0x8FFF //0x04 find 5 code
#elif CodeVersion1
  #define CodeMaxNum  0x8FFF //0x04 find 5 code
#else
	#define CodeMaxNum  0x04 //0x04 find 5 code
#endif

#endif


