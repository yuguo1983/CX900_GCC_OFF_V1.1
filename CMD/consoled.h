#ifndef _CONSOLED_H_
#define _CONSOLED_H_

#include "gd32f30x_usart.h"
#include "usartfifo.h"


void at_proc(uint8_t ch);
void help_proc(char* str);
void dis_proc(char *str);
void power_proc(char* str);
void turn_proc(char* str);
void updata_proc(char *str);
void Ready_proc(char *str);
void Clear_proc(char* str);
void Connect_proc(char *str);
void uprgb_proc(char *str);
uint8_t appUpload(uint8_t *p);//输入制定名称然后写入
uint8_t removeFile(uint8_t * p);
uint8_t uploadfile(void);
uint8_t mkfs(void);
uint8_t bootUpload(uint8_t *p);
void Version_proc(char *str);
uint8_t UappUpload ( uint8_t *str );
#endif

