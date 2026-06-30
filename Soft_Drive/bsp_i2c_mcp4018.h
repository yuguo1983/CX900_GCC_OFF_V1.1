/*
*********************************************************************************************************
*
*    模块名称 : 数字电位器MCP4018驱动模块
*    文件名称 : bsp_i2c_mcp4018.h
*    版    本 : V1.0
*    说    明 : 头文件
*
*    
*********************************************************************************************************
*/

#ifndef _BSP_MCP4018_H
#define _BSP_MCP4018_H
#include "gd32f30x.h"
#include "chipiic.h"




void 		bsp_InitMCP4018(void);
int MCP4018_WriteData(uint8_t _ucOpecode);
uint8_t MCP4018_ReadData(void);
void 		bsp_SetTVCC(uint16_t _volt);
void 		MCP4018_GPIO_init(void);

#endif


