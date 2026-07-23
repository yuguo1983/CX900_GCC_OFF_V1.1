void INITLCD(void){
		SPI_WriteCmd(0xB7);
	SPI_WriteData(0x10);//10=TX_CLK 30=PCLK
	SPI_WriteData(0x02);


	SPI_WriteCmd(0xBD);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	
SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xf4);
SSD2828_SPI_Write_Data(0xd2);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x85);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc4);
SSD2828_SPI_Write_Data(0x1e);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa1);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xb3);
SSD2828_SPI_Write_Data(0x4);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x9);
SSD2828_SPI_Write_Data(0x24);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xe8);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x40);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xb3);
SSD2828_SPI_Write_Data(0xf8);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x85);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xa7);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xd0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc3);
SSD2828_SPI_Write_Data(0x35);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xd3);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc3);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xd4);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc3);
SSD2828_SPI_Write_Data(0x35);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xd7);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc3);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x87);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xa4);
SSD2828_SPI_Write_Data(0xf);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x89);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xa4);
SSD2828_SPI_Write_Data(0x2e);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8d);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xa4);
SSD2828_SPI_Write_Data(0xf);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8f);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xa4);
SSD2828_SPI_Write_Data(0x2e);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xca);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x80);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x82);

SSD2828_WritePackageSize(3);
SSD2828_SPI_Write_Data(0xa7);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x80);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x84);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x24);
SSD2828_SPI_Write_Data(0x83);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x24);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x82);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x87);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa5);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x81);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x87);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xaa);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x84);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x87);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x83);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x87);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb5);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x81);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xba);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x81);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xc0);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x81);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xc5);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x81);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xe0);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x33);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x80);

SSD2828_WritePackageSize(17);
SSD2828_SPI_Write_Data(0xcb);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xfe);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xc5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x35);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xc0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x90);

SSD2828_WritePackageSize(17);
SSD2828_SPI_Write_Data(0xcb);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x40);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x40);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xcb);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xcb);
SSD2828_SPI_Write_Data(0x55);
SSD2828_SPI_Write_Data(0x56);
SSD2828_SPI_Write_Data(0x55);
SSD2828_SPI_Write_Data(0x55);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x80);

SSD2828_WritePackageSize(17);
SSD2828_SPI_Write_Data(0xcc);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x16);
SSD2828_SPI_Write_Data(0x17);
SSD2828_SPI_Write_Data(0x18);
SSD2828_SPI_Write_Data(0x24);
SSD2828_SPI_Write_Data(0x3);
SSD2828_SPI_Write_Data(0x23);
SSD2828_SPI_Write_Data(0x22);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x90);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xcc);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0x9);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x29);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x80);

SSD2828_WritePackageSize(17);
SSD2828_SPI_Write_Data(0xcd);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x16);
SSD2828_SPI_Write_Data(0x17);
SSD2828_SPI_Write_Data(0x18);
SSD2828_SPI_Write_Data(0x24);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x23);
SSD2828_SPI_Write_Data(0x22);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x90);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xcd);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0x9);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x29);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(17);
SSD2828_SPI_Write_Data(0xcc);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x16);
SSD2828_SPI_Write_Data(0x17);
SSD2828_SPI_Write_Data(0x18);
SSD2828_SPI_Write_Data(0x24);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x23);
SSD2828_SPI_Write_Data(0x22);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xcc);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0x9);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x29);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(17);
SSD2828_SPI_Write_Data(0xcd);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x16);
SSD2828_SPI_Write_Data(0x17);
SSD2828_SPI_Write_Data(0x18);
SSD2828_SPI_Write_Data(0x24);
SSD2828_SPI_Write_Data(0x3);
SSD2828_SPI_Write_Data(0x23);
SSD2828_SPI_Write_Data(0x22);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xcd);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0x6);
SSD2828_SPI_Write_Data(0x9);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x29);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x80);

SSD2828_WritePackageSize(7);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8a);

SSD2828_WritePackageSize(3);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x1b);
SSD2828_SPI_Write_Data(0x9);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x90);

SSD2828_WritePackageSize(7);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x79);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x6d);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x10);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(7);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x3b);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x10);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xd7);

SSD2828_WritePackageSize(7);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x74);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x71);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x10);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(6);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x79);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x2a);
SSD2828_SPI_Write_Data(0x10);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xc1);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xc0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xae);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x88);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x74);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xcc);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa5);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xc1);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x56);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x2);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x82);

SSD2828_WritePackageSize(14);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x9);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xd8);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xd8);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x90);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x90);
SSD2828_SPI_Write_Data(0xd);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x9);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x90);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x82);
SSD2828_SPI_Write_Data(0xd);
SSD2828_SPI_Write_Data(0x5c);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x82);
SSD2828_SPI_Write_Data(0x80);
SSD2828_SPI_Write_Data(0x9);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(4);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(4);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x22);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xc0);

SSD2828_WritePackageSize(4);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xd1);

SSD2828_WritePackageSize(8);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xa);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x5e);
SSD2828_SPI_Write_Data(0x1);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xe1);

