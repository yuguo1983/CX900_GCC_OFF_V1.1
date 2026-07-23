#include "power_task.h"
#include "pport_spi.h"
#include "app.h"
#include "user_config.h"
#include "GPU_Cfg.h"
#include "timer.h"
#include "mipi_Cfg.h"
#include "file_opration.h"
#include "log.h"
#include "usartfifo.h"
#include "ina220.h"
#include "ncs8805_edp.h"
#include "ssd_2832.h"
#include "GPU_GPIO.h"
#include "GPU_Show.h"
#include "GPU_SPI.h"
#include "lcd_cfg.h"
#include "log.h"
//////////////////////

void Init_NT36523B(void);
void init_nt35516(void);
void Power_Off()
{
    SPI_WriteCmd(0xB7);
    SPI_WriteData(0x50);//10=TX_CLK 50=PCLK
    SPI_WriteData(0x02);
    SPI_WriteCmd(0xBD);
    SPI_WriteData(0x00);
    SPI_WriteData(0x00);
    SSD2828_WritePackageSize(1);
  	SPI_WriteData(0x28);		   	  //SleepIn
   	bsp_DelayMS(10);
   	SSD2828_WritePackageSize(1);
    SPI_WriteData(0x10);		     //display OFF
  	bsp_DelayMS(5);
    O_PWR_5V_EN(0);
    set_envcc(0);
    set_eniovcc(0);
    set_envsp(0);
    set_envsn(0);
    SetGpuExgpio(1,0);
    set_vcc(0);
    set_iovcc(0);
    set_resetvcc(0);
    set_vspvol(0);
    set_vsnvol(0);
    SetGpuExgpio(2,0);//GPIO_2
    Lcd_Reset(0); //LCD reset 
    bridge_RSTPIN_reset();
    RGB_Disable();
    Ssd2828ON(1);
    O_PWR_BL_EN(0); //BL_EN
    O_LCM_5V_EN(0);
    O_PWR_LED(0);
    O_SSD2828_SPI_CS(0);
    O_SSD2828_SPI_CLK(0);
    O_SSD2828_SPI_SDI(0);
    O_SSD2828_RESET(0);	
    GPU_Beep(15);
    SetGpuGpio(1,0);
    SetGpuGpio(2,0);
    SetGpuGpio(3,0);
    SetGpuGpio(4,0);
}





uint8_t tempbuf[10];
uint8_t rdbuf[100];
 int jd9365tg_Read_FW_RegMultiSpi(uint32_t addr, uint8_t *rdata, uint16_t rlen);
int jd9365tg_Read_BackDoor_RegMulti(uint32_t addr, uint8_t *rdata, uint16_t rlen);
static int jd9365tg_Write_BackDoor_RegSingle(uint32_t addr, uint8_t wdata);
 int jd9365tg_Read_FW_RegSingleSpi(uint32_t addr, uint8_t *rdata);
static int jd9365tg_Write_FW_RegSingleSpi(uint32_t addr, uint8_t wdata);
static int jd9365tg_EnterBackDoor(void);
static int jd9365tg_ExitBackDoor(void);
int jd9365tg_Read_BackDoor_RegSingle(uint32_t addr, uint8_t *rdata);

//#define SSD2832

