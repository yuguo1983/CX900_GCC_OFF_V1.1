#include "pport_spi.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "mipi_Cfg.h"
#include "lcd_cfg.h"

/*
void Initial_LCM_CODE(void){

    SPI_WriteCmd(0xB7);
	SPI_WriteData(0x50);//10=TX_CLK 30=PCLK
	SPI_WriteData(0x02);
	SPI_WriteCmd(0xBD);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

SSD2828_WritePackageSize(1);
SPI_WriteData(0x11);
bsp_DelayMS(200);
SSD2828_WritePackageSize(1);
SPI_WriteData(0x29);
bsp_DelayMS(100);

}

*/
void fun1(void)
{
	SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x05);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB1);
SPI_WriteData(0xE5);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x88);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x04);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB8);
SPI_WriteData(0x00);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB6);
SPI_WriteData(0x03);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0x8B);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0x15);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0x0C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0x0C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x01);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE0);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE1);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDC);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDD);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCD);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC9);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x03);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0x2C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDE);
SPI_WriteData(0x2C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCA);
SPI_WriteData(0x42);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD6);
SPI_WriteData(0x88);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD7);
SPI_WriteData(0x08);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD2);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD3);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x05);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x52);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB8);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD5);
SPI_WriteData(0x32);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0x16);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0x24);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0x25);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0x31);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0x2A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0x33);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC9);
SPI_WriteData(0x37);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCA);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCD);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCE);
SPI_WriteData(0x2E);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCF);
SPI_WriteData(0x29);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD0);
SPI_WriteData(0x04);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD2);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD3);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD4);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD5);
SPI_WriteData(0x26);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD6);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD7);
SPI_WriteData(0x31);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD8);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD9);
SPI_WriteData(0x3D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDA);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDB);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDC);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDD);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDE);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDF);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE0);
SPI_WriteData(0x35);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE1);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE2);
SPI_WriteData(0x0A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x06);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB8);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0x33);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x07);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0xF5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBB);
SPI_WriteData(0x74);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0xEF);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBD);
SPI_WriteData(0xF1);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBE);
SPI_WriteData(0x6B);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0xE3);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x6B);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x20);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x6A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0x8A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0xA6);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0xB5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0xC6);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0xDA);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0xE4);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0xE8);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x08);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0xFF);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBB);
SPI_WriteData(0x81);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0x01);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBD);
SPI_WriteData(0x03);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBE);
SPI_WriteData(0x82);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0xAf);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x41);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x87);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0xC2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0xD2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0xE4);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0xF7);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0xFC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0xFC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x09);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB9);
SPI_WriteData(0xB7);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0xFD);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBB);
SPI_WriteData(0x83);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0x05);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBD);
SPI_WriteData(0x07);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBE);
SPI_WriteData(0x86);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0xFE);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0xAB);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x40);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x87);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0xA2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0xBC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0xCC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0xDD);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0xF2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0xF8);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0xFA);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x04);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x1E);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xC9);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCA);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCD);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCE);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCF);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD0);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD1);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD2);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD3);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD4);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD5);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD6);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD7);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD8);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD9);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDA);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDB);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDC);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDD);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDE);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDF);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE0);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE2);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE3);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE4);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE5);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x0C);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x08);

}
void fun2(void)
{
SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0x40);
SPI_WriteData(0x82);
SPI_WriteData(0x01);
SPI_WriteData(0x90);
SPI_WriteData(0x60);
SPI_WriteData(0x00);
SPI_WriteData(0x24);
SPI_WriteData(0xD0);
SPI_WriteData(0x01);
SPI_WriteData(0x09);
SPI_WriteData(0x74);
SPI_WriteData(0x40);
SPI_WriteData(0x02);
SPI_WriteData(0x1D);
SPI_WriteData(0x90);
SPI_WriteData(0x40);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0x07);
SPI_WriteData(0x24);
SPI_WriteData(0xD0);
SPI_WriteData(0x01);
SPI_WriteData(0x09);
SPI_WriteData(0x1E);
SPI_WriteData(0x46);
SPI_WriteData(0x1E);
SPI_WriteData(0x46);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0xC5);
SPI_WriteData(0x0F);
SPI_WriteData(0x00);
SPI_WriteData(0xC0);

