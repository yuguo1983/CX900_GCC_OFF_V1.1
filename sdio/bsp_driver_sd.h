#ifndef __BSP_DRIVER_SD_H
#define __BSP_DRIVER_SD_H

#include "sdcard.h"

extern sd_card_info_struct sd_cardinfo;  

sd_error_enum sd_io_init(void);
void card_info_get(void);
void SD_test(void);

#endif //__BSP_DRIVER_SD_H
