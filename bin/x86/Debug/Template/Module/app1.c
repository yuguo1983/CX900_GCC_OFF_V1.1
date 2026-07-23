#include <stdio.h>
#include "app.h"
#include "pport_spi.h"
#include "user_config.h"
#include "delay.h"
#include "GPU_Cfg.h"
#include "GPU_PIC.h"
#include "GPU_Show.h"
#include "usartfifo.h"
#include "timer.h"
#include "mytext.h"
extern uint8_t P0_SampleValue;
extern uint8_t KeyPowerPressed;
extern uint8_t KeyUpPressed;
extern uint8_t KeyDownPressed;
extern uint8_t ShowMode;
//extern   uint8_t 				*pic_name;
//初始化IO驱动强度
void Init_IO(void)
{
    init_spi();
}

void DrawRed(void);
//GpuShowString(0,0,"123",3,0x00FF00);


/*
*********************************************************************************************************
*    函 数 名: Lcd_ShowMode
*    功能说明:
*    形    参: --
*    返 回 值:
*    日期	 :2022-10-08
*********************************************************************************************************
*/

void Lcd_ShowMode(uint8_t ShowId)
{
    uint16_t Width, Hight;
    Width = ptr_MIPI_TABLE[gMipiTableIndex]->HACT_WIDTH;
    Hight = ptr_MIPI_TABLE[gMipiTableIndex]->VACT_WIDTH;
        switch(ShowId)
        {
        case 0:
            Lcd_ShowPureColor(Width, Hight, 0xFF0000);
            ShowString(Width / 2 - 12, 100, 100, 20, 24, "red");
				    printk("stringphotored \r\n"); 

            break; //(R,G,B)红
        case 1:
            Lcd_ShowPureColor(Width, Hight, 0x00FF00);
            ShowString(Width / 2 - 20, 100, 100, 20, 24, "green");
						printk("stringphotogreen \r\n"); 
            break; //(R,G,B)绿
        case 2:
            Lcd_ShowPureColor(Width, Hight, 0x0000FF);
            ShowString(Width / 2 - 16, 100, 100, 20, 24, "blue");
						printk("stringphotoblue \r\n"); 
            break; //(R,G,B)蓝
        case 3:
            FLINK(Width, Hight, 0x800080, 0x008000) ;
				    printk("stringphotoFLINK \r\n"); 
            break; //(R,G,B)白
        case 4:
            ColorGradientCol(Width, Hight, 0xFFFFFF, 64);
						printk("stringphoto0xFFFFFF \r\n"); 
            break; //(R,G,B)黑
        case 5:
            ColorGradientRow(Width, Hight, 0xFFFFFF, 64);

            break; //(R,G,B)灰
        case 6:
            Checkerboard(Width, Hight, 12);
						printk("stringphotoCheckerboard \r\n"); 
            break;
        case 7:
            BlackWight(1, 1, Width - 1, Hight - 1, Width, Hight, 0x00ffffff, 0x000000);
						printk("stringphotoBlackWight \r\n"); 
            break;
        case 8:
            ColorBarCol(Width, Hight, 8);
						printk("stringphotoColorBarCol\r\n"); 
            break;
        case 9:
            ColorBarRow(Width, Hight, 4);
						printk("stringphotoColorBarRow\r\n"); 
            break;
        case 10:
            DisplayBMP(1);
						printk("stringphotoBMP1\r\n");
            break;
        case 11:
            DisplayBMP(2);
						printk("stringphotoBMP2\r\n");
            break;
        default:
            break;
        }    
}




