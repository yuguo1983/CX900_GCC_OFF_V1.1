#include "pport_spi.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "mipi_Cfg.h"
#include "lcd_cfg.h"

 
void Initial_LCM_CODE(void){



	SPI_WriteCmd(0xB7);
	SPI_WriteData(0x10);//10=TX_CLK 30=PCLK
	SPI_WriteData(0x02);

	SPI_WriteCmd(0xBD);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);////*/SSD2828_WritePackageSize

	

//-------------  Display Initial Code Setting  -------------------------
//Stop reload
SSD2828_WritePackageSize(2);SPI_WriteData(0x41);SPI_WriteData(0x5A);
 
//INT CANCEL__SPI mode
//      GEN_WR(0x4C);SPI_WriteData(0x03);
 
//VCOM
        //GEN_WR(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x03);
        //GEN_WR(0x80);SPI_WriteData(0x32);

//Blank 8
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x08);
SSD2828_WritePackageSize(5);SPI_WriteData(0x80);SPI_WriteData(0x82);SPI_WriteData(0x00);SPI_WriteData(0x82);SPI_WriteData(0x00);
//Blank 9
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x09);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x1A);SPI_WriteData(0x01);SPI_WriteData(0x2B);SPI_WriteData(0x93);SPI_WriteData(0xA5);SPI_WriteData(0x97);SPI_WriteData(0x59);SPI_WriteData(0x2A);SPI_WriteData(0xB1);SPI_WriteData(0x07);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0xDF);SPI_WriteData(0x80);SPI_WriteData(0x10);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x42);SPI_WriteData(0x44);SPI_WriteData(0x84);SPI_WriteData(0x14);SPI_WriteData(0xC6);SPI_WriteData(0x23);SPI_WriteData(0x9A);SPI_WriteData(0x11);SPI_WriteData(0xC0);SPI_WriteData(0xFB);SPI_WriteData(0x43);SPI_WriteData(0xAE);SPI_WriteData(0x07);SPI_WriteData(0x60);SPI_WriteData(0x28);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x80);SPI_WriteData(0x90);SPI_WriteData(0x20);SPI_WriteData(0xAA);SPI_WriteData(0x00);SPI_WriteData(0x04);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x05);SPI_WriteData(0x00);SPI_WriteData(0x0F);SPI_WriteData(0x15);SPI_WriteData(0x42);SPI_WriteData(0x00);SPI_WriteData(0xFE);SPI_WriteData(0xFF);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x03);SPI_WriteData(0xDB);SPI_WriteData(0xC7);SPI_WriteData(0x00);SPI_WriteData(0xFF);SPI_WriteData(0x00);SPI_WriteData(0xFF);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x41);SPI_WriteData(0x25);SPI_WriteData(0x00);SPI_WriteData(0x4A);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x04);SPI_WriteData(0x02);SPI_WriteData(0x00);SPI_WriteData(0x07);SPI_WriteData(0x00);SPI_WriteData(0x08);SPI_WriteData(0x18);
SSD2828_WritePackageSize(3);SPI_WriteData(0xD0);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 10
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x0A);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xA5);SPI_WriteData(0xA5);SPI_WriteData(0xD4);SPI_WriteData(0x0C);SPI_WriteData(0x21);SPI_WriteData(0x27);SPI_WriteData(0x3B);SPI_WriteData(0x47);SPI_WriteData(0x53);SPI_WriteData(0x67);SPI_WriteData(0x75);SPI_WriteData(0x78);SPI_WriteData(0x85);SPI_WriteData(0x87);SPI_WriteData(0x9C);SPI_WriteData(0x68);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x56);SPI_WriteData(0x58);SPI_WriteData(0x4E);SPI_WriteData(0x48);SPI_WriteData(0x3D);SPI_WriteData(0x30);SPI_WriteData(0x28);SPI_WriteData(0x21);SPI_WriteData(0x14);SPI_WriteData(0x10);SPI_WriteData(0x0D);SPI_WriteData(0x0C);SPI_WriteData(0x21);SPI_WriteData(0x27);SPI_WriteData(0x3B);SPI_WriteData(0x47);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x53);SPI_WriteData(0x67);SPI_WriteData(0x75);SPI_WriteData(0x78);SPI_WriteData(0x85);SPI_WriteData(0x87);SPI_WriteData(0x9C);SPI_WriteData(0x68);SPI_WriteData(0x56);SPI_WriteData(0x58);SPI_WriteData(0x4E);SPI_WriteData(0x48);SPI_WriteData(0x3D);SPI_WriteData(0x30);SPI_WriteData(0x28);SPI_WriteData(0x21);
SSD2828_WritePackageSize(4);SPI_WriteData(0xB0);SPI_WriteData(0x14);SPI_WriteData(0x10);SPI_WriteData(0x0D);
//Blank 11
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x0B);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x50);SPI_WriteData(0xB5);SPI_WriteData(0xC5);SPI_WriteData(0xAA);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xA0);SPI_WriteData(0x6A);SPI_WriteData(0x8B);SPI_WriteData(0xA5);SPI_WriteData(0xAE);SPI_WriteData(0x22);SPI_WriteData(0x02);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x0F);SPI_WriteData(0xD8);SPI_WriteData(0xB8);SPI_WriteData(0xF7);SPI_WriteData(0x25);SPI_WriteData(0x70);SPI_WriteData(0xE0);SPI_WriteData(0x08);SPI_WriteData(0x11);SPI_WriteData(0x02);SPI_WriteData(0x40);SPI_WriteData(0x13);SPI_WriteData(0x4F);SPI_WriteData(0x4D);SPI_WriteData(0x3C);SPI_WriteData(0x35);
SSD2828_WritePackageSize(9);SPI_WriteData(0xA0);SPI_WriteData(0xF1);SPI_WriteData(0xA4);SPI_WriteData(0x06);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0x00);SPI_WriteData(0x03);SPI_WriteData(0x00);
//Blank 12
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x0C);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xFA);SPI_WriteData(0x68);SPI_WriteData(0xF4);SPI_WriteData(0xA1);SPI_WriteData(0xAF);SPI_WriteData(0xF7);SPI_WriteData(0xC1);SPI_WriteData(0x07);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x56);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x55);SPI_WriteData(0x61);SPI_WriteData(0x15);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x55);SPI_WriteData(0x51);SPI_WriteData(0x15);SPI_WriteData(0x56);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x56);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x55);SPI_WriteData(0x61);SPI_WriteData(0x15);SPI_WriteData(0x55);SPI_WriteData(0x51);SPI_WriteData(0x15);SPI_WriteData(0x56);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0xD1);SPI_WriteData(0x87);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x40);SPI_WriteData(0x94);SPI_WriteData(0x02);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x30);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x28);SPI_WriteData(0x15);SPI_WriteData(0x80);SPI_WriteData(0x04);SPI_WriteData(0x00);SPI_WriteData(0x18);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x30);SPI_WriteData(0x0A);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(8);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x01);SPI_WriteData(0x05);SPI_WriteData(0xC2);SPI_WriteData(0xB0);SPI_WriteData(0x00);SPI_WriteData(0x05);
//Blank 13
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x0D);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x08);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x28);SPI_WriteData(0x02);SPI_WriteData(0x00);SPI_WriteData(0x04);SPI_WriteData(0x9F);SPI_WriteData(0x00);SPI_WriteData(0x0B);SPI_WriteData(0x02);SPI_WriteData(0x77);SPI_WriteData(0x01);SPI_WriteData(0xB1);SPI_WriteData(0x10);SPI_WriteData(0xF0);
SSD2828_WritePackageSize(7);SPI_WriteData(0x90);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x58);SPI_WriteData(0x16);SPI_WriteData(0x04);SPI_WriteData(0xA1);
//Blank 14
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x0E);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xFF);SPI_WriteData(0x81);SPI_WriteData(0x68);SPI_WriteData(0xEC);SPI_WriteData(0x24);SPI_WriteData(0xFD);SPI_WriteData(0x22);SPI_WriteData(0x00);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x05);SPI_WriteData(0x5A);SPI_WriteData(0x5A);SPI_WriteData(0x80);
SSD2828_WritePackageSize(7);SPI_WriteData(0x90);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x60);SPI_WriteData(0x01);SPI_WriteData(0x00);
//Blank 15
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x0F);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x01);SPI_WriteData(0x91);SPI_WriteData(0xC3);SPI_WriteData(0x04);SPI_WriteData(0x01);SPI_WriteData(0x24);SPI_WriteData(0x30);SPI_WriteData(0x41);SPI_WriteData(0x00);SPI_WriteData(0x09);SPI_WriteData(0x70);SPI_WriteData(0x06);SPI_WriteData(0x12);SPI_WriteData(0x00);SPI_WriteData(0xE4);SPI_WriteData(0x42);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x1C);SPI_WriteData(0x78);SPI_WriteData(0x11);SPI_WriteData(0xC0);SPI_WriteData(0x07);SPI_WriteData(0x1C);SPI_WriteData(0x00);SPI_WriteData(0xA0);SPI_WriteData(0x05);SPI_WriteData(0x5A);SPI_WriteData(0x10);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x84);SPI_WriteData(0x50);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x2D);SPI_WriteData(0xD8);SPI_WriteData(0xC2);SPI_WriteData(0x4C);SPI_WriteData(0x08);SPI_WriteData(0x58);SPI_WriteData(0x88);SPI_WriteData(0x0F);SPI_WriteData(0x86);SPI_WriteData(0xDA);SPI_WriteData(0x06);SPI_WriteData(0x00);SPI_WriteData(0x67);SPI_WriteData(0x68);SPI_WriteData(0x08);SPI_WriteData(0xE0);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x28);SPI_WriteData(0x74);SPI_WriteData(0x00);SPI_WriteData(0xA0);SPI_WriteData(0x40);SPI_WriteData(0xE2);SPI_WriteData(0x82);SPI_WriteData(0x13);SPI_WriteData(0x00);SPI_WriteData(0x88);SPI_WriteData(0xE0);SPI_WriteData(0x40);SPI_WriteData(0x00);SPI_WriteData(0x2D);SPI_WriteData(0xD0);SPI_WriteData(0x82);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x40);SPI_WriteData(0x94);SPI_WriteData(0x52);SPI_WriteData(0xC2);SPI_WriteData(0x41);SPI_WriteData(0x1C);SPI_WriteData(0x32);SPI_WriteData(0x5B);SPI_WriteData(0x07);SPI_WriteData(0x10);SPI_WriteData(0x62);SPI_WriteData(0x84);SPI_WriteData(0x28);SPI_WriteData(0x03);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0x8A);SPI_WriteData(0x88);SPI_WriteData(0x88);SPI_WriteData(0x48);SPI_WriteData(0x92);SPI_WriteData(0x09);SPI_WriteData(0x0F);SPI_WriteData(0x15);SPI_WriteData(0x1E);SPI_WriteData(0xE0);SPI_WriteData(0x31);SPI_WriteData(0x06);SPI_WriteData(0x04);SPI_WriteData(0x02);SPI_WriteData(0x14);SPI_WriteData(0x04);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0x10);SPI_WriteData(0x22);SPI_WriteData(0x22);SPI_WriteData(0xFD);SPI_WriteData(0x60);SPI_WriteData(0xCA);SPI_WriteData(0x2F);SPI_WriteData(0xA5);SPI_WriteData(0x4B);SPI_WriteData(0x39);SPI_WriteData(0x37);SPI_WriteData(0x2C);SPI_WriteData(0x65);SPI_WriteData(0x40);SPI_WriteData(0x41);SPI_WriteData(0x00);
SSD2828_WritePackageSize(16);SPI_WriteData(0xF0);SPI_WriteData(0x00);SPI_WriteData(0x15);SPI_WriteData(0x41);SPI_WriteData(0x04);SPI_WriteData(0xF5);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0x3F);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x15);SPI_WriteData(0x40);SPI_WriteData(0x14);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 16
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x10);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x03);SPI_WriteData(0xE7);SPI_WriteData(0x8F);SPI_WriteData(0x0B);SPI_WriteData(0x04);SPI_WriteData(0x32);SPI_WriteData(0x30);SPI_WriteData(0xF1);SPI_WriteData(0x67);SPI_WriteData(0x0C);SPI_WriteData(0x18);SPI_WriteData(0xC4);SPI_WriteData(0x20);SPI_WriteData(0xC5);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x1C);SPI_WriteData(0x94);SPI_WriteData(0xD4);SPI_WriteData(0x62);SPI_WriteData(0xCD);SPI_WriteData(0x3D);SPI_WriteData(0xF8);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0x0F);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);
SSD2828_WritePackageSize(3);SPI_WriteData(0xA0);SPI_WriteData(0x81);SPI_WriteData(0x00);
//Blank 17
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x11);
SSD2828_WritePackageSize(8);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);SPI_WriteData(0xFF);
//Blank 18
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x12);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x2D);SPI_WriteData(0x23);SPI_WriteData(0x05);SPI_WriteData(0xFB);SPI_WriteData(0x00);SPI_WriteData(0x2D);SPI_WriteData(0x23);SPI_WriteData(0x05);SPI_WriteData(0xFB);SPI_WriteData(0x00);
SSD2828_WritePackageSize(8);SPI_WriteData(0xB0);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 19
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x13);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x01);SPI_WriteData(0x08);SPI_WriteData(0x80);SPI_WriteData(0x15);SPI_WriteData(0x00);SPI_WriteData(0x90);SPI_WriteData(0x10);SPI_WriteData(0x19);SPI_WriteData(0x3E);SPI_WriteData(0x10);SPI_WriteData(0x00);SPI_WriteData(0xD6);SPI_WriteData(0x03);SPI_WriteData(0x04);SPI_WriteData(0x18);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x70);SPI_WriteData(0x88);SPI_WriteData(0x30);SPI_WriteData(0x90);SPI_WriteData(0x32);SPI_WriteData(0x70);SPI_WriteData(0x3E);SPI_WriteData(0x97);SPI_WriteData(0x8B);SPI_WriteData(0x39);SPI_WriteData(0x30);SPI_WriteData(0xC4);SPI_WriteData(0x09);SPI_WriteData(0xC4);SPI_WriteData(0x09);SPI_WriteData(0xC4);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x89);SPI_WriteData(0x4F);SPI_WriteData(0xB6);SPI_WriteData(0x43);SPI_WriteData(0x7D);SPI_WriteData(0x09);SPI_WriteData(0xC4);SPI_WriteData(0x09);SPI_WriteData(0xC4);SPI_WriteData(0x09);SPI_WriteData(0x7D);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x9B);SPI_WriteData(0x01);SPI_WriteData(0x21);SPI_WriteData(0x65);SPI_WriteData(0xA9);SPI_WriteData(0x43);SPI_WriteData(0x87);SPI_WriteData(0xCB);SPI_WriteData(0x21);SPI_WriteData(0x65);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0xA9);SPI_WriteData(0x43);SPI_WriteData(0x87);SPI_WriteData(0xCB);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x74);SPI_WriteData(0x0F);SPI_WriteData(0xF0);SPI_WriteData(0x00);SPI_WriteData(0x32);SPI_WriteData(0x3C);SPI_WriteData(0x80);SPI_WriteData(0x0C);SPI_WriteData(0x06);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0x40);SPI_WriteData(0x82);SPI_WriteData(0x01);SPI_WriteData(0x90);SPI_WriteData(0x60);SPI_WriteData(0x00);SPI_WriteData(0x24);SPI_WriteData(0x28);SPI_WriteData(0x82);SPI_WriteData(0x0C);SPI_WriteData(0x8A);SPI_WriteData(0x20);SPI_WriteData(0x03);SPI_WriteData(0x1D);SPI_WriteData(0x90);SPI_WriteData(0x40);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0x07);SPI_WriteData(0x24);SPI_WriteData(0xD0);SPI_WriteData(0x01);SPI_WriteData(0x09);SPI_WriteData(0x1F);SPI_WriteData(0x46);SPI_WriteData(0x1E);SPI_WriteData(0x46);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x05);SPI_WriteData(0x20);SPI_WriteData(0x80);SPI_WriteData(0xC0);
SSD2828_WritePackageSize(13);SPI_WriteData(0xF0);SPI_WriteData(0x10);SPI_WriteData(0x40);SPI_WriteData(0x26);SPI_WriteData(0x4E);SPI_WriteData(0x46);SPI_WriteData(0x02);SPI_WriteData(0xC8);SPI_WriteData(0x20);SPI_WriteData(0x80);SPI_WriteData(0x0C);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 20
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x14);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x01);SPI_WriteData(0x02);SPI_WriteData(0x40);SPI_WriteData(0x2C);SPI_WriteData(0x99);SPI_WriteData(0xDF);SPI_WriteData(0xEF);SPI_WriteData(0xF7);SPI_WriteData(0x83);SPI_WriteData(0xE0);SPI_WriteData(0x03);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xFA);SPI_WriteData(0x82);SPI_WriteData(0x50);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x41);SPI_WriteData(0x26);SPI_WriteData(0x13);SPI_WriteData(0x10);SPI_WriteData(0x17);SPI_WriteData(0xC8);SPI_WriteData(0x50);SPI_WriteData(0x03);SPI_WriteData(0x62);SPI_WriteData(0x02);SPI_WriteData(0x19);SPI_WriteData(0x6A);SPI_WriteData(0xC0);SPI_WriteData(0xE0);SPI_WriteData(0x08);SPI_WriteData(0x04);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x08);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xDB);SPI_WriteData(0x81);SPI_WriteData(0x4C);SPI_WriteData(0x26);SPI_WriteData(0x00);SPI_WriteData(0xF4);SPI_WriteData(0x05);SPI_WriteData(0x51);SPI_WriteData(0x04);SPI_WriteData(0xA0);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0xD5);SPI_WriteData(0x12);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0xF9);SPI_WriteData(0x05);SPI_WriteData(0xF9);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x05);SPI_WriteData(0x05);SPI_WriteData(0x00);SPI_WriteData(0x30);SPI_WriteData(0x18);SPI_WriteData(0x0C);SPI_WriteData(0x4F);SPI_WriteData(0x00);SPI_WriteData(0x08);SPI_WriteData(0x5E);SPI_WriteData(0x14);SPI_WriteData(0xC5);SPI_WriteData(0x00);SPI_WriteData(0xF4);SPI_WriteData(0x24);SPI_WriteData(0x80);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0xE0);SPI_WriteData(0x45);SPI_WriteData(0x51);SPI_WriteData(0x0C);SPI_WriteData(0x40);SPI_WriteData(0x4F);SPI_WriteData(0x04);SPI_WriteData(0x08);SPI_WriteData(0x5E);SPI_WriteData(0x14);SPI_WriteData(0xC5);SPI_WriteData(0x00);SPI_WriteData(0xF4);SPI_WriteData(0x64);SPI_WriteData(0x80);SPI_WriteData(0xE0);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0x45);SPI_WriteData(0x51);SPI_WriteData(0x0C);SPI_WriteData(0x40);SPI_WriteData(0x4E);SPI_WriteData(0x03);SPI_WriteData(0x08);SPI_WriteData(0x5E);SPI_WriteData(0x14);SPI_WriteData(0xC5);SPI_WriteData(0x00);SPI_WriteData(0xE4);SPI_WriteData(0x44);SPI_WriteData(0x80);SPI_WriteData(0xE0);SPI_WriteData(0x45);
SSD2828_WritePackageSize(17);SPI_WriteData(0xF0);SPI_WriteData(0x51);SPI_WriteData(0x0C);SPI_WriteData(0x40);SPI_WriteData(0x4E);SPI_WriteData(0x05);SPI_WriteData(0x08);SPI_WriteData(0x5E);SPI_WriteData(0x14);SPI_WriteData(0xC5);SPI_WriteData(0x00);SPI_WriteData(0xE4);SPI_WriteData(0x64);SPI_WriteData(0x80);SPI_WriteData(0xE0);SPI_WriteData(0x45);SPI_WriteData(0x51);
//Blank 21
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x15);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x0C);SPI_WriteData(0x40);SPI_WriteData(0x41);SPI_WriteData(0x80);SPI_WriteData(0xDF);SPI_WriteData(0x0F);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0x85);SPI_WriteData(0x82);SPI_WriteData(0x02);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0xD0);SPI_WriteData(0x17);SPI_WriteData(0xF4);SPI_WriteData(0x03);SPI_WriteData(0x95);SPI_WriteData(0xC7);SPI_WriteData(0x0B);SPI_WriteData(0x04);SPI_WriteData(0x8F);SPI_WriteData(0xE7);SPI_WriteData(0x10);SPI_WriteData(0x94);SPI_WriteData(0x40);SPI_WriteData(0x20);SPI_WriteData(0x08);SPI_WriteData(0x81);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x60);SPI_WriteData(0x00);SPI_WriteData(0x0E);SPI_WriteData(0x00);SPI_WriteData(0xA0);SPI_WriteData(0x14);SPI_WriteData(0xD6);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0xD5);SPI_WriteData(0xB4);SPI_WriteData(0x34);SPI_WriteData(0xAF);SPI_WriteData(0x7B);SPI_WriteData(0x5F);SPI_WriteData(0xD7);SPI_WriteData(0x35);SPI_WriteData(0xCD);SPI_WriteData(0x20);SPI_WriteData(0x18);SPI_WriteData(0x86);SPI_WriteData(0xA2);SPI_WriteData(0x38);SPI_WriteData(0x8E);SPI_WriteData(0xA9);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);
SSD2828_WritePackageSize(17);SPI_WriteData(0xF0);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xD7);SPI_WriteData(0xD5);SPI_WriteData(0xB4);SPI_WriteData(0x34);SPI_WriteData(0xAF);SPI_WriteData(0x7B);SPI_WriteData(0x5F);SPI_WriteData(0xD7);SPI_WriteData(0x35);SPI_WriteData(0x4D);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x04);
//Blank 22
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x16);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x82);SPI_WriteData(0x30);SPI_WriteData(0x0C);SPI_WriteData(0xA9);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0xDB);SPI_WriteData(0xB6);SPI_WriteData(0x6D);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x11);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xC0);SPI_WriteData(0x1F);SPI_WriteData(0xE1);SPI_WriteData(0x41);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x28);SPI_WriteData(0x02);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x04);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x06);SPI_WriteData(0x64);SPI_WriteData(0xE8);SPI_WriteData(0x04);SPI_WriteData(0x99);SPI_WriteData(0x4C);SPI_WriteData(0x16);SPI_WriteData(0xC8);SPI_WriteData(0x50);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0x93);SPI_WriteData(0x40);SPI_WriteData(0x86);SPI_WriteData(0x1A);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x40);SPI_WriteData(0x81);SPI_WriteData(0x4C);SPI_WriteData(0x26);SPI_WriteData(0x00);SPI_WriteData(0x0A);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0x00);SPI_WriteData(0x0A);SPI_WriteData(0x8A);SPI_WriteData(0x00);SPI_WriteData(0x5A);SPI_WriteData(0x2D);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x28);SPI_WriteData(0x10);SPI_WriteData(0x28);
SSD2828_WritePackageSize(17);SPI_WriteData(0xF0);SPI_WriteData(0x04);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);SPI_WriteData(0x00);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);SPI_WriteData(0x08);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);SPI_WriteData(0x10);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);
//Blank 23
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x17);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x18);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);SPI_WriteData(0x20);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);SPI_WriteData(0x28);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);SPI_WriteData(0x30);SPI_WriteData(0x90);SPI_WriteData(0xA1);SPI_WriteData(0x23);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x00);SPI_WriteData(0xFC);SPI_WriteData(0x7E);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xFA);SPI_WriteData(0xE0);SPI_WriteData(0x03);SPI_WriteData(0xC5);SPI_WriteData(0xE3);SPI_WriteData(0x05);SPI_WriteData(0x82);SPI_WriteData(0xC7);SPI_WriteData(0x0B);SPI_WriteData(0x41);SPI_WriteData(0x05);SPI_WriteData(0x02);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x41);SPI_WriteData(0x08);SPI_WriteData(0x04);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0x08);SPI_WriteData(0x00);SPI_WriteData(0xDE);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(7);SPI_WriteData(0xD0);SPI_WriteData(0x00);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 24
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x18);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xD4);SPI_WriteData(0x7F);SPI_WriteData(0xD4);SPI_WriteData(0xD4);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x7A);SPI_WriteData(0x83);SPI_WriteData(0x7A);SPI_WriteData(0x85);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0xFE);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xFE);SPI_WriteData(0xD4);SPI_WriteData(0x7F);SPI_WriteData(0xD4);
SSD2828_WritePackageSize(17);SPI_WriteData(0xF0);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xD4);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);
//Blank 25
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x19);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0xAA);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);SPI_WriteData(0x7F);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x7F);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x79);SPI_WriteData(0x86);SPI_WriteData(0x7A);SPI_WriteData(0x83);SPI_WriteData(0x7A);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7A);SPI_WriteData(0x85);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7B);SPI_WriteData(0x84);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);SPI_WriteData(0x83);SPI_WriteData(0x7C);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x83);SPI_WriteData(0x7F);SPI_WriteData(0x04);SPI_WriteData(0xFF);SPI_WriteData(0x1E);SPI_WriteData(0x00);SPI_WriteData(0x08);SPI_WriteData(0x10);SPI_WriteData(0x18);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0xFC);SPI_WriteData(0x00);SPI_WriteData(0x04);
SSD2828_WritePackageSize(12);SPI_WriteData(0xD0);SPI_WriteData(0x20);SPI_WriteData(0x00);SPI_WriteData(0x01);SPI_WriteData(0x08);SPI_WriteData(0x40);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x10);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0xFC);
//Blank 26
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x1A);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xF0);SPI_WriteData(0xD9);SPI_WriteData(0xC8);SPI_WriteData(0xBA);SPI_WriteData(0xAF);SPI_WriteData(0xA6);SPI_WriteData(0x9E);SPI_WriteData(0x98);SPI_WriteData(0x92);SPI_WriteData(0x8D);SPI_WriteData(0x88);SPI_WriteData(0x84);SPI_WriteData(0x00);SPI_WriteData(0x60);SPI_WriteData(0xF6);SPI_WriteData(0xCF);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0xFC);SPI_WriteData(0x6F);SPI_WriteData(0xF6);SPI_WriteData(0xEF);SPI_WriteData(0xCF);SPI_WriteData(0xAF);SPI_WriteData(0x5F);SPI_WriteData(0x55);SPI_WriteData(0x00);SPI_WriteData(0xF8);SPI_WriteData(0x00);SPI_WriteData(0xF8);SPI_WriteData(0x00);SPI_WriteData(0xF8);SPI_WriteData(0xAD);SPI_WriteData(0x8D);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x73);SPI_WriteData(0x60);SPI_WriteData(0x53);SPI_WriteData(0x4A);SPI_WriteData(0x43);SPI_WriteData(0x7F);SPI_WriteData(0x78);SPI_WriteData(0x10);SPI_WriteData(0xA0);SPI_WriteData(0x3F);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(9);SPI_WriteData(0xC0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 28
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x1C);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0x04);SPI_WriteData(0x08);SPI_WriteData(0x0C);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x14);SPI_WriteData(0x18);SPI_WriteData(0x1C);SPI_WriteData(0x00);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x00);SPI_WriteData(0x40);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x00);SPI_WriteData(0x60);SPI_WriteData(0x68);SPI_WriteData(0x70);SPI_WriteData(0x78);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0x88);SPI_WriteData(0x90);SPI_WriteData(0x98);SPI_WriteData(0x00);SPI_WriteData(0xA0);SPI_WriteData(0xA8);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0xB0);SPI_WriteData(0xB8);SPI_WriteData(0x00);SPI_WriteData(0xC0);SPI_WriteData(0xC8);SPI_WriteData(0xD0);SPI_WriteData(0xD8);SPI_WriteData(0x00);SPI_WriteData(0xE0);SPI_WriteData(0xE8);SPI_WriteData(0xF0);SPI_WriteData(0xF8);SPI_WriteData(0x00);SPI_WriteData(0xFC);SPI_WriteData(0xFE);SPI_WriteData(0xFF);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x04);SPI_WriteData(0x08);SPI_WriteData(0x0C);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x14);SPI_WriteData(0x18);SPI_WriteData(0x1C);SPI_WriteData(0x00);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x00);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x00);SPI_WriteData(0x60);SPI_WriteData(0x68);SPI_WriteData(0x70);SPI_WriteData(0x78);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0x88);SPI_WriteData(0x90);SPI_WriteData(0x98);SPI_WriteData(0x00);SPI_WriteData(0xA0);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0xA8);SPI_WriteData(0xB0);SPI_WriteData(0xB8);SPI_WriteData(0x00);SPI_WriteData(0xC0);SPI_WriteData(0xC8);SPI_WriteData(0xD0);SPI_WriteData(0xD8);SPI_WriteData(0x00);SPI_WriteData(0xE0);SPI_WriteData(0xE8);SPI_WriteData(0xF0);SPI_WriteData(0xF8);SPI_WriteData(0x00);SPI_WriteData(0xFC);SPI_WriteData(0xFE);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0xFF);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x04);SPI_WriteData(0x08);SPI_WriteData(0x0C);SPI_WriteData(0x00);SPI_WriteData(0x10);SPI_WriteData(0x14);SPI_WriteData(0x18);SPI_WriteData(0x1C);SPI_WriteData(0x00);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);
SSD2828_WritePackageSize(17);SPI_WriteData(0xF0);SPI_WriteData(0x00);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x00);SPI_WriteData(0x60);SPI_WriteData(0x68);SPI_WriteData(0x70);SPI_WriteData(0x78);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0x88);SPI_WriteData(0x90);SPI_WriteData(0x98);SPI_WriteData(0x00);
//Blank 29
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x1D);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xA0);SPI_WriteData(0xA8);SPI_WriteData(0xB0);SPI_WriteData(0xB8);SPI_WriteData(0x00);SPI_WriteData(0xC0);SPI_WriteData(0xC8);SPI_WriteData(0xD0);SPI_WriteData(0xD8);SPI_WriteData(0x00);SPI_WriteData(0xE0);SPI_WriteData(0xE8);SPI_WriteData(0xF0);SPI_WriteData(0xF8);SPI_WriteData(0x00);SPI_WriteData(0xFC);
SSD2828_WritePackageSize(5);SPI_WriteData(0x90);SPI_WriteData(0xFE);SPI_WriteData(0xFF);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 31
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x1F);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x5A);SPI_WriteData(0x0F);SPI_WriteData(0x70);SPI_WriteData(0x09);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x40);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x38);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x40);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x40);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x58);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x60);SPI_WriteData(0x20);SPI_WriteData(0x28);SPI_WriteData(0x30);SPI_WriteData(0x38);SPI_WriteData(0x40);SPI_WriteData(0x48);SPI_WriteData(0x50);SPI_WriteData(0x58);SPI_WriteData(0xFF);SPI_WriteData(0x5A);SPI_WriteData(0x1E);SPI_WriteData(0x20);
SSD2828_WritePackageSize(13);SPI_WriteData(0xD0);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x20);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x20);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x20);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0xFE);
//Blank 32
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x20);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x45);SPI_WriteData(0x75);SPI_WriteData(0x03);SPI_WriteData(0x00);SPI_WriteData(0x0A);SPI_WriteData(0xF3);SPI_WriteData(0xFF);SPI_WriteData(0x83);SPI_WriteData(0x14);SPI_WriteData(0x08);SPI_WriteData(0x02);SPI_WriteData(0x08);SPI_WriteData(0x03);SPI_WriteData(0x41);SPI_WriteData(0x18);SPI_WriteData(0x36);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x18);SPI_WriteData(0x46);SPI_WriteData(0xE1);SPI_WriteData(0x40);SPI_WriteData(0xE1);SPI_WriteData(0x20);SPI_WriteData(0x36);SPI_WriteData(0x18);SPI_WriteData(0xCA);SPI_WriteData(0x21);SPI_WriteData(0x41);SPI_WriteData(0x01);SPI_WriteData(0x21);SPI_WriteData(0x13);SPI_WriteData(0x40);SPI_WriteData(0x42);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x91);SPI_WriteData(0x50);SPI_WriteData(0x28);SPI_WriteData(0x14);SPI_WriteData(0x0A);SPI_WriteData(0x85);SPI_WriteData(0x03);SPI_WriteData(0xD3);SPI_WriteData(0xC0);SPI_WriteData(0x50);SPI_WriteData(0x36);SPI_WriteData(0x7F);SPI_WriteData(0xD0);SPI_WriteData(0x1F);SPI_WriteData(0x12);SPI_WriteData(0xE0);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x18);SPI_WriteData(0x36);SPI_WriteData(0x1B);SPI_WriteData(0x11);SPI_WriteData(0x04);SPI_WriteData(0x20);SPI_WriteData(0x02);SPI_WriteData(0xD0);SPI_WriteData(0x80);SPI_WriteData(0xB3);SPI_WriteData(0x21);SPI_WriteData(0x38);SPI_WriteData(0x40);SPI_WriteData(0x20);SPI_WriteData(0x88);SPI_WriteData(0x03);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x83);SPI_WriteData(0xA1);SPI_WriteData(0x4C);SPI_WriteData(0x70);SPI_WriteData(0x80);SPI_WriteData(0x40);SPI_WriteData(0x8D);SPI_WriteData(0x0D);SPI_WriteData(0xA4);SPI_WriteData(0xA2);SPI_WriteData(0x00);SPI_WriteData(0x80);SPI_WriteData(0x04);SPI_WriteData(0x38);SPI_WriteData(0x00);SPI_WriteData(0x50);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0x80);SPI_WriteData(0x13);SPI_WriteData(0xE0);SPI_WriteData(0x00);SPI_WriteData(0x1C);SPI_WriteData(0x80);SPI_WriteData(0x50);SPI_WriteData(0x30);SPI_WriteData(0x00);SPI_WriteData(0xE0);SPI_WriteData(0x81);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x28);SPI_WriteData(0x0E);SPI_WriteData(0x06);
SSD2828_WritePackageSize(17);SPI_WriteData(0xE0);SPI_WriteData(0x03);SPI_WriteData(0x11);SPI_WriteData(0x11);SPI_WriteData(0x11);SPI_WriteData(0x11);SPI_WriteData(0x01);SPI_WriteData(0x90);SPI_WriteData(0x84);SPI_WriteData(0x88);SPI_WriteData(0x88);SPI_WriteData(0x88);SPI_WriteData(0x88);SPI_WriteData(0xC4);SPI_WriteData(0x10);SPI_WriteData(0x84);SPI_WriteData(0xC6);
SSD2828_WritePackageSize(17);SPI_WriteData(0xF0);SPI_WriteData(0xE0);SPI_WriteData(0x81);SPI_WriteData(0x00);SPI_WriteData(0x20);SPI_WriteData(0x00);SPI_WriteData(0x21);SPI_WriteData(0x42);SPI_WriteData(0x88);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x02);SPI_WriteData(0x00);SPI_WriteData(0x31);
//Blank 33
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x21);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x04);SPI_WriteData(0x41);SPI_WriteData(0x06);SPI_WriteData(0x00);SPI_WriteData(0x92);SPI_WriteData(0x24);SPI_WriteData(0x49);SPI_WriteData(0x00);SPI_WriteData(0x20);SPI_WriteData(0x49);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x20);SPI_WriteData(0x49);
SSD2828_WritePackageSize(17);SPI_WriteData(0x90);SPI_WriteData(0x92);SPI_WriteData(0x04);SPI_WriteData(0x00);SPI_WriteData(0x85);SPI_WriteData(0x11);SPI_WriteData(0x0C);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x40);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x16);SPI_WriteData(0x00);SPI_WriteData(0xA5);
SSD2828_WritePackageSize(17);SPI_WriteData(0xA0);SPI_WriteData(0x00);SPI_WriteData(0x08);SPI_WriteData(0x08);SPI_WriteData(0x14);SPI_WriteData(0x10);SPI_WriteData(0x49);SPI_WriteData(0x92);SPI_WriteData(0x24);SPI_WriteData(0x49);SPI_WriteData(0x28);SPI_WriteData(0x20);SPI_WriteData(0x92);SPI_WriteData(0x24);SPI_WriteData(0x49);SPI_WriteData(0x92);SPI_WriteData(0x50);
SSD2828_WritePackageSize(17);SPI_WriteData(0xB0);SPI_WriteData(0x40);SPI_WriteData(0x24);SPI_WriteData(0x92);SPI_WriteData(0x94);SPI_WriteData(0x24);SPI_WriteData(0x49);SPI_WriteData(0x92);SPI_WriteData(0x24);SPI_WriteData(0x09);SPI_WriteData(0xE0);SPI_WriteData(0x0F);SPI_WriteData(0x00);SPI_WriteData(0x55);SPI_WriteData(0x10);SPI_WriteData(0x01);SPI_WriteData(0x08);
SSD2828_WritePackageSize(17);SPI_WriteData(0xC0);SPI_WriteData(0x01);SPI_WriteData(0x42);SPI_WriteData(0x01);SPI_WriteData(0x31);SPI_WriteData(0x20);SPI_WriteData(0x02);SPI_WriteData(0x10);SPI_WriteData(0x10);SPI_WriteData(0x01);SPI_WriteData(0x08);SPI_WriteData(0x88);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x21);SPI_WriteData(0x00);SPI_WriteData(0x02);
SSD2828_WritePackageSize(17);SPI_WriteData(0xD0);SPI_WriteData(0x22);SPI_WriteData(0x00);SPI_WriteData(0x3F);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xE0);SPI_WriteData(0x4E);SPI_WriteData(0x52);SPI_WriteData(0x40);SPI_WriteData(0x04);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x03);SPI_WriteData(0x18);SPI_WriteData(0x10);SPI_WriteData(0x16);
SSD2828_WritePackageSize(3);SPI_WriteData(0xE0);SPI_WriteData(0x10);SPI_WriteData(0x00);
//Blank 34
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x22);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0xA9);SPI_WriteData(0xDF);SPI_WriteData(0x00);SPI_WriteData(0x40);SPI_WriteData(0x55);SPI_WriteData(0x01);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x55);SPI_WriteData(0x05);SPI_WriteData(0x54);SPI_WriteData(0x40);SPI_WriteData(0x55);SPI_WriteData(0x1F);SPI_WriteData(0x70);
SSD2828_WritePackageSize(4);SPI_WriteData(0x90);SPI_WriteData(0xF0);SPI_WriteData(0x00);SPI_WriteData(0x00);
//Blank 35
SSD2828_WritePackageSize(2);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x23);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x19);SPI_WriteData(0x01);SPI_WriteData(0x02);SPI_WriteData(0x05);SPI_WriteData(0x00);SPI_WriteData(0x05);SPI_WriteData(0x04);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
SSD2828_WritePackageSize(10);SPI_WriteData(0x90);SPI_WriteData(0x06);SPI_WriteData(0xFF);SPI_WriteData(0x1F);SPI_WriteData(0x20);SPI_WriteData(0x00);SPI_WriteData(0x01);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xFE);
//Blank 36
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x24);
SSD2828_WritePackageSize(17);SPI_WriteData(0x80);SPI_WriteData(0x00);SPI_WriteData(0x03);SPI_WriteData(0x00);SPI_WriteData(0x77);SPI_WriteData(0xFF);SPI_WriteData(0x66);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0xDC);SPI_WriteData(0xF5);
SSD2828_WritePackageSize(15);SPI_WriteData(0x90);SPI_WriteData(0x5A);SPI_WriteData(0xA5);SPI_WriteData(0x5A);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x22);SPI_WriteData(0x22);SPI_WriteData(0x3A);SPI_WriteData(0x22);SPI_WriteData(0x00);SPI_WriteData(0x00);SPI_WriteData(0x00);
//-------------  LCD Initial code end -------------------------
//SPI not FINISH
//      GEN_WR(0x90);SPI_WriteData(0x5A);
//SPI FINISH
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x24);
SSD2828_WritePackageSize(2);SPI_WriteData(0x90);SPI_WriteData(0xA5);
 
//Blank select 2F 
SSD2828_WritePackageSize(3);SPI_WriteData(0x41);SPI_WriteData(0x5A);SPI_WriteData(0x2F);
//INT CANCEL__TP_I2C mode 
SSD2828_WritePackageSize(2);SPI_WriteData(0x4C);SPI_WriteData(0x03);
//Bypass or FIFO mode 
SSD2828_WritePackageSize(2);SPI_WriteData(0x09);SPI_WriteData(0x01);
//CMD1 LEDPWM set
SSD2828_WritePackageSize(3);SPI_WriteData(0x51);SPI_WriteData(0x7f);SPI_WriteData(0x0f);
SSD2828_WritePackageSize(2);SPI_WriteData(0x53);SPI_WriteData(0x24);
SSD2828_WritePackageSize(2);SPI_WriteData(0x55);SPI_WriteData(0x00);
 
SSD2828_WritePackageSize(1);
SPI_WriteData(0x29);
bsp_DelayMS(150);
SSD2828_WritePackageSize(1);
SPI_WriteData(0x29);
bsp_DelayMS(100);

}

  