void Power_On(void)
{
    unsigned char mipi_dataarray[20] ;
    struct mipi_port srtmipiport;
    uint8_t readbuf[10]={0};
    uint8_t ret=0;
    BeepOn();
    set_tim_vcc(10, 100);
    set_tim_iovcc(30, 100);
    set_tim_reset(30, 100);
    set_tim_vsp(50, 100);
    set_tim_vsn(50, 100);
    set_vspvol(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVSPSET);
    set_vsnvol(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVSNSET);
    set_vcc1(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVCC1SET);
    set_vcc2(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVCC2SET);
    set_vcc3(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVCC3SET);
    set_vcc4(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVCC4SET);
    set_vcc5(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVCC5SET);
    set_vcc6(ptr_MIPI_TABLE[gMipiTableIndex]->NomalVCC6SET);
    set_envcc1(1);
    set_envcc2(1);
    set_envcc3(1);
    set_envcc4(1);
    set_envcc5(1);
    set_envcc6(1);

    set_envsp(1);
    set_envsn(1);
    O_PWR_5V_EN(1);
    Ssd2828ON(0);
    //	  O_PWR_EN_OTP(1,500);
#ifdef  SSD2832




#else
    O_SSD2828_RESET(1);
    O_SSD2828_SHUT(0);
    O_SSD2828_SPI_CS(1);
    Reset(1);
    bsp_DelayMS(10);
    Reset(0);
    bsp_DelayMS(50);
    Reset(1);
    bsp_DelayMS(50);	
#endif
    O_LCD_RESET(1);
    O_PWR_LED(1);
    bsp_DelayMS(50);
    O_LCD_RESET(0);
    GPU_Beep(15);
    bsp_DelayMS(50);
    O_LCD_RESET(1);
    bsp_DelayMS(50);
//////////////TPRESET//////////		
    SetGpuExgpio(2,1);
    bsp_DelayMS(50);
    SetGpuExgpio(2,0);
    bsp_DelayMS(50);
    SetGpuExgpio(2,1);
//////////////TPRESET//////////	

    GPU_BL(ptr_MIPI_TABLE[gMipiTableIndex]->BLMASET); //PWM
    if(ptr_MIPI_TABLE[gMipiTableIndex]->Display_Mode <= 2)
    RGB_Enable();else ;
    Lcd_ShowMode(0);
		
//   Ssd2828_ID_OK_check();
//   int temp=SSD2828_SPI_Read_Chip_ID();
//	 log_info("0x%x 0x%x",temp>>16,(uint16_t)temp);
	
/////////////////////////////////////////

#ifdef SSD2832
    SSD2832_GPIO_Init();
    bsp_DelayMS(20);
    bridge_init();
	srtmipiport.hs_or_lp = 0;
	srtmipiport.dual = 3;  		
	srtmipiport.video_or_cmd = 0;
	srtmipiport.port = 0;
	srtmipiport.data_type = 0x15;
	mipi_dataarray[0] = 0xff;
	mipi_dataarray[1] = 0xd0;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	bsp_DelayMS(10);	
	mipi_dataarray[0] = 0xfb;
	mipi_dataarray[1] = 0x01;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);
	mipi_dataarray[0] = 0x09;
	mipi_dataarray[1] = 0xa6;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0x1c;
	mipi_dataarray[1] = 0x99;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0x1d;
	mipi_dataarray[1] = 0x09;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0xff;
	mipi_dataarray[1] = 0xe0;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	bsp_DelayMS(10);		
	mipi_dataarray[0] = 0xfb;
	mipi_dataarray[1] = 0x01;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0x92;
	mipi_dataarray[1] = 0xd0;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0xff;
	mipi_dataarray[1] = 0xf0;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	bsp_DelayMS(10);	
	mipi_dataarray[0] = 0xfb;
	mipi_dataarray[1] = 0x01;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0xc6;
	mipi_dataarray[1] = 0x00;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0xff;
	mipi_dataarray[1] = 0x27;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	bsp_DelayMS(10);	
	mipi_dataarray[0] = 0xfb;
	mipi_dataarray[1] = 0x01;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0x3f;
	mipi_dataarray[1] = 0x35;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0x40;
	mipi_dataarray[1] = 0x28;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0x41;
	mipi_dataarray[1] = 0x30;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0x4d;
	mipi_dataarray[1] = 0xfb;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0x4e;
	mipi_dataarray[1] = 0x9f;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0xff;
	mipi_dataarray[1] = 0x10;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);			
	bsp_DelayMS(10);		
	mipi_dataarray[0] = 0xfb;
	mipi_dataarray[1] = 0x00;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0xb0;
	mipi_dataarray[1] = 0x01;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);	
	mipi_dataarray[0] = 0x55;
	mipi_dataarray[1] = 0x80;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0x26;
	mipi_dataarray[1] = 0x01;
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);		
	mipi_dataarray[0] = 0xc0;
	mipi_dataarray[1] = 0x10;//0x11:10bit 0x10:8bit 0x03:dsc10bit
	mipi_write_regs(&srtmipiport,mipi_dataarray,2);			
    bsp_DelayMS(10);	
	srtmipiport.data_type = 0x39;	
	
	mipi_dataarray[0] = 0xc1;
	mipi_dataarray[1] = 0xAB;
	mipi_dataarray[2] = 0x2A;
	mipi_dataarray[3] = 0x00;
	mipi_dataarray[4] = 0x20;
	mipi_dataarray[5] = 0x02;
	mipi_dataarray[6] = 0x00;	
	mipi_dataarray[7] = 0x01;		
	mipi_dataarray[8] = 0xD8;		
	mipi_dataarray[9] = 0x03;		
	mipi_dataarray[10] = 0xB3;	
	mipi_dataarray[11] = 0x00;	
	mipi_dataarray[12] = 0x0A;	
	mipi_dataarray[13] = 0x03;	
	mipi_dataarray[14] = 0x19;	
	mipi_dataarray[15] = 0x03;	
	mipi_dataarray[16] = 0xE4;		
	mipi_write_regs(&srtmipiport,mipi_dataarray,17);		
    bsp_DelayMS(10);	
	mipi_dataarray[0] = 0xc2;
	mipi_dataarray[1] = 0x0C;
	mipi_dataarray[2] = 0xF0;
	mipi_write_regs(&srtmipiport,mipi_dataarray,3);		
	bsp_DelayMS(10);	

    srtmipiport.data_type = 0x15;
	mipi_dataarray[0] = 0x11;
	mipi_write_regs(&srtmipiport, mipi_dataarray,1);	
	bsp_DelayMS(200);
	mipi_dataarray[0] = 0x29;
	mipi_write_regs(&srtmipiport,mipi_dataarray,1);	
	bsp_DelayMS(100);	
		

   // bridge_setbistmode(1);
	
	srtmipiport.data_type = 0x15;
	//video enable
	bridge_write_reg_16bit(0xB7, 0x034B);




