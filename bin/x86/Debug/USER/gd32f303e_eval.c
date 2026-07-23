/*!
    \file    gd32f303e_eval.c
    \brief   functions to manage leds, keys, COM ports

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

#include <gd32f30x.h>
#include "gd32f303e_eval.h"
#include "display.h"
#include "ina220.h"
/* private variables */



static uint32_t GPIO_PORT[LEDn] = {LED1_GPIO_PORT};
static uint32_t GPIO_PIN[LEDn] = {LED1_PIN};



static rcu_periph_enum COM_CLK[COMn] = {EVAL_COM1_CLK, EVAL_COM2_CLK,EVAL_COM3_CLK};
static uint32_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN, EVAL_COM2_TX_PIN,EVAL_COM3_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN, EVAL_COM2_RX_PIN,EVAL_COM3_RX_PIN};
static uint32_t COM_GPIO_PORT[COMn] = {EVAL_COM1_GPIO_PORT, EVAL_COM2_GPIO_PORT,EVAL_COM3_GPIO_PORT};
static rcu_periph_enum COM_GPIO_CLK[COMn] = {EVAL_COM1_GPIO_CLK, EVAL_COM2_GPIO_CLK,EVAL_COM3_GPIO_CLK};

static rcu_periph_enum GPIO_CLK[LEDn] = {LED1_GPIO_CLK};


/*!
    \brief      configure led GPIO
    \param[in]  lednum: specify the led to be configured
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
															 


void gd_eval_led_on(led_typedef_enum lednum)
{
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}


void  gd_eval_led_init (led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);

    /* configure led GPIO port */ 
    gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the led to be turned on
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/






/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the led to be turned off
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
void gd_eval_led_off(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      toggle selected led
    \param[in]  lednum: specify the led to be toggled
      \arg        LED2
      \arg        LED3
      \arg        LED4
      \arg        LED5
    \param[out] none
    \retval     none
*/
void gd_eval_led_toggle(led_typedef_enum lednum)
{
    gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum], 
                    (bit_status)(1 - gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));
}




void gd_eval_com_init(uint32_t com)
{
    uint32_t com_id = 0U;
    if(EVAL_COM1 == com){
        com_id = 0U;
    }else if(EVAL_COM2 == com){
        com_id = 1U;
    }
		else if(EVAL_COM3 == com)
		{
				com_id = 2U;
		}
    
    /* enable GPIO clock */
    rcu_periph_clock_enable(COM_GPIO_CLK[com_id]);
//		rcu_periph_clock_enable(COM_GPIO_CLK[com_id]);
    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[com_id]);
		rcu_periph_clock_enable( RCU_AF);
		gpio_pin_remap_config( GPIO_USART0_REMAP,DISABLE); 
    /* connect port to USARTx_Tx */
    gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, COM_TX_PIN[com_id]);

    /* connect port to USARTx_Rx */
    gpio_init(COM_GPIO_PORT[com_id], GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, COM_RX_PIN[com_id]);

		switch(com)
		{
			case EVAL_COM1:nvic_irq_enable(USART0_IRQn, 0, 1);break;
			case EVAL_COM2:nvic_irq_enable(USART1_IRQn, 0, 0);break;
			case EVAL_COM3:nvic_irq_enable(USART2_IRQn, 0, 0);break;
			default:;break;
		}	
    /* USART configure */
    usart_deinit(com);
		switch(com)
		{
			case EVAL_COM1:usart_baudrate_set(com, 115200);break;
			case EVAL_COM2:usart_baudrate_set(com, 115200);break;
			case EVAL_COM3:usart_baudrate_set(com, 460800);break;
			default:;break;
		}	
    usart_receive_config(com, USART_RECEIVE_ENABLE);
    usart_transmit_config(com, USART_TRANSMIT_ENABLE);
    usart_enable(com);
		usart_interrupt_enable(com, USART_INT_RBNE);
}



led_type_t  led_type={
.lcd_flag=0,
};
extern _ADC_port adc_volue;
void led_poll(void)
{
	if(led_type.trige)
	{
		led_type.trige=0;
		if(led_type.lcd_flag==0)
		{
			led_type.lcd_flag=1;
			gpio_bit_set(GPIOB, GPIO_PIN_9);
		}
		else 
		{
			led_type.lcd_flag=0;
			gpio_bit_reset(GPIOB, GPIO_PIN_9);	
		}
	}


}
