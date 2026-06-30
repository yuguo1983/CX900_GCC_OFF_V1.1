/*!
    \file  main.c
    \brief SPI flash demo

    \version 2021-03-23, V2.0.0, demo for GD32F30x
*/

/*
    Copyright (c) 2021, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <stdio.h>
#include "gd32f30x.h"
#include "gd25qxx.h"
#include "gd32f303e_eval.h"
#include "bsp_lcd.h"
#include "screenUI.h"
#include "malloc.h"
#include "timer.h"
#include "usart.h"
#include "display.h"
#include "log.h"
#include "GPU_PIC.h"
#include "GPU_DAC.h"
#include "GPU_SDIO.h"
#include "BSP.h"
#include "GPU_GPIO.h"
#include "stdio.h"
#include "chipiic.h"
#include "ina220.h"
#include "pll_freq_def.h"
#include "mb.h"
#include "mbport.h"
#include "user_mb_app.h"
#include "bspdrivermemory.h"
#include "calibthread.h"
#include "Function.h"
#include "file_opration.h"
#include "bsp_driver_sd.h"
#include "fatfs.h"
#include "dac5571.h"
//#include "fontupd.h"
#include "iap.h"
#include "menu.h"
#include "usartfifo.h"
#include "ff.h"
#include "fatfs.h"
#include "GPU_Show.h"


#define  SFLASH_ID                     0xEF4017
#define  MAX_TASK			10
#include  "uart_protocol.h"

uint8_t System_Ready;
void Recevefile(void);
void init_receivefile(void);

extern uint8_t Fatfs_init(uint8_t driver);
extern uint32_t crcvalue;
extern uint32_t crc_read;
ErrStatus memory_compare(uint8_t *src, uint8_t *dst, uint16_t length);

void led_init(void);
void bsp_Idle(void);
void bsp_init(void);
void start_usb(void);
void dis_usb (void);
void start_usb(void);
void app_fatfs_init(void);

extern uint8_t temp_read_data[14];




///***************************************************************************************************//
// 函数名：bsp_init
// 功能：初始化一些相关外设和必要的函数
// 参数：无
//返回：无
//**************************************************************************************************//
void bsp_init(void)
{
    uint32_t flash_id = 0;
    systick_config();   
    gd_eval_com_init(EVAL_COM1);
    gd_eval_com_init(EVAL_COM2);
    gd_eval_com_init(EVAL_COM3);
		led_init();
    time_config();
    spi_flash_init();
    GPIO_Configuration();
    MCU_GPU_FSMCConfig();
	//modbusflag=0;
	if(modbusflag)
	{
		eMBInit( MB_RTU, 1, 0, 115200, MB_PAR_NONE);  //modbus init
		eMBEnable();
	}else
	{
		msgfifo_init();
		msg_init();	
	}
    CHIP_IIC_Init();
    MEMORY_Init();
    InitDac();
    Ina220_Iint();
    flash_id = spi_flash_read_id();
    if(flash_id == SFLASH_ID)
    {
        log_info("Flash init successfull");
    }
    else log_info("Flash init FAIL!!!");
    read_pass_num(temp_read_data);
}

