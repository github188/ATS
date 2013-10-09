/**
 *  osa_log.c
 *
 */


#include "osa_types.h"
#include "osa_log.h"

#include <stdarg.h>


void    _logit(osa_logtype_t type, osa_char_t *f, osa_uint32_t l, osa_char_t *fmt, ...)
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
        printf("[FATAL] ");
        break;
    }
    case OSA_LOG_ERROR:
    {
        printf("[ERROR] ");
        break;
    }
    case OSA_LOG_WARN:
    {
        printf("[WARN] ");
        break;
    }
    case OSA_LOG_INFO:
    {
        printf("[INFO] ");
        break;
    }
    case OSA_LOG_DEBUG:
    {
        printf("[DEBUG]<%s, %d> ", f, l);
        break;
    }
    case OSA_LOG_MAX:
    default:
    {
        break;
    }
    }

    vprintf(fmt, ap);

    va_end(ap);
}
