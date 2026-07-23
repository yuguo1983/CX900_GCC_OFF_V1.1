#ifndef _CALIB_THREAD_H_
#define _CALIB_THREAD_H_

#include <stdint.h>








typedef enum
{
	CALIB_TYPE_NONE=0,
	CALIB_TYPE_V,
	CALIB_TYPE_I,
}
_enumCalibType;


//calib base data ,just voltage,current
typedef struct
{
	int32_t VMonMin;    	//CV mon值0
	int32_t VMonMax;			//CV mon值1
	
	int32_t VOutMin;	//万用表测出2
	int32_t VOutMax;	//万用表测出3
	
	int32_t MAmonMin;	//CV mon值4
	int32_t MAmonMax;	//CV mon值5
	
	int32_t MAOutMin;	//万用表测出6
	int32_t MAOutMax;	//万用表测出7
	
	
	int32_t UAMONMin;	//CC mon值8
	int32_t UAMONMax; //CC mon值9
	
	int32_t UAOUTMin;	//万用表测出10
	int32_t UAOUTMax;  //万用表测出11
	
	int32_t uimAOffsetmin; //空载最小值,在uA校准时候来记录12
	int32_t uimAOffsetmax; //空载最大值,在uA校准时候来记录13	


	int32_t uimAOffset; //空载最小值,在uA校准时候来记录14
	int32_t uiuAOffset; //空载最大值,在uA校准时候来记录15
	


	uint32_t uiIsValid;  //是否校准过16
	
	
}
_srtCalibData;
#define SLOPE_ITEM_OFFSET(member)	(((uint32_t)(&(((_srtCalibData *)0)->member))) / sizeof(uint32_t))
//calib information,include port0,1,2,3 calib result
typedef struct
{
	_srtCalibData Port1;
	_srtCalibData Port2;
	_srtCalibData Port3;
	_srtCalibData Port4;	
	_srtCalibData Port5;
	_srtCalibData Port6;
	_srtCalibData Port7;
	_srtCalibData Port8;
//	_srtCalibData Port9;
//	_srtCalibData Port10;	
}
_srtCalibInfor;


void CALIB_THREAD_Init(void);
int CALIB_THREAD_Poll(void);
uint32_t CALIB_THREAD_VOutToDACCode(uint32_t uiPort,int32_t iValue);
uint32_t CALIB_THREAD_VMonToValue(uint32_t uiPort,int32_t iCode);
uint32_t CALIB_THREAD_VMonToOffset(uint32_t uiPort,int32_t iCode);
uint32_t CALIB_THREAD_IMonToValue(uint32_t uiPort,int32_t iValue);

_srtCalibData *CALIB_THREAD_GetInfor(uint32_t uiPort);


//typedef enum{
//ISNULL=0,
//ISVMODE=1,
//ISIMODE=2,
//}_MODE_TYPE;



typedef struct
{
	uint32_t uiChannel;      //校准通道
	uint32_t uiIsFinish;     //校准是否完成
	uint32_t uiResult;       //校准结果
	uint32_t uiRecordVValue; //实际电压值,根据万用表测量
	uint32_t uiRecordAValue; //实际电流值,根据万用表测量
	uint32_t uiIRange;       //校准档位mA/uA
	uint32_t uiType;         //校准类型,电压校准/电流校准
	uint32_t uiTrigger;      //触发信号
	uint32_t uiStatus;       //状态机
	uint32_t uiTick;         //间隔
	uint32_t uiStartTick;    //起始时刻
	uint32_t uiMODE;  //是否为CV模式
}
_srtCalibPoll;
#define CALIB_ITEM_OFFSET(member)	(((uint32_t)(&(((_srtCalibPoll *)0)->member))) / sizeof(uint32_t))

_srtCalibPoll *CALIB_THREAD_GetPoll(void);
int CALIB_THREAD_StartChannel(uint32_t uiChannel);
int CALIB_THREAD_RecordChannel(uint32_t uiValue,uint32_t uiType);
int CALIB_THREAD_SetIRange(uint32_t uiRange);
int CALIB_THREAD_StartType(uint32_t uiType);
int CALIB_THREAD_RecordTriiger(void);
int CALIB_THREAD_CheckValid(uint32_t uiPort);
void CALIB_THREAD_ValidDefault(void);
int CALIB_THREAD_Setmode(uint32_t mode);


uint32_t CALIB_THREAD_VToVset(uint32_t uiPort,int32_t uiCode);
uint32_t CALIB_THREAD_IToSet(uint32_t uiPort,int32_t uiValue);
uint32_t CALIB_THREAD_ImonToValue(uint32_t uiPort,int32_t uiValue);
uint32_t CALIB_THREAD_VoutToIout(uint32_t uiPort,int32_t uiVIN);
uint32_t CALIB_THREAD_ImonTooffset(uint32_t uiPort, int32_t uiCode);//处理噪音
#endif
