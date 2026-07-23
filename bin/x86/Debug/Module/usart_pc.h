#ifndef __USART_PC_H
#define __USART_PC_H

//#include "misc.h"
//#include "stm32f10x.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_usart.h"
//#include "stm32f10x_tim.h"
//#include "stm32f10x_exti.h"
//#include "stm32f10x_gpio.h"
//#include "MCU_GPU_fsmc.h"
#include "app.h"
#define UART1_RX_BUF_SIZE				640
void Usart_Init(uint32_t SetBaudRate);
void Timer3_Configuration(void);
void Timer3_Enable(void);
void Timer3_DISABLE(void);
void UartProcess(void);

void UART_TxChar(uint8_t uint8_tData);

#endif /* __USART&PC_H */
