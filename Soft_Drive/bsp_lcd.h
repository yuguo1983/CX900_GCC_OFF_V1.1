
#ifndef __BSP_LCD_h__
#define __BSP_LCD_h__

#include "gd32f30x.h"
#include "gd32f30x_exmc.h"
#include "gd32f303e_eval.h"
#include "gd25qxx.h"

//extern unsigned short int Logo_TST[];
//extern const unsigned char Hanzi[16*2*45];
//extern const unsigned char HanziBig[24*3*2];
//extern const unsigned char asc2_1608[1520];
//extern const unsigned char asc1_1206[95][12];
//extern const unsigned char asc1_1608[95][16];
//extern const unsigned char asc1_2412[95][36];


#define BASE_CH_16x16    0x5f0
#define BASE_CH_24x24    0x365c0
#define BASE_ASCII_8x16  0x0
#define BASE_ASCII_12x24 0x353f0
#define BASE_Logo 0xAD540

//#define MCU_GPU_ADDR  	*(volatile uint16_t *)0x60000000
//#define MCU_GPU_DATA  	*(volatile uint16_t *)0x60040000

#define RGB565(r, g, b) ((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3))

#define RED   RGB565(255,0,0)		//ºìÉ«
#define GREEN RGB565(0,255,0)		//ÂÌÉ«
#define BLUE  RGB565(0,0,255)		//À¶É«
#define BLACK RGB565(0,0,0)			//ºÚÉ«
#define WHITE RGB565(255,255,255)	//°×É«
#define DimGrey RGB565(105,105,105)	//»ÒÉ
#define Yellow1 RGB565(255,255,0)	//»ÒÉ««

#define ROW  320		    //ÏÔÊ¾µÄÐÐ¡¢ÁÐÊý
#define COL  240
#define BACK_COLOR BLUE
#define POINT_COLOR WHITE
void EXMC_Configuration(void);
//---------------------------------------------------------------------


void Lcd_Set_Data(uint16_t index);
void Lcd_Set_BL(uint8_t index);
void WriteComm(uint16_t cmd);
void WriteData(uint16_t temp);
void BSP_LCD_Init(void);
void LCD_Logo_Disp(void);
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend);
void LCD_Clear(uint16_t Color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t PixelColor);
void LCD_DrawPoint_big(uint16_t x,uint16_t y, uint16_t PixelColor);
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t PixelColor);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t PixelColor);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t PixelColor);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode,uint16_t fColor,uint16_t bColor);
void LCD_ShowChar12x24(uint16_t x,uint16_t y,uint8_t num,uint8_t mode,uint16_t fColor,uint16_t bColor);
void LCD_ShowHanziChar(uint16_t x,uint16_t y,uint16_t num,uint8_t mode,uint16_t fColor,uint16_t bColor);
void LCD_ShowHanzi24x24Char(uint16_t x,uint16_t y,uint16_t num,uint8_t mode,uint16_t fColor,uint16_t bColor);
uint32_t mypow(uint8_t m,uint8_t n);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len);
void DispNumber(int x,int y,int value,uint16_t len,uint16_t cValue);
void DispHexChar(int x,int y,int value,uint16_t len,uint16_t cValue);
void LCD_Show2Num(uint16_t x,uint16_t y,uint16_t num,uint8_t len);
void LCD_ShowString(uint16_t x,uint16_t y,const char *p,uint16_t fColor,uint16_t bColor);
void LCD_ShowString1(uint16_t x,uint16_t y,const char *p, uint16_t fColor,uint16_t bColor);
void Disp_Window(unsigned short x,unsigned short y, unsigned short width,unsigned short high,unsigned short cc);
uint16_t LCD_ReadPoint(uint16_t x,uint16_t y);
void LCD_SetCursor( uint16_t Xpos, uint16_t Ypos );
uint16_t LCD_RD_data(void);

void LCD_ShowChar1(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);
void LCD_ShowString2(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p);
void LCD_ShowNum1(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size);

#endif


