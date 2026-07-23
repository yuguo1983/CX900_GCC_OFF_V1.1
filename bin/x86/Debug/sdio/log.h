
#ifndef __LOG_H__
#define __LOG_H__

#include "usart.h"

#define LOG_ERROR                      (0x01)
#define LOG_WARNING                    (0x02)
#define LOG_NOTICE                     (0x04)
#define LOG_INFO                       (0x08)
#define LOG_DEBUG                      (0x10)

/* This log macro must be set befor compiler, output error, warning, info debug lever */
#define DEBUG_LEVEL_SWITCH             (0xFF)
#define LOGHEARD			"CX900"
#define DebugPrintf(fmt, arg...)          printf((const char*)fmt, ##arg) 

#if ((DEBUG_LEVEL_SWITCH & LOG_ERROR) == LOG_ERROR)
#define log_err(fmt, arg...)      DebugPrintf("%s:[%s@%s,%d]"fmt"\r\n",LOGHEARD,__FUNCTION__,__FILE__,__LINE__, ##arg)
#else
    #define log_err(fmt, arg...)
#endif

#if ((DEBUG_LEVEL_SWITCH & LOG_WARNING) == LOG_WARNING)
    #define log_warn(fmt, arg...)      DebugPrintf("%s:"fmt"\r\n",LOGHEARD, ##arg)
#else
    #define log_warn(fmt, arg...)
#endif

#if ((DEBUG_LEVEL_SWITCH & LOG_NOTICE) == LOG_NOTICE)
    #define log_notice(fmt, arg...)      DebugPrintf("%s:"fmt"\r\n",LOGHEARD, ##arg)
#else
    #define log_notice(fmt, arg...)
#endif

#if ((DEBUG_LEVEL_SWITCH & LOG_INFO) == LOG_INFO)
    #define log_info(fmt, arg...)      DebugPrintf("%s:"fmt"\r\n",LOGHEARD, ##arg)
#else
    #define log_info(fmt, arg...)
#endif

#if ((DEBUG_LEVEL_SWITCH & LOG_DEBUG) == LOG_DEBUG)
#define log_debug(fmt, arg...)      DebugPrintf("%s:[%s@%s,%d]"fmt"\r\n",LOGHEARD,__FUNCTION__,__FILE__,__LINE__, ##arg)
#else
    #define log_debug(fmt, arg...)
#endif

#if ((DEBUG_LEVEL_SWITCH & LOG_DEBUG) == LOG_DEBUG)
#define log_data(data,size)    HAL_UART_Transmit(&huart1,data,size,100)     
#else
    #define log_data(data, size)
#endif
#endif


