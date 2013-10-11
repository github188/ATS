/**
 *  sdk_log.h
 *
 */


#ifndef __SDK_LOG_H__
#define __SDK_LOG_H__


#include "osa.h"


#ifdef __cplusplus
extern "C"
{
#endif



typedef enum
{
    SDK_LOG_OFF = 0,
    SDK_LOG_FATAL = 1,
    SDK_LOG_ERROR = 2,
    SDK_LOG_WARN = 3,
    SDK_LOG_INFO = 4
}SDK_LogType;


#define     SDK_LOG_FILE        "C:\\SDK_log.txt"


OSA_API osa_err_t   SDK_LogOpen(osa_char_t *logfile);
OSA_API void        SDK_LogClose();


OSA_API void    _sdkWriteLog(SDK_LogType type, const char *file, int line, const char *fmt, ...);


#define SDK_LogFatal(fmt, ...)  _sdkWriteLog(SDK_LOG_FATAL, NULL, 0, fmt, __VA_ARGS__);
#define SDK_LogError(fmt, ...)  _sdkWriteLog(SDK_LOG_ERROR, NULL, 0, fmt, __VA_ARGS__);
#define SDK_LogWarn(fmt, ...)   _sdkWriteLog(SDK_LOG_WARN, NULL, 0, fmt, __VA_ARGS__);
#define SDK_LogInfo(fmt, ...)   _sdkWriteLog(SDK_LOG_INFO, NULL, 0, fmt, __VA_ARGS__);


#ifdef __cplusplus
}
#endif

#endif