SSD2828_WritePackageSize(12);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x15);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x15);
SSD2828_SPI_Write_Data(0x2);
SSD2828_SPI_Write_Data(0x15);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x2c);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x62);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xf1);

SSD2828_WritePackageSize(10);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0x17);
SSD2828_SPI_Write_Data(0xb);
SSD2828_SPI_Write_Data(0xf);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0xb0);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x3d);
SSD2828_SPI_Write_Data(0x1);
SSD2828_SPI_Write_Data(0x63);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x82);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x84);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x87);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x89);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8a);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x7);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8b);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8c);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x92);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x94);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x97);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x99);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x9a);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x7);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x9b);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x9c);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x24);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa2);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa4);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa7);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa9);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x6);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x6c);
SSD2828_SPI_Write_Data(0x70);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb5);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x5);
SSD2828_SPI_Write_Data(0x5);
SSD2828_SPI_Write_Data(0x35);
SSD2828_SPI_Write_Data(0x39);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xc0);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0xca);
SSD2828_SPI_Write_Data(0xce);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xc5);

SSD2828_WritePackageSize(5);
SSD2828_SPI_Write_Data(0xcf);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x8);
SSD2828_SPI_Write_Data(0xc);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(41);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x19);
SSD2828_SPI_Write_Data(0x21);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x30);
SSD2828_SPI_Write_Data(0x93);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x44);
SSD2828_SPI_Write_Data(0x48);
SSD2828_SPI_Write_Data(0x62);
SSD2828_SPI_Write_Data(0x4d);
SSD2828_SPI_Write_Data(0x54);
SSD2828_SPI_Write_Data(0x5b);
SSD2828_SPI_Write_Data(0x61);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x68);
SSD2828_SPI_Write_Data(0x6e);
SSD2828_SPI_Write_Data(0x75);
SSD2828_SPI_Write_Data(0x7d);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x86);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x92);
SSD2828_SPI_Write_Data(0x99);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0xa1);
SSD2828_SPI_Write_Data(0xac);
SSD2828_SPI_Write_Data(0xb9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0xdd);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0xf1);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0xcb);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(41);
SSD2828_SPI_Write_Data(0xe2);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x19);
SSD2828_SPI_Write_Data(0x21);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x30);
SSD2828_SPI_Write_Data(0x93);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x44);
SSD2828_SPI_Write_Data(0x48);
SSD2828_SPI_Write_Data(0x62);
SSD2828_SPI_Write_Data(0x4d);
SSD2828_SPI_Write_Data(0x54);
SSD2828_SPI_Write_Data(0x5b);
SSD2828_SPI_Write_Data(0x61);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x68);
SSD2828_SPI_Write_Data(0x6e);
SSD2828_SPI_Write_Data(0x75);
SSD2828_SPI_Write_Data(0x7d);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x86);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x92);
SSD2828_SPI_Write_Data(0x99);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0xa1);
SSD2828_SPI_Write_Data(0xac);
SSD2828_SPI_Write_Data(0xb9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0xdd);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0xf1);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0xcb);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(41);
SSD2828_SPI_Write_Data(0xe3);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x19);
SSD2828_SPI_Write_Data(0x21);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x30);
SSD2828_SPI_Write_Data(0x93);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x44);
SSD2828_SPI_Write_Data(0x48);
SSD2828_SPI_Write_Data(0x62);
SSD2828_SPI_Write_Data(0x4d);
SSD2828_SPI_Write_Data(0x54);
SSD2828_SPI_Write_Data(0x5b);
SSD2828_SPI_Write_Data(0x61);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x68);
SSD2828_SPI_Write_Data(0x6e);
SSD2828_SPI_Write_Data(0x75);
SSD2828_SPI_Write_Data(0x7d);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x86);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x92);
SSD2828_SPI_Write_Data(0x99);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0xa1);
SSD2828_SPI_Write_Data(0xac);
SSD2828_SPI_Write_Data(0xb9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0xdd);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0xf1);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0xcb);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(41);
SSD2828_SPI_Write_Data(0xe4);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x19);
SSD2828_SPI_Write_Data(0x21);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x30);
SSD2828_SPI_Write_Data(0x93);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x44);
SSD2828_SPI_Write_Data(0x48);
SSD2828_SPI_Write_Data(0x62);
SSD2828_SPI_Write_Data(0x4d);
SSD2828_SPI_Write_Data(0x54);
SSD2828_SPI_Write_Data(0x5b);
SSD2828_SPI_Write_Data(0x61);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x68);
SSD2828_SPI_Write_Data(0x6e);
SSD2828_SPI_Write_Data(0x75);
SSD2828_SPI_Write_Data(0x7d);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x86);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x92);
SSD2828_SPI_Write_Data(0x99);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0xa1);
SSD2828_SPI_Write_Data(0xac);
SSD2828_SPI_Write_Data(0xb9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0xdd);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0xf1);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0xcb);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(41);
SSD2828_SPI_Write_Data(0xe5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x19);
SSD2828_SPI_Write_Data(0x21);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x30);
SSD2828_SPI_Write_Data(0x93);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x44);
SSD2828_SPI_Write_Data(0x48);
SSD2828_SPI_Write_Data(0x62);
SSD2828_SPI_Write_Data(0x4d);
SSD2828_SPI_Write_Data(0x54);
SSD2828_SPI_Write_Data(0x5b);
SSD2828_SPI_Write_Data(0x61);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x68);
SSD2828_SPI_Write_Data(0x6e);
SSD2828_SPI_Write_Data(0x75);
SSD2828_SPI_Write_Data(0x7d);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x86);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x92);
SSD2828_SPI_Write_Data(0x99);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0xa1);
SSD2828_SPI_Write_Data(0xac);
SSD2828_SPI_Write_Data(0xb9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0xdd);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0xf1);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0xcb);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(41);
SSD2828_SPI_Write_Data(0xe6);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x7);
SSD2828_SPI_Write_Data(0xe);
SSD2828_SPI_Write_Data(0x33);
SSD2828_SPI_Write_Data(0x19);
SSD2828_SPI_Write_Data(0x21);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x30);
SSD2828_SPI_Write_Data(0x93);
SSD2828_SPI_Write_Data(0x38);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x44);
SSD2828_SPI_Write_Data(0x48);
SSD2828_SPI_Write_Data(0x62);
SSD2828_SPI_Write_Data(0x4d);
SSD2828_SPI_Write_Data(0x54);
SSD2828_SPI_Write_Data(0x5b);
SSD2828_SPI_Write_Data(0x61);
SSD2828_SPI_Write_Data(0x27);
SSD2828_SPI_Write_Data(0x68);
SSD2828_SPI_Write_Data(0x6e);
SSD2828_SPI_Write_Data(0x75);
SSD2828_SPI_Write_Data(0x7d);
SSD2828_SPI_Write_Data(0x3e);
SSD2828_SPI_Write_Data(0x86);
SSD2828_SPI_Write_Data(0x8c);
SSD2828_SPI_Write_Data(0x92);
SSD2828_SPI_Write_Data(0x99);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0xa1);
SSD2828_SPI_Write_Data(0xac);
SSD2828_SPI_Write_Data(0xb9);
SSD2828_SPI_Write_Data(0xc2);
SSD2828_SPI_Write_Data(0xdd);
SSD2828_SPI_Write_Data(0xce);
SSD2828_SPI_Write_Data(0xe1);
SSD2828_SPI_Write_Data(0xf1);
SSD2828_SPI_Write_Data(0xff);
SSD2828_SPI_Write_Data(0xcb);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x84);

