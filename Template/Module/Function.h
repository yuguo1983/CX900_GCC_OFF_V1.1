#ifndef __Function_H
#define __Function_H

#include "gd32f30x.h"
#include "power_task.h"
#include "display.h"
#include "app.h"
#include "sysInit.h"
#include "user_config.h"
#include "TouchPoint.h"
extern uint8_t KeyPowerPressed;
extern uint8_t KeyUpPressed;
extern uint8_t KeyDownPressed;
extern uint8_t KeyAutoPressed;
extern uint8_t KeyOTPPressed;
extern uint8_t AutoFlag;
extern uint8_t PowerStatus;

void mainInit(void);
void mainFunction(void);
void PowerOff_Process(void);
void PowerOn_Process(void);
void KeyUp_Process(void);
void KeyDown_Process(void);
void KeyAuto_Process(void);
void KeyOTP_Process(void);
void CheckDW_Process(void );
void  ParameterDownload(void);
#endif /* __Function_H */
