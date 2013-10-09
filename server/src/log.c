/*
 * log.c
 *
 * Copyright (C) TuoAn
 *
 */

#include <stdarg.h>

#include "osa.h"
#include "module.h"
#include "ats.h"
#include "conf_xml.h"
#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif


ATS_Log log;


osa_err_t   ATS_LogOpen(ATS_Conf *cf)
{
    osa_assert(cf != NULL);

    ATS_LogSetLevel(ATS_LOG_OFF);

    CONF_Log cflog;

    if (XML_LogParse(cf, &cflog) != OSA_ERR_OK)
    {
        // 日志已经关闭，所以不能使用ATS_LOG
        osa_log_error("Failed to parse XML file!\n");
        return OSA_ERR_ERR;
    }

    log.file = osa_file_open(cflog.logFile, OSA_F_APPEND);
    if (!log.file)
    {
        osa_log_error("Failed to open log file: %s\n", cflog.logFile);
        return OSA_ERR_ERR;
    }

    ATS_LogSetLevel(cflog.level);

    return OSA_ERR_OK;
}

void    ATS_LogClose()
{
    osa_file_close(log.file);
}

void    ATS_LogSetLevel(osa_uint8_t level)
{
    log.logLevel = level;
}


osa_uint8_t ATS_LogGetLevel()
{
    return log.logLevel;
}


void ATS_LogWrite(osa_uint8_t logType, char *file, osa_uint32_t line, const char *fmt, ...)
{
    if (logType > log.logLevel)
    {
        return;
    }

    va_list ap;
    va_start(ap, fmt);

    char buf[1024] = {0};
    osa_size_t  sz = 0;

    switch (logType)
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
    default:
    {
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