SSD2828_WritePackageSize(13);
SPI_WriteData(0xF0);
SPI_WriteData(0x10);
SPI_WriteData(0x40);
SPI_WriteData(0x26);
SPI_WriteData(0x4E);
SPI_WriteData(0x46);
SPI_WriteData(0x02);
SPI_WriteData(0xC8);
SPI_WriteData(0x20);
SPI_WriteData(0x80);
SPI_WriteData(0x0C);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

//Blank20
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x01);
SPI_WriteData(0x02);
SPI_WriteData(0x40);
SPI_WriteData(0x2C);
SPI_WriteData(0x99);
SPI_WriteData(0xDF);
SPI_WriteData(0xEF);
SPI_WriteData(0xF7);
SPI_WriteData(0xD3);
SPI_WriteData(0x1A);
SPI_WriteData(0x03);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x3B);
SPI_WriteData(0x84);
SPI_WriteData(0x98);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0xA0);
SPI_WriteData(0xD5);
SPI_WriteData(0x1A);
SPI_WriteData(0x10);
SPI_WriteData(0x0F);
SPI_WriteData(0xB4);
SPI_WriteData(0x5A);
SPI_WriteData(0x03);
SPI_WriteData(0x76);
SPI_WriteData(0x81);
SPI_WriteData(0x56);
SPI_WriteData(0x4B);
SPI_WriteData(0xC0);
SPI_WriteData(0x1E);
SPI_WriteData(0xD0);
SPI_WriteData(0x6A);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x09);
SPI_WriteData(0xD0);
SPI_WriteData(0x0C);
SPI_WriteData(0xBF);
SPI_WriteData(0x1F);
SPI_WriteData(0x01);
SPI_WriteData(0x9A);
SPI_WriteData(0xE1);
SPI_WriteData(0xF7);
SPI_WriteData(0x23);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x07);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x77);
SPI_WriteData(0x08);
SPI_WriteData(0x77);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x08);
SPI_WriteData(0x05);
SPI_WriteData(0x00);
SPI_WriteData(0x30);
SPI_WriteData(0x18);
SPI_WriteData(0x0C);
SPI_WriteData(0xCF);
SPI_WriteData(0x01);
SPI_WriteData(0xAD);
SPI_WriteData(0x91);
SPI_WriteData(0x04);
SPI_WriteData(0xC3);
SPI_WriteData(0x00);
SPI_WriteData(0xF4);
SPI_WriteData(0x0C);
SPI_WriteData(0xD0);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0x1A);
SPI_WriteData(0x49);
SPI_WriteData(0x30);
SPI_WriteData(0x0C);
SPI_WriteData(0x40);
SPI_WriteData(0x4F);
SPI_WriteData(0x00);
SPI_WriteData(0xAD);
SPI_WriteData(0x91);
SPI_WriteData(0x04);
SPI_WriteData(0xC3);
SPI_WriteData(0x00);
SPI_WriteData(0xF4);
SPI_WriteData(0x14);
SPI_WriteData(0xD0);
SPI_WriteData(0x1A);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0x49);
SPI_WriteData(0x30);
SPI_WriteData(0x0C);
SPI_WriteData(0x40);
SPI_WriteData(0x4F);
SPI_WriteData(0x02);
SPI_WriteData(0xAD);
SPI_WriteData(0x91);
SPI_WriteData(0x04);
SPI_WriteData(0xC3);
SPI_WriteData(0x00);
SPI_WriteData(0xF4);
SPI_WriteData(0x34);
SPI_WriteData(0xD0);
SPI_WriteData(0x1A);
SPI_WriteData(0x49);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xF0);
SPI_WriteData(0x30);
SPI_WriteData(0x0C);
SPI_WriteData(0x40);
SPI_WriteData(0x4F);
SPI_WriteData(0x04);
SPI_WriteData(0xAD);
SPI_WriteData(0x91);
SPI_WriteData(0x04);
SPI_WriteData(0xC3);
SPI_WriteData(0x00);
SPI_WriteData(0xF4);
SPI_WriteData(0x54);
SPI_WriteData(0xD0);
SPI_WriteData(0x1A);
SPI_WriteData(0x49);
SPI_WriteData(0x30);

