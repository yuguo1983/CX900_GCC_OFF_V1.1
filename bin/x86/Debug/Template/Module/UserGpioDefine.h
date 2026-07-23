#ifndef __UserGpioDefine_H
#define __UserGpioDefine_H
#include "gd32f30x.h"



int8_t I_FPGA_CF_DONE(void);
void O_FPGA_CF_RECONFIG(uint8_t value);
void O_M25P80_SPI_CSN(uint8_t value);
void O_M25P80_SPI_CLK(uint8_t value);
void O_M25P80_SPI_MOSI(uint8_t value);
void O_PWR_LED(uint8_t value);
uint8_t I_M25P80_SPI_MISO(void);
void EnableGPU_SPI_FLASH_OutputDriving(void);
void DisableGPU_SPI_FLASH_OutputDriving(void);
void EnableEBindingPin_OutputDriving(uint16_t GPIO_PinX);
void DisableEBindingPin_OutputDriving(uint16_t GPIO_PinX);




void O_SSD2828_RESET(uint8_t value);
void O_SSD2828_SPI_CS(uint8_t value);
void O_SSD2828_SPI_CLK(uint8_t value);
void O_SSD2828_SPI_SDI(uint8_t value);
uint8_t I_SSD2828_SPI_SDO(void);
uint8_t I_SSD2828_SPI1_SDO(void);

void O_SSD2828_SPI_CS1(uint8_t value);
void O_LCD_RESET(uint8_t value);
void O_USB_EN(uint8_t value);
void O_SSD2828_SHUT(uint8_t value);
int8_t get_nSTATUS(void);
void O_FPGA_PS_DATA(uint8_t value);
void O_FPGA_PS_CLK(uint8_t value);
void FPGA_RST(uint8_t value);


uint8_t GPG_TP_I2C_SCL(uint8_t value);
uint8_t GPG_TP_I2C_SDA(uint8_t value);




void O_PWR_EN_OTP(uint8_t enable,uint16_t vol);
void O_PWR_EN_2V8(uint8_t value);
void O_TP_RESET(uint8_t value);
void O_PWR_BL_EN(uint8_t value);
void O_PWR_5V_EN(uint8_t value);
void O_PWR_VPN_EN(uint8_t value);

void set_vcc1(uint16_t vol);
void set_vcc2(uint16_t vol);
void set_vcc3(uint16_t vol);
void set_vcc4(uint16_t vol);
void set_vcc5(uint16_t vol);
void set_vcc6(uint16_t vol);
void set_envcc1(uint8_t Enable);
void set_envcc2(uint8_t Enable);
void set_envcc3(uint8_t Enable);
void set_envcc4(uint8_t Enable);
void set_envcc5(uint8_t Enable);
void set_envcc6(uint8_t Enable);
void set_tim_vcc1(uint16_t uptim, uint16_t dwntim);
void set_tim_vcc2(uint16_t uptim, uint16_t dwntim);
void set_tim_vcc3(uint16_t uptim, uint16_t dwntim);
void set_tim_vcc4(uint16_t uptim, uint16_t dwntim);
void set_tim_vcc5(uint16_t uptim, uint16_t dwntim);
void set_tim_vcc6(uint16_t uptim, uint16_t dwntim);


void set_resetvcc(uint16_t vol);
void set_eniovcc(uint8_t value);
void set_iovcc(uint16_t vol);
void set_tim_iovcc(uint16_t uptim,uint16_t dwntim);
void set_envcc(uint8_t value);
void set_vcc(uint16_t vol);
void set_tim_vcc(uint16_t uptim,uint16_t dwntim);
void set_envsn(uint8_t value);
void set_envsp(uint8_t value);
void set_tim_vsn(uint16_t uptim,uint16_t dwntim);
void set_tim_vsp(uint16_t uptim,uint16_t dwntim);
void set_vspvol(uint16_t vol);
void set_vsnvol(uint16_t vol);
void set_tim_reset(uint16_t uptim, uint16_t dwntim);

uint8_t I_USER_K1_AUTO(void);
uint8_t I_USER_K2_POWER(void);
uint8_t I_USER_K3_NEXT(void);
uint8_t I_USER_K4_UP(void);
uint8_t I_USER_K5(void);
uint8_t I_USER_K6_MODE(void);

void GPIO_Configuration(void);

uint8_t ReadDW1(void);
uint8_t ReadDW2(void);
void Fpga_Start(void);
void Turn_chanel(uint8_t ch);
void Turn_chane2(uint8_t ch);

#endif /* __UserGpioDefine_H */
