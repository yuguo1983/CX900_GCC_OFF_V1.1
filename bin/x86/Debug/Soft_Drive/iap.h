#ifndef __IAP_H__
#define __IAP_H__
#include "bsp.h"
#include "gd32f30x.h"
typedef  void (*iapfun)(void);				//定义一个函数类型的参数.
								


void iap_load_app(uint32_t appxaddr);			//执行flash里面的app程序
void iap_init(void);
uint8_t iap_check_file(uint8_t * path);
uint8_t app_check_file(uint8_t * path);
uint8_t app_check_update(void);
void app_update_fimware(uint8_t *path);

void disable_used_irq(void);

#endif







































