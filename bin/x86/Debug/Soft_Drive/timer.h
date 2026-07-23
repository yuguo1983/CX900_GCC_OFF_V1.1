#ifndef __TIMER_H
#define	__TIMER_H
#include "gd32f303e_eval.h"
#include "key.h"

#define DISABLE_INT() 	__set_PRIMASK(1)
#define ENABLE_INT()		__set_PRIMASK(0)


static void tick_callback(void);
uint32_t TIM_CORE_GetTick(void);
static void bsp_RunPer10ms(void);
void SysTick_ISR(void);
void bsp_DelayMS(uint32_t n);
void bsp_DelayUS(uint32_t n);
void Timer1_Configuration(void);
















#endif

