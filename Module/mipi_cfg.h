#ifndef __MIPI_CFG_H
#define __MIPI_CFG_H

#include "gd32f30x.h"
#include "stdio.h"
#include "systick.h"
#include "pport_spi.h"
#include "user_config.h"
#include "timer.h"
void lcm_mipi_set(uint8_t value);
typedef enum
{
    MIPI_VIDEO_MODE	  = 0,
    MIPI_COMMAND_MODE = 1   
    
}MIPI_MODE_T;

typedef enum
{
    NON_BURST_PULSES = 0x00, // Non burst mode with sync pulses
    NON_BURST_EVENTS = 0x01, // Non burst mode with sync events
    BURST_MODE = 0x02
}BURST_MODE_T;

typedef enum
{
    MIPI_RTX_LP  = 0,
    MIPI_RTX_HS  = 1,
    MIPI_RTX_VD  = 2,
    MIPI_RTX_DCS = 3    
}MIPI_RTX_MODE_T;

typedef enum
{   
	_1LANE = 0X00,
  _2LANE = 0X01,
  _3LANE = 0X02,
  _4LANE = 0X03,
  _8LANE = _4LANE
}MIPI_LANE_NUM_T;

#define Mipi_Write(DT, dat, ...)  SSD2828_Mipi_Write(DT, dat, ##__VA_ARGS__, -1)
#define GEN_WR(dat, ...)  FocalTech_Mipi_Write(dat, ##__VA_ARGS__, -1)

void PANEL_RESET_L(void);
void PANEL_RESET_H(void);
void SPI_CS_L(void);
void SPI_CS_H(void);

void SPI_SCK_H(void);
void SPI_SCK_L(void);
void SPI_SDI_H(void);
void SPI_SDI_L(void);



void SSD2828_RESET_H(void);
void SSD2828_RESET_L(void);
void SSD2828_SHUT_H(void);
void SSD2828_SHUT_L(void);

void W_C(uint16_t data);
void W_D(uint16_t data);

void SSD2828_Init(void);
void SSD2828_Init_Chip(void);

void SSD2828_LP(void);
void SSD2828_HS(void);
void SSD2828_Video(void);

void SSD2828_Write_Reg(uint8_t cmd, uint8_t dat1, uint8_t dat2);
uint8_t   SSD2828_Dcs_Read_DT06(uint8_t adr, uint16_t l, uint8_t *p);
uint8_t   SSD2828_Generic_Read_DT14(uint8_t adr, uint16_t l, uint8_t *p);

void SSD2828_Reset(void);
void SSD2828_Spi_Init_Chip(void);
uint16_t SSD2828_Spi_Read(void);
void SSD2828_Spi_Write_Reg(unsigned char cmd, unsigned char dat1, unsigned char dat2);
void SSD2828_Spi_Write_Cmd(unsigned char cmd);
uint8_t   SSD2828_Spi_Dcs_Read_DT06(uint8_t adr, uint16_t l, uint8_t *p, uint8_t mipi_rtx_mode);
uint8_t   SSD2828_Spi_GenericRead_DT14(uint8_t adr, uint16_t l, uint8_t *p, uint8_t mipi_rtx_mode);

void SSD2828_Cmod_Init_Chip(void);
void SSD2828_Cmod_Write_Cmd(uint8_t data);
void SSD2828_Cmod_Write_Dat(uint32_t data);
uint16_t  SSD2828_Cmod_Read_Reg(uint8_t reg);
uint32_t  SSD2828_Cmod_Read_Dat(void);
void SSD2828_Cmod_Write_Reg(uint8_t cmd, uint8_t msb, uint8_t lsb);
uint8_t   SSD2828_Cmod_DCS_Read_Dt06(uint8_t adr, uint16_t l, uint8_t *p, uint8_t mipi_rtx_mode);
uint8_t   SSD2828_Cmod_GenericRead_DT14(uint8_t adr, uint16_t l, uint8_t *p);
void SSD2828_Cmod_Write_Data_Separate(uint8_t reg2, uint8_t reg1, uint8_t reg0);
void SSD2828_Cmod_Write_Vedio_Data_Separate(uint8_t r, uint8_t g, uint8_t b);
void SSD2828_Cmod_Set_Data_Write_Gap(uint8_t dat);
void SSD2828_Cmod_Set_Video_Write_Gap(uint8_t dat);
void SSD2828_Cmod_Set_Dispaly_Area(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void SSD2828_Cmod_Update_Screen(uint16_t uint16_tTime);
void SSD2828_Cmod_Update_Screen2(uint8_t r, uint8_t g, uint8_t b);
void SSD2828_Cmod_Update_Screen_Non_Block(uint16_t uint16_tTime);

//void SSD2828_SPI_Read_Chip_ID(void);
uint32_t  SSD2828_SPI_Read_Chip_ID(void );
void SSD2828_SPI_Write_Data(unsigned char dat);
void SSD2828_Cmod_Read_Chip_ID(void);

void SSD2828_Mipi_Write(uint8_t DT, uint16_t dat, ...);
void FocalTech_Mipi_Write(uint16_t dat, ...);
void Init_SSD2828_video_mode(void);
void Mipi_lp(void);

void InitCodeBefore(void);
void InitCodeAfter(void);

#endif /* __GPU_CFG_H */
