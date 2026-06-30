#ifndef    USER_APP
#define USER_APP
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
//#include "mb_m.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbutils.h"

/* -----------------------Slave Defines -------------------------------------*/
//Modbus规定寄存器起始地址为1
#define REG_INPUT_START 1001
#define REG_INPUT_NREGS 10
#define REG_HOLDING_START 1011
#define REG_HOLDING_NREGS 200

#define REG_MACHINECTRL_START 100

#define POWER_STATUS	 REG_MACHINECTRL_START+0
#define AUTO_STATUS	   REG_MACHINECTRL_START+1
#define SHOW_STATUS	   REG_MACHINECTRL_START+2
#define POWER_ON			 REG_MACHINECTRL_START+3
#define POWER_OFF			 REG_MACHINECTRL_START+4
#define TURN_UP			 	 REG_MACHINECTRL_START+5
#define TURN_DOWN			 REG_MACHINECTRL_START+6
#define TURN_AUTO			 REG_MACHINECTRL_START+7
#define SHOW_PIC			 REG_MACHINECTRL_START+8



#define EXOUTBASE 	REG_MACHINECTRL_START+20
#define EXOUT1			 EXOUTBASE+0
#define EXOUT2			 EXOUTBASE+1
#define EXOUT3		 	 EXOUTBASE+2
#define EXOUT4			 EXOUTBASE+3



#define EXINBASE 		 EXOUTBASE+5
#define EXIN1			   EXINBASE+0
#define EXIN2			   EXINBASE+1
#define EXIN3			   EXINBASE+2
#define EXIN4			   EXINBASE+3
#define EXIN5			   EXINBASE+4
#define EXIN6			   EXINBASE+5
#define EXIN7			   EXINBASE+6
#define EXIN8			   EXINBASE+7


#define SET_MODE				10
#define SET_UPTIM				11
#define SET_DNTIM				12
#define SET_ITYPE				13
#define SET_VVALUE			14
#define SET_IVALUE			15
#define SET_RVALUE			16
#define SET_LEDVF				17
#define POWER						18



#define SET1_MODE				20
#define SET1_UPTIM			21
#define SET1_DNTIM			22
#define SET1_ITYPE			23
#define SET1_VVALUE			24
#define SET1_IVALUE			25
#define SET1_RVALUE			26
#define SET1_LEDVF			27
#define POWER1					28

//校准
#define START						40

#define ISMODE					41//设置校准模式　
#define SET_RAIN				42//设置校准档位　A/MA
#define SET_CHANEL			43//设置校准通道　1，2
#define RECOVER_VALUE		44//输入万用表测的值

#define STATUS					46


#define CALIBRST        80
#define PARAMRST        81












void mbapp_poll(void);



#endif
