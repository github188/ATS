/**
 *  osa_log.c
 *
 */


#include "osa_types.h"
#include "osa_log.h"

#include <stdarg.h>


void    _logit(osa_logtype_t type, osa_char_t *f, osa_uint32_t l, const osa_char_t *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);

    switch (type)
    {
    case OSA_LOG_OFF:
    {
        return;
    }
    case OSA_LOG_FATAL:
    {
        printf("[OSA_FATAL] ");
        break;
    }
    case OSA_LOG_ERROR:
    {
        printf("[OSA_ERROR] ");
        break;
    }
    case OSA_LOG_WARN:
    {
        printf("[OSA_WARN] ");
        break;
    }
    case OSA_LOG_INFO:
    {
        printf("[OSA_INFO] ");
        break;
    }
    case OSA_LOG_DEBUG:
    {
        printf("[OSA_DEBUG]<%s, %d> ", f, l);
        break;
    }
    case OSA_LOG_MAX:
    default:
    {
        break;
    }
    }

    vprintf(fmt, ap);
    fflush(stdout);

    va_end(ap);
}
