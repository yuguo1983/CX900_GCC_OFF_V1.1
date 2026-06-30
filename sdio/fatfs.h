#ifndef __FATFS_H
#define __FATFS_H
#include "gd32f30x.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h" /* defines SD_Driver as external */
extern FATFS Flash;
enum{
    USBDisk = 0,
	SDCard,
	SPIFlash
    
	
};


extern FIL openfile;
uint8_t fatfs_getfree(uint8_t *drv,uint32_t *total,uint32_t *free);
uint8_t Fatfs_init(uint8_t driver);
uint8_t Fatfs_getfree(uint8_t driver);
uint8_t Fatfs_open(uint8_t driver,uint8_t*path,uint8_t mode);
uint8_t Fatfs_close(void);
uint8_t Fatfs_read(uint8_t *data,uint32_t len);
uint8_t Fatfs_write(uint8_t *data,uint32_t len);
#endif //__FATFS_H
