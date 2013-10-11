/**
 *  osa_log.h
 *
 */


#ifndef __OSA_LOG_H__
#define __OSA_LOG_H__


#include "osa_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


typedef enum
{
    OSA_LOG_OFF = 0,
    OSA_LOG_FATAL,
    OSA_LOG_ERROR,
    OSA_LOG_WARN,
    OSA_LOG_INFO,
    OSA_LOG_DEBUG,

    OSA_LOG_MAX,
}
osa_logtype_t;

#ifndef OSA_NO_DEBUG

#if (defined(__MINGW32__) || defined(__GNUC__) || defined(GCC))

#define osa_log_fatal(fmt, msg...)  _logit(OSA_LOG_FATAL, NULL, 0, fmt, ##msg);
#define osa_log_error(fmt, msg...)  _logit(OSA_LOG_ERROR, NULL, 0, fmt, ##msg);
#define osa_log_warn(fmt, msg...)   _logit(OSA_LOG_WARN, NULL, 0, fmt, ##msg);
#define osa_log_info(fmt, msg...)   _logit(OSA_LOG_INFO, NULL, 0, fmt, ##msg);
#define osa_log_debug(fmt, msg...)  _logit(OSA_LOG_DEBUG, __FILE__, __LINE__, fmt, ##msg);

#else

#define osa_log_fatal(fmt, ...)  _logit(OSA_LOG_FATAL, NULL, 0, fmt, __VA_ARGS__);
#define osa_log_error(fmt, ...)  _logit(OSA_LOG_ERROR, NULL, 0, fmt, __VA_ARGS__);
#define osa_log_warn(fmt, ...)   _logit(OSA_LOG_WARN, NULL, 0, fmt, __VA_ARGS__);
#define osa_log_info(fmt, ...)   _logit(OSA_LOG_INFO, NULL, 0, fmt, __VA_ARGS__);
#define osa_log_debug(fmt, ...)  _logit(OSA_LOG_DEBUG, __FILE__, __LINE__, fmt, __VA_ARGS__);

#endif

#else

#define osa_log_fatal(fmt, ...)
#define osa_log_error(fmt, ...)
#define osa_log_warn(fmt, ...)
#define osa_log_info(fmt, ...)
#define osa_log_debug(fmt, ...)

#endif


void    _logit(osa_logtype_t type, osa_char_t *f, osa_uint32_t l, const osa_char_t *fmt, ...);



#ifdef __cplusplus
}
#endif

#endif