//Blank21
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x15);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x0C);
SPI_WriteData(0x40);
SPI_WriteData(0x40);
SPI_WriteData(0x80);
SPI_WriteData(0xDF);
SPI_WriteData(0x0F);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x1C);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x08);
SPI_WriteData(0x42);
SPI_WriteData(0x60);
SPI_WriteData(0x0E);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x60);
SPI_WriteData(0x0F);
SPI_WriteData(0x14);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x2C);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0xCB);
SPI_WriteData(0x34);
SPI_WriteData(0x1D);
SPI_WriteData(0x47);
SPI_WriteData(0x51);
SPI_WriteData(0x0C);
SPI_WriteData(0x43);
SPI_WriteData(0x10);
SPI_WriteData(0x38);
SPI_WriteData(0xAE);
SPI_WriteData(0xEB);
SPI_WriteData(0x24);
SPI_WriteData(0xA9);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xF0);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0x29);
SPI_WriteData(0xCA);
SPI_WriteData(0x34);
SPI_WriteData(0x19);
SPI_WriteData(0x06);
SPI_WriteData(0x41);
SPI_WriteData(0x08);
SPI_WriteData(0x02);
SPI_WriteData(0x00);
SPI_WriteData(0x38);
SPI_WriteData(0xAE);
SPI_WriteData(0xEB);
SPI_WriteData(0x20);

//Blank22
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x16);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0xA8);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0xDB);
SPI_WriteData(0xB6);
SPI_WriteData(0x6D);
SPI_WriteData(0x01);
SPI_WriteData(0x03);
SPI_WriteData(0x03);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0xC0);
SPI_WriteData(0x1F);
SPI_WriteData(0xE1);
SPI_WriteData(0x01);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x28);
SPI_WriteData(0x02);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0x06);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x01);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xF0);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

//Blank23
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x17);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x20);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x10);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x10);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x40);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x01);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x10);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(7);
SPI_WriteData(0xD0);
SPI_WriteData(0x00);
SPI_WriteData(0x01);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

//Blank24
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x18);
}

void fun3(void)
{
SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xD4);
SPI_WriteData(0x7F);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x7A);
SPI_WriteData(0x83);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0xFE);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xFE);
SPI_WriteData(0xD4);
SPI_WriteData(0x7F);
SPI_WriteData(0xD4);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xF0);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xD4);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
}


void fun4(void)
{

//Blank25
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x19);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0xAA);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);
SPI_WriteData(0x7F);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x7F);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x79);
SPI_WriteData(0x86);
SPI_WriteData(0x7A);
SPI_WriteData(0x83);
SPI_WriteData(0x7A);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7A);
SPI_WriteData(0x85);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7B);
SPI_WriteData(0x84);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);
SPI_WriteData(0x83);
SPI_WriteData(0x7C);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x83);
SPI_WriteData(0x7F);
SPI_WriteData(0x04);
SPI_WriteData(0xFF);
SPI_WriteData(0x1E);
SPI_WriteData(0x00);
SPI_WriteData(0x08);
SPI_WriteData(0x10);
SPI_WriteData(0x18);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0xFC);
SPI_WriteData(0x00);
SPI_WriteData(0x04);

SSD2828_WritePackageSize(12);
SPI_WriteData(0xD0);
SPI_WriteData(0x20);
SPI_WriteData(0x00);
SPI_WriteData(0x01);
SPI_WriteData(0x08);
SPI_WriteData(0x40);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0x10);
SPI_WriteData(0x80);
SPI_WriteData(0x00);
SPI_WriteData(0xFC);

