#ifndef LOG_H
#define LOG_H

#include "osa.h"


#define TP_LogFatal(fmt, args...)      osa_log_fatal(fmt, ##args)
#define TP_LogError(fmt, args...)      osa_log_error(fmt, ##args)
#define TP_LogInfo(fmt, args...)       osa_log_info(fmt, ##args)
#define TP_LogDebug(fmt, args...)      osa_log_debug(fmt, ##args)


#endif // LOG_H
