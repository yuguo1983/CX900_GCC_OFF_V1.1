#ifndef __INA220_H_
#define __INA220_H_

#include <stdint.h>
#include <display.h>
#include "calibthread.h"
#include "Function.h"
typedef struct{
uint32_t uTICK;
uint32_t uStatu;
uint32_t uRefresh;
uint32_t ufinish;
uint32_t Itype;	
uint32_t Vvalue;
uint32_t MAvalue;
uint32_t UAvalue;	
uint16_t VUpper;
uint16_t VLower;
uint16_t mAUpper;
uint16_t mALower;
uint16_t uAUpper;
uint16_t uALower;
uint16_t alarm;
uint16_t Aalarm;	
}_DataType ;


typedef struct{
_DataType port1;
_DataType port2;
_DataType port3;	
_DataType port4;	
_DataType port5;
_DataType port6;	
_DataType port7;	
_DataType port8;		
}_ADC_port;


typedef struct {
uint32_t  vol_value;
uint32_t 	all_cut;
uint32_t 	ch1_cut;
uint32_t 	ch2_cut;
uint32_t 	ch3_cut;
uint16_t  VUpper;
uint16_t 	VLower;
uint16_t 	mAUpper;
uint16_t	mALower;
uint16_t	alarm;
}_BK_type;



typedef struct 
{
uint8_t triger;
uint8_t flag;
uint32_t tick;

}ina_220_t;

extern ina_220_t ina_220 ;
extern  _BK_type  bk_type;
/****************************ɪ÷º¯ʽǸ************************/
typedef enum{
NOMAL =0,
ISMA=1,
ISUA=2,
}_Itype;
void Ina220_Iint(void);
int INA220_Init(uint8_t chanel,uint32_t uiPort,uint32_t uiShuntR,uint32_t uiIMaxExpected);
int INA220_GetShuntCurrent(uint8_t chanel,uint32_t uiPort, uint32_t *puiValue);
int INA220_GetVoltage(uint8_t chanel,uint32_t uiPort, uint32_t *puiValue);
_DataType *ADC_THREAD_GetInfor(uint32_t uiPort);
void measurement (void );
void sendtoscreen(void);
uint32_t getVportvalue(uint8_t port);
uint8_t get_port_adcvalue(uint32_t port);
uint32_t getIportvalue(uint8_t port);
int INA220_GetCurrent(uint8_t chanel,uint32_t uiPort,uint32_t *puiValue);
void SET_IRAGE(void);
void Init_Alarm(void);
int ClearAlarm(uint8_t uiPort);
int8_t GetAlarm(uint8_t uiPort);
void AlarmPocess(void);
int GetVolPort(uint8_t uiPort,uint32_t *voltage, uint32_t *current);
void AlarmEnable(uint32_t bit);

void ina220_poll(void);
void reportinfo(void);


#endif
