/**
 * log.c
 *
 */

 
#include "osa.h"
#include "log.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


static ats_log_t log;


osa_err_t ats_log_open(const osa_char_t *logfile)
{
    osa_assert(logfile != NULL);

    log.file = osa_file_open(logfile, OSA_F_APPEND);
    if (!log.file)
    {
        return OSA_ERR_ERR;
    }

    ats_log_set_level(LOG_DEFAULT_LEVEL);

    return OSA_ERR_OK;
}


void ats_log_close()
{
    if (log.file)
    {
        osa_file_close(log.file);
    }
    log.file = NULL;
}


void ats_log_set_level(osa_uint8_t level)
{
    log.level = level;
}


osa_uint8_t ats_log_get_level()
{
    return log.level;
}


void ats_log_write(osa_uint8_t log_type, char *file, osa_uint32_t line, const char *fmt, ...)
{
    if (log_type > log.level)
    {
        return;
    }

    va_list ap;
    va_start(ap, fmt);

    char        buf[1024] = {0};
    osa_size_t  sz = 0;

    switch (log_type)
    {
    case ATS_LOG_FATAL:
    {
        sz += sprintf(buf, "[FATAL] ");
        break;
    }
    case ATS_LOG_ERROR:
    {
        sz += sprintf(buf, "[ERROR] ");
        break;
    }
    case ATS_LOG_WARN:
    {
        sz += sprintf(buf, "[WARN] ");
        break;
    }
    case ATS_LOG_INFO:
    {
        sz += sprintf(buf, "[INFO] ");
        break;
    }
    case ATS_LOG_DEBUG:
    {
        sz += sprintf(buf, "[DEBUG]<%s, %d> ", file, line);
        break;
    }
    }

    sz += vsprintf(buf+sz, fmt, ap);

    buf[1023] = '\0';

    if (!log.file)
    {
        printf("%s\n", buf);
    }
    else
    {
        osa_file_write(log.file, buf, strlen(buf));
    }

    va_end(ap);
}


#ifdef __cplusplus
}
#endif
