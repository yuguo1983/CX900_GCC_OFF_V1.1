#ifndef _CHIP_IIC_H_
#define _CHIP_IIC_H_

#include <stdint.h>

typedef struct
{
	void (*SCL_L)(void);
	void (*SCL_H)(void);
	void (*SDA_L)(void);
	void (*SDA_H)(void);
	
	int (*readSCL)(void);
	int (*readSDA)(void);
	
}
_srtI2CBase;

typedef struct
{
	_srtI2CBase Port1;
	_srtI2CBase Port2;
	_srtI2CBase Port3;
}
_srtI2CPort;

_srtI2CPort *CHIP_IIC_GetInfor(void);
void CHIP_IIC_Init(void);
void CHIP_IIC_WakeUpBus(_srtI2CBase *psrtPort);
int CHIP_IIC_Stop(_srtI2CBase *psrtPort) ;
int CHIP_IIC_Start(_srtI2CBase *psrtPort,unsigned char ucSlaveAddr);
int CHIP_IIC_StartAgain(_srtI2CBase *psrtPort,unsigned char ucSlaveAddr);
int CHIP_IIC_WriteFrame(_srtI2CBase *psrtPort,unsigned char *pucFrame,uint32_t uiLen);
int CHIP_IIC_ReadFrame(_srtI2CBase *psrtPort,unsigned char *pucFrame,uint32_t uiLen);
void CHIP_IIC_WriteByte(_srtI2CBase *psrtPort,unsigned char Data);
#endif
