#ifndef __APP_H
#define __APP_H

//#include "BasicDataType.h"
#include "UserGpioDefine.h"
#include "GPU_PIC.h"
#include "display.h"

#define SEL_KEY_AUTO  0x01
#define SEL_KEY_UP    0x02
#define SEL_KEY_DOWN  0x04
#define SEL_KEY_RESET 0x08
#define SEL_KEY_POWER 0x10

#define RGB565(r, g, b) ((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3))

#define RED   RGB565(255,0,0)		//ºìÉ«
#define GREEN RGB565(0,255,0)		//ÂÌÉ«
#define BLUE  RGB565(0,0,255)		//À¶É«
#define BLACK RGB565(0,0,0)			//ºÚÉ«
#define WHITE RGB565(255,255,255)	//°×É«
#define DimGrey RGB565(105,105,105)	//»ÒÉ
#define Yellow1 RGB565(255,255,0)	//»ÆÉ«
#define PINK    RGB565(0,255,255)	//»ÒÉ««

//pattern type detail
#define PATTERN_FLICKER_COLUMN_INVERSION  (0x00)
#define PATTERN_FLICKER_ONE_DOT           (0x01)
#define PATTERN_CROSSTALK_BLACK_L127_GRAY (0x02)
#define PATTERN_CROSSTALK_WHITE_L127_GRAY (0x03)
#define PATTERN_CHECKER_BLACK_WHITE       (0x04)
#define PATTERN_CHECKER_WHITE_BLACK       (0x05)
#define PATTERN_GRAY_SCALE_V_L0_L255      (0x06)
#define PATTERN_GRAY_SCALE_H_L0_L255      (0x07)
#define PATTERN_8COLORBAR_V_BBRGWCYM      (0x08)
#define PATTERN_8COLORBAR_H_BBRGWCYM      (0x09)
#define PATTERN_4COLORBAR_V_L0_L255       (0x0A)
#define PATTERN_4COLORBAR_H_L0_L255       (0x0B)
#define PATTERN_FLICKER_RGBBBB_1          (0x0C)
#define PATTERN_FLICKER_RGBBBB_2          (0x0D)
#define PATTERN_COLOR_OUTLINE             (0x0E)
#define PATTERN_RGB3COLORBAR_H            (0x0F)
#define PATTERN_GRAY_SCALE_V_L255_L0      (0x10)
#define PATTERN_GRAY_SCALE_H_L255_L0      (0x11)
#define PATTERN_4COLORBAR_V_L255_L0       (0x12)
#define PATTERN_4COLORBAR_H_L255_L0       (0x13)


void Init_IO(void);
void Lcd_ShowMode(uint8_t ShowId);
uint8_t KEY_Value(uint8_t key_sel);
uint8_t Get_UpKeyNeg(void);
uint8_t Get_DownKeyNeg(void);
uint8_t Get_AutoKeyNeg(void);
uint8_t Get_PowerKeyNeg(void);
void delay_1ms_with_KeyScan(uint16_t ms);
void delay_1ms_Only_PowerKeyScan(uint16_t ms);

#endif /* __APP_H */