O_PWR_BL_EN(1);




#else
//////////////////////////////tp reset

    SetGpuExgpio(1,1);
    bsp_DelayUS(10);
    SetGpuExgpio(1,0);		
    bsp_DelayUS(50);		
    SetGpuExgpio(1,1);		
//////////////////////////////////////
//	O_PWR_EN_OTP(1);

    //bsp_DelayMS(200);
    //Read_ID_OriseIC();
    //Init_SSD2828READ();
	//SSD2828_WritePackageSize(2);

    //bsp_DelayMS(100);
    //ret=SSD2828GenericReadDT14(0X04,4,readbuf,1);
    //log_info("ret: %s",ret?"SUSCEED":"FAIL");
    //for(int i=0;i<4;i++)
    //log_info("ID:0X%x",readbuf[i]);
    lcm_mipi_set(0);
    Initial_LCM_CODE();
    lcm_mipi_set(1);
    O_PWR_BL_EN(1);
    
/*
    spi_set_spispeed(6);  ///spi opration
    spi_set_spimode(0);

    SetGpuGpio(1,1);  ///gipo opration
    SetGpuGpio(2,1);
    SetGpuGpio(3,1);
    SetGpuGpio(4,1);
*/
#endif
}


static int jd9365tg_Write_FW_RegSingleSpi(uint32_t addr, uint8_t wdata)
{
    uint8_t addrBuf[8];
    addrBuf[0] = 0xF2;
    addrBuf[1] = (uint8_t)((addr & 0xFF000000) >> 24);
    addrBuf[2] = (uint8_t)((addr & 0x00FF0000) >> 16);
    addrBuf[3] = (uint8_t)((addr & 0x0000FF00) >> 8);
    addrBuf[4] = (uint8_t)((addr & 0x000000FF) >> 0);
    addrBuf[5] = 0x00;
    addrBuf[6] = 0x01;
    addrBuf[7] = wdata;
		spi_write(addrBuf,8);
    return 1;
}




 int jd9365tg_Read_FW_RegMultiSpi(uint32_t addr, uint8_t *rdata, uint16_t rlen)
{
    uint8_t addrBuf[7];

    addrBuf[0] = 0xF3;
    addrBuf[1] = (uint8_t)((addr & 0xFF000000) >> 24);
    addrBuf[2] = (uint8_t)((addr & 0x00FF0000) >> 16);
    addrBuf[3] = (uint8_t)((addr & 0x0000FF00) >> 8);
    addrBuf[4] = (uint8_t)((addr & 0x000000FF) >> 0);
    addrBuf[5] = (uint8_t)((rlen & 0xFF00) >> 8);
    addrBuf[6] = (uint8_t)((rlen & 0x00FF) >> 0);
		spi_read(addrBuf, sizeof(addrBuf), rdata, rlen);
    return 1;
}
int jd9365tg_Read_BackDoor_RegMulti(uint32_t addr, uint8_t *rdata, uint16_t rlen)
{
    uint8_t addrBuf[6];

    addrBuf[0] = 0xF3;
    addrBuf[1] = (uint8_t)((addr & 0xFF000000) >> 24);
    addrBuf[2] = (uint8_t)((addr & 0x00FF0000) >> 16);
    addrBuf[3] = (uint8_t)((addr & 0x0000FF00) >> 8);
    addrBuf[4] = (uint8_t)((addr & 0x000000FF) >> 0);
    addrBuf[5] = 0x03;
		spi_read(addrBuf, sizeof(addrBuf), rdata, rlen);
    return 1;
}

 int jd9365tg_Read_FW_RegSingleSpi(uint32_t addr, uint8_t *rdata)
{
    int ReCode;
    uint8_t addrBuf[7];
    uint8_t readBuf[1];

    addrBuf[0] = 0xF3;
    addrBuf[1] = (uint8_t)((addr & 0xFF000000) >> 24);
    addrBuf[2] = (uint8_t)((addr & 0x00FF0000) >> 16);
    addrBuf[3] = (uint8_t)((addr & 0x0000FF00) >> 8);
    addrBuf[4] = (uint8_t)((addr & 0x000000FF) >> 0);
    addrBuf[5] = 0x00;
    addrBuf[6] = 0x01;

    spi_read(addrBuf, sizeof(addrBuf), readBuf, sizeof(readBuf));
    *rdata = readBuf[0];

    return ReCode;
}