///***************************************************************************************************//
// 函数名：main
// 功能：入口函数
// 参数：无
//返回：无
//**************************************************************************************************//
//extern  _srtCalibInfor srtCalibInfor;
uint32_t pixcolor[100]={0xff0000};
int main(void)
{
		UINT bw;
		FRESULT res;
		DISABLE_INT();
    ENABLE_INT();
    nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x10000);
	  System_Ready=0;
    bsp_init();
	  ringbuffer_init();
		Fpga_Start();
	  mainInit();
		GPU_Beep(1);
    O_PWR_5V_EN(1);
	GPU_SDIO_INIT();
	GPU_FindBmp();
	  //Gpu_Mcu_Fill(0,0,10,10,pixcolor);
    GPU_PIC_Init();
    CALIB_THREAD_Init();
    Init_Alarm();
    printf("\r\n#################################User Start######################################\r\n");
	  printk("checktestnum%d \r\n",temp_read_data[0] << 8 | temp_read_data[1]);

		FATFS_Init();
    mem_init(SRAMIN);
    log_info("SDCard :%d \r\n",Fatfs_init(SDCard));
		log_info("SPIFlash :%d \r\n",Fatfs_init(SPIFlash));
		// res=f_mount(NULL,"0:",1);
		// log_info("f_mount NULL :%d \r\n",res);
		// ShowBMP("0:\F01.BMP");
    f_mount(NULL,"1:",1);
    res=f_mount(&Flash,"1:",1);
    if(res==FR_NO_FILESYSTEM)
    {
        res=f_mkfs("1:",0,0);
        log_info("open %d \r\n",res);
        f_mount(NULL,"1:",1);
        f_mount(&Flash,"1:",1);
        FIL fil;
        res = f_open(&fil, "1:/test1.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
        log_info("open %d size %d\r\n",res,(uint32_t)f_size(&fil));
        uint8_t buf[13]= {0};
        uint8_t wrbuf[11]="hello word";
        uint8_t mm[11];
        int read_len;
        for(int i=0 ; i<10; i++)
        {
            sprintf((char *)buf,"%s %d",wrbuf,i);
            res = f_write(&fil, buf, sizeof(buf), &bw);
            log_info("write %d len %d\r\n",res,bw);
        }

        f_close(&fil);
        res = f_open(&fil, "1:/test1.txt",FA_WRITE|FA_READ);
        log_info("open %d size %d\r\n",res,(uint32_t)f_size(&fil));

        for(int i=0 ; i<10; i++)
        {
            res = f_read(&fil,mm,13,(UINT *)&read_len);
            log_info("read %s len %d res %d\r\n",(char*)mm,read_len,res);
        }


        f_close(&fil);
        scan_files("1:");
    }
#if 0
    FIL fil;
    res = f_open(&fil, "1:/test2.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
    log_info("open %d size %d\r\n",res,f_size(&fil));
    uint8_t buf[13]= {0};
    uint8_t wrbuf[11]="hello word";
    uint8_t mm[11];
    int read_len;
    for(int i=0 ; i<10; i++)
    {
        sprintf((char *)buf,"%s %d",wrbuf,i);
        res = f_write(&fil, buf, sizeof(buf), &bw);
        log_info("write %d len %d\r\n",res,bw);
        //delay_1ms(20);
    }

    f_close(&fil);
    //f_lseek(&fil,0);
    res = f_open(&fil, "1:/test1.txt",FA_WRITE|FA_READ);
    log_info("open %d size %d\r\n",res,f_size(&fil));

    for(int i=0 ; i<12; i++)
    {
        res = f_read(&fil,mm,13,&read_len);
        log_info("read %s len %d res %d\r\n",(char*)mm,read_len,res);
        //delay_1ms(20);
    }
    f_close(&fil);
#endif
    scan_files("1:");
    uint8_t cont[30]= {0};
    for(int i=0; i<60; i++)
    {
        if(strcmp((char *)app_name[i],(char *)cont)==0)
            break;
        log_info("%s",app_name[i]);
    }
/*
    app_fatfs_init();
    res = Fatfs_open(SDCard, "UPDATA/app.bin", FA_OPEN_ALWAYS | FA_WRITE);
   res = f_open(&fs, "0:/UPDATA/app.bin", FA_OPEN_ALWAYS | FA_WRITE);
   if(res != FR_OK)
   {
       log_info("open file  operation fail!!");
    }
    else ;
    Main_Menu();  //测试YMODLE协议用
    uint8_t *temp = (uint8_t *)0x8070000;
    for(int i = 0; i < 200; i++)
		printf("number:[%03d  0x%02x ] ",i+1, temp[i]);
*/
    ParameterDownload();
    System_Ready=1;
    while(1)
    {
        mainFunction();
		if(modbusflag)
		{
        ( void )eMBPoll(  );
		}
		else
		{
			msg_read();
			
		}
        CALIB_THREAD_Poll();
//        measurement();
					ina220_poll();
					reportinfo();
        led_poll();
			
				debug_read();			
				mbapp_poll(	);
    }
}

uint8_t crc = 0;
uint8_t file_creatflag = 0;
extern uint32_t firmware_size;
void app_fatfs_init(void)
{
    MCU_GPU_ADDR = GPU_SDIO_CTRL;//enable sd ip
    MCU_GPU_DATA = 0x00;
    bsp_DelayMS(2);
    iap_init();
}



///***************************************************************************************************//
// 函数名：bsp_Idle
// 功能：在bsp_DelayMS时会调用此函数
// 参数：无
//返回：无
//**************************************************************************************************//




void bsp_Idle  (void)
{
    led_poll();
	  debug_read();	
//		mainFunction();
		//( void )eMBPoll(  );
		CALIB_THREAD_Poll();
		ina220_poll();
		reportinfo();		
		mbapp_poll(	);
}


///***************************************************************************************************//
// 函数名：led_init
// 功能：初始化LED灯
// 参数：无
//返回：无
//**************************************************************************************************//

void led_init(void)
{
    /* initialize the leds */
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    log_info("LED init successfull");
}


///***************************************************************************************************//
// 函数名：memory_compare
// 功能：内存对比函数
// 参数：原目标，对比目标 ，长度
//返回：成功 失败
//**************************************************************************************************//

ErrStatus memory_compare(uint8_t *src, uint8_t *dst, uint16_t length)
{
    while(length --)
    {
        if(*src++ != *dst++)
            return ERROR;
    }
    return SUCCESS;
}





