/*
 * log.h
 *
 * Copyright (C) TuoAn
 *
 */

#ifndef LOG_H_
#define LOG_H_


#include "class.h"
#include "osa.h"


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

    ATS_LOG_MAX     = 6
};


#define LOG_DEFAULT_LEVEL   ATS_LOG_INFO

struct ATS_LOG_CLASS
{
    osa_file_t      *file;       // 日志文件
    osa_uint8_t     level;      // 日志等级
};


#ifndef NDEBUG

#define ats_log_fatal(fmt, args...)  ats_log_write(ATS_LOG_FATAL, __FILE__, __LINE__, fmt, ##args)
#define ats_log_error(fmt, args...)  ats_log_write(ATS_LOG_ERROR, __FILE__, __LINE__, fmt, ##args)
#define ats_log_warn(fmt, args...)  ats_log_write(ATS_LOG_WARN, __FILE__, __LINE__, fmt, ##args)
#define ats_log_info(fmt, args...)  ats_log_write(ATS_LOG_INFO, __FILE__, __LINE__, fmt, ##args)
#define ats_log_debug(fmt, args...)  ats_log_write(ATS_LOG_DEBUG, __FILE__, __LINE__, fmt, ##args)

#else

#define ats_log_fatal(fmt, args...)
#define ats_log_error(fmt, args...)
#define ats_log_warn(fmt, args...)
#define ats_log_info(fmt, args...)
#define ats_log_debug(fmt, args...)

#endif

osa_err_t   ats_log_open(const osa_char_t *logfile);
void        ats_log_close();
void        ats_log_write(osa_uint8_t log_type,
                          const char *file, osa_uint32_t line,
                          const char *fmt, ...);
void        ats_log_set_level(osa_uint8_t level);
osa_uint8_t ats_log_get_level();


#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
