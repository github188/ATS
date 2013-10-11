#include <stdio.h>
#include <stdarg.h>

#include "sdk_log.h"


static FILE *logfp = NULL;


osa_err_t   SDK_LogOpen(osa_char_t *logfile)
{
    if (logfp)
    {
        SDK_LogClose();
    }
    
    logfp = fopen(logfile, "a");
    if (!logfp)
    {
        return OSA_ERR_ERR;
    }
    
    return OSA_ERR_OK;
}


void        SDK_LogClose()
{
    if (logfp)
    {
        fclose(logfp);
    }
    logfp = NULL;
}


void    _sdkWriteLog(SDK_LogType type, const char *file, int line, const char *fmt, ...)
{
    if (!logfp)
    {
        if (SDK_LogOpen(SDK_LOG_FILE) != OSA_ERR_OK)
        {
            return;
        }
    }
    
    va_list ap;

    va_start(ap, fmt);

    switch (type)
    {
    case SDK_LOG_OFF:
    {
        return;
    }
    case SDK_LOG_FATAL:
    {
        printf("[FATAL] ");
        break;
    }
    case SDK_LOG_ERROR:
    {
        printf("[ERROR] ");
        break;
    }
    case SDK_LOG_WARN:
    {
        printf("[WARN] ");
        break;
    }
    case SDK_LOG_INFO:
    {
        printf("[INFO] ");
        break;
    }
    }
    
    vfprintf(logfp, fmt, ap);
    
    fflush(logfp);
    
    va_end(ap);
}