#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

#include "gd32f30x.h"
#include "UserGpioDefine.h"


//--- MCU固件程序版本信息, 最高一个bit为1表示MCuint32_t, 为0表示MCuint8_t; ----------------------------------------------------------

//--- 外部LCD接口板类型 ------------------------------------------------------------
// 1: 表示最初的双MIPI转接板; 
// 2: 表示在最初双MIPI转接板基础上加了上下电泄放电路的转接板; 
// 3: 表示eDP的转接板; 
// 4: 新的Dual-CommandMode转接板
#define LCD_DAUGHTER_BOARD_TYPE  (4)
uint8_t FramRateCalc(void);

typedef struct {
	uint32_t  func;
	uint32_t param1;
	uint32_t param2;
}_tDismod;


typedef struct {
	uint8_t 		bLCDName[29]; //用于记录该MIPI-LCD的分辨率
	uint8_t 		bICName[29]; //用于记录该MIPI-LCD的分辨率
	uint8_t 		CodeZip[29]; //用于记录该MIPI-LCD的分辨率
	uint8_t 		DUAL_MIPI_LCD; 			//--- 声明该LCD是否为双MIPI屏(单MIPI屏时主板会输出两路相同的单MIPI信号以同时驱动两个屏)
	uint8_t 		DUAL_MIPI_CHANNEL_SWAP; 	//--- 该双MIPI屏的两个通道的数据需要调换一下, 0不做调换, 1做调换
	uint8_t 		ODD_EVEN_nLEFT_RIGHT;     //---  声明该双MIPI屏是左右通道模式还是奇偶通道模式, 0表示左右通道(Left-Right Division), 1表示奇偶通道(Odd-Even Division)
	uint16_t 		PCLK_Freq; 	//PCLK Frequecy, 4~400的整数, 单位MHz
	uint8_t 		LANE_CNT;	// 4:4Lane, 8:8Lane, Others Reserved
	uint8_t 		V_DE;		// 1:DE 高电平有效, 0:DE 低电平有效
	uint8_t 		V_VS;		// 1:VS 高电平有效, 0:VS 低电平有效
	uint8_t 		V_HS; 	// 1:HS 高电平有效, 0:HS 低电平有效
	uint8_t 		V_CLK;		// 1:clk 上升沿, 0:clk 下降沿,
	uint8_t 		Display_Mode; 	// 显示模式 0:Non burst mode with sync pulses  1:Non burst mode with sync events 2:Burst mode 
	uint16_t 		HACT_WIDTH;	//宽度
	uint16_t 		VACT_WIDTH;	//高度
	uint16_t 		HFP_WIDTH;	//宽前肩
	uint16_t 		HBP_WIDTH;	//宽后肩
	uint16_t 		HSW_WIDTH;	//宽同步
	uint16_t 		VFP_WIDTH;	//高前肩
	uint16_t 		VBP_WIDTH;	//高后肩
	uint16_t 		VSW_WIDTH; 	//高同步
			
	uint16_t 		NomalVCC1SET;
	uint16_t 		LowperVCC1VOL;
	uint16_t 		UperVCC1VOL;
	uint16_t 		LowperVCC1MA;
	uint16_t 		UperVCC1MA;	
		
	uint16_t 		NomalVCC2SET;
	uint16_t 		LowperVCC2VOL;
	uint16_t 		UperVCC2VOL;
	uint16_t 		LowperVCC2MA;
	uint16_t 		UperVCC2MA;	
		
	uint16_t 		NomalVCC3SET;
	uint16_t 		LowperVCC3VOL;
	uint16_t 		UperVCC3VOL;
	uint16_t 		LowperVCC3MA;
	uint16_t 		UperVCC3MA;
		
		
	uint16_t 		NomalVCC4SET;
	uint16_t 		LowperVCC4VOL;
	uint16_t 		UperVCC4VOL;
	uint16_t 		LowperVCC4MA;
	uint16_t 		UperVCC4MA;
		
	uint16_t 		NomalVCC5SET;
	uint16_t 		LowperVCC5VOL;
	uint16_t 		UperVCC5VOL;
	uint16_t 		LowperVCC5MA;
	uint16_t 		UperVCC5MA;
		
	uint16_t 		NomalVCC6SET;
	uint16_t 		LowperVCC6VOL;
	uint16_t 		UperVCC6VOL;
	uint16_t 		LowperVCC6MA;
	uint16_t 		UperVCC6MA;
			
	uint16_t 		NomalVSPSET;
	uint16_t 		LowperVSPVOL;
	uint16_t 		UperVSPVOL;
	uint16_t 		LowperVSPMA;
	uint16_t 		UperVSPMA;	
			
	uint16_t 		NomalVSNSET;
	uint16_t 		LowperVSNVOL;
	uint16_t 		UperVSNVOL;
	uint16_t 		LowperVSNMA;
	uint16_t 		UperVSNMA;

	uint16_t 		NomalBLSET;
	uint16_t 		LowperBLVOL;
	uint16_t 		UperBLVOL;
	uint16_t 		LowperBLMA;
	uint16_t 		UperBLMA;
	uint16_t 		BLMASET;



	uint32_t    VCC1Time;
	uint32_t    VCC2Time;
	uint32_t    VCC3Time;
	uint32_t    VCC4Time;
	uint32_t    VCC5Time;
	uint32_t    VCC6Time;
	uint32_t    VSPTime;
	uint32_t    VSNTime;	
	
	
	uint16_t 		Low_Delay;
	uint16_t 		SIZE_OF_SHOW_MODE; 	//显示的总画面个数
  uint8_t  		AlarmFlag;
  uint16_t  	TimeLock;
	uint16_t 		Reserve1;
	uint16_t 		Reserve2;
	uint16_t 		Reserve3;
	uint16_t 		Reserve4;
	uint16_t 		Reserve5;
	uint8_t	 		MIPI_MODE;
	uint8_t  		DW1_EN;
	uint8_t	 		DW2_EN;
	const _tDismod 		tdis[20];
} pMIPI_Para_Table;


extern const pMIPI_Para_Table *ptr_MIPI_TABLE[];
extern unsigned char MIPI_TABLE_LAST_INDEX;
extern volatile uint8_t gMipiTableIndex;




#endif /* __USER_CONFIG_H */