//Blank26
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x1A);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0xF0);
SPI_WriteData(0xD9);
SPI_WriteData(0xC8);
SPI_WriteData(0xBA);
SPI_WriteData(0xAF);
SPI_WriteData(0xA6);
SPI_WriteData(0x9E);
SPI_WriteData(0x98);
SPI_WriteData(0x92);
SPI_WriteData(0x8D);
SPI_WriteData(0x88);
SPI_WriteData(0x84);
SPI_WriteData(0x00);
SPI_WriteData(0x60);
SPI_WriteData(0xF6);
SPI_WriteData(0xCF);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0xFC);
SPI_WriteData(0x6F);
SPI_WriteData(0xF6);
SPI_WriteData(0xEF);
SPI_WriteData(0xCF);
SPI_WriteData(0xAF);
SPI_WriteData(0x5F);
SPI_WriteData(0x55);
SPI_WriteData(0x00);
SPI_WriteData(0xF8);
SPI_WriteData(0x00);
SPI_WriteData(0xF8);
SPI_WriteData(0x00);
SPI_WriteData(0xF8);
SPI_WriteData(0xAD);
SPI_WriteData(0x8D);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x73);
SPI_WriteData(0x60);
SPI_WriteData(0x53);
SPI_WriteData(0x4A);
SPI_WriteData(0x43);
SPI_WriteData(0x7F);
SPI_WriteData(0x78);
SPI_WriteData(0x10);
SPI_WriteData(0xA0);
SPI_WriteData(0x3F);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(9);
SPI_WriteData(0xC0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

//Blank28
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x1C);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x08);
SPI_WriteData(0x0C);
SPI_WriteData(0x00);
SPI_WriteData(0x10);
SPI_WriteData(0x14);
SPI_WriteData(0x18);
SPI_WriteData(0x1C);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x00);
SPI_WriteData(0x40);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x00);
SPI_WriteData(0x60);
SPI_WriteData(0x68);
SPI_WriteData(0x70);
SPI_WriteData(0x78);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x88);
SPI_WriteData(0x90);
SPI_WriteData(0x98);
SPI_WriteData(0x00);
SPI_WriteData(0xA0);
SPI_WriteData(0xA8);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0xB0);
SPI_WriteData(0xB8);
SPI_WriteData(0x00);
SPI_WriteData(0xC0);
SPI_WriteData(0xC8);
SPI_WriteData(0xD0);
SPI_WriteData(0xD8);
SPI_WriteData(0x00);
SPI_WriteData(0xE0);
SPI_WriteData(0xE8);
SPI_WriteData(0xF0);
SPI_WriteData(0xF8);
SPI_WriteData(0x00);
SPI_WriteData(0xFC);
SPI_WriteData(0xFE);
SPI_WriteData(0xFF);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x08);
SPI_WriteData(0x0C);
SPI_WriteData(0x00);
SPI_WriteData(0x10);
SPI_WriteData(0x14);
SPI_WriteData(0x18);
SPI_WriteData(0x1C);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x00);
SPI_WriteData(0x60);
SPI_WriteData(0x68);
SPI_WriteData(0x70);
SPI_WriteData(0x78);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x88);
SPI_WriteData(0x90);
SPI_WriteData(0x98);
SPI_WriteData(0x00);
SPI_WriteData(0xA0);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0xA8);
SPI_WriteData(0xB0);
SPI_WriteData(0xB8);
SPI_WriteData(0x00);
SPI_WriteData(0xC0);
SPI_WriteData(0xC8);
SPI_WriteData(0xD0);
SPI_WriteData(0xD8);
SPI_WriteData(0x00);
SPI_WriteData(0xE0);
SPI_WriteData(0xE8);
SPI_WriteData(0xF0);
SPI_WriteData(0xF8);
SPI_WriteData(0x00);
SPI_WriteData(0xFC);
SPI_WriteData(0xFE);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0xFF);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x08);
SPI_WriteData(0x0C);
SPI_WriteData(0x00);
SPI_WriteData(0x10);
SPI_WriteData(0x14);
SPI_WriteData(0x18);
SPI_WriteData(0x1C);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xF0);
SPI_WriteData(0x00);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x00);
SPI_WriteData(0x60);
SPI_WriteData(0x68);
SPI_WriteData(0x70);
SPI_WriteData(0x78);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x88);
SPI_WriteData(0x90);
SPI_WriteData(0x98);
SPI_WriteData(0x00);

