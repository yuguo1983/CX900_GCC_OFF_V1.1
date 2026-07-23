#ifndef __PPORT_SPI_H
#define __PPORT_SPI_H


#include "timer.h"
#include "gd32f30x_spi.h"
#include "UserGpioDefine.h"
void init_spi(void);
void reset_lcd(void);
void SPI_3W_SET_Cmd(unsigned int Sdata);
void SPI_3W_SET_PAs(unsigned int Sdata);
unsigned char SPI_ReadData(void);
void SPI_WriteData(unsigned char value);
void SPI_WriteCmd(unsigned char value);
void SPI_2828_WrReg(unsigned char c,unsigned char PAs_L, unsigned char PAs_H);
void GP_COMMAD_PA(unsigned int num);
void SPI_WriteCmdData(unsigned char value,unsigned char data);
void Reset(unsigned char Val);
void Lcd_Reset(unsigned char Val);
void Delay(unsigned int x);
void SSD2828_RegConfig(unsigned char address,unsigned char lbyte,unsigned char hbyte);
void SSD2828_WritePackageSize(unsigned char num);
unsigned char Ssd2828_ID_OK_check(void);
void SSD2828WriteReg(unsigned char c,  unsigned char PAs_H, unsigned char PAs_L);
int Read_ID_OriseIC(void);
void Init_SSD2828READ(void);
unsigned int SSD2828GenericReadDT14(uint8_t adr, uint16_t l, uint8_t *p,uint8_t mode);
unsigned int SSD2828DcsReadDT06(uint8_t adr, uint16_t l, uint8_t *p,uint8_t mode);
#endif /* __PPORT_SPI_H */
