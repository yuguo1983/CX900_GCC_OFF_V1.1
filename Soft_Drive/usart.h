#ifndef __UART_H
#define	__UART_H
#include "gd32f303e_eval.h"
#include "bsp_lcd.h"
#include "gd25qxx.h"
#include "stdio.h"
#include "usartfifo.h"

typedef enum
{
  USART_OK       = 0x00U,
  USART_ERROR    = 0x01U,
  USART_BUSY     = 0x02U,
  USART_TIMEOUT  = 0x03U
}USART_TypeDef;
extern uint8_t modbusflag;

void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void UART_TxChar(uint8_t uint8_tData);
void SetUartBaudRate( void);
void Uart1SendBuffer(uint8_t *puint8_tData, uint16_t uint16_tLength);
void FlashRead(void);
void FlashEnable(uint8_t value);
void FlashWrite(void);
void Response( uint8_t value);
void FlashErase(void);
void Timer3_Enable(void);
void UartProcess(void);
int fputc(int ch, FILE *f);
void time_config(void);
USART_TypeDef UART_Transmit(uint32_t usart_periph,uint8_t *p_string,uint32_t len,uint32_t timeout);
void UART_TxChar1(uint32_t usart_periph,uint8_t uint8_tData);
USART_TypeDef UART_Receive(uint32_t usart_periph,uint8_t *buffer,uint32_t len,uint32_t timeout);



#endif