static int jd9365tg_Write_BackDoor_RegSingle(uint32_t addr, uint8_t wdata)
{
    uint8_t addrBuf[7];

    addrBuf[0] = 0xF2;
    addrBuf[1] = (uint8_t)((addr & 0xFF000000) >> 24);
    addrBuf[2] = (uint8_t)((addr & 0x00FF0000) >> 16);
    addrBuf[3] = (uint8_t)((addr & 0x0000FF00) >> 8);
    addrBuf[4] = (uint8_t)((addr & 0x000000FF) >> 0);
    addrBuf[5] = 0x03;
    addrBuf[6] = wdata;
		spi_write(addrBuf,7);
    return 1;
}
int jd9365tg_Read_BackDoor_RegSingle(uint32_t addr, uint8_t *rdata)
{
    int ReCode;
    uint8_t addrBuf[6];
    uint8_t readBuf[1];

    addrBuf[0] = 0xF3;
    addrBuf[1] = (uint8_t)((addr & 0xFF000000) >> 24);
    addrBuf[2] = (uint8_t)((addr & 0x00FF0000) >> 16);
    addrBuf[3] = (uint8_t)((addr & 0x0000FF00) >> 8);
    addrBuf[4] = (uint8_t)((addr & 0x000000FF) >> 0);
    addrBuf[5] = 0x03;

    spi_read(addrBuf, sizeof(addrBuf), readBuf, sizeof(readBuf));
    *rdata = readBuf[0];

    return ReCode;
}

static int jd9365tg_ExitBackDoor(void)
{
    int ReCode;
    uint8_t addrBuf[6];

    addrBuf[0] = 0xF2;
    addrBuf[1] = 0xAA;
    addrBuf[2] = 0x88;
    addrBuf[3] = 0x00;
    addrBuf[4] = 0x00;
    addrBuf[5] = 0x00;

    spi_write(addrBuf,6);
	return 1;
}

static int jd9365tg_EnterBackDoor(void)
{
			tempbuf[0]=0xF2  ;
			tempbuf[1]=0xAA  ;
			tempbuf[2]=0xF0  ;
			tempbuf[3]=0x0F  ;
			tempbuf[4]=0x55  ;
			tempbuf[5]=0x68  ;			

			spi_write(tempbuf,6);
	return 1;
}