//Blank29
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x1D);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0xA0);
SPI_WriteData(0xA8);
SPI_WriteData(0xB0);
SPI_WriteData(0xB8);
SPI_WriteData(0x00);
SPI_WriteData(0xC0);
SPI_WriteData(0xC8);
SPI_WriteData(0xD0);
SPI_WriteData(0xD8);
SPI_WriteData(0x00);
SPI_WriteData(0xE0);
SPI_WriteData(0xE8);
SPI_WriteData(0xF0);
SPI_WriteData(0xF8);
SPI_WriteData(0x00);
SPI_WriteData(0xFC);

SSD2828_WritePackageSize(5);
SPI_WriteData(0x90);
SPI_WriteData(0xFE);
SPI_WriteData(0xFF);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

//Blank31
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x1F);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x5A);
SPI_WriteData(0x0F);
SPI_WriteData(0x70);
SPI_WriteData(0x09);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x40);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x38);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x40);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x40);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x58);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x60);
SPI_WriteData(0x20);
SPI_WriteData(0x28);
SPI_WriteData(0x30);
SPI_WriteData(0x38);
SPI_WriteData(0x40);
SPI_WriteData(0x48);
SPI_WriteData(0x50);
SPI_WriteData(0x58);
SPI_WriteData(0xFF);
SPI_WriteData(0x5A);
SPI_WriteData(0x1E);
SPI_WriteData(0x20);

SSD2828_WritePackageSize(13);
SPI_WriteData(0xD0);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0x20);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0x20);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0x20);
SPI_WriteData(0x00);
SPI_WriteData(0x02);
SPI_WriteData(0xFE);