SSD2828_WritePackageSize(3);
SSD2828_SPI_Write_Data(0xc5);
SSD2828_SPI_Write_Data(0x28);
SSD2828_SPI_Write_Data(0x28);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xd3);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xd4);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xd5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xd6);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(9);
SSD2828_SPI_Write_Data(0xd7);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);
SSD2828_SPI_Write_Data(0x7f);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(3);
SSD2828_SPI_Write_Data(0xd8);
SSD2828_SPI_Write_Data(0x2b);
SSD2828_SPI_Write_Data(0x2b);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x00);

SSD2828_WritePackageSize(4);
SSD2828_SPI_Write_Data(0xd9);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x8d);
SSD2828_SPI_Write_Data(0x8d);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa3);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc5);
SSD2828_SPI_Write_Data(0x2d);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa9);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc5);
SSD2828_SPI_Write_Data(0x19);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x86);

SSD2828_WritePackageSize(4);
SSD2828_SPI_Write_Data(0xc5);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x60);
SSD2828_SPI_Write_Data(0xc);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x90);

SSD2828_WritePackageSize(13);
SSD2828_SPI_Write_Data(0xc5);
SSD2828_SPI_Write_Data(0x82);
SSD2828_SPI_Write_Data(0x20);
SSD2828_SPI_Write_Data(0x43);
SSD2828_SPI_Write_Data(0x84);
SSD2828_SPI_Write_Data(0x1d);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8c);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc3);
SSD2828_SPI_Write_Data(0x3);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x8e);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xc3);
SSD2828_SPI_Write_Data(0x10);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xa5);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xb3);
SSD2828_SPI_Write_Data(0xc0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0xf5);
SSD2828_SPI_Write_Data(0x0);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0x82);

SSD2828_WritePackageSize(3);
SSD2828_SPI_Write_Data(0xa4);
SSD2828_SPI_Write_Data(0x29);
SSD2828_SPI_Write_Data(0x23);

SSD2828_WritePackageSize(2);
SSD2828_SPI_Write_Data(0x00);
SSD2828_SPI_Write_Data(0xb0);

SSD2828_WritePackageSize(3);
SSD2828_SPI_Write_Data(0xf3);
SSD2828_SPI_Write_Data(0x5);
SSD2828_SPI_Write_Data(0xfa);

	
SSD2828_WritePackageSize(1);
SSD2828_SPI_Write_Data(0x11);
bsp_DelayMS(120);

SSD2828_WritePackageSize(1);
SSD2828_SPI_Write_Data(0x29);	   
bsp_DelayMS(120);
}