#ifndef __USARTFIFO__
#define __USARTFIFO__
#include "timer.h"
#include "gd32f30x_usart.h"
#include "stdio.h"
#include "ff.h"
#include <string.h>
#include "consoled.h"



#define  MAX_SIZE   255



typedef struct 
{
	volatile unsigned int read_index;           /* ????? */
	volatile unsigned int write_index;          /* ????? */  
	unsigned int buffer_size;					/* ringbuffer?? */
    unsigned char *buffer_ptr;  				/* ??ringbuffer */    
} UART_S;

int uart_buf_put(uint8_t ch);
int uart_buf_get (uint8_t *ch);
void ringbuffer_init(void);
void debug_read(void);
void uart_rev_enable(void);
void uart_init(void);
void uart_it_cb(void);
void uart_it_cb1(void);
void printk(char *frm,...);


#endif