//Blank32
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x20);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x47);
SPI_WriteData(0x73);
SPI_WriteData(0x03);
SPI_WriteData(0x00);
SPI_WriteData(0x0A);
SPI_WriteData(0xF6);
SPI_WriteData(0xFF);
SPI_WriteData(0xC3);
SPI_WriteData(0x10);
SPI_WriteData(0x08);
SPI_WriteData(0x02);
SPI_WriteData(0x08);
SPI_WriteData(0x03);
SPI_WriteData(0x41);
SPI_WriteData(0x18);
SPI_WriteData(0x30);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x18);
SPI_WriteData(0x44);
SPI_WriteData(0xE1);
SPI_WriteData(0x40);
SPI_WriteData(0xE1);
SPI_WriteData(0x20);
SPI_WriteData(0x30);
SPI_WriteData(0x18);
SPI_WriteData(0xC8);
SPI_WriteData(0x21);
SPI_WriteData(0x41);
SPI_WriteData(0x01);
SPI_WriteData(0x31);
SPI_WriteData(0x13);
SPI_WriteData(0x44);
SPI_WriteData(0x42);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x91);
SPI_WriteData(0x50);
SPI_WriteData(0x28);
SPI_WriteData(0x14);
SPI_WriteData(0x0A);
SPI_WriteData(0x85);
SPI_WriteData(0x83);
SPI_WriteData(0xD2);
SPI_WriteData(0xC0);
SPI_WriteData(0x40);
SPI_WriteData(0x36);
SPI_WriteData(0x7F);
SPI_WriteData(0xD0);
SPI_WriteData(0x1F);
SPI_WriteData(0x12);
SPI_WriteData(0xE0);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x18);
SPI_WriteData(0x36);
SPI_WriteData(0x1B);
SPI_WriteData(0x11);
SPI_WriteData(0x04);
SPI_WriteData(0x20);
SPI_WriteData(0x02);
SPI_WriteData(0xD0);
SPI_WriteData(0x80);
SPI_WriteData(0xB3);
SPI_WriteData(0x21);
SPI_WriteData(0x38);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x88);
SPI_WriteData(0x83);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x82);
SPI_WriteData(0x81);
SPI_WriteData(0x40);
SPI_WriteData(0x70);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x8D);
SPI_WriteData(0x0D);
SPI_WriteData(0xA4);
SPI_WriteData(0xA2);
SPI_WriteData(0x00);
SPI_WriteData(0x80);
SPI_WriteData(0x04);
SPI_WriteData(0x38);
SPI_WriteData(0x00);
SPI_WriteData(0x50);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0x80);
SPI_WriteData(0x13);
SPI_WriteData(0xE0);
SPI_WriteData(0x00);
SPI_WriteData(0x1C);
SPI_WriteData(0x80);
SPI_WriteData(0x50);
SPI_WriteData(0x30);
SPI_WriteData(0x00);
SPI_WriteData(0xE0);
SPI_WriteData(0x81);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x28);
SPI_WriteData(0x0E);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xE0);
SPI_WriteData(0x83);
SPI_WriteData(0x99);
SPI_WriteData(0x99);
SPI_WriteData(0x99);
SPI_WriteData(0x99);
SPI_WriteData(0x99);
SPI_WriteData(0x99);
SPI_WriteData(0x88);
SPI_WriteData(0x88);
SPI_WriteData(0x88);
SPI_WriteData(0x88);
SPI_WriteData(0x88);
SPI_WriteData(0x48);
SPI_WriteData(0x08);
SPI_WriteData(0x82);
SPI_WriteData(0xC6);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xF0);
SPI_WriteData(0xE0);
SPI_WriteData(0x13);
SPI_WriteData(0xFF);
SPI_WriteData(0xC4);
SPI_WriteData(0x7F);
SPI_WriteData(0x31);
SPI_WriteData(0x43);
SPI_WriteData(0x88);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x40);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x18);

//Blank33
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x21);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x04);
SPI_WriteData(0x41);
SPI_WriteData(0xA6);
SPI_WriteData(0x6D);
SPI_WriteData(0x92);
SPI_WriteData(0x04);
SPI_WriteData(0x49);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x49);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x20);
SPI_WriteData(0x49);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x90);
SPI_WriteData(0x92);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x85);
SPI_WriteData(0x11);
SPI_WriteData(0x0C);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x40);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x16);
SPI_WriteData(0x00);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xA0);
SPI_WriteData(0x00);
SPI_WriteData(0x08);
SPI_WriteData(0x08);
SPI_WriteData(0x14);
SPI_WriteData(0x10);
SPI_WriteData(0x49);
SPI_WriteData(0x92);
SPI_WriteData(0x24);
SPI_WriteData(0x49);
SPI_WriteData(0x28);
SPI_WriteData(0x20);
SPI_WriteData(0x92);
SPI_WriteData(0x24);
SPI_WriteData(0x49);
SPI_WriteData(0x92);
SPI_WriteData(0x50);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xB0);
SPI_WriteData(0x40);
SPI_WriteData(0x24);
SPI_WriteData(0x49);
SPI_WriteData(0x92);
SPI_WriteData(0x24);
SPI_WriteData(0x49);
SPI_WriteData(0x92);
SPI_WriteData(0x24);
SPI_WriteData(0x09);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x55);
SPI_WriteData(0x10);
SPI_WriteData(0x01);
SPI_WriteData(0x08);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xC0);
SPI_WriteData(0x01);
SPI_WriteData(0x42);
SPI_WriteData(0x01);
SPI_WriteData(0x31);
SPI_WriteData(0x20);
SPI_WriteData(0x02);
SPI_WriteData(0x10);
SPI_WriteData(0x10);
SPI_WriteData(0x01);
SPI_WriteData(0x08);
SPI_WriteData(0x88);
SPI_WriteData(0x00);
SPI_WriteData(0x04);
SPI_WriteData(0x44);
SPI_WriteData(0x00);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(17);
SPI_WriteData(0xD0);
SPI_WriteData(0x22);
SPI_WriteData(0x00);
SPI_WriteData(0x01);
SPI_WriteData(0xA2);
SPI_WriteData(0x80);
SPI_WriteData(0x80);
SPI_WriteData(0x08);
SPI_WriteData(0x40);
SPI_WriteData(0x40);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x18);
SPI_WriteData(0x00);
SPI_WriteData(0x16);

