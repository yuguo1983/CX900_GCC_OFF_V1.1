#ifndef __BSP_H
#define __BSP_H

#include "gd32f30x.h"

#define FLASH_PAGE_SIZE         ((uint32_t)0x00000800)   /* FLASH Page Size:2K */
#define FLASH_BOOT_ADDR		0x08000000  	//第一个应用程序起始地址(存放在FLASH)										
                                      	//保留0X08000000~0X0800FE00的空间为IAP使用
#define USER_BOOT_END_ADDRESS 0X0800FE00
#define CRC_FLASH_ADDR  (FLASH_USER_START_ADDR-FLASH_PAGE_SIZE)  //IAP 空间最后一页保存CRC校验值
#define FLASH_BOOT_END_ADDR 	FLASH_USER_START_ADDR		
#define FLASH_USER_START_ADDR   ((uint32_t)0x08010000)   /* Start @ of user Flash area; GD32F207ZC 256K flash ���6K��Ϊ�û����� */
#define USER_FLASH_END_ADDRESS     ((uint32_t)0x08010000 + 0x70001)   /* End @ of user Flash area */

//#define LED1_PIN                         GPIO_PIN_9
//#define LED1_GPIO_PORT                   GPIOB
//#define LED1_GPIO_CLK                    RCU_GPIOB
//#define LED1_ON()                        GPIO_BOP(LED1_GPIO_PORT) = LED1_PIN
//#define LED1_OFF()                       GPIO_BC(LED1_GPIO_PORT) = LED1_PIN


#define USART0_CLK                    RCU_USART0
#define USART0_TX_PIN                 GPIO_PIN_9
#define USART0_TX_GPIO_PORT           GPIOA
#define USART0_RX_PIN                 GPIO_PIN_10
#define USART0_RX_GPIO_PORT           GPIOA
#define USART0_TX_GPIO_CLK            RCU_GPIOA
#define USART0_RX_GPIO_CLK            RCU_GPIOA


#define UID_ADDR           0x1FFFF7E8



uint8_t writeToFlash32(uint32_t* databuf, uint32_t writelength, uint32_t targetflashaddress);
uint8_t writeToFlash(char* databuf, uint32_t writelength, uint32_t targetflashaddress);
uint8_t erase_flash( uint32_t writelength, uint32_t targetflashaddress);
void iap_load_app(uint32_t appxaddr);
#endif//__BSP_H
