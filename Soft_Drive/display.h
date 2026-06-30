#ifndef __DISPLAY_H
#define __DISPLAY_H



#include "string.h"
#include "gd32f303e_eval.h"
#include "screenUI.h"
#include "FLASH.h"
#include "bsp_lcd.h"
#include "timer.h"
#include "power_task.h"
typedef struct
{
	uint8_t keypw_flag;
	uint8_t keypower;
	uint8_t keyup_flag;
	uint8_t keyup;
	uint8_t keydown_flag;	
	uint8_t keydown;
	uint8_t keyauto_flag;	
	uint8_t keyauto;
	uint8_t keyotp_flag;	
	uint8_t keyotp;
}serial_key;



extern unsigned int   DVDDVoltage;
extern unsigned int   DVDDCurrent;

extern unsigned int   IOVCCVoltage;
extern unsigned int   IOVCCCurrent;

extern unsigned int   AVDDVoltage;
extern unsigned int   AVDDCurrent;

extern unsigned int   VSPVoltage;
extern unsigned int   VSPCurrent;

extern unsigned int   VSNVoltage;
extern unsigned int   VSNCurrent;

extern unsigned int   BLVCCVoltage;
extern unsigned int   BLVCCCurrent;


void SetMaxCurrent(void);
void SetDispString1(void);
void SetPowerOff(void);
void Usart2_Init(void);
void Timer1_Configuration(void);
void Timer1_Enable(void);
void Timer1_DISABLE(void);
void Uart2Process(void);
void Uart3KeyProcess(uint8_t i);
void getSdioInfo(uint16_t len,char *p);
void mainKey(uint8_t value);
void ResponseUart2(uint8_t cmd, uint8_t value);

void sdcardShow(void);
void selectProc(uint8_t value);
void enterProc(void);
void backUpProc(void);

void SetDispColor(void);
void SetDispString(void);
void SetDispFill(void);
void GetVolCur(void);
void SetDispPic(void);

void rec_program_num(void);
void rec_ip_model(void);
void rec_pic_name(void);
void send_string(uint8_t cmd,uint8_t str[29]);
void send_testcount(uint16_t num);
void send_app_num(uint16_t num);
void send_vol_cut(uint8_t cmd,uint16_t vol ,uint16_t cut );

void updata_program(void);
void keypoll(void);

#endif /* __DISPLAY_H */

