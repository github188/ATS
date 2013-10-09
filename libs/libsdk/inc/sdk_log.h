/**
 *  sdk_log.h
 *
 */


#ifndef __SDK_LOG_H__
#define __SDK_LOG_H__


#include "osa.h"


#define     SDK_LogFatal(fmt, args...)      osa_log_info(fmt, ##args)
#define     SDK_LogError(fmt, args...)      osa_log_error(fmt, ##args)
#define     SDK_LogWarn(fmt, args...)       osa_log_warn(fmt, ##args)
#define     SDK_LogInfo(fmt, args...)       osa_log_info(fmt, ##args)


#endif