#ifndef __GPU_CFG_H
#define __GPU_CFG_H

#include "gd32f30x.h"
#include "stdio.h"
#include "GPU_RGB.h"
#include "UserGpioDefine.h"
////sd card commnd

#define MCU_GPU_ID_ADDR0      0x0F
#define MCU_GPU_ID_ADDR1      0x0E
#define MCU_GPU_STATU_ADDR0   0x0C
#define MCU_GPU_TEST_ADDR0    0x02
#define MCU_GPU_Beep          0x03
#define MCU_GPU_GPIO_ADDR0    0x04
#define MCU_GPU_GPIO_ADDR1    0x05
#define MCU_GPU_BL            0x02
#define MCU_GPU_STATU_ADDR0   0x0C






uint32_t Get_GPU_DateTime(void);
int GPU_LogicWorkStatus(void);
void Get_GPU_Version(void);
uint8_t * Get_GPU_Date(void);
uint16_t GPU_Connection_Check(void);

#define MCU_GPU_ADDR  	*(volatile uint16_t *)0x60000000
#define MCU_GPU_DATA  	*(volatile uint16_t *)0x60040000 	

void O_TP_VCC(uint16_t Val,uint16_t vol);
void MCU_GPU_FSMCConfig(void);
void GPU_Beep(uint16_t value);
void GPU_BL(uint8_t value);
void O_LCM_5V_EN(uint16_t Val);
void O_LCM_Rest_SW(uint16_t Val) ;

void MCU_CMD_Init(void);
void MCU_CMD_Refresh(uint8_t mode);
void MCU_CMD_Pix(uint32_t Cmd,uint8_t mode);
void MCU_CMD_Wr(uint32_t Cmd, uint32_t *WData, uint16_t WrCnt);
void MCU_CMD_Rd(uint32_t Cmd, uint32_t *RData, uint16_t RdCnt);

void CMD_WriteData(unsigned short value);
void CMD_GP_COMMAD_PA(unsigned int num);
void LoadLcdParameterConfig_CmdMode(void);
void CMD_MIPI_Init_end(void);
void CMD_MIPI_Init_head(void);
void CMD_LcmInitWrite(const uint8_t *code);


void RS485EN_COM0(uint16_t Val);
void CheckTurnA0(uint16_t Val);
void CheckTurnA1(uint16_t Val);

void VspuA(uint16_t Val);
void VsnuA(uint16_t Val);
void VCC1uA(uint16_t Val);
void VCC2uA(uint16_t Val);
void VCC3uA(uint16_t Val);
void VCC4uA(uint16_t Val);
void VCC5uA(uint16_t Val);
void VCC6uA(uint16_t Val);
void Ssd2828ON(uint16_t Val);


uint8_t ReadGpuGpio(uint8_t ch);
void SetGpuGpio(uint8_t ch,uint8_t value);


















#endif /* __GPU_CFG_H */
