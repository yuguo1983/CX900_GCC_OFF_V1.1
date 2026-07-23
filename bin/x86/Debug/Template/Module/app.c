#include"user_config.h"
#include "delay.h"
#include "GPU_Cfg.h"
#include "GPU_PIC.h"
#include "GPU_Show.h"
#include "usartfifo.h"
#include "timer.h"
#include "mytext.h"
#include "mytext.h"
extern uint8_t P0_SampleValue;
extern uint8_t KeyPowerPressed;
extern uint8_t KeyUpPressed;
extern uint8_t KeyDownPressed;
extern uint8_t ShowMode;
void Init_IO(void)
{
init_spi();
}
/**********************************************************************************************************
*     函 数 名: Lcd_ShowMode
*     功能说明:
*     形    参: --
*     返 回 值:
*     日期	 :2022-10-08
*********************************************************************************************************
*/ 
void Color(uint32_t color)
{
	Lcd_ShowPureColor(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH,ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH,color);
	printk("stringphoto0x%06x \r\n",color);
}
void ColorBarCol(uint16_t div)
{
	ColorBarCol1(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH,ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH,div);
	printk("stringphotoColorBarCol \r\n");
}
void ColorBarRow(uint16_t div)
{
	ColorBarRow1(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH,ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH,div);
	printk("stringphotoColorBarRow \r\n");
}

void BlackWight(uint32_t color1, uint32_t color2)
{
	BlackWight1(1, 1, ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH-1, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH-1, ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH,ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH,color1, color2);
	printk("stringphotoBlackWight \r\n");
}

void Checkerboard(uint16_t div)
{
	Checkerboard1(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH,ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH,div);
	printk("stringphotoCheckerboard \r\n");
}

void CrossTalk(uint32_t color1, uint32_t color2)
{
	BlackWight1(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH/3, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH/3, ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH - ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH/3, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH - ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH/3, ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH,color1, color2);
	printk("stringphotoCrossTalk \r\n");
}

void Picture(uint8_t value)
{
	DisplayBMP(value);
	printk("stringphotoBMP%d \r\n",value);
}

void GradientCol(uint32_t color,uint16_t div)
{
	ColorGradientRow(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH, color,div);
	printk("stringphotoGradientCol \r\n");
}

void GradientRow(uint32_t color,uint16_t div)
{
	ColorGradientCol(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH, color,div);
	printk("stringphotoGradientRow \r\n");
}

void Flicker(uint32_t color1, uint32_t color2)
{
    printk("stringphotoflink \r\n");
	FLINK(ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH, ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH, color1, color2) ;
	
}
void TpTest(void)
{
 TP_Main();
}
void Lcd_ShowMode(uint8_t ShowId) 
{
    uint16_t Width, Hight;
    uint8_t temp[64];
    char path[30];
  switch (ShowId)
   {
case 0:
      Color(0xffffffff);
 break;
case 1:
      Color(0xffff0000);
 break;
case 2:
      Color(0xff00ff00);
 break;
case 3:
      Color(0xff0000ff);
 break;
case 4:
      Color(0xff808080);
 break;
case 5:
      Color(0xff000000);
 break;
case 6:
      BlackWight(0xffffffff,0xff000000);
 break;
case 7:
      GradientRow(0xffffffff,255);
 break;
case 8:
      GradientCol(0xffffffff,255);
 break;
case 9:
      CrossTalk(0xffffffff,0xff000000);
 break;
case 10:
      Picture(1);
 break;

 default:break; 
}
}
