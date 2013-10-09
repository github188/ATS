/*
 * log.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef LOG_H_
#define LOG_H_

#include "osa.h"
#include "conf.h"


#undef NDEBUG

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    ATS_LOG_OFF     = 0,
    ATS_LOG_FATAL   = 1,
    ATS_LOG_ERROR   = 2,
    ATS_LOG_WARN    = 3,
    ATS_LOG_INFO    = 4,
    ATS_LOG_DEBUG   = 5,

    ATS_LOG_MAX     = 6,
};


#define LOG_DEFAULT_LEVEL   ATS_LOG_INFO

typedef struct _ATS_LOG
{
    osa_file_t      *file;       // 日志文件
    osa_uint8_t     logLevel;      // 日志等级
} ATS_Log;


#ifndef NDEBUG

#define ATS_LogFatal(fmt, args...)  ATS_LogWrite(ATS_LOG_FATAL, __FILE__, __LINE__, fmt, ##args)
#define ATS_LogError(fmt, args...)  ATS_LogWrite(ATS_LOG_ERROR, __FILE__, __LINE__, fmt, ##args)
#define ATS_LogWarn(fmt, args...)  ATS_LogWrite(ATS_LOG_WARN, __FILE__, __LINE__, fmt, ##args)
#define ATS_LogInfo(fmt, args...)  ATS_LogWrite(ATS_LOG_INFO, __FILE__, __LINE__, fmt, ##args)
#define ATS_LogDebug(fmt, args...)  ATS_LogWrite(ATS_LOG_DEBUG, __FILE__, __LINE__, fmt, ##args)

#else

#define ATS_LogFatal(fmt, args...)
#define ATS_LogError(fmt, args...)
#define ATS_LogWarn(fmt, args...)
#define ATS_LogInfo(fmt, args...)
#define ATS_LogDebug(fmt, args...)

#endif

osa_err_t   ATS_LogOpen(ATS_Conf *cf);
void        ATS_LogClose();
void        ATS_LogWrite(osa_uint8_t logType, char *file, osa_uint32_t line, const char *fmt, ...);
void        ATS_LogSetLevel(osa_uint8_t level);
osa_uint8_t ATS_LogGetLevel();


#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