SSD2828_WritePackageSize(3);
SPI_WriteData(0xE0);
SPI_WriteData(0x10);
SPI_WriteData(0x00);

//Blank34
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x22);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x29);
SPI_WriteData(0xD3);
SPI_WriteData(0x00);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x55);
SPI_WriteData(0x1F);
SPI_WriteData(0x70);

SSD2828_WritePackageSize(4);
SPI_WriteData(0x90);
SPI_WriteData(0xF0);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

//Blank35
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x23);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x09);
SPI_WriteData(0x01);
SPI_WriteData(0x02);
SPI_WriteData(0x05);
SPI_WriteData(0x00);
SPI_WriteData(0x05);
SPI_WriteData(0x04);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(10);
SPI_WriteData(0x90);
SPI_WriteData(0x00);
SPI_WriteData(0xFF);
SPI_WriteData(0x1F);
SPI_WriteData(0x20);
SPI_WriteData(0x00);
SPI_WriteData(0x01);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0xFE);

//Blank36
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x24);

SSD2828_WritePackageSize(17);
SPI_WriteData(0x80);
SPI_WriteData(0x00);
SPI_WriteData(0x03);
SPI_WriteData(0x00);
SPI_WriteData(0xFF);
SPI_WriteData(0xFF);
SPI_WriteData(0x66);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x08);
SPI_WriteData(0x2A);

SSD2828_WritePackageSize(15);
SPI_WriteData(0x90);
SPI_WriteData(0x5A);
SPI_WriteData(0xA5);
SPI_WriteData(0x5A);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x22);
SPI_WriteData(0x22);
SPI_WriteData(0x3A);
SPI_WriteData(0x22);
SPI_WriteData(0x00);
SPI_WriteData(0x00);
SPI_WriteData(0x00);



//SPInotFINISH
//SSD2828_WritePackageSize(1);
//SPI_WriteData(0x90);
//SPI_WriteData(0x5A);

//SPIFINISH

SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x24);

SSD2828_WritePackageSize(2);
SPI_WriteData(0x90);
SPI_WriteData(0xA5);


//Blankselect2F
SSD2828_WritePackageSize(3);
SPI_WriteData(0x41);
SPI_WriteData(0x5A);
SPI_WriteData(0x2F);

//INTCANCEL__TP_I2Cmode
SSD2828_WritePackageSize(2);
SPI_WriteData(0x4C);
SPI_WriteData(0x03);

//BypassorFIFOmode
SSD2828_WritePackageSize(2);
SPI_WriteData(0x09);
SPI_WriteData(0x01);

//CMD1LEDPWMset
SSD2828_WritePackageSize(3);
SPI_WriteData(0x51);
SPI_WriteData(0xff);
SPI_WriteData(0x0f);

SSD2828_WritePackageSize(2);
SPI_WriteData(0x53);
SPI_WriteData(0x24);

SSD2828_WritePackageSize(2);
SPI_WriteData(0x55);
SPI_WriteData(0x00);
}
void Initial_LCM_CODE(void)
{

SPI_WriteCmd(0xB7);
	SPI_WriteData(0x10);//10=TX_CLK 30=PCLK
	SPI_WriteData(0x02);


	SPI_WriteCmd(0xBD);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x05);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB1);
SPI_WriteData(0xE5);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x88);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x04);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB8);
SPI_WriteData(0x00);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB6);
SPI_WriteData(0x03);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0x8B);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0x15);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0x0C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0x0C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x01);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE0);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE1);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDC);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDD);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCD);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC9);
SPI_WriteData(0x10);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x03);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0x2C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDE);
SPI_WriteData(0x2C);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCA);
SPI_WriteData(0x42);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD6);
SPI_WriteData(0x88);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD7);
SPI_WriteData(0x08);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD2);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD3);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x05);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x52);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB8);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD5);
SPI_WriteData(0x32);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0x16);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0x24);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0x25);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0x31);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0x2A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0x33);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC9);
SPI_WriteData(0x37);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCA);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCD);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCE);
SPI_WriteData(0x2E);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCF);
SPI_WriteData(0x29);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD0);
SPI_WriteData(0x04);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD2);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD3);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD4);
SPI_WriteData(0x14);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD5);
SPI_WriteData(0x26);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD6);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD7);
SPI_WriteData(0x31);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD8);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD9);
SPI_WriteData(0x3D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDA);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDB);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDC);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDD);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDE);
SPI_WriteData(0x3F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDF);
SPI_WriteData(0x38);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE0);
SPI_WriteData(0x35);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE1);
SPI_WriteData(0x2D);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE2);
SPI_WriteData(0x0A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x06);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB8);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0x33);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x07);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0xF5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBB);
SPI_WriteData(0x74);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0xEF);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBD);
SPI_WriteData(0xF1);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBE);
SPI_WriteData(0x6B);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0xE3);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x6B);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x20);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x6A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0x8A);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0xA6);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0xB5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0xC6);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0xDA);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0xE4);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0xE8);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x08);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0xFF);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBB);
SPI_WriteData(0x81);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0x01);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBD);
SPI_WriteData(0x03);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBE);
SPI_WriteData(0x82);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0x02);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0xAf);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x41);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x87);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0xA5);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0xC2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0xD2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0xE4);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0xF7);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0xFC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0xFC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x09);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB9);
SPI_WriteData(0xB7);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBA);
SPI_WriteData(0xFD);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBB);
SPI_WriteData(0x83);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBC);
SPI_WriteData(0x05);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBD);
SPI_WriteData(0x07);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBE);
SPI_WriteData(0x86);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xBF);
SPI_WriteData(0xFE);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x06);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0xAB);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC0);
SPI_WriteData(0x40);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x87);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC2);
SPI_WriteData(0xA2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC3);
SPI_WriteData(0xBC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC4);
SPI_WriteData(0xCC);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC5);
SPI_WriteData(0xDD);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC6);
SPI_WriteData(0xF2);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC7);
SPI_WriteData(0xF8);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xC8);
SPI_WriteData(0xFA);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x04);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xC1);
SPI_WriteData(0x1E);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xC9);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCA);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCB);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCC);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCD);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCE);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xCF);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD0);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD1);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD2);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD3);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD4);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD5);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD6);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD7);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD8);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xD9);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDA);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDB);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDC);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDD);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDE);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xDF);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE0);
SPI_WriteData(0x00);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE2);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE3);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE4);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xE5);
SPI_WriteData(0x0F);

SSD2828_WritePackageSize(2);
SPI_WriteData(0xB0);
SPI_WriteData(0x00);
 
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x0C);
  
SSD2828_WritePackageSize(2);
SPI_WriteData(0xB3);
SPI_WriteData(0x08);
  



//SSD2828_WritePackageSize(2);
//SPI_WriteData(0x02);
//SPI_WriteData(0x5A);
bsp_DelayMS(40);
SSD2828_WritePackageSize(1);
SPI_WriteData(0x11);
bsp_DelayMS(140);
SSD2828_WritePackageSize(1);
SPI_WriteData(0x29);
bsp_DelayMS(40);



}